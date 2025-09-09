# C++11 Interval Tree Implementation

![Language](https://img.shields.io/badge/language-C%2B%2B11-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A header-only C++11 implementation of a self-balancing Interval Tree. An Interval Tree is a data structure designed to efficiently store and query intervals (ranges). This implementation is augmented with an AVL balancing scheme to ensure that all operations maintain logarithmic time complexity.

## Features

* **Modern C++11**: Utilizes smart pointers (`std::shared_ptr`) for safe, automatic memory management.
* **Header-Only Library**: Easy to integrate into any project by simply including the `IntervalTree.h` file.
* **Templated & Generic**: Can be used with any comparable data type, such as `int`, `float`, or custom numeric types.
* **Self-Balancing (AVL)**: Implements AVL tree rotations (`RotateLeft`, `RotateRight`) to maintain balance, ensuring that insertion and removal operations have a time complexity of O(log n).
* **Rich Query API**: Provides a comprehensive set of functions to find intervals that **overlap** with a given range, **contain** a specific point, and more.

## Requirements

* A C++11 compatible compiler (e.g., GCC 4.8+, Clang 3.3+, MSVC 2015+).

## Usage

As a header-only library, no special compilation or linking is required. Simply include `IntervalTree.h` in your project and create an instance of the `IntervalTree` class.

### Example

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include "IntervalTree.h"

int main() {
    // Create an Interval Tree for integers
    IntervalTree<int> tree;

    // Insert intervals
    tree.Insert(15, 20);
    tree.Insert(10, 30);
    tree.Insert(17, 19);
    tree.Insert(5, 20);
    tree.Insert(12, 15);
    tree.Insert(30, 40);

    std::cout << "Intervals in the tree: " << tree.ToString() << std::endl;
    // Expected output (in-order): [5, 20] [10, 30] [12, 15] [15, 20] [17, 19] [30, 40]

    // Query for intervals overlapping with the range [14, 16]
    std::cout << "\nQuerying for overlaps with [14, 16]:" << std::endl;
    auto overlapping_intervals = tree.Overlapping(14, 16);

    for (const auto& p : overlapping_intervals) {
        std::cout << "  Found overlap: [" << p.first.low << ", " << p.first.high << "]" << std::endl;
    }
    // Expected overlaps: [15, 20], [10, 30], [5, 20], [12, 15]

    return 0;
}
```
API Documentation
The IntervalTree class provides the following public methods:

### Modifiers
* void Insert(T low, T high, ...): Inserts a new interval.

* void Remove(Interval<T> i): Removes an interval.

* void Update(Interval<T> oldInterval, ...): Updates an interval.

* void Clear(): Clears all intervals from the tree.

### Queries
* std::vector<...> Overlapping(T low, T high) const: Finds all intervals that overlap with a given range.

* std::vector<...> Containing(T value) const: Finds all intervals that contain a specific value.

* T MaxHighOverlapping(T low, T high) const: Finds the max high value of overlapping intervals.

* bool Overlaps(T low, T high) const: Checks if any interval overlaps with a range.

* bool Contains(T value) const: Checks if any interval contains a value.

### Utilities
* bool IsEmpty() const: Returns true if the tree is empty.

* size_t Size() const: Returns the number of intervals.

* std::string ToString() const: Returns an in-order string representation.

### License
This project is licensed under the MIT License. See the LICENSE file for details.
