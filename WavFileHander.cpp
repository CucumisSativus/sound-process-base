//
// Created by Michał Gutowski on 23.03.15.
//

#include "WavFileHander.h"

WavFileHander::WavFileHander(std::string infilename, std::string outfilename) {
    if (!(infileHandle = SndfileHandle(infilename, SFM_READ))) {
        throw std::runtime_error("Cannot open input file");
    };

    if (infileHandle.channels() > MAX_CHANNELS) {
        throw std::runtime_error("Too many channels");
    };
    /* Open the output file. */
    if (!(outfileHandle = SndfileHandle(outfilename, SFM_WRITE, infileHandle.format(), infileHandle.channels(), infileHandle.samplerate()))) {
        throw std::runtime_error("Cannot open output file");
    };
    readWhole();
}

sf_count_t WavFileHander::read(double *data) {
    return infileHandle.read(data, BUFFER_LEN);
}

void WavFileHander::readWhole() {
    sf_count_t readCount;
    while((readCount = (read(data))) != 0){
        sampleVector vector(data, data + readCount);
        samples.reserve(samples.size() + vector.size());
        samples.insert( samples.end(), vector.begin(), vector.end());
    }
}

sampleVector WavFileHander::wholeFile() const {
    return samples;
}

void WavFileHander::writeToOutFile() {
    double * outputData = samples.data();
    sf_count_t size = samples.size();
    outfileHandle.write(outputData, size);
}

int WavFileHander::samplerate() const{
    infileHandle.samplerate();
}
