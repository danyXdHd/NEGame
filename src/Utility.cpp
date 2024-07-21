#include <Utility.hpp>

const double PI = 3.14159265358979323846;

double angleWithXAxis(int x1, int y1, int x2, int y2) {

    double deltaX = x2 - x1;
    double deltaY = y2 - y1;

    double angleRad = std::atan2(deltaY, deltaX);
    double angleDeg = std::round(angleRad * (180.0 / PI)); // Convertim din radiani în grade

    // Asigurăm că unghiul este în intervalul [0, 360)
    angleDeg = fmod(angleDeg, 360.0);
    if (angleDeg < 0) {
        angleDeg += 360.0;
    }

    return angleDeg;

}

std::pair<double, double> calculatePointInDirection(int x1, int y1, double angle, int distance) {
    // Convertim unghiul în radiani
    angle = angle * (PI / 180.0);

    // Calculăm noile coordonate
    double x2 = x1 + std::cos(angle) * distance;
    double y2 = y1 + std::sin(angle) * distance;

    return std::make_pair(x2, y2);
}