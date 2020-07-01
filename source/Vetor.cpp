#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>

#include "headers/Vetor.hpp"


//Construtor vazio. Inicializa um vetor padrão colcando 3 posições de memória.
Vetor::Vetor() {
    mElementos = 3;
    mData = new double[mElementos];
}

//Construtor que cria um novo vetor a partir de outro.
Vetor::Vetor(const Vetor& outroVetor) {
    mElementos = outroVetor.GetNumElementos();
    mData = new double[mElementos];
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = outroVetor.mData[i];
    }    
}

//Construtor que aloca n_elementos para um vetor.
Vetor::Vetor(int n_elementos) {
    mElementos = n_elementos;
    mData = new double[mElementos];
}

//Sobrescreve o método destrutor para desalocar a memória de maneira apropriada.
Vetor::~Vetor() {
    delete[] mData;
}

//Retorna o numero de elementos em um vetor.
int Vetor::GetNumElementos() const {
    return mElementos;
}

//Calcula a norma euclidiana de um vetor. Utilizada para calcular o comprimento de um vetor. Ver mais em https://pt.wikipedia.org/wiki/Vetor_(matemática).
double Vetor::CalculaNorma(int p) const {
    double valorNorma, soma {0.0};
    for (int i = 0; i < mElementos; i++)
    {
        soma += pow(fabs(mData[i]), p);
    }
    valorNorma = pow(soma, 1.0/((double) p ));
    return valorNorma;
}

//Calcula o angulo entre dois vetores, utilizando a norma euclidiana para p=2;
double Vetor::CalculaAngulo(const Vetor& outroVetor) {
    double angulo;
    angulo = acos((*this * outroVetor)/(CalculaNorma()*outroVetor.CalculaNorma()));
    return angulo;
}

//Sobrescreve o operador [] para retornar o indice de um vetor, de modo que o primeiro elemento será igual terá indice zero.
double& Vetor::operator[](int index_elemento) {
    assert(index_elemento > -1);
    assert(index_elemento < mElementos);
    return mData[index_elemento];
}

//Sobrescreve o operador [] para retornar o indice de um vetor, de modo que o primeiro elemento será igual terá indice 1.
double& Vetor::operator()(int index_elemento) {
    assert(index_elemento > 0);
    assert(index_elemento < mElementos + 1);
    return mData[index_elemento];
} 

//Sobrescreve o operador de atribuição. Dessa forma uma variável do tipo Vetor pode ser atribuida a outra desde que possuam o mesmo tamanho de espaço alocado.
Vetor& Vetor::operator=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de atribição e soma. Sejam dois vetor A e B, com a mesma quantidade de elementos. Em A+=B, os valores de ambos são somados e o resultado é colocado de volta em A.
Vetor& Vetor::operator+=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] += outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de atribição e subtração. Sejam dois vetor A e B, com a mesma quantidade de elementos. Em A-=B, os valores de ambos são subtratidos A-B, e o resultado é colocado de volta em A.
Vetor& Vetor::operator-=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] -= outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de soma. Dois vetores A e B, de mesmo tamanho são somados e o resultado é colocado em um terceiro vetor de Saida.
Vetor Vetor::operator+(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] + outroVetor.mData[i];
    }
    return Saida;
}

//Sobrescreve a operação de soma. Dois vetores A e B, de mesmo tamanho são subtraidos e o resultado é colocado em um terceiro vetor de Saida.
Vetor Vetor::operator-(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] - outroVetor.mData[i];
    }
    return Saida;
}

//Sobrescreve o operador unário de subtração de modo que são atribuidos à vetor de saida os valores de um outro vetor multiplicados por -1.
Vetor Vetor::operator-() const {
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = -mData[i];
    }
    return Saida;
}

//Sobrescreve a operação de multiplicação. Um vetor A tem cada um dos seus elementos multiplicados por um escalar n, e o resultado é colocado dentro de um terceiro vetor de Saida.
Vetor Vetor::operator*(double n) {
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] * n;
    }
    return Saida;
}

//Sobrescreve a operação de multiplicação retornando o produto escalar de dois vetores, de modo que ambos possuam o mesmo tamanho.
double Vetor::operator*(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    double soma {0.0};
    for (int i = 0; i < mElementos; i++)
    {
        soma += mData[i] * outroVetor.mData[i];
    }
    return soma;
}

//Sobrescreve a operação <<, retornando na tela os elementos de um vetor A.
std::ostream& operator<<(std::ostream& saida, const Vetor& A) {
    for (int i = 0; i < A.mElementos; i++)
    {
        saida << A.mData[i] << std::setw(15);
    }
    return saida;
}

//Retorna o tamanho de um vetor A recebendo como argumento o vetor. Semelhante a sintaxe do python.
int len(const Vetor& A) {
    return A.GetNumElementos();
}
