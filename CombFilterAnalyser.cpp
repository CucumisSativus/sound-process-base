//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFilterAnalyser.h"

CombFilterAnalyser::CombFilterAnalyser(const WavFileHander &handler, WaveFunction *function, int freqMin, int freqMax)
    : function(function), freqMin(freqMin), freqMax(freqMax)
{
    samples = handler.wholeFile();
}

CombFilterAnalyser::~CombFilterAnalyser() {
    delete function;
}

int CombFilterAnalyser::results(int frequencyStep) const {
    double max = -1 * std::numeric_limits<double>::max();
    int result = 0;
    double sum = 0;
    for(int frequency = freqMin; frequency < freqMax; frequency += frequencyStep){
        for(unsigned long sample = 0; sample < samples.size(); ++sample) {
            sum += function->compute(sample, frequency) * samples[sample];

        }
        std::cout << "Frequency: " << frequency << " sum: " << sum << std::endl;
        if(sum > max){
            max = sum;
            result = frequency;
        }
        sum = 0;
    }
    return result;
}
