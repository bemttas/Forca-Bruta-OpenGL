//
//  QuadTree.hpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 02/09/22.
//  Copyright © 2022 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef QuadTree_hpp
#define QuadTree_hpp
#include "Poligono.h"

class NodoQT
{
public:
    int *pontosNoEnvelope;
    NodoQT *Filhos[4];
    int nroDePontosNoEnvelope;
    Envelope BB;
    NodoQT();
};

class QuadTree{
public:
    Poligono *Pontos; // referencia para os pontos do cenário
    Envelope E;
    NodoQT *Raiz;
    int qtdMaxDePontos;
    QuadTree(Envelope E, Poligono *P, int nPontos);
    NodoQT *InsereNodo(Envelope E);
    bool DeveDividir(Envelope E);
    void Desenha();
    void Desenha(NodoQT *n);
    unsigned ContaPontosInternosAoEnvelope(Envelope E);
    int *GeraPontosInternosAoEnvelope(Envelope E, unsigned n);
    void DesenhaNodosComColisao(Envelope E);
    void DesenhaNodosComColisao2(NodoQT *n, Envelope E);
    void DesenhaNodosComColisao(NodoQT *n, Envelope E);
};

#endif /* QuadTree_hpp */
