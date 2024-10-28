#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max(); // Initialize infinity value

// Structure to represent a node in the subnet graph
struct Node {
    char id;
    std::vector<std::pair<char, int>> neighbors; // Neighbor node ID and delay
};

// Structure to represent a routing table entry
struct RoutingTableEntry {
    char destination;
    char nextHop;
    int delay;
    RoutingTableEntry(char dest, char next, int del) : destination(dest), nextHop(next), delay(del) {} // Constructor added
};

// Function to print routing table
void printRoutingTable(const std::vector<RoutingTableEntry>& routingTable) {
    std::cout << "Destination\tNext Hop\tDelay\n";
    for (const auto& entry : routingTable) {
        std::cout << entry.destination << "\t" << entry.nextHop << "\t" << entry.delay << "\n";
    }
}

// Function to update routing table using Distance Vector Routing Algorithm
void updateRoutingTable(std::vector<RoutingTableEntry>& routingTable, const std::vector<Node>& nodes, char currentNode) {
    for (auto& entry : routingTable) {
        // Find the current node's neighbors
        const Node* currentNodeNeighbors = nullptr;
        for (const auto& node : nodes) {
            if (node.id == currentNode) {
                currentNodeNeighbors = &node;
                break;
            }
        }

        // Check if destination is directly connected
        bool isDirectlyConnected = false;
        int directDelay = INF;
        for (const auto& neighbor : currentNodeNeighbors->neighbors) {
            if (neighbor.first == entry.destination) {
                isDirectlyConnected = true;
                directDelay = neighbor.second;
                break;
            }
        }

        if (isDirectlyConnected && directDelay < entry.delay) {
            entry.delay = directDelay;
            entry.nextHop = currentNode;
        } else {
            // Check if going through current node reduces delay
            for (const auto& neighbor : currentNodeNeighbors->neighbors) {
                const Node* neighborNode = nullptr;
                for (const auto& node : nodes) {
                    if (node.id == neighbor.first) {
                        neighborNode = &node;
                        break;
                    }
                }

                for (const auto& neighborEntry : routingTable) {
                    if (neighborEntry.destination == entry.destination) {
                        int newDelay = neighbor.second + neighborEntry.delay;
                        if (newDelay < entry.delay) {
                            entry.delay = newDelay;
                            entry.nextHop = neighbor.first;
                        }
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    // Define subnet graph nodes and their neighbors
    std::vector<Node> nodes = {
        {'A', {{'B', 3}, {'C', 2}}},
        {'B', {{'A', 3}, {'D', 1}}},
        {'C', {{'A', 2}, {'D', 1}}},
        {'D', {{'B', 1}, {'C', 1}}}
    };

    // Initialize routing tables for each node
    std::vector<std::vector<RoutingTableEntry>> routingTables(4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j) {
                routingTables[i].push_back(RoutingTableEntry('A' + j, 'A' + j, INF));
            }
        }
    }

    // Initialize routing tables with direct delays
    for (int i = 0; i < nodes.size(); ++i) {
        for (const auto& neighbor : nodes[i].neighbors) {
            for (auto& entry : routingTables[i]) {
                if (entry.destination == neighbor.first) {
                    entry.delay = neighbor.second;
                    entry.nextHop = neighbor.first;
                }
            }
        }
    }

    // Run Distance Vector Routing Algorithm
    bool converged = false;
    while (!converged) {
        converged = true;
        for (int i = 0; i < nodes.size(); ++i) {
            updateRoutingTable(routingTables[i], nodes, nodes[i].id);
            for (const auto& entry : routingTables[i]) {
                if (entry.delay == INF) {
                    converged = false;
                }
            }
        }
    }

    // Print routing tables
    for (int i = 0; i < nodes.size(); ++i) {
        std::cout << "Routing Table for Node " << nodes[i].id << ":\n";
        printRoutingTable(routingTables[i]);
        std::cout << "\n";
    }

    return 0;
}