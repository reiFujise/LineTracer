#include <mbed.h>
#include "interupter.h"

DigitalOut m1_phase(D0);
PwmOut     m1_enable(D6);
DigitalOut m2_phase(D1);
PwmOut     m2_enable(D5);
Counter    interrupt_counter(D9);  //モータのポートと被ってることに気づいたのでコメントアウト
AnalogIn   ref1_value(A1); 
AnalogIn   ref2_value(A2); 
