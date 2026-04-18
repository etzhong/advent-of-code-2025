#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ranges>


// Struct representing a 2D point for a red tile location
struct Point {
    Point(long long px, long long py)
    : x(px), y(py) {}
    long long x;
    long long y;

    bool operator==(const Point&) const = default;
};

// Compute area between two tile points
inline long long compute_area(Point const& a, Point const& b) {
    return (a.x-b.x+1)*(a.y-b.y+1);
}

int main() {
    // Open input file and parse red tiles
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> tokens;
    std::vector<Point> redTiles;
    std::unordered_map<long long, std::vector<std::pair<long long>>> xEdges;
    std::unordered_map<long long, std::vector<std::pair<long long>>> yaEdges;
    long long px = INT_MAX, py = INT_MAX;
    while (std::getline(ifile, line)) {
        tokens.clear();
        for (auto&& part : line | std::views::split(','))
            tokens.emplace_back(part.begin(), part.end());
        long long x = std::stoll(tokens[0]);
        long long y = std::stoll(tokens[1]);
        if (px != INT_MAX && py != INT_MAX) {
            if (px == x) { // Horizontal edge

            } else if (py == y) { // Vertical edge

            }
        }
        redTiles.emplace_back(x, y);
        px = x; py = y;
    }
    ifile.close();


    // Key insight: Pattern cannot fully enclose an empty space. A candidate pair is valid if
    // all four edges are validly enclosed




    // Given list of points from input, determine which ones are "red"
    // Requirements for a tile being red
        // On edge (has at least one of adjacent 8 tiles missing)
        // Must be one corner tile missing or 3 corner tiles missing
    // Iterate through red pairwise red points and determine largest
    // Key insight: cannot enclose an empty space
    int maxArea;

    // Ouput max area
    std::cout << std::format("Max Area: {}\n", maxArea);

    return 0;
}
