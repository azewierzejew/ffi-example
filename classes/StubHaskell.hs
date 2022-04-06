-- Exports stubs from to C for Haskell functions.

module StubHaskell () where

import Control.Exception (assert)
import Foreign
import Foreign.C.String
import Foreign.C.Types
import Foreign.Storable
import Impl
import StubLib
import System.IO
import Text.Printf (printf)

-- ######################################## Stub ########################################
fooHaskellStub :: Ptr (CShow (CEq IdentityWrapper) a) -> Ptr (CShow (CEq IdentityWrapper) a) -> IO ()
fooHaskellStub xPtr yPtr = do
  x <- castPtrToWrapper xPtr
  y <- castPtrToWrapper yPtr
  foo x y

barHaskellStub :: Ptr (CShow IdentityWrapper a) -> IO ()
barHaskellStub xPtr = do
  x <- castPtrToWrapper xPtr
  bar x

foreign export ccall fooHaskellStub :: Ptr (CShow (CEq IdentityWrapper) a) -> Ptr (CShow (CEq IdentityWrapper) a) -> IO ()

foreign export ccall barHaskellStub :: Ptr (CShow IdentityWrapper a) -> IO ()