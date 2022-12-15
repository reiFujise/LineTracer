#include <mbed.h>

class Reflector{
  public:
		float value;
    // 初期値はfalse
    bool is_black;

    // 白黒判定の境界値
    double boundary_value = 0.75f;

		void assign_color(AnalogIn ref_value);
};

inline void Reflector::assign_color(AnalogIn ref_value){
	if(ref_value.read() > this->boundary_value){
		this->is_black = true;
	}else{
		this->is_black = false;
	}
}
