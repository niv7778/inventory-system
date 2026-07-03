#include "Inventory.h"
#include <iostream>
#include <chrono>

int main() {
    // ---- Part 1: basic usage demo ----
    std::cout << "=== Inventory Demo ===\n\n";

    Inventory store;
    store.addProduct(101, "Wireless Mouse", 50, 499.00);
    store.addProduct(102, "Mechanical Keyboard", 30, 2499.00);
    store.addProduct(103, "USB-C Hub", 100, 899.00);

    std::cout << "Initial inventory:\n";
    store.printAll();

    std::cout << "\nPlacing an order: 5 x Wireless Mouse (id 101)\n";
    bool ok = store.placeOrder(101, 5);
    std::cout << (ok ? "Order succeeded.\n" : "Order failed (insufficient stock).\n");

    std::cout << "\nAttempting to over-order: 1000 x USB-C Hub (id 103)\n";
    ok = store.placeOrder(103, 1000);
    std::cout << (ok ? "Order succeeded.\n" : "Order failed (insufficient stock).\n");

    std::cout << "\nInventory after orders:\n";
    store.printAll();

    store.saveToFile("inventory.csv");
    std::cout << "\nSaved inventory to inventory.csv\n";

    // ---- Part 2: performance comparison, linear search vs hash map ----
    std::cout << "\n=== Performance Benchmark: Linear Search vs Hash Map ===\n";

    Inventory bigStore;
    const int N = 100000;
    for (int i = 0; i < N; i++) {
        bigStore.addProduct(i, "Product" + std::to_string(i), 10, 99.99);
    }
    std::cout << "Loaded " << N << " products.\n";

    int targetId = N - 1; // worst case for linear search: last element

    auto start1 = std::chrono::high_resolution_clock::now();
    Product* p1 = bigStore.findByIdLinear(targetId);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto linearMicros = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();

    auto start2 = std::chrono::high_resolution_clock::now();
    Product* p2 = bigStore.findByIdHashMap(targetId);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto hashMicros = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

    std::cout << "Linear search (O(n)):   " << linearMicros << " microseconds "
               << "(found: " << (p1 ? p1->name : "not found") << ")\n";
    std::cout << "Hash map search (O(1)): " << hashMicros << " microseconds "
               << "(found: " << (p2 ? p2->name : "not found") << ")\n";

    if (hashMicros > 0) {
        std::cout << "Hash map lookup was ~" << (linearMicros / (double)hashMicros)
                   << "x faster on this run.\n";
    }

    return 0;
}
