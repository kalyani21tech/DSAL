#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

class node {
public:
    char keyword[20];
    char meaning[20];
    node *left;
    node *right;
    int ht;

    node() {
        strcpy(meaning, "");
        strcpy(keyword, "");
        left = right = NULL;
        ht = 0;
    }
};

class tree {
private:
    node *root;

public:
    tree() {
        root = NULL;
    }

    void insert1(char key[20], char mean[20]) {
        root = insert(root, key, mean);
    }

    node* insert(node* T, char word[20], char mean[20]);
    void preorder(node*);
    void inorder(node*);
    void postorder(node*);
    void display();
    void modify(node*);
    void delet();
    node* In_Succ(node*);
    void ascending();
    void descending(node*);
    void search1(node*);
    void search();
    void max_compare(node*);
    node* Rotate_Left(node*);
    node* Rotate_Right(node*);
    int BF(node*);
    int height(node*);
};

int tree::BF(node* T) {
    int lh, rh;
    if (T == NULL)
        return 0;
    lh = (T->left == NULL) ? 0 : 1 + T->left->ht;
    rh = (T->right == NULL) ? 0 : 1 + T->right->ht;
    return (lh - rh);
}

node* tree::Rotate_Right(node* x) {
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

node* tree::Rotate_Left(node* T) {
    node* temp = T->right;
    T->right = temp->left;
    temp->left = T;
    T->ht = height(T);
    temp->ht = height(temp);
    return temp;
}

int tree::height(node* T) {
    if (T == NULL) return 0;
    int left_height = (T->left == NULL) ? 0 : 1 + T->left->ht;
    int right_height = (T->right == NULL) ? 0 : 1 + T->right->ht;
    return (left_height > right_height) ? left_height : right_height;
}

node* tree::insert(node* T, char word[20], char mean[20]) {
    if (T == NULL) {
        T = new node();
        strcpy(T->keyword, word);
        strcpy(T->meaning, mean);
        T->left = T->right = NULL;
    } else if (strcmp(word, T->keyword) > 0) {
        T->right = insert(T->right, word, mean);
        if (BF(T) == -2) {
            if (strcmp(word, T->right->keyword) > 0)
                T = Rotate_Left(T);
            else {
                T->right = Rotate_Right(T->right);
                T = Rotate_Left(T);
            }
        }
    } else if (strcmp(word, T->keyword) < 0) {
        T->left = insert(T->left, word, mean);
        if (BF(T) == 2) {
            if (strcmp(word, T->left->keyword) < 0)
                T = Rotate_Right(T);
            else {
                T->left = Rotate_Left(T->left);
                T = Rotate_Right(T);
            }
        }
    }
    T->ht = height(T);
    return T;
}

void tree::modify(node* head) {
    char data[20], mean[20];
    node* temp = head;
    cout << "\nEnter the word for which you want to modify the meaning: ";
    cin >> data;
    cout << "\nEnter the new meaning: ";
    cin >> mean;
    while (temp != NULL) {
        if (strcmp(temp->keyword, data) == 0) {
            strcpy(temp->meaning, mean);
            cout << "\nThe keyword is: " << temp->keyword << " and its modified meaning is: " << temp->meaning << "\n";
            return;
        }
        temp = (strcmp(temp->keyword, data) < 0) ? temp->right : temp->left;
    }
    cout << "\nThe word " << data << " is not present in the BST\n";
}

void tree::delet() {
    node* temp = root;
    node* parent = temp;
    char data[20];
    cout << "\nEnter the word you want to delete: ";
    cin >> data;

    while (temp != NULL) {
        if (strcmp(temp->keyword, data) == 0)
            break;
        parent = temp;
        temp = (strcmp(temp->keyword, data) < 0) ? temp->right : temp->left;
    }

    if (temp == NULL) {
        cout << "\nThe word --" << data << "-- is not present in the BST to delete\n";
        return;
    }

    if (temp->left == NULL && temp->right == NULL) {
        if (parent->left == temp) parent->left = NULL;
        else parent->right = NULL;
        delete temp;
    } else if (temp->left != NULL && temp->right == NULL) {
        if (parent->left == temp) parent->left = temp->left;
        else parent->right = temp->left;
        delete temp;
    } else if (temp->right != NULL && temp->left == NULL) {
        if (parent->left == temp) parent->left = temp->right;
        else parent->right = temp->right;
        delete temp;
    } else {
        node* in_succ = In_Succ(parent);
        strcpy(temp->keyword, in_succ->keyword);
        strcpy(temp->meaning, in_succ->meaning);
        parent->right = in_succ->right;
        delete in_succ;
    }
    cout << "\nThe node has been deleted.\n";
}

node* tree::In_Succ(node* root) {
    node* trav = root->right;
    while (trav->left != NULL)
        trav = trav->left;
    return trav;
}

void tree::preorder(node* root) {
    if (root != NULL) {
        cout << endl << root->keyword << "   !   " << root->meaning;
        preorder(root->left);
        preorder(root->right);
    }
}

void tree::inorder(node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << endl << root->keyword << "   !   " << root->meaning;
        inorder(root->right);
    }
}

void tree::descending(node* root) {
    if (root != NULL) {
        descending(root->right);
        cout << endl << root->keyword << "   !   " << root->meaning;
        descending(root->left);
    }
}

void tree::postorder(node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << endl << root->keyword << "   !   " << root->meaning;
    }
}

void tree::display() {
    int ch;
    do {
        cout << "\nEnter your choice" << endl;
        cout << "1. Pre-order\n2. In-order\n3. Post-order\n4. Modify\n5. Search\n6. Delete\n7. Ascending order\n8. Descending order\n9. Max Comparisons\n0. Exit\n";
        cin >> ch;
        switch (ch) {
            case 1: cout << "\n KEYWORD   !   MEANING"; preorder(root); break;
            case 2: cout << "\n KEYWORD   !   MEANING"; inorder(root); break;
            case 3: cout << "\n KEYWORD   !   MEANING"; postorder(root); break;
            case 4: modify(root); break;
            case 5: search(); break;
            case 6: delet(); break;
            case 7: ascending(); break;
            case 8: descending(root); break;
            case 9: max_compare(root); break;
            case 0: exit(0);
            default: cout << "\nWrong choice"; break;
        }
    } while (ch != 0);
}

void tree::search1(node* head) {
    node* temp = head;
    char data[20];
    cout << "\nEnter the word you want to search: ";
    cin >> data;

    while (temp != NULL) {
        if (strcmp(temp->keyword, data) == 0) {
            cout << "\nThe word " << data << " is present in the BST\n";
            cout << "Its meaning is: " << temp->meaning << "\n";
            return;
        }
        temp = (strcmp(temp->keyword, data) < 0) ? temp->right : temp->left;
    }
    cout << "\nThe word " << data << " is not present in the BST\n";
}

void tree::max_compare(node* root) {
    cout << "\nMax Comparisons: ";
    if (root != NULL) {
        max_compare(root->left);
        max_compare(root->right);
    }
}

int main() {
    tree obj;
    obj.insert1("hello", "greeting");
    obj.insert1("world", "earth");
    obj.insert1("apple", "fruit");
    obj.insert1("banana", "fruit");

    obj.display();
    return 0;
}
