class HashTable:
    def __init__(self, size, method="separate_chaining"):
        self.size = size
        self.method = method
        if method == "separate_chaining":
            self.table = [[] for _ in range(size)]  # List of lists for separate chaining
        elif method == "linear_probing":
            self.table = [None] * size  # Flat list for linear probing

    def hash_function(self, key):
        """Simple hash function: sum of ASCII values of characters mod table size."""
        return sum(ord(c) for c in key) % self.size

    def insert(self, key, value):
        """Insert a key-value pair into the hash table."""
        index = self.hash_function(key)
        if self.method == "separate_chaining":
            # Append to the list at the hashed index
            self.table[index].append((key, value))
        elif self.method == "linear_probing":
            # Linear probing to handle collisions
            original_index = index
            while self.table[index] is not None:
                index = (index + 1) % self.size
                if index == original_index:
                    print("Hash table is full!")
                    return
            self.table[index] = (key, value)

    def search(self, key):
        """Search for a key in the hash table and return its value and comparison count."""
        index = self.hash_function(key)
        comparisons = 0

        if self.method == "separate_chaining":
            for k, v in self.table[index]:
                comparisons += 1
                if k == key:
                    return v, comparisons
        elif self.method == "linear_probing":
            start_index = index
            while self.table[index] is not None:
                comparisons += 1
                if self.table[index][0] == key:
                    return self.table[index][1], comparisons
                index = (index + 1) % self.size
                if index == start_index:
                    break

        return None, comparisons

# Example usage
def main():
    size = 10  # Size of hash table
    telephone_book = [
        ("Alice", "12345"),
        ("Bob", "67890"),
        ("Charlie", "54321"),
        ("David", "98765"),
        ("Eve", "56789"),
    ]

    # Separate Chaining
    ht_separate = HashTable(size, method="separate_chaining")
    for name, number in telephone_book:
        ht_separate.insert(name, number)

    # Linear Probing
    ht_linear = HashTable(size, method="linear_probing")
    for name, number in telephone_book:
        ht_linear.insert(name, number)

    # Search for keys and compare the number of comparisons
    search_keys = ["Alice", "Charlie", "Eve"]

    print("Searching for keys using Separate Chaining:")
    for key in search_keys:
        result, comparisons = ht_separate.search(key)
        print(f"Key: {key}, Value: {result}, Comparisons: {comparisons}")

    print("\nSearching for keys using Linear Probing:")
    for key in search_keys:
        result, comparisons = ht_linear.search(key)
        print(f"Key: {key}, Value: {result}, Comparisons: {comparisons}")

if __name__ == "__main__":
    main()
