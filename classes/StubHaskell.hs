{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE UndecidableInstances #-}

module StubHaskell where

import Control.Exception (assert)
import Foreign
import Foreign.C.String
import Foreign.C.Types
import Foreign.Storable
import Impl
import Text.Printf (printf)

-- ######################################## Wrapper ########################################
class Wrapper w where
  getValue :: w a -> Ptr a

newtype IdentityWrapper a = IdentityWrapper (Ptr a)

instance Wrapper IdentityWrapper where
  getValue (IdentityWrapper x) = x

unwrapStringView :: StringView -> CStringLen
unwrapStringView (StringView x) = x

newtype StringView = StringView CStringLen

instance Storable StringView where
  sizeOf _ = 16
  alignment _ = 8
  peek ptr = do
    len <- peekByteOff ptr 0
    data_ptr <- peekByteOff ptr 8
    return $ StringView (data_ptr, len)
  poke ptr (StringView (data_ptr, len)) = do
    pokeByteOff ptr 0 len
    pokeByteOff ptr 8 data_ptr

-- ######################################## CShow ########################################
data CShow w a = CShow {cShow :: FunPtr (Ptr a -> Ptr StringView), cShowValue :: w a}

instance Wrapper w => Wrapper (CShow w) where
  getValue = getValue . cShowValue

instance Wrapper w => ShowIO (CShow w a) where
  showIO x = do
    stringLen <- peek $ applyCShow (cShow x) (getValue $ cShowValue x)
    peekCStringLen . unwrapStringView $ stringLen

foreign import ccall "dynamic"
  applyCShow :: FunPtr (Ptr a -> Ptr StringView) -> (Ptr a -> Ptr StringView)

instance (Wrapper w, Eq (w a)) => Eq (CShow w a) where
  x == y = cShowValue x == cShowValue y

-- ######################################## CEq ########################################
data CEq w a = CEq {cEq :: FunPtr (Ptr a -> Ptr a -> Bool), cEqValue :: w a}

instance Wrapper w => Wrapper (CEq w) where
  getValue = getValue . cEqValue

instance Wrapper w => Eq (CEq w a) where
  x == y = assert (cEq x == cEq y) (applyCEq (cEq x) (getValue x) (getValue y))

foreign import ccall "dynamic"
  applyCEq :: FunPtr (Ptr a -> Ptr a -> Bool) -> (Ptr a -> Ptr a -> Bool)

instance (Wrapper w, ShowIO (w a)) => ShowIO (CEq w a) where
  showIO = showIO . cEqValue

-- ######################################## Stub ########################################
fooHaskellStub :: Ptr a -> Ptr b -> IO ()
fooHaskellStub xPtr yPtr = do
  xShow <- peekByteOff xPtr 0
  xEq <- peekByteOff xPtr 8
  let x = xPtr `plusPtr` 16
  yShow <- peekByteOff yPtr 0
  yEq <- peekByteOff yPtr 8
  let y = yPtr `plusPtr` 16
  foo
    ( CShow
        { cShow =
            xShow,
          cShowValue = (CEq {cEq = xEq, cEqValue = IdentityWrapper x})
        }
    )
    ( CShow
        { cShow =
            yShow,
          cShowValue = (CEq {cEq = yEq, cEqValue = IdentityWrapper (castPtr y)})
        }
    )

barHaskellStub :: Ptr a -> IO ()
barHaskellStub xPtr = do
  xShow <- peekByteOff xPtr 0
  let x = xPtr `plusPtr` 8
  bar
    ( CShow
        { cShow =
            xShow,
          cShowValue = IdentityWrapper x
        }
    )

foreign export ccall fooHaskellStub :: Ptr a -> Ptr b -> IO ()

foreign export ccall barHaskellStub :: Ptr a -> IO ()