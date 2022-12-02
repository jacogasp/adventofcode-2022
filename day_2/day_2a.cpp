#include<iostream>
#include<string>

enum Rank {
  rock = 1,
  paper = 2,
  scissor = 3,
  unknown
};

std::ostream& operator<<(std::ostream &out, const Rank &r) {
  switch (r) {
    case rock: { out << "Rock"; break; }
    case paper: { out << "Paper"; break; }
    case scissor: { out << "Scissor"; break; }
    default: { out << "Unknown"; }
  }
  return out;
}

Rank&& get_rank(const char c) {
  Rank rank;
  switch (c) {
    case 'A': case 'X': { rank = rock; break; }
    case 'B': case 'Y': { rank = paper; break; }
    case 'C': case 'Z': { rank = scissor; break; }
    default: { rank = unknown; break; } 
  }
  return std::move(rank);
}

int play(const Rank &player, const Rank &elf) {
  int score = static_cast<int>(player);
  if (player == elf) return score + 3;
  
  if ((player == paper && elf == rock)   || 
      (player == rock && elf == scissor) || 
      (player == scissor && elf == paper))
    return score + 6;

  return score;
}

int main() {
  std::string s;
  Rank elf;
  Rank player;
  int score = 0;

  while(std::getline(std::cin, s)) {
    elf = get_rank(s[0]);
    player = get_rank(s[2]);
    score += play(player, elf);
    // std::cout << "Elf: " << elf << ", player: " << player << std::endl;
  }
  std::cout << "Your score is: " << score << std::endl;
  return 0;
}
