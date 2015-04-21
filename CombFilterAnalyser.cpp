//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFilterAnalyser.h"
#include "GnuplotPlotter.h"

CombFilterAnalyser::CombFilterAnalyser(const WavFileHander &handler, WaveFunction *function, int freqMin,
                                       int freqMax, unsigned long batchSize)
        : function(function), freqMin(freqMin), freqMax(freqMax), batchSize(batchSize), samplingRate(44100) {
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
            copy(samples.begin() + batch, samples.begin() + batch + dataSize, samplesBatch);
        }
        else {
            copy(samples.begin() + batch, samples.end(), samplesBatch);
        }
        prepareDataForFft(samplesBatch, dataSize, batchSize);
        calculateFft(samplesBatch, transformedSamplesBatch, dataSize);
        double result = (double) calculateCombFrequency(frequencyStep, transformedSamplesBatch, dataSize, samplingRate/batchSize);
        std::cout << "batches from: " << batch << " to :" << batch + dataSize << " frequency: " << result << std::endl;


        analysisResults.push_back(result);
        fftw_free(samplesBatch);
        fftw_free(transformedSamplesBatch);

    }
    return analysisResults;
}

int CombFilterAnalyser::calculateCombFrequency(int frequencyStep, fftw_complex *transformedSamplesBatch, int dataSize,
                                               int resolution) {
    double max = 0;
    int result = 0;
    double sum = 0;
    GnuplotPlotter plotter("comb.dat");
    PointsVector2d points;
    bool plot = false;
    for (int frequency = freqMin; frequency < freqMax; frequency += frequencyStep) {
        for (unsigned long sampleIndex = 0; sampleIndex < dataSize/2; ++sampleIndex) {
            double functionValue = function->compute(sampleIndex, frequency/resolution, resolution);
            double combReal = transformedSamplesBatch[sampleIndex][0];
            double combImaginary =  transformedSamplesBatch[sampleIndex][1];
            double combMagnitude =  std::sqrt(combReal * combReal + combImaginary * combImaginary);
            points.push_back(std::make_tuple((double)1000 * functionValue, (double)100 * combMagnitude) );
            if(combMagnitude != 0){
                plot = true;
            }

            sum += functionValue * combMagnitude;
        }
        if(frequency == 591) {
//            plotter.plot2d(points);
            plot = false;
        }
        points.clear();
        if (sum > max) {
            max = sum;
            result = frequency;
        }
        sum = 0;
    }
    return result;
}

void CombFilterAnalyser::calculateFft(double *data, fftw_complex *out, int dataSize) {
    fftw_plan plan = fftw_plan_dft_r2c_1d(dataSize, data, out, FFTW_MEASURE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

void CombFilterAnalyser::prepareDataForFft(double *data, int size, int batchSize) {
    for(int i=0; i < size; ++i){
        data[i] *= 0.53836 - 0.46164 * std::cos((2 * M_PI * i)/ batchSize -1 );
    }
}
