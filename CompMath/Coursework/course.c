#include <stdio.h>
#include <math.h>

#define T_MAX 90.0
#define TOL 1e-4

int main() {
    double alphaE = 0.999;
    double alphaI = 0.999;
    double k  = 0.042;
    double p    = 0.952;
    double beta   = 0.999;
    double mu     = 0.0188;
    double N      = 2798170.0;

    double E = 99.0;
    double R = 24.0;
    double S = N - E - R;
    double I = 0.0;
    double D = 0.0;

    double t = 0.0;
    double h = 1.0;

    FILE *fp = fopen("output.txt", "w");
    if (!fp) {
        perror("Не удалось открыть файл для записи");
        return 1;
    }
    fprintf(fp, "t\t\t\tS\t\t\tE\tI\t\tR\t\tD\n");
    while (t < T_MAX) {
        if (t + h > T_MAX) h = T_MAX - t;

        double c = 1.0;

        double dS = -c * (alphaI * S * I / N + alphaE * S * E / N);
        double dE =  c * (alphaI * S * I / N + alphaE * S * E / N) - (k + p) * E;
        double dI =  k * E - beta * I - mu * I;
        double dR =  beta * I + p * E;
        double dD =  mu * I;

        double S1 = S + h * dS;
        double E1 = E + h * dE;
        double I1 = I + h * dI;
        double R1 = R + h * dR;
        double D1 = D + h * dD;

        double h2 = 0.5 * h;
        double S_temp = S + h2 * dS;
        double E_temp = E + h2 * dE;
        double I_temp = I + h2 * dI;
        double R_temp = R + h2 * dR;
        double D_temp = D + h2 * dD;

        double dS2 = -c * (alphaI * S_temp * I_temp / N + alphaE * S_temp * E_temp / N);
        double dE2 =  c * (alphaI * S_temp * I_temp / N + alphaE * S_temp * E_temp / N) - (k + p) * E_temp;
        double dI2 =  k * E_temp - beta * I_temp - mu * I_temp;
        double dR2 =  beta * I_temp + p * E_temp;
        double dD2 =  mu * I_temp;

        double S2 = S_temp + h2 * dS2;
        double E2 = E_temp + h2 * dE2;
        double I2 = I_temp + h2 * dI2;
        double R2 = R_temp + h2 * dR2;
        double D2 = D_temp + h2 * dD2;

        double err = fmax(fmax(fabs(S1 - S2), fabs(E1 - E2)),
                          fmax(fmax(fabs(I1 - I2), fabs(R1 - R2)), fabs(D1 - D2)));

        if (err > TOL) {
            h *= 0.5;
            continue;
        }

        S = S2; E = E2; I = I2; R = R2; D = D2;
        t += h;

        fprintf(fp, "%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", t, S, E, I, R, D);

        if (err < TOL / 4) h *= 2.0;
    }

    fclose(fp);
    return 0;
}
