#include <iostream>

#include "headers/Vetor.hpp"
#include "headers/Matriz.hpp"
#include "headers/SisLinear.hpp"

int main()
{
    Matriz mpA = Matriz(3);
    double ARef[3][3] {
        {0.0, 4.0, 5.0},
        {7.0, 2.0, 9.0},
        {9.0, 8.0, 1.0},
    };

    for (int i = 0; i < mpA.GetNumLinhas(); i++)
    {
        for (int j = 0; j < mpA.GetNumColunas(); j++)
        {
            mpA[i][j] = ARef[i][j];
        }
    }

    Vetor mpb = Vetor(3);
    mpb[0] = 5.4; mpb[1] = 3.5; mpb[2] = 8.7;
    
    SisLinear sis1(mpA, mpb);

    std::cout << sis1.Solve() << std::endl;
    
    return 0;
}
