#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

struct Node {
    char id;
    std::vector<char> neighbors;
    std::vector<int> delays;
    std::vector<char> nextHops;
    std::vector<int> distances;
};

void printRoutingTable(const Node& node) {
    std::cout << "Node " << node.id << " Routing Table:" << std::endl;
    std::cout << "| Destination | Next Hop | Delay |" << std::endl;
    for (int i = 0; i < node.distances.size(); ++i) {
        std::cout << "| " << node.id + i << "       | " << node.nextHops[i] << "       | " << node.distances[i] << "     |" << std::endl;
    }
    std::cout << std::endl;
}

void distanceVectorRouting(std::vector<Node>& nodes) {
    bool updated;
    do {
        updated = false;
        for (auto& node : nodes) {
            for (int i = 0; i < node.neighbors.size(); ++i) {
                char neighbor = node.neighbors[i];
                int delay = node.delays[i];
                int neighborIndex = -1;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (nodes[j].id == neighbor) {
                        neighborIndex = j;
                        break;
                    }
                }
                if (neighborIndex != -1) {
                    const Node& neighborNode = nodes[neighborIndex];
                    for (int j = 0; j < neighborNode.distances.size(); ++j) {
                        char destination = neighborNode.id + j;
                        int newDelay = delay + neighborNode.distances[j];
                        int currentIndex = -1;
                        for (int k = 0; k < node.distances.size(); ++k) {
                            if (node.id + k == destination) {
                                currentIndex = k;
                                break;
                            }
                        }
                        if (currentIndex != -1 && newDelay < node.distances[currentIndex]) {
                            node.distances[currentIndex] = newDelay;
                            node.nextHops[currentIndex] = neighbor;
                            updated = true;
                        }
                    }
                }
            }
        }
    } while (updated);
}

int main() {
    // Define nodes and their neighbors
    std::vector<Node> nodes = {
        {'A', {'B', 'D'}, {2, 4}, {'B', 'D'}, {0, 0, INF, INF, INF}},
        {'B', {'A', 'C'}, {2, 3}, {'A', 'C'}, {INF, 0, 0, INF, INF}},
        {'C', {'B', 'E'}, {3, 1}, {'B', 'E'}, {INF, INF, 0, INF, 0}},
        {'D', {'A', 'E'}, {4, 1}, {'A', 'E'}, {0, INF, INF, 0, 0}},
        {'E', {'D', 'C'}, {1, 1}, {'D', 'C'}, {INF, INF, 0, 0, 0}}
    };

    // Initialize distances and next hops
    for (auto& node : nodes) {
        for (int i = 0; i < node.distances.size(); ++i) {
            if (node.id + i == node.id) {
                std::cout<<"eeee";
                node.distances[i] = 0;
            }
        }
    }

    // Run distance vector routing algorithm
    distanceVectorRouting(nodes);

    // Print routing tables
    for (const auto& node : nodes) {
        printRoutingTable(node);
    }

    return 0;
}