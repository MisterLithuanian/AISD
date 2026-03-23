#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class SetSimple {
private:
    int N;
    vector<bool> data;

public:
    SetSimple(int size) : N(size), data(size, false) {}
    void insert(int x) {
        if (x >= 0 && x < N)
            data[x] = true;
    }
    void remove(int x) {
        if (x >= 0 && x < N)
            data[x] = false;
    }
    bool contains(int x) const {
        if (x >= 0 && x < N)
            return data[x];
        return false;
    }
    SetSimple unionSet(const SetSimple& other) const {
        SetSimple result(N);
        for (int i = 0; i < N; i++) {
            result.data[i] = data[i] || other.data[i];
        }
        return result;
    }
    SetSimple intersection(const SetSimple& other) const {
        SetSimple result(N);
        for (int i = 0; i < N; i++) {
            result.data[i] = data[i] && other.data[i];
        }
        return result;
    }
    SetSimple difference(const SetSimple& other) const {
        SetSimple result(N);
        for (int i = 0; i < N; i++) {
            result.data[i] = data[i] && !other.data[i];
        }
        return result;
    }
    bool equals(const SetSimple& other) const {
        for (int i = 0; i < N; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
    void print() const {
        cout << "{ ";
        for (int i = 0; i < N; i++) {
            if (data[i]) cout << i << " ";
        }
        cout << "}" << endl;
    }
};
void testComplexity() {
    cout << "BADANIE ZLOZONOSCI OBLICZENIOWEJ" << endl;
    cout << "Rozmiar N\tSuma (ms)\tWstawianie (ns)" << endl;
    vector<long int> sizes = {10000000, 50000000, 100000000}; 
    for (long int N : sizes) {
        SetSimple A(N), B(N);
        auto start_insert = high_resolution_clock::now();
        A.insert(N - 1);
        auto stop_insert = high_resolution_clock::now();
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);
        auto start_union = high_resolution_clock::now();
        SetSimple C = A.unionSet(B);
        auto stop_union = high_resolution_clock::now();
        auto duration_union = duration_cast<milliseconds>(stop_union - start_union);

        cout << N << "\t\t" << duration_union.count() << "\t\t" << duration_insert.count() << " ns" << endl;
    }
}
int main() {
    int N = 10;
    SetSimple A(N), B(N);

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
    cout << "3 w A: " << A.contains(3) << endl;
    cout << "2 w A: " << A.contains(2) << endl;
    A.remove(3);
    cout << "A po usunieciu 3: "; A.print();
    cout << "A == B: " << A.equals(B) << endl;
    testComplexity();
    return 0;
}
