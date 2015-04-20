//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
#define SOUND_PROCESS_BASE_COMBFILTERANALYSER_H

#include <vector>
#include <limits>
#include <fftw3.h>
#include <cmath>
#include <thread>
#include "WaveFunction.h"
#include "WavFileHander.h"
#include "GnuplotPlotter.h"

typedef std::vector<double> CombVector;

class CombFilterAnalyser {
public:
    CombFilterAnalyser(const WavFileHander &handler, WaveFunction *function, int freqMin,
                       int freqMax, unsigned long batchSize);
    ~CombFilterAnalyser();

    std::vector<double> results(int frequencyStep);
private:
    CombVector samples;
    WaveFunction * function;
    int freqMin;
    int freqMax;
    unsigned long batchSize;
    int samplingRate;

    void calculateFft(double *data, fftw_complex *out, int dataSize);
    int calculateCombFrequency(int frequencyStep, fftw_complex *transformedSamplesBatch, int dataSize,
                                                   int resolution);
    void prepareDataForFft(double *data, int size, int batchSize);
};


#endif //SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
