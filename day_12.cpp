// Advent of Code 2022
// Day 12: Hill Climbing Algorithm

#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

enum Direction {
    RIGHT,
    UP,
    LEFT,
    DOWN
};

struct Node {
    size_t x;
    size_t y;
    int steps;

    Node(size_t x_, size_t y_, int steps_) {
        x = x_;
        y = y_;
        steps = steps_;
    }
};

int pathfind(
    std::vector<std::vector<char>> &map,
    size_t start_x,
    size_t start_y,
    std::function<bool(size_t, size_t, char)> end,
    std::function<bool(char, char)> valid_move
) {
    std::queue<Node> queue;
    queue.push(Node(start_x, start_y, 0));

    int width = map[0].size();
    int height = map.size();

    bool seen[height][width];

    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            seen[y][x] = false;
        }
    }

    seen[start_y][start_x] = true;

    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        if (end(current.x, current.y, map[current.y][current.x])) {
            return current.steps;
        }

        for (int dir = RIGHT; dir <= DOWN; ++dir) {
            size_t new_x = current.x;
            size_t new_y = current.y;

            switch (dir) {
                case RIGHT: ++new_x; break;
                case UP: --new_y; break;
                case LEFT: --new_x; break;
                case DOWN: ++new_y; break;
            }

            if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
                continue;
            }

            if (
                !seen[new_y][new_x] &&
                valid_move(map[current.y][current.x], map[new_y][new_x])
            ) {
                queue.push(Node(new_x, new_y, current.steps + 1));
                seen[new_y][new_x] = true;
            }
        }
    }

    return -1;
}

int main() {
    std::ifstream file("inputs/day_12.txt");

    std::vector<std::vector<char>> map;
    
    size_t start_x;
    size_t start_y;

    size_t end_x;
    size_t end_y;

    size_t y = 0;
    for (std::string line; std::getline(file, line); ++y) {
        std::vector<char> row;

        for (size_t x = 0; x < line.size(); ++x) {
            if (line[x] == 'S' || line[x] == 'A') {
                row.push_back('a');

                start_x = x;
                start_y = y;
            } else if (line[x] == 'E') {
                row.push_back('z');

                end_x = x;
                end_y = y;
            } else {
                row.push_back(line[x]);
            }
        }

        map.push_back(row);
    }

    std::cout << "[PART 1] Fewest steps: "
              << pathfind(
                     map,
                     start_x,
                     start_y,
                     [end_x, end_y](size_t x, size_t y, char ch) -> bool {
                         return x == end_x && y == end_y;
                     },
                     [](char current, char next) -> bool {
                        return next <= current + 1;
                     }
              )
              << "\n";

    std::cout << "[PART 2] Fewest steps: "
              << pathfind(
                     map,
                     end_x,
                     end_y,
                     [](size_t x, size_t y, char ch) -> bool {
                         return ch == 'a';
                     },
                     [](char current, char next) -> bool {
                        return current <= next + 1;
                     }
              )
              << "\n";
}