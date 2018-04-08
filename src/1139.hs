main = interact $ show . run . map (pred . read) . words
run [a, b] = (a `div` gcd a b + b `div` gcd a b - 1) * gcd a b