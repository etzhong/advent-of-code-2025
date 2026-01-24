#include <iostream>
#include <fstream>

#define NUM_JOLTAGE_CELLS 12

int main() {
    std::vector<std::string> batteryBanks;
    std::array<unsigned int, NUM_JOLTAGE_CELLS> joltageCellIdxs{};
    std::string bank;
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    while (std::getline(ifile, bank))
        batteryBanks.emplace_back(bank);
    ifile.close();
    unsigned long long maxJoltage = 0;
    for (const auto& bank : batteryBanks) {
        joltageCellIdxs[0] = 0;
        for (unsigned int cellIdx = 1; cellIdx < bank.size()-(NUM_JOLTAGE_CELLS-1); cellIdx++)
            if (bank[cellIdx] > bank[joltageCellIdxs[0]])
                joltageCellIdxs[0] = cellIdx;
        for (unsigned int cellNum = 1; cellNum < NUM_JOLTAGE_CELLS; cellNum++) {
            joltageCellIdxs[cellNum] = joltageCellIdxs[cellNum-1]+1;
            for (unsigned int cellIdx = joltageCellIdxs[cellNum-1]+2;
                cellIdx < bank.size()-(NUM_JOLTAGE_CELLS-cellNum-1); cellIdx++) {
                if (bank[cellIdx] > bank[joltageCellIdxs[cellNum]])
                    joltageCellIdxs[cellNum] = cellIdx;
            }
        }
        unsigned long long maxBankJoltage = 0, multiplier = 1;
        for (int cellNum = NUM_JOLTAGE_CELLS-1; cellNum >= 0; cellNum--) {
            maxBankJoltage += (static_cast<unsigned long long>((bank[joltageCellIdxs[cellNum]] - '0')) * multiplier);
            multiplier *= 10;
        }
        maxJoltage += maxBankJoltage;
    }
    std::cout << "Max Joltage: " << maxJoltage << std::endl;
    return 0;
}
