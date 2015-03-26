//
// Created by Michał Gutowski on 26.03.15.
//

#include "ToFilePlotter.h"

void ToFilePlotter::plot(PointsVector points) {
    for(unsigned long i=0; i< points.size(); ++i){
        outFile << points[i].first << ' ' << points[i].second << std::endl;
    }
}

ToFilePlotter::ToFilePlotter(const std::string &fileName) {
    outFile.open(fileName);
}

ToFilePlotter::~ToFilePlotter() {
    outFile.close();
}
