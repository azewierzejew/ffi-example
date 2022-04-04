module Impl where

import Text.Printf (printf)

class ShowIO a where
  showIO :: a -> IO String

foo :: (Eq a, ShowIO a) => a -> a -> IO ()
foo x y =
  do
    sx <- showIO x
    sy <- showIO y
    if x == y
      then printf "%s and %s are equal\n" sx sy
      else printf "%s and %s are not equal\n" sx sy


bar :: ( ShowIO a) => a -> IO ()
bar x =
  do
    sx <- showIO x
    printf "Got: %s\n" sx