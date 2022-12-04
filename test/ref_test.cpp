// フォトリフレクタのテスト
// フォトリフレクタの戻り値をターミナル上に表示するテストを作成する

#include <mbed.h>

AnalogIn ref1_value(A1); // ラインセンサ1の電圧入力
AnalogIn ref2_value(A2); // ラインセンサ2の電圧入力

class Reflector{
  public:
    float value;
    bool black = false;
    float border_value = 0.5f;

    void check_color();
};

void Reflector::check_color(){
  // 黒判定をする際の電圧入力の値
  if (this->value > this->border_value){
    this->black = true;
  }else{
    this->black = false;
  }
}

int main(){
  Reflector ref1;
  Reflector ref2;

  while(1){
    ref1.value = ref1_value.read();
    ref2.value = ref2_value.read();

    ref1.check_color();
    ref2.check_color();

    printf("DebugLog: ref1 = black? => %d, ref2 = black? => %d\n", ref1.black, ref2.black);
    printf("DebugLog: ref1_value = %f, ref2_value = %f\n", ref1_value.read(), ref2_value.read());
    printf("check_value: ref1.value = %f, ref2.value = %f\n", ref1.value, ref2.value);

    ThisThread::sleep_for(200);
  }
}