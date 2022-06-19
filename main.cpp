#include <iostream>

#include "LinearithmicTimeClosestPair.h"
#include "CGALComponents.h"
#include "QuadraticTimeClosestPair.h"
#include "DrawUsingQt.h"


typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie();

    //plot();

    for (unsigned i = 1; i <= 20; i++) {
        size_t numOfPoints = i * 1000;
        double timeCountNlonN = 0.0;
        double timeCountQuadraticAlgo = 0.0;
        for (unsigned j = 1; j <= 5; j++) {
            std::vector<Point> points;
            CGAL::Timer clock;
            clock_t st, ed;

            generatePointsInsideASquare(numOfPoints, 2000, points);

            auto pointsToIdsMap = createMapOfPoints(points);

            //clock.start();
            st = std::clock();
            std::pair closetPair = findClosetPairLinearithmic(points);
            //std::cout << "NlogN " << CGAL::sqrt(CGAL::squared_distance(closetPair.first, closetPair.second))
            //        << std::endl;
            //std::cout << findClosetPairLinearithmic(points) << std::endl;
            //clock.stop();
            ed = std::clock();
            timeCountNlonN += (double) (ed - st) / CLOCKS_PER_SEC;
            //clock.reset();

            //clock.start();
            reboot(std::clock());
            st = std::clock();
            double closetPair1 = findClosestPairQuadratic(points);
            //clock.stop();
            ed = std::clock();

            timeCountQuadraticAlgo += (double) (ed - st) / CLOCKS_PER_SEC;
            std::vector<unsigned> idsOfSpecialPoints;
            //idsOfSpecialPoints.emplace_back(pointsToIdsMap[closetPair.first]);
            //idsOfSpecialPoints.push_back(pointsToIdsMap[closetPair.second]);
            std::cout << std::sqrt(closetPair1) << std::endl;
            points.clear();
        }

        std::cout << numOfPoints << " " << (double) timeCountQuadraticAlgo / 5 << " " << (double) timeCountNlonN / 5
                  << std::endl;
        //draw(points, idsOfSpecialPoints, false);
    }
}

