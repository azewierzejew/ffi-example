{-# LANGUAGE ForeignFunctionInterface #-}

module Safe where

import Foreign.C.Types
import Text.Printf (printf)

fibHs :: CInt -> IO CInt
fibHs n = do
  printf "Fib Hs: %d\n" (fromIntegral n :: Int)
  if n <= 1
    then return n
    else do
      c <- fibC (n - 2)
      hs <- fibHs (n - 1)
      return (hs + c)

foreign export ccall fibHs :: CInt -> IO CInt

foreign import ccall safe "fibC" fibC :: CInt -> IO CInt