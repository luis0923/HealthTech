#include "../MatrixGenerator/DataSetReader.hpp"
#include <climits>

static const int INF = 1e9;

class FloydWarshall
{
public:
    DataSetRead dataSet;
    int pondMatrix[21][21];
    
    void matrixGenerator()
    {
        

        for(int i = 0; i <= dataSet.amountVertex; i++)
        {
            for(int j = 0; j <= dataSet.amountVertex; j++)
            {
                if(i == j)
                {
                    pondMatrix[i][j] = 0;
                }
                else
                {
                    pondMatrix[i][j] = INF;
                }
                
            }
        }
        for(const auto& e: dataSet.edges)
        {
            pondMatrix[e.from][e.to] = e.weight;
        }
    };
    void floydWarshall()
    {
        for(int k = 1; k <= dataSet.amountVertex; k++)
        {
            for(int i = 1; i<=dataSet.amountVertex; i++)
            {
                for(int j = 1; j<=dataSet.amountVertex; j++)
                {
                    if(pondMatrix[i][k] != INF && pondMatrix[k][j] != INF && pondMatrix[i][k] + pondMatrix[k][j] < pondMatrix[i][j])
                    {
                        pondMatrix[i][j] = pondMatrix[i][k] + pondMatrix[k][j];
                    }
                }
            }
        }
    };
    void printMatrix()
    {
        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                if(pondMatrix[i][j] == INF)
                {
                    std::cout << "INF ";
                }
                else
                {
                    std::cout << pondMatrix[i][j] << " ";
                }
            }

            std::cout << "\n";
        }
    };
    int baseAmbulanceDefiner()
    {
        long long routeSum = LLONG_MAX;
        int bestVertex = 0;
        
        
        

        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            long long atualRoute = 0;
            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                atualRoute += pondMatrix[i][j];

            }
            if(i == 1 || routeSum > atualRoute)
            {
                routeSum = atualRoute;
                bestVertex = i;
            }
        }
        std::cout << bestVertex << '\n';
        return bestVertex;
    }
};
