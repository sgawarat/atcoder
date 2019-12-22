// 解説後
#include <iostream>

// 末尾の0の個数 = 10で割り切れる回数
//
// Nが奇数のとき、f(N)は10で割り切れないので、末尾の0の個数は0
//
// Nが偶数のとき、f(N) = \prod_{i=1}^{N/2}(2i)
// このとき、f(N)が2で割り切れる回数は十分に大きいので、
// f(N)が10で割り切れる回数はf(N)が5で割り切れる回数に等しい
//
// 5でn回だけ割り切れる値は{5,5^2,5^3,...,5^n}のすべてで割り切れる
// => {1,2,3,...,N/2}のうち5^iで割り切れる値の個数はN/2/5^i
// => f(N)が5で割り切れる回数はΣ(N/2/5^i)になる
int solve_E() {
  uint64_t N;
  std::cin >> N;

  if (N % 2 != 0) {
    std::cout << '0';
  } else {
    uint64_t result = 0;
    for (uint64_t i = 10; i <= N; i *= 5) {
      result += N / i;
    }
    std::cout << result;
  }

  return 0;
}

int main() { return solve_E(); }
