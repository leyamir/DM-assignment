/*
    Author: Nguyen Dang Binh Nguyen
    ID: 2052620
*/

#include <bits/stdc++.h>
#define MAX INT_MAX

typedef std::pair <int, int> int2;
std::queue <int2> q;

void read_map(std::vector <int2> *_map, int size, int number_of_vertex) {
    for(int i = 1; i <= size; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;                        //x is initial vertex, y is terminal vertex, z is distance from x to y
        _map[x].push_back(int2(z, y));                  //directed graph
    }
    for(int i = 1; i <= number_of_vertex; i++) {
        _map[i].push_back(int2(0, 0));                  //push 0 at the back of our vector so that we can exit the loop over the vector by detect 0
    }
}
int** create_matrix(int x, int k) {                     //create distance matrix with x vertexs, each of vertex contains a array of all shortest path to it.
    int** _distance = new int* [x + 1];
    for(int i = 1; i <= x; i++) {
        _distance[i] = new int [k];
    }
    for(int i = 1; i <= x; i++) {
        for(int j = 0; j < k; j++) {
            _distance[i][j] = MAX;                      //According to Dijkstra, initial of shortest distance is a maxium integer
        }
    }
    return _distance;
}

int main() {
    int x, y, m, n, k;
    std::cin >> x >> y >> m >> n >> k;                         //x,y is number of vertexs and edges respectively. m,n is initial and terminal vertex. k is kth shortest path
    
    std::vector <int2> *map = new std::vector <int2> [x + 1];  //create pointer to array (mean that there is a array of vector)
    
    read_map(map, y, x);

    int** ptr_distance = create_matrix(x, k);   

    ptr_distance[m][k - 1] = 0;                                //starting at vertex m
    q.push(int2(0, m));

    while(!q.empty()) {
        int shortest_dis = q.front().first;                    //take shortest distance to this vertex
        int vertex = q.front().second;                         //this is main vertex and next step we will traveses neighbor of it
        q.pop();                                               //remove this vertex from the queue
        for(int i = 0; int neighbor = map[vertex][i].second; i++) {                     //by pushing 0 to the end of vector so that the condition of the loop look nicer
            if(ptr_distance[neighbor][k - 1] > shortest_dis + map[vertex][i].first) {   //if the shortest distance to neighbor vertex is higher than shortest distance of main vertex plus the distance between them.
                ptr_distance[neighbor][k - 1] = shortest_dis + map[vertex][i].first;    //updating it
                q.push(int2(ptr_distance[neighbor][k - 1], neighbor));                  //pushing to the queue
                
                std::sort(ptr_distance[neighbor], ptr_distance[neighbor] + k);          //For example k = 3, [MAX MAX shortest_dis] so we need to sort it to [shortest_dis MAX MAX]
            }
        }
    }
    for(int i = 0; i < k; i++) {
        std::cout << ptr_distance[n][i] << " ";                //print list of shortest distance to our terminal vertex in increasing order
    }
    return 0;
}