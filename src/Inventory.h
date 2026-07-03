#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <unordered_map>

// A single product record in the inventory.
struct Product {
    int id;
    std::string name;
    int quantity;
    double price;
};

// Inventory system supporting two lookup strategies for the same data:
//  - Linear search over a std::vector (O(n) per lookup)
//  - Hash map lookup over an std::unordered_map (O(1) average per lookup)
//
// Both are kept in sync so we can fairly benchmark search performance
// against each other on the same dataset.
class Inventory {
public:
    // Adds a product to both the vector and the hash map.
    void addProduct(int id, const std::string& name, int quantity, double price);

    // O(n) search: scans the vector until it finds a matching id.
    // Returns nullptr if not found.
    Product* findByIdLinear(int id);

    // O(1) average search: direct hash map lookup by id.
    // Returns nullptr if not found.
    Product* findByIdHashMap(int id);

    // Reduces stock for a given product id (simulates placing an order).
    // Returns true if the order succeeded (enough stock was available).
    bool placeOrder(int id, int quantityOrdered);

    // Prints all products currently in the inventory.
    void printAll() const;

    // Number of products currently stored.
    size_t size() const;

    // Saves all products to a CSV file.
    void saveToFile(const std::string& filename) const;

    // Loads products from a CSV file (clears existing data first).
    void loadFromFile(const std::string& filename);

private:
    std::vector<Product> products;                 // backing store for linear search
    std::unordered_map<int, size_t> idToIndex;      // id -> index into `products`, for O(1) lookup
};

#endif
