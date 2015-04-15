//
// Created by Michał Gutowski on 20.03.15.
//

#ifndef _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
#define _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_


#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <tuple>

#include "analyser.h"
#include "WavFileHander.h"
#include "Base_Plotter.h"
class PhaseSpaceAnalyser : public Analyser {
public:
    PhaseSpaceAnalyser(const WavFileHander &handler, BasePlotter *plotter, unsigned long k,
                       unsigned long batch_size = 1024);
    ~PhaseSpaceAnalyser();

    void plot(unsigned long start, unsigned long samples_count) const;

    std::vector<double> results();
private:
    bool breakIteration(unsigned long iterations_num, double current_x, double current_y, double current_z,
                        double first_x,
                        double first_y, double first_z);

    PointsVector phaseSpace;
    BasePlotter * plotter;
    std::vector<unsigned long> iterationsCounts;
    int samplingRate;



};


#endif //_SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
