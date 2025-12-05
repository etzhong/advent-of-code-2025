#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<int> moves;
    std::string move;
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    while (ifile >> move) {
        if (move.empty() || (move.front() != 'L' && move.front() != 'R')) {
            std::cerr << "Invalid input file" << std::endl;
            return 1;
        }
        const int val = ((move.front() == 'L') ? -1 : 1) * std::stoi(move.substr(1, move.size()-1));
        moves.emplace_back(val);
    }
    ifile.close();
    int pos = 50, numZero = 0;
    for (int move : moves) {
        int endPos = pos + ((std::abs(move) % 100) * ((move < 0) ? -1 : 1));
        if (pos != 0 && (endPos >= 100 || endPos <= 0)) numZero++;
        numZero += std::abs(move / 100);
        pos = ((pos + move) % 100 + 100) % 100;
    }
    std::cout << "Password: " << numZero << std::endl;
    return 0;
}
