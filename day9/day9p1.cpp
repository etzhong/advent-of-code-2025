#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>

// Struct representing a 2D point for a red tile location
struct Point {
    Point(int px, int py)
    : x(px), y(py) {}
    long long x;
    long long y;
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
    std::vector<Point> tiles;
    while (std::getline(ifile, line)) {
        tokens.clear();
        for (auto&& part : line | std::views::split(','))
            tokens.emplace_back(part.begin(), part.end());
        tiles.emplace_back(std::stod(tokens[0]), std::stod(tokens[1]));
    }
    ifile.close();

    // Iterate through all possible corners and get max area
    long long maxArea = 0;
    for (int t1=0; t1<(tiles.size()-1); t1++) {
        for (int t2=t1+1; t2<tiles.size(); t2++) {
            maxArea = std::max(maxArea, compute_area(tiles[t1], tiles[t2]));
        }
    }

    // Ouput max area
    std::cout << std::format("Max Area: {}\n", maxArea);

    return 0;
}
