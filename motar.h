# include <mbed.h>

class Motar{
  public:
    M(){
      duty[] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
      // デファルとで徐行にしとく
      speed     = 1;
      max_speed = 9;
      min_speed = 0;
      period    = 0.01f;

      void speed_up();
      void speed_down();
    }

    // duty比を配列に格納し、段階的に調整できるようにする
    // 両輪の値を正確に揃えるため、固定値にする
    // 一旦duty比の最大値を50％とする
    float duty; // duty比宣言用
    int   max_speed; // dutyの要素数の最大値
    int   min_speed; // dutyの要素数の最小値
    int   speed; // dutyの要素数
    float period; //duty比の周期

    void speed_up();
    void speed_down();
  
  private:
};

void Motar::speed_up(){
  this->speed += 1;
}

void Motar::speed_down(){
  this->speed -= 1;
}
