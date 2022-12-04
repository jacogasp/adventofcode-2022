#include <iostream>

struct Range {
  int min;
  int max;
};

std::ostream & operator<<(std::ostream &out, const Range &r) {
  return out << '[' << r.min << ", " << r.max << ']';
}


Range get_range(const std::string &s) {
  Range r;
  auto delimiter = s.find('-');
  r.min = std::stoi(s.substr(0, delimiter));
  r.max = std::stoi(s.substr(delimiter + 1));
  return r;
}

int main() {
  std::string s;
  int counts = 0;
  while (std::getline(std::cin, s)) {
      auto found = s.find(',');
      std::string left_s = s.substr(0, found);
      std::string right_s = s.substr(found + 1);

      Range range_l = get_range(left_s);
      Range range_r = get_range(right_s);
      std::cout << range_l << ' ' << range_r << std::endl;

      if (!(range_l.max < range_r.min || range_l.min > range_r.max)) counts++;
  }
  std::cout << "Counts: " << counts << std::endl;
  return 0;
}
