//
// Created by Michał Gutowski on 26.03.15.
//

#include "ToFilePlotter.h"

void ToFilePlotter::plot(PointsVector points) {
    for(unsigned long i=0; i< points.size(); ++i){
        outFile << std::get<0>(points[i]) << ' ' << std::get<1>(points[i]) << ' ' << std::get<2>(points[i]) <<
        std::endl;
    }
}

ToFilePlotter::ToFilePlotter(const std::string &fileName) {
    outFile.open(fileName);
}

ToFilePlotter::~ToFilePlotter() {
    outFile.close();
}
