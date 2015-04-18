//
// Created by Michał Gutowski on 20.03.15.
//

#include "PhaseSpaceAnalyser.h"


PhaseSpaceAnalyser::PhaseSpaceAnalyser(const WavFileHander &handler, BasePlotter *plotter, unsigned long k,
                                           unsigned long batch_size, int dimensionsNum)
        : plotter(plotter), dimensionsNum(dimensionsNum){
    samplingRate = 44100;
    if(dimensionsNum <=0 ){
        throw std::invalid_argument("Wrong number of dimensions");
    }
    sampleVector samples = handler.wholeFile();
    for (unsigned long batch = (dimensionsNum -1) * k; batch < samples.size(); batch += batch_size) {

        std::vector<double> firstPoints;

        for(int dimension = 0; dimension < dimensionsNum ; ++dimension){
            firstPoints.push_back(samples[batch - (dimension *k)]);
        }
        unsigned long iterations_num = 0;

        for (unsigned long sample = batch + 1; sample < samples.size() && sample < batch + batch_size; ++sample) {
            std::vector<double> currentPoints;

            for(int dimension =0; dimension < dimensionsNum; ++dimension){
                currentPoints.push_back(samples[sample - (dimension * k)]);
            }
            
            if (breakIteration(iterations_num, firstPoints, currentPoints)) {
                break;
            }
            currentPoints.clear();
            iterations_num++;

        }
        if (plotter) {
            plot(batch - k, iterations_num);
        }
        phaseSpace.clear();
        iterationsCounts.push_back(iterations_num);
    }
}

PhaseSpaceAnalyser::~PhaseSpaceAnalyser() {
    if (plotter) {
        delete plotter;
    }
}

void PhaseSpaceAnalyser::plot(unsigned long start, unsigned long samples_count) const {
    PointsVector3d::const_iterator begin = phaseSpace.begin();
    PointsVector3d::const_iterator end = phaseSpace.begin()+ samples_count;
    PointsVector3d subVector(begin, end);
    plotter->plot(subVector);
}

bool PhaseSpaceAnalyser::breakIteration(unsigned long iterations_num, std::vector<double> firstPoints, std::vector<double> currentPoint) {
    const double tolerance = 0.01;
    const unsigned long minIterationNum = 50;
    if (iterations_num < minIterationNum) {
        return false;
    }
    double distancesSum = 0;
    for(int dimension =0; dimension < dimensionsNum; ++dimension){
        distancesSum += (currentPoint[dimension] - firstPoints[dimension]) * (currentPoint[dimension] - firstPoints[dimension]);
    }

    double distance = std::sqrt(distancesSum);
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
