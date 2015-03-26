//
// Created by Michał Gutowski on 20.03.15.
//

#include "PhaseSpaceAnalyser.h"


PhaseSpaceAnalyser::PhaseSpaceAnalyser(const WavFileHander &handler, BasePlotter *plotter, unsigned long k)
:   plotter(plotter)
{
    sampleVector samples = handler.wholeFile();
    std::cout << "In Analyser constructor, samples size" << samples.size() << std::endl;
    phaseSpace.reserve(samples.size());

    for(unsigned long i = k; i < samples.size(); ++i){
        phaseSpace.push_back(std::pair<double, double>(samples[i], samples[i-k]));
    }
    std::cout << "In Analyser constructor, phase space size" << phaseSpace.size() << std::endl;
}

PhaseSpaceAnalyser::~PhaseSpaceAnalyser() {
    delete plotter;
}

void PhaseSpaceAnalyser::plot() {
    PointsVector::const_iterator begin = phaseSpace.begin();
    PointsVector::const_iterator end = phaseSpace.begin() + 300;
    PointsVector subVector(begin, end);
    std::cout << "In Analyser plot, subVector size" << subVector.size() << std::endl;
    plotter->plot(subVector);
}
