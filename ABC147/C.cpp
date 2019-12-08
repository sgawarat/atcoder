// 解説前
#include <algorithm>
#include <iostream>
#include <vector>

// N<=15なので、2^N<4*10^4になる
// => すべてのパターンをチェックできそう

// N<=15なので、N*2^N<6*10^5になる
// => すべてのパターンにおいて、そのときの正直者の証言が正しいことを確認すればいい
int solve_C() {
  // 人数を読み取る
  size_t N = 0;
  std::cin >> N;

  // 証言を読み取る
  std::vector<uint16_t> ones(N);  // iの証言による正直者の人のビットセット
  std::vector<uint16_t> zeros(N);  // iの証言による不親切な人のビットセット
  for (size_t i = 0; i < N; ++i) {
    size_t A;
    std::cin >> A;
    for (size_t j = 0; j < A; ++j) {
      int x, y;
      std::cin >> x >> y;
      if (y == 1) {
        ones[i] |= size_t(1) << (x - 1);
      } else if (y == 0) {
        zeros[i] |= size_t(1) << (x - 1);
      }
    }
  }

  // 正直者の最大人数を計算する
  // stateは正直者である人のビットセット
  size_t result = 0;
  for (uint16_t state = 1; state < (1 << N); ++state) {
    [&] {
      // 各人の証言が正しいことを確認する
      size_t count = 0;
      for (size_t i = 0; i < N; ++i) {
        // iが正直者であれば、その発言が現在の状態と矛盾するかを調べる
        if (state & (1 << i)) {
          const uint16_t one = ones[i];
          const uint16_t zero = zeros[i];
          if ((state & one) != one || (~state & zero) != zero) {
            // 矛盾したので、この状態での人数は数えない
            return;
          }

          // 正直者の人数を数える
          count++;
        }
      }

      // 正直者の最大人数を計算する
      result = std::max(result, count);
    }();
  }

  // 結果発表
  std::cout << result;

  return 0;
}

int main() {
  return solve_C();
}
