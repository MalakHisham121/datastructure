#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Item {
private:
    string itemName;
    string category;
    int price;

public:
    Item(string name, string cat, int pr) : itemName(name), category(cat), price(pr) {}

    string getItemName() const {
        return itemName;
    }

    void print() const {
        cout << itemName << endl;
        cout << category << endl;
        cout << price << endl;
        cout<<endl;
    }

    string toLowerCase(const string& str) const {
        string result;
        for (char c : str) {
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
        if (price == other.price) {
            return toLowerCase(itemName) > toLowerCase(other.toLowerCase(itemName));
        }
        return price > other.price;
    }
};

class AVLTreeByPrice {
private:
    struct Node {
        Item data;
        int height {};
        Node* left {};
        Node* right {};

        Node(Item data) : data(data) {}

        int ch_height(Node* node) {
            if (!node)
                return -1;
            return node->height;
        }

        int update_height() {
            return height = 1 + max(ch_height(left), ch_height(right));
        }

        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };

    Node *root {};

    Node* right_rotation(Node* Q) {
        Node* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update_height();
        P->update_height();
        return P;
    }

    Node* left_rotation(Node* P) {
        Node* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }

    Node* balance(Node* node) {
        if (node->balance_factor() == 2) {
            if (node->left->balance_factor() == -1)
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        } else if (node->balance_factor() == -2) {
            if (node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);
            node = left_rotation(node);
        }
        return node;
    }

    Node* insert_node(Item target, Node* node) {
        if ( node->data >target ) {
            if (!node->left)
                node->left = new Node(target);
            else
                node->left = insert_node(target, node->left);
        } else {
            if (!node->right)
                node->right = new Node(target);
            else
                node->right = insert_node(target, node->right);
        }
        node->update_height();
        return balance(node);
    }

    Node* min_node(Node* cur) {
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }

    Node* delete_node(Item target, Node* node) {
        if (!node)
            return nullptr;

        if (node->data> target ) {
            node->left = delete_node(target, node->left);
        } else if ( target>node->data ) {
            node->right = delete_node(target, node->right);
        } else {
            Node* tmp = node;

            if (!node->left && !node->right)
                node = nullptr;
            else if (!node->right)
                node = node->left;
            else if (!node->left)
                node = node->right;
            else {
                Node* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
                tmp = nullptr;
            }
            if (tmp)
                delete tmp;
        }
        if (node) {
            node->update_height();
            node = balance(node);
        }
        return node;
    }

    void print_inorder_Ascending(Node* node) {
        if (!node)
            return;
        print_inorder_Ascending(node->left);
        node->data.print();
        print_inorder_Ascending(node->right);
    }

    void print_inorder_descending(Node* node) {
        if (!node)
            return;
        print_inorder_descending(node->right);
        node->data.print();
        print_inorder_descending(node->left);
    }

public:
    void insert_value(Item target) {
        if (!root)
            root = new Node(target);
        else
            root = insert_node(target, root);
    }

    void delete_value(Item target) {
        if (root) {
            root = delete_node(target, root);
        }
    }

    void print_inorder_descending() {
        print_inorder_descending(root);
    }

    void print_inorder_Ascending() {
        print_inorder_Ascending(root);
    }
};

class Node {
public:
    Item item;
    Node* left;
    Node* right;

    Node(Item i) : item(i), left(nullptr), right(nullptr) {}
};

class AVLbyName {
private:
    vector<Item> items;
    Node* root_node;

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        int maxHeight = max(getHeight(node->left), getHeight(node->right));
        return 1 + maxHeight;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        int h = getHeight(node->left) - getHeight(node->right);
        return h;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* z = x->right;
        x->right = y;
        y->left = z;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* z = y->left;
        y->left = x;
        x->right = z;
        return y;
    }

    Node* AddItem(Node* node, const Item& data) {
        if (node == nullptr)
            return new Node(data);

        if (data < node->item)
            node->left = AddItem(node->left, data);
        else if (node->item < data)
            node->right = AddItem(node->right, data);
        else
            return node;

        int balance_factor = getBalance(node);

        if (balance_factor > 1 && data < node->left->item)
            return rotateRight(node);
        if (balance_factor < -1 && node->right->item < data)
            return rotateLeft(node);
        if (balance_factor > 1 && node->left->item < data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance_factor < -1 && data < node->right->item) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, const Item& data) {
        if (root == nullptr)
            return root;

        if (data < root->item) {
            root->left = deleteNode(root->left, data);
        } else if (root->item < data) {
            root->right = deleteNode(root->right, data);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                Node* temp = minValNode(root->right);
                root->item = temp->item;
                root->right = deleteNode(root->right, temp->item);
            }
        }

        if (root == nullptr)
            return root;

        int balance_factor = getBalance(root);

        if (balance_factor > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);
        if (balance_factor > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance_factor < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);
        if (balance_factor < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void display_normally() {
        for (const auto& item : items) {
            item.print();
        }
    }

    void Ascending_sort(Node* root) {
        if (root != nullptr) {
            Ascending_sort(root->left);
            items.push_back(root->item);
            root->item.print();
            Ascending_sort(root->right);
        }
    }

    void descending_sort(Node* root) {
        if (root != nullptr) {
            descending_sort(root->right);
            items.push_back(root->item);
            root->item.print();
            descending_sort(root->left);
        }
    }

public:
    AVLbyName() {
        root_node = nullptr;
    }

    void insert(const Item& data) {
        root_node = AddItem(root_node, data);
        items.push_back(data);
    }

    void remove(const Item& data) {
        root_node = deleteNode(root_node, data);
        auto it = remove_if(items.begin(), items.end(), [&](const Item& item) {
            return item.getItemName() == data.getItemName();
        });
        items.erase(it, items.end());
    }

    void displayNormally() {
        display_normally();
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

class AVLTree {
    AVLbyName name;
    AVLTreeByPrice price;

public:
    void add(Item t) {
        name.insert(t);
        price.insert_value(t);
    }

    void del(Item t) {
        name.remove(t);
        price.delete_value(t);
    }

    void display_normally() {
        name.displayNormally();
    }

    void display_Ascending_by_name() {
        name.displayAscending();
    }

    void display_Ascending_by_price() {
        price.print_inorder_Ascending();
    }

    void display_Descending_by_name() {
        name.displayDescending();
    }

    void display_Descending_by_price() {
        price.print_inorder_descending();
    }
};

int main() {
    cout << "Choose an operation to do on AVL Tree (enter from 1 to 8):" << endl;
    cout << "1. Add item" << endl;
    cout << "2. Remove item" << endl;
    cout << "3. Display items normally" << endl;
    cout << "4. Display all items sorted by name ascending" << endl;
    cout << "5. Display all items sorted by name descending" << endl;
    cout << "6. Display all items sorted by price ascending" << endl;
    cout << "7. Display all items sorted by price descending" << endl;
    cout << "8. Exit" << endl;

    AVLTree AvlTree;
    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name, category;
                int price;
                cout << "Enter Item Name: ";
                cin >> name;
                cout << "Enter Category: ";
                cin >> category;
                cout << "Enter Price: ";
                cin >> price;
                Item newItem(name, category, price);
                AvlTree.add(newItem);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Item Name to remove: ";
                cin >> name;
                Item remove_item(name, "", 0);
                AvlTree.del(remove_item);
                break;
            }
            case 3: {
                cout << "Displaying items:" << endl;
                AvlTree.display_normally();
                break;
            }
            case 4: {
                cout << "Displaying items sorted by name ascending:" << endl;
                AvlTree.display_Ascending_by_name();
                break;
            }
            case 5: {
                cout << "Displaying items sorted by name descending:" << endl;
                AvlTree.display_Descending_by_name();
                break;
            }
            case 6: {
                cout << "Displaying items sorted by price ascending:" << endl;
                AvlTree.display_Ascending_by_price();
                break;
            }
            case 7: {
                cout << "Displaying items sorted by price descending:" << endl;
                AvlTree.display_Descending_by_price();
                break;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
