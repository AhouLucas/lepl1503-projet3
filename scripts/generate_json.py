import random
import json

points = set()

for _ in range(1_000_000):
    points.add(tuple([random.randint(0, 1_000_000) for _ in range(2)]))

res = {
    "vectors": list(points)
}

with open('big.json', 'w') as f:
    json.dump(res, f)