// Advent of Code 2022
// Day 10: Cathode-Ray Tube

#include <fstream>
#include <iostream>
#include <string>

#include <cstdlib>

int main() {
    std::ifstream file("inputs/day_10.txt");

    int X = 1;
    int strength_sum = 0;

    int pixel = 0;
    std::string image;

    int cycle = 1;
    for (std::string line; std::getline(file, line);) {
        std::string instruction = line.substr(0, 4);

        for (int i = 0; i <= (instruction == "addx") ? 1 : 0; ++i) {
            if (
                cycle == 20 || cycle == 60 || cycle == 100 ||
                cycle == 140 || cycle == 180 || cycle == 220
            ) {
                strength_sum += cycle * X;
            }

            if (std::abs(pixel - X) <= 1) {
                image += "#";
            } else {
                image += ".";
            }

            ++pixel;

            if (pixel == 40) {
                image += "\n                         ";
                pixel = 0;
            }

            ++cycle;
        }

        if (instruction == "addx") {
            X += std::stod(line.substr(5));
        }
    }

    std::cout << "[PART 1] Sum of signal strengths: " << strength_sum << "\n";
    std::cout << "[PART 2] Rendered image: " << image.substr(0, 371);
}