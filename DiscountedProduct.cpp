#include "DiscountedProduct.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//Constructor Accepting Arguement Of Parent Class And Child Class
DiscountedProduct::DiscountedProduct(int ProductId, string ProductName, int ProductQuantity, double ProductPrice)
    : Product(ProductId, ProductName, ProductQuantity, ProductPrice)
{
    this->ProductDiscount = 10;
}

double DiscountedProduct::discountCalculation(){
    return ProductDiscount/100;
}

double DiscountedProduct::calculateFinalPrice(){
    return ProductPrice - (ProductPrice * discountCalculation());
}

void DiscountedProduct::displayProduct(){
    cout << "| " << setw(10) << left << productID
         << "| " << setw(20) << left << ProductName
         << "| " << setw(17) << left << ProductQuantity
         << "| R" << setw(12) << left << calculateFinalPrice()// Price AFTER 10% Discount
         << "| " << setw(13) << left << "Discount (-10%)"
         << "   |" << endl;
}

