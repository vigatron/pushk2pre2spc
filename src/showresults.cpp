#include "main.hpp"

static const char szHEX[] = "0123456789ABCDEF";

//
void showresults_n(uint8_t *fng) {
  uint8_t cmplx[32] = {0};
  for (int i = 0; i < 256; i++) {
    uint8_t bpos = i >> 3;
    uint8_t mask = 1 << 7 - (i % 8);
    if (fng[i]) {
      cmplx[bpos] |= mask;
    }
  }

  for (int i = 0; i < 32; i++) {
    uint8_t v = cmplx[i];
    std::cout << szHEX[(v >> 4) & 0xF] << szHEX[v & 0xF];
  }
  std::cout << "\n";
}

//
void showresults_t(uint8_t *fng) {
  for (int i = 0; i < 256; i++) {
    uint8_t v = fng[i] ? '#' : '.';
    bool sep = (i % 16) == 15;
    std::cout << v;
    if (sep)
      std::cout << '\n';
  }
}

//
void showresults_s(uint8_t *fng) {
  int cnt = 0;
  for (int i = 0; i < 256; i++) {
    if (fng[i])
      cnt++;
  }
  std::cout << cnt << '\n';
}