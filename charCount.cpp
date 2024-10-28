#include <iostream>
#include <string>

using namespace std;

void characterCountFraming(const string& data, string& frame) {
    int dataLength = data.length();

    // Convert data length to string and prepend it to the data
    frame = to_string(dataLength) + data;
}

int main() {
    string data = "Hello, world!";
    string frame;

    characterCountFraming(data, frame);

    cout << "Frame: " << frame << endl;

    return 0;
}
