//Developed By Taha Farooqui
//FAST-NU karachi

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

class User 
{
private:
    string name;
    string email;
    string password;
public:
    User() {}
    User(string name, string email, string password)
    {
        this->name = name;
        this->email = email;
        this->password = password;
    }
    void registerUser()
{
    string name, email, password;

    cout << "\n\n\t\t\tWelcome! \n\t\t\t\tPlease enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "\n\t\t\t\tPlease enter your email address: ";
    getline(cin, email);
    cout << "\n\t\t\t\tPlease choose a password: ";
    getline(cin, password);
    system("cls");
    cout << "\n\n\t\t\t\tThank you for registering, " << name << "!" << std::endl;

    // Save user data to file
    ofstream outFile;
    outFile.open("users.txt", ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << name << "," << email << "," << password << endl;
        outFile.close();
    }
    else
    {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

    void displayUserInfo()
    {
        cout << "\n\t\t\tName: " << name << endl;
        cout <<"\t\t\tEmail: "<<email<<endl;
        
    }
    string getEmail() {
        return email;
    }
    string getPassword() {
        return password;
    }
};
//Developed By Taha Farooqui
//FAST-NU karachi
class Product
{
private:
    string name;
    string description;
    float price;
    vector<Product>* products; // pointer to vector
public:
    Product(string name, string description, float price, vector<Product>* products)
        : name(name), description(description), price(price), products(products) // initializer list
    {
    }

    void addProduct()
{
    string name, description;
    float price;
    system("cls");
    cout << "\n\n\t\t\t\tEnter product name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\n\t\t\t\tEnter product description: ";
    getline(cin, description);

    cout << "\n\t\t\t\tEnter product price: ";
    cin >> price;

    Product newProduct(name, description, price, products); // pass the address of the vector
    products->push_back(newProduct); // use the arrow operator to access vector methods

    // write the product data to file
    ofstream outfile("products.txt", ios::app);
    if (outfile.is_open())
    {
        outfile << name << ',' << description << ',' << price << endl;
        outfile.close();
        cout << "\n\t\t\t\tProduct added successfully!" << endl;
    }
    else
    {
        cout << "\n\t\t\t\tError opening file" << endl;
    }
}
//Developed By Taha Farooqui
//FAST-NU karachi
    void removeProduct()
{
    string name;
    bool found = false;

    cout << "Enter the name of the product to remove: ";
    cin.ignore();
    getline(cin, name);

    // open the input and output files
    ifstream infile("products.txt");
    ofstream outfile("temp.txt");

    if (infile.is_open() && outfile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            stringstream ss(line);
            string currentName, description;
            float price;
            getline(ss, currentName, ',');
            getline(ss, description, ',');
            ss >> price;

            // if the current product name matches the name entered by the user, skip writing it to the temp file
            if (currentName == name) {
                found = true;
            }
            else {
                outfile << currentName << "," << description << "," << price << endl;
            }
        }

        // close the input and output files
        infile.close();
        outfile.close();

        if (found) {
            // rename the temp file to overwrite the original file
            remove("products.txt");
            rename("temp.txt", "products.txt");
            cout << "Product removed successfully!" << endl;
        }
        else {
            cout << "Product not found!" << endl;
            // delete the temp file
            remove("temp.txt");
        }
    }
    else {
        cout << "Error opening file" << endl;
    }
}
    void updateInfo() {
        int index;
        system("cls");
        cout << "\n\t\t\tEnter the index of the product to update: ";
        cin.ignore();
        cin >> index;
        if (index >= 0 && index < products->size()) {
            // Prompt user for updated information
            string name, description;
            float price;

            cout << "\n\n\t\t\t\tEnter updated product name: ";
            cin.ignore();
            getline(cin >> ws, name);

            cout << "\n\t\t\t\tEnter updated product description: ";
            getline(cin, description);

            cout << "\n\t\t\t\tEnter updated product price: ";
            cin >> price;

            // Update product information
            (*products)[index].name = name;
            (*products)[index].description = description;
            (*products)[index].price = price;

            cout << "\n\t\t\t\t\tProduct information updated successfully!" << endl;
            system("cls");
        }
        else {
            cout << "Invalid index!" << endl;
        }
    }

void displayAllProducts() 
{
    system("cls");
    cout << "List of all products:" << endl;
    cout << setw(20) << "Item No's" << setw(20) << "Product Name" << setw(20) << "Description" << setw(20) << "Price" << setw(20) << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    // read product data from file
    ifstream infile("products.txt");
    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            stringstream ss(line);
            string name, description;
            float price;
            getline(ss, name, ',');
            getline(ss, description, ',');
            ss >> price;

            // display the product data
            cout << setw(18) << products->size() << setw(18) << name << setw(18) << description << setw(18) << price << endl;
            products->emplace_back(name, description, price, products);
        }
        infile.close();
    }
    else
    {
        cout << "\n\t\t\t\tError opening file" << endl;
    }
}

    string getName()
    {
        return name;
    }
    int getPrice()
    {
        return price;
    }
};


class Cart{
private:
    vector<Product> cartItems;
    vector<int> quantities;
    float totalCost;

public:
    void addProductToCart(vector<Product>& products)
    {
        string productName;
        int productQuantity;
        system("cls");
        cout << "\n\n\t\t\t\tEnter the name of the product you want to add to your cart: ";
        cin.ignore();
        cin >> productName;

        bool foundProduct = false;
        for (int i = 0; i < products.size(); i++) {
            if (products[i].getName() == productName) {
                foundProduct = true;

                cout << "\t\t\t\tEnter the quantity of the product you want to add to your cart: ";
                cin >> productQuantity;

                cartItems.push_back(products[i]);
                quantities.push_back(productQuantity);
                totalCost += products[i].getPrice() * productQuantity;

                cout << "\n\t\t\t\t\t"<<productName << " has been added to your cart." << endl;
                break;
            }
        }

        if (!foundProduct) {
            cout << "Sorry, " << productName << " is not available." << endl;
        }
    }

    void removeProductfromCart(vector<Product>& products)
    {
        string productName;
        system("cls");
        cout << "\n\n\t\t\t\tEnter the name of the product you want to remove from your cart: ";
        cin.ignore();
        cin >> productName;

        // Check if the product is in the cart
        for (int i = 0; i < cartItems.size(); i++) {
            if (cartItems[i].getName() == productName) {
                // Remove the product and its quantity from the cart
                totalCost -= cartItems[i].getPrice() * quantities[i];
                cartItems.erase(cartItems.begin() + i);
                quantities.erase(quantities.begin() + i);

                cout << productName << " has been removed from your cart." << endl;
                return;
            }
        }

        // If the product is not in the cart, display an error message
        cout << "Sorry, " << productName << " is not in your cart!" << endl;
    }

    void displayCartItems()
    {
        if (cartItems.size() == 0) {
            cout << "Cart is empty!" << endl;
            return;
        }

        cout << "\n\n\t\t\t\tCart items: " << endl;
          cout << setw(20) << "Item No's" << setw(20) << "Name" << setw(20) << setw(20) << "Quantity" << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < cartItems.size(); i++) {
            cout <<setw(20) <<i + 1 <<setw(20)<< cartItems[i].getName() << setw(20) <<  quantities[i]<<setw(20) << endl;
        }
        cout << "\n\n\t\t\t\tTotal cost: " << totalCost << endl;
    }

    float calculateTotalCost()
    {
        return totalCost;
    }

    void checkout(float discount, float taxRate)
    {
        system("cls");
        // Check if the cart is empty
        if (cartItems.size() == 0) {
            cout << "\n\n\n\t\t\tYour cart is empty. Please add items to your cart before checking out." << endl;
            return;
        }

		 int orderID = rand() % 10000 + 1;

        // Display the cart items and total cost
        cout << "\n\n\t\t\t\t\t\tYour Cart" << endl;
        cout << "\t\t\t\t\t\t**********\n";
        displayCartItems();

        // Calculate subtotal
        float subtotal = calculateTotalCost();

        // Calculate discount
        float discountAmount = subtotal * discount;
        float discountedSubtotal = subtotal - discountAmount;

        // Calculate tax
        float taxAmount = discountedSubtotal * taxRate;

        // Calculate total bill
        float totalBill = discountedSubtotal + taxAmount;

        // Display total bill including discounted price and tax
       cout << "\n\n\t\t\t\t\t\tSubtotal: $" << subtotal << endl;
    cout << "\t\t\t\t\t\tDiscount: $" << discountAmount << endl;
    cout << "\t\t\t\t\tDiscounted subtotal: $" << discountedSubtotal << endl;
    cout << "\t\t\t\t\t\tTax (" << (taxRate * 100) << "%): $" << taxAmount << endl;
    cout << "\n\t\t\t\t\t***************************************";
    cout << "\n\t\t\t\t\t\tTotal bill: $" << totalBill << endl;
    cout << "\t\t\t\t\t***************************************";


        // Ask the user if they want to proceed with checkout
        char choice;
         cout << "\n\n\t\t\t\t\tDo you want to proceed with checkout? (Y/N): ";
        cin >> choice;

        if (toupper(choice) == 'Y') {
            // Perform checkout
            // Deduct the cost of items from the user's account or process payment
            // Update the inventory of the products in the cart
            for (int i = 0; i < cartItems.size(); i++) {
                int quantity = quantities[i];
            }

            // Clear the cart
            cartItems.clear();
            quantities.clear();
            totalCost = 0;
         cout<<"\n\n\n\n\n\t\t\t\t\t\t********************************************";
        cout << "\n\n\t\t\t\t\tCheckout complete. Thank you for shopping with us!" << endl;
        cout<<"\n\t\t\t\t\t\t********************************************\n\n\n\n\n\n\n\n\n\n\n";
        
         ofstream billFile;
        billFile.open("bill.txt", ios::app);
        billFile << "-------------------------" << endl;
        billFile << "Checkout details" << endl;
        billFile << "-------------------------" << endl;
        billFile<< "Order ID: " << orderID << endl;
        billFile << "Subtotal: $" << subtotal << endl;
        billFile << "Discount: $" << discountAmount << endl;
        billFile << "Discounted subtotal: $" << discountedSubtotal << endl;
        billFile << "Tax (" << (taxRate * 100) << "%): $" << taxAmount << endl;
        billFile << "Total bill: $" << totalBill << endl;
        billFile << "-------------------------" << endl;
        billFile.close();

        cout << "\n\n\n\n\n\t\t\t\t\t\t********************************************";
        cout << "\n\n\t\t\t\t\tCheckout complete. Thank you for shopping with us!" << endl;
        cout << "\n\t\t\t\t\t\t********************************************\n\n\n\n\n\n\n\n\n\n\n";
        
        }
        else {
            // Cancel checkout
            cout << "Checkout cancelled." << endl;
        }
    }
    
    void displayOrder() {
    ifstream billFile("bill.txt");
    if (!billFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(billFile, line)) {
        if (line.find("Order ID: ") != string::npos) {
            cout << line << endl;
        }
        else if (line.find("Total bill: $") != string::npos) {
            cout << line << endl;
            cout << "-------------------------" << endl;
        }
    }

    billFile.close();
}
};

class UserManager 
{
private:
    vector<User> users;
    Cart cart;
public:
    void registerUser() 
    {
        User newUser;
        newUser.registerUser();
        users.push_back(newUser);
    }
    void displayAllUsers() {
        for (int i = 0; i < users.size(); i++) {
            users[i].displayUserInfo();
        }
    }
    User* getUserByEmail(string email) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getEmail() == email) {
                return &users[i];
            }
        }
        return nullptr;
    }
    bool loginUser()
{
    string email, password;
    cout << "\n\n\t\t\t\tPlease enter your email address: ";
    cin.ignore();
    getline(cin, email);
    cout << "\n\t\t\t\tPlease enter your password: ";
    getline(cin, password);

    ifstream inFile;
    inFile.open("users.txt");
    if (!inFile.is_open())
    {
        cout << "Error: Unable to open file for reading." << endl;
        return false;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string name, fileEmail, filePassword;
        getline(ss, name, ',');
        getline(ss, fileEmail, ',');
        getline(ss, filePassword);

        if (fileEmail == email && filePassword == password)
        {
            system("cls");
            cout << "\n\t\t\tLogin successful! Welcome, " << name << "!" << endl;
            inFile.close();
            return true;
        }
    }

    cout << "\n\t\t\tInvalid email or password. Please try again." << endl;
    inFile.close();
    return false;
}

        
        bool loginAdmin() {
        string email, password;
        cout << "\n\n\t\t\t\tPlease enter your username: ";
        cin.ignore();
        getline(cin, email);
        cout << "\n\t\t\t\tPlease enter your password: ";
        getline(cin, password);

        if (email == "admin" && password == "admin") 
{
            system("cls");
            cout << "\n\t\t\tLogin successful! Welcome, "<<email<<" !"<<endl;
            return true;
        }
        else {
            //cout << "\n\t\t\tInvalid email or password. Please try again." << endl;
            return false;
        }
    }
    
    
        void addProductToCart(vector<Product>& product)
    {
        cart.addProductToCart(product);
    }

    void showOrders(){
    	cart.displayOrder();
	}
    
       void removeProductFromCart(vector<Product>& product)
    {
        cart.removeProductfromCart(product);
    }

    
        float calculateCartTotalCost() {
        return cart.calculateTotalCost();
    }

       void showcart(Product product)
    {
        cart.displayCartItems();
    }

    
    
       void checkoutCart() {
        cart.checkout(0.2,0.15);
    }

};
class Order 
{
private:
    vector<Product> products;
    vector<int> quantities;
    float totalCost;
    time_t orderTime;
public:
    void createOrder() {
        // code for creating a new order
    }

    vector<Order> getOrderHistory() {
        // code for retrieving order history
    }

    void cancelOrder() {
        // code for canceling an order
    }
};

class Address {
private:
    string streetAddress;
    string city;
    string state;
    string postalCode;
    string country;
public:
    bool validateAddress() {
        // code for validating the address
        return true;
    }

    string formatForDisplay() {
        // code for formatting the address for display
        return "";
    }
};
class Admin
{
private:
    string name;
    string email;
    string password;
    bool canAddProducts;
    bool canRemoveProducts;
    bool canManageOrders;
public:
    Admin(string name, string email, string password,
        bool canAddProducts, bool canRemoveProducts, bool canManageOrders)
        : name(name), email(email), password(password),
        canAddProducts(canAddProducts), canRemoveProducts(canRemoveProducts),
        canManageOrders(canManageOrders) {}

    void addProduct(Product product) {
        if (canAddProducts) {
            product.addProduct();
            system("cls");
            cout << "\n\t\tProduct added successfully!" << endl;
        }
        else {
            cout << "You do not have permission to add products!" << endl;
        }
    }

        void removeProduct(Product products) {
        if (canRemoveProducts) 
	  {
	  	products.removeProduct();
        }
        else {
            cout << "You do not have permission to remove products!" << endl;
        }
    }
    void manageOrders(vector<Order>& orders) {
        if (canManageOrders) {
            // code for managing orders
            // e.g., print list of orders, mark orders as shipped, etc.
        }
        else {
            cout << "You do not have permission to manage orders!" << endl;
        }
    }

    void updateUserInfo(User user) 
    {
        // code for updating user information
        // e.g., change user's name, email, password, etc.
    }
    void displayAllProducts(Product product) 
    {
        product.displayAllProducts();
    }
};
int main()
{
    UserManager manager;
    Admin admin("John Doe", "john@example.com", "password", true, true, true);
    int choice = 0;
    bool loggedIn = false;
    bool UserLogin = false;
    bool AdminLogin = false;
    vector<Product> products;
    vector<Cart> carts;
    
    
    cout<<"\n\n\t\t\tWELCOME TO FAST E-COMMERCE STORE MANAGMENT SYSTEM";
    
while (true) {
   if (!AdminLogin && !UserLogin) {
        main:
        cout << "\nPlease choose an option:" << endl;
        cout << "1. Register as User" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        
        switch(choice){
            
            case 1:
                system("cls");
                manager.registerUser();
                break;
            case 2:
                system("cls");
                cout << "\n\n\t\t\t\tPlease choose an option:" << endl;
                cout << "\t\t\t\t1. Login as User" << endl;
                cout << "\t\t\t\t2. Login as Admin" << endl;
                cin>> choice;
                
                    if(choice == 1){
                        system("cls");
                        if (UserLogin) {
                            cout << "You are already logged in." << endl;
                            break;
                        }
                        else 
                        {
                            UserLogin = manager.loginUser();
                            if (UserLogin) {
                                goto userpanel;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                    }else if(choice == 2){
                        system("cls");
                        if (AdminLogin) {
                            cout << "You are already logged in." << endl;
                            break;
                        }
                        else 
                        {
                            AdminLogin = manager.loginAdmin();
                            if (AdminLogin) {
                                goto adminpanel;
                            }
                            else {
                                break;
                            }
                        }
                    }else{
                        system("cls");
                        cout << "\n\n\t\t\t\tExiting program." << endl;
                        return 0;
                    }
                break;
            case 3:
                system("cls");
                cout << "\n\n\t\t\t\tExiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    
            if(AdminLogin){
                adminpanel:
                cout << "Please choose an option:" << endl;
                cout << "1. Display all users" << endl;
                cout << "2. Add product" << endl;
                cout << "3. Display all products" << endl;
                cout << "4. Remove product" << endl;
                cout << "5. Show Orders"<<endl;
                cout << "6. Logout" << endl;
                cin >> choice;
                
                switch(choice){
                    
                    case 1:
                        system("cls");
                        cout<<"\n\n\t\t\t\tLIST OF ALL REGISTERED USERS\n";
                        manager.displayAllUsers();
                        goto adminpanel;
                        break;
                    case 2:
                        system("cls");
                        admin.addProduct(Product("", "", 0, &products));
                        goto adminpanel;
                        break;
                    case 3:
                        system("cls");
                        admin.displayAllProducts(Product("", "", 0, &products));
                        goto adminpanel;
                        break;
                    case 4:
                        system("cls");
                        admin.removeProduct(Product("", "", 0, &products));
                        goto adminpanel;
                        break;
                    case 5:
                    	system("cls");
                    	system("cls");
                        manager.showOrders();
                        break;
                    case 6:
                        system("cls");
                        AdminLogin = false;
                        goto main;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;

                }
                
            }
            if(UserLogin){
                userpanel: 
               cout << "Please choose an option:" << endl;
                cout << "1. Display all products" << endl;
                cout << "2. Add product to cart" << endl;
                cout << "3. Remove product from cart" << endl;
                cout << "4. Show cart" << endl;
                cout << "5. checkout" << endl;
                cout << "6. Logout" << endl;
                cin >> choice;
                
                switch(choice){
                    
                    case 1:
                        system("cls");
                        admin.displayAllProducts(Product("", "", 0, &products));
                        goto userpanel;
                        break;
                    case 2:
                        system("cls");
                        manager.addProductToCart(products);
                        manager.calculateCartTotalCost();
                        goto userpanel;
                        break;
                    case 3:
                        system("cls");
                        manager.removeProductFromCart(products);
                        goto userpanel;
                        break;
                    case 4:
                        system("cls");
                        manager.showcart(Product("", "", 0, &products));
                        goto userpanel;
                        break;
                    case 5:
                        system("cls");
                        manager.checkoutCart();
                        goto userpanel;
                        break;
                    case 6:
                        system("cls");
                        goto main;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    
                }
            } //user close
            
   }//main if close
   
}//main while close

        return 0;
}

