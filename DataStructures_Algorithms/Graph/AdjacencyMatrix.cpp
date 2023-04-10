#include <iostream>

using namespace std;

const int vertexCount = 5;
class Graph
{
public:
    void ResetGraph();
    void ConnectDir(int, int);
    void ConnectUndir(int, int);
    void Disconnect(int, int);
    void ShowConnections();
private:
    char vertices[5] {'A', 'B', 'C', 'D', 'E'};
    int edges[vertexCount][vertexCount];
};

int main()
{
    Graph g;

    g.ResetGraph();

    g.ConnectUndir(0,1);
    g.ConnectUndir(0,2);
    g.ConnectUndir(0,3);
    g.ConnectUndir(1,2);
    g.ConnectUndir(1,3);
    g.ConnectUndir(2,4);
    g.ConnectDir(3,4);
    //g.ConnectUndir(4,1);

    g.ShowConnections();
}

//Directed connection
void Graph::ConnectDir(int from, int to)
{
    edges[from][to] = 1;
}

//Undirected connection
void Graph::ConnectUndir(int from, int to)
{
    edges[from][to] = 1;
    edges[to][from] = 1;
}

void Graph::Disconnect(int from, int to)
{
    edges[from][to] = 0;
    edges[to][from] = 0;
}

void Graph::ShowConnections()
{
    for(int i = 0; i < vertexCount; i++)
    {
        for(int j = 0; j < vertexCount; j++)
        {
            cout << edges[i][j];
        }
        cout << endl;
    }
}

void Graph::ResetGraph()
{
    for(int i = 0; i < vertexCount; i++)
    {
        for(int j = 0; j < vertexCount; j++)
        {
            edges[i][j] = 0;
        }
    }
}