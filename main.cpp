// Joshua Oliver
// 8/15/23 - 
// a c++ implementation of Klatt's synthesizer

#include "model.h"
#include "wav.h"
#include <iostream>


int main() {
	wav_stream wav;
	wav.open("out1.wav");
	wav.write_header(1);
	init_model();
	int sr = 44100;
	float update_freq = 0.005;
	int x = 0;
	for (unsigned long long i = 0; i < sr; ++i) {
		//std::cout << eval_model(i) << "\n";
		wav.write_int2(eval_model(i, sr));
		//if (x > sr * update_freq) {
		//	
		//	x = 0;
		//}
		//else {

		//}
	}
	wav.close();
}