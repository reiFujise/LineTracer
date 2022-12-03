#include <mbed.h>
#include "interupter.h"

DigitalOut m1_mode(D2); // モータ1のモード
DigitalOut m2_mode(D1); // モータ2のモード
DigitalOut m1_phase(D3); //　モータドライバとかいうやつのモード選択を行う　
DigitalOut m2_phase(D4); 
PwmOut     enable(D12); // モータドライバ関連
Counter    interrupt_counter(D1); // フォトインタラプタのカウンタ
AnalogIn   ref1_value(A1); // ラインセンサ1の電圧値を受け取る
AnalogIn   ref2_value(A2); // ラインセンサ2の電圧値を受け取る