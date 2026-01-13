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
        ranges.emplace_back(lower, upper);
    }
    ifile.close();
    unsigned long long invalidIdSum = 0;
    for (const auto& rp : ranges) {
        const unsigned long long lowerVal = std::stoull(rp.first);
        const unsigned long long upperVal = std::stoull(rp.second);
        const unsigned int lowerWidth = rp.first.size();
        const unsigned int upperWidth = rp.second.size();
        for (unsigned long long v = lowerVal; v <= upperVal; v++) {
            const std::string vString = std::to_string(v);
            bool isInvalid = false;
            for (unsigned int chunkSize = 1; chunkSize <= vString.size()/2; chunkSize++) {
                if (vString.size() % chunkSize != 0) continue;
                unsigned int numChunks = vString.size() / chunkSize;
                const std::string chunk = vString.substr(0, chunkSize);
                std::string repeatChunkString; repeatChunkString.reserve(chunk.size() * numChunks);
                for (unsigned int c=0; c<numChunks; c++)
                    repeatChunkString += chunk;
                if (repeatChunkString == vString)
                    isInvalid = true;
            }
            if (isInvalid)
                invalidIdSum += v;
        }
    }
    std::cout << "Invalid ID Total: " << invalidIdSum << std::endl;
    return 0;
}
