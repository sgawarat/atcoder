// 解説前
#include <iostream>
#include <string>
#include <vector>
#include <set>

// 連結した文字列は十分に長いので、足りない場合は考えない。
// N<=10^5なので、O(NlogN)の方法でやりたい。
// tの文字に対応するsの文字を順番に見つけて、そのさいに通過したsの文字数を累計すれば良い。
// 文字数分だけループするとすれば、次の文字を見つける方法はO(logN)でなければならない。
int solve_E() {
  std::string s;  // もととなる文字列
  std::string t;  // 見つけたい文字列
  std::cin >> s >> t;

  // 文字の種類ごとにs内のインデックスのsetを作る
  std::vector<std::set<size_t>> index_sets(26);  // aからzの26文字
  for (size_t i = 0; i < s.size(); ++i) {
    index_sets[s[i] - 'a'].insert(i);
  }

  // sからtを作れるかを調べる
  size_t result = 0;
  for (const auto c : t) {
    // cがsに含まれていなければ、sからtを作れない
    const auto& index_set = index_sets[c - 'a'];
    if (index_set.empty()) {
      std::cout << "-1";
      return 0;
    }

    // cとなる次の文字を見つける
    const size_t offset = result % s.size();  // sにおける現在の位置
    auto iter = index_set.upper_bound(offset);
    if (iter == index_set.end()) {
      // 現在地以降にcがない場合、最初のcを選択する
      result += s.size() - offset;
      result += *index_set.begin();
    } else {
      // 現在地以降にcがある場合、それを選択する
      result += *iter - offset;
    }
  }

  // 結果発表
  std::cout << (result + 1);  // 1スタートのインデックスに変換する
  return 0;
}

int main() {
  return solve_E();
}
