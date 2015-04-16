//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFilterAnalyser.h"

CombFilterAnalyser::CombFilterAnalyser(const WavFileHander &handler, WaveFunction *function, int freqMin,
                                       int freqMax, unsigned long batchSize)
        : function(function), freqMin(freqMin), freqMax(freqMax), batchSize(batchSize) {
    samples = handler.wholeFile();
}

CombFilterAnalyser::~CombFilterAnalyser() {
    delete function;
}

std::vector<int> CombFilterAnalyser::results(int frequencyStep) {
    std::vector<int> results;
    for (unsigned long batch = 0; batch < samples.size(); batch += batchSize) {
        double *samplesBatch = NULL;
        fftw_complex *transformedSamplesBatch = NULL;
        int dataSize = batch + batchSize < samples.size() ? batchSize : samples.size() - batch;

        samplesBatch = (double *) fftw_malloc(sizeof(double) * dataSize);
        transformedSamplesBatch = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * dataSize);
        if (batch + dataSize < samples.size()) {
            copy(samples.begin() + batch, samples.begin() + batch + dataSize - 1, samplesBatch);
        }
        else {
            copy(samples.begin() + batch, samples.end(), samplesBatch);
        }
        calculateFft(samplesBatch, transformedSamplesBatch, dataSize);

        int result = calculateCombFrequency(frequencyStep, samplesBatch, transformedSamplesBatch, dataSize);
        std::cout << "batches from: " << batch << " to :" << batch + dataSize << " frequency: " << result << std::endl;
        results.push_back(result);
        fftw_free(samplesBatch);
        fftw_free(transformedSamplesBatch);

    }
    return results;
}

int CombFilterAnalyser::calculateCombFrequency(int frequencyStep, double *samplesBatch,
                                               fftw_complex *transformedSamplesBatch, int dataSize) {
    double max = -1 * std::numeric_limits<double>::max();
    int result = 0;
    double sum = 0;
    for (int frequency = freqMin; frequency < freqMax; frequency += frequencyStep) {
        double *functionData;
        fftw_complex *transformedFunctionData;
        calculateFunctionFft(samplesBatch, dataSize, frequency, functionData, transformedFunctionData);
        for (unsigned long sampleIndex = 0; sampleIndex < dataSize; ++sampleIndex) {
            sum += functionData[sampleIndex] * transformedSamplesBatch[sampleIndex][0];

        }
        if (sum > max) {
            max = sum;
            result = frequency;
        }
        fftw_free(functionData);
        fftw_free(transformedFunctionData);
        sum = 0;
    }
    return result;
}

void CombFilterAnalyser::calculateFunctionFft(double *samplesBatch, int dataSize, int frequency, double *&functionData,
                                              fftw_complex *&transformedFunctionData) {
    functionData = (double *) fftw_malloc(sizeof(double) * dataSize);
    transformedFunctionData = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * dataSize);
    for (unsigned long sampleIndex = 0; sampleIndex < dataSize; ++sampleIndex) {
        functionData[sampleIndex] = function->compute(sampleIndex, frequency);

    }
    calculateFft(functionData, transformedFunctionData, dataSize);
}

void CombFilterAnalyser::calculateFft(double *data, fftw_complex *out, int dataSize) {
    fftw_plan plan = fftw_plan_dft_r2c_1d(dataSize, data, out, FFTW_MEASURE);
    fftw_execute(plan);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

