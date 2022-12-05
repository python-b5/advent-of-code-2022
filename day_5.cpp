// Advent of Code 2022
// Day 5: Supply Stacks

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>
#include <sstream>
#include <utility>
#include <vector>
#include <string>

#include <cctype>

enum ParsingMode {
    STACKS,
    INSTRUCTIONS
};

int main() {
    std::ifstream file("inputs/day_5.txt");

    std::stack<std::string> stack_lines;

    std::vector<std::stack<char>> stacks_1;
    std::vector<std::stack<char>> stacks_2;

    ParsingMode mode = STACKS;
    for (std::string line; std::getline(file, line);) {
        switch (mode) {
            case STACKS:
                if (isdigit(line[1])) {
                    line.erase(
                        std::remove(line.begin(), line.end(), ' '),
                        line.end()
                    );

                    size_t stacks_count = line.size();
                    for (size_t i = 0; i < stacks_count; ++i) {
                        stacks_1.push_back(std::stack<char>());
                    }

                    while (!stack_lines.empty()) {
                        std::string stack_line = stack_lines.top();
                        stack_lines.pop();

                        size_t size = stack_line.size();
                        for (size_t i = 0; i < size; ++i) {
                            if (stack_line[i] != ' ' && (i + 3) % 4 == 0) {
                                stacks_1[(i + 3) / 4 - 1].push(stack_line[i]);
                            }
                        }
                    }

                    stacks_2 = stacks_1;
                    mode = INSTRUCTIONS;
                } else {
                    stack_lines.push(line);
                }
            break;

            case INSTRUCTIONS:
                if (line.empty()) {
                    continue;
                }

                line.erase(
                    std::remove_if(
                        line.begin(),
                        line.end(),
                        static_cast<int (*)(int)>(std::isalpha)
                    ),
                    line.end()
                );

                std::istringstream stream(line);
                int parts[3];

                for (size_t i = 0; stream.good(); ++i) {
                    stream >> parts[i];
                }

                std::stack<char> group;

                for (size_t i = 0; i < parts[0]; ++i) {
                    stacks_1[parts[2] - 1].push(stacks_1[parts[1] - 1].top());
                    stacks_1[parts[1] - 1].pop();

                    group.push(stacks_2[parts[1] - 1].top());
                    stacks_2[parts[1] - 1].pop();
                }

                while (!group.empty()) {
                    stacks_2[parts[2] - 1].push(group.top());
                    group.pop();
                }
            break;
        }
    }

    std::cout << "[PART 1] Crates on top of each stack: ";

    for (std::stack<char> &stack : stacks_1) {
        std::cout << stack.top() << "";
    }

    std::cout << "\n[PART 2] Crates on top of each stack: ";

    for (std::stack<char> &stack : stacks_2) {
        std::cout << stack.top() << "";
    }

    std::cout << "\n";
}