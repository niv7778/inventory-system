#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

void Inventory::addProduct(int id, const std::string& name, int quantity, double price) {
    products.push_back({id, name, quantity, price});
    idToIndex[id] = products.size() - 1;
}

Product* Inventory::findByIdLinear(int id) {
    for (auto& p : products) {
        if (p.id == id) {
            return &p;
        }
    }
    return nullptr;
}

Product* Inventory::findByIdHashMap(int id) {
    auto it = idToIndex.find(id);
    if (it == idToIndex.end()) {
        return nullptr;
    }
    return &products[it->second];
}

bool Inventory::placeOrder(int id, int quantityOrdered) {
    Product* p = findByIdHashMap(id);
    if (p == nullptr || p->quantity < quantityOrdered) {
        return false;
    }
    p->quantity -= quantityOrdered;
    return true;
}

void Inventory::printAll() const {
    std::cout << std::left
               << std::setw(8) << "ID"
               << std::setw(20) << "Name"
               << std::setw(10) << "Qty"
               << "Price\n";
    for (const auto& p : products) {
        std::cout << std::left
                   << std::setw(8) << p.id
                   << std::setw(20) << p.name
                   << std::setw(10) << p.quantity
                   << p.price << "\n";
    }
}

size_t Inventory::size() const {
    return products.size();
}

void Inventory::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    for (const auto& p : products) {
        out << p.id << "," << p.name << "," << p.quantity << "," << p.price << "\n";
    }
}

void Inventory::loadFromFile(const std::string& filename) {
    products.clear();
    idToIndex.clear();

    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string idStr, name, qtyStr, priceStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qtyStr, ',');
        std::getline(ss, priceStr, ',');

        if (idStr.empty()) continue;

        addProduct(std::stoi(idStr), name, std::stoi(qtyStr), std::stod(priceStr));
    }
}
