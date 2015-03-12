#include 	<iostream>
#include	<sndfile.hh>

#define		BUFFER_LEN	1024

#define		MAX_CHANNELS	6

static void process_data (double *data, int count, int channels) ;


int
main (void)
{
	static double data [BUFFER_LEN] ;

	int			readcount ;
	const char	*infilename = "input.wav" ;
	const char	*outfilename = "output.wav" ;
	SndfileHandle infileHandle;
	SndfileHandle outfileHandle;

	if (! (infileHandle = SndfileHandle(infilename, SFM_READ)))
	{
		std::cout << "Not able to open input file " << infilename << std::endl;
		puts (sf_strerror (NULL)) ;
		return 1 ;
	} ;

	if (infileHandle.channels() > MAX_CHANNELS)
	{
		std::cout << "Not able to process more than %d channels "<<  MAX_CHANNELS;
		return 1 ;
	} ;
	/* Open the output file. */
	if (! (outfileHandle = SndfileHandle(outfilename, SFM_WRITE, infileHandle.format(), infileHandle.channels(), infileHandle.samplerate())))
	{
		std:: cout << "Not able to open output file " << outfilename;
		puts (sf_strerror (NULL)) ;
		return 1 ;
	} ;

	while ((readcount = infileHandle.read(data, BUFFER_LEN)))
	{	process_data (data, readcount, infileHandle.channels()) ;
		outfileHandle.write(data, readcount) ;
	} ;

	return 0 ;
} /* main */

static void
process_data (double *data, int count, int channels)
{	double channel_gain [MAX_CHANNELS] = { 2.5, 0.8, 0.1, 0.4, 0.4, 0.9 } ;
	int k, chan ;

	for (chan = 0 ; chan < channels ; chan ++)
		for (k = chan ; k < count ; k+= channels)
			data [k] *= channel_gain [chan] ;

	return ;
} /* process_data */

