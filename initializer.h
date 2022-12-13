#include <mbed.h>

DigitalOut m1_phase(D0);
PwmOut     m1_enable(D6);
DigitalOut m2_phase(D1);
PwmOut     m2_enable(D5);
AnalogIn   ref1_value(A1); 
AnalogIn   ref2_value(A2); 
