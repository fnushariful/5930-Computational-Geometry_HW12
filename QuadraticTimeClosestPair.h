//
// Created by FNU Shariful on 2/2/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H


#include <utility>
#include "CGALComponents.h"

//std::pair<double, double> findClosestPairQuadratic(const std::vector<Point> &P) {
double findClosestPairQuadratic(const std::vector<Point> &P) {
    double minDistanceSoFar = INFINITY;
    unsigned p, q;

    for (unsigned i = 0; i < P.size(); ++i)
        for (unsigned j = i + 1; j < P.size() - 1; ++j) {
            double d = CGAL::squared_distance(P[i], P[j]); // returns squared distance
            if (d < minDistanceSoFar) {
                p = i;
                q = j;
                minDistanceSoFar = d;
            }
        }

    //return std::make_pair(p, q);
    return minDistanceSoFar;
}

#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H
