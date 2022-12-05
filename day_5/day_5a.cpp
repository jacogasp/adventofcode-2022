#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>


using Stack = std::stack<char>;
using stacks_t = std::vector<Stack>;
using lines_t = std::vector<std::string>;

struct Instruction {  
  int n, from, to;
  Instruction(int N, int from_, int to_) : n{N}, from{from_ - 1}, to{to_ - 1} {};
};

using instructions_t = std::vector<Instruction>;

stacks_t parse_header(const lines_t &h) {
  std::stringstream s;
  s << h.back();
  
  std::string t;
  std::vector<std::string> tokens;
  while (std::getline(s, t, ' ')) tokens.push_back(t);

  int n_stacks = std::stoi(tokens.back()); 
  stacks_t stacks;
  stacks.resize(n_stacks);

  for (int i = h.size() - 2; i >= 0; --i) {
    auto &line = h.at(i);
    for (int j = 0; j <  n_stacks; ++j) {
      char c {line.at(j * 4 + 1)};
      if (c != ' ') stacks.at(j).push(c);
    }
  }
 return stacks; 
}

instructions_t parse_body(const lines_t &lines) {
  instructions_t ins;
  int n, from, to;
  for (auto &l : lines) {
    std::sscanf(l.c_str(), "move %d from %d to %d", &n, &from, &to);
    ins.emplace_back(n, from, to);
  }
  return ins;
}


int main() {
  std::string line;
  std::vector<std::string> header;
  std::vector<std::string> body;
  bool read_header = true;

  while(std::getline(std::cin, line)) {
    if (line.empty()) { read_header = false; continue; }
    if (read_header) header.push_back(line);
    else body.push_back(line);
  }
  auto stacks = parse_header(header);
  auto instructions = parse_body(body);

  std::cout << "Number of stacks: " << stacks.size() << std::endl;
  std::cout << "Number of instructions: " << instructions.size() << std::endl;
  
  for (auto &instruction : instructions) {
    for (int k = 0; k < instruction.n; ++k) {
      auto &from = stacks.at(instruction.from);
      auto &to = stacks.at(instruction.to);
      auto el = from.top();
      to.push(std::move(el));
      from.pop();
    }
  }

  for (auto &stack : stacks) std::cout << stack.top();
  std::cout << std::endl;
  
  return 0;
}
