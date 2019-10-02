#include <iostream>

// 本戦
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
// int main() {
//  int A, B;
//  std::cin >> A >> B;
//
//  const int N = std::min(A, B);
//  std::vector<> tbl(N);
//
//  return 0;
//}

// 解説後
#include <iostream>

// 最大公約数を求める
template <typename T>
inline T gcd(T a, T b) noexcept {
  if (a < b) std::swap(a, b);
  while (b > 0) {
    const T tmp = a % b;
    a = b;
    b = tmp;
  }
  return a;
}

// 公約数は最大公約数の素因数から組み合わせられる値である。（gcd = 2^a * 3^b * 5^c * ...）
// 選ばれる約数は他すべてと互いに素となるので、素因数が重複する値は選べない。（2を選ぶと4や6は選べなくなる）
// 問題とされるのは最大の個数なので、素因数をひとつだけ持つ値を選ぶと良い。（6を選ぶより2と3を選ぶほうが個数が多い）
// ⇒最大公約数の素因数の数を数えれば良い。
//
// Tips:
// - mから素因数由来の要素を取り除くことでループ回数を最適化する
// - AとBは10^12>2^32なので64ビット整数を使う
// - mに素因数iが含まれているかはループの条件式をi^2<=mとして調べれば良い
//   - mに素因数が2つ以上含まれている場合、mはi^2より大きいので、確実に処理できる
//   - mに素因数が1つだけ含まれている場合、
//     - それが二乗以上ならば、mはi^2以上なので、確実に処理できる
//     - そうでなくても、そのmはsqrt(m)以下のiで割り切れないことから素数であることがわかる
int solve_D() {
  uint64_t A, B;
  std::cin >> A >> B;

  // 最大公約数を求める
  uint64_t m = gcd(A, B);

  // 最大公約数の素因数の個数を数える
  if (m == 1) {
    // AとBが互いに素であれば、公約数は1だけしかない
    std::cout << '1';
  } else {
    // 最終的なmが素数であることを判定したいので、i^2<=mを条件として繰り返す
    uint64_t result = 1;  // 1はかならず選ばれるのであらかじめ計上する
    for (uint64_t i = 2; i * i <= m; ++i) {
      // 素因数かどうかを調べる
      if (m % i == 0) {
        result++;

        // mからiの累乗を取り除く
        do {
          m /= i;
        } while (m % i == 0);

        // すべての素因数を取り除いたら終了
        if (m == 1) break;
      }
    }

    // 処理しきれなかった素因数を計上する
    if (m > 1) result++;

    // 結果発表
    std::cout << result;
  }

  return 0;
}
