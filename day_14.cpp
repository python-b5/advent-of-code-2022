// Advent of Code 2022
// Day 14: Regolith Reservoir

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <utility>

int simulate(
    int part,
    int start_x,
    int start_y,
    std::set<std::pair<int, int>> blocked,
    int max_y
) {
    int sand_x = start_x;
    int sand_y = start_y;

    int sand_count = 1;
    while (true) {
        bool above_floor = sand_y + 1 <= max_y + 1;

        if (
            above_floor &&
            blocked.find(std::make_pair(sand_x, sand_y + 1)) == blocked.end()
        ) {
            ++sand_y;
        } else if (
            above_floor &&
            blocked.find(
                std::make_pair(sand_x - 1, sand_y + 1)
            ) == blocked.end()
        ) {
            --sand_x;
            ++sand_y;
        } else if (
            above_floor &&
            blocked.find(
                std::make_pair(sand_x + 1, sand_y + 1)
            ) == blocked.end()
        ) {
            ++sand_x;
            ++sand_y;
        } else {
            if (part == 1 && sand_y > max_y) {
                return sand_count - 1;
            }

            if (part == 2 && sand_x == start_x && sand_y == start_y) {
                return sand_count;
            }

            blocked.insert(std::make_pair(sand_x, sand_y));
            ++sand_count;

            sand_x = start_x;
            sand_y = start_y;
        }
    }
}

int main() {
    std::ifstream file("inputs/day_14.txt");

    std::set<std::pair<int, int>> blocked;
    int max_y = -1;

    for (std::string line; std::getline(file, line);) {
        std::replace(line.begin(), line.end(), '-', ' ');
        std::replace(line.begin(), line.end(), '>', ' ');

        int current_x;
        int current_y;

        std::istringstream stream(line);
        bool first = true;

        for (std::string coords; stream >> coords;) {
            size_t comma = coords.find_first_of(',');

            int end_x = std::stoi(coords.substr(0, comma));
            int end_y = std::stoi(coords.substr(comma + 1));

            if (end_y > max_y) {
                max_y = end_y;
            }

            if (first) {
                blocked.insert(std::make_pair(end_x, end_y));
                first = false;
            } else {
                bool horizontal = (end_x - current_x != 0);
                int &end = horizontal ? end_x : end_y;
                int &current = horizontal ? current_x : current_y;

                int sign = (end - current > 0) ? 1 : -1;
                for (current += sign;; current += sign) {
                    blocked.insert(std::make_pair(current_x, current_y));

                    if (current == end) {
                        break;
                    }
                }
            }

            current_x = end_x;
            current_y = end_y;
        }
    }

    std::cout << "[PART 1] Units of sand: "
              << simulate(1, 500, 0, blocked, max_y)
              << "\n";

    std::cout << "[PART 2] Units of sand: "
              << simulate(2, 500, 0, blocked, max_y)
              << "\n";
}