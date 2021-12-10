#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int v;
    int flow;
    int capacity;
    int index_of_reverse_edge;
};

class Graph
{
    int number_of_nodes;
    int *level;
    vector<Edge> *adj;

public:
    Graph(int number_of_nodes)
    {
        adj = new vector<Edge>[number_of_nodes];
        this->number_of_nodes = number_of_nodes;
        level = new int[number_of_nodes];
    }
    void addEdge(int u, int v, int capacity)
    {
        Edge a{v, 0, capacity, int(adj[v].size())};
        Edge b{u, 0, 0, int(adj[u].size())};

        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    bool BFS(int source, int sink);
    int sendFlow(int source, int flow, int sink, int ptr[]);
    int DinicMaxflow(int source, int sink);
};

bool Graph::BFS(int source, int sink)
{
    for (int i = 0; i < number_of_nodes; i++)
        level[i] = -1;
    level[source] = 0;
    list<int> q;
    q.push_back(source);

    vector<Edge>::iterator i;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++)
        {
            Edge &e = *i;
            if (level[e.v] < 0 && e.flow < e.capacity)
            {
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }
    return level[sink] < 0 ? false : true;
}

int Graph::sendFlow(int u, int flow, int sink, int start[])
{
    int current_vertex = u;
    if (current_vertex == sink)
        return flow;
    for (; start[current_vertex] < adj[current_vertex].size(); start[current_vertex]++)
    {
        Edge &e = adj[current_vertex][start[current_vertex]];
        if (level[e.v] == level[current_vertex] + 1 && e.flow < e.capacity)
        {
            int current_flow = min(flow, e.capacity - e.flow);
            int temp_flow = sendFlow(e.v, current_flow, sink, start);
            if (temp_flow > 0)
            {
                e.flow += temp_flow;
                adj[e.v][e.index_of_reverse_edge].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

int Graph::DinicMaxflow(int source, int sink)
{
    if (source == sink)
        return -1;
    int total_flow = 0;
    while (BFS(source, sink) == true)
    {
        int *start = new int[number_of_nodes + 1]{0};
        while (int flow = sendFlow(source, INT_MAX, sink, start))
            total_flow += flow;
    }
    return total_flow;
}
int main()
{
    cout << "How many vertices? ";
    int V;
    cin >> V;
    Graph g(V);
    cout << "How many edges? ";
    int edges;
    cin >> edges;
    cout << "Input graph" << endl;
    int u, v, w;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    cout << "Which is source? ";
    int s;
    cin >> s;
    cout << "Which is sink? ";
    int d;
    cin >> d;
    cout << "Maximum flow is " << g.DinicMaxflow(s, d);
    return 0;
}