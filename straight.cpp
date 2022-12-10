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

  float duty[] = { 0.1f, 0.9f };

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

    printf("--- Start while loop ---\n\n");
  // 左のセンサしか使い物にならないので、左が黒に入ったらみぎへ、
  // 左のセンサが白に入ったら左へ傾ける処理にすれば真っ直ぐ行くんじゃね？？？

  bool right_flag = true;
  
  while(1){
      m1_enable.write(duty[1]);
      m2_enable.write(duty[1]);

    // // ref1 はバグっているため使用しない.てか使用できない！


  //   while( right_flag == 0){

    //   m2.speed_up(1);
    //   m1.speed_down(1);
    //   m1.speed = check_speed(m1);
    //   m2.speed = check_speed(m2);

    //   m1_enable.write(duty[m1.speed]);
    //   m2_enable.write(duty[m2.speed]);

    //   ref2.value = ref2_value.read();
    //   ref2.assign_color();
    //   if(ref2.is_black == 1){
    //     if(right_flag == 1){
    //       right_flag = 0;
    //     }else{
    //       right_flag = 1;
    //     }
    //   }
    //   printf("\nCOLOR --- ref2 => %d --- \n", ref2.is_black);
    //   printf("SPEED --- m1 => %d --- m2 => %d\n", m1.speed, m2.speed);
    // }

    // while(right_flag == 1){
    //   m2.speed_down(1);
    //   m1.speed_up(1);
    //   m1.speed = check_speed(m1);
    //   m2.speed = check_speed(m2);

    //   m1_enable.write(duty[m1.speed]);
    //   m2_enable.write(duty[m2.speed]);

	  //   ref2.value = ref2_value.read();
    //   ref2.assign_color();
    //   if(ref2.is_black == 1){
    //     if(right_flag == 1){
    //       right_flag = 0;
    //     }else{
    //       right_flag = 1;
    //     }
    //   }
    //   printf("\nCOLOR --- ref2 => %d --- \n", ref2.is_black);
    //   printf("SPEED --- m1 => %d --- m2 => %d\n", m1.speed, m2.speed);
    //   // m1_enable.write(duty[2]);
    //   // m2_enable.write(duty[2]);
    // }
  }
}

