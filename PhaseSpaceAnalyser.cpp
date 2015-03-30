//
// Created by Michał Gutowski on 20.03.15.
//

#include "PhaseSpaceAnalyser.h"


PhaseSpaceAnalyser::PhaseSpaceAnalyser(const WavFileHander &handler, BasePlotter *plotter, unsigned long k)
:   plotter(plotter)
{
    samplingRate = handler.samplerate();
    sampleVector samples = handler.wholeFile();
    std::cout << "In Analyser constructor, samples size" << samples.size() << std::endl;
    phaseSpace.reserve(samples.size());

    double first_x = samples[k];
    double first_y = samples[0];

    for(iterations = k+1; iterations < samples.size(); ++iterations){
        double &x = samples[iterations];
        double &y = samples[iterations-k];

        if(breakIteration(x, y, first_x, first_y)){
            break;
        }
        phaseSpace.push_back(std::pair<double, double>(x, y));

    }
    std::cout << "In Analyser constructor, phase space size" << phaseSpace.size() << std::endl;
}

PhaseSpaceAnalyser::~PhaseSpaceAnalyser() {
    delete plotter;
}

void PhaseSpaceAnalyser::plot() {
    PointsVector::const_iterator begin = phaseSpace.begin();
    PointsVector::const_iterator end = phaseSpace.begin() + iterations;
    PointsVector subVector(begin, end);
    std::cout << "In Analyser plot, subVector size" << subVector.size() << std::endl;
    plotter->plot(subVector);
}

bool PhaseSpaceAnalyser::breakIteration(double current_x, double current_y, double first_x, double first_y) {
    const double tolerance = 0.001;
    const unsigned long minIterationNum = 50;

    if(iterations < minIterationNum){
        return false;
    }

    double distance_x = (current_x - first_x) * (current_x - first_x);
    double distance_y = (current_y - first_y) * (current_y - first_y);

    double distance = std::sqrt(distance_x + distance_y);

    return distance <= tolerance;
}

double PhaseSpaceAnalyser::results() {
    return (double)samplingRate/iterations;
}
