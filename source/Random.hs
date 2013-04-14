import Control.Monad
import Data.List(intercalate)
import System.Environment
import System.Random

main = do
  args <- liftM (map read) getArgs
  if length args /= 2 then
    putStrLn "Usage: ./Random { element-count } { limit }"
    else
    let extract = take (args !! 0) . map (abs . flip rem (args !! 1))
    in do numbers <- liftM (extract . randoms) getStdGen :: IO [Int]
          putStrLn $ intercalate ", " $ map show numbers
