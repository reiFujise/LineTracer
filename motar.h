# include <mbed.h>

class Motar{
  public:
      // デファルとで徐行にしとく
      int speed = 1;
      int max_speed = 4;
      int min_speed = 0;
      float period  = 1.0f;

      void speed_up(int num);
      void speed_down(int num);
  
  private:
};

void Motar::speed_up(int num){
  this->speed += num;
}

void Motar::speed_down(int num){
  this->speed -= num;
}
