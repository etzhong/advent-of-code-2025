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
    std::vector<std::string> inputText;
    while (std::getline(ifile, line) && !line.empty())
        inputText.emplace_back(line);
    ifile.close();
    int const inputWidth = inputText.front().size();
    int const inputHeight = inputText.size();
    int colStartPtr = 0;
    long long totalOpSum = 0;
    for (int colIdx=1; colIdx<inputWidth; colIdx++) {
        bool endCol = true;
        for (int rowIdx=0; rowIdx<(inputHeight-1); rowIdx++)
            if (inputText[rowIdx][colIdx] != ' ')
                endCol = false;
        if (endCol == true || colIdx == (inputWidth-1)) { // Reached end of operation column. Perform operation
            if (colIdx == (inputWidth-1)) // Shift right colIdx pointer if last operation column
                colIdx = inputWidth;
            bool const multiply = (inputText[inputHeight-1][colStartPtr] == '*');
            long long opTotal = (multiply) ? 1 : 0;
            for (int operandIdx=colIdx-1; operandIdx >= colStartPtr; operandIdx--) {
                long long operandVal = 0;
                long long multiplier = 1;
                for (int digitIdx=(inputHeight-2); digitIdx >= 0; digitIdx--) {
                    if (inputText[digitIdx][operandIdx] != ' ') {
                        operandVal += ((inputText[digitIdx][operandIdx] - '0') * multiplier);
                        multiplier *= 10;
                    }
                }
                opTotal = (multiply) ? (opTotal * operandVal) : (opTotal + operandVal);
            }
            totalOpSum += opTotal;
            colStartPtr = colIdx + 1;
        }
    }
    std::cout << "Total Operation Sum: " << totalOpSum << "\n";
    return 0;
}
