#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using Vec2 = std::vector<std::vector<int>>;

int scenic_score(int x, int y, const Vec2 &m) {
    int z = m[y][x];
    int x_size = m.front().size();
    int y_size = m.size();

    int scenic_score = 0;
    int visible_trees = 0;

    // Left
    for (int i = x - 1; i >= 0; --i) {
        visible_trees++;
        if (m[y][i] >= z) break; 
    }
    scenic_score = visible_trees;
    visible_trees = 0;

    // Right
    for (int i = x + 1; i < x_size; ++i) {
        visible_trees++;
        if (m[y][i] >= z) break;
    }
    scenic_score *= visible_trees;
    visible_trees = 0;

    // Up
    for (int i = y - 1; i >= 0; --i) {
        visible_trees++;
        if (z <= m[i][x]) break;
    }
    scenic_score *= visible_trees;
    visible_trees = 0;

    // Down
    for (int i = y + 1; i < y_size; ++i) {
        visible_trees++;
        if (z <= m[i][x]) break;
    }
    scenic_score *= visible_trees;
    return scenic_score;
}

int main(int arc, char** argv) {
    Vec2 values;

    std::string line;
    std::ifstream file{argv[1]};
    
    while (std::getline(file, line)) {
        std::vector<int> v{};
        for (const char c : line) v.push_back((int)c - '0');
        values.push_back(v);
    }

    file.close();

    auto size_x = values.size();
    auto size_y = values.at(0).size();

    int max_scenic_score = 0;

    for (int x = 1; x < size_x - 1; ++x)
        for (int y = 1; y < size_y - 1; ++y)
            max_scenic_score = std::max(max_scenic_score, scenic_score(x, y, values));


    std::cout << "Max scenic score: " << max_scenic_score <<  std::endl;
    return 0;
}