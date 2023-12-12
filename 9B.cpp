#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<int> parse_line(std::string line) {
    std::stringstream str(line);
    std::vector<int> nums;

    int k;
    while (str) {
        str >> k;

        if(str) nums.push_back(k);
    }

    return nums;
}

bool all_zero(std::vector<int> v) {
    for (auto i : v) {
        if (i != 0) return false;
    }

    return true;
}

int main() {
    std::ifstream input_file;
    input_file.open("input/9.txt");

    int next_sum = 0;

    while (input_file) {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) break;

        auto nums = parse_line(line);

        std::vector<std::vector<int>> diffs{nums};

        while ( !all_zero(diffs.back()) ) {
            std::vector<int> df;
            for (int i=0; i<diffs.back().size()-1; i++) {
                df.push_back(diffs.back()[i+1] - diffs.back()[i]);
            }

            diffs.push_back(df);
        }

        int left = 0;
        for (int i = diffs.size() - 2; i >= 0; i--) {
            int last = diffs[i].size() - 1;

            left = diffs[i][0] - left;
        }

        next_sum += left;
    }

    std::cout << next_sum << std::endl;
}
