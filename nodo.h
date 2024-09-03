#ifndef _NODO_H_
#define _NODO_H_
#include<iostream>


template<class elemento>
class nodo
{
	private:
		nodo *prox;
		elemento info;
	public:
		nodo<elemento>() : prox(NULL), info() {};
		nodo<elemento>(elemento in) : prox(NULL), info(in) {};
		nodo<elemento>(const nodo& a);
		nodo<elemento>* cons_prox() {return prox;}
		elemento cons_info() {return info;}
		void mod_prox(nodo<elemento> *p) {prox=p;}
		void mod_info(elemento in) {info=in;}
		bool operator == (const nodo<elemento>& a);
		bool operator != (const nodo<elemento>& a);
		void operator = (const nodo<elemento>& a);

};

template<class elemento>
nodo<elemento>::nodo(const nodo& a)
{
	prox=a.prox;
	info=a.info;
}

template<class elemento>
bool nodo<elemento>::operator == (const nodo<elemento>& a)
{
	return ((a.prox==prox)&&(a.info==info));
}


template<class elemento>
bool nodo<elemento>::operator != (const nodo<elemento>& a)
{
	return (!((a.prox==prox)&&(a.info==info)));
}

template<class elemento>
void nodo<elemento>::operator = (const nodo<elemento>& a)
{
	this->nodo(a);
}


#endif
