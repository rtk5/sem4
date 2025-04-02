import pandas as pd
import matplotlib.pyplot as plt

# Load Horspool values
horspool_df = pd.read_csv("horspool_values.txt")
boyermoore_df = pd.read_csv("boyermoore_values.txt")

# Graph 1: Comparisons vs Pattern Length
plt.figure(figsize=(10, 5))
plt.plot(horspool_df["patternlen"], horspool_df["cmp"], label="Horspool", marker='o', linestyle='--')
plt.plot(boyermoore_df["patternlen"], boyermoore_df["cmp"], label="Boyer-Moore", marker='s', linestyle='-')
plt.xlabel("Pattern Length")
plt.ylabel("Number of Comparisons")
plt.title("Comparisons vs Pattern Length")
plt.legend()
plt.grid(True)
plt.show()

# Graph 2: Time Taken vs Pattern Length
plt.figure(figsize=(10, 5))
plt.plot(horspool_df["patternlen"], horspool_df["timetaken"], label="Horspool", marker='o', linestyle='--')
plt.plot(boyermoore_df["patternlen"], boyermoore_df["timetaken"], label="Boyer-Moore", marker='s', linestyle='-')
plt.xlabel("Pattern Length")
plt.ylabel("Time Taken (ns)")
plt.title("Time Taken vs Pattern Length")
plt.legend()
plt.grid(True)
plt.show()
