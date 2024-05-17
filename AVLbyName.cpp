#include<iostream>
#include <algorithm>
#include<vector>
using namespace std;

class Item {
private:
    string itemName;
    string category;
    int price;


public:
    Item(string name,string cat,int pr) {
        itemName=name;
        category=cat;
        price=pr;
    }

    string getItemName() const {
        return itemName;
    }

    void print() const {
        cout<<itemName<<endl;
        cout<<category<<endl;
        cout<<price<<endl;
    }
    string toLowerCase(const string& str) const {
        string result;
        for (char c: str) {
            result += tolower(c);
        }
        return result;
    }

    bool operator<(const Item& other) const {
        string name= toLowerCase(itemName);
        string otherName = toLowerCase(other.itemName);
        return name< otherName;
    }
    bool operator>(const Item& other) const {
        string name= toLowerCase(itemName);
        string otherName= toLowerCase(other.itemName);
        return name >otherName;
    }
};

class Node {
public:
    Item item;
    Node* left;
    Node* right;

    Node(Item i):item(i), left(nullptr), right(nullptr){}
};
class AVLbyName {
private:
    vector<Item> items; // Vector to store items
    Node* root_node;

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        int maxHeight= max(getHeight(node->left),getHeight(node->right));
        return 1+maxHeight;
    }

    int getBalance(Node* node) {
        if (node== nullptr)
            return 0;
        int h=getHeight(node->left)- getHeight(node->right);
        return h;
    }

    Node* rotateRight(Node* y) {
        Node* x= y->left;
        Node* z= x->right;
        x->right= y;
        y->left= z;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y= x->right;
        Node* z= y->left;
        y->left= x;
        x->right= z;
        return y;
    }

    Node* AddItem(Node* node, const Item& data) {
        if (node== nullptr)
            return new Node(data);

        if (data < node->item)
            node->left= AddItem(node->left, data);
        else if (data> node->item)
            node->right= AddItem(node->right, data);
        else
            return node;

        int balance_factor= getBalance(node);

        if (balance_factor> 1 && data< node->left->item)
            return rotateRight(node);
        if (balance_factor< -1 && data> node->right->item)
            return rotateLeft(node);
        if (balance_factor> 1 && data> node->left->item) {
            node->left= rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance_factor< -1 && data< node->right->item) {
            node->right= rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValNode(Node* node) {
        Node* current= node;
        while (current->left !=nullptr)
            current= current->left;
        return current;
    }
    Node* deleteNode(Node* root, const Item& data) {
        if (root== nullptr)
            return root;

        if (data< root->item) {
            root->left= deleteNode(root->left,data);
        }
        else if (data> root->item) {
            root->right= deleteNode(root->right,data);
        }
        else {
            if (root->left== nullptr || root->right== nullptr){
                Node* temp= root->left? root->left: root->right;

                if (temp== nullptr){
                    temp= root;
                    root= nullptr;
                }
                else
                    *root= *temp;

                delete temp;
            }
            else{
                Node* temp= minValNode(root->right);
                root->item= temp->item;
                root->right= deleteNode(root->right,temp->item);
            }
        }

        if (root== nullptr)
            return root;

        int balance_factor= getBalance(root);

        if (balance_factor> 1 && getBalance(root->left)>= 0)
            return rotateRight(root);
        if (balance_factor> 1 && getBalance(root->left)< 0) {
            root->left= rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance_factor< -1 && getBalance(root->right)<= 0)
            return rotateLeft(root);
        if (balance_factor< -1 && getBalance(root->right)>0) {
            root->right= rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void display_normally(){
        for (const auto& item:items) {
            item.print();
        }
    }

    void Ascending_sort(Node* root) {
        if (root != nullptr) {
            Ascending_sort(root->left);
            items.push_back(root->item); //add item in the vector
            root->item.print();
            Ascending_sort(root->right);
        }
    }

    void descending_sort(Node* root) {
        if (root != nullptr) {
            descending_sort(root->right);
            items.push_back(root->item); //add item in the vector
            root->item.print();
            descending_sort(root->left);
        }
    }

public:
    AVLbyName(){
        root_node= nullptr;
    }

    void insert(const Item& data) {
        root_node = AddItem(root_node,data);
        items.push_back(data); //add item in the vector
        //cout<<"item "<<data.getItemName()<<" is at index "<< items.size()-1<<endl;
    }

    void remove(const Item& data) {
        root_node = deleteNode(root_node,data);
        // Remove item from the vector
        auto it = remove_if(items.begin(), items.end(), [&](const Item& item) {
            return item.getItemName()== data.getItemName();
        });
        items.erase(it, items.end());
    }
    void displayNormally(){
        display_normally();
        //display_normally(root_node);
//        for (const auto& item : items) {
//            item.print();
//        }
    }
    void displayAscending() {
        Ascending_sort(root_node);
    }

    void displayDescending() {
        descending_sort(root_node);
    }

    vector<Item> getItems() const {
        return items;
    }


};



int main() {
    cout<<"Choose an operation to do on AVL Tree (enter from 1 to 6):"<< endl;
    cout<<"1. Add item "<< endl;
    cout<<"2. Remove item"<< endl;
    cout<<"3. Display items normally" << endl;
    cout<<"4. Display all items sorted by name ascending" << endl;
    cout<<"5. Display all items sorted by name descending" << endl;
    cout<<"6. Exit"<<endl;

    AVLbyName byNameAvlTree;
    int choice;
    do {
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice){
            case 1: {
                string name, category;
                int price;
                cout<<"Enter Item Name: ";
                cin>>name;
                cout<<"Enter Category: ";
                cin>>category;
                cout<<"Enter Price: ";
                cin>>price;
                Item newItem(name, category, price);
                byNameAvlTree.insert(newItem);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Item Name to remove: ";
                cin >> name;
                Item remove_item(name, "", 0);
                byNameAvlTree.remove(remove_item);
                break;
            }
            case 3: {
                cout << "Displaying items:"<<endl;
                byNameAvlTree.displayNormally();
                break;
            }
            case 4: {
                cout << "Displaying items sorted by name ascending:" << endl;
                byNameAvlTree.displayAscending();
                break;
            }
            case 5: {
                cout<<"Displaying all items sorted by name descending:" << endl;
                byNameAvlTree.displayDescending();
                break;
            }
            case 6: {
                cout<<"Exit"<< endl;
                break;
            }
            default:
                cout << "Invalid choice. try again." << endl;
        }
    } while (choice != 6);



    return 0;
}