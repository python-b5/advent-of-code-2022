// Advent of Code 2022
// Day 9: Rope Bridge

#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include <cstdlib>

int main() {
    std::ifstream file("inputs/day_9.txt");

    std::pair<int, int> knots[10];
    for (size_t i = 0; i < 10; ++i) {
        knots[i] = std::make_pair(0, 0);
    }

    std::set<std::pair<int, int>> tail_positions_part_1;
    std::set<std::pair<int, int>> tail_positions_part_2;

    for (std::string line; std::getline(file, line);) {
        int &head_axis = (line[0] == 'R' || line[0] == 'L') ?
                         knots[0].first : knots[0].second;

        int amount = std::stoi(line.substr(2));
        int sign = (line[0] == 'R' || line[0] == 'D') ? 1 : -1;

        for (int step = 0; step < amount; ++step) {
            head_axis += sign;

            for (size_t i = 1; i < 10; ++i) {
                std::pair<int, int> &knot = knots[i];
                std::pair<int, int> &parent = knots[i - 1];

                int x_diff = parent.first - knot.first;
                int y_diff = parent.second - knot.second;

                if (std::abs(x_diff) == 2 || std::abs(y_diff) == 2) {
                    knot.first += (x_diff > 0) ? 1 : ((x_diff < 0) ? -1 : 0);
                    knot.second += (y_diff > 0) ? 1 : ((y_diff < 0) ? -1 : 0);
                }
            }

            tail_positions_part_1.insert(knots[1]);
            tail_positions_part_2.insert(knots[9]);
        }
    }

    std::cout << "[PART 1] Positions visited by tail: "
              << tail_positions_part_1.size()
              << "\n";

    std::cout << "[PART 2] Positions visited by tail: "
              << tail_positions_part_2.size()
              << "\n";
}