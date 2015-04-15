//
// Created by Michał Gutowski on 26.03.15.
//

#ifndef _SOUND_PROCESS_BASE_BASE_PLOTTER_H_
#define _SOUND_PROCESS_BASE_BASE_PLOTTER_H_

#include <vector>

typedef std::vector<std::tuple<double, double, double> > PointsVector;

class BasePlotter {
public:
    virtual void plot(PointsVector points) = 0;
    virtual ~BasePlotter() {};
};
#endif //_SOUND_PROCESS_BASE_BASE_PLOTTER_H_
