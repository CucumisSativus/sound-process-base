//
// Created by Michał Gutowski on 20.03.15.
//

#ifndef _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
#define _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_


#include <vector>
#include <string>

#include "analyser.h"
#include "WavFileHander.h"
#include "Base_Plotter.h"

class PhaseSpaceAnalyser : public Analyser {
public:
    PhaseSpaceAnalyser(const WavFileHander & handler, BasePlotter * plotter, unsigned long k = 10);
    ~PhaseSpaceAnalyser();

    void plot();

private:
    std::vector<std::pair<double, double> > phaseSpace;
    BasePlotter * plotter;



};


#endif //_SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
