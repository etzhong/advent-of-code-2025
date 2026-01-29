#include <iostream>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

int main() {
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<std::string>> tokens;
    while (std::getline(ifile, line) && !line.empty()) {
        std::vector<std::string> lineTokens;
        for (auto const& token : line | std::views::split(' ')) {
            if (token.empty()) continue;
            lineTokens.emplace_back(token.begin(), token.end());
        }
        tokens.emplace_back(lineTokens);
    }
    ifile.close();
    long long totalOpSum = 0;
    for (int col=0; col<tokens.front().size(); col++) {
        long long currentOpTotal = std::stoll(tokens.front()[col]);
        for (int row=1; row<tokens.size()-1; row++) {
            if (tokens.back()[col] == "+")      currentOpTotal += std::stoll(tokens[row][col]);
            else if (tokens.back()[col] == "*") currentOpTotal *= std::stoll(tokens[row][col]);
        }
        totalOpSum += currentOpTotal;
    }
    std::cout << "Total Operation Sum: " << totalOpSum << "\n";
    return 0;
}
