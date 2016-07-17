#include <iostream>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

using namespace std;

int **adj;  // Matriz de Adjacentes
int **cost; // Matriz de Custos
int minPath = INT_MAX;      // Custo do Melhor Caminho Atual
int BestPath[50];      // Melhor Caminho
int V, E;
#define V_MAX 20

int visited (int city, int hops, const int *path)
{
    for (int i = 0; i < hops; i++)
        if (path[i] == city) return 1;
    return 0;
}

void visit(const int city, int hops, int lenth, int *path)
{
    int visitCity = 0;

	if(hops == V + 1 && city == 0) visitCity = 1;
	else if(!visited(city, hops, path)) // se não foi visitada
    {
		visitCity = 1;
		path[hops-1] = city;
    }
    
    if(visitCity)
    {
        if (lenth >= minPath)
        {
            return;
        }
        if(hops == V + 1)
        {
            if (lenth < minPath)
            {
                minPath = lenth;
            }
            for(int i=0;i<V;i++)
            {
                BestPath[i] = path[i];
            }

			return;
        }
	    for (int i = 0; i < V; i++)
        {
			if(adj[city][i])
			{		 
				visit(i, hops+1, lenth+cost[city][i], path);
			}
        }
    }
}

int main()
{
    int a, b, d;
    double begin, end;
    double time_spent;
	int Visitedi[1000];
	int ans;
	
	cin >> V >> E;

	if(true)
	{
		adj = new int*[V];
		cost = new int*[V];
		for(int i = 0; i < V; i++)
		{
			adj[i] = new int[V]();
			cost[i] = new int[V]();
		}
		
		for(int i = 0; i < E; i++)
		{
			cin >> a >> b >> d;
			cost[a][b] = d;
			cost[b][a] = d;
			adj[a][b] = 1;
		}
		
		begin = omp_get_wtime();
		
		fill(Visitedi, Visitedi + V, -1);

		visit(0, 1, 0, Visitedi);
		
		ans = minPath;
	}
    
    end = omp_get_wtime();

    printf("%d\n", ans);
	
	printf ("Elapsed time is: %f s\n\n", end - begin);
    
    return 0;
}


