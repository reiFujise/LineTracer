# include <mbed.h>

class Motar{
  public:
    // デファルとで徐行にしとく
    float period;
    float duty_ratio;

    void increase_duty(float rate);
    void decrease_duty(float rate);
  
  private:
};

inline void Motar::increase_duty(float increase_rate){
  this->duty_ratio += increase_rate;
  if (this->duty_ratio > 0.4f) this->duty_ratio = 0.4f;
}

inline void Motar::decrease_duty(float decrease_rate){
  this->duty_ratio -= decrease_rate;
  if (this->duty_ratio < 0.0f) this->duty_ratio = 0.0f;
}
