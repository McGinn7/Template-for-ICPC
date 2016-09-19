#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point3 {
    double x, y, z;

    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
} p[4];
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

double dmult(Point3 u, Point3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Point3 xmult(Point3 u, Point3 v) {
    Point3 ret;
    ret.x = u.y * v.z - v.y * u.z;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}

Point3 subt(Point3 u, Point3 v) {
    Point3 ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}

Point3 pvec(Point3 s1, Point3 s2, Point3 s3) {
    return xmult(subt(s1, s2), subt(s2, s3));
}

bool judge(Point3 a, Point3 b, Point3 c, Point3 d) {
    return zero(dmult(pvec(a, b, c), subt(d, a)));
}

double dist(Point3 a, Point3 b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double s[4];
double get(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double vol(double a, double b, double c, double a1, double b1, double c1){
    double aa = a * a, bb = b * b, cc = c * c;
    double m = bb + cc - a1 * a1, n = aa + cc - b1 * b1, p = aa + bb - c1 * c1;
    double v = aa * bb * cc -((aa * m * m) + (bb * n * n) + (cc * p * p) - m * n * p) / 4.0;
    return sqrt(v) / 6.0;
}

double getv() {
    double a = dist(p[0], p[1]);
    double b = dist(p[0], p[2]);
    double c = dist(p[0], p[3]);
    double c1 = dist(p[1], p[2]);
    double b1 = dist(p[1], p[3]);
    double a1 = dist(p[2], p[3]);
    return vol(a, b, c, a1, b1, c1);
}

int main() {
    while (~scanf("%lf%lf%lf", &p[0].x, &p[0].y, &p[0].z)) {
        for (int i = 1; i < 4; i++) p[i].read();
        if (judge(p[0], p[1], p[2], p[3])) printf("O O O O\n");
        else {
            Point3 tmp[4];
            for (int i = 0; i < 4; i++) {
                int tn = 0;
                for (int j = 0; j < 4; j++) {
                    if (j == i) continue;
                    tmp[tn++] = p[j];
                }
                s[i] = get(dist(tmp[0], tmp[1]), dist(tmp[1], tmp[2]), dist(tmp[2], tmp[0]));
            }
            double xx = (s[0] * p[0].x + s[1] * p[1].x + s[2] * p[2].x + s[3] * p[3].x) / (s[0] + s[1] + s[2] + s[3]);
            double yy = (s[0] * p[0].y + s[1] * p[1].y + s[2] * p[2].y + s[3] * p[3].y) / (s[0] + s[1] + s[2] + s[3]);
            double zz = (s[0] * p[0].z + s[1] * p[1].z + s[2] * p[2].z + s[3] * p[3].z) / (s[0] + s[1] + s[2] + s[3]);
            double r = 3 * getv() / (s[0] + s[1] + s[2] + s[3]);
            printf("%.4f %.4f %.4f %.4f\n", xx,yy, zz, r);
        }
    }
    return 0;
}