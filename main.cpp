#include	<stdio.h>
#include	<string.h>

#include	<sndfile.hh>

#define		BUFFER_LEN	1024

#define		MAX_CHANNELS	6

static void process_data (double *data, int count, int channels) ;


int
main (void)
{
	static double data [BUFFER_LEN] ;

	SNDFILE	*infile, *outfile ;

	SF_INFO		sfinfo ;
	int			readcount ;
	const char	*infilename = "input.wav" ;
	const char	*outfilename = "output.wav" ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;


	if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
	{	/* Open failed so print an error message. */
		printf ("Not able to open input file %s.\n", infilename) ;
		/* Print the error message from libsndfile. */
		puts (sf_strerror (NULL)) ;
		return 1 ;
	} ;

	if (sfinfo.channels > MAX_CHANNELS)
	{	printf ("Not able to process more than %d channels\n", MAX_CHANNELS) ;
		return 1 ;
	} ;
	/* Open the output file. */
	if (! (outfile = sf_open (outfilename, SFM_WRITE, &sfinfo)))
	{	printf ("Not able to open output file %s.\n", outfilename) ;
		puts (sf_strerror (NULL)) ;
		return 1 ;
	} ;

	while ((readcount = sf_read_double (infile, data, BUFFER_LEN)))
	{	process_data (data, readcount, sfinfo.channels) ;
		sf_write_double (outfile, data, readcount) ;
	} ;

	sf_close (infile) ;
	sf_close (outfile) ;

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

