//
// Created by 陈洋 on 24-11-1.
//

#ifndef CARLOS_H
#define CARLOS_H
#include <variant>
#include <memory>
#include <vector>
#include <glog/logging.h>

namespace carlos {
class Range;
class Array;

class Range {
 public:
  Range(const int start, const int end, const bool inclusive)
      : start(start), end(end), inclusive(inclusive) {}
  int start;
  int end;
  bool inclusive;
};
class Array {
 public:
  Array(const int size,
        std::vector<std::variant<std::nullptr_t, int, bool, char, float, Range,
                                 std::shared_ptr<Array>>>
            values)
      : size(size), values(std::move(values)) {}

  std::variant<std::nullptr_t, int, bool, char, float, Range,
               std::shared_ptr<Array>>
  get(const std::vector<int> &indices) {
    return get_inner(values, indices, 0);
  }

  void set(std::vector<int> &indices,
           const std::variant<std::nullptr_t, int, bool, char, float, Range,
                              std::shared_ptr<Array>> &value) {
    auto inner = &values;
    for (auto i = 0; i < indices.size() - 1; i++) {
      const auto idx = indices[i];

      if (const auto arr =
              std::get_if<std::shared_ptr<Array>>(&(*inner)[idx])) {
        inner = &(*arr)->values;
      } else {
        LOG(FATAL) << "Not an array";
        return;
      }
    }
    const auto idx = indices.back();

    (*inner)[idx] = value;
  }

  [[nodiscard]] std::vector<int> dimensions() {
    auto dims = std::vector<int>{};
    auto inner = &values;
    while (true) {
      dims.push_back(inner->size());
      if (const auto arr = std::get_if<std::shared_ptr<Array>>(&(*inner)[0])) {
        inner = &(*arr)->values;
      } else {
        break;
      }
    }
    return dims;
  }

  std::variant<std::nullptr_t, int, bool, char, float, Range,
               std::shared_ptr<Array>>
  basic_value() {
    const auto indices = std::vector(dimensions().size(), 0);
    return get(indices);
  }

  int size;

  std::vector<std::variant<std::nullptr_t, int, bool, char, float, Range,
                           std::shared_ptr<Array>>>
      values{};

 private:
  static std::variant<std::nullptr_t, int, bool, char, float, Range,
                      std::shared_ptr<Array>>
  get_inner(std::vector<std::variant<std::nullptr_t, int, bool, char, float,
                                     Range, std::shared_ptr<Array>>> &vals,
            const std::vector<int> &indices, const int index) {
    const auto idx = indices[index];

    if (index == indices.size() - 1) {
      return vals[idx];
    }
    if (const auto arr = std::get_if<std::shared_ptr<Array>>(&vals[idx])) {
      return get_inner((*arr)->values, indices, index + 1);
    }
    return {nullptr};
  }
};
}  // namespace carlos
#endif  // CARLOS_H
