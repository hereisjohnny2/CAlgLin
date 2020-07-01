#include "headers/SisLinear.hpp"
#include "headers/Matriz.hpp"
#include "headers/Vetor.hpp"

#include <iostream>
#include <cmath>
#include <cassert>


SisLinear::SisLinear(Matriz _mpA, Vetor _mpb) 
{
    int localSize = _mpA.GetNumColunas();
    assert(_mpA.GetNumLinhas() == localSize);
    assert(_mpb.GetNumElementos() == localSize);
    mSize = localSize;
    mpA = new Matriz(_mpA);
    mpb = new Vetor(_mpb);
}

Matriz SisLinear::P(int N, int k, int n) 
{
    Matriz A(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j && (i != k || j != k) && (i != n || j != n)) {
                A[i][j] = 1;
            } else if (i == k && j == n) {
                A[i][j] = 1;
            } else if (i == n && j == k) {
                A[i] [j] = 1;
            } else {
                A[i][j] = 0;
            }
        }
    }
    return A;
}

int SisLinear::MaiorElemento(Matriz* A, int N, int k)
{
    double Maior = (*A)[k][k];
    int iMaior = k;
    for (int i = k+1; i < N; i++) {
        if (fabs((*A)[i][k]) > fabs(Maior)) {
            Maior = (*A)[i][k];
            iMaior = i;
        } 
    }
    return iMaior; 
}

Vetor SisLinear::Solve()
{
    for (int k = 0; k < mSize-1; k++)
    {
        Matriz pivot(mSize);
        int MaiorIndice = MaiorElemento(mpA, mSize, k);
        pivot = P(mSize, k, MaiorIndice);
        (*mpA) = pivot * (*mpA);
        (*mpb) = pivot * (*mpb);
        for (int i = k + 1; i < mSize; i++)
        {
            double m;
            m = (*mpA)[i][k] / (*mpA)[k][k];
            (*mpb)[i] = (*mpb)[i] - (*mpb)[k] * m;
            for (int j = 0; j < mSize; j++)
            {
                (*mpA)[i][j] -= (*mpA)[k][j] * m;
            }
        }
    }

    Vetor u(mSize);
    u[mSize - 1] = (*mpb)[mSize - 1]/(*mpA)[mSize - 1][mSize - 1];
    for (int k = mSize-2; k >= 0; k--)
    {
        double soma {0.0};
        for (int i = k; i < mSize; i++)
        {
            soma += (*mpA)[k][i] * u[i];
        }
        u[k] = ((*mpb)[k] - soma)/(*mpA)[k][k];
    }
    
    return u;
}