#pragma once
#include "values.h"
#include "filters.h"

//int eval_model() {
//
//}

//int eval_resonator() {
//
//}

impulse_gen ig;
resonator rgp;
antiresonator rgz;
resonator rgs;
resonator av;
resonator avs;

void init_model() {
	ig.set(400, 2000, 44100);
	rgp.set(0, 100);
	rgp.calc_coeff((float)1 / 44100);
}

void update_model() {
	//ig.calc(400, 500, 44100);
	rgp.calc_coeff((float)1 / 44100);
}

int eval_model(unsigned long long t, int sr) {
	// voicing source
	float a = rgz.apply(rgp.apply(ig.run()));
	return a;
}