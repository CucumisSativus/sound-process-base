//
// Created by Michał Gutowski on 01.04.15.
//

#include "CombFunction.h"

double CombFunction::compute(int x, int frequency, int resolution) {
    int roundedArg = roundToNearestValue(x, resolution);
    if(roundedArg % frequency == 0 || x == 0){
        return 1;
    }
    else if(roundedArg % frequency == frequency/2){
        return -1;
    }
    else{
        return 0;
    }
}

int CombFunction::roundToNearestValue(int x, int resolution) {
    int distanceFromClosestResolution = x - (x - (x % resolution));
    int roundedValue =0;
    if(distanceFromClosestResolution <= resolution/2){
        roundedValue = x - distanceFromClosestResolution;
    }
    else{
        roundedValue= x + (resolution - distanceFromClosestResolution);
    }
    return roundedValue;
}
