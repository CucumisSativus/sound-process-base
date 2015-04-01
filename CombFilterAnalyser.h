//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
#define SOUND_PROCESS_BASE_COMBFILTERANALYSER_H

#include <vector>

#include "WaveFunction.h"
#include "WavFileHander.h"

typedef std::vector<double> CombVector;

class CombFilterAnalyser {
public:
    CombFilterAnalyser(const WavFileHander & handler, WaveFunction * function, int freqMin = 16, int freqMax = 22000);
    ~CombFilterAnalyser();
    int results();
private:
    CombVector samples;
    WaveFunction * function;
    int freqMin;
    int freqMax;
};


#endif //SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
