#include 	<iostream>
#include "WavFileHander.h"
#include "GnuplotPlotter.h"
#include "PhaseSpaceAnalyser.h"
#include "CombFilterAnalyser.h"
#include "CombFunction.h"
#include <cmath>

std::vector<double> generateSoundSamples(std::vector<double> frequencies, int batchSize, int sampleRate) {
    std::vector<double> samples(frequencies.size(), 0);
    int counter = 0;
    double phaseAngle = 0;
    for (std::vector<double>::iterator freq = frequencies.begin(); freq != frequencies.end(); ++freq) {

        for (int i = 0; i < batchSize; i++) {
            samples.push_back(std::sin(phaseAngle));
            phaseAngle += (double) *freq / 44100 * 2 * M_PI;
        }
        counter += batchSize;
    }
    return samples;
}

int main(void) {
    const char *infilename = "input.wav";
    const char *outfilename = "output.wav";

    WavFileHander hander(infilename, outfilename);

    int batchSize = 2048;
    PhaseSpaceAnalyser analyser(hander, nullptr, 10, batchSize, 5);
    std::vector<double> phaseSpaceResults = analyser.results();
    int counter = 0;
    for (std::vector<double>::const_iterator it = phaseSpaceResults.cbegin(); it != phaseSpaceResults.cend(); ++it) {
        std::cout << ++counter << " Phase space: " << *it << std::endl;
    }
    hander.writeToOutFile(generateSoundSamples(phaseSpaceResults, batchSize, hander.samplerate()));

    CombFilterAnalyser analyser2(hander, new CombFunction(), 200, 2200, batchSize);
    std::vector<double> combFilterResults = analyser2.results(1);
    counter = 0;
    for (std::vector<double>::const_iterator it = combFilterResults.cbegin(); it != combFilterResults.cend(); ++it) {
        std::cout << ++counter << " Comb filter: " << *it << std::endl;
    }
    double totalErro = 0;
    for (unsigned long i = 0; i < phaseSpaceResults.size(); ++i) {
        double error = std::abs(phaseSpaceResults[i] - combFilterResults[i]);
        std::cout << "error: " << error << std::endl;
        totalErro += error;
    }
    std::cout << "Total error: " << totalErro << std::endl;
    return 0;
}

