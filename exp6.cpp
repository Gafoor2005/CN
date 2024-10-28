#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Data structure to represent a routing table entry
struct Route {
    string destination;
    string nextHop;
    int cost;
};

// Data structure to represent a network node
struct Node {
    string id;
    vector<Node*> children;
    Node* parent;
    map<string, Route> routes;
};

// Hierarchical Routing Algorithm implementation
class HierarchicalRouter {
public:
    // Constructor
    HierarchicalRouter(Node* root) : root(root) {}

    // Add a child node to a parent node
    void addNode(Node* parent, Node* child) {
        parent->children.push_back(child);
        child->parent = parent;
    }

    // Add a route to the routing table
    void addRoute(Node* node, Route route) {
        string dest = route.destination;
        node->routes[dest] = route;
    }

    // Find the shortest path using hierarchical routing
    string findPath(string source, string destination) {
        Node* srcNode = findNode(root, source);
        Node* dstNode = findNode(root, destination);

        if (srcNode == nullptr || dstNode == nullptr) {
            return "Path not found";
        }

        // Perform hierarchical routing
        string path = hierarchicalRouting(srcNode, dstNode);
        return path;
    }

private:
    Node* root;

    // Find a node in the network
    Node* findNode(Node* node, string id) {
        if (node->id == id) {
            return node;
        }

        for (Node* child : node->children) {
            Node* found = findNode(child, id);
            if (found != nullptr) {
                return found;
            }
        }

        return nullptr;
    }

    // Hierarchical routing function
    string hierarchicalRouting(Node* src, Node* dst) {
        // Base case: source and destination are the same
        if (src == dst) {
            return src->id;
        }

        // Check if destination is a child of source
        for (Node* child : src->children) {
            if (child == dst) {
                return src->id + " -> " + hierarchicalRouting(child, dst);
            }
        }

        // Check if source is a child of destination
        if (src->parent != nullptr && src->parent == dst) {
            return hierarchicalRouting(src->parent, dst);
        }

        // Recursively search for a path
        for (Node* child : src->children) {
            string path = hierarchicalRouting(child, dst);
            if (path != "Path not found") {
                return src->id + " -> " + path;
            }
        }

        // If no path is found, return error message
        return "Path not found";
    }
};

int main() {
    // Create network nodes
    Node nodeA = {"A", {}, nullptr};
    Node nodeB = {"B", {}, nullptr};
    Node nodeC = {"C", {}, nullptr};
    Node nodeD = {"D", {}, nullptr};
    Node nodeE = {"E", {}, nullptr};

    // Create hierarchical router
    HierarchicalRouter router(&nodeA);

    // Add child nodes
    router.addNode(&nodeA, &nodeB);
    router.addNode(&nodeA, &nodeC);
    router.addNode(&nodeB, &nodeD);
    router.addNode(&nodeC, &nodeE);

    // Add routes
    Route route1 = {"D", "B", 2};
    router.addRoute(&nodeA, route1);
    Route route2 = {"E", "C", 3};
    router.addRoute(&nodeA, route2);

    // Find path
    string path = router.findPath("A", "D");
    cout << "Path: " << path << endl;

    return 0;
}
// output:
// Path: A -> B -> D