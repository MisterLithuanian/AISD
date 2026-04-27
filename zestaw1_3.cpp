#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 50; 

class Zbior {
private:
    string tab[MAX_SIZE];
    int size;

public:
    Zbior() {
        size = 0;
    }
    bool contains(string x) {
        for (int i = 0; i < size; i++) {
            if (tab[i] == x) {
                return true;
            }
        }
        return false;
    }
    void insert(string x) {
        if (x.length() > 50) {
            cout << "napis za dlugi\n";
            return;
        }
        if (contains(x)) {
            return;
        }
        if (size < MAX_SIZE) {
            tab[size++] = x;
        } else {
            cout << "Zbior pelny\n";
        }
    }
    void remove(string x) {
        for (int i = 0; i < size; i++) {
            if (tab[i] == x) {
                tab[i] = tab[size - 1]; 
                size--;
                return;
            }
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            cout << tab[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Zbior A;

    A.insert("Lorem ");
    A.insert("ipsum");
    A.insert("dolor");
    A.print();
    cout << "Czy jest 'ipsum'? " << A.contains("ipsum") << endl;
    A.remove("ipsum");
    A.print();

    return 0;
}