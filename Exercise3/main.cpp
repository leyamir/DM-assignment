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

int** reset_matrix(int** _distance ,int x, int k) {                     //create distance matrix with x vertexs, each of vertex contains a array of all shortest path to it.
    for (int i= 1; i<= x; i++)
        delete [] _distance[i];
    delete [] _distance;
    _distance = new int* [x + 1];
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
void cleanup_matrix(int*** ptr_dis, int x, int k, int e){
    for (int i = 0; i < e; i++) {
        for(int j = 1; j <= x; j++) delete [] ptr_dis[i][j];
        delete [] ptr_dis[i];
    }
    delete [] ptr_dis;
}
void shortestkth(int** ptr_distance, std::vector <int2> *map, int m, int _k) {
    ptr_distance[m][_k - 1] = 0;                                //starting at vertex m
    q.push(int2(0, m));
    while(!q.empty()) {
        int shortest_dis = q.front().first;                    //take shortest distance to this vertex
        int vertex = q.front().second;                         //this is main vertex and next step we will traveses neighbor of it
        q.pop();                                               //remove this vertex from the queue
        for(int i = 0; int neighbor = map[vertex][i].second; i++) {                     //by pushing 0 to the end of vector so that the condition of the loop look nicer
            if(ptr_distance[neighbor][_k - 1] > shortest_dis + map[vertex][i].first) {   //if the shortest distance to neighbor vertex is higher than shortest distance of main vertex plus the distance between them.
                ptr_distance[neighbor][_k - 1] = shortest_dis + map[vertex][i].first;    //updating it
                q.push(int2(ptr_distance[neighbor][_k - 1], neighbor));                  //pushing to the queue
                
                std::sort(ptr_distance[neighbor], ptr_distance[neighbor] + _k);          //For example k = 3, [MAX MAX shortest_dis] so we need to sort it to [shortest_dis MAX MAX]
            }
        }
    }
}

int** create_mandatory_edge_matrix(int number_of_edge) {
    int** _mandatory = new int* [number_of_edge];
    for(int i = 0; i < number_of_edge; i++) {
        _mandatory[i] = new int [3];
    }
    for(int i = 0; i < number_of_edge; i++) {
        int x, y, distance;
        std::cin >> x >> y >> distance;
        _mandatory[i][0] = x;
        _mandatory[i][1] = y;
        _mandatory[i][2] = distance;
    }
    return _mandatory;
}

int*** create_matrix(int e, int x, int k) {                     //create distance matrix with x vertexs, each of vertex contains a array of all shortest path to it.
    int*** _distance = new int** [e];
    for(int i = 0; i < e; i++) {
        _distance[i] = new int* [x + 1];
    }
    for(int i = 0; i < e; i++) {
        for(int j = 1; j <= x; j++) {
            _distance[i][j] = new int [k];
        }
    }
    for(int _e = 0; _e < e; _e++) {
        for(int i = 1; i <= x; i++) {
            for(int j = 0; j < k; j++) {
                _distance[_e][i][j] = MAX;                      //According to Dijkstra, initial of shortest distance is a maxium integer
            }
        }
    }
    return _distance;
}
std::vector <int> or_operator_(int** _ptr_distance, int*** ptr, int e, int size, int n) {
    std::vector <int> _ptr;
    for(int i = 0; i < size; i++) {
        _ptr.push_back(_ptr_distance[n][i]);
    }
    std::vector <int> temp;
    for(int _e = 0; _e < e; _e++) {
        int b = 0, z = 0;
        temp.clear();
        while(z < _ptr.size() && b < size) {
            if(_ptr[z] == MAX) break;
            if(_ptr[z] == ptr[_e][n][b]){
                z++;
                b++;
                continue;
            }
            if(_ptr[z] < ptr[_e][n][b]) {
                temp.push_back(_ptr[z]);
                z++;
            }
            else {
                b++;
            }
        }
        _ptr = temp;
    }
    return _ptr;
}
int main() {
    int x, y, m, n, k, e;
    std::cin >> x >> y >> m >> n >> k >> e;                         //x,y is number of vertexs and edges respectively. m,n is initial and terminal vertex. k is kth shortest path
    
    int** mandatory_edge = create_mandatory_edge_matrix(e);

    std::vector <int2> *map = new std::vector <int2> [x + 1];  //create pointer to array (mean that there is a array of vector)
    std::vector <int> result;

    read_map(map, y, x);
    auto start = std::chrono::steady_clock::now();
    int** ptr_distance = create_matrix(x, k);
    int _k = 0;
    do {
        _k += 300;
        int*** ptr_distance_storing = create_matrix(e, x, _k);
        int** ptr_distance = create_matrix(x, _k);
        shortestkth(ptr_distance, map, m, _k);
        for(int u = 0; u < e; u++) {
            for(int z = 0; int v = map[mandatory_edge[u][0]][z].second; z++) {
                if(mandatory_edge[u][1] == v and mandatory_edge[u][2] == map[mandatory_edge[u][0]][z].first) {
                    map[mandatory_edge[u][0]].erase(map[mandatory_edge[u][0]].begin() + z);
                    break;
                }
            }
            shortestkth(ptr_distance_storing[u] ,map, m, _k);
            map[mandatory_edge[u][0]].pop_back();
            map[mandatory_edge[u][0]].push_back(int2(mandatory_edge[u][2], mandatory_edge[u][1]));
            map[mandatory_edge[u][0]].push_back(int2(0, 0));
        }
        result = or_operator_(ptr_distance, ptr_distance_storing, e, _k, n);
        if(result.size() >= k) break;
        cleanup_matrix(ptr_distance_storing, x, _k, e);
        reset_matrix(ptr_distance, x, _k);
    }
    while(result.size() != k);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    auto time = std::chrono::duration <double> (diff).count();
    if(time > 5.0) {
        std::cout<<"Timed out, meaning can not find kth shortest path or the result met the our limitation !";
        return 0;
    }
    std::cout <<"Executation time: "<< std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;
    for(int i = 0; i < k; i++) {
        std::cout << result[i] << " ";                //print list of shortest distance to our terminal vertex in increasing order
    }
    std::cout<<std::endl;
    std::cout<<"The result: "<<result[k - 1];
    return 0;
}