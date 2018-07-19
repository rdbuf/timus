import Control.Applicative
import Data.Monoid
import Data.List
import Data.Ratio

deleteAt idx = (<>) <$> take idx <*> drop (idx + 1)

(<.>) = (sum .) . zipWith (*)
(<->) = zipWith (-)
(<+>) = zipWith (+)
(^+>) = map . (+)
(^*>) = map . (*)

det [] = Just 1
det matrix | not . all ((== length matrix) . length) $ matrix = Nothing
           | otherwise = fmap sum . sequence $ zipWith (fmap . (*)) coefficients (map det submatrices) where
    coefficients = zipWith ($) (cycle [id, negate]) (head matrix)
    submatrices = map ($ transpose . tail $ matrix) (map deleteAt [0..dim-1])
    dim = length . head $ matrix

orthogonal a b = a <.> b == 0
complanar a b c d = det [b <-> a, c <-> a, d <-> a] == Just 0
projectionCoeff target source = (source <.> target) % (target <.> target)

main = do
    [a,b,c,d] <- map (map read . words) . lines <$> getContents
    let valid = orthogonal (b <-> a) (d <-> c) && complanar a b c d && coordinatesValid where
        coordinatesValid = c' !! 0 >= b' !! 0 && (c' !! 1 >= 0) == (d' !! 1 >= 0) && abs (c' !! 1) < abs (d' !! 1)
        a' = [0, 0]
        b' = [1, 0]
        c' = [projectionCoeff (b <-> a) (c <-> a), projectionCoeff (d <-> c) (c <-> a)]
        d' = c' <+> [0, 1]
    putStr $ if valid then "Valid" else "Invalid"
