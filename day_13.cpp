// Advent of Code 2022
// Day 13: Distress Signal

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

const std::regex NUMBER_REGEX(R"(\s?[0-9]+\s?)");

enum Comparison {
    CORRECT,
    INCORRECT,
    UNDECIDED   
};

struct Packet {
    int value = -1;
    std::vector<Packet> contained_packets;

    bool operator==(const Packet &other) {
        return get_str() == other.get_str();
    }

    bool has_children() {
        return !contained_packets.empty();
    }

    std::string get_str() const {
        std::string str;

        if (contained_packets.empty()) {
            str += std::to_string(value) + ",";
        } else {
            for (const Packet &packet : contained_packets) {
                str += "[" + packet.get_str() + "],";
            }
        }

        return str;
    }
};

Packet parse_packet(std::string str) {
    if (str[0] == '[') {
        str.erase(0, 1);
    }

    if (str.back() == ']') {
        str.erase(str.size() - 1, 1);
    }

    Packet packet;

    if (std::regex_match(str, NUMBER_REGEX)) {
        packet.value = std::stoi(str);
    } else if (!str.empty()) {
        std::vector<std::string> values;

        std::string current_value;
        int depth = 0;

        for (char ch : str) {
            if (ch == '[') {
                ++depth;
            } else if (ch == ']') {
                --depth;
            }
            
            if (depth == 0 && ch == ',') {
                values.push_back(current_value);
                current_value.clear();
            } else {
                current_value += ch;
            }
        }

        values.push_back(current_value);

        for (std::string value : values) {
            packet.contained_packets.push_back(parse_packet(value));
        }
    }

    return packet;
}

Comparison compare(Packet &left, Packet &right) {
    bool left_children = left.has_children() || left.value == -1;
    bool right_children = right.has_children() || right.value == -1;
    
    if (left_children && right_children) {
        size_t left_size = left.contained_packets.size();
        size_t right_size = right.contained_packets.size();

        size_t min_size = std::min(left_size, right_size);
        for (size_t i = 0; i < min_size; ++i) {
            Comparison comparison = compare(
                left.contained_packets[i],
                right.contained_packets[i]
            );

            if (comparison != UNDECIDED) {
                return comparison;
            }
        }

        if (left_size < right_size) {
            return CORRECT;
        } else if (left_size > right_size) {
            return INCORRECT;
        } else {
            return UNDECIDED;
        }
    } if (!left_children && !right_children) {
        if (left.value < right.value) {
            return CORRECT;
        } else if (left.value > right.value) {
            return INCORRECT;
        } else {
            return UNDECIDED;
        }
    } else if (left_children) {
        Packet new_right;
        new_right.contained_packets.push_back(right);

        return compare(left, new_right);
    } else {
        Packet new_left;
        new_left.contained_packets.push_back(left);

        return compare(new_left, right);
    }
}

int main() {
    std::ifstream file("inputs/day_13.txt");

    std::vector<std::pair<Packet, Packet>> pairs;
    std::vector<Packet> packets;

    int i = 0;
    for (std::string line; std::getline(file, line); i = (i + 1) % 3) {
        if (i == 0) {
            pairs.push_back(std::pair<Packet, Packet>());
        }

        if (i != 2) {
            std::pair<Packet, Packet> &pair = pairs.back();
            Packet &packet = (i == 0) ? pair.first : pair.second;

            packet = parse_packet(line);
            packets.push_back(packet);
        }
    }

    int correct_pairs = 0;

    for (size_t i = 0; i < pairs.size(); ++i) {
        if (compare(pairs[i].first, pairs[i].second) == CORRECT) {
            correct_pairs += i + 1;
        }
    }

    Packet divider_1 = parse_packet("[[2]]");
    Packet divider_2 = parse_packet("[[6]]");

    packets.push_back(divider_1);
    packets.push_back(divider_2);

    std::sort(
        packets.begin(),
        packets.end(),
        [](Packet &left, Packet &right) -> bool {
            return compare(left, right) == CORRECT;
        }
    );

    std::cout << "[PART 1] Correct pairs: " << correct_pairs << "\n";

    std::cout << "[PART 2] Decoder key: "
              << (std::distance(
                     packets.begin(),
                     std::find(packets.begin(), packets.end(), divider_1)
                 ) + 1) *
                 (std::distance(
                     packets.begin(),
                     std::find(packets.begin(), packets.end(), divider_2)
                 ) + 1)
              << "\n";
}