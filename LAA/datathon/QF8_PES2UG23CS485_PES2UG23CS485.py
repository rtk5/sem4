import numpy as np
from numpy.linalg import matrix_rank

def compute_rank_and_nullity(A):
    rank = matrix_rank(A)  # Compute the rank using numpy's matrix_rank function
    nullity = A.shape[1] - rank  # Nullity = Number of columns - Rank
    return rank, nullity

# Read input
m, n = map(int, input().split())
A = []
for _ in range(m):
    row = list(map(int, input().split()))
    A.append(row)

# Convert to numpy array
A = np.array(A)

# Compute rank and nullity
rank, nullity = compute_rank_and_nullity(A)

# Print the result
print(rank, nullity)