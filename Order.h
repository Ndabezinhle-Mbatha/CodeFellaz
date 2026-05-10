#pragma once
#include <string>
#include <vector>
using namespace std;

// Represents one product line inside an order
struct OrderItem {
    int productId;
    int quantityRequested;
};

class Order {
    private:
        int OrderId;
        vector<OrderItem> items;   //Contains product quantity and product id
        string status;

    public:
        Order(int OrderId, vector<OrderItem> items, string status);

        int getOrderId();
        vector<OrderItem>& getItems();
        string getStatus();
        void setStatus(string status);
};
