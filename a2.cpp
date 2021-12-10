#include <bits/stdc++.h>

using namespace std;

int INF = 1e9;


void findkthshortest(int n, int m, int k, int edges[][3]){

    vector<vector<pair<int, int>> > map_(n + 1);
    for (int i = 0; i < m; i++) {

        int from = edges[i][0];
        int to = edges[i][1];
        int d = edges[i][2];
        map_[from].push_back({to, d});
    }


    vector<vector<int>> dist(n + 1, vector<int>(k, INF));
    dist[1][0] = 0;


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    pq.push({0,1});


    while (!pq.empty()) {

        int N = pq.top().second;
        int D = (pq.top().first);
        pq.pop();

            if (dist[N][k - 1] < D) continue;
            vector<pair<int, int> > near = map_[N];

            for (int i = 0; i < near.size(); i++) {
                    int a = near[i].first;
                    int b = near[i].second;

                    if (D + b < dist[a][k - 1]) {
                        dist[a][k - 1] = D + b;
                        sort(dist[a].begin(), dist[a].end());


                        pq.push({(D + b),a });
                    }
            }
    }


    for (int i = 0; i < k; i++) {
        cout << dist[n][i] << " ";
    }
}



int main(){
    int N, M, K; //N = nodes, M = edges
    cin >> N >> M >> K;

    int edges[M][3];
    for (int i=0; i<M; i++)
        for (int j=0; j<3; j++) cin >> edges[i][j]; //example for input: edges = {1, 2, 3} means the distance from 1 to 2 is 3.

    if (K == 1) cout << "The " << K << " shortest path is: ";
    else cout << "The " << K << " shortest paths are: ";

    findkthshortest(N, M, K, edges);
    return 0;
}
