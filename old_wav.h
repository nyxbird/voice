///*************************************\
//* This is the file from the old_voice *
//* project. It's here for reference,   *
//* not to be used.                     *
//\*************************************/
//#pragma once
//#pragma once
//#include <fstream>
//#include <vector>
//#include "instrument.h"
//using namespace std;
//
//struct wav {
//	int channels = 1;
//	int sample_rate = 44100;
//	int bits_per_sample = 16;
//
//	double length = 2;
//
//	vector<instrument*> instruments;
//
//	void write_file(fstream& file) {
//		write_header(file);
//		write_data(file);
//	}
//
//	void write_header(fstream& file) {
//		write_string(file, "RIFF");
//		write_int4(file, get_file_length());
//		write_string(file, "WAVE");
//		write_string(file, "fmt ");
//		write_int4(file, 16); // length of above format data
//		write_int2(file, 1); // type of format (1 is pcm)
//		write_int2(file, channels); // number of channels
//		write_int4(file, sample_rate); // sample write
//		write_int4(file, sample_rate * bits_per_sample * channels / 8); // byte rate
//		write_int2(file, bits_per_sample * channels / 8); // bytes per complete sample
//		write_int2(file, bits_per_sample); // bits per sample
//		write_string(file, "data");
//		write_int4(file, get_data_length()); // length of data
//	}
//
//	void write_data(fstream& file) {
//		// //(attempt to) write a square wave
//		//int count = 0;
//		//bool on = false;
//		//int j = 200;
//		//for (int i = 0; i < square_wav_secs * sample_rate; ++i) {
//		//	if (on) {
//		//		write_int2(file, 0xffff);
//		//	}
//		//	else {
//		//		write_int2(file, 0);
//		//	}
//		//	++count;
//		//	if (count == j) {
//		//		count = 0;
//		//		on = !on;
//		//		j--;
//		//	}
//		//}
//		//square_wave sw = square_wave(128, 440, 0.5);
//		//square_wave c = square_wave(0, 4, 0x2000, 261.6256, 0.5);
//		//square_wave e = square_wave(1, 4, 0x2000, 329.6276, 0.5);
//		//square_wave g = square_wave(2, 4, 0x2000, 391.9954, 0.5);
//		//sine_wave c = sine_wave(0, 4, 0x2000, 261.6256, 0.5);
//		//sine_wave e = sine_wave(1, 4, 0x2000, 329.6276, 0.5);
//		//sine_wave g = sine_wave(2, 4, 0x2000, 391.9954, 0.5);
//		//overtoned c = square_toned(0, 1, 0x2000, 261.6256, 100);
//		//square_wave swc = square_wave(1, 2, 0x2000, 261.6256, 0.5);
//
//		//vector<square_wave> waves;
//
//		//for (int i = 0; i < 10; ++i) {
//		//	waves.push_back(square_wave(i * 0.4, (i + 1) * 0.4, 0x2000, 261.6256, i / 10));
//		//	instruments.push_back(&waves[i]);
//		//	cout << &waves[i] << "\n";
//		//}
//
//		//square_wave w0 = square_wave(0 * 0.4, 1 * 0.4, 0x2000, 261.6256, 0.0);
//		//square_wave w1 = square_wave(1 * 0.4, 2 * 0.4, 0x2000, 261.6256, 0.1);
//		//square_wave w2 = square_wave(2 * 0.4, 3 * 0.4, 0x2000, 261.6256, 0.2);
//		//square_wave w3 = square_wave(3 * 0.4, 4 * 0.4, 0x2000, 261.6256, 0.3);
//		//square_wave w4 = square_wave(4 * 0.4, 5 * 0.4, 0x2000, 261.6256, 0.4);
//		//square_wave w5 = square_wave(5 * 0.4, 6 * 0.4, 0x2000, 261.6256, 0.5);
//		//square_wave w6 = square_wave(6 * 0.4, 7 * 0.4, 0x2000, 261.6256, 0.6);
//		//square_wave w7 = square_wave(7 * 0.4, 8 * 0.4, 0x2000, 261.6256, 0.7);
//		//square_wave w8 = square_wave(8 * 0.4, 9 * 0.4, 0x2000, 261.6256, 0.8);
//		//square_wave w9 = square_wave(9 * 0.4, 10 * 0.4, 0x2000, 261.6256, 0.9);
//
//		//instruments.push_back(&w0);
//		//instruments.push_back(&w1);
//		//instruments.push_back(&w2);
//		//instruments.push_back(&w3);
//		//instruments.push_back(&w4);
//		//instruments.push_back(&w5);
//		//instruments.push_back(&w6);
//		//instruments.push_back(&w7);
//		//instruments.push_back(&w8);
//		//instruments.push_back(&w9);
//		//instruments.push_back(&swc);
//		//instruments.push_back(&c);
//		//instruments.push_back(&e);
//		//instruments.push_back(&g);
//		for (int i = 0; i < length * sample_rate; ++i) {
//			int sum = 0;
//			for (auto it = instruments.begin(); it != instruments.end(); ++it) {
//				if (i >= (*it)->start * sample_rate && i <= (*it)->end * sample_rate) {
//					sum += (*it)->value(i, sample_rate);
//				}
//			}
//			if (i % 100 == 0) cout << length * sample_rate << " " << i << " " << sum << "\n";
//			write_int2(file, sum);
//		}
//	}
//
//	void write_num_data(fstream& file) {
//		for (int i = 0; i < length * sample_rate; ++i) {
//			int sum = 0;
//			for (auto it = instruments.begin(); it != instruments.end(); ++it) {
//				if (i >= (*it)->start * sample_rate && i <= (*it)->end * sample_rate) {
//					sum += (*it)->value(i, sample_rate);
//				}
//			}
//			if (i % 100 == 0) cout << length * sample_rate << " " << i << " " << sum << "\n";
//			file << sum << ",";
//		}
//	}
//
//	void add_instrument(instrument* i) {
//		instruments.push_back(i);
//	}
//
//	int get_file_length() {
//		//return
//		//	44 + // header
//		//	bits_per_sample * sample_rate;
//		return bits_per_sample / 8 * sample_rate * channels * length + 36;
//		//return 44 + length * sample_rate * 
//		//return 40;
//	}
//
//	int get_data_length() {
//		return bits_per_sample / 8 * sample_rate * channels * length;
//	}
//
//	// write a string to the file
//	void write_string(fstream& file, string s) {
//		for (char c : s) {
//			file.put(c);
//		}
//	}
//
//	// write a 4-byte int to the file
//	void write_int4(fstream& file, unsigned int n) {
//		file.put(n);
//		file.put(n / 0x100);
//		file.put(n / 0x10000);
//		file.put(n / 0x1000000);
//	}
//
//	// write a 2-byte int to the file 
//	void write_int2(fstream& file, unsigned n) {
//		file.put(n);
//		file.put(n / 0x100);
//	}
//};