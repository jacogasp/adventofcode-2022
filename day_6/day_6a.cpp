#include <iostream>
#include <unordered_set>

int get_start_packet(const std::string &l, int window_size) {
  std::unordered_set<char> s{};
  for(auto it = l.begin() + window_size; it != l.end(); ++it) {
    for (auto kt = it - window_size; kt != it; ++kt) s.insert(*kt);  
    if (s.size() == window_size) return std::distance(l.begin(), it);
    s.clear();
  }
  return std::distance(l.begin(), l.end());
}

int main() {
  std::string l;
  std::getline(std::cin, l);
  int window_size = 4;
  int result = get_start_packet(l, window_size); 
  std::cout << result << std::endl;
  return 0;
}
