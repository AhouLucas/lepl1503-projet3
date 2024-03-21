import time
import random
import json
import subprocess
import numpy as np

python_perf = []
c_perf = []
num_points = []

for i in range(1, 500, 10):
    print("Iter", i)

    points = set()

    for _ in range(10 * i):
        points.add(tuple([random.randint(-1_000, 1_000) for _ in range(3)]))

    num_points.append(10 * i)

    res = {
        "vectors": list(points)
    }

    with open("bench.json", "w") as f:
        json.dump(res, f)

    subprocess.run(["python", "json_to_input.py", "bench.json", "bench.bin"])

    start = time.time()

    subprocess.run(["python", "k-means.py", "-k", "3", "-p", "5", "bench.bin", "-f", "output-py.csv"])

    end = time.time()

    python_perf.append(end - start)

    start = time.time()

    subprocess.run(["../kmeans", "-k", "3", "-p", "5", "bench.bin", "-f", "output-c.csv"])

    end = time.time()

    c_perf.append(end - start)