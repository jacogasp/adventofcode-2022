#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int get_priority(const char c) {
  int priority = 1 + static_cast<int>(c - 'a');
  if (priority < 0) priority += 58;
  return priority;
}

int main() {
  std::string line;
  int total_priority = 0;
  while(std::getline(std::cin, line)) {
    auto start = line.begin();
    auto middle = line.begin() + line.size() / 2; 
    for (auto it = start; it != middle; it++) {
      auto result = std::find_if(middle, line.end(), [it](char c) { return *it == c; });
      if (result != line.end()) { total_priority += get_priority(*result); break; }
    }
  }
  std::cout << "Total priority: " << total_priority <<  std::endl;
  return 0;
}
