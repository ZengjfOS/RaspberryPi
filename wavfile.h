/*
A simple sound library for CSE 20211 by Douglas Thain.
This work is made available under the Creative Commons Attribution license.
https://creativecommons.org/licenses/by/4.0/

For course assignments, you should not change this file.
For complete documentation, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile
*/

#ifndef WAVFILE_H
#define WAVFILE_H

#include <stdio.h>
#include <inttypes.h>

FILE * wavfile_open( const char *filename );
void wavfile_write( FILE *file, short data[], int length );
void wavfile_close( FILE * file );

#define WAVFILE_SAMPLES_PER_SECOND  8000
#define WAVFILE_CHANNELS            2
#define WAVFILE_PLAY_SECONDS        10

#endif
