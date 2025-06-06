#include <iostream>
#include <cstring>
using namespace std;

struct node {
    char k[20]; // keyword
    char m[20]; // meaning
    node *left;
    node *right;
};

class dict {
public:
    node *root;

    dict() {
        root = NULL;
    }

    void create();
    void disp(node *);
    void insert(node *root, node *temp);
    int search(node *, char []);
    int update(node *, char []);
    node* del(node *, char []);
    node* min(node *);
};

void dict::create() {
    node *temp;
    int ch;

    do {
        temp = new node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;

        temp->left = NULL;
        temp->right = NULL;

        if (root == NULL)
            root = temp;
        else
            insert(root, temp);

        cout << "Do you want to add more? (Yes=1 / No=0): ";
        cin >> ch;
    } while (ch == 1);
}

void dict::insert(node *root, node *temp) {
    if (strcmp(temp->k, root->k) < 0) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    } else {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

void dict::disp(node *root) {
    if (root != NULL) {
        disp(root->left);
        cout << "\nKeyword: " << root->k << "\tMeaning: " << root->m;
        disp(root->right);
    }
}

int dict::search(node *root, char k[20]) {
    int c = 0;
    while (root != NULL) {
        c++;
        if (strcmp(k, root->k) == 0) {
            cout << "\nNumber of Comparisons: " << c;
            return 1;
        }
        if (strcmp(k, root->k) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return -1;
}

int dict::update(node *root, char k[20]) {
    while (root != NULL) {
        if (strcmp(k, root->k) == 0) {
            cout << "Enter New Meaning for keyword \"" << root->k << "\": ";
            cin >> root->m;
            return 1;
        }
        if (strcmp(k, root->k) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return -1;
}

node* dict::del(node *root, char k[20]) {
    node *temp;

    if (root == NULL) {
        cout << "\nElement Not Found";
        return root;
    }

    if (strcmp(k, root->k) < 0) {
        root->left = del(root->left, k);
        return root;
    }

    if (strcmp(k, root->k) > 0) {
        root->right = del(root->right, k);
        return root;
    }

    if (root->left == NULL && root->right == NULL) {
        delete root;
        return NULL;
    }

    if (root->left == NULL) {
        temp = root;
        root = root->right;
        delete temp;
        return root;
    }

    if (root->right == NULL) {
        temp = root;
        root = root->left;
        delete temp;
        return root;
    }

    temp = min(root->right);
    strcpy(root->k, temp->k);
    strcpy(root->m, temp->m);
    root->right = del(root->right, temp->k);
    return root;
}

node* dict::min(node *q) {
    while (q->left != NULL)
        q = q->left;
    return q;
}

int main() {
    int ch;
    dict d;

    do {
        cout << "\nMenu\n1. Create\n2. Display\n3. Search\n4. Update\n5. Delete\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                d.create();
                break;
            case 2:
                if (d.root == NULL)
                    cout << "\nNo keywords to display.";
                else
                    d.disp(d.root);
                break;
            case 3:
                if (d.root == NULL)
                    cout << "\nDictionary is empty. Add keywords first.";
                else {
                    char k[20];
                    cout << "\nEnter keyword to search: ";
                    cin >> k;
                    if (d.search(d.root, k) == 1)
                        cout << "\nKeyword Found.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 4:
                if (d.root == NULL)
                    cout << "\nDictionary is empty. Add keywords first.";
                else {
                    char k[20];
                    cout << "\nEnter keyword to update meaning: ";
                    cin >> k;
                    if (d.update(d.root, k) == 1)
                        cout << "\nMeaning Updated.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 5:
                if (d.root == NULL)
                    cout << "\nDictionary is empty. Add keywords first.";
                else {
                    char k[20];
                    cout << "\nEnter keyword to delete: ";
                    cin >> k;
                    d.root = d.del(d.root, k);
                }
                break;
            default:
                cout << "\nInvalid choice.";
        }
    } while (ch <= 5);

    return 0;
}
