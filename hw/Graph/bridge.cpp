#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
class Graph{
    int total_vertex;
    list<pair<int, int>> *adj;

public:

    Graph(int vertex);//constructor
    void add_edge(int v1, int v2, int weight, int start, int end);
    void erase_edge(int v1, int v2, int weight);
    int shortest_path(int start, int end);
    void print_adj();
};

Graph::Graph(int total_vertex){
    this->total_vertex = total_vertex+1;
    adj = new list<pair<int, int>> [total_vertex+1];
}

void Graph :: add_edge(int v1, int v2, int weight, int start, int end){
    if(v1 == start)adj[v1].push_back(make_pair(v2, weight));
    else if(v2 == start)adj[v2].push_back(make_pair(v1, weight));
    else if(v1 == end)adj[v2].push_back(make_pair(v1, weight));
    else if(v2 == end)adj[v1].push_back(make_pair(v2, weight));
    else{
        adj[v1].push_back(make_pair(v2, weight));
        adj[v2].push_back(make_pair(v1, weight));
    }
    //cout << (*adj[v1].end()).first << " " << (*adj[v1].end()).second << endl;
    //cout << (*adj[v2].end()).first << " " << (*adj[v2].end()).second << endl;
}

void Graph :: erase_edge(int v1, int v2, int weight){
    adj[v1].pop_back();
    adj[v2].pop_back();

    //cout << (*adj[v1].end()).first << " " << (*adj[v1].end()).second << endl;
    //cout << (*adj[v2].end()).first << " " << (*adj[v2].end()).second << endl;
}

int Graph:: shortest_path(int start, int end){
    priority_queue<pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(total_vertex, INF);
    pq.push(make_pair(0, start));
    dist[start] = 0;

    while(!pq.empty()){
        int from = pq.top().second;//the target vertex which holds the current min cost in the queue
        //cout << from << endl;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[from].begin(); i != adj[from].end(); ++i){
            int to = (*i).first;
            int weight = (*i).second;

            if(dist[to] > dist[from] + weight){
                dist[to] = dist[from] + weight;
                //cout << "weight = " << weight << endl;
                //cout << "dist[" << to << "] > dist[" << from << "]+ weight : " << dist[to] << endl;
                pq.push(make_pair(dist[to], to));
            }
        }
    }

    return dist[end];
}

/*void Graph:: print_adj(){
    int i = 1;
    //while(i++){
    cout << (*adj[i].end()).first << " " << (*adj[i].end()).second << endl;
    list< pair<int, int> >::iterator k;
    for(k = adj[i].begin(); k != adj[i].end(); ++k){
        cout << i << " "<< (*k).first <<" " << (*k).second << endl;
    }
    
}*/

int main(){
    int N, S, E;
    int T, B;
    int v, u, w;
    int max;
    cin >> N >> S >> E;
    Graph g(N);
    cin >> T;
    while(T > 0){
        T--;
        cin >> v >> u >> w;
        g.add_edge(v, u, w, S, E);
    }
    //g.print_adj();
    max = g.shortest_path(S, E);
    cin >> B;
    while(B > 0){
        int tmp;
        B--;
        cin >> v >> u >> w;
        g.add_edge(v, u, w, S, E);
        if((tmp = g.shortest_path(S, E)) < max)max = tmp;
        g.erase_edge(v, u, w);
    }
    cout << max << endl;
    return 0;
} 