#pragma once
#include "Vetor.hpp"
#include "Matriz.hpp"

class SisLinear 
{
private:
    int mSize;
    Vetor* mpb;
    Matriz* mpA;
public: 
    SisLinear(Matriz _mpA, Vetor _mpb);
    ~SisLinear() = default;
    Matriz P(int N, int k, int n);
    int MaiorElemento(Matriz* A, int N, int k);
    virtual Vetor Solve();

};