#include <iostream>
#include <vector>

// Function to calculate even parity
int calculateParity(std::vector<int> data) {
    int parity = 0;
    for (int bit : data) {
        parity ^= bit;
    }
    return parity;
}

// Function to detect error using even parity
bool detectError(std::vector<int> data) {
    int parity = calculateParity(data);
    return parity != 0;
}

int main() {
    // Example data
    std::vector<int> data = {1, 0, 1, 0, 1};

    // Detect error
    bool errorDetected = detectError(data);

    if (errorDetected) {
        std::cout << "Error detected!" << std::endl;
    } else {
        std::cout << "No error detected." << std::endl;
    }

    return 0;
}