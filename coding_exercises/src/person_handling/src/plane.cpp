#include <vector>
class Plane
{
public:
Plane(std::vector<double> coefficients); // coefficients a,b,c,d such that ax + by + cz + d = 0
Plane(std::vector<double> A, std::vector<double> normalVector); // constructor based on a point and a unit normal vector
std::vector<double> normalVector() { return normalVector; };
double distancePointToPlane(double pt_x, double pt_y, double pt_z);
// Class members
std::vector<double> A; // point belonging to the plane
std::vector<double> normalVector; // unit normal vector of the plane
};
Plane::Plane(std::vector<double> coefficients)
{
normalVector = std::vector<double>(3);
normalVector[0] = coefficients[0];
normalVector[1] = coefficients[1];
normalVector[2] = coefficients[2];

double squarednorm = normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1] + normalVector[2] * normalVector[2];
A = std::vector<double>(3);
A[0] = -coefficients[0] * coefficients[3] / squarednorm;
A[1] = -coefficients[1] * coefficients[3] / squarednorm;
A[2] = -coefficients[2] * coefficients[3] / squarednorm;
}
Plane::Plane(std::vector<double> A_input, std::vector<double> normalVector_input)
{
normalVector = std::vector<double>(3);
normalVector[0] = normalVector_input[0];
normalVector[1] = normalVector_input[1];
normalVector[2] = normalVector_input[2];
A = std::vector<double>(3);
A[0] = A_input[0];
A[1] = A_input[1];
A[2] = A_input[2];
}
double Plane::distancePointToPlane(double pt_x, double pt_y, double pt_z)
{
double res = (pt_x - A[0]) * normalVector[0] + (pt_y - A[1]) * normalVector[1] + (pt_z - A[2]) * normalVector[2];
if (res <= 0)
 res = -res;
return res;
}