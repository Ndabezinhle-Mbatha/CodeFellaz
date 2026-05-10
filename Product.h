#pragma once
#include <string>

using namespace std;

class Product {
    protected :
        int productID;
        string ProductName;
        int ProductQuantity;
        double ProductPrice;

    public:
        Product(int productID, string ProductName, int ProductQuantity, double ProductPrice);

        int getQuantity();
        void setQuantity(int quantity);
        int getProductID();
        string getName();
        double getPrice();
        virtual double calculateFinalPrice();
        virtual void  displayProduct();
        virtual ~Product() = default;
};

