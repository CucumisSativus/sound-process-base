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
//	PhaseSpaceAnalyser analyser(hander, new GnuplotPlotter("out.dat"), 10, 10000);
	PhaseSpaceAnalyser analyser(hander, nullptr, 10, 10000);

	std::vector<double> phaseSpaceResults = analyser.results();
	for (std::vector<double>::const_iterator it = phaseSpaceResults.cbegin(); it != phaseSpaceResults.cend(); ++it) {
		std::cout << "Phase space: " << *it << std::endl;
	}

	CombFilterAnalyser analyser2(hander, new CombFunction(), 16, 22000, 10000);
	std::vector<int> combFilterResults = analyser2.results(10);
	for (std::vector<int>::const_iterator it = combFilterResults.cbegin(); it != combFilterResults.cend(); ++it) {
		std::cout << "Comb filter: " << *it << std::endl;
	}
	return 0;
}

