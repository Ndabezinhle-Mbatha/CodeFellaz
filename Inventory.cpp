#include "Inventory.h"
#include "Product.h"
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <thread>

using namespace std;

//Method For A adding Product In Products Map
bool Inventory::addProduct(shared_ptr<Product> product){

    lock_guard<mutex> lock(inventoryMutex);
    int productID = product->getProductID();

    auto it = products.find(productID);//Single Map Lookup

    if(it != products.end()){//Product Already Exists
        return false;
    }

    products[productID] = product;//Insert Product
    return true;
}
//Method For Removing Product in products map using it productID
bool Inventory::removeProduct(int productID){
    lock_guard<mutex> lock(inventoryMutex);//Lock mutex To Ensure Thread Safe Read Access
    if(products.count(productID)){//Checks If The Product With That productID Exists inside map container
        products.erase(productID);  //Removing That Product If Exist
        return true;
    }
    return false; //If Entered The Product that do not exist inside map
}

bool Inventory::searchProduct(int ProductID){
    lock_guard<mutex> lock(inventoryMutex); //Lock mutex To Ensure Thread Safe Read Access

    //find_if Scans The Map And Returns An Iterator To The First Product
    //Whose ID matches ProductID
    auto it = find_if(products.begin(), products.end(),
        [ProductID](const auto& pair){
            return pair.second->getProductID() == ProductID;
        });

    if(it != products.end()){
        cout << "Product found!\n";
        cout << "Name: " << it->second->getName()
             << " | Quantity: " << it->second->getQuantity()
             << " | Price: R" << it->second->getPrice() << endl;
        return true;
    }
    cout << "Product not found!" << endl;
    return false;
}

void Inventory::displayAllProduct(){
    DisplayTableHeader();
    lock_guard<mutex> lock(inventoryMutex);
    if(!products.empty()){
        for(auto product : products){ //Iterating through map for displaying all product existing in map
            product.second -> displayProduct();
        }
    }else{
        cout << "| " << setw(10) << left << "N/A"
         << "| " << setw(20) << left << "N/A"
         << "| " << setw(17) << left << "N/A"
         << "| " << setw(13) << left << "N/A"
         << "| " << setw(13) << left << "N/A"
         << "|" << endl;
    }
}

void Inventory::sortByPrice(){
    //Method to sort products by price
    cout << "Products Sorted by Price:"<<endl;
    DisplayTableHeader();
    lock_guard<mutex> lock(inventoryMutex);
    vector<pair<int,shared_ptr<Product>>> sortedByPrice;
    for(auto& item: products){
        sortedByPrice.push_back(item);
    }

    sort(sortedByPrice.begin(), sortedByPrice.end(),[](const auto& a, const auto& b) {//

      return a.second->calculateFinalPrice() < b.second->calculateFinalPrice();
    });

    for (const auto& sortedItems : sortedByPrice) {
        sortedItems.second->displayProduct();
    }
}

void Inventory::sortByQuantity(){
     //Method to sort products by price
    cout << "Products Sorted by quantity:"<<endl;
    DisplayTableHeader();
    lock_guard<mutex> lock(inventoryMutex);
    vector<pair<int,shared_ptr<Product>>> sortedByQuantity;
    for(auto& item: products){
        sortedByQuantity.push_back(item);
    }

    sort(sortedByQuantity.begin(), sortedByQuantity.end(),[](const auto& a, const auto& b) {
      return a.second->getQuantity() < b.second->getQuantity();
    });

    for (const auto& sortedItems : sortedByQuantity) {
        sortedItems.second->displayProduct();
    }
}

bool Inventory::processOrder(Order& order) {
    stringstream ss;

    // Add the header line showing which thread is processing which order
    ss << "[Thread: " << this_thread::get_id()
       << "] Processing Order #" << order.getOrderId() << "\n";

    // Flag to determine whether the order can be processed
    bool canProcess = true;

    // Check stock sufficiency
    {
        // Lock inventory
        lock_guard<mutex> lock(inventoryMutex);

        // Loop through every item in the order
        for (auto& item : order.getItems()) {

            // Try to find the product in the inventory map
            auto it = products.find(item.productId);

            // If product does not exist, fail the order
            if (it == products.end()) {
                ss << "\tORDER FAILED | Product ID: "
                   << item.productId << " NOT FOUND\n\n";
                canProcess = false;
                break;
            }

            // If not enough stock, fail the order
            if (it->second->getQuantity() < item.quantityRequested) {

                ss << "\tORDER FAILED | Product ID: "
                   << item.productId<<" | Product Name: "
                   << it->second->getName()
                   << " | Requested: " << item.quantityRequested
                   << " | In Stock: " << it->second->getQuantity()
                   << "\n\n";
                canProcess = false;
                break;
            }
        }
    } // inventory mutex released here

    // If validation failed, update status and print result
    if (!canProcess) {
        order.setStatus("Failed");
        processedOrders.push_back(make_unique<Order>(order));
        lock_guard<mutex> printLock(printMutex);// Lock output to prevent mixed printing
        cout << ss.str();
        return false;
    }

    double orderTotal = 0;

    // Update stock
    {
        // Lock inventory again to safely update stock
        lock_guard<mutex> lock(inventoryMutex);

        // Loop through each item again
        for (auto& item : order.getItems()) {

            // Get the product from the map
            auto& product = products[item.productId];

            // Calculate total cost for this item
            double lineTotal =
                product->calculateFinalPrice() * item.quantityRequested;

            // Add to total order price
            orderTotal += lineTotal;

            // Reduce product quantity in inventory
            product->setQuantity(
                product->getQuantity() - item.quantityRequested
            );

            // Add details of this item to output
            ss << "\t+ Product ID: "
               << item.productId<<" | Product Name: "
               << product->getName()
               << " x" << item.quantityRequested
               << " | R" << fixed << setprecision(2) << lineTotal
               << " | Remaining Stock: "
               << product->getQuantity() << "\n";
        }

        order.setStatus("Successful");
        processedOrders.push_back(make_unique<Order>(order));
    } // inventory mutex released here

    // output total
    ss << "\tORDER SUCCESSFUL | Total: R"
       << fixed << setprecision(2) << orderTotal << "\n\n";

    // Final output
    {
        // Lock printing so output from different threads does not mix
        lock_guard<mutex> printLock(printMutex);
        cout << ss.str();
    }

    return true;
}

void Inventory::DisplayTableHeader(){
    cout << "+-----------+---------------------+------------------+--------------+-------------------+" << endl;
    cout << "| " << setw(10) << left << "PRODUCT ID"
         << "| " << setw(20) << left << "PRODUCT NAME"
         << "| " << setw(17) << left << "PRODUCT QUANTITY"
         << "| " << setw(13) << left << "PRODUCT PRICE"
          << "| " << setw(13) << left << "PRODUCT TYPE"
         << "     |" << endl;

    cout << "+-----------+---------------------+------------------+--------------+-------------------+" << endl;
}
