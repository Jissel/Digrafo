#ifndef DIGRAFO_H
#define DIGRAFO_H
#include"lista.h"
#include"cola.h"
#include"nodo_arc.h"
#include"nodo_vert.h"
#include<iostream>
using namespace std;
template<class elemento>
class Digrafo
{
	private:
		NodoVert<elemento> *vertices;
		int num_vert;
		int num_arc;
		//metodos publicos:
		void insert_vertice(elemento v);
		void insert_arco(elemento v1,elemento v2);
		void delete_arco(NodoVert<elemento> *&v1,elemento v2);
		void delete_vertice(NodoVert<elemento> *v);
		bool existe_arc(NodoVert<elemento> *v1, elemento v2);
		int pos_vert(elemento v);
		elemento vert_pos(int pos);
		void visitarDFS(elemento u,int F[],int color[],int Predecesor[],int distancia[],int &marca);
	public:
		Digrafo() : vertices(NULL), num_vert(0), num_arc(0) {};
		Digrafo(const Digrafo<elemento> &a);
		void insertar_vertice(elemento v);
		void insertar_arco(elemento v1,elemento v2);
		bool existe_vertice(elemento v);
		void eliminar_arco(elemento v1,elemento v2);
		bool existe_arco(elemento v1,elemento v2);
		void eliminar_vertice(elemento v);
		lista<elemento> sucesores(elemento v);
		lista<elemento> predecesores(elemento v);
		void BFS(elemento s,int color[],int Predecesor[],int distancia[]);
		void DFS(int F[],int color[],int Predecesor[],int distancia[]);
		elemento vertice_posicion(int pos) {return vert_pos(pos);}
		int numero_vertices() {return num_vert;}
		int posicion_vertice(elemento v){return pos_vert(v);}
		int numero_comp_conexas();
		void clear();
		void imprimir();
		~Digrafo();
};


//CONSTRUCTOR COPIA
//PUBLICO
template<class elemento>
Digrafo<elemento>::Digrafo(const Digrafo<elemento> &a)
{
	vertices=NULL;
	num_vert=0;
	num_arc=0;
	if(a.vertices!=NULL)
	{
		int i;
		NodoVert<elemento> *aux=a.vertices;
		NodoArc<elemento> *aux2;
		for(i=0;i<a.num_vert;i++)
		{
			insert_vertice(aux->cons_info());
			aux=aux->cons_prox();
		}
		aux=a.vertices;
		while(aux!=NULL)
		{
			aux2=aux->cons_arcos();
			while(aux2!=NULL)
			{
				insert_arco(aux->cons_info(),aux2->cons_vert()->cons_info());
				aux2=aux2->cons_prox();
			}
			aux=aux->cons_prox();
		}	
	}	
}
//F_CONSTRUCTOR_COPIA

//INSERTAR VERTICE
//PRIVADO:
template<class elemento>
void Digrafo<elemento>::insert_vertice(elemento v)
{
	if(vertices==NULL)
	{
		vertices=new NodoVert<elemento>(v);
		num_vert++;
	}
	else
	{
		NodoVert<elemento> *aux=vertices;
		bool esta=false;
		while((!esta)&&((aux->cons_prox())!=NULL))
		{
			if(aux->cons_info()!=v)
			{
				aux=aux->cons_prox();
			}
			else
			{
				esta=true;
			}
		}
		if(!esta)
		{
			aux->mod_prox(new NodoVert<elemento>(v));
			aux=NULL;
			num_vert++;
		}
	}
}

//PUBLICO:
template<class elemento>
void Digrafo<elemento>::insertar_vertice(elemento v)
{
	insert_vertice(v);
}
//F_INSERTAR VERTICE

//INSERTAR ARCO
//PRIVADO:
template<class elemento>
void Digrafo<elemento>::insert_arco(elemento v1,elemento v2)
{
	NodoVert<elemento> *aux1,*aux2,*aux3;
	NodoArc<elemento> *arc;
	bool v1_encontrado=false,v2_encontrado=false;
	aux1=vertices;
	while((!v1_encontrado)||(!v2_encontrado))
	{
		if(!v1_encontrado)
		{
			if(aux1->cons_info()==v1)
			{
				aux2=aux1;
				v1_encontrado=true;
			}
		}
		if(!v2_encontrado)
		{
			if(aux1->cons_info()==v2)
			{
				aux3=aux1;
				v2_encontrado=true;
			}
		}
		aux1=aux1->cons_prox();
	}
	if(aux2->cons_arcos()==NULL)
	{
		aux2->mod_arcos(new NodoArc<elemento>(aux3));
	}
	else
	{
		arc=aux2->cons_arcos();
		while(arc->cons_prox()!=NULL)
		{
			arc=arc->cons_prox();
		}
		arc->mod_prox(new NodoArc<elemento>(aux3));
	}
	num_arc++;
}
//PUBLICO
template<class elemento>
void Digrafo<elemento>::insertar_arco(elemento v1,elemento v2)
{
	if((existe_vertice(v1))&&(existe_vertice(v2)))
		insert_arco(v1,v2);
}
//F_INSERTAR ARCO

//EXISTE VERTICE
template<class elemento>
bool Digrafo<elemento>::existe_vertice(elemento v)
{
	//int i;
	NodoVert<elemento> *aux=vertices;
	bool encontrado=false;
	while((!encontrado)&&(aux!=NULL))
	{
		if(aux->cons_info()==v)
		{
			encontrado=true;
		}
		else
		{
			aux=aux->cons_prox();
		}
	}
	return encontrado;
}
//F_EXISTE VERTICE

//ELIMINAR ARCO
//PRIVADO:lista<elemento> predecesores(elemeno v)
template<class elemento>
void Digrafo<elemento>::delete_arco(NodoVert<elemento> *&v1,elemento v2)
{
	NodoArc<elemento> *aux=v1->cons_arcos(),*auxx=NULL;
	bool eliminado=false;
	if(aux!=NULL)
	{
		if(aux->cons_vert()->cons_info()==v2)
		{
			v1->mod_arcos(aux->cons_prox());
			aux->mod_prox(NULL);
			delete aux;
			aux=NULL;
			num_arc--;
		}
		else
		{
			auxx=aux;
			aux=aux->cons_prox();
			while((!eliminado)&&(aux!=NULL))
			{
				if(aux->cons_vert()->cons_info()==v2)
				{
					auxx->mod_prox(aux->cons_prox());
					aux->mod_prox(NULL);
					delete aux;
					aux=NULL;
					eliminado=true;
					num_arc--;
				}
				else
				{
					auxx=aux;
					aux=aux->cons_prox();
				}
			}
		}
	}
}
//PUBLICO:
template<class elemento>
void Digrafo<elemento>::eliminar_arco(elemento v1,elemento v2)
{
	if(existe_vertice(v1)&&existe_vertice(v2))
	{
		NodoVert<elemento> *aux=vertices;
		bool encontrado=false;
		while((aux!=NULL)&&(!encontrado))
		{
			if(aux->cons_info()==v1)
			{
				encontrado=true;
			}
			else
			{
				aux=aux->cons_prox();
			}
		}
		if(aux!=NULL)
			delete_arco(aux,v2);
	}
}
//F_ELIMINAR ARCO

//EXISTE_ARCO
//PRIVADO
template<class elemento>
bool Digrafo<elemento>::existe_arc(NodoVert<elemento> *v1, elemento v2)
{
	bool enc_arc=false;
	if(v1!=NULL)
	{		
		NodoArc<elemento> *aux2=v1->cons_arcos();
		while((!enc_arc)&&(aux2!=NULL))
		{
			if(aux2->cons_vert()->cons_info()==v2)
			{
				enc_arc=true;
			}
			else
			{
				aux2=aux2->cons_prox();
			}
		}
	}
	return enc_arc;
}
//PUBLICO
template<class elemento>
bool Digrafo<elemento>::existe_arco(elemento v1,elemento v2)
{
	NodoVert<elemento> *aux=vertices;
	NodoArc<elemento> *aux2;
	bool enc_vert=false, enc_arc=false;
	if((vertices!=NULL)&&(num_arc>0))
	{
		while((!enc_vert)&&(aux!=NULL))
		{
			if(aux->cons_info()==v1)
			{
				enc_vert=true;
			}
			else
			{
				aux=aux->cons_prox();
			}
		}
		enc_arc=existe_arc(aux,v2);
	}
	return enc_arc;
}
//F_EXISTE ARCO
//ELIMINAR VERTICE
//PRIVADOlista<elemento> predecesores(elemeno v)
template<class elemento>
void Digrafo<elemento>::delete_vertice(NodoVert<elemento> *v)
{
	NodoVert<elemento> *aux=v,*aux2=vertices;
	NodoArc<elemento> *auxx=v->cons_arcos(),*auxx2;
	int i;
	for(i=0;i<num_vert;i++)
	{
		delete_arco(aux2,aux->cons_info());
		aux2=aux2->cons_prox();
	}
	if(v->cons_arcos()!=NULL)
	{
		while(auxx->cons_prox()!=NULL)
		{
			auxx2=auxx->cons_prox();
			auxx->mod_prox(auxx2->cons_prox());
			auxx2->mod_prox(NULL);
			auxx2->mod_vert(NULL);
			delete auxx2;
			num_arc--;
		}
		delete v->cons_arcos();
		v->mod_arcos(NULL);
		num_arc--;
	}
	
	
}
//PUBLICO
template<class elemento>
void Digrafo<elemento>::eliminar_vertice(elemento v)
{
	if(existe_vertice(v))
	{
		NodoVert<elemento> *aux=vertices;
		if(vertices->cons_info()==v)
		{
			delete_vertice(aux);
			vertices=vertices->cons_prox();
			aux->mod_prox(NULL);
			delete aux;
		}
		else
		{
			while(aux->cons_prox()->cons_info()!=v)
			{
				aux=aux->cons_prox();
			}
			delete_vertice(aux->cons_prox());
			aux->mod_prox(aux->cons_prox()->cons_prox());
		}
		num_vert--;
	}
}
//F_ELIMINAR_VERTICE

//SUCESORES
//PUBLICO:
template<class elemento>
lista<elemento> Digrafo<elemento>::sucesores(elemento v)
{
	lista<elemento> suc,suc2;
	NodoVert<elemento> *aux=vertices;
	bool encontrado=false;
	while((!encontrado)&&(aux!=NULL))
	{
		if(aux->cons_info()==v)
		{
			encontrado=true;
		}
		else
		{
			aux=aux->cons_prox();
		}
	}
	if(aux!=NULL)
	{
		if(aux->cons_arcos()!=NULL)
		{
			NodoArc<elemento> *aux2=aux->cons_arcos();
			while(aux2!=NULL)
			{
				suc.insertar(aux2->cons_vert()->cons_info(),1);
				aux2=aux2->cons_prox();
			}
		}
	}
	while(!suc.es_vacia())
	{
		suc2.insertar(suc.consultar(1),1);
		suc.eliminar(1);
	}
	return suc2;
}
//F_SUCESORES

//PREDECESORES
template<class elemento>
lista<elemento> Digrafo<elemento>::predecesores(elemento v)
{
	lista<elemento> pre;
	NodoVert<elemento> *aux=vertices;
	while(aux!=NULL)
	{
		if(existe_arc(aux,v))
		{
			pre.insertar(aux->cons_info(),1);
		}
		aux=aux->cons_prox();
	}
	return pre;
}

//POS VERT
//PRIVADO
template<class elemento>
int Digrafo<elemento>::pos_vert(elemento v)
{
	NodoVert<elemento> *aux=vertices;
	bool encontrado=false;
	int i=0,n=0;
	while((!encontrado)&&(aux!=NULL))
	{
		if(aux->cons_info()==v)
		{
			n=i;
			encontrado=true;
		}
		else
		{
			i++;
			aux=aux->cons_prox();
		}
	}
	return n;
}
//F_POS VER

//POST_VERT
//PRIVADO
template<class elemento>
elemento Digrafo<elemento>::vert_pos(int pos)
{
	NodoVert<elemento> *aux=vertices;
	int i=0;
	for(i=0;i<pos;i++)
		aux=aux->cons_prox();
	return aux->cons_info();
}

//BFS
//PUBLICO
template<class elemento>
void Digrafo<elemento>::BFS(elemento s,int color[],int Predecesor[],int distancia[])
{
	cola<elemento> Q;
	lista<elemento> sucesor;
	elemento u,v;
	int i,pos;
	for(i=0;i<num_vert;i++)
	{
		color[i]=0;
		Predecesor[i]=0;
		distancia[i]=-1;
	}
	pos=pos_vert(s);
	color[pos]=1;
	distancia[pos]=0;
	Predecesor[pos]=0;
	Q.encolar(s);
	while(!Q.es_vacia())
	{
		u=Q.frente();
		sucesor=sucesores(u);
		while(!sucesor.es_vacia())
		{
			v=sucesor.consultar(1);
			sucesor.eliminar(1);
			pos=pos_vert(v);
			if(color[pos]==0)
			{
				color[pos]=1;
				distancia[pos]=distancia[pos_vert(u)]+1;
				Predecesor[pos]=pos_vert(u);
				Q.encolar(v);
			}
		}
		Q.desencolar();
		color[pos_vert(u)]=2;
	}
}
//F_BFS

//DFS
//VISITAR DFS
template<class elemento>
void Digrafo<elemento>::visitarDFS(elemento u,int F[],int color[],int Predecesor[],int distancia[],int &marca)
{
	elemento v;
	int pos=pos_vert(u);
	lista<elemento> sucesor;
	color[pos]=1;
	marca=marca+1;
	distancia[pos]=marca;
	sucesor=sucesores(u);
	while(!sucesor.es_vacia())
	{
		v=sucesor.consultar(1);
		pos=pos_vert(v);
		if(color[pos]==0)
		{
			Predecesor[pos]=pos_vert(u);
			visitarDFS(v,F,color,Predecesor,distancia,marca);
		}
		sucesor.eliminar(1);
	}
	color[pos_vert(u)]=2;
	F[pos_vert(u)]=marca;
	marca=marca+1;
}
//DFS (PROCEDIMIENTO!)
template<class elemento>
void Digrafo<elemento>::DFS(int F[],int color[],int Predecesor[],int distancia[])
{
		elemento u;
		cola<elemento> q;
		NodoVert<elemento> *aux=vertices;
		int marca,i;
		for(i=0;i<num_vert;i++)
		{
			color[i]=0;
			Predecesor[i]=-1000;
			F[i]=0;
			distancia[i]=0;
		}
		marca=0;
		while(aux!=NULL)
		{
			u=aux->cons_info();
			if(color[pos_vert(u)]==0)
			{
				visitarDFS(u,F,color,Predecesor,distancia,marca);
			}
			aux=aux->cons_prox();
		}
}
//F_DFS

template<class elemento>
int Digrafo<elemento>::numero_comp_conexas()
{
		int i,ncc;
		char color[numero_vertices()];
		cola<elemento> C;
		elemento u,v;
		lista<elemento> L;
		
		for(i=0;i<numero_vertices();i++)
		{
				color[i]='b';
		}
		ncc=0;
		for(i=0;i<numero_vertices();i++)
		{
			if(color[i]=='b')
			{
				ncc=ncc+1;
				color[i]='g';
				C.encolar(vertice_posicion(i));
			}
			while(!C.es_vacia())
			{
				u=C.frente();
				C.desencolar();
				L=sucesores(u);
			
				while(!L.es_vacia())
				{
					v=L.consultar(1);
					L.eliminar(1);
					if(color[posicion_vertice(v)]=='b')
					{
							color[posicion_vertice(v)]='g';
							C.encolar(v);
					}
				}
				color[posicion_vertice(u)]='n';
			}
		}
		return ncc;
}
template<class elemento>
void Digrafo<elemento>::clear()
{
	Digrafo<elemento> b;
	b.vertices=vertices;
	vertices=NULL;
	b.num_vert=num_vert;
	num_vert=0;
	b.num_arc=num_arc;
	num_arc=0;
}

template<class elemento>
void Digrafo<elemento>::imprimir()
{
		NodoVert<elemento> *vert;
		NodoArc<elemento> *arco;
	
	vert = vertices;
	while(vert != NULL)
	{
		cout << endl << vert->cons_info();
		arco = vert->cons_arcos();
		while(arco != NULL)
		{
			cout << " -> " << arco->cons_vert();
			arco = arco->cons_prox();
		}
		vert = vert->cons_prox();
	}
	cout << endl;
}
//DESTRUCTOR
template<class elemento>
Digrafo<elemento>::~Digrafo()
{
	if(vertices!=NULL)
	{
		NodoVert<elemento> *aux=vertices;
		while(vertices!=NULL)
		{
			aux=vertices;
			delete_vertice(vertices);
			vertices=vertices->cons_prox();
			aux->mod_prox(NULL);
			delete aux;
			aux=NULL;
			num_vert--;
		}
	}
}
//F_DESTRUCTOR

#endif
