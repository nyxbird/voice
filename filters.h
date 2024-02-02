#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

// a piece of the model
struct filter {
	virtual double apply(double input) = 0;
};

struct amp_control : filter {
	// amplitude
	double amp;

	void set(double amp) {
		this->amp = amp;
	}

	double apply(double input) {
		return input * amp;
	}
};

// generates a signal with a specifed frequency and bandwidth
struct resonator : filter {
	// frequency and bandwidth
	double f, bw;
	// coefficients of input, y1, and y2
	double a, b, c;
	// previous and before-previous term
	double y1 = 0, y2 = 0;

	void set(double f, double bw) {
		this->f = f;
		this->bw = bw;
	}

	void calc_coeff(double t) {
		c = -exp(-2 * M_PI * bw * t);
		b = 2 * exp(-M_PI * bw * t) * cos(2 * M_PI * f * t);
		a = 1 - b - c;
		std::cout << a << ", " << b << ", " << c << "\n";
	}

	double apply(double input) {
		double y0 = a * input + b * y1 + c * y2;
		y2 = y1;
		y1 = y0;
		return y0;
	}
};

struct antiresonator : filter {
	// frequency and bandwidth
	double f, bw;
	// coefficients of input, x1, and x2
	double a, b, c;
	// previous and before-previous term
	double x1 = 0, x2 = 0;

	void set(double f, double bw) {
		this->f = f;
		this->bw = bw;
	}

	void calc_coeff(float t) {
		double c0 = -exp(-2 * M_PI * bw * t);
		double b0 = 2 * exp(-M_PI * bw * t) * cos(2 * M_PI * f * t);
		double a0 = 1 - b - c;
		a = 1 / a0;
		b = -b0 / a0;
		c = -c0 * a0;
		std::cout << a << ", " << b << ", " << c << "\n";
	}

	double apply(double input) {
		double y0 = a * input + b * x1 + c * x2;
		x2 = x1;
		x1 = input;
		return y0;
	}
};

struct low_pass : filter {
	double y1 = 0;

	double apply(double input) {
		double y0 = input + y1;
		y1 = y0;
		return y0;
	}
};

struct modulator : filter {
	int t0;
	int x = 0;
	bool on;
	sine_gen sine;

	void set(double f0, double av, int sr) {
		on = av > 0 && f0 > 0;
		if(on) t0 = sr / f0;
		sine = sine_gen();
		sine.set(f0, 1, sr);
	}

	double apply(double input) {
		if (on) {
			return input * (sine.run() / sine.v);
		}
		else return input;
	}
};

struct impulse_gen {
	int t0;
	double v;
	int x = 0;
	bool on;

	void set(double f0, double av, int sr) {
		on = av > 0 && f0 > 0;
		if (on) {
			t0 = sr / f0;
			v = av;
		}
	}

	double run() {
		if (x >= t0) {
			x = 0;
			return v;
		}
		else {
			++x;
			return 0;
		}
	}
};

struct sine_gen {
	int t0;
	double v;
	int x = 0;

	void set(double f0, double av, int sr) {
		t0 = sr / f0;
		v = av;
	}

	double run() {
		++x;
		return v * sin((double)x / t0 * 2 * M_PI);
	}
};

// returns a random double between -1 and 1
double randd() {
	return (double)rand() / RAND_MAX * 2 - 1;
}

struct white_noise {
	double v;
	int x = 0;

	void set(double a) {
		this->v = v;
	}

	double run() {
		return ((float)rand()/RAND_MAX*2-1)*v/2;
	}
};

struct gauss_rng {
	double v;

	void set(double v) {
		this->v = v;
	}

	// approximates gaussian distribution by averaging 16 numbers
	double run() {
		double s = 0;
		for (int i = 0; i < 16; ++i) {
			s += randd() / 16 * v/2;
		}
		return s;
	}
};