#pragma once
#include <iostream>

class Vetor {

private:
    double* mData;
    int mElementos;

public:
    Vetor();
    Vetor(const Vetor& outroVetor);
    Vetor(int n_elementos);
    ~Vetor();

    int GetNumElementos() const;

    double CalculaNorma(int p=2) const;
    double CalculaAngulo(const Vetor& outroVetor);

    double& operator[](int index_elemento);
    double& operator()(int index_elemento);

    Vetor& operator=(const Vetor& outraVetor);
    Vetor& operator+=(const Vetor& outraVetor);
    Vetor& operator-=(const Vetor& outraVetor);

    Vetor operator+(const Vetor& outraVetor) const;
    Vetor operator-(const Vetor& outraVetor) const;
    Vetor operator-() const;

    Vetor operator*(double n);
    double operator*(const Vetor& outraVetor) const;

    friend std::ostream& operator<<(std::ostream& saida, const Vetor& A);
};

int len(const Vetor& A);