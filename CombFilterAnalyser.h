//
// Created by Michał Gutowski on 01.04.15.
//

#ifndef SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
#define SOUND_PROCESS_BASE_COMBFILTERANALYSER_H

#include <vector>
#include <limits>
#include <fftw3.h>
#include <cmath>
#include "WaveFunction.h"
#include "WavFileHander.h"

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

    void calculateFft(double *data, fftw_complex *out, int dataSize);

    void calculateFunctionFft(double *samplesBatch, int dataSize, int frequency, double *&functionData,
                              fftw_complex *&transformedFunctionData);

    int calculateCombFrequency(int frequencyStep, double *samplesBatch, fftw_complex *transformedSamplesBatch,
                               int dataSize);
};


#endif //SOUND_PROCESS_BASE_COMBFILTERANALYSER_H
