-- Haskell module with implementation

module Impl where

import Text.Printf (printf)

foo :: (Eq a, Show a) => a -> a -> IO ()
foo x y =
  do
    if x == y
      then printf "%s and %s are equal\n" (show x) (show y)
      else printf "%s and %s are not equal\n" (show x) (show y)

bar :: (Show a) => a -> IO ()
bar x =
  let sx = show x
   in printf "Got string of len: %d, contents: %s.\n" (length sx) sx