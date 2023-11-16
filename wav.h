#pragma once
#include <fstream>

struct wav_stream {
	int channels = 1;
	int sample_rate = 44100;
	int bits_per_sample = 16;
	std::fstream file;

	void open(std::string name) {
		file.open(name, std::ios::out | std::ios::binary);
	}

	// writes the file header based on the length in seconds
	void write_header(float length) {
		write_string("RIFF");
		write_int4(get_file_length(length));
		write_string("WAVE");
		write_string("fmt ");
		write_int4(16); // length of above format data
		write_int2(1); // type of format (1 is pcm)
		write_int2(channels); // number of channels
		write_int4(sample_rate); // sample write
		write_int4(sample_rate * bits_per_sample * channels / 8); // byte rate
		write_int2(bits_per_sample * channels / 8); // bytes per complete sample
		write_int2(bits_per_sample); // bits per sample
		write_string("data");
		write_int4(get_data_length(length)); // length of data
	}

	int get_file_length(float length) {
		return bits_per_sample / 8 * sample_rate * channels * length + 36;
	}

	int get_data_length(float length) {
		return bits_per_sample / 8 * sample_rate * channels * length;
	}

	// write a string to the file
	void write_string(std::string s) {
		for (char c : s) {
			file.put(c);
		}
	}

	// write a 4-byte int to the file
	void write_int4(unsigned long n) {
		file.put(n);
		file.put(n / 0x100);
		file.put(n / 0x10000);
		file.put(n / 0x1000000);
	}

	// write a 2-byte int to the file 
	void write_int2(unsigned n) {
		file.put(n);
		file.put(n / 0x100);
	}

	void close() {
		file.close();
	}
};