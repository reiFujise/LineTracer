#include <mbed.h>

DigitalOut m1_mode(D1);
DigitalOut m2_mode(D5);
DigitalOut m1_phase(D0);
DigitalOut m2_phase(D4);
PwmOut     enable(D9);

int main(){ 
  m1_mode  = 0;
  m2_mode  = 0;
  m1_phase = 1;
  m2_phase = 1;

  float duty = 0.2f;

  float period = 0.01f;

  while(1){
    enable.period(period);
    enable.period(period);
    enable.write(duty);
    enable.write(duty);

    ThisThread::sleep_for(200);
  }
}