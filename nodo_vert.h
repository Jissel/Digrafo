#ifndef NODO_VERT_H
#define NODO_VERT_H
#include"nodo_arc.h"
#include<iostream>
template<class elemento>
class NodoArc;

template<class elemento>
class NodoVert
{
	private:
		elemento info;
		NodoVert<elemento> *prox;
		NodoArc<elemento> *arcos;
	public:
		NodoVert(): info(),prox(NULL),arcos(NULL) {};
		NodoVert(elemento inf) : info(inf), prox(NULL), arcos(NULL) {};
		NodoVert(const NodoVert &a);
		void mod_info(elemento inf) {info=inf;}
		void mod_prox(NodoVert<elemento> *p) {prox=p;}
		void mod_arcos(NodoArc<elemento> *a) {arcos=a;}
		elemento cons_info() {return info;}
		NodoVert<elemento>* cons_prox() {return prox;}
		NodoArc<elemento>* cons_arcos() {return arcos;}
};
template<class elemento>
NodoVert<elemento>::NodoVert(const NodoVert<elemento> &a)
{
	info=a.info;
	prox=a.prox;
	arcos=a.arcos;
}

#endif
