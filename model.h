#pragma once
#include "params.h"
#include "filters.h"

//int eval_model() {
//
//}

//int eval_resonator() {
//
//}

white_noise wn;
impulse_gen ig;
sine_gen sine;

gauss_rng rng;

resonator rgp;
antiresonator rgz;
resonator rgs;

amp_control av;
amp_control avs;
low_pass lpf;

modulator mod;

void init_model(int sr) {
	//wn.set(8000);
	ig.set(200, 16000, sr);
	////ig.set(200, 16000, 10000);
	////sine.set(200, 16000, 44100);
	//
	//rgp.set(0, 100);
	//rgp.calc_coeff((double)1 / 20000);
	////rgp.calc_coeff((float)1 / 5000);

	rgp.set(0, 100);
	rgp.calc_coeff((double)4 / sr);

	rgz.set(1500, 6000);
	rgz.calc_coeff((double)4 / sr);

	rgs.set(0, 200);
	rgs.calc_coeff((double)4 / sr);

	rng.set(16000);
	mod.set(100, )
}

void update_model() {
	//ig.calc(400, 500, 44100);
	//rgp.calc_coeff((float)1 / 10000);
}

int eval_model(unsigned long long t, int sr) {
	// voicing source
	//float a = rgp.apply(ig.run());
	//float a = lpf.apply(ig.run());
	//return a;
	//return av.apply(rgz.apply(a)) + avs.apply(rgs.apply(a));
	//return a;
	//return rgp.apply(wn.run());
	//return rgz.apply(wn.run());
	//return rgz.apply(rgp.apply(ig.run()));
	//return rgz.apply(rgp.apply(ig.run()));
	//return rgp.apply(ig.run());
	//return rgz.apply(ig.run());
	//return ig.run();
	//return sine.run();
	//return rgz.apply(sine.run());

	//return rgs.apply(rgp.apply(ig.run()));
	//return rgz.apply(rgp.apply(ig.run()));
	//return rgp.apply(ig.run());

	//return rng.run();
	return mod.apply(rng.run());
}