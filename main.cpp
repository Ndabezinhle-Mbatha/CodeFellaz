#include "Inventory.h"
#include "TaxableProduct.h"
#include "DiscountedProduct.h"
#include "Order.h"
#include "Product.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <random>
#include <sstream>
#include <cctype>

using namespace std;

    Inventory inventory; //The Single Shared Inventory All Threads Operate On
    vector<Order> orders; //Stores All Orders Entered By The User


    void mainMenu() {
               cout<<"\n--------------MAIN MENU------------"<<endl;
               cout<<"     1. Display All Products"<<endl;
               cout<<"     2. Add Product"<<endl;
               cout<<"     3. Remove Product"<<endl;
               cout<<"     4. Search Product"<<endl;
               cout<<"     5. Process Orders"<<endl;
               cout<<"     6. Sort Product By Quantity"<<endl;
               cout<<"     7. Sort Product By Price"<<endl;
               cout<<"     8. Exit"<<endl;
               cout<<"------------------------------------"<<endl;
               cout<<"Enter Choice: ";
    }


    template <typename T>
    void validator(T &value) {
        while (!(cin >> value) || value < 0) {
            cout << "Invalid input! Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    //Specialization for int
    template <>
    void validator<int>(int &value) {
        string input;

        while (true) {
            cin >> input;
            stringstream ss(input);
            int temp;
            char extra;

            if (ss >> temp && !(ss >> extra) && temp >= 0) {
                value = temp;
                break;
            }

            cout << "Enter a valid whole number: ";
        }
    }

    //Specialization for string
    template <>
    void validator<string>(string &value) {
        while (true) {
            getline(cin, value);

            if (value.empty()) {
                cout << "Name cannot be empty!\nEnter product name: ";
                continue;
            }

            bool valid = true;

            for(char c : value) {
                if (!isalpha(static_cast<unsigned char>(c)) && c != ' ') {
                    valid = false;
                    break;
                }
            }

            if(!valid) {
                cout << "Invalid name! Use letters and spaces only.\nEnter product name: ";
                continue;
            }

            break;
        }
    }

    //Pre-load 160 Products Into Inventory
    void loadProduct(){
        inventory.addProduct(make_shared<TaxableProduct>  (1,"GearBox",200,2000));
        inventory.addProduct(make_shared<DiscountedProduct>(2,"Engine",186,20000));
        inventory.addProduct(make_shared<TaxableProduct>  (3,"Clutch",122,8000));
        inventory.addProduct(make_shared<DiscountedProduct>(4,"Brake Pads",300,5000));
        inventory.addProduct(make_shared<TaxableProduct>  (5,"Fan Belt",180,3450));
        inventory.addProduct(make_shared<DiscountedProduct>(6,"Alternator",350,8500));
        inventory.addProduct(make_shared<TaxableProduct>  (7,"Radiator",250,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(8,"Spark Plugs",200,350));
        inventory.addProduct(make_shared<TaxableProduct>  (9,"Oil Filter",160,450));
        inventory.addProduct(make_shared<DiscountedProduct>(10,"Air Filter",300,600));

        inventory.addProduct(make_shared<TaxableProduct>  (11,"Fuel Pump",300,200));
        inventory.addProduct(make_shared<DiscountedProduct>(12,"Shock Absorber",125,2300));
        inventory.addProduct(make_shared<TaxableProduct>  (13,"Timing Belt",322,1800));
        inventory.addProduct(make_shared<DiscountedProduct>(14,"Starter Motor",110,2500));
        inventory.addProduct(make_shared<TaxableProduct>  (15,"Camshaft",250,15000));
        inventory.addProduct(make_shared<DiscountedProduct>(16,"Turbocharger",107,30000));
        inventory.addProduct(make_shared<TaxableProduct>  (17,"Piston Kit",125,5500));
        inventory.addProduct(make_shared<DiscountedProduct>(18,"Crankshaft",106,18000));
        inventory.addProduct(make_shared<TaxableProduct>  (19,"Head Gasket",200,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(20,"Water Pump",108,3500));

        inventory.addProduct(make_shared<TaxableProduct>  (21,"Ignition Coil",133,900));
        inventory.addProduct(make_shared<DiscountedProduct>(22,"Fuel Injector",220,2500));
        inventory.addProduct(make_shared<TaxableProduct>  (23,"Exhaust Pipe",154,4000));
        inventory.addProduct(make_shared<DiscountedProduct>(24,"Catalytic Converter",105,2200));
        inventory.addProduct(make_shared<TaxableProduct>  (25,"Wheel Hub",166,3200));
        inventory.addProduct(make_shared<DiscountedProduct>(26,"Brake Disc",130,2800));
        inventory.addProduct(make_shared<TaxableProduct>  (27,"Steering Rack",109,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(28,"Control Arm",118,2100));
        inventory.addProduct(make_shared<TaxableProduct>  (29,"Drive Shaft",200,9800));
        inventory.addProduct(make_shared<DiscountedProduct>(30,"Differential",88,2700));

        inventory.addProduct(make_shared<TaxableProduct>  (31,"Oil Pan",90,2200));
        inventory.addProduct(make_shared<DiscountedProduct>(32,"Valve Cover",118,1800));
        inventory.addProduct(make_shared<TaxableProduct>  (33,"Throttle Body",200,7500));
        inventory.addProduct(make_shared<DiscountedProduct>(34,"Mass Airflow Sensor",114,3200));
        inventory.addProduct(make_shared<TaxableProduct>  (35,"Oxygen Sensor",185,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(36,"Fuel Tank",178,9500));
        inventory.addProduct(make_shared<TaxableProduct>  (37,"Radiator Cap",150,150));
        inventory.addProduct(make_shared<DiscountedProduct>(38,"Thermostat",301,400));
        inventory.addProduct(make_shared<TaxableProduct>  (39,"Timing Chain",112,3500));
        inventory.addProduct(make_shared<DiscountedProduct>(40,"Serpentine Belt",222,800));

        inventory.addProduct(make_shared<TaxableProduct>  (41,"Wheel Bearing",135,900));
        inventory.addProduct(make_shared<DiscountedProduct>(42,"ABS Sensor",116,1400));
        inventory.addProduct(make_shared<TaxableProduct>  (43,"Brake Caliper",120,2700));
        inventory.addProduct(make_shared<DiscountedProduct>(44,"Brake Drum",115,2100));
        inventory.addProduct(make_shared<TaxableProduct>  (45,"Leaf Spring",159,4500));
        inventory.addProduct(make_shared<DiscountedProduct>(46,"Coil Spring",218,2300));
        inventory.addProduct(make_shared<TaxableProduct>  (47,"Strut Mount",325,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(48,"Ball Joint",240,700));
        inventory.addProduct(make_shared<TaxableProduct>  (49,"Tie Rod End",135,650));
        inventory.addProduct(make_shared<DiscountedProduct>(50,"Sway Bar Link",128,550));

        inventory.addProduct(make_shared<TaxableProduct>  (51,"Power Steering Pump",210,6800));
        inventory.addProduct(make_shared<DiscountedProduct>(52,"Steering Column",106,1200));
        inventory.addProduct(make_shared<TaxableProduct>  (53,"Ignition Switch",189,900));
        inventory.addProduct(make_shared<DiscountedProduct>(54,"Starter Relay",135,300));
        inventory.addProduct(make_shared<TaxableProduct>  (55,"Fuse Box",317,2500));
        inventory.addProduct(make_shared<DiscountedProduct>(56,"Headlight Assembly",120,1500));
        inventory.addProduct(make_shared<TaxableProduct>  (57,"Tail Light",164,1100));
        inventory.addProduct(make_shared<DiscountedProduct>(58,"Fog Light",198,950));
        inventory.addProduct(make_shared<TaxableProduct>  (59,"Side Mirror",212,1800));
        inventory.addProduct(make_shared<DiscountedProduct>(60,"Wiper Motor",196,1300));

        inventory.addProduct(make_shared<TaxableProduct>  (61,"Wiper Blade",160,200));
        inventory.addProduct(make_shared<DiscountedProduct>(62,"Window Regulator",486,2200));
        inventory.addProduct(make_shared<TaxableProduct>  (63,"Door Handle",140,300));
        inventory.addProduct(make_shared<DiscountedProduct>(64,"Door Lock Actuator",118,900));
        inventory.addProduct(make_shared<TaxableProduct>  (65,"Seat Belt",217,2500));
        inventory.addProduct(make_shared<DiscountedProduct>(66,"Airbag Module",205,1800));
        inventory.addProduct(make_shared<TaxableProduct>  (67,"Dashboard Panel",107,8000));
        inventory.addProduct(make_shared<DiscountedProduct>(68,"Instrument Cluster",106,9500));
        inventory.addProduct(make_shared<TaxableProduct>  (69,"Gear Knob",305,350));
        inventory.addProduct(make_shared<DiscountedProduct>(70,"Pedal Set",87,1200));

        inventory.addProduct(make_shared<TaxableProduct>  (71,"Master Cylinder",514,2700));
        inventory.addProduct(make_shared<DiscountedProduct>(72,"Slave Cylinder",116,2300));
        inventory.addProduct(make_shared<TaxableProduct>  (73,"Transmission Mount",208,1900));
        inventory.addProduct(make_shared<DiscountedProduct>(74,"Engine Mount",429,2100));
        inventory.addProduct(make_shared<TaxableProduct>  (75,"Differential Oil",130,400));
        inventory.addProduct(make_shared<DiscountedProduct>(76,"Transmission Fluid",135,450));
        inventory.addProduct(make_shared<TaxableProduct>  (77,"Coolant",311,300));
        inventory.addProduct(make_shared<DiscountedProduct>(78,"Brake Fluid",153,250));
        inventory.addProduct(make_shared<TaxableProduct>  (79,"Power Steering Fluid",128,350));
        inventory.addProduct(make_shared<DiscountedProduct>(80,"Washer Fluid",160,150));

        inventory.addProduct(make_shared<TaxableProduct>  (81,"Battery",159,2200));
        inventory.addProduct(make_shared<DiscountedProduct>(82,"Alternator Belt",125,500));
        inventory.addProduct(make_shared<TaxableProduct>  (83,"Starter Motor Gear",310,3200));
        inventory.addProduct(make_shared<DiscountedProduct>(84,"Spark Plug Wire",140,600));
        inventory.addProduct(make_shared<TaxableProduct>  (85,"Distributor Cap",432,900));
        inventory.addProduct(make_shared<DiscountedProduct>(86,"Rotor Arm",520,450));
        inventory.addProduct(make_shared<TaxableProduct>  (87,"Fuel Filter",650,300));
        inventory.addProduct(make_shared<DiscountedProduct>(88,"Cabin Filter",145,350));
        inventory.addProduct(make_shared<TaxableProduct>  (89,"Intake Manifold",108,7000));
        inventory.addProduct(make_shared<DiscountedProduct>(90,"Exhaust Manifold",30,6500));

        inventory.addProduct(make_shared<TaxableProduct>  (91,"Muffler",110,4000));
        inventory.addProduct(make_shared<DiscountedProduct>(92,"Resonator",112,3500));
        inventory.addProduct(make_shared<TaxableProduct>  (93,"Catalyst Sensor",115,2800));
        inventory.addProduct(make_shared<DiscountedProduct>(94,"Fuel Rail",109,5000));
        inventory.addProduct(make_shared<TaxableProduct>  (95,"Injector Seal Kit",310,600));
        inventory.addProduct(make_shared<DiscountedProduct>(96,"Oil Cooler",111,4200));
        inventory.addProduct(make_shared<TaxableProduct>  (97,"Radiator Fan",411,2600));
        inventory.addProduct(make_shared<DiscountedProduct>(98,"Fan Relay",135,400));
        inventory.addProduct(make_shared<TaxableProduct>  (99,"Timing Cover",213,3100));
        inventory.addProduct(make_shared<DiscountedProduct>(100,"Crank Pulley",90,3700));

        inventory.addProduct(make_shared<TaxableProduct>  (101,"Engine Oil",290,500));
        inventory.addProduct(make_shared<DiscountedProduct>(102,"Grease",240,300));
        inventory.addProduct(make_shared<TaxableProduct>  (103,"Axle Shaft",132,8500));
        inventory.addProduct(make_shared<DiscountedProduct>(104,"CV Joint",148,3200));
        inventory.addProduct(make_shared<TaxableProduct>  (105,"CV Boot",78,450));
        inventory.addProduct(make_shared<DiscountedProduct>(106,"Hub Cap",150,250));
        inventory.addProduct(make_shared<TaxableProduct>  (107,"Wheel Rim",320,4000));
        inventory.addProduct(make_shared<DiscountedProduct>(108,"Tyre",67,1800));
        inventory.addProduct(make_shared<TaxableProduct>  (109,"Spare Wheel",340,2200));
        inventory.addProduct(make_shared<DiscountedProduct>(110,"Jack",500,900));

        inventory.addProduct(make_shared<TaxableProduct>  (111,"Wheel Spanner",125,350));
        inventory.addProduct(make_shared<DiscountedProduct>(112,"Tool Kit",287,1500));
        inventory.addProduct(make_shared<TaxableProduct>  (113,"Tow Hook",172,800));
        inventory.addProduct(make_shared<DiscountedProduct>(114,"Roof Rack",87,3200));
        inventory.addProduct(make_shared<TaxableProduct>  (115,"Boot Liner",367,1200));
        inventory.addProduct(make_shared<DiscountedProduct>(116,"Floor Mats",183,700));
        inventory.addProduct(make_shared<TaxableProduct>  (117,"Seat Cover",210,1100));
        inventory.addProduct(make_shared<DiscountedProduct>(118,"Sun Visor",65,450));
        inventory.addProduct(make_shared<TaxableProduct>  (119,"Glove Box",169,950));
        inventory.addProduct(make_shared<DiscountedProduct>(120,"Cup Holder",310,300));

        inventory.addProduct(make_shared<TaxableProduct>  (121,"Radiator Hose",122,600));
        inventory.addProduct(make_shared<DiscountedProduct>(122,"Heater Core",56,4200));
        inventory.addProduct(make_shared<TaxableProduct>  (123,"Blower Motor",210,2300));
        inventory.addProduct(make_shared<DiscountedProduct>(124,"AC Compressor",236,1400));
        inventory.addProduct(make_shared<TaxableProduct>  (125,"AC Condenser",139,8500));
        inventory.addProduct(make_shared<DiscountedProduct>(126,"AC Evaporator",157,7800));
        inventory.addProduct(make_shared<TaxableProduct>  (127,"Expansion Valve",144,2100));
        inventory.addProduct(make_shared<DiscountedProduct>(128,"Cabin Sensor",78,950));
        inventory.addProduct(make_shared<TaxableProduct>  (129,"Temperature Sensor",328,700));
        inventory.addProduct(make_shared<DiscountedProduct>(130,"Pressure Sensor",220,1200));

        inventory.addProduct(make_shared<TaxableProduct>  (131,"Knock Sensor",55,1500));
        inventory.addProduct(make_shared<DiscountedProduct>(132,"Cam Sensor",114,1800));
        inventory.addProduct(make_shared<TaxableProduct>  (133,"Crank Sensor",92,2000));
        inventory.addProduct(make_shared<DiscountedProduct>(134,"Speed Sensor",200,1100));
        inventory.addProduct(make_shared<TaxableProduct>  (135,"Parking Sensor",182,950));
        inventory.addProduct(make_shared<DiscountedProduct>(136,"Reverse Camera",320,2500));
        inventory.addProduct(make_shared<TaxableProduct>  (137,"Infotainment System",106,15000));
        inventory.addProduct(make_shared<DiscountedProduct>(138,"Speaker Set",270,1800));
        inventory.addProduct(make_shared<TaxableProduct>  (139,"Amplifier",320,4500));
        inventory.addProduct(make_shared<DiscountedProduct>(140,"Subwoofer",400,5000));

        inventory.addProduct(make_shared<TaxableProduct>  (141,"GPS Module",190,3500));
        inventory.addProduct(make_shared<DiscountedProduct>(142,"USB Port",139,400));
        inventory.addProduct(make_shared<TaxableProduct>  (143,"Cigarette Lighter",45,300));
        inventory.addProduct(make_shared<DiscountedProduct>(144,"12V Socket",50,350));
        inventory.addProduct(make_shared<TaxableProduct>  (145,"Horn",300,600));
        inventory.addProduct(make_shared<DiscountedProduct>(146,"Relay Switch",140,250));
        inventory.addProduct(make_shared<TaxableProduct>  (147,"Control Module",106,9000));
        inventory.addProduct(make_shared<DiscountedProduct>(148,"ECU",197,20000));
        inventory.addProduct(make_shared<TaxableProduct>  (149,"OBD Scanner",230,3200));
        inventory.addProduct(make_shared<DiscountedProduct>(150,"Key Fob",64,1800));

        inventory.addProduct(make_shared<TaxableProduct>  (151,"Immobilizer",108,4200));
        inventory.addProduct(make_shared<DiscountedProduct>(152,"Central Locking Kit",193,3500));
        inventory.addProduct(make_shared<TaxableProduct>  (153,"Alarm System",150,2800));
        inventory.addProduct(make_shared<DiscountedProduct>(154,"Dash Cam",300,2200));
        inventory.addProduct(make_shared<TaxableProduct>  (155,"Parking Brake Cable",98,900));
        inventory.addProduct(make_shared<DiscountedProduct>(156,"Handbrake Lever",276,1300));
        inventory.addProduct(make_shared<TaxableProduct>  (157,"Fuel Cap",87,250));
        inventory.addProduct(make_shared<DiscountedProduct>(158,"Oil Dipstick",190,150));
        inventory.addProduct(make_shared<TaxableProduct>  (159,"Engine Cover",200,2700));
        inventory.addProduct(make_shared<DiscountedProduct>(160,"Skid Plate",311,3500));
}

    //Handles Concurrent Processing Of Multiple Customer Orders Using Threads
    //Each Order Is Processed Simultaneously To Simulate A Real-time Trading System
void handleProccessOrder() {
    vector<thread> threads;
    random_device random;
    mt19937 generator(random());//initialises a random number generator

    uniform_int_distribution<> productRange(1, 160);
    uniform_int_distribution<> quantityRange(1, 100);
    uniform_int_distribution<> itemCountRange(1, 10); // 1-5 products per order

    orders.clear();

    for (int i = 1; i <= 20; i++) {
        vector<OrderItem> items;
        int numItems = itemCountRange(generator);

        for (int j = 0; j < numItems; j++) {
            items.push_back({ productRange(generator), quantityRange(generator) });
        }

        orders.push_back(Order(i, items, "Pending"));
    }

    for (size_t i = 0; i < orders.size(); i++) {
        threads.emplace_back(&Inventory::processOrder, &inventory, ref(orders[i]));
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
}
    //Handles Adding A New Product To The Inventory
    //Prompts The User To Choose Between A Taxable or Discounted Product Type
    void handleAdd() {
        int type;

        while (true) {
            cout << "1. Taxable Product \n2. Discounted Product" << endl;
            cout << "Enter a choice: ";
            validator(type);

            if (type == 1 || type == 2) {
                break;
            }

            cout << "Invalid Choice!!\n";
        }

        cout << "------------------------------------" << endl;

        int productID;
        string productName;
        int productQuantity;
        double productPrice;

        cout << "1. Enter Product ID: ";
        validator(productID);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "2. Enter Product Name: ";
        validator(productName);

        cout << "3. Enter Product Quantity: ";
        validator(productQuantity);

        cout << "4. Enter Product Price: ";
        validator(productPrice);

        bool check = false;

        if (type == 1) {
            check = inventory.addProduct(
                make_shared<TaxableProduct>(
                    productID, productName, productQuantity, productPrice
                )
            );

        if (check) {
            cout << "Taxable Product SUCCESSFULLY Added." << endl;
        } else {
            cout << "Product ID already exists" << endl;
        }
    }
    else {
        check = inventory.addProduct(
            make_shared<DiscountedProduct>(
                productID, productName, productQuantity, productPrice
            )
        );

        if (check) {
            cout << "Discounted Product SUCCESSFULLY Added." << endl;
        } else {
            cout << "Product ID already exists" << endl;
        }
    }
}

    //Handles Displaying All Products Currently Stored In The Inventory
    //Calls displayAllProduct() Which Iterates Through The map And Prints
    //Each Product In A Formatted Table Showing ID, Name, Quantity, Price and Type(Taxable or Discounted)
    void handleDisplay(){
        inventory.displayAllProduct();
    }

    //Handles Removing A Product From The Inventory By Product ID
    void handleRemove(){
        int productID;
        cout<<"Enter product ID of product to be removed:";
        validator(productID); //Ensures Product ID Entered Is A Valid Integer

        //removeProduct() Returns True If The Product Was Found And Removed
        //Returns False If No Product With That ID Exists In The Inventory
        if(inventory.removeProduct(productID)){
            cout<<"The selected product: "<<productID<<" has been removed SUCCESSFULLY."<<endl;
        }else{
            cout<<"The selected product: "<<productID<<" does not exist."<<endl;
        }
    }

    //Handles Searching For A Product In The Inventory By Product ID
    void handleSearch(){
         int productID;
         cout<<"Enter product ID:";
         validator(productID); //Ensures Product ID Entered Is A Valid Integer

         //searchProduct() Uses std::find_if To Search The Map For A Matching Product ID
         // If Found: Displays The Product Name, Quantity and Price
         // If Not Found: Displays "Product not found" Message
         inventory.searchProduct(productID);
    }

    //Handles Sorting And Displaying All Products By Stock Quantity In Ascending Order
    //Pass Onto sortByQuantity() Which Copies The Map Into A Vector
    //And Uses std::sort With A Lambda Comparator To Sort By Quantity
    void handleSortByQuantity(){
        inventory.sortByQuantity();
    }

    //Handles Sorting And Displaying All Products By Price In Ascending Order
    //Pass Onto sortByPrice() Which Copies The Map Into A Vector
    //And Uses std::sort With A Lambda Comparator To Sort By Price
    void handleSortByPrice(){
        inventory.sortByPrice();
    }


int main(){

    loadProduct();//Pre-load Products Into Inventory
    int choice;

    //Keep The Menu Running Until The User Chooses To Exit (Option 8)
    do{
        mainMenu();
        validator(choice);
        //validator() Handles Invalid Input (Non-Numeric) And Re-prompts The USser

        switch(choice){

            case 1:
                handleDisplay(); //Display All Products
                break;

            case 2:
                handleAdd(); //Add A New Taxable or Discounted Product To Inventory
                break;
            case 3:
                handleRemove(); //Remove A Product From Inventory By Product ID
                break;

            case 4:
                handleSearch();  //Search For A Product By Product ID
                break;
            case 5:
                handleProccessOrder(); //Create Concurrent Threads To Process Customer Orders
                break;
            case 6:
                handleSortByQuantity(); //Sort And Display Products By Stock Quantity (Ascending)
                break;
            case 7:
                handleSortByPrice(); //Sort And Display Products By Price (Ascending)
                break;
            case 8:
                break;
            default:
                cout<<"Invalid Choice!\n"<<endl;  //Handles Any Input Outside 1-8


        }
    }while(choice != 8); //Exit Condition  User Selects 8 To Quit The Program

};
