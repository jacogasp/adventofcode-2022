#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

constexpr char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int get_priority(const char c) {
  int priority = 1 + static_cast<int>(c - 'a');
  if (priority < 0) priority += 58;
  return priority;
}

int main() {
  std::string line;
  int total_priority = 0;
  std::vector<std::string> lines;
  while(std::getline(std::cin, line)) lines.push_back(line);

  for (int i = 0; i < lines.size() ; i += 3) {
    std::string &l0 { lines.at(i) };
    std::string &l1 { lines.at(i + 1) };
    std::string &l2 { lines.at(i + 2) };
    
    for (auto c : characters) {
      auto r0 = std::find_if(l0.begin(), l0.end(), [c](char k) { return c == k; });
      auto r1 = std::find_if(l1.begin(), l1.end(), [c](char k) { return c == k; });
      auto r2 = std::find_if(l2.begin(), l2.end(), [c](char k) { return c == k; });
      if (r0 == l0.end() || r1 == l1.end() || r2 == l2.end()) continue;
      if (*r0 == *r1 && *r0 == *r2) { total_priority += get_priority(c); break; }
    }
  }
  
  std::cout << "Total priority: " << total_priority <<  std::endl;
  return 0;
}
