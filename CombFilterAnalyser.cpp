//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFilterAnalyser.h"
#include "fftw3.h"
#include <iostream>

CombFilterAnalyser::CombFilterAnalyser(const WavFileHander &handler, WaveFunction *function, int freqMin, int freqMax)
    : function(function), freqMin(freqMin), freqMax(freqMax)
{
    samples = handler.wholeFile();
}

CombFilterAnalyser::~CombFilterAnalyser() {
    delete function;
}

int CombFilterAnalyser::results(int frequencyStep) const {
    double* data = NULL;
    fftw_complex* out = NULL;
    fftw_plan plan;
    int N = samples.size();

    data = (double*) fftw_malloc(sizeof(double)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    std::copy( samples.begin(), samples.begin()+N-1, data );
    plan = fftw_plan_dft_r2c_1d(N,data,out,FFTW_MEASURE);

    fftw_execute(plan);

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
