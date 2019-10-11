// 解説前
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int solve_F() {
  size_t N = 0;
  std::cin >> N;

  std::multiset<uint64_t> s;
  for (size_t i = 0; i < size_t(1) << N; ++i) {
    uint64_t S = 0;
    std::cin >> S;
    s.insert(S);
  }

  std::vector<uint64_t> healths;
  healths.reserve(1 << N);
  healths.push_back(*--s.end());
  s.erase(--s.end());
  for (size_t i = 0; i < N; ++i) {
    const size_t size = healths.size();
    healths.resize(size * 2);
    for (size_t j = 0; j < size; ++j) {
      auto iter = s.lower_bound(healths[j]);
      if (iter == s.begin()) {
        std::cout << "No";
        return 0;
      }
      healths[size + j] = *--iter;
      s.erase(iter);
    }
  }

  std::cout << "Yes";
  return 0;
}
