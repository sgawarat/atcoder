// 本戦
#include <iostream>

int students[100001];  // 登校した生徒の番号リスト

int solve_C() {
  int N;
  std::cin >> N;

  // 登校の早い順に生徒番号を並べ替える
  for (int i = 1; i <= N; ++i) {
    int A;  // 到着時点で教室にいた人数＝到着した順位
    std::cin >> A;
    students[A] = i;
  }

  // 登校の早い順に生徒番号を表示する
  std::cout << students[1];
  for (int i = 2; i <= N; ++i) {
    std::cout << ' ' << students[i];
  }
  return 0;
}
