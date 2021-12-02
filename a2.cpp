#include <bits/stdc++.h>

using namespace std;


void findkthshortest(int n, int m, int k, int edges[][3]){

    vector<vector<pair<int, int>> > map_(n + 1);
    for (int i = 0; i < m; i++) {

        map_[edges[i][0]].push_back({edges[i][1], edges[i][2]});
    }


    vector<vector<int> > dist(n + 1, vector<int>(k, 1e9));

    priority_queue<pair<int, int>,
                   vector<pair<int, int> >,
                   greater<pair<int, int> > >

        pq;

    pq.push({0, 1});
    dist[1][0] = 0;


    while (!pq.empty()) {

        int u = pq.top().second;

        int d = (pq.top().first);
        pq.pop();
        if (dist[u][k - 1] < d)
            continue;
        vector<pair<int, int> > v = map_[u];

    for (int i = 0; i < v.size(); i++) {

            int a = v[i].first;
            int b = v[i].second;

            if (d + b < dist[a][k - 1]) {
                dist[a][k - 1] = d + b;

                sort(dist[a].begin(), dist[a].end());

                pq.push({ (d + b),a });
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
    else cout << "The " << K << " shortest path are: ";

    findkthshortest(N, M, K, edges);
    return 0;
}
