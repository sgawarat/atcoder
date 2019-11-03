// 解説後
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 連結した文字列は十分に長いので、足りない場合は考えない。
// N<=10^5なので、O(NlogN)の方法でやりたい。
// tの文字に対応するsの文字を順番に見つけて、そのさいに通過したsの文字数を累計すれば良い。
// 文字数分だけループするとすれば、次の文字を見つける方法はO(logN)でなければならない。
//
// 1文字目も含めて見つけたいので、lower_bound()を使う。
// なので、次の文字を見つけるためには、resultは見つけた文字のインデックス+1となる。
// 表示する値は1スタートのインデックスなので、resultをそのまま出力できる。
int solve_E() {
  std::string s;  // もととなる文字列
  std::string t;  // 見つけたい文字列
  std::cin >> s >> t;

  // 文字の種類ごとにs内のインデックスの配列を作る
  std::vector<std::vector<size_t>> indices_by_char(26);  // aからzの26文字
  for (size_t i = 0; i < s.size(); ++i) {
    indices_by_char[s[i] - 'a'].push_back(i);
  }

  // sからtを作れるかを調べる
  int64_t result = 0;
  for (const auto t_i : t) {
    // t_iがsに含まれていなければ、sからtを作れない
    const auto& indices = indices_by_char[t_i - 'a'];
    if (indices.empty()) {
      std::cout << "-1";
      return 0;
    }

    // t_iと同じ文字をまだ見ていない部分から見つける
    const size_t offset = result % s.size();  // sにおける未見部分の先頭
    auto iter = std::lower_bound(indices.cbegin(), indices.cend(), offset);
    if (iter == indices.end()) {
      // 未見部分にt_iと同じ文字がない場合、次の繰り返し分から選択する
      result += s.size() - offset;
      result += indices[0] + 1;  // 次の文字から探し始めたいので+1
    } else {
      // 未見部分にt_iと同じ文字がある場合、それを選択する
      result += *iter - offset + 1;  // 次の文字から探し始めたいので+1
    }
  }

  // 結果発表
  std::cout << result;
  return 0;
}
