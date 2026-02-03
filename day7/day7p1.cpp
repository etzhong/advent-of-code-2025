#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    const int manifoldWidth = manifold.front().size();
    const int manifoldHeight = manifold.size();
    std::vector<std::vector<bool>> beamMap(manifoldHeight, std::vector<bool>(manifoldWidth, false));
    beamMap.front()[manifold.front().find('S')] = true;
    int splitCount = 0;
    for (int row=1; row<manifoldHeight; row++) {
        for (int col=0; col<manifoldWidth; col++) {
            if(beamMap[row-1][col]) {
                if (manifold[row][col] == '^') {
                    splitCount++;
                    if (col > 0) beamMap[row][col-1] = true;
                    if (col < (manifoldWidth-1)) beamMap[row][col+1] = true;
                }
                else beamMap[row][col] = true;
            }
        }
    }
    std::cout << "Split Count: " << splitCount << "\n";
    return 0;
}
