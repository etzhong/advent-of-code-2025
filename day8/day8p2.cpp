#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <vector>
#include <queue>
#include <unordered_set>
#include <ranges>
#include <algorithm>
#include <cmath>

// Struct representing a 3D point for a junction box location
struct Point {
    Point(double px, double py, double pz)
    : x(px), y(py), z(pz) {}
    double x;
    double y;
    double z;
    std::vector<Point*> connections;
};

// Struct representing a connection between 2 junctions and its associated distance
struct Connection {
    Connection (Point* const pa, Point* const pb, double pdist)
    : a(pa), b(pb), distance(pdist) {}
    Point* a;
    Point* b;
    double distance;
    bool operator < (Connection const& other) const {
        return distance > other.distance;
    }
};

// Compute euclidean distance between two points
inline double compute_distance(Point const& a, Point const& b) {
    double const dx = a.x-b.x;
    double const dy = a.y-b.y;
    double const dz = a.z-b.z;
    return std::sqrt(dx*dx+dy*dy+dz*dz);
}

// Determine if two points are connected already by running BFS
bool isConnected(Point* const a, Point* const b) {
    std::queue<Point*> q;
    std::unordered_set<Point*> explored;
    q.emplace(a);
    while (!q.empty()) {
        Point* const node = q.front();
        q.pop();
        for (auto const neighbor : node->connections) {
            if (neighbor == b) return true;
            if (!explored.contains(neighbor)) q.emplace(neighbor);
        }
        explored.emplace(node);
    }
    return false;
}

int main() {
    // Open input file and parse junctions
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> tokens;
    std::vector<Point> junctions;
    while (std::getline(ifile, line)) {
        tokens.clear();
        for (auto&& part : line | std::views::split(','))
            tokens.emplace_back(part.begin(), part.end());
        junctions.emplace_back(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
    }
    ifile.close();

    // Minheap with custom comparator to sort all possible connections by shortest distance
    auto cmp = [](Connection const& a, Connection const&b) {
        return a.distance > b.distance;
    };
    std::priority_queue<Connection, std::vector<Connection>, decltype(cmp)> connectionHeap;

    // Iterate through all possible pairwise connections and add to connectionHeap
    for (int junctIdx=0; junctIdx<junctions.size(); junctIdx++)
        for (int connIdx = junctIdx+1; connIdx<junctions.size(); connIdx++)
            connectionHeap.emplace(
                &junctions[junctIdx],
                &junctions[connIdx],
                compute_distance(junctions[junctIdx], junctions[connIdx])
            );

    // Keep making connections until entire graph is connected
    while (!connectionHeap.empty()){
        Connection const shortestConnection = connectionHeap.top();
        Point* const a = shortestConnection.a;
        Point* const b = shortestConnection.b;
        connectionHeap.pop();
        if (!isConnected(shortestConnection.a, shortestConnection.b)) {
            // Make shortest connection
            a->connections.emplace_back(b);
            b->connections.emplace_back(a);

            // Check if entire graph is now connected
            std::queue<Point*> q;
            std::unordered_set<Point*> explored;
            q.emplace(a);
            int numConnected = 0;
            while (!q.empty()) {
                Point* const node = q.front();
                q.pop();
                for (auto const neighbor : node->connections) {
                    if (!explored.contains(neighbor))
                        q.emplace(neighbor);
                }
                explored.emplace(node);
                numConnected++;
            }
            if (numConnected == junctions.size()) {
                std::cout << static_cast<int>(a->x * b->x) << "\n";
                return 0;
            }
        }
    }

    return 0;
}
