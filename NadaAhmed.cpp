#include <iostream>
using namespace std;

class TreeNode {
public:
    string itemname;
    string category;
    int price;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string name, string cat, int p) {
        itemname = name;
        category = cat;
        price = p;
        left = nullptr;
        right = nullptr;
    }
};
////
class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, string name, string cat, int price) {
        if (node == nullptr) {
            node = new TreeNode(name, cat, price);
        }
        else if (name < node->itemname) {
            node->left = insert(node->left, name, cat, price);
        }
        else {
            node->right = insert(node->right, name, cat, price);
        }
        return node;
    }

    void ascending(TreeNode* node) {
        if (node != nullptr) {
            ascending(node->left);
            cout << "Name: " << node->itemname << ", Category: " << node->category << ", Price: " << node->price << endl;
            ascending(node->right);
        }
    }
    void  descending(TreeNode* node) {
        if (node != nullptr) {
            descending(node->right);
            cout << "Name: " << node->itemname << " Category: " << node->category << " Price: " << node->price << endl;
            descending(node->left);
        }
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* node, string name,string cat,int p) {
        if (node == nullptr) {
            return node;
        }

        if (name < node->itemname) {
            node->left = deleteNode(node->left, name,cat,p);
        }
        else if (name > node->itemname) {
            node->right = deleteNode(node->right, name,cat,p);
        }
        else if(name==node->itemname && cat==node->category && p==node->price) {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->itemname = temp->itemname;
            node->category = temp->category;
            node->price = temp->price;
            node->right = deleteNode(node->right, temp->itemname,temp->category,temp->price);
        }
        return node;
    }
public:
    BST() {
        root = nullptr;
    }
    void insert(string name, string cat, int price) {
        root = insert(root, name, cat, price);
    }

    void sort_ascending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            ascending(root);
        }
    }
    void sort_descending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            descending(root);
        }
    }
    void deleteItem(string name,string category ,int price) {
        root = deleteNode(root,name,category,price);
    }
};

class BST_price {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, string name, string cat, int price) {
        if (node == nullptr) {
            node = new TreeNode(name, cat, price);
        }
        else if (price < node->price) {
            node->left = insert(node->left, name, cat, price);
        }
        else {
            node->right = insert(node->right, name, cat, price);
        }
        return node;
    }

    void ascending(TreeNode* node) {
        if (node != nullptr) {
            ascending(node->left);
            cout << "Name: " << node->itemname << ", Category: " << node->category << ", Price: " << node->price << endl;
            ascending(node->right);
        }
    }
    void  descending(TreeNode* node) {
        if (node != nullptr) {
            descending(node->right);
            cout << "Name: " << node->itemname << ", Category: " << node->category << ", Price: " << node->price << endl;
            descending(node->left);
        }
    }
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* node, string name, string cat, int p) {
        if (node == nullptr) {
            return node;
        }

        if (p < node->price) {
            node->left = deleteNode(node->left, name, cat, p);
        }
        else if (p > node->price) {
            node->right = deleteNode(node->right, name, cat, p);
        }
        else if (name == node->itemname && cat == node->category && p == node->price) {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->itemname = temp->itemname;
            node->category = temp->category;
            node->price = temp->price;
            node->right = deleteNode(node->right,temp->itemname,temp->category ,temp->price);
        }
        return node;
    }
public:
    BST_price() {
        root = nullptr;
    }

    void insert(string name, string cat, int price) {
        root = insert(root, name, cat, price);
    }

    void sort_ascending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            ascending(root);
        }
    }
    void sort_descending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            descending(root);
        }
    }
    void deleteItem(string name,string category,int p) {
        root = deleteNode(root, name,category,p);
    }
};
BST bst;
BST_price bst1;

void insert(string name,string Category,int price) {
    bst.insert(name, Category, price);
    bst1.insert(name, Category, price);
}
void delete_item(string name, string Category, int price) {
    bst.deleteItem(name, Category, price);
    bst1.deleteItem(name, Category, price);
}
int main() {
    while (true) {
        cout << "If you want \n  to insert element input 1 \n to delete item input 2 \n to display items input 3 \n to sort by price 4\n sort by name 5 \n Exist 6\n";
        int x, p;
        string s, cat;
        cin >> x;
        if (x == 1) {
            cin >> s >> cat >> p;
            insert(s, cat, p);
        }
        else if (x == 2) {
            cin >> s >> cat >> p;
            delete_item(s, cat, p);
        }
        else if (x == 4) {
            bst.sort_ascending();
            cout << "*" << '\n';
            bst.sort_descending();
        }
        else if (x == 5) {
            bst1.sort_ascending();
            cout << "\n";
            bst1.sort_descending();
        }
        else if (x == 6)break;
        else continue;
    }
    return 0;
}