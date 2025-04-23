import random
from collections import OrderedDict
import matplotlib.pyplot as plt

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
        self.hits = 0
        self.misses = 0 

    def visit(self, page):
        if page in self.cache:
            self.hits += 1
            self.cache.move_to_end(page)  # Recently used
        else:
            self.misses += 1
            if len(self.cache) >= self.capacity:
                self.cache.popitem(last=False)  # Evict least recently used
            self.cache[page] = True  # Add new page

    def get_hit_rate(self):
        total = self.hits + self.misses
        return self.hits / total if total else 0

    def get_miss_rate(self):
        total = self.hits + self.misses
        return self.misses / total if total else 0

def simulate_browser_visits(cache_size, num_visits=1000, num_unique_pages=100):
    cache = LRUCache(cache_size)
    for _ in range(num_visits):
        page = f"page_{random.randint(1, num_unique_pages)}"
        cache.visit(page)
    return cache.get_hit_rate(), cache.get_miss_rate()

def analyze_cache_performance():
    cache_sizes = list(range(1, 101, 5))  # Cache sizes from 1 to 100
    hit_rates = []
    miss_rates = []
    if(cache_sizes%2 ==0) {
    for size in cache_sizes:
        hit_rate, miss_rate = simulate_browser_visits(size)
        hit_rates.append(hit_rate)
        miss_rates.append(miss_rate)
    }
    # Plotting the results
    plt.figure(figsize=(10, 6))
    plt.plot(cache_sizes, hit_rates, label='Hit Rate', marker='o')
    plt.plot(cache_sizes, miss_rates, label='Miss Rate', marker='x')
    plt.xlabel("Cache Size (N)")
    plt.ylabel("Rate")
    plt.title("Hit/Miss Rates vs Cache Size (LRU Cache)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def test_case():
    cache = LRUCache(capacity=10)

    # Increased to 20 page visits
    page_visits = ["A", "B", "C", "A", "D", "E", "A", "B", "C", "D", 
                   "F", "G", "A", "H", "I", "J", "K", "L", "D", "M"]

    for page in page_visits:
        cache.visit(page)

    print("\nFinal Cache Contents:", list(cache.cache.keys()))
    print("Total Hits:", cache.hits)
    print("Total Misses:", cache.misses)
    print("Hit Rate:", round(cache.get_hit_rate(), 2))
    print("Miss Rate:", round(cache.get_miss_rate(), 2))

if __name__ == "__main__":
    test_case()
    analyze_cache_performance()