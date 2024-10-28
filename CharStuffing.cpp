#include <iostream>
#include <string>

using namespace std;

const char FLAG = 0x7E;
const char ESCAPE = 0x7D;

void stuff_data(const string& data, string& stuffed_data) {
    stuffed_data.clear();
    stuffed_data += FLAG;

    for (char c : data) {
        if (c == FLAG || c == ESCAPE) {
            stuffed_data += ESCAPE;
        }
        stuffed_data += c;
    }

    stuffed_data += FLAG;
}

void de_stuff_data(const string& stuffed_data, string& data) {
    data.clear();

    for (size_t i = 1; i < stuffed_data.length() - 1; ++i) {
        if (stuffed_data[i] == ESCAPE) {
            ++i; // Skip the escape character
            data += stuffed_data[i]; // Directly add the next character
        } else {
            data += stuffed_data[i];
        }
    }
}

int main() {
    string data = "This is some data with a FLAG(~) and an ESCAPE(})";
    string stuffed_data, de_stuffed_data;

    cout << "Original data: " << data << endl;

    stuff_data(data, stuffed_data);
    cout << "Stuffed data: " << stuffed_data << endl;

    de_stuff_data(stuffed_data, de_stuffed_data);
    cout << "De-stuffed data: " << de_stuffed_data << endl;

    return 0;
}
