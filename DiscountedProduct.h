#pragma once
#include "Product.h"
#include <string>

using namespace std;

class DiscountedProduct : public Product {
    private:
        double ProductDiscount = 10;
        double discountedPrice = 0;

    public:
        DiscountedProduct (int ProductId, std::string ProductName, int ProductQuantity, double ProductPrice);
            
            
        double calculateFinalPrice() override;
        void displayProduct();

    private:
        double discountCalculation();
};


