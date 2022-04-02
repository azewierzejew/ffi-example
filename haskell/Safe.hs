{-# LANGUAGE ForeignFunctionInterface #-}

module Safe where

import Foreign.C.Types
import Text.Printf (printf)

fibonacciHs :: CInt -> IO CInt
fibonacciHs n = do
  printf "Fib Hs: %d\n" (fromIntegral n :: Int)
  if n <= 1
    then return n
    else do
      c <- fibonacciC (n - 2)
      hs <- fibonacciHs (n - 1)
      return (hs + c)

foreign export ccall fibonacciHs :: CInt -> IO CInt

foreign import ccall safe "fibonacciC" fibonacciC :: CInt -> IO CInt