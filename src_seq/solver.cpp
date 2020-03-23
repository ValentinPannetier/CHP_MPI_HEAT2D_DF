#include "solver.h"

Vector conj_gradient (const Matrix &A, const Vector &b)
{
    int N = b.size ();

    if (N != (A.Nx * A.Ny)) return Vector (N, 0.);

    double eps = 1e-5;

    Vector x (N, 0.);
    Vector r = b;
    Vector p = r;

    int k;
    for (k = 0; k < N; k++) {

        double alpha = (r | r) / ((A * p) | p);

        x += alpha * p;

        Vector r_bis = r;
        r_bis -= alpha * (A * p);

        // printf("error : %10.5f\n", sqrt ((r_bis|r_bis)));
        if (sqrt ((r_bis|r_bis)) < eps)
        {
            r = r_bis;
            break;
        }

        double beta = (r_bis | r_bis) / (r | r);

        p *= beta;
        p += r_bis;
        r = r_bis;
    }

    printf ("(GradConj) : %i étapes \t erreur = %f", k, sqrt(r|r));

    return x;
}
