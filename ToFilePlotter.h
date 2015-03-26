//
// Created by Michał Gutowski on 26.03.15.
//

#ifndef SOUND_PROCESS_BASE_TOFILEPLOTTER_H
#define SOUND_PROCESS_BASE_TOFILEPLOTTER_H

#include <iosfwd>
#include <fstream>
#include "Base_Plotter.h"

class ToFilePlotter : public BasePlotter{

public:
    ToFilePlotter(const std::string & fileName);
    ~ToFilePlotter();
    virtual void plot(PointsVector points);


private:
    std::ofstream outFile;
};


#endif //SOUND_PROCESS_BASE_TOFILEPLOTTER_H
