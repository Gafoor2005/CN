#include <iostream>
#include <vector>

using namespace std;

void bit_stuffing(vector<bool>& data) {
    int count = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i]) {
            count++;
            if (count == 5) {
                data.insert(data.begin() + i + 1, 0);
                count = 0;
            }
        } else {
            count = 0;
        }
    }
}

void bit_destuffing(vector<bool>& data) {
    int count = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i]) {
            count++;
        } else {
            if (count == 5) {
                data.erase(data.begin() + i);
            }
            count = 0;
        }
    }
}

int main() {
    vector<bool> data = {0,0,1,1,1,1,1,0,1};

    cout << "Original data: ";
    for (bool bit : data) {
        cout << bit;
    }
    cout << endl;

    bit_stuffing(data);

    cout << "Stuffed data: ";
    for (bool bit : data) {
        cout << bit;
    }
    cout << endl;

    bit_destuffing(data);

    cout << "De-stuffed data: ";
    for (bool bit : data) {
        cout << bit;
    }
    cout << endl;

    return 0;
}
