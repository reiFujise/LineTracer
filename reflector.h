#include <mbed.h>

class Reflector{
  public:
    // 初期値はfalse
    bool black  = false;

    // 白黒判定の境界値
    // これより大きければ白だった気がする
    const double bordar_value = 0.5f;
};