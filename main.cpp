#include <mbed.h>
#include "initializer.h"
#include "motar.h"
#include "reflector.h"

int check_speed(Motar m){
  if(m.speed > m.min_speed && m.speed < m.max_speed){
    return m.speed;
  }else if(m.speed < m.min_speed){
    return m.min_speed;
  }else if(m.speed > m.max_speed){
    return m.max_speed;
  }else{
    return m.speed;
  }
}

int main(){

  float duty[] = { 0.0f, 1.0f };

  // インスタンス化
  Motar m1;
  Motar m2;
	Reflector ref1;
	Reflector ref2;

  m1_phase = 1;
  m2_phase = 1;

  m1_enable.period(m1.period);
  m2_enable.period(m2.period);

 // 十分な回転数が確保できるよう初期トルクを大きくする
 // トルクが大きすぎたためコメントアウト

  
  while(1){
  }
}

