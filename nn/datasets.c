#include "datasets.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double rnd_unit()
{
    return (double)rand() / (double)RAND_MAX;
}

int generate_spiral(size_t N, double *data, size_t *labels, size_t classes, double noise)
{
    if (!data || !labels || classes < 2) return -1;
    size_t per = N / classes;
    size_t idx = 0;

    for (size_t c = 0; c < classes; c++)
    {
        size_t count = per + (c < (N % classes) ? 1 : 0);
        for (size_t i = 0; i < count; i++)
        {
            double r = (double)i / (double)count;
            double t = r * 4.0 * M_PI + (double)c * (2.0 * M_PI / (double)classes);
            double x = r * cos(t);
            double y = r * sin(t);
            x += (rnd_unit() - 0.5) * noise;
            y += (rnd_unit() - 0.5) * noise;

            data[2 * idx + 0] = x;
            data[2 * idx + 1] = y;
            labels[idx] = c;
            idx++;
            if (idx >= N) break;
        }
        if (idx >= N) break;
    }

    return 0;
}

int generate_moons(const size_t N, float64_t *data, size_t *labels, const double noise)
{
    if (!data || !labels || N < 2)
    {
        return -1;
    }

    const size_t n1 = N / 2;
    const size_t n2 = N - n1;

    size_t idx = 0;

    for (size_t i = 0; i < n1; i++)
    {
        double t = M_PI * (float64_t)i / (float64_t)n1;

        double x = cos(t);
        double y = sin(t);

        x += (rnd_unit() - 0.5) * noise;
        y += (rnd_unit() - 0.5) * noise;

        data[2 * idx + 0] = x;
        data[2 * idx + 1] = y;

        labels[idx] = 0;
        idx++;
    }

    for (size_t i = 0; i < n2; i++)
    {
        double t = M_PI * (double)i / (double)n2;
        double x = 1.0 - cos(t);
        double y = -sin(t) - 0.5;

        x += (rnd_unit() - 0.5) * noise;
        y += (rnd_unit() - 0.5) * noise;

        data[2 * idx + 0] = x;
        data[2 * idx + 1] = y;

        labels[idx] = 1;
        idx++;
    }

    return 0;
}
