#ifndef _COLA_H_
#define _COLA_H_

#include<iostream>
#include"nodo.h"

using std::ostream;
using std::endl;

template<class elemento>
class cola
{
	private:
		nodo<elemento> *C;
	public:
		cola<elemento>() : C(NULL) {};
		cola<elemento>(const cola<elemento>& co);
		void encolar(elemento e);
		void desencolar();
		elemento frente();
		bool es_vacia() {return (C==NULL);}
		void operator = (const cola<elemento>& c);
		bool operator == (const cola<elemento>& c);
		bool operator != (const cola<elemento>& c) {return (!(this==c));}
		template<class elem>
		friend ostream& operator << (ostream& out, const cola<elem>& c);
		~cola<elemento>();
};

	template<class elemento>
	cola<elemento>::cola(const cola<elemento>& co)
	{
		nodo<elemento> *aux,*point=co.C;
		if(point!=NULL)
		{
			aux=new nodo<elemento>();
			this->C=aux;
			aux->mod_info(point->cons_info());
			point=point->cons_prox();
			while(point!=NULL)
			{
				aux->mod_prox(new nodo<elemento>(point->cons_info()));
				aux=aux->cons_prox();
				point=point->cons_prox();
			}
			aux->mod_prox(NULL);
		}
	}
	
	template<class elemento>
	void cola<elemento>::encolar(elemento e)
	{
		nodo<elemento> *aux=new nodo<elemento>(e),*pos=C;
		if(pos==NULL)
		{
			C=aux;
			aux=NULL;
		}
		else
		{
			while(pos->cons_prox()!=NULL)
			{
				pos=pos->cons_prox();
			}
			pos->mod_prox(aux);
			aux->mod_prox(NULL);
		}
		aux=NULL;

	}
	
	template<class elemento>
	void cola<elemento>::desencolar()
	{
		nodo<elemento> *aux;
		aux=C;
		C=C->cons_prox();
		aux->mod_prox(NULL);
		delete aux;
	}

	template<class elemento>
	elemento cola<elemento>::frente()
	{
		return C->cons_info();
	}
	

	template<class elemento>
	void cola<elemento>::operator = (const cola<elemento>& c)
	{
		cola<elemento> aux(c);
		this->C=aux.C;
		aux.C=NULL;
	}

	template<class elemento>
	bool cola<elemento>::operator == (const cola<elemento>& c)
	{
		bool t=true;
		nodo<elemento> *aux=C,*aux2=c.C;
		while((t)&&((aux!=NULL)&&(aux2!=NULL)))
		{
			t=((t)&&((aux->cons_info())==(aux2->cons_info())));
			aux=aux->cons_prox();
			aux2=aux2->cons_prox();
		}
		return t;
	}	
	
	template<class elem>
	ostream& operator << (ostream& out, const cola<elem>& c)
	{
		nodo<elem> *aux=c.C;
		while(aux!=NULL)
		{
			out << aux->cons_info() << endl;
			aux=aux->cons_prox();
		}
		return out;
	}

	template<class elemento>
	cola<elemento>::~cola()
	{
		nodo<elemento> *aux=C;
		while(C!=NULL)
		{
			C=aux->cons_prox();
			delete aux;
			aux=C;
		}
	}

#endif
