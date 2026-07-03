# Inventory & Order Management System (C++)

A console-based inventory management system that supports adding products,
placing orders, and persisting data to a file — built to compare two search
strategies (linear search vs. hash map lookup) on the same dataset.

## Features

- Add products (id, name, quantity, price)
- View all products
- Place an order (reduces stock, fails gracefully if insufficient stock)
- Save/load inventory data to/from a CSV file
- Two lookup implementations on the same data, for comparison:
  - `findByIdLinear` — O(n) linear scan over a `std::vector`
  - `findByIdHashMap` — O(1) average lookup via `std::unordered_map`

## Why two search implementations?

The project includes a small benchmark (see `main.cpp`) that loads 100,000
products and times both search methods for the same lookup. On a typical
run:

```
Loaded 100000 products.
Linear search (O(n)):   374 microseconds
Hash map search (O(1)): 0 microseconds
Hash map lookup was ~374x faster on this run.
```

This demonstrates why choosing the right data structure matters once an
application has to handle a large number of records — a linear scan that's
fine for 10 products becomes a real bottleneck at scale, while a hash map
stays fast regardless of dataset size.

## Project layout

```
inventory-system/
├── README.md
└── src/
    ├── Inventory.h          # Product struct + Inventory class declaration
    ├── Inventory.cpp        # Inventory class implementation
    ├── main.cpp             # Demo + performance benchmark
    └── test_inventory.cpp   # Assert-based test suite (8 tests)
```
## Sample Output

```
=== Inventory Demo ===

Initial inventory:
ID      Name                Qty       Price
101     Wireless Mouse      50        499
102     Mechanical Keyboard 30        2499
103     USB-C Hub           100       899

Placing an order: 5 x Wireless Mouse (id 101)
Order succeeded.

Attempting to over-order: 1000 x USB-C Hub (id 103)
Order failed (insufficient stock).

Inventory after orders:
ID      Name                Qty       Price
101     Wireless Mouse      45        499
102     Mechanical Keyboard 30        2499
103     USB-C Hub           100       899

Saved inventory to inventory.csv

=== Performance Benchmark: Linear Search vs Hash Map ===
Loaded 100000 products.
Linear search (O(n)):   374 microseconds (found: Product99999)
Hash map search (O(1)): 0 microseconds (found: Product99999)
Hash map lookup was ~374x faster on this run.
```

```
testAddAndFindLinear passed
testAddAndFindHashMap passed
testFindMissingReturnsNull passed
testPlaceOrderSucceedsWithEnoughStock passed
testPlaceOrderFailsWithInsufficientStock passed
testPlaceOrderOnMissingProductFails passed
testSizeTracksAddedProducts passed
testSaveAndLoadRoundTrip passed

All tests passed!
```

## Build & run

Requires a C++17-compatible compiler (e.g. g++).

```bash
# Run the demo + benchmark
g++ -std=c++17 -O2 -o inventory_demo main.cpp Inventory.cpp
./inventory_demo

# Run the tests
g++ -std=c++17 -o test_inventory test_inventory.cpp Inventory.cpp
./test_inventory
```

## Tests

`test_inventory.cpp` covers: adding and finding products (both search
methods), searching for a missing product, placing a successful order,
placing an order that exceeds available stock, ordering a non-existent
product, tracking inventory size, and a save/load round trip to file.
