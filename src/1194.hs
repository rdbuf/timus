import Control.Applicative
main = interact $ show . sum . map (handshakes . map read . everyNth 2 . drop 2 . words) . drop 1 . lines
handshakes = (sum .) . zipWith (*) <$> scanl1 (+) <*> tail
everyNth n = map head . takeWhile (not . null) . iterate (drop n) . drop (pred n) 
