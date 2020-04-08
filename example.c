/*
This example program makes use of the simple
sound library to generate a sine wave and write the
output to sound.wav.
For complete documentation on the library, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile
Go ahead and modify this program for your own purposes.
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "wavfile.h"

// (8000 * 2) * 10s
const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND * WAVFILE_CHANNELS) * WAVFILE_PLAY_SECONDS;

int main()
{
	short* waveform		= NULL;
	double frequency	= 1500.0;
	int volume		= 32000;
	int length		= NUM_SAMPLES;
	int i;
	FILE * f		= NULL;

	// 16bit X2
	waveform = (short *)malloc(sizeof(short) * NUM_SAMPLES);

	for(i = 0; i < length / WAVFILE_CHANNELS; i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;

		// start a frame data
		if (WAVFILE_CHANNELS == 2) {
			// left channel
			waveform[i * 2] =  volume * sin(frequency * t * 2 * M_PI);
			// right channel
			waveform[i * 2 + 1] = volume / 2 * sin((frequency / 3) * t * 2 * M_PI);
		} else {
			// single channel
			waveform[i] = volume * sin(frequency * t * 2 * M_PI);
		}
		// end a frame data
	}

	f = wavfile_open("sound.wav");
	if(!f) {
		printf("couldn't open sound.wav for writing: %s", strerror(errno));
		return 1;
	}

	wavfile_write(f, waveform, length);
	wavfile_close(f);

	free(waveform);

	return 0;
}
