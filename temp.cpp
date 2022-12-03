#include <mbed.h>
#include "initializer.h"
#include "reflector.h"

void speed_up(int speed){
  speed += 1;
}

void speed_down(int speed){
  speed -= 1;
}

void turn_to_m2(int m1_speed, int m2_speed, int max, int min){
  // モータ2側に傾ける
  if(m1_speed < max) speed_up(m1_speed);
  if(m2_speed > min) speed_down(m2_speed);
}

void turn_to_m1(int m1_speed, int m2_speed, int max, int min){
  // モータ1側に傾ける
  if(m2_speed < max) speed_up(m2_speed);
  if(m1_speed > min) speed_down(m1_speed);
}

void  adjust_speed(int m1_speed, int m2_speed){
  // モータ1とモータ2の速度を合わせる
  if(m1_speed < m2_speed){
    m1_speed = m2_speed;
  }else if(m2_speed < m1_speed){
    m2_speed = m1_speed;
  }else{
    return;
  }
}

int main(){
  // モータのインスタンス化
  float m1_duty[] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
  // デファルとで徐行にしとく
  int m1_speed = 1;
  int m1_period    = 0.01f;

  float m2_duty[] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
  // デファルとで徐行にしとく
  int m2_speed = 1;
  int m2_period    = 0.01f;

  int max_speed = 9;
  int min_speed = 0;

  // mode 選択
  m1_mode = 1;
  m2_mode = 1;

  // phase 選択
  m1_phase = 0;
  m2_phase = 0;

  // リフレクタのインスタンス化
  Reflector ref1;
  Reflector ref2;

  // 走行時の処理
  while(1){
    // 処理の初めに色判別をする
    if(ref1_value > ref1.bordar_value) ref1.black = true;
    if(ref2_value > ref2.bordar_value) ref2.black = true;

    // ログ出力
    printf("DebugLog: ref1 = black? => %d, ref2 = black? => %d\n", ref1.black, ref2.black);

  //   // センサに応じた処理
  //   if (ref1.black == false && ref2.black == true){
  //     // パターン1: センサ1が白、センサ2が黒
  //     turn_to_m2(m1, m2, max_speed, min_speed);
  //   }else if (ref1.black == true && ref2.black == false){
  //     // パターン2: センサ1が黒、センサ2が白
  //     turn_to_m1(m1, m2, max_speed, min_speed);
  //   }else if (ref1.black == true && ref2.black == true){
  //     // パターン3: 両センサとも黒
  //     // スピードを合わせた後1段階スピードを上げる
  //     adjust_speed(m1_speed, m2_speed, max);
  //     if (m1_speed < max) m1_speed += 1;
  //     if (m2_speed < max) m2_speed += 1;
  //   }else{
  //     // パターン4: 両センサとも白
  //     // 現状どうしようもないのでただ返す
  //     return;
  //   }

    // 走行させる
    enable.period(m1_period);
    enable.period(m2_period);
    enable.write(m1_duty[m1_speed]);
    enable.write(m2_duty[m2_speed]);

    // ログ出力
    printf("Motar1 => duty比: %d %%, speed: %d, \n", m1_duty[m1_speed]*100, m1_speed);
    printf("Motar2 => duty比: %d %%, speed: %d, \n", m2_duty[m2_speed]*100, m2_speed);
  }
}

