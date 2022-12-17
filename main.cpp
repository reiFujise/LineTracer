#include <mbed.h>
#include "motar.h"
#include "reflector.h"
#include "interupter.h"

  // インスタンス化
  DigitalOut r_motar_phase(D0);
  PwmOut     r_motar_enable(D1);
  DigitalOut l_motar_phase(D5);
  PwmOut     l_motar_enable(D6);
  AnalogIn   ref1_value(A1); 
  AnalogIn   ref2_value(A2); 
  Counter    r_counter(D9);
  // interupter のポート接続が完了したらコメントイン
  Counter l_counter(D10);
  Motar      r_motar;
  Motar      l_motar;
	Reflector  r_ref;
	Reflector  l_ref;
  

// 目標の回転数に近づける処理
void PID(Motar r_motar, Motar l_motar){
  r_motar.duty_ratio = 0.2f;
  l_motar.duty_ratio = 0.2f;
  r_motar_enable.write(r_motar.duty_ratio);
  l_motar_enable.write(l_motar.duty_ratio);
}

// p_motar 側に車体を傾ける
void r_rotate(Motar r_motar, Motar l_motar, float change_rate){
  r_motar.decrease_duty(change_rate);
  l_motar.increase_duty(change_rate);
  r_motar_enable.write(r_motar.duty_ratio);
  l_motar_enable.write(l_motar.duty_ratio);
}

void l_rotate(Motar l_motar, Motar r_motar, float change_rate){
  l_motar.decrease_duty(change_rate);
  r_motar.increase_duty(change_rate);
  l_motar_enable.write(l_motar.duty_ratio);
  r_motar_enable.write(r_motar.duty_ratio);
}

void adjust_speed(Motar r_motar, Motar l_motar){
  float aver_rate = (r_motar.duty_ratio + l_motar.duty_ratio) / 2;
  r_motar.duty_ratio = aver_rate;
  l_motar.duty_ratio = aver_rate;
  r_motar_enable.write(r_motar.duty_ratio);
  l_motar_enable.write(l_motar.duty_ratio);
}

int main(){
  // モータの回転の向き: 1が正転 0が反転
  r_motar_phase      = 1;
  l_motar_phase      = 1;
  // 初期化
  r_motar.period     = 0.001f;
  l_motar.period     = 0.001f;
  r_motar.duty_ratio = 0.2f;
  l_motar.duty_ratio = 0.2f;

  // pwd の周期決定 走行中に変動させたいのでwhile文の中に入れる
  r_motar_enable.period(r_motar.period);
  l_motar_enable.period(l_motar.period);

  r_ref.is_black = false;
  l_ref.is_black = false;

  while(1){
    // 色判定
    r_ref.assign_color(ref1_value);
    l_ref.assign_color(ref2_value);
    // 色の判定をチェックする
    printf("--- Check Color --- Right Senser => %d --- Left Senser => %d ---\n", r_ref.is_black, l_ref.is_black);
    printf("value ----- Ritght => %f --- Left => %f --- \n", ref1_value.read(), ref2_value.read());

    /////////////////////  duty比とperiodの決定をする処理
    if(r_ref.is_black == true && l_ref.is_black == true){
      PID(r_motar, l_motar);
    }else if(r_ref.is_black == true && l_ref.is_black == false){
      float change_rate = 0.1f;
      while(l_ref.is_black == false){
        // 指数関数的に増加させる
        change_rate += change_rate;
        r_rotate(r_motar, l_motar, change_rate);
        l_ref.assign_color(ref2_value);
        printf("--- Check Color --- Right Senser => %d --- Left Senser => %d ---\n", r_ref.is_black, l_ref.is_black);
        printf("value --- Left => %f --- \n",ref2_value.read());

      }
      adjust_speed(r_motar, l_motar);
    }else if(r_ref.is_black == false && l_ref.is_black == true){
      float change_rate = 0.1f;
      while(r_ref.is_black == false){
        change_rate += change_rate;
        l_rotate(l_motar, r_motar, change_rate);
        r_ref.assign_color(ref1_value);
        printf("--- Check Color --- Right Senser => %d --- Left Senser => %d ---\n", r_ref.is_black, l_ref.is_black);
        printf("value ----- Ritght => %f --- \n", ref1_value.read());

      }
      adjust_speed(r_motar, l_motar);
    }else{
      PID(r_motar, l_motar);
    }

    // 回転数の計測の処理

    ////////////////////  特定の距離を走行したら実行する処理
  }
}
