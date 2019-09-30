#include <iostream>

// A
// int main() {
//  int N;
//  std::cin >> N;
//
//  std::cout << (static_cast<double>((N + 1) / 2) / static_cast<double>(N));
//  return 0;
//}

// B
// int main() {
//  int N, K;
//  std::cin >> N >> K;
//
//  size_t count = 0;
//  for (int i = 0; i < N; ++i) {
//    int h;
//    std::cin >> h;
//    if (h >= K) count++;
//  }
//
//  std::cout << count;
//  return 0;
//}

// C
// int students[100001];  // 登校した生徒の番号リスト
//
// int main() {
//  int N;
//  std::cin >> N;
//
//  // 登校の早い順に生徒番号を並べ替える
//  for (int i = 1; i <= N; ++i) {
//    int A;  // 到着時点で教室にいた人数＝到着した順位
//    std::cin >> A;
//    students[A] = i;
//  }
//
//  // 登校の早い順に生徒番号を表示する
//  std::cout << students[1];
//  for (int i = 2; i <= N; ++i) {
//    std::cout << ' ' << students[i];
//  }
//  return 0;
//}

// D
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

// E（本戦後）
//#include <vector>
//#include <unordered_set>
//
//int main() {
//  size_t N;  // 宝箱の個数
//  size_t M;  // 鍵の個数
//  std::cin >> N >> M;
//
//  // 各宝箱を開けられる最安値の鍵を調べる
//  const uint32_t INVALID_PRICE = UINT32_MAX;
//  const size_t INVALID_KEY_INDEX = SIZE_MAX;
//  uint32_t min_prices[12];
//  std::unordered_set<size_t> key_sets[12];  // 同価格の鍵の集合
//  for (size_t i = 0; i < N; ++i) {
//    min_prices[i] = INVALID_PRICE;
//  }
//  for (size_t i = 0; i < M; ++i) {
//    uint32_t price;
//    size_t count;
//    std::cin >> price >> count;
//    for (size_t j = 0; j < count; ++j) {
//      size_t box;
//      std::cin >> box;
//      if (price < min_prices[box - 1]) {
//        min_prices[box - 1] = price;
//        key_sets[box - 1].clear();
//        key_sets[box - 1].insert(i);
//      } else if (price == min_prices[box - 1]) {
//        key_sets[box - 1].insert(i);
//      }
//    }
//  }
//
//  // すべての宝箱を開けるために必要な総費用を計算する
//  int64_t result = 0;
//  std::unordered_set<size_t> used_key_set;  // 計上済みの鍵の集合
//  for (size_t i = 0; i < N; ++i) {
//    // いずれかの宝箱が開けられない場合
//    if (used_key_set.empty()) {
//      result = -1;
//      break;
//    }
//
//    // 宝箱が使用済みの鍵で開けられるなら計上しない
//    bool used = false;
//    for (const auto& key : key_sets[i]) {
//      if (used_key_set.find(key) != used_key_set.end()) {
//        used = true;
//        break;
//      }
//    }
//
//    // 使った鍵を1つ分だけ計上する
//    if (!used) {
//      result += min_prices[i];
//    }
//  }
//
//  std::cout << result;  
//  return 0;
//}

// E（提出済、CE）
//#include <iostream>
//#include <set>
//     
//int main() {
//  size_t N;  // 宝箱の個数
//  size_t M;  // 鍵の個数
//  std::cin >> N >> M;
//     
//  // 各宝箱を開けられる最安値の鍵を調べる
//  const uint32_t INVALID_PRICE = 100001;
//  const size_t INVALID_KEY_INDEX = 1001;
//  uint32_t min_prices[12];
//  size_t key_indices[12];
//  for (size_t i = 0; i < N; ++i) {
//    min_prices[i] = INVALID_PRICE;
//    key_indices[i] = INVALID_KEY_INDEX;
//  }
//  for (size_t i = 0; i < M; ++i) {
//    uint32_t price;
//    size_t count;
//    std::cin >> price >> count;
//    for (size_t j = 0; j < count; ++j) {
//      size_t box;
//      std::cin >> box;
//      if (price < min_prices[box - 1]) {
//        min_prices[box - 1] = price;
//        key_indices[box - 1] = i;
//      }
//    }
//  }
//     
//  // すべての宝箱を開けるために必要な総費用を計算する
//  int64_t result = 0;
//  std::set<uint32_t> used_key_set;
//  for (size_t i = 0; i < N; ++i) {
//    // いずれかの宝箱が開けられない場合
//    if (key_indices[i] == INVALID_KEY_INDEX) {
//      result = -1;
//      break;
//    }
//     
//    // まだ使っていない鍵を計上する
//    if (used_key_set.find(key_indices[i] != used_key_set.end())) {
//      result += min_prices[i];
//      used_key_set.insert(key_indices[i]);
//    }
//  }
//     
//  std::cout << result;  
//  return 0;
//}

//// E（解説後）
//#include <algorithm>
//
//int dp[1 << 12];  // 「開けた宝箱のビットセット」をインデックスとしたときの最小費用のDPテーブル
//int prices[1000];  // 鍵の値段
//int box_flags[1000];  // 鍵が開けられる宝箱のビットセット
//
//int main() {
//  int N;  // 宝箱の個数
//  int M;  // 鍵の個数
//  std::cin >> N >> M;
//
//  // 鍵の情報を取得する
//  for (int i = 0; i < M; ++i) {
//    int box_count;
//    std::cin >> prices[i] >> box_count;
//
//    // 開けられる宝箱をビットセットにまとめる
//    for (int j = 0; j < box_count; ++j) {
//      int box;
//      std::cin >> box;
//      box_flags[i] |= 1 << (box - 1);
//    }
//  }
//
//  // dpテーブルを埋める
//  // ただし、dp[(1 << N) - 1]以外の値は正しくない可能性がある
//  const int INVALID_PRICE = 1500000;
//  dp[0] = 0;
//  for (int i = 1; i < (1 << N); ++i) {
//    dp[i] = INVALID_PRICE;
//  }
//  for (int i = 0; i < (1 << N); ++i) {
//    for (int key = 0; key < M; ++key) {
//      const int ij = i | box_flags[key];
//      if (ij != i) {
//        dp[ij] = std::min(dp[ij], dp[i] + prices[key]);
//      }
//    }
//  }
//
//  if (dp[(1 << N) - 1] == INVALID_PRICE) {
//    std::cout << "-1";
//  } else {
//    std::cout << dp[(1 << N) - 1];
//  }
//  return 0;
//}

//// E（解説後、コンテナ使用）
//#include <algorithm>
//#include <unordered_map>
//#include <vector>
//
//using BoxBitset = uint32_t;  // 宝箱のビットセット
//using Price = uint32_t;  // 値段
//
//// 鍵
//struct Key {
//  Price price;  // 値段
//  BoxBitset box_bitset;  // 開けられる宝箱のビットセット
//};
//
//int main() {
//  size_t N = 0;  // 宝箱の個数
//  size_t M = 0;  // 鍵の個数
//  std::cin >> N >> M;
//
//  // 鍵の情報を取得する
//  std::vector<Key> keys(M);
//  for (auto& key : keys) {
//    size_t box_count = 0;
//    std::cin >> key.price >> box_count;
//
//    // 開けられる宝箱をビットセットにまとめる
//    for (size_t i = 0; i < box_count; ++i) {
//      size_t box = 0;
//      std::cin >> box;
//      key.box_bitset |= 1 << (box - 1);
//    }
//  }
//
//  // 宝箱を開けるための最小費用を計算する
//  std::unordered_map<BoxBitset, Price> price_map;  // 開けた宝箱のビットセットから最小費用を探すためのマップ
//  price_map.emplace(0, 0);  // 初期状態はどれも開けていない状態
//  for (int box_bitset = 0; box_bitset < (1 << N); ++box_bitset) {
//    // box_bitsetのように宝箱を開けるパターンが存在するなら、追加の鍵で宝箱を開けた状態を計算して記録する
//    const auto price_iter = price_map.find(box_bitset);  // box_bitsetのように宝箱を開けるために現時点で必要な費用
//    if (price_iter != price_map.end()) {
//      for (const auto& key : keys) {
//        // next_box_bitsetのように宝箱を開けるのに必要な最小費用を累積的に計算する
//        const auto next_box_bitset = box_bitset | key.box_bitset;  // keyで宝箱を開けた後の状態
//        const auto next_price_iter = price_map.find(next_box_bitset);  // keyで宝箱を開けた後に必要な費用
//        if (next_price_iter == price_map.end()) {
//          price_map.emplace(next_box_bitset, price_iter->second + key.price);
//        } else {
//          next_price_iter->second = std::min(next_price_iter->second, price_iter->second + key.price);
//        }
//      }
//    }
//  }
//
//  // すべての宝箱を開けたときの費用を表示する
//  const auto price_iter = price_map.find((1 << N) - 1);
//  if (price_iter == price_map.end()) {
//    std::cout << "-1";
//  } else {
//    std::cout << price_iter->second;
//  }
//
//  return 0;
//}

// D（解説後）
int main_D();

int main() {
  return main_D();
}
