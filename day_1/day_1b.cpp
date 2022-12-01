#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int main() {
  std::string s;
  std::vector<int> v;
  int x = 0;

  while(std::getline(std::cin, s)) {
    if (s.empty()) { 
      v.push_back(x);
      x = 0;
      continue; 
    }
    
    x += std::stoi(s);
  }

  std::sort(v.begin(), v.end(), [](auto a, auto b) { return a > b; });
  int total = 0;
  for (int i = 0; i < 3; i++) total += v.at(i);
  std::cout << total << std::endl;
  return 0;
}
