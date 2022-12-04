// Advent of Code 2022
// Day 4: Camp Cleanup

#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("inputs/day_4.txt");

    int containments = 0;
    int overlaps = 0;

    for (std::string line; std::getline(file, line);) {
        size_t comma = line.find_first_of(',');
        std::string group_1 = line.substr(0, comma);
        std::string group_2 = line.substr(comma + 1);

        size_t dash = group_1.find_first_of('-');
        int group_1_left = std::stoi(group_1.substr(0, dash));
        int group_1_right = std::stoi(group_1.substr(dash + 1));

        dash = group_2.find_first_of('-');
        int group_2_left = std::stoi(group_2.substr(0, dash));
        int group_2_right = std::stoi(group_2.substr(dash + 1));

        if (
            (group_1_left >= group_2_left && group_1_right <= group_2_right) ||
            (group_2_left >= group_1_left && group_2_right <= group_1_right)
        ) {
            ++containments;
        }

        if (group_1_left <= group_2_right && group_1_right >= group_2_left) {
            ++overlaps;
        }
    }

    std::cout << "[PART 1] Full containments: " << containments << "\n";
    std::cout << "[PART 2] Overlaps: " << overlaps << "\n";
}