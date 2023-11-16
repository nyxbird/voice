#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

// a piece of the model
struct filter {
	virtual float apply(float input) = 0;
};

struct amp_control : filter {

};

// generates a signal with a specifed frequency and bandwidth
struct resonator : filter {
	// frequency and bandwidth
	float f, bw;
	// coefficients of input, y1, and y2
	float a, b, c;
	// previous and before-previous term
	float y1 = 0, y2 = 0;

	void set(float f, float bw) {
		this->f = f;
		this->bw = bw;
	}

	void calc_coeff(float t) {
		c = -exp(-2 * M_PI * bw * t);
		b = 2 * exp(-M_PI * bw * t) * cos(2 * M_PI * f * t);
		a = 1 - b - c;
		std::cout << a << ", " << b << ", " << c << "\n";
	}

	float apply(float input) {
		float y0 = a * input + b * y1 + c * y2;
		y2 = y1;
		y1 = y0;
		return y0;
	}
};

struct antiresonator : filter {
	// frequency and bandwidth
	float f, bw;
	// coefficients of input, x1, and x2
	float a, b, c;
	// previous and before-previous term
	float x1 = 0, x2 = 0;

	float calc_coeff(float t) {
		float c0 = -exp(-2 * M_PI * bw * t);
		float b0 = 2 * exp(-M_PI * bw * t) * cos(2 * M_PI * f * t);
		float a0 = 1 - b - c;
		a = 1 / a0;
		b = -b0 / a0;
		c = -c0 * a0;
	}

	float apply(float input) {
		float y0 = a * input + b * x1 + c * x2;
		x2 = x1;
		x1 = input;
		return y0;
	}
};

struct low_pass : filter {
	float y1 = 0;

	float apply(float input) {
		float y0 = input + y1;
		y1 = y0;
		return y0;
	}
};

struct impulse_gen {
	int t0;
	float v;
	int x = 0;

	void set(float f0, float av, int sr) {
		t0 = sr / f0;
		v = av;
	}

	float run() {
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