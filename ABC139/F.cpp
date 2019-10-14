// 解説後
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

template <typename T>
struct Vector2 {
  Vector2& operator+=(const Vector2& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
  }

  friend Vector2 operator+(Vector2 lhs, Vector2 rhs) noexcept {
    return Vector2(lhs) += rhs;
  }

  // 内積
  template<typename U>
  auto dot(Vector2<U> rhs) const noexcept {
    return x * rhs.x + y * rhs.y;
  }

  // ノルムの2乗
  auto norm2() const noexcept { return dot(*this); }

  // ノルム
  auto norm() const noexcept { return sqrt(norm2()); }

  T x, y;
};

// L^2ノルムを最大化したいので、方向が同じベクトルを集める
int solve_F() {
  size_t N;
  std::cin >> N;

  // 指標となる方向ベクトルを作る
  std::vector<Vector2<double>> directions(360);
  for (size_t i = 0; i < directions.size(); ++i) {
    const double angle = 3.14159265358979 * 2 * i / directions.size();
    directions[i].x = cos(angle);
    directions[i].y = sin(angle);
  }


  // 指標となる方向と同じ向きを持つベクトルの総和を計算する
  std::vector<Vector2<int64_t>> summations(directions.size());
  for (size_t i = 0; i < N; ++i) {
    Vector2<int64_t> v;
    std::cin >> v.x >> v.y;

    for (size_t j = 0; j < directions.size(); ++j) {
      if (directions[j].dot(v) >= 0.0) {
        summations[j] += v;
      }
    }
  }

  // 最も長いベクトルの距離を計算する
  double result = 0.0;
  for (const auto& v : summations) {
    result = std::max(result, v.norm());
  }

  // 結果発表
  std::cout << std::setprecision(20) << result;
  return 0;
}

int main() { return solve_F(); }
