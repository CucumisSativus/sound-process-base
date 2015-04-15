//
// Created by Michał Gutowski on 20.03.15.
//

#include "PhaseSpaceAnalyser.h"


PhaseSpaceAnalyser::PhaseSpaceAnalyser(const WavFileHander &handler, BasePlotter *plotter, unsigned long k,
                                       unsigned long batch_size)
        : plotter(plotter) {
    samplingRate = handler.samplerate();
    sampleVector samples = handler.wholeFile();
    for (unsigned long batch = 2 * k; batch < samples.size(); batch += batch_size) {
        double first_x = samples[batch];
        double first_y = samples[batch - k];
        double first_z = samples[batch - 2 * k];
        unsigned long iterations_num = 0;

        for (unsigned long sample = batch + 1; sample < samples.size() && sample < batch + batch_size; ++sample) {
            double &x = samples[sample];
            double &y = samples[sample - k];
            double &z = samples[sample - 2 * k];

            if (breakIteration(iterations_num, x, y, z, first_x, first_y, first_z)) {
                break;
            }
            phaseSpace.push_back(std::make_tuple(x, y, z));
            iterations_num++;

        }
        if (plotter) {
            plot(batch - k, batch - k + iterations_num);
        }
        iterationsCounts.push_back(iterations_num);
    }
}

PhaseSpaceAnalyser::~PhaseSpaceAnalyser() {
    if (plotter) {
        delete plotter;
    }
}

void PhaseSpaceAnalyser::plot(unsigned long start, unsigned long samples_count) const {
    PointsVector::const_iterator begin = phaseSpace.begin() + start;
    PointsVector::const_iterator end = phaseSpace.begin() + samples_count;
    PointsVector subVector(begin, end);
    plotter->plot(subVector);
}

bool PhaseSpaceAnalyser::breakIteration(unsigned long iterations_num, double current_x, double current_y,
                                        double current_z, double first_x,
                                        double first_y, double first_z) {
    const double tolerance = 0.01;
    const unsigned long minIterationNum = 50;

    if (iterations_num < minIterationNum) {
        return false;
    }

    double distance_x = (current_x - first_x) * (current_x - first_x);
    double distance_y = (current_y - first_y) * (current_y - first_y);
    double distance_z = (current_z - first_z) * (current_z - first_z);

    double distance = std::sqrt(distance_x + distance_y + distance_z);

    return distance <= tolerance;
}

std::vector<double> PhaseSpaceAnalyser::results() {
    std::vector<double> result;
    for (std::vector<unsigned long>::const_iterator it = iterationsCounts.cbegin();
         it != iterationsCounts.cend(); ++it) {
        result.push_back((double) samplingRate / (*it));
    }
    return result;
}
