# プログラミングTips

## I/O

### 浮動小数点数を出力する精度を変更する

```cpp
#include <iomanip>

double pi = 3.14159265358979;
std::cout << std::setprecision(6) << pi;  // => 3.14159
```

## アルゴリズム

### 二分探索

以下の関数は対数時間で行われる。

- `lower_bound`：ある値以上の要素を持つ最初のイテレータを返す
  - => ある値の部分列の先頭イテレータを返す
- `upper_bound`：ある値より大きい要素を持つ最初のイテレータを返す
  - => ある値の部分列の終端イテレータを返す
- `binary_search`：ある値が範囲内に存在するかを求める
- `equal_range`：ある値の部分列の範囲を指すイテレータのペアを返す

ただし、非メンバ関数バージョンにはいくつかの条件がある。

- 渡される範囲内の要素はソートされている必要がある
- 渡されるイテレータがRandomAccessIteratorの場合のみ対数時間で処理する
  - それ以外では線形になる

```cpp
std::vector<size_t> v{0, 1, 2, 2, 3, 7};  // vはソート済み
std::lower_bound(v.begin(), v.end(), 2);  // == v.begin() + 2
std::lower_bound(v.begin(), v.end(), 5);  // == v.begin() + 5
std::lower_bound(v.begin(), v.end(), 9);  // == v.end()
std::upper_bound(v.begin(), v.end(), 2);  // == v.begin() + 4
std::upper_bound(v.begin(), v.end(), 5);  // == v.begin() + 5
std::upper_bound(v.begin(), v.end(), 9);  // == v.end()
```
