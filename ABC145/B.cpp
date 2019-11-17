// 本戦
#include <iostream>
#include <string>

int main() {
  int N;
  std::string S;
  std::cin >> N >> S;

  if (N % 2 != 0) {
    // 奇数の場合
    std::cout << "No";
  } else {
    // 偶数の場合
    const int m = N / 2;
    for (int i = 0; i < m; ++i) {
      if (S[i] != S[m + i]) {
        std::cout << "No";
        return 0;
      }
    }
    std::cout << "Yes";
  }
  
  return 0;
}
