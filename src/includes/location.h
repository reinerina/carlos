//
// Created by 陈洋 on 24-10-16.
//

#ifndef LOCATION_H
#define LOCATION_H

namespace carlos {
struct Location {
  using position = std::size_t;
  position begin{};
  position end{};
  position current{};

  Location() = default;
  Location(const position begin, const position end) : begin(begin), end(end) {}
  friend std::ostream& operator<<(std::ostream& os, const Location& loc) {
    os << loc.begin << ":" << loc.end - loc.current;
    return os;
  }

  void next_word(const position length) {
    current = length;
    end += length;
  }

  void next_line(const position line_number) {
    begin = line_number;
    end = 1;
  }
};

}  // namespace carlos
#endif  // LOCATION_H
