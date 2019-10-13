// 解説前
#include <iostream>

// $i = N$のとき、$M_N = N - 1$が最大値 ⇒ $P_i = N - 1$
// $i = N - 1$のとき、$M_{N-1} = N - 2$が最大値 ⇒ $P_i = N - 2$
// ...
// $i = 2$のとき、$M_2 = 1$が最大値 ⇒ $P_i = 1$
// $i = 1$のとき、$M_1 = 0$が最大値 ⇒ 何でも良いが、消去法で$P_i = N$
// したがって、$\sum_{i=1}^N M_i = \sum_{i=1}^{N-1} i = \frac{1}{2} N (N - 1)$
int solve_D() {
  size_t N = 0;
  std::cin >> N;

  std::cout << (N * (N - 1) / 2);
  return 0;
}
