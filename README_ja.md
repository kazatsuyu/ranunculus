# ranunculus

適当にまとめたC++ライブラリ

## integer\_sequence.hpp
`std::integer_sequence` 風のテンプレートクラスに対しての拡張。
concat, slice, append, prependなど、よくある配列に対する操作を使える。

## type\_sequence.hpp
`std::tuple`など、可変長型配列に対する拡張。
内容はinteger\_sequence.hppのものとほぼ共通。

## bitcount.hpp
popcount, nlz, ntzなどのビット操作を定数式で実装。scoped enum型にも対応
