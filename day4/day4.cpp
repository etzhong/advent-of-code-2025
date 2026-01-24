#include <iostream>
#include <fstream>

bool const can_access(const std::vector<std::string>& map, int row, int col) {
    bool const onTopEdge = (row == 0);
    bool const onBotEdge = (row == (map.size()-1));
    bool const onLeftEdge = (col == 0);
    bool const onRightEdge = (col == (map.front().size()-1));
    int numAdjacentRolls = 0;
    if (!onTopEdge && !onLeftEdge)  numAdjacentRolls += (map[row-1][col-1] == '@');
    if (!onTopEdge)                 numAdjacentRolls += (map[row-1][col] == '@');
    if (!onTopEdge && !onRightEdge) numAdjacentRolls += (map[row-1][col+1] == '@');
    if (!onLeftEdge)                numAdjacentRolls += (map[row][col-1] == '@');
    if (!onRightEdge)               numAdjacentRolls += (map[row][col+1] == '@');
    if (!onBotEdge && !onLeftEdge)  numAdjacentRolls += (map[row+1][col-1] == '@');
    if (!onBotEdge)                 numAdjacentRolls += (map[row+1][col] == '@');
    if (!onBotEdge && !onRightEdge) numAdjacentRolls += (map[row+1][col+1] == '@');
    return (numAdjacentRolls < 4);
}

int main() {
    std::vector<std::string> map;
    std::string row;
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    ifile.close();
    while (std::getline(ifile, row))
        map.emplace_back(row);
    int numRemovableRolls = 0;
    std::vector<std::pair<int, int>> toRemove;
    do {
        for (auto roll : toRemove)
            map[roll.first][roll.second] = '.';
        toRemove.clear();
        for (int row=0; row<map.size(); row++)
            for (int col=0; col<map.front().size(); col++)
                if (map[row][col] == '@' && can_access(map, row, col)) {
                    numRemovableRolls++;
                    toRemove.emplace_back(row, col);
                }
    } while (!toRemove.empty());
    std::cout << "Total Removable Rolls: " << numRemovableRolls << std::endl;
    return 0;
}
