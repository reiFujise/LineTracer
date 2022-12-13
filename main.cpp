#include <mbed.h>
#include "initializer.h"
#include "motar.h"
#include "reflector.h"
#include "interupter.h"

  // インスタンス化
  DigitalOut m1_phase(D0);
  PwmOut     m1_enable(D6);
  DigitalOut m2_phase(D1);
  PwmOut     m2_enable(D5);
  AnalogIn   ref1_value(A1); 
  AnalogIn   ref2_value(A2); 
  Counter    r_counter(D9);
  // interupter のポート接続が完了したらコメントイン
  // Counter l_counter(D10);
  Motar      r_motar;
  Motar      l_motar;
	Reflector  r_ref;
	Reflector  l_ref;
  

// 目標の回転数に近づける処理
void PID(){

}

// p_motar 側に車体を傾ける
void rotate(Motar p_motar, Motar s_motar, float change_rate){
  p_motar.decrease_duty(change_rate);
  s_motar.increase_duty(change_rate);
  m1_enable.write(p_motar.duty_ratio);
  m2_enable.write(s_motar.duty_ratio);
}

void adjust_speed(Motar r_motar, Motar l_motar){
  float aver_rate = (r_motar.duty_ratio + l_motar.duty_ratio) / 2;
  r_motar.duty_ratio = aver_rate;
  l_motar.duty_ratio = aver_rate;
  m1_enable.write(r_motar.duty_ratio);
  m2_enable.write(l_motar.duty_ratio);
}

int main(){
  // モータの回転の向き: 1が正転 0が反転
  m1_phase      = 1;
  m2_phase      = 1;
  // 初期化
  m1.period     = 1.0f;
  m2.period     = 1.0f;
  m1.duty_ratio = 0.5f;
  m2.duty_ratio = 0.5f;

  // pwd の周期決定 走行中に変動させたいのでwhile文の中に入れる
  m1_enable.period(r_motar.period);
  m2_enable.period(l_motar.period);

  while(1){
    // 色判定
    r_ref.assign_color(ref1_value);
    l_ref.assign_color(ref2_value);
    // 色の判定をチェックする
    printf("--- Check Color --- Right Senser => %d --- Left Senser => %d ---\n", r_ref.is_black, l_ref.is_black);

    /////////////////////  duty比とperiodの決定をする処理
    if(r_ref.is_black == true && l_ref.is_black == true){
      PID();
    }else if(r_ref.is_black == true && l_ref.is_black == false){
      float change_rate = 0.01f;
      while(l_motar.is_black == false){
        // 指数関数的に増加させる
        change_rate += change_rate;
        rotate(r_motar, l_motar, change_rate);
        l_ref.assign_color(ref2_value);
      }
      adjust_speed(r_motar, l_motar);
    }else if(r_ref.is_black == false && l_ref.is_black == true){
      float change_rate = 0.01f;
      while(r_motar.is_black == false){
        change_rate += change_rate;
        rotate(l_motar, r_motar, change_rate);
        r_ref.assign_color(ref1_value);
      }
      adjust_speed(r_motar, l_motar);
    }else{
      PID();
    }

    // 回転数の計測の処理

    ////////////////////  特定の距離を走行したら実行する処理
  }
}
