import Data.Function
import Control.Applicative
import Data.Monoid
import Data.List
import Data.Ratio

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

projectionK target source = k where
    k = (source <.> target) % (target <.> target)

deleteAt idx = (<>) <$> take idx <*> drop (idx + 1)

orthogonal a b = a <.> b == 0
complanar a b c d = det [b <-> a, c <-> a, d <-> a] == Just 0

main = do
    [a,b,c,d] <- map (map read . words) . lines <$> getContents
    let valid = orthogonal (b <-> a) (d <-> c) && complanar a b c d && validateCoordinates where
        validateCoordinates = c' !! 0 >= b' !! 0 && (c' !! 1 >= 0) == (d' !! 1 >= 0) && abs (c' !! 1) < abs (d' !! 1)
        (a', b', c', d') = ([0, 0], [1, 0], [projectionK (b <-> a) (c <-> a), projectionK (d <-> c) (c <-> a)], c' <+> [0, 1])
    putStr $ if valid then "Valid" else "Invalid"
    return ()