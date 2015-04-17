//
// Created by Michał Gutowski on 26.03.15.
//

#include "ToFilePlotter.h"
#include <stdio.h>
void ToFilePlotter::plot(PointsVector3d points) {
    if(outFile.is_open()){
        outFile.close();
        remove( filename.c_str() );
    }
    outFile.open(filename, std::ofstream::out | std::ofstream::trunc);
    for(unsigned long i=0; i< points.size(); ++i){
        outFile << std::get<0>(points[i]) << ' ' << std::get<1>(points[i]) << ' ' << std::get<2>(points[i]) <<
        std::endl;
    }
}

ToFilePlotter::ToFilePlotter(const std::string &fileName): filename(fileName) {
    outFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
}

ToFilePlotter::~ToFilePlotter() {
    outFile.close();
}

void ToFilePlotter::plot2d(PointsVector2d points) {
    if(outFile.is_open()){
        outFile.close();
        remove( filename.c_str() );
    }
    outFile.open(filename, std::ofstream::out | std::ofstream::trunc);
    for(unsigned long i=0; i< points.size(); ++i) {
        outFile << std::get<0>(points[i]) << ' ' << std::get<1>(points[i]) <<
        std::endl;
    }
}
