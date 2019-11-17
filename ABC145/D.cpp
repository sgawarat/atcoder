// 解説前
#include <iostream>
#include <vector>
#include <cstdint>

// 剰余付き累乗を計算する
// 参考：https://stackoverflow.com/questions/8496182/calculating-powa-b-mod-n
template <typename T>
T pow(T x, T y, T m) noexcept {
  T r = 1;
  while (y > 0) {
    // 指数のiビット目を見て、xの2^i乗をかける
    if (y & 1) {
      r *= x;
      if (r >= m) r %= m;
    }

    // xの2^i乗を累積的に計算する
    x *= x;
    if (x >= m) x %= m;

    y >>= 1;
  }
  return r;
}

// 剰余付き組み合わせ数を計算する（pは素数）
// 参考：https://ikatakos.com/pot/programming_algorithm/number_theory/mod_combination
template <typename T>
T combination(T n, T r, T p) noexcept {
  // nCr = nC_{n-r}なので、計算量が少なくなる方を選ぶ
  if (r > n - r) r = n - r;
  
  // 分子（nPr mod p）を計算する
  T num = 1;
  for (T i = 0; i < r; ++i) {
    num *= n - i;
    if (num >= p) num %= p;
  }

  // 分母（r! mod p）を計算する
  T denom = 1;
  for (T i = 1; i <= r; ++i) {
    denom *= i;
    if (denom >= p) denom %= p;
  }

  // 分母の逆数（r!^{-1} mod p = r!^{p-2} mod p）を計算する
  // フェルマーの小定理から導かれる
  const T denom_inv = pow(denom, p - 2, p);

  // 組み合わせ数（nCr mod p）を計算する
  return (num * denom_inv) % p;
}

// L^1ノルムを考えると、(1,2)と(2,1)のどちらの方向でも距離3だけ移動する
// => 到達可能な地点までのL^1ノルムは3の倍数になる
// => 動かした回数はn=(X+Y)/3となる
// 
// すべての移動を(1,2)の方向に動かしたとすると、X=nとなる
// その状態からどこか1つを(2,1)の方向に動かすよう変えた場合、Xは+1だけ増える
// => (2,1)方向に動かした回数はX-nとなる
//
// 進む経路を図に起こすと、その個数はパスカルの三角形を描く
// => 動かす回数をn、(2,1)の方向に動かした回数をrとして、nCrを計算すれば良い 
int solve_D() {
  uint64_t X, Y;
  std::cin >> X >> Y;

  // 経路の数を計算する
  const auto distance = X + Y;  // L^1ノルム
  if (distance % 3 != 0) {
    // (X, Y)に到達できない場合
    std::cout << '0';
  } else {
    // (X, Y)に到達できる場合
	const auto n = distance / 3;  // 移動回数
	const auto r = X - n;  // (2,1)の方向に動かした回数

    // 組み合わせ数（nCr mod 10^9+7）を計算する
    const uint64_t m = 1'000'000'007;
    std::cout << combination(n, r, m);
  }
  return 0;
}

int main() {
  return solve_D();
}
