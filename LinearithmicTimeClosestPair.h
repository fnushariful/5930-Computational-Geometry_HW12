
#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Timer.h>


typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point;

double currentBestDistance = INFINITY;
Point currentX, currentY;

void plot() {
    freopen("a.txt", "w", stdout);
}

bool compareXCord(Point p, Point q) {
    return p.x() < q.x();
}


bool less(Point p, Point q) {
    if (p.y() < q.y()) return true;
    if (p.y() > q.y()) return false;

    return p.x() < q.x();
}

void merge(std::vector<Point> a, std::vector<Point> aux, unsigned lo, unsigned mid, unsigned hi) {
    unsigned i, j, k;

    for (k = lo; k <= hi; k++) {
        aux.emplace_back(a[k]);
    }

    i = lo, j = mid + 1;

    while (i <= mid && j <= hi) {
        a.emplace_back(less(aux[i], aux[j]) ? aux[i++] : aux[j++]);
    }

    while (i <= mid) {
        a.emplace_back(aux[i++]);
    }
}

double computeClosetPair(std::vector<Point> XSorted, std::vector<Point> YSorted, std::vector<Point> aux, unsigned lo,
                         unsigned hi) {

    if (hi <= lo) {
        return INFINITY;
    }

    unsigned mid = lo + (hi - lo) / 2;

    double stripD = computeClosetPair(XSorted, YSorted, aux, lo, mid);
    double dist = computeClosetPair(XSorted, YSorted, aux, mid + 1, hi);

    stripD = std::min(dist, stripD);

    merge(YSorted, aux, lo, mid, hi);

    unsigned M;

    for (unsigned i = lo; i <= hi; i++) {
        if (abs(YSorted[i].x() - XSorted[mid].x()) < stripD)
            aux.emplace_back(YSorted[i]);
    }

    double distance;
    M = aux.size();
    for (unsigned i = 0; i < M; i++) {
        for (unsigned j = i + 1; j < M && (aux[j].y() - aux[i].y() < stripD); j++) {
            distance = CGAL::squared_distance(aux[i], aux[j]);
            if (distance < stripD) {
                stripD = distance;
                if (stripD < currentBestDistance) {
                    currentBestDistance = stripD;
                    currentX = aux[i];
                    currentY = aux[j];
                }
            }
        }
    }
    return stripD;
}

std::pair<Point, Point> findClosetPairLinearithmic(std::vector<Point> P) {

    std::vector<Point> XSorted(P.begin(), P.end());
    std::vector<Point> YSorted;
    std::vector<Point> aux;

    sort(XSorted.begin(), XSorted.end(), compareXCord);
    YSorted = XSorted;
    std::cout << std::sqrt(computeClosetPair(XSorted, YSorted, aux, 0, P.size() - 1)) << std::endl;

    return std::make_pair(currentX, currentY);
}

// https://www.youtube.com/watch?v=_pSl90jq-m0