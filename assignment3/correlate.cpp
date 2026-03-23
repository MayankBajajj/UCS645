#include <cmath>
#include <omp.h>

void correlate(int ny, int nx, const float* data, float* result)
{
    double* mean = new double[ny];
    double* stddev = new double[ny];

    for(int i = 0; i < ny; i++)
    {
        double sum = 0.0;
        for(int x = 0; x < nx; x++)
            sum += data[x + i * nx];

        mean[i] = sum / nx;

        double variance = 0.0;
        for(int x = 0; x < nx; x++)
        {
            double diff = data[x + i * nx] - mean[i];
            variance += diff * diff;
        }

        stddev[i] = sqrt(variance);
    }

    #pragma omp parallel for schedule(static)
    for(int i = 0; i < ny; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            double numerator = 0.0;

            for(int x = 0; x < nx; x++)
            {
                double a = data[x + i * nx] - mean[i];
                double b = data[x + j * nx] - mean[j];
                numerator += a * b;
            }

            double denom = stddev[i] * stddev[j];

            if(denom == 0)
                result[i + j * ny] = 0;
            else
                result[i + j * ny] = numerator / denom;
        }
    }

    delete[] mean;
    delete[] stddev;
}