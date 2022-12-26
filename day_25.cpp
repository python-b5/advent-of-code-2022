// Advent of Code 2022
// Day 25: Full of Hot Air

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("inputs/day_25.txt");

    std::vector<int> digits;

    for (std::string line; std::getline(file, line);) {
        for (int i = line.length() - 1; i >= 0; --i) {
            int digit;

            if (line[i] == '-') {
                digit = -1;
            } else if (line[i] == '=') {
                digit = -2;
            } else {
                digit = line[i] - '0';
            }

            int digit_i = line.length() - 1 - i;

            if (digit_i >= digits.size()) {
                digits.push_back(digit);;
            } else {
                while (true) {
                    if (digit_i >= digits.size()) {
                        digits.push_back(0);
                    }

                    int added = digits[digit_i] + digit;

                    if (added > 2) {
                        digits[digit_i] = added - 5;
                        digit = 1;

                        ++digit_i;
                    } else if (added < -2) {
                        digits[digit_i] = 5 + added;
                        digit = -1;

                        ++digit_i;
                    } else {
                        digits[digit_i] = added;
                        break;
                    }
                }
            }
        }
    }

    while (!digits.empty() && digits.back() == 0) {
        digits.pop_back();
    }

    std::cout << "[PART 1] Sum: ";

    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] == -1) {
            std::cout << '-';
        } else if (digits[i] == -2) {
            std::cout << '=';
        } else {
            std::cout << digits[i];
        }
    }

    std::cout << "\n";
}