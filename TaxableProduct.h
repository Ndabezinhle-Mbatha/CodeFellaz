#pragma once
#include "Product.h"
#include <string>

class TaxableProduct : public Product{
    private:
        const double productTax = 15.0;

    public:
        TaxableProduct(int ProductId, std::string ProductName, int ProductQuantity, double ProductPrice);
            

        double calculateFinalPrice() override;
        void displayProduct() override;
};
