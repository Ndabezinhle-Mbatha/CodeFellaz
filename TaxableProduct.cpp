#include "TaxableProduct.h"
#include <iostream>
#include <iomanip>
using namespace std;

TaxableProduct::TaxableProduct(int ProductId, string ProductName, int ProductQuantity, double ProductPrice)
    : Product(ProductId, ProductName, ProductQuantity, ProductPrice) {}

double TaxableProduct::calculateFinalPrice() {
    return getPrice() * (1 + productTax / 100.0);
}

void TaxableProduct::displayProduct() {
    cout << "| " << setw(10) << left << getProductID()
         << "| " << setw(20) << left << getName()
         << "| " << setw(17) << left << getQuantity()
         << "| R" << setw(12) << left << calculateFinalPrice()
         << "| " << setw(13) << left << "Taxable  (+15%)"
         << "   |" << endl;
}
