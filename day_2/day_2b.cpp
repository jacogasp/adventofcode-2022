#include<iostream>
#include<string>

enum Rank {
  rock = 1,
  paper = 2,
  scissor = 3,
  unknown
};

enum Outcome { win, loose, draw };

std::ostream& operator<<(std::ostream &out, const Rank &r) {
  switch (r) {
    case rock: { out << "Rock"; break; }
    case paper: { out << "Paper"; break; }
    case scissor: { out << "Scissor"; break; }
    default: { out << "Unknown"; }
  }
  return out;
}

Rank get_rank(const char c) {
  Rank rank;
  switch (c) {
    case 'A': { rank = rock; break; }
    case 'B': { rank = paper; break; }
    case 'C': { rank = scissor; break; }
    default: { rank = unknown; break; } 
  }
  return rank;
}

Outcome get_outcome(const char c) {
  Outcome o;
  switch (c) {
    case 'X': { o = loose; break; }
    case 'Y': { o = draw; break; }
    default: { o = win; }
  }
  return o;
}

int play(const Outcome &outcome, const Rank &elf) {
  int score = 0;
  Rank player;

  switch (outcome) {
    case win: {
      if (elf == rock) player = paper;
      else if (elf == scissor) player = rock;
      else if (elf == paper) player = scissor;
      score = 6;
      break;
    }
    case loose: {
      if (elf == rock) player = scissor;
      else if (elf == scissor) player = paper;
      else if (elf == paper) player = rock;
      break;
    }
    default: {
      player = elf;
      score = 3;
      break;
    }
  }
  return score + static_cast<int>(player);
}

int main() {
  std::string s;
  int score = 0;

  while(std::getline(std::cin, s)) {
    Rank elf = get_rank(s[0]);
    Outcome outcome = get_outcome(s[2]);
    score += play(outcome, elf);
    // std::cout << "Elf: " << elf << ", player: " << player << std::endl;
  }
  std::cout << "Your score is: " << score << std::endl;
  return 0;
}
