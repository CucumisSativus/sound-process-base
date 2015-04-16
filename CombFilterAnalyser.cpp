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

std::vector<double> CombFilterAnalyser::results(int frequencyStep) {
    std::vector<double> analysisResults;
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

        double result = (double)calculateCombFrequency(frequencyStep, samplesBatch, transformedSamplesBatch, dataSize);
        std::cout << "batches from: " << batch << " to :" << batch + dataSize << " frequency: " << result << std::endl;


        analysisResults.push_back(result);
        fftw_free(samplesBatch);
        fftw_free(transformedSamplesBatch);

    }
    fftw_complex * frequencies = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * analysisResults.size());
    for(unsigned long i = 0; i < analysisResults.size(); ++i){
        frequencies[i][0] = analysisResults[i];
        frequencies[i][1] = 0;
    }
//    double * output = (double *) fftw_malloc(sizeof(double) * analysisResults.size());
//    fftw_plan plan = fftw_plan_dft_c2r_1d(analysisResults.size(), frequencies, output, FFTW_MEASURE);
//    std::vector<double> after_fftw;
//    after_fftw.assign(output, output + analysisResults.size());

    return analysisResults;
}

int CombFilterAnalyser::calculateCombFrequency(int frequencyStep, double *samplesBatch,
                                               fftw_complex *transformedSamplesBatch, int dataSize) {
    fftw_complex max;
    max[0] = 0;
    max[1] = 0;
    int result = 0;
    fftw_complex sum;
    sum[0] = 0;
    sum[1] = 0;
    for (int frequency = freqMin; frequency < freqMax; frequency += frequencyStep) {
        double *functionData;
        fftw_complex *transformedFunctionData;
        calculateFunctionFft(samplesBatch, dataSize, frequency, functionData, transformedFunctionData);
        for (unsigned long sampleIndex = 0; sampleIndex < dataSize; ++sampleIndex) {
            sum[0] += functionData[sampleIndex] * transformedSamplesBatch[sampleIndex][0];
            sum[1] += functionData[sampleIndex] * transformedSamplesBatch[sampleIndex][1];

        }
        double absoluteSum = std::sqrt(sum[0] * sum[0] + sum[1] * sum[1]);
        double absoluteMax = std::sqrt(max[0] * max[0] + max[1] * max[1]);
        if (absoluteSum > absoluteMax) {
            max[0] = sum[0];
            max[1] = sum[1];
            result = frequency;
        }
        fftw_free(functionData);
        fftw_free(transformedFunctionData);
        sum[0] = 0;
        sum[1] = 0;
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

