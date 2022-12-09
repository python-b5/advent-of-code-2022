// Advent of Code 2022
// Day 8: Treetop Tree House

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Direction {
    RIGHT,
    UP,
    LEFT,
    DOWN
};

int main() {
    std::ifstream file("inputs/day_8.txt");

    std::vector<std::vector<int>> map;

    for (std::string line; std::getline(file, line);) {
        std::vector<int> row;

        for (char ch : line) {
            row.push_back(ch - '0');
        }

        map.push_back(row);
    }

    size_t width = map[0].size();
    size_t height = map.size();

    int visible_trees = width * 2 + height * 2 - 4;
    int highest_scenic_score = 0;

    for (size_t x = 1; x < width - 1; ++x) {
        for (size_t y = 1; y < height - 1; ++y) {
            bool visible_trees_increased = false;
            int scenic_score = 1;

            for (int dir = RIGHT; dir <= DOWN; ++dir) {
                size_t check_x = x;
                size_t check_y = y;

                bool horizontal = (dir == RIGHT || dir == LEFT);
                size_t &axis = horizontal ? check_x : check_y;
                size_t &size = horizontal ? width : height;
                int sign = (dir == RIGHT || dir == DOWN) ? 1 : -1;

                bool blocked = false;
                int view_distance = 0;

                for (axis += sign; axis < size; axis += sign) {
                    ++view_distance;

                    if (map[check_y][check_x] >= map[y][x]) {
                        blocked = true;
                        break;
                    }

                    if (axis == 0 && sign == -1) {
                        break;
                    }
                }

                if (!visible_trees_increased && !blocked) {
                    ++visible_trees;
                    visible_trees_increased = true;
                }

                scenic_score *= view_distance;
            }

            if (scenic_score > highest_scenic_score) {
                highest_scenic_score = scenic_score;
            }
        }
    }

    std::cout << "[PART 1] Visible trees from outside: " << visible_trees << "\n";
    std::cout << "[PART 2] Highest scenic score: " << highest_scenic_score << "\n";
}
