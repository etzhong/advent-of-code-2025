#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
    std::vector<std::pair<unsigned int, unsigned int>> rangeWidths;
    std::string range;
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    while (std::getline(ifile, range, ',')) {
        const std::string lower = range.substr(0, range.find('-'));
        const std::string upper = range.substr(range.find('-')+1);
        ranges.emplace_back(std::stoull(lower), std::stoull(upper));
        rangeWidths.emplace_back(lower.size(), upper.size());
    }
    ifile.close();
    std::vector<long long> invalidIDs;
    for (unsigned int i=0; i<ranges.size(); i++) {

    }

    return 0;
}

/*
func outputInvalidFromPair (a, b) {

}


Key Insights
    (1) An invalid ID MUST have an even number of digits
    (2) Given (1), we only need to check the "even-digit subrange" of an invalid range
    (3)

*/
