//
// Created by Michał Gutowski on 20.03.15.
//

#ifndef _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
#define _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_


#include <vector>
#include <string>
#include <set>
#include <cmath>

#include "analyser.h"
#include "WavFileHander.h"
#include "Base_Plotter.h"
class PhaseSpaceAnalyser : public Analyser {
public:
    PhaseSpaceAnalyser(const WavFileHander & handler, BasePlotter * plotter, unsigned long k = 10);
    ~PhaseSpaceAnalyser();

    void plot() const;
    double results() const;
private:
    bool breakIteration(double current_x, double current_y, double first_x, double first_y);

    std::vector<std::pair<double, double> > phaseSpace;
    BasePlotter * plotter;
    unsigned long iterations;
    sf_count_t samplingRate;



};


#endif //_SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
