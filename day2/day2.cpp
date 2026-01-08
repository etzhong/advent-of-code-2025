#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> ranges;
    std::string range;
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    while (std::getline(ifile, range, ',')) {
        std::string lower = range.substr(0, range.find('-'));
        std::string upper = range.substr(range.find('-')+1);
        if (upper.back() == '\n') upper.pop_back();
        ranges.emplace_back(lower, upper);
    }
    ifile.close();
    unsigned long long invalidIdSum = 0;
    for (const auto& rp : ranges) {
        const std::string lower = rp.first;
        const std::string upper = rp.second;
        unsigned long long lowerHalfIdBound, upperHalfIdBound;
        if (lower.size() % 2 && upper.size() % 2 && lower.size() == upper.size()) continue;
        else if(lower.size() % 2 == 0 && upper.size() % 2 == 1) {
            lowerHalfIdBound = std::stoull(lower.substr(0, lower.size()/2));
            upperHalfIdBound = (std::pow(10, lower.size()/2) - 1);
        } else if (lower.size() % 2 == 1 && upper.size() % 2 == 0) {
            lowerHalfIdBound = std::pow(10, upper.size()/2 - 1);
            upperHalfIdBound = std::stoull(upper.substr(0, upper.size()/2));
        } else if (lower.size() % 2 == 0 && upper.size() % 2 == 0) {
            lowerHalfIdBound = std::stoull(lower.substr(0, lower.size()/2));
            upperHalfIdBound = std::stoull(upper.substr(0, upper.size()/2));
        }
        for (unsigned long long halfId = lowerHalfIdBound; halfId <= upperHalfIdBound; halfId++) {
            unsigned long long id = std::stoull(std::to_string(halfId) + std::to_string(halfId));
            if (std::stoull(lower) <= id && id <= stoull(upper))
                invalidIdSum += id;
        }
    }
    std::cout << "Invalid ID Total: " << invalidIdSum << std::endl;
    return 0;
}
