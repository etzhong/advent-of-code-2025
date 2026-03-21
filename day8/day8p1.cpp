#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <ranges>
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

// Compute euclidean distance between two points
inline double compute_distance(Point const& a, Point const& b) {
    double const dx = a.x-b.x;
    double const dy = a.y-b.y;
    double const dz = a.z-b.z;
    return std::sqrt(dx*dx+dy*dy+dz*dz);
}

// Determine if two points are connected already by running BFS
bool isConnected(Point* const a, Point* const b) {
    std::queue<Point* const> q;
    std::unordered_set<Point* const> explored;
    q.emplace(&a);
    while (!q.empty()) {
        Point* node = q.front();
        q.pop();
        for (auto neighbor : node->connections) {
            if (neighbor == b) return true;
            //if (!explored.contains(neighbor)) q.emplace(neighbor);
        }
        explored.emplace(node);
    }
    return false;
}

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

int main() {
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

    std::priority_queue<Connection, std::vector<Connection>> connectionHeap;
    for (int junctIdx=0; junctIdx<junctions.size(); junctIdx++)
        for (int connIdx = junctIdx+1; connIdx<junctions.size(); connIdx++)
            /*connectionHeap.emplace(
                compute_distance(junctions[junctIdx], junctions[connIdx]),
                &junctions[junctIdx],
                &junctions[connIdx]
            );*/
            ;

    int const NUM_CONNECTIONS = 1000;
    for (int conn=0; conn<NUM_CONNECTIONS; conn++) {
        // Connection const shortestConnection = connectionHeap.top();
        // connectionHeap.pop();
        // if (isConnected(shortestConnection.a, shortestConnection.b));
    }


    // Read in input. Parse into list of junctions representing graph structure
    // Iterate through all points and push pairs into a heap
    // for every 1000 connections
    //      Pop the shortest connection from the heap
    //      Run BFS on one of the points to determine if junction boxes are already in the same circuit
    //      if connected already in circuit -> do nothing
    //      else: create connection between two points
    // Iterate through junction list and run BFS starting from different points. Track max size of graphs

    return 0;
}
