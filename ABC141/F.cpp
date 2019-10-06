// 解説後
#include <algorithm>
#include <iostream>
#include <vector>

// 最大のXORサブセットを返す関数
// from https://www.geeksforgeeks.org/find-maximum-subset-xor-given-set/
uint64_t max_subarray_xor(uint64_t* p, size_t n) noexcept {
  const size_t BITS = 60;  // 値のビット数

  // 最上位ビットから順に要素を調べる
  size_t index = 0;  // 入れ替える最大要素の終端
  for (uint64_t mask = uint64_t(1) << (BITS - 1); mask > 0; mask >>= 1) {
    // iビット目が立っている要素の中で最大のものを探す
    size_t max_element = 0;
    size_t max_element_index = index;
    for (size_t j = index; j < n; ++j) {
      if ((p[j] & mask) != 0 && p[j] > max_element) {
        max_element = p[j];
        max_element_index = j;
      }
    }

    // iビット目が立っている要素がなければ、次のビットへ進む
    if (max_element == 0) continue;

    // 最大要素をindex番目と入れ替える
    std::swap(p[index], p[max_element_index]);
    max_element_index = index;

    // p[max_element_index]をiビット目が立っている要素にXORする
    // TODO:どのように辻褄を合わせているかを調べる
    for (size_t j = 0; j < n; ++j) {
      if (j != max_element_index && (p[j] & mask) != 0) {
        p[j] = p[j] ^ p[max_element_index];
      }
    }

    // 次の要素へ
    index++;
  }

  // 結果を計算する
  uint64_t result = 0;
  for (size_t i = 0; i < n; ++i) {
    result ^= p[i];
  }

  return result;
}

// 赤色側をXORした値をR、青色側をXORした値をBとする
// S = A_1 ^ A_2 ^ ... ^ A_N = R ^ B
// Sで1となるビットに対応する(R_i, B_i)は(1, 0)か(0, 1)である
// ⇒ R+Bは塗り分け方に左右されずにそのビットが必ず1になる
// Sで0となるビットに対応する(R_i, B_i)は(0, 0)か(1, 1)である
// ⇒ R&~S（=B&~S）が最大となるような塗り分け方を選択したい
int solve_F() {
  size_t N = 0;
  std::cin >> N;

  std::vector<uint64_t> A(N);
  uint64_t S = 0;
  for (auto& a : A) {
    std::cin >> a;
    S ^= a;
  }

  // Sで0となるビットのみを残す
  for (auto& a : A) {
    a &= ~S;
  }

  // Sで0となるビットだけのXORで値が最大となるパターンを見つける
  const uint64_t subset = max_subarray_xor(A.data(), A.size());

  // Sで0となるビットだけのR（subset） + Sで0となるビットだけのB（subset） + Sで1となるビットだけのR+B（S）
  std::cout << (subset * 2 + S);
  return 0;
}
