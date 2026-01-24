#include <iostream>
#include <fstream>

int main() {
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::pair<long long, long long>> intervals;
    std::vector<long long> ids;
    while (std::getline(ifile, line) && !line.empty())
        intervals.emplace_back(std::stoll(line.substr(0, line.find('-'))), std::stoll(line.substr(line.find('-')+1)));
    while (std::getline(ifile, line))
        ids.emplace_back(std::stoll(line));
    ifile.close();
    int numFreshItems = 0;
    bool isFresh;
    for (auto const id : ids) {
        isFresh = false;
        for (auto const& interval : intervals) {
            if (interval.first <= id && id <= interval.second) {
                isFresh = true;
                break;
            }
        }
        numFreshItems += isFresh;
    }
    std::cout << "Number of Fresh Items: " << numFreshItems << std::endl;
    return 0;
}
