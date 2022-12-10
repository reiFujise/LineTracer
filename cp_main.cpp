#include <mbed.h>
#include "initializer.h"
#include "motar.h"
#include "reflector.h"

void turn_to_m2(Motar m1, Motar m2){
  // モータ2側に傾ける
  if(m1.speed < m1.max_speed) m1.speed_up();
  if(m2.speed > m2.min_speed) m2.speed_down();
}

void turn_to_m1(Motar m1, Motar m2){
  // モータ1側に傾ける
  if(m2.speed < m2.max_speed) m2.speed_up();
  if(m1.speed > m1.min_speed) m1.speed_down();
}

void  adjust_speed(Motar m1, Motar m2){
  // モータ1とモータ2の速度を合わせる
  if(m1.speed < m2.speed){
    m1.speed = m2.speed;
  }else if(m2.speed < m1.speed){
    m2.speed = m1.speed;
  }else{
    return;
  }
}

int main(){
  // モータのインスタンス化
  Motar m1;
  Motar m2;

  // phase 選択
  m1_phase = 1;
  m2_phase = 1;

  // リフレクタのインスタンス化
  Reflector ref1;
  Reflector ref2;

  // 走行時の処理
  while(1){
    // 処理の初めに色判別をする
    if(ref1_value > ref1.bordar_value) ref1.black = true;
    if(ref2_value > ref2.bordar_value) ref2.black = true;

    // ログ出力
    printf("DebugLog: ref1 = black? => %d, ref2 = black? => %d\n", ref1.black, ref2.black)

    // センサに応じた処理
    if (ref1.black == false && ref2.black == true){
      // パターン1: センサ1が白、センサ2が黒
      turn_to_m2(m1, m2);
    }else if (ref1.black == true && ref2.black == false){
      // パターン2: センサ1が黒、センサ2が白
      turn_to_m1(m1, m2);
    }else if (ref1.black == true && ref2.black == true){
      // パターン3: 両センサとも黒
      // スピードを合わせた後1段階スピードを上げる
      adjust_speed(m1, m2);
      if (m1.speed < m1.max_speed) m1.speed += 1;
      if (m2.speed < m2.max_speed) m2.speed += 1;
    }else{
      // パターン4: 両センサとも白
      // 現状どうしようもないのでただ返す
      return;
    }

    // 走行させる
    m1_enable.period(m1.period);
    m2_enable.period(m2.period);
    m1_enable.write(m1.duty[m1.speed]);
    m2_enable.write(m2.duty[m2.speed]);

    // ログ出力
    printf("Motar1 => duty比: %d, speed: %d, \n", m1.duty[m1.speed]*100, m1.speed);
    printf("Motar2 => duty比: %d, speed: %d, \n", m2.duty[m2.speed]*100, m2.speed);
  }
}

