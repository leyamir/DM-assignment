#include <iostream>
#include <queue>

using namespace std;

int number_of_nodes = 4;
bool bfs(int **residual_graph, int source, int sink, int path[]);
int fordFulkerson(int **graph, int source, int sink);
int main()
{
    cout << "How many vertices of network? ";
    cin >> number_of_nodes;
    cout << endl;
    int **graph;
    graph = new int *[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
    {
        graph[i] = new int[number_of_nodes];
    }
    cout << "Input graph " << endl;
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            cin >> graph[i][j];
        }
    }
    int source, sink;
    cout << "Which is source? ";
    cin >> source;
    cout << endl;
    cout << "Which is sink? ";
    cin >> sink;
    cout << endl;
    cout << "The maximum possible flow is " << fordFulkerson(graph, source, sink);
    return 0;
}

bool bfs(int **residual_graph, int source, int sink, int path_from_source_to_sink[])
{
    bool visited_table[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
    {
        visited_table[i] = false;
    }
    queue<int> q;
    q.push(source);
    visited_table[source] = true;
    path_from_source_to_sink[source] = -1;
    while (!q.empty())
    {
        int considering_node = q.front();
        q.pop();
        for (int neighbor = 0; neighbor < number_of_nodes; neighbor++)
        {
            if (visited_table[neighbor] == false and residual_graph[considering_node][neighbor] > 0)
            {
                if (neighbor == sink)
                {
                    path_from_source_to_sink[neighbor] = considering_node;
                    return true;
                }
                q.push(neighbor);
                path_from_source_to_sink[neighbor] = considering_node;
                visited_table[neighbor] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int **graph, int source, int sink)
{
    int **residual_graph;

    residual_graph = new int *[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
    {
        residual_graph[i] = new int[number_of_nodes];
    }
    for (int u = 0; u < number_of_nodes; u++)
    {
        for (int v = 0; v < number_of_nodes; v++)
        {
            residual_graph[u][v] = graph[u][v];
        }
    }

    int path_from_source_to_sink[number_of_nodes];
    int posible_max_flow = 0;
    while (bfs(residual_graph, source, sink, path_from_source_to_sink))
    {
        int max_flow_posible_on_path_found_by_bfs = INT_MAX;
        for (int n = sink; n != source; n = path_from_source_to_sink[n])
        {
            int node_adjacent_to_n = path_from_source_to_sink[n];
            max_flow_posible_on_path_found_by_bfs = min(max_flow_posible_on_path_found_by_bfs, residual_graph[node_adjacent_to_n][n]);
        }

        for (int n = sink; n != source; n = path_from_source_to_sink[n])
        {
            int node_adjacent_to_n = path_from_source_to_sink[n];
            residual_graph[node_adjacent_to_n][n] -= max_flow_posible_on_path_found_by_bfs;
            residual_graph[n][node_adjacent_to_n] += max_flow_posible_on_path_found_by_bfs;
        }
        posible_max_flow += max_flow_posible_on_path_found_by_bfs;
    }
    return posible_max_flow;
}