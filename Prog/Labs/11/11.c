#include <stdio.h>
#include <math.h>

double ln(double x, int n) {
    double E = pow(10, -3);
    double term = pow(-1, n + 1) * pow(x - 1, n) / n;
    if (fabs(term) >= E) {
        return term + ln(x, n + 1);
    }
    return 0;
}

int main() {
    for (double i = 0.1; i<=2.1; i += 0.1){
        double lnX = ln(i, 1);
        printf("ln(%.1f) = %f\n", i, lnX);
    }

    return 0;
}
