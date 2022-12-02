// Advent of Code 2022
// Day 2: Rock Paper Scissors

#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("inputs/day_2.txt");

    int score_part_1 = 0;
    int score_part_2 = 0;

    for (std::string line; std::getline(file, line);) {
        char first = line[0];
        char second = line[2];

        switch (second) {
            case 'X':
                score_part_1 += 1;

                switch (first) {
                    case 'A': score_part_2 += 3; break;
                    case 'B': score_part_2 += 1; break;
                    case 'C': score_part_2 += 2; break;
                }
            break;

            case 'Y':
                score_part_1 += 2;
                score_part_2 += 3;

                switch (first) {
                    case 'A': score_part_2 += 1; break;
                    case 'B': score_part_2 += 2; break;
                    case 'C': score_part_2 += 3; break;
                }
            break;

            case 'Z':
                score_part_1 += 3;
                score_part_2 += 6;

                switch (first) {
                    case 'A': score_part_2 += 2; break;
                    case 'B': score_part_2 += 3; break;
                    case 'C': score_part_2 += 1; break;
                }
            break;
        }

        if (
            (first == 'A' && second == 'X') ||
            (first == 'B' && second == 'Y') ||
            (first == 'C' && second == 'Z')
        ) {
            score_part_1 += 3;
        } else if (
            (first == 'A' && second == 'Y') ||
            (first == 'B' && second == 'Z') ||
            (first == 'C' && second == 'X')
        ) {
            score_part_1 += 6;
        }
    }

    std::cout << "[PART 1] Total score: " << score_part_1 << "\n";
    std::cout << "[PART 2] Total score: " << score_part_2 << "\n";
}