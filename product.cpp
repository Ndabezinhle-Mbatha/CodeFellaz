#include "Product.h"
#include <iostream>
#include <iomanip>
using namespace std;


Product::Product(int productID, string ProductName, int ProductQuantity, double ProductPrice){
    this->productID = productID;
    this->ProductName = ProductName;
    this->ProductQuantity = ProductQuantity;
    this->ProductPrice = ProductPrice;
}

int Product::getQuantity(){ return ProductQuantity;}

void Product::setQuantity(int quantity){ ProductQuantity = quantity;}

int Product::getProductID() { return productID; }

string Product::getName() { return ProductName; }

double Product::getPrice() { return ProductPrice; }

double Product::calculateFinalPrice(){ return ProductPrice; }

void Product::displayProduct(){
     cout << "| " << setw(10) << left << productID
         << "| " << setw(20) << left << ProductName
         << "| " << setw(17) << left << ProductQuantity
         << "| " << setw(13) << left << ProductPrice
         << "| " << setw(13) << left << "Taxable Product"
         << "   |" << endl;
}

