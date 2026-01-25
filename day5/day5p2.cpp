#include <iostream>
#include <fstream>
#include <list>

int main() {
    std::ifstream ifile("input.txt");
    if (!ifile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::list<std::pair<long long, long long>> intervals;
    std::vector<std::pair<long long, long long>> toMerge;
    while (std::getline(ifile, line) && !line.empty()) {
        auto const newInterval = std::make_pair(std::stoll(line.substr(0, line.find('-'))),
            std::stoll(line.substr(line.find('-')+1)));
        toMerge.clear();
        for (auto& interval : intervals) {
            if ((newInterval.first <= interval.second && newInterval.second >= interval.second)
                || (newInterval.first <= interval.first && newInterval.second >= interval.first)
                || (newInterval.first <= interval.first && newInterval.second >= interval.second)
                || (newInterval.first >= interval.first && newInterval.second <= interval.second)) {
                toMerge.emplace_back(interval);
            }
        }
        if (!toMerge.empty()) {
            long long maxLowerBound = newInterval.first;
            long long maxUpperBound = newInterval.second;
            for (const auto& interval : toMerge) {
                maxLowerBound = std::min(maxLowerBound, interval.first);
                maxUpperBound = std::max(maxUpperBound, interval.second);
                intervals.remove(interval);
            }
            intervals.emplace_back(maxLowerBound, maxUpperBound);
        }
        else
            intervals.emplace_back(newInterval);
    }
    ifile.close();
    long long numFreshIds = 0;
    for (auto const& interval : intervals)
        numFreshIds += ((interval.second-interval.first) + 1);
    std::cout << "Number of Fresh Ids: " << numFreshIds << std::endl;
    return 0;
}
