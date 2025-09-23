#pragma once
#include "RtWeekend.h"

class Interval {
public:
    double min, max;
    
    Interval();
    Interval(double min, double max);
    
    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    
    static const Interval empty;
    static const Interval universe;
    
};

