import numpy as np
import scipy.linalg

def decompose_and_solve(A, b):  
    P, L, U = scipy.linalg.lu(A)
    b = b.reshape(-1, 1)  
    Pb = np.dot(P, b)
    y = scipy.linalg.solve_triangular(L, Pb, lower=True)
    if np.isclose(U[-1, -1], 0): 
        x = np.linalg.lstsq(A, b, rcond=None)[0]
    else:
        x = scipy.linalg.solve_triangular(U, y)
    x = x.flatten()
    return P, L, U, x  

def main():   
    n = int(input())
    A = []
    for _ in range(n):
        row = list(map(float, input().split()))
        A.append(row)
    b = list(map(float, input().split()))

    A = np.array(A)
    b = np.array(b)

    try:
        P, L, U, x = decompose_and_solve(A, b)  
        
        print(f"P ({n}x{n}):\n", np.round(P, 2))  
        print(f"L ({n}x{n}):\n", np.round(L, 2))  
        print(f"U ({n}x{n}):\n", np.round(U, 2))  
        print("Force magnitudes:", np.round(x, 2))  
    except ValueError as e:
        print(e)

if __name__ == "__main__":  
    main()
