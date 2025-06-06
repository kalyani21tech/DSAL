#include<iostream>
using namespace std;

struct node {
    int data;
    node *L;
    node *R;
};

node *root, *temp;
int count, key;

class bst {
public:
    bst() {
        root = NULL;
        count = 0;
    }

    void create();
    void insert(node*, node*);
    void disin(node*);
    void dispre(node*);
    void dispost(node*);
    void search(node*, int);
    int height(node*);
    void mirror(node*);
    void min(node*);
};

void bst::create() {
    char ans;
    do {
        temp = new node;
        cout << "Enter the data: ";
        cin >> temp->data;
        temp->L = NULL;
        temp->R = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp);
        }

        cout << "Do you want to insert more value (y/n): ";
        cin >> ans;
        count++;
        cout << endl;
    } while (ans == 'y');

    cout << "The total number of nodes are: " << count << endl;
}

void bst::insert(node *root, node *temp) {
    if (temp->data > root->data) {
        if (root->R == NULL) {
            root->R = temp;
        } else {
            insert(root->R, temp);
        }
    } else {
        if (root->L == NULL) {
            root->L = temp;
        } else {
            insert(root->L, temp);
        }
    }
}

void bst::disin(node *root) {
    if (root != NULL) {
        disin(root->L);
        cout << root->data << "\t";
        disin(root->R);
    }
}

void bst::dispre(node *root) {
    if (root != NULL) {
        cout << root->data << "\t";
        dispre(root->L);
        dispre(root->R);
    }
}

void bst::dispost(node *root) {
    if (root != NULL) {
        dispost(root->L);
        dispost(root->R);
        cout << root->data << "\t";
    }
}

void bst::search(node *root, int key) {
    int flag = 0;
    cout << "\nEnter your key: ";
    cin >> key;
    temp = root;

    while (temp != NULL) {
        if (key == temp->data) {
            cout << "\nKEY FOUND\n";
            flag = 1;
            break;
        }

        if (key > temp->data) {
            temp = temp->R;
        } else {
            temp = temp->L;
        }
    }

    if (flag == 0) {
        cout << "\nKEY NOT FOUND\n";
    }
}

int bst::height(node *root) {
    if (root == NULL) {
        return 0;
    } else {
        int hl = height(root->L);
        int hr = height(root->R);
        return 1 + max(hl, hr);
    }
}

void bst::min(node *root) {
    temp = root;
    while (temp->L != NULL) {
        temp = temp->L;
    }
    cout << temp->data << endl;
}

void bst::mirror(node *root) {
    if (root != NULL) {
        mirror(root->L);
        mirror(root->R);
        temp = root->L;
        root->L = root->R;
        root->R = temp;
    }
}

int main() {
    bst t;
    int ch;
    char ans;

    do {
        cout << "\nMenu:\n";
        cout << "1) Insert new node\n";
        cout << "2) Number of nodes in longest path\n";
        cout << "3) Minimum value\n";
        cout << "4) Mirror tree\n";
        cout << "5) Search a key\n";
        cout << "6) Inorder traversal\n";
        cout << "7) Preorder traversal\n";
        cout << "8) Postorder traversal\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                t.create();
                break;
            case 2:
                cout << "\nNumber of nodes in longest path: " << t.height(root) << endl;
                break;
            case 3:
                cout << "\nThe minimum element is: ";
                t.min(root);
                break;
            case 4:
                t.mirror(root);
                cout << "\nThe mirror of the tree (Inorder): ";
                t.disin(root);
                break;
            case 5:
                t.search(root, key);
                break;
            case 6:
                cout << "\n*************** INORDER ***************\n";
                t.disin(root);
                break;
            case 7:
                cout << "\n*************** PREORDER ***************\n";
                t.dispre(root);
                break;
            case 8:
                cout << "\n*************** POSTORDER ***************\n";
                t.dispost(root);
                break;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "\nDo you want to continue (y/n)? ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
