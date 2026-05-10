#pragma once
#include "Product.h"
#include "Order.h"
#include <iostream>
#include <map>
#include <vector>
#include <mutex>
#include <memory>

using namespace std;

class Inventory
{
    private:
        map<int,shared_ptr<Product>> products;
        vector<unique_ptr<Order>> processedOrders;
        mutex inventoryMutex;
        mutex printMutex;

    public:
        bool addProduct(shared_ptr<Product> product);
        bool removeProduct(int productID);
        bool searchProduct(int ProductID);
        void displayAllProduct();
        void sortByPrice();
        void sortByQuantity();
        bool processOrder(Order &order);
        void DisplayTableHeader();

};

