//
// Created by Michał Gutowski on 20.03.15.
//

#ifndef _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
#define _SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_


#include <vector>
#include <string>

#include "analyser.h"

class PhaseSpaceAnalyser : public Analyser {
public:
    PhaseSpaceAnalyser();

private:
    std::vector<std::pair<double, double> > phaseSpace;


};


#endif //_SOUND_PROCESS_BASE_PHASESPACEANALYSER_H_
