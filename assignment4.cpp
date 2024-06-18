#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

using namespace std;

// Product structure
struct Product {
    string name;
    int quantity;
    double price;
};

// Function to manage inventory operations
void manageInventory(vector<unique_ptr<Product> >& inventory, unordered_map<string, int>& productIndex, char action, const string& productName, int quantity = 0, double price = 0) {
    assert(!productName.empty() && "Product name must not be empty");
    assert(action == 'A' || action == 'R' || action == 'S' || action == 'E' && "Invalid action");

    int index = -1; // Declare index variable outside switch

    switch (action) {
    case 'A': // Add a product
        assert(quantity > 0 && price >= 0 && "Invalid quantity or price");
        inventory.push_back(unique_ptr<Product>(new Product()));
        inventory.back()->name = productName;
        inventory.back()->quantity = quantity;
        inventory.back()->price = price;
        productIndex[productName] = inventory.size() - 1;
        cout << "Product added: " << productName << endl; // Logging
        break;

    case 'R': // Remove a product
        if (productIndex.find(productName) == productIndex.end()) {
            throw invalid_argument("Product not found.");
        }
        index = productIndex[productName];
        inventory.erase(inventory.begin() + index);
        productIndex.erase(productName);
        cout << "Product removed: " << productName << endl; // Logging
        break;

    case 'S': // Search for a product
        if (productIndex.find(productName) == productIndex.end()) {
            throw invalid_argument("Product not found.");
        }
        index = productIndex.at(productName);
        cout << "Product found:" << endl;
        cout << "Name: " << inventory[index]->name << endl;
        cout << "Quantity: " << inventory[index]->quantity << endl;
        cout << "Price: $" << inventory[index]->price << endl; // Logging
        break;

    case 'E': // Exit
        cout << "Exiting..." << endl; // Logging
        break;

    default:
        throw invalid_argument("Invalid action.");
    }
}

int main() {
    vector<unique_ptr<Product> > inventory;
    unordered_map<string, int> productIndex;

    // Test the refactored function with various actions
    try {
        manageInventory(inventory, productIndex, 'A', "Apple", 10, 2.5); // Adding a product
        manageInventory(inventory, productIndex, 'S', "Apple"); // Searching for the product
        manageInventory(inventory, productIndex, 'R', "Apple"); // Removing the product
        manageInventory(inventory, productIndex, 'S', "Apple"); // Attempting to find the removed product (should throw)
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl; // Logging errors
    }

    return 0;
}