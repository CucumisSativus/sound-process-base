#include 	<iostream>
#include "WavFileHander.h"

static void process_data(double *data, int count, int channels);


int
main(void) {

	int readcount;
	const char *infilename = "input.wav";
	const char *outfilename = "output.wav";


	WavFileHander hander(infilename, outfilename);
	hander.writeToOutFile();

	return 0;
}

/* main */

//static void
//process_data(double *data, int count, int channels) {
//	double channel_gain[MAX_CHANNELS] = {2.5, 0.8, 0.1, 0.4, 0.4, 0.9};
//	int k, chan;
//
//	for (chan = 0; chan < channels; chan++)
//		for (k = chan; k < count; k += channels)
//			data[k] *= channel_gain[chan];
//
//	return;
//} /* process_data */

