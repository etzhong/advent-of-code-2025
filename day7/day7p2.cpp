#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

int main() {
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> manifold;
    while (std::getline(ifile, line))
        manifold.emplace_back(line);
    ifile.close();
    int const manifoldWidth = manifold.front().size();
    int const manifoldHeight = manifold.size();
    std::vector<std::vector<long long>> timelineMap(manifoldHeight, std::vector<long long>(manifoldWidth, 0));
    timelineMap.front()[manifold.front().find('S')] = 1;
    for (int row=1; row<manifoldHeight; row++) {
        for (int col=0; col<manifoldWidth; col++) {
            if(timelineMap[row-1][col]) {
                if (manifold[row][col] == '^') {
                    if (col > 0) timelineMap[row][col-1] += timelineMap[row-1][col];
                    if (col < (manifoldWidth-1)) timelineMap[row][col+1] += timelineMap[row-1][col];
                }
                else timelineMap[row][col] += timelineMap[row-1][col];
            }
        }
    }
    long long const numTimelines = std::accumulate(timelineMap.back().begin(), timelineMap.back().end(), 0LL);
    std::cout << "Number of Timelines: " << numTimelines << "\n";
    return 0;
}
