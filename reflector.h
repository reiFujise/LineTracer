#include <mbed.h>

class Reflector{
  public:
		float value;
    // 初期値はfalse
    bool is_black  = false;

    // 白黒判定の境界値
    double boundary_value = 0.9f;

		void assign_color();
};

void Reflector::assign_color(){
	if(this->value > this->boundary_value){
		this->is_black = true;
	}else{
		this->is_black = false;
	}
}
