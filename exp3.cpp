#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure to represent a network device
struct Device {
    string name;
    int distance;
    bool visited;
    Device* previous;
};

// Define a function to print the shortest path
void printPath(Device* device) {
    if (device->previous != nullptr) {
        printPath(device->previous);
    }
    cout << device->name << " ";
}

// Define Dijkstra's algorithm function
void dijkstra(vector<Device*> devices, Device* start) {
    // Initialize distances and previous devices
    for (Device* device : devices) {
        device->distance = numeric_limits<int>::max();
        device->visited = false;
        device->previous = nullptr;
    }
    start->distance = 0;

    // Priority queue to hold devices to be processed
    priority_queue<pair<int, Device*>, vector<pair<int, Device*>>, greater<pair<int, Device*>>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        Device* current = queue.top().second;
        queue.pop();

        if (current->visited) {
            continue;
        }

        current->visited = true;

        // Process neighbors
        for (Device* neighbor : devices) {
            if (neighbor == current) {
                continue;
            }

            int distance = current->distance + 1; // Assuming equal weights

            if (distance < neighbor->distance) {
                neighbor->distance = distance;
                neighbor->previous = current;
                queue.push({distance, neighbor});
            }
        }
    }
}

int main() {
    // Create network devices
    Device device1 = {"Device1", 0, false, nullptr};
    Device device2 = {"Device2", 0, false, nullptr};
    Device device3 = {"Device3", 0, false, nullptr};
    Device device4 = {"Device4", 0, false, nullptr};

    // Add edges (connections) between devices
    vector<Device*> devices = {&device1, &device2, &device3, &device4};

    // Run Dijkstra's algorithm
    dijkstra(devices, &device1);

    // Print shortest paths
    for (Device* device : devices) {
        cout << "Shortest path from Device1 to " << device->name << ": ";
        printPath(device);
        cout << endl;
    }

    return 0;
}