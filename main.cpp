#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

typedef struct point {
    int x;
    int y;
} point;

int parse_mem_index(int x, int y, int const width) {
    return x + y * width;
}

std::vector<int> effect_point(int x, int y, int width, int height) {
    std::vector<int> area;
    std::vector<point> targets;
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1) return area;
    targets.push_back((point){x, y});
    if (x - 1 >= 0) targets.push_back((point){x-1, y});
    if (x + 1 <= width -1) targets.push_back((point){x+1, y});
    if (y - 1 >= 0) targets.push_back((point){x, y-1});
    if (y + 1 <= height -1)  targets.push_back((point){x, y+1});

    int min = 0;
    int max = width * height - 1;
    for (int i = 0; i < targets.size(); i++) {
        int index = parse_mem_index(targets[i].x, targets[i].y, width);
        if (index >= min && index <= max) {
            area.push_back(index);
        }
    }
    return area;
}

void dump_area(std::vector<char> const& area, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", area[j + i * width]);
        } printf("\n");
    }
}

void next(int x, int y, int width, int height, std::vector<char>& area) {
    std::vector<int> points = effect_point(x, y, width, height);
    for (int i = 0; i < points.size(); i++) {
        area[points[i]] = !area[points[i]];
    }
}

struct point user_input() {
    std::string line;
    printf("next point(X Y): ");
    std::getline(std::cin, line, ' ');
    struct point p;
    p.x = std::stoi(line);
    std::getline(std::cin, line);
    p.y = std::stoi(line);
    return p;
}

int main(int argc, char* argv[]) {
    std::ifstream file("input.txt");
    std::stringstream ss;

    ss << file.rdbuf();

    std::string line;
    int width;
    int height;

    std::getline(ss, line, ' ');
    height = std::stoi(line);
    std::getline(ss, line);
    width = std::stoi(line);

    // init area
    std::vector<char> area;
    area.resize(width * height);

    int current_line = 0;
    while (true) {
        std::istream& is = std::getline(ss, line);
        if (!is) break;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] != '_')
                area[i + current_line * line.length()] = 1;
        }
        current_line++;
    }

    while (true) {
        dump_area(area, width, height);
        printf("\n");
        struct point p = user_input();
        next(p.x, p.y, width, height, area);
    }

    return 0;
}
