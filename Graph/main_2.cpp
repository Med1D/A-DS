//
//  main.cpp
//  Lab5
//
//  Created by Иван Медведев on 07/04/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <ctime>

//алгоритм Дейкстры
const int V=3;
const int n=V;
void Dijkstra(int GR[V][V], int st)
{
    int distance[V], count, index, i, u, m=st+1;
    bool visited[V];
    for (i=0; i<V; i++)
    {
        distance[i]=INT_MAX; visited[i]=false;
    }
    distance[st]=0;
    for (count=0; count<V-1; count++)
    {
        int min=INT_MAX;
        for (i=0; i<V; i++)
            if (!visited[i] && distance[i]<=min)
            {
                min=distance[i]; index=i;
            }
        u=index;
        visited[u]=true;
        for (i=0; i<V; i++)
            if (!visited[i] && GR[u][i] && distance[u]!=INT_MAX &&
                distance[u]+GR[u][i]<distance[i])
                distance[i]=distance[u]+GR[u][i];
    }
    std::cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
    for (i=0; i<V; i++) if (distance[i]!=INT_MAX)
        std::cout<<m<<" -> "<<i+1<<" = "<<distance[i]<<std::endl;
    else std::cout<<m<<" -> "<<i+1<<" = "<<"маршрут недоступен"<<std::endl;
}

//Алгоритм Флойда-Уоршелла
void FU(int D[V][V], int V)
{
    int i, j;
    int k;
    for (i=0; i<V; i++)
        D[i][i]=0;
    
    for (k=0; k<V; k++)
        for (i=0; i<V; i++)
            for (j=0; j<V; j++)
                if (D[i][k] && D[k][j] && i!=j)
                    if (D[i][k]+D[k][j]<D[i][j] || D[i][j]==0)
                        D[i][j]=D[i][k]+D[k][j];
    
    for (i=0; i<V; i++)
    {
        for (j=0; j<V; j++)
            std::cout<<D[i][j]<<"\t";
        std::cout<<std::endl;
    }
}


int main(int argc, const char * argv[]) {
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    Clock::time_point start_time;
    Clock::time_point end_time;
    microseconds ms;
    
    
    
    int start, GR[V][V]={
        {0, 4, 7},
        {4, 0, 3},
        {7, 3, 0},
    };
    std::cout<<"Начальная вершина: ";
    std::cin>>start;
    
    
    start_time = Clock::now();
    Dijkstra(GR, start-1);
    end_time = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end_time - start_time);
    double result1 = (double)ms.count()/1000000;
    
    
    start_time = Clock::now();
    FU(GR, n);
    end_time = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end_time - start_time);
    double result2 = (double)ms.count()/1000000;
    
    std::cout << "Алгоритм Дейкстры: " << std::fixed <<result1 << std::endl;
    std::cout << "Алгоритм Флойда-Уоршелла: " << std::fixed << result2 << std::endl;
    
    return 0;
}
