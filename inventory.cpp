#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm> 
using namespace std;
class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;
public:
    Product(int id, string name, string category, double price, int quantity) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }
    int getId() const {
        return id;
    }
    void setId(int id) {
        this->id = id;
    }
    string getName() const {
        return name;
    }
    void setName(string name) {
        this->name = name;
    }
    string getCategory() const {
        return category;
    }
    void setCategory(string category) {
        this->category = category;
    }
    double getPrice() const {
        return price;
    }
    void setPrice(double price) {
        this->price = price;
    }
    int getQuantity() const {
        return quantity;
    }
    void setQuantity(int quantity) {
        this->quantity = quantity;
    }
};

class Inventory {
private:
    vector<Product> products;
    string filename;

public:
    Inventory(const string& filename) : filename(filename) {}

void addProduct(Product product) {
        bool found = false;
        for (auto& p : products) {
            if (p.getId() == product.getId()) {
                cout << "Id already exists." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            products.push_back(product);
            cout << "Product added successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

void removeProduct(int id) {
    bool found = false;
    std::ifstream inputFile("inventory.csv");
    std::ofstream tempFile("temp.csv");

    if (inputFile.is_open() && tempFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string idStr, name, category, priceStr, quantityStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, category, ',');
            std::getline(ss, priceStr, ',');
            std::getline(ss, quantityStr, ',');

            int productId = std::stoi(idStr);
            if (productId != id) {
                tempFile << line << '\n';
            } else {
                found = true;
            }
        }

        inputFile.close();
        tempFile.close();

        if (found) {
            if (std::remove("inventory.csv") == 0 && std::rename("temp.csv", "inventory.csv") == 0) {
                std::cout << "Product removed successfully." << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;

                // Remove the product from the products vector
                products.erase(std::remove_if(products.begin(), products.end(),
                                              [id](const Product& p) { return p.getId() == id; }),
                               products.end());
            } else {
                std::cout << "Error: Failed to update the CSV file." << std::endl;
            }
        } else {
            std::cout << "ID does not exist." << std::endl;
        }
    } else {
        std::cout << "Error: Failed to open the CSV file." << std::endl;
    }
}
void printProduct() const {
        for (const auto& p : products) {
            cout << "ID: " << p.getId() << endl;
            cout << "Name: " << p.getName() << endl;
            cout << "Category: " << p.getCategory() << endl;
            cout << "Price: $" << p.getPrice() << endl;
            cout << "Quantity: " << p.getQuantity() << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }
   Product* findProduct(int id) {
          for (auto& product : products) {
            if (product.getId() == id) {
                return &product;
            }
        }
        return nullptr;
    }
    void saveInventoryToFile(string filename) 
        {
            ofstream file;
            file.open(filename, ios::out | ios::app);
            for (int i = 0; i < products.size(); i++) 
            {
                Product p = products[i];
                file << p.getId() << " " << p.getName() << " " << p.getCategory() << " " << p.getPrice() << " " << p.getQuantity() << endl;
            }
            file.close();
        }
void loadInventoryFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            std::stringstream ss(line);
            std::string idStr, name, category, priceStr, quantityStr;
            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, category, ',') &&
                std::getline(ss, priceStr, ',') &&
                std::getline(ss, quantityStr, ',')) {
                try {
                    int id = std::stoi(idStr);
                    double price = std::stod(priceStr);
                    int quantity = std::stoi(quantityStr);
                    Product p(id, name, category, price, quantity);
                    products.push_back(p);
                    
                    // Display the details of each item
                    cout << "ID: " << p.getId() << endl;
                    cout << "Name: " << p.getName() << endl;
                    cout << "Category: " << p.getCategory() << endl;
                    cout << "Price: $" << p.getPrice() << endl;
                    cout << "Quantity: " << p.getQuantity() << endl;
                    cout << "-----------------------------------------------------------" << endl;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: Invalid argument encountered while parsing line " << lineNumber << ": " << line << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: Out of range value encountered while parsing line " << lineNumber << ": " << line << std::endl;
                }
            } else {
                std::cout << "item " << lineNumber << ": " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "Error: Could not open file " << filename << std::endl;
    }
}

};

int main() {
    Inventory inventory("inventory.csv");
    char choice;
    do {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout<<  "3. Find a the product" <<endl;
        cout << "4. View all products" << endl;
        cout << "5. Save inventory to file" << endl;
        cout << "6. Load Inventory from file" << endl;
        cout << "7. Quit" << endl;
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }
        case '2': {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }
         case '3': {
                   int id;
            cout << "Enter product ID: ";
            cin >> id;
            Product* product = inventory.findProduct(id);
            if (product) {
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: $" << product->getPrice() << endl;
                cout << "Quantity: " << product->getQuantity() << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else {
                cout << "Product not found." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }
        case '4': {
            inventory.printProduct();
            break;
        }
 case '5': {
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '6': {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    inventory.loadInventoryFromFile(filename);
    cout << "Inventory loaded from file." << endl;
    cout << "-----------------------------------------------------------" << endl;
    break;
}
   case '7': {
            cout << "Exiting the program." << endl;
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
    } while (true);

    return 0;
}
