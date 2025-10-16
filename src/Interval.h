#pragma once
#include "RtWeekend.h"

class Interval {
public:
    double min, max;
    
    Interval();
    Interval(double min, double max);
    Interval(const Interval& a, const Interval& b);
    
    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;

    double clamp(double x) const;

    Interval expand(double delta) const;

    friend Interval operator+(const Interval& iVal, double displacement);
    friend Interval operator+(double displacement, const Interval& iVal);

    static const Interval empty;
    static const Interval universe;
    
};

