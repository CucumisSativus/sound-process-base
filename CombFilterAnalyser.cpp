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

int CombFilterAnalyser::results() {
    double max = 0;
    int maxFreq = 0;
    double sum = 0;
    for(int i = freqMin; i < freqMax; ++i){
        for(unsigned long j = 0; j < samples.size(); ++j) {
            sum = function->compute(i *j) + samples[j];
            if(sum > max){
                max = sum;
                maxFreq =i;
            }
        }
    }
    return maxFreq;
}
