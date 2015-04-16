//
// Created by Michał Gutowski on 26.03.15.
//

#ifndef _SOUND_PROCESS_BASE_BASE_PLOTTER_H_
#define _SOUND_PROCESS_BASE_BASE_PLOTTER_H_

#include <vector>

typedef std::vector<std::tuple<double, double, double> > PointsVector3d;
typedef std::vector<std::tuple<double, double> > PointsVector2d;

class BasePlotter {
public:
    virtual void plot(PointsVector3d points) = 0;
    virtual void plot2d(PointsVector2d points) = 0;
    virtual ~BasePlotter() {};
};
#endif //_SOUND_PROCESS_BASE_BASE_PLOTTER_H_
