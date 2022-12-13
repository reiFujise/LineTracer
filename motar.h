# include <mbed.h>

class Motar{
  public:
    // デファルとで徐行にしとく
    float period;
    float duty_ratio;

    void increase_duty(int num);
    void decrease_duty(int num);
  
  private:
};

void Motar::increase_duty(float increase_rate){
  this->duty_ratio += increase_rate;
  if (this->duty_ratio > 1.0f) this->duty_ratio = 1.0f;
}

void Motar::decrease_duty(int decrease_rate){
  this->duty_ratio -= decrease_rate;
  if (this->duty_ratio < 0) this->duty_ratio = 0.0f;
}
