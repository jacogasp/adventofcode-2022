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

  // for (auto z : v) std::cout << z << std::endl;
  auto result = std::max_element(v.begin(), v.end());

  std::cout << std::distance(v.begin(), result) << ' ' << *result  << std::endl;  
  return 0;
}
