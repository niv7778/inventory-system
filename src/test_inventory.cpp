#include "Inventory.h"
#include <iostream>
#include <cassert>

// Simple assert-based test suite (no external framework required).
// Run with: g++ -std=c++17 test_inventory.cpp Inventory.cpp -o test_inventory && ./test_inventory

void testAddAndFindLinear() {
    Inventory inv;
    inv.addProduct(1, "Item A", 10, 100.0);
    inv.addProduct(2, "Item B", 5, 50.0);

    Product* p = inv.findByIdLinear(2);
    assert(p != nullptr);
    assert(p->name == "Item B");
    assert(p->quantity == 5);

    std::cout << "testAddAndFindLinear passed\n";
}

void testAddAndFindHashMap() {
    Inventory inv;
    inv.addProduct(1, "Item A", 10, 100.0);
    inv.addProduct(2, "Item B", 5, 50.0);

    Product* p = inv.findByIdHashMap(1);
    assert(p != nullptr);
    assert(p->name == "Item A");

    std::cout << "testAddAndFindHashMap passed\n";
}

void testFindMissingReturnsNull() {
    Inventory inv;
    inv.addProduct(1, "Item A", 10, 100.0);

    assert(inv.findByIdLinear(999) == nullptr);
    assert(inv.findByIdHashMap(999) == nullptr);

    std::cout << "testFindMissingReturnsNull passed\n";
}

void testPlaceOrderSucceedsWithEnoughStock() {
    Inventory inv;
    inv.addProduct(1, "Item A", 10, 100.0);

    bool result = inv.placeOrder(1, 4);
    assert(result == true);
    assert(inv.findByIdHashMap(1)->quantity == 6);

    std::cout << "testPlaceOrderSucceedsWithEnoughStock passed\n";
}

void testPlaceOrderFailsWithInsufficientStock() {
    Inventory inv;
    inv.addProduct(1, "Item A", 3, 100.0);

    bool result = inv.placeOrder(1, 10);
    assert(result == false);
    // quantity should remain unchanged after a failed order
    assert(inv.findByIdHashMap(1)->quantity == 3);

    std::cout << "testPlaceOrderFailsWithInsufficientStock passed\n";
}

void testPlaceOrderOnMissingProductFails() {
    Inventory inv;
    bool result = inv.placeOrder(999, 1);
    assert(result == false);

    std::cout << "testPlaceOrderOnMissingProductFails passed\n";
}

void testSizeTracksAddedProducts() {
    Inventory inv;
    assert(inv.size() == 0);
    inv.addProduct(1, "Item A", 10, 100.0);
    inv.addProduct(2, "Item B", 5, 50.0);
    assert(inv.size() == 2);

    std::cout << "testSizeTracksAddedProducts passed\n";
}

void testSaveAndLoadRoundTrip() {
    Inventory inv;
    inv.addProduct(1, "Item A", 10, 100.5);
    inv.addProduct(2, "Item B", 5, 50.25);
    inv.saveToFile("test_inventory.csv");

    Inventory loaded;
    loaded.loadFromFile("test_inventory.csv");

    assert(loaded.size() == 2);
    Product* p = loaded.findByIdHashMap(2);
    assert(p != nullptr);
    assert(p->name == "Item B");
    assert(p->quantity == 5);

    std::cout << "testSaveAndLoadRoundTrip passed\n";
}

int main() {
    testAddAndFindLinear();
    testAddAndFindHashMap();
    testFindMissingReturnsNull();
    testPlaceOrderSucceedsWithEnoughStock();
    testPlaceOrderFailsWithInsufficientStock();
    testPlaceOrderOnMissingProductFails();
    testSizeTracksAddedProducts();
    testSaveAndLoadRoundTrip();

    std::cout << "\nAll tests passed!\n";
    return 0;
}
