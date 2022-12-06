// Advent of Code 2022
// Day 6: Tuning Trouble

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("inputs/day_6.txt");

    std::vector<char> buffer;

    size_t chars_part_1 = 0;
    size_t chars_part_2 = 0;

    size_t i = 1;
    for (char ch; file >> ch;) {
        if (std::find(buffer.begin(), buffer.end(), ch) != buffer.end()) {
            buffer.clear();
        }

        buffer.push_back(ch);

        size_t size = buffer.size();
        if (size == 14) {
            chars_part_2 = i;
        } else if (chars_part_1 == 0 && size == 4) {
            chars_part_1 = i;
        }

        if (chars_part_1 != 0 && chars_part_2 != 0) {
            break;
        }

        ++i;
    }

    std::cout << "[PART 1] Characters until packet: " << chars_part_1 << "\n";
    std::cout << "[PART 2] Characters until packet: " << chars_part_2 << "\n";
}