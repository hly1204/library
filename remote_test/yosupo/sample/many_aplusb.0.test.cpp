#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "misc/scanner_printer.hpp"

int main() {
  lib::Scanner scanner;
  lib::Printer printer;
  int T;
  unsigned long long n, m;
  scanner.scan(T);
  while (T--) {
    scanner.scan(n, m);
    printer.print(n + m, '\n');
  }
  return 0;
}