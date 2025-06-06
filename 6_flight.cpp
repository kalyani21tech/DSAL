#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct node {
    string vertex;
    int time;
    node *next;
};

class adjmatlist {
    int m[10][10], n, i, j;
    char ch;
    string v[20];
    node *head[20];
    node *temp = NULL;

public:
    adjmatlist() {
        for (i = 0; i < 20; i++) {
            head[i] = NULL;
        }
    }

    void getgraph();
    void adjlist();
    void displaym();
    void displaya();
};

void adjmatlist::getgraph() {
    cout << "\nEnter number of cities (max 20): ";
    cin >> n;

    cout << "Enter names of cities:\n";
    for (i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << "\nIs there a path between " << v[i] << " and " << v[j] << "? (y/n): ";
            cin >> ch;

            if (ch == 'y') {
                cout << "Enter time required to reach " << v[j] << " from " << v[i] << " (in minutes): ";
                cin >> m[i][j];
            } else if (ch == 'n') {
                m[i][j] = 0;
            } else {
                cout << "Unknown entry. Assuming no connection.\n";
                m[i][j] = 0;
            }
        }
    }

    adjlist(); // Convert matrix to list
}

void adjmatlist::adjlist() {
    for (i = 0; i < n; i++) {
        node *p = new node;
        p->vertex = v[i];
        p->next = NULL;
        head[i] = p;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                node *p = new node;
                p->vertex = v[j];
                p->time = m[i][j];
                p->next = NULL;

                if (head[i]->next == NULL) {
                    head[i]->next = p;
                } else {
                    temp = head[i];
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = p;
                }
            }
        }
    }
}

void adjmatlist::displaym() {
    cout << "\nAdjacency Matrix:\n\t";
    for (j = 0; j < n; j++) {
        cout << v[j] << "\t";
    }

    for (i = 0; i < n; i++) {
        cout << "\n" << v[i] << "\t";
        for (j = 0; j < n; j++) {
            cout << m[i][j] << "\t";
        }
    }
    cout << endl;
}

void adjmatlist::displaya() {
    cout << "\nAdjacency List:\n";
    for (i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\nNo adjacency list present.\n";
            break;
        } else {
            cout << head[i]->vertex;
            temp = head[i]->next;
            while (temp != NULL) {
                cout << " -> " << temp->vertex;
                temp = temp->next;
            }
            cout << endl;
        }
    }

    cout << "\nPaths and Time Required:\n";
    for (i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\nNo adjacency list present.\n";
            break;
        } else {
            temp = head[i]->next;
            while (temp != NULL) {
                cout << head[i]->vertex << " -> " << temp->vertex;
                cout << " [Time: " << temp->time << " min]\n";
                temp = temp->next;
            }
        }
    }
}

int main() {
    int m;
    adjmatlist a;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Display Adjacency List\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> m;

        switch (m) {
            case 1:
                a.getgraph();
                break;
            case 2:
                a.displaym();
                break;
            case 3:
                a.displaya();
                break;
            case 4:
                exit(0);
            default:
                cout << "\nUnknown choice. Try again.\n";
        }
    }

    return 0;
}
