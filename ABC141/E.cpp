// 解説後
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int solve_E() {
  size_t N;  // 文字列の長さ
  std::string S;  // 文字列
  std::cin >> N >> S;

  // 一致する部分文字列の最大長を求める
  size_t result = 0;  // 一致する部分文字列の最大長
  std::vector<size_t> z;  // [0, z[i])と[i, i+z[i])が一致するときの長さ
  for (size_t l1 = 0; l1 < N - 1; ++l1) {
    // バッファをクリアする
    z.clear();
    z.resize(N - l1, 0);

    // Z-Algorithm
    size_t beg = 0, end = 0;  // [l1, l1+(end-beg))と一致する[beg, end)
    for (size_t i = 1; i < z.size(); ++i) {
      if (i + z[i - beg] < end) {
        // 一致を確認した範囲の中であれば、以前に計算した値を再利用できる
        z[i] = z[i - beg];
      } else {
        // 一致を確認した範囲を外れる場合、改めて一致する部分を探す
        const size_t l2 = l1 + i;
        size_t len = i < end ? (end - i) : 0;  // 一致することが分かっている部分を長さに含める
        for (; l2 + len < N; ++len) {
          if (S[l1 + len] != S[l2 + len]) break;
        }
        z[i] = len;
        beg = i;
        end = i + len;
      }

      // 文字列同士が重ならないような長さ（l2-l1=i）を考慮しつつ最大長を求める
      result = std::max(result, std::min(i, z[i]));
    }
  }

  // 結果発表
  std::cout << result;
  return 0;
}
