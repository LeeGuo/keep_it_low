#include <iostream>
#include <math.h>

using namespace std;

// ax + by = c
// dx + ey = f
// x = (fb - ec)/(bd - ae)
// y = (af - dc)/(ae - db)
double X(double a, double b, double c, double d, double e, double f) {
	double son = (f*b - e*c);
	double mother = (b*d - a*e);
	if (mother == 0)
		return pow(10, 6);
	return son / mother;
}

double Y(double a, double b, double c, double d, double e, double f) {
	double son = (a*f - d*c);
	double mother = (a*e - d*b);
	if (mother == 0)
		return pow(10, 6);
	return son / mother;
}

double Z(double a, double b, double x, double y) {
	return a*x + b*y;
}

bool OK(double x, double y, double a, double b, double c) {
	return a*x + b*y <= c;
}

void maximumBenefit(double A, double B, double C, double D, double E, double F, double G, double H, double J, double K, double P) {
	double lines[5][3] = {
		{C, D, E},
		{F, G, H},
		{J, K, P},
		{1.0, 0, 0},
		{0, 1.0, 0},
	};
	
	double xMax = 0, yMax = 0, zMax = 0;
	for (int i=0; i<5; ++i) {
		for (int j=i+1; j<5; ++j) {
			double crossX = X(lines[i][0], lines[i][1], lines[i][2], lines[j][0], lines[j][1], lines[j][2]);
			double crossY = Y(lines[i][0], lines[i][1], lines[i][2], lines[j][0], lines[j][1], lines[j][2]);
			if (crossX > (pow(10, 6) - 1) || crossY > (pow(10, 6) - 1))
				continue;

			double benefit = Z(A, B, crossX, crossY);
			
			if (benefit > zMax) {
				bool ok = true;
				for (int z=0; z<3; ++z) {
					ok &= OK(crossX, crossY, lines[z][0], lines[z][1], lines[z][2]);
					if (!ok) break;
				}
				
				if (ok) {
					xMax = crossX;
					yMax = crossY;
					zMax = benefit;
				}
			}
		}
	}
	
	cout << "\nMax profit = " << zMax << ", x = " << xMax << ", y = " << yMax << "\n" << endl;
	return;
}

int main() {
    double A, B, C, D, E, F, G, H, J, K, P;
    while (true) {
        cout << "A = ", cin >> A;
        if (A < 0) break;
        cout << "B = ", cin >> B;
        cout << "C = ", cin >> C;
        cout << "D = ", cin >> D;
        cout << "E = ", cin >> E;
        cout << "F = ", cin >> F;
        cout << "G = ", cin >> G;
        cout << "H = ", cin >> H;
        cout << "J = ", cin >> J;
        cout << "K = ", cin >> K;
        cout << "P = ", cin >> P;
        maximumBenefit(A, B, C, D, E, F, G, H, J, K, P);
    }

    return 0;
}
