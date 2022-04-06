{-# LANGUAGE ScopedTypeVariables #-}

module StubLib (AllocString, castPtrToString, CShow, CEq, IdentityWrapper, Wrapper (castPtrToWrapper)) where

import Control.Exception (assert)
import Data.Char (chr)
import Foreign
  ( ForeignPtr,
    FunPtr,
    Ptr,
    Storable (alignment, peek, sizeOf),
    Word64,
    alignPtr,
    castPtr,
    newForeignPtr,
    plusPtr,
    withForeignPtr,
  )
import Foreign.C (CSize (..))
import GHC.IO (unsafePerformIO)

-- ######################################## Wrapper for C alloc_string ########################################
data AllocString

foreign import ccall unsafe "alloc_string_get_size" allocStringGetSize :: Ptr AllocString -> IO CSize

foreign import ccall unsafe "alloc_string_peek" allocStringPeek :: Ptr AllocString -> CSize -> Word64

foreign import ccall unsafe "&alloc_string_free" allocStringFree :: FunPtr (Ptr AllocString -> IO ())

castPtrToString :: Ptr AllocString -> String
castPtrToString ptr =
  go 0
  where
    -- AllocString is immutable so we can lazily convert it into an Haskell String.
    fPtr :: ForeignPtr AllocString
    size :: CSize
    (fPtr, size) =
      unsafePerformIO $ do
        fPtr <- newForeignPtr allocStringFree ptr
        size <- withForeignPtr fPtr allocStringGetSize
        return (fPtr, size)
    go :: CSize -> String
    go idx = unsafePerformIO $ do
      val <- withForeignPtr fPtr (\ptr -> return (allocStringPeek ptr idx))
      let pref = word64ToString val
      return
        ( if idx + 8 >= size
            then take (fromIntegral (size - idx)) pref
            else
              let rest = go (idx + 8)
               in pref ++ rest
        )
    word64ToString :: Word64 -> String
    word64ToString x =
      f 8 x
      where
        f 0 _ = []
        f n x =
          chr (fromIntegral (x `mod` 256)) : f (n - 1) (x `div` 256)

-- ######################################## Wrapper ########################################
class Wrapper w where
  -- Parse from pointer to start of `a`.
  castPtrToWrapper :: Ptr (w a) -> IO (w a)

  -- INTERNAL.
  -- Get pointer to the start of actual data of `a`.
  getWrappedPtr :: w a -> Ptr a

newtype IdentityWrapper a = IdentityWrapper (Ptr a)

instance Wrapper IdentityWrapper where
  castPtrToWrapper ptr = return $ IdentityWrapper (castPtr ptr)
  getWrappedPtr (IdentityWrapper x) = x

-- ######################################## CShow ########################################
data CShow w a = CShow {cShow :: FunPtr (Ptr a -> Ptr AllocString), cShowValue :: w a}

instance Wrapper w => Wrapper (CShow w) where
  castPtrToWrapper ptr =
    do
      (fShow, ptr) <- peekPtrIncrement ptr
      value <- castPtrToWrapper ptr
      return $ CShow {cShow = fShow, cShowValue = value}
  getWrappedPtr = getWrappedPtr . cShowValue

instance Wrapper w => Show (CShow w a) where
  show x =
    castPtrToString $ applyCShow (cShow x) (getWrappedPtr $ cShowValue x)

foreign import ccall "dynamic"
  applyCShow :: FunPtr (Ptr a -> Ptr AllocString) -> (Ptr a -> Ptr AllocString)

instance (Wrapper w, Eq (w a)) => Eq (CShow w a) where
  x == y = cShowValue x == cShowValue y

-- ######################################## CEq ########################################
data CEq w a = CEq {cEq :: FunPtr (Ptr a -> Ptr a -> Bool), cEqValue :: w a}

instance Wrapper w => Wrapper (CEq w) where
  castPtrToWrapper ptr =
    do
      (fEq, ptr) <- peekPtrIncrement ptr
      value <- castPtrToWrapper ptr
      return $ CEq {cEq = fEq, cEqValue = value}
  getWrappedPtr = getWrappedPtr . cEqValue

instance Wrapper w => Eq (CEq w a) where
  x == y = assert (cEq x == cEq y) (applyCEq (cEq x) (getWrappedPtr x) (getWrappedPtr y))

foreign import ccall "dynamic"
  applyCEq :: FunPtr (Ptr a -> Ptr a -> Bool) -> (Ptr a -> Ptr a -> Bool)

instance (Wrapper w, Show (w a)) => Show (CEq w a) where
  show = show . cEqValue

-- ######################################## Utils ########################################
peekPtrIncrement :: forall a b c. Storable b => Ptr a -> IO (b, Ptr c)
peekPtrIncrement ptrA = do
  let ptrB :: Ptr b = castPtr ptrA `alignPtr` alignment (undefined :: b)
  v <- peek ptrB
  let ptrC :: Ptr c = ptrB `plusPtr` sizeOf v
  return (v, ptrC)