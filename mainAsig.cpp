///   Universidad de Carabobo
///   Facultad de Ciencias y Tecnologia - FACyT
///   Algoritmos y Programacion II 
///   Jissel Rodriguez 
///   **********************************************************************/

#include"digrafo.h"
#include<iostream>
#include<fstream>
using namespace std;

int main()
{	
	Digrafo<char> grafo;
	lista<char> suce;
	int num_casos,i,s,num_comp;
	char a,b,aux;
	bool bandera;
	//ifstream in("pruebaAsig.txt"); /*desbloquear para entrada por archivo*/
	bandera=false;
	cin>>num_casos;
	
	for(i=0;i<num_casos;i++)
	{
		bandera=false;
		while((a!='*')&&(b!='*'))
		{
			cin>>a;
			cin>>b;
			if((a!='*')||(b!='*'))
			{
				if(!grafo.existe_vertice(a))
				{
					grafo.insertar_vertice(a);
				}
				if(!grafo.existe_vertice(b))
				{
					grafo.insertar_vertice(b);
				}
				grafo.insertar_arco(a,b);//se coloca al derecho y alreves para simular el grafo no dirigido 
				grafo.insertar_arco(b,a);
			}
			else
			{
				num_comp=grafo.numero_comp_conexas();
				if(num_comp!=1)
				{
			//	cout<<"Puede Fallar"<<endl;
					bandera=true;
				}
				s=0;
				while((s < grafo.numero_vertices()) && !bandera)
				{
					aux=grafo.vertice_posicion(0); //guardo un vertice
					suce=grafo.sucesores(aux);     //sucesores de ese vertice;
					grafo.eliminar_vertice(aux);
					num_comp=grafo.numero_comp_conexas();
					if(num_comp!=1)
					{
						bandera=true;
					}
					else
					{
							grafo.insertar_vertice(aux);
							while(!suce.es_vacia())
							{
									grafo.insertar_arco(aux,suce.consultar(1));
									grafo.insertar_arco(suce.consultar(1),aux);
									suce.eliminar(1);
							}
							s=s+1;
					}
				}
				if(bandera)
				{
					cout<<"Puede Fallar"<<endl;
				}
				else
				{
					cout<<"Sigue Funcionando"<<endl;
				}
			}
		}
		
		grafo.clear();//inicializa el grafo para el siguiente caso
		a='+';//inicializa las variables en caracter distinto a *
		b='+';
	}
	//in.close(); /* desbloquear para entrada por archivo*/
	return 0;
}	
	

