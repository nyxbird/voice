// Joshua Oliver
// 8/15/23 - 
// a c++ implementation of Klatt's synthesizer

#include "model.h"
#include "wav.h"
#include <iostream>


int main() {
	int sr = 44100;
	wav_stream wav;
	wav.open("fric.wav", sr);
	wav.write_header(1);
	init_model(sr);
	float update_freq = 0.005;
	int x = 0;
	for (unsigned long long i = 0; i < sr; ++i) {
		//std::cout << eval_model(i) << "\n";
		wav.write_int2(eval_model(i, sr));
		//wav.write_int2(x);/*
		//x = 16000 - x;*/
		//if (x > sr * update_freq) {
		//	
		//	x = 0;
		//}
		//else {

		//}
	}
	wav.close();
}