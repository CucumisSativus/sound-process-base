#include 	<iostream>
#include "WavFileHander.h"
#include "GnuplotPlotter.h"
#include "PhaseSpaceAnalyser.h"
#include "CombFilterAnalyser.h"
#include "CombFunction.h"

int main(void) {
	const char *infilename = "input.wav";
	const char *outfilename = "output.wav";

	WavFileHander hander(infilename, outfilename);
	PhaseSpaceAnalyser analyser(hander, new GnuplotPlotter("out.dat"), 10, 10000);
	std::vector<double> phaseSpaceResults = analyser.results();
	for (std::vector<double>::const_iterator it = phaseSpaceResults.cbegin(); it != phaseSpaceResults.cend(); ++it) {
		std::cout << "Phase space: " << *it << std::endl;
	}

	CombFilterAnalyser analyser2(hander, new CombFunction());
	std::cout << "Comb filter: " << analyser2.results(10) << std::endl;
	return 0;
}

