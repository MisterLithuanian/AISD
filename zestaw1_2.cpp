#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

class SetLinked {
private:
    Node* head;
    Node* copyList(Node* otherHead) const {
        if (!otherHead) return nullptr;

        Node* newHead = new Node(otherHead->value);
        Node* currNew = newHead;
        Node* currOld = otherHead->next;

        while (currOld) {
            currNew->next = new Node(currOld->value);
            currNew = currNew->next;
            currOld = currOld->next;
        }
        return newHead;
    }

public:
    SetLinked() : head(nullptr) {}
    ~SetLinked() {
        Node* curr = head;
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    void insert(int x) {
        if (!head || x < head->value) {
            Node* n = new Node(x);
            n->next = head;
            head = n;
            return;
        }
        Node* curr = head;
        while (curr->next && curr->next->value < x) {
            curr = curr->next;
        }
        if (curr->value == x || (curr->next && curr->next->value == x))
            return;
        Node* n = new Node(x);
        n->next = curr->next;
        curr->next = n;
    }
    void remove(int x) {
        if (!head) return;
        if (head->value == x) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }

        Node* curr = head;
        while (curr->next && curr->next->value < x) {
            curr = curr->next;
        }

        if (curr->next && curr->next->value == x) {
            Node* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp;
        }
    }
    bool contains(int x) const {
        Node* curr = head;
        while (curr && curr->value <= x) {
            if (curr->value == x) return true;
            curr = curr->next;
        }
        return false;
    }
    SetLinked unionSet(const SetLinked& other) const {
        SetLinked result;
        Node *a = head, *b = other.head;
        Node** tail = &result.head;

        while (a && b) {
            if (a->value < b->value) {
                *tail = new Node(a->value);
                a = a->next;
            } else if (b->value < a->value) {
                *tail = new Node(b->value);
                b = b->next;
            } else {
                *tail = new Node(a->value);
                a = a->next;
                b = b->next;
            }
            tail = &((*tail)->next);
        }

        while (a) {
            *tail = new Node(a->value);
            tail = &((*tail)->next);
            a = a->next;
        }

        while (b) {
            *tail = new Node(b->value);
            tail = &((*tail)->next);
            b = b->next;
        }

        return result;
    }
    SetLinked intersection(const SetLinked& other) const {
        SetLinked result;
        Node *a = head, *b = other.head;
        Node** tail = &result.head;

        while (a && b) {
            if (a->value < b->value) {
                a = a->next;
            } else if (b->value < a->value) {
                b = b->next;
            } else {
                *tail = new Node(a->value);
                tail = &((*tail)->next);
                a = a->next;
                b = b->next;
            }
        }

        return result;
    }

    SetLinked difference(const SetLinked& other) const {
        SetLinked result;
        Node *a = head, *b = other.head;
        Node** tail = &result.head;

        while (a) {
            while (b && b->value < a->value) {
                b = b->next;
            }

            if (!b || a->value != b->value) {
                *tail = new Node(a->value);
                tail = &((*tail)->next);
            }
            a = a->next;
        }

        return result;
    }
    bool equals(const SetLinked& other) const {
        Node *a = head, *b = other.head;
        while (a && b) {
            if (a->value != b->value) return false;
            a = a->next;
            b = b->next;
        }
        return a == nullptr && b == nullptr;
    }
    void print() const {
        cout << "{ ";
        Node* curr = head;
        while (curr) {
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << "}" << endl;
    }
};

int main() {
    SetLinked A, B;

    A.insert(1);
    A.insert(3);
    A.insert(5);

    B.insert(3);
    B.insert(4);
    B.insert(5);

    cout << "A = "; A.print();
    cout << "B = "; B.print();

    cout << "A ∪ B = "; A.unionSet(B).print();
    cout << "A ∩ B = "; A.intersection(B).print();
    cout << "A - B = "; A.difference(B).print();

    cout << "3 in A: " << A.contains(3) << endl;
    cout << "2 in A: " << A.contains(2) << endl;

    A.remove(3);
    cout << "A after removing 3: "; A.print();

    cout << "A == B: " << A.equals(B) << endl;

    return 0;
}
