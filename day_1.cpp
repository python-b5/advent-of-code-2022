// Advent of Code 2022
// Day 1: Calorie Counting

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("inputs/day_1.txt");

    std::vector<int> calorie_counts;

    int current_calories = 0;
    for (std::string line; std::getline(file, line);) {
        if (line.empty()) {
            calorie_counts.push_back(current_calories);
            current_calories = 0;
        } else {
            current_calories += std::stoi(line);
        }
    }

    int first = 0;
    int second = 0;
    int third = 0;

    for (int calories : calorie_counts) {
        if (calories > first) {
            third = second;
            second = first;
            first = calories;
        } else if (calories > second) {
            third = second;
            second = calories;
        } else if (calories > third) {
            third = calories;
        }
    }

    std::cout << "[PART 1] Largest amount of Calories: " << first << "\n";
    std::cout << "[PART 2] Sum of top 3: " << first + second + third << "\n";
}