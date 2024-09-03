#ifndef _LISTA_H_
#define _LISTA_H_

#include<iostream>
#include"nodo.h"
using std::ostream;
using std::endl;

template<class elemento>
class lista
{
	private:
		nodo<elemento> *L;
		int lon;
	public:
		lista<elemento>(): L(NULL), lon(0) {};
		lista<elemento>(const lista<elemento>& l);
		elemento consultar(int pos);
		void insertar(elemento e,int pos);
		void eliminar(int pos);
		bool es_vacia();
		int longitud() {return lon;}
		void operator = (const lista<elemento>& lis);
		bool operator == (const lista<elemento>& lis);
		bool operator != (const lista<elemento>& lis) {return (!(this==lis));}
		template<class elem>
		friend ostream& operator << (ostream& out, const lista<elem>& lis);
		~lista<elemento>();
};

template<class elemento>
lista<elemento>::lista(const lista<elemento>& l)
{
	nodo<elemento> *aux, *point=l.L;
	if(point!=NULL)
	{
		aux=new nodo<elemento>();
		this->L=aux;
		this->lon=l.lon;
		aux->mod_info(point->cons_info());
		point=point->cons_prox();
		while(point!=NULL)
		{
			aux->mod_prox(new nodo<elemento>(point->cons_info()));
			aux=aux->cons_prox();
			point=point->cons_prox();
		}
		aux->mod_prox(NULL);
		aux=NULL;
		point=NULL;
	}
	else
	{
		L=NULL;
		lon=0;
	}
}

template<class elemento>
elemento lista<elemento>::consultar(int pos)
{
	nodo<elemento> *aux=L;
	int i=1;
	while(i!=pos)
	{
		aux=aux->cons_prox();
		i++;
	}
	return aux->cons_info();
}

template<class elemento>
void lista<elemento>::insertar(elemento e, int pos)
{
	nodo<elemento> *aux=new nodo<elemento>(e),*ap=L;
	lon++;
	int i=1;
	if(pos==1)
	{
		aux->mod_prox(L);
		L=aux;
	}
	else
	{
		while(i<pos-1)
		{
			ap=ap->cons_prox();
			i++;
		}
		aux->mod_prox(ap->cons_prox());
		ap->mod_prox(aux);	
	}
}

template<class elemento>
void lista<elemento>::eliminar(int pos)
{
	int i=1;
	nodo<elemento> *act=L,*ant=NULL;
	if(pos==1)
	{
		L=act->cons_prox();
		act->mod_prox(NULL);
		delete act;		
	}
	else
	{
		while(i<pos-1)
		{
			act=act->cons_prox();
			i++;
		}
		ant=act->cons_prox();
		act->mod_prox(ant->cons_prox());
		delete ant;
	}
	lon--;
}

template<class elemento>
bool lista<elemento>::es_vacia()
{
	return (L==NULL);
}

template<class elemento>
void lista<elemento>::operator =(const lista<elemento>& lis)
{

	lista<elemento> aux(lis);
	L=aux.L;
	lon=lis.lon;
	aux.L=NULL;
	aux.lon=0;
}

template<class elemento>
bool lista<elemento>::operator == (const lista<elemento>& lis)
{
	nodo<elemento> *aux=L,*aux2=lis.L;
	bool t=true;
	t=((t)&&(lon==lis.lon));
	while((aux!=NULL)&&(aux2!=NULL)&&(t))
	{
		t=((t)&&(aux->cons_info()==aux2->cons_info()));
		aux=aux->cons_prox();
		aux2=aux2->cons_prox();
	}
	return t;
}

template<class elem>
ostream& operator << (ostream& out, const lista<elem>& lis)
{
	nodo<elem> *aux=lis.L;
	while(aux!=NULL)
	{
		out << aux->cons_info() << endl;
		aux=aux->cons_prox();
	}
	return out;
}

template<class elemento>
lista<elemento>::~lista()
{
	nodo<elemento> *aux=L;
	while(L!=NULL)
	{
		L=aux->cons_prox();
		delete aux;
		aux=L;
	}
}

#endif



