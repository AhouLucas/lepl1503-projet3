import random
import json

points = set()

for _ in range(1_000):
    points.add(tuple([random.randint(-1_000, 1_000) for _ in range(3)]))

res = {
    "vectors": list(points)
}

with open('big.json', 'w') as f:
    json.dump(res, f)