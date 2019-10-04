// 解説後
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int solve_E() {
  size_t N;
  std::string S;
  std::cin >> N >> S;

  // 共通文字列の最大長を求める
  size_t result = 0;  // 一致する部分文字列の最大長
  std::vector<size_t> z;  // [0, z[i])と[i, i+z[i])が一致している
  for (size_t l1 = 0; l1 < N - 1; ++l1) {
    // バッファをクリアする
    z.clear();
    z.resize(N - l1, 0);

    // Z-Algorithm
    size_t c = 0;  // [l1, l1+len)と[c, z[c])が一致している
    for (size_t i = 1; i < z.size(); ++i) {
      if (i + z[i - c] < c + z[c]) {
        // 一致を確認した範囲の中であれば、以前に計算した値を再利用できる
        z[i] = z[i - c];
      } else {
        // 一致を確認した範囲を外れる場合、改めて一致する部分を探す
        const size_t l2 = l1 + i;
        size_t len = 0;
        if (c + z[c] > i) len = c + z[c] - i;
        for (; l2 + len < N; ++len) {
          if (S[l1 + len] != S[l2 + len]) break;
        }
        z[i] = len;
        c = i;
      }
    }
    z[0] = z.size();

    for (size_t i = 0; i < z.size(); ++i) {
      result = std::max(result, std::min(i, z[i]));
    }
  }

  std::cout << result;
  return 0;
}
