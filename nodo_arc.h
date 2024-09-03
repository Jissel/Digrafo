#ifndef NODO_ARCOS_H
#define NODO_ARCOS_H
#include"nodo_vert.h"
#include<iostream>
template<class elemento>
class NodoArc
{
	private:
		NodoVert<elemento> *vertice;
		NodoArc<elemento> *prox;
	public:
		NodoArc() : vertice(NULL), prox(NULL) {};
		NodoArc(NodoVert<elemento> *v): vertice(v), prox(NULL) {};
		NodoArc(NodoVert<elemento> *v, NodoArc<elemento> *p) : vertice(v), prox(p) {};
		NodoArc(const NodoArc<elemento> &a);
		void mod_vert(NodoVert<elemento> *v) {vertice=v;}
		void mod_prox(NodoArc<elemento> *p) {prox=p;}
		NodoVert<elemento>* cons_vert() {return vertice;}
		NodoArc<elemento>* cons_prox() {return prox;}
};

template<class elemento>
NodoArc<elemento>::NodoArc(const NodoArc<elemento> &a)
{
	vertice=a.vertice;
	prox=a.prox;
}

#endif
