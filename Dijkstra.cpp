#include "FloydWarshall.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Dijkstra
{
    
    public:
    
    vector<vector<Edge>> AdjacencyList;
    DataSetRead dataset;
    


    

    Dijkstra()
    {
        AdjacencyList.resize(dataset.amountVertex + 1);

        for(const auto& e : dataset.edges)
        {
            AdjacencyList[e.from].push_back(e);
        }

        //baseAmbulance = floydwarshall.baseAmbulanceDefiner();
    };

    
   
    
    int bestRouteOfBaseToAccident(int base, int accident) //USando Dijkstra calcula a melhor rota da base até o acidente
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> dijkstra;
        vector<int> dist(dataset.amountVertex + 1, INT_MAX);

        dist[base] = 0;
        dijkstra.push({0, base});

        while(!dijkstra.empty())
        {
            auto[d, u] = dijkstra.top();
            dijkstra.pop();

            if(d > dist[u]){continue;}
            
            for(const auto& edge : AdjacencyList[u])
            {
                
                if(edge.weight < 0){continue;}

                if(dist[u] + edge.weight < dist[edge.to])
                {
                    dist[edge.to] = dist[u] + edge.weight;
                    dijkstra.push({dist[edge.to], edge.to});
                }
                if(u == accident)
                {
                    return dist[u];
                }
            }
        }
        return dist[accident];
    };

};

int main()
{
    Dijkstra dijkstra;
    FloydWarshall floydwarshall;

    floydwarshall.matrixGenerator();
    floydwarshall.floydWarshall();
    cout << "Deu certo\n" <<dijkstra.bestRouteOfBaseToAccident(floydwarshall.baseAmbulanceDefiner(), 8);

    return 0;
};