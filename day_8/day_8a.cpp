#include <iostream>
#include <vector>
#include <cstdio>

using Vec2 = std::vector<std::vector<int>>;

bool is_visible(int x, int y, const Vec2 &m) {
    int z = m[x][y];
    int x_size = m.size();
    int y_size = m.front().size();

    int flg_hidden = 0;

    for (int i = 0; i < x; ++i) if (m[i][y] >= z) { flg_hidden |= 1; break; }           // Left
    for (int i = x + 1; i < x_size; ++i) if (m[i][y] >= z) { flg_hidden |= 2; break; }  // Right
    for (int i = 0; i < y; ++i) if (m[x][i] >= z) { flg_hidden |= 4; break; }           // Up
    for (int i = y + 1; i < y_size; ++i) if (m[x][i] >= z) { flg_hidden |= 8; break; }  // Down
    
    return flg_hidden != 15;
}

int main() {
    Vec2 values;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> v{};
        for (const char c : line) v.push_back((int)c - '0');
        values.push_back(v);
    }

    auto size_x = values.size();
    auto size_y = values.at(0).size();

    printf("Grid size: (%zu, %zu)\n", size_x, size_y);
    int count = 2 * (size_x + size_y) - 4;

    for (int x = 1; x < size_x - 1; ++x)
        for (int y = 1; y < size_y - 1; ++y) {
            if (is_visible(x, y, values)) count++;
        }


    std::cout << "\n# visible trees: " << count << std::endl;
    return 0;
}