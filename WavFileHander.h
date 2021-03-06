//
// Created by Michał Gutowski on 23.03.15.
//

#ifndef _SOUND_PROCESS_BASE_WAVFILEHANDER_H_
#define _SOUND_PROCESS_BASE_WAVFILEHANDER_H_


#include <iosfwd>
#include <string>
#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <vector>

typedef std::vector<double> sampleVector;

const int MAX_CHANNELS = 6;
const int BUFFER_LEN = 1024;

class WavFileHander {
public:
    WavFileHander(std::string infilename, std::string outfilename);

    sampleVector wholeFile() const ;
    int samplerate() const;
    void writeToOutFile();
    void writeToOutFile(std::vector<double> samples);
    std::vector<int> batchesSizes(int batch_size);

private:
    sf_count_t read(double *data);

    void readWhole();

    sampleVector samples;
    SndfileHandle infileHandle;
    SndfileHandle outfileHandle;
    double data[BUFFER_LEN];
};


#endif //_SOUND_PROCESS_BASE_WAVFILEHANDER_H_
