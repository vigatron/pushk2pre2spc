#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <string>

class Fingerprint {
public:
  static constexpr int SIZE = 256;
  static constexpr int HEX_BLOCKS = SIZE / 8;
  static constexpr int LINE_WIDTH = 16;
  static constexpr char HEX_DIGITS[] = "0123456789ABCDEF";

  explicit Fingerprint(const uint8_t *data) : fng(data) {}

  // Компактный HEX-вывод
  void printHex() const {
    std::array<uint8_t, HEX_BLOCKS> cmplx{};
    for (int i = 0; i < SIZE; ++i) {
      int bpos = i >> 3;
      uint8_t mask = 1u << (7 - (i % 8));
      if (fng[i]) {
        cmplx[bpos] |= mask;
      }
    }
    for (uint8_t v : cmplx) {
      std::cout << HEX_DIGITS[(v >> 4) & 0xF] << HEX_DIGITS[v & 0xF];
    }
    std::cout << '\n';
  }

  // Текстовый вывод (# и .)
  void printText() const {
    for (int i = 0; i < SIZE; ++i) {
      std::cout << (fng[i] ? '#' : '.');
      if ((i + 1) % LINE_WIDTH == 0) {
        std::cout << '\n';
      }
    }
  }

  // Подсчет единиц
  void printCount() const {
    int cnt = 0;
    for (int i = 0; i < SIZE; ++i) {
      cnt += fng[i] ? 1 : 0;
    }
    std::cout << cnt << '\n';
  }

  // JSON-вывод (пример расширения)
  void printJson() const {
    std::cout << "{ \"fingerprint\": [";
    for (int i = 0; i < SIZE; ++i) {
      std::cout << static_cast<int>(fng[i]);
      if (i < SIZE - 1)
        std::cout << ", ";
    }
    std::cout << "] }\n";
  }

private:
  const uint8_t *fng;
};
