# include <mbed.h>

class Motar{
  public:
    // デファルとで徐行にしとく
    float period     = 1.0f;
    float duty_ratio = 0.0f;

    void speed_up(int num);
    void speed_down(int num);
  
  private:
};

void Motar::increase_duty(float increase_rate){
  this->duty_ratio += increase_rate;
}

void Motar::decrease_duty(int decrease_rate){
  this->duty_ratio -= decrease_rate;
}
