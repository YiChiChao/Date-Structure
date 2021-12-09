#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include<iomanip>


using namespace std;
#define INF (float)0x3f3f3f3f
class Graph{
    int total_vertex;
    list<pair<int, float>> *adj;

public:

    Graph(int vertex);//constructor
    void add_edge(int v1, int v2, float probability);
    void erase_edge(int v1, int v2, float probability);
    float shortest_path(int start, int end);
    void print_adj();
};

Graph::Graph(int total_vertex){
    this->total_vertex = total_vertex;
    adj = new list<pair<int, float>> [total_vertex];
}

void Graph :: add_edge(int v1, int v2, float probability){
    adj[v1].push_back(make_pair(v2, probability*(-1)));
    adj[v2].push_back(make_pair(v1, probability*(-1)));

    //cout << (*adj[v1].end()).first << " " << (*adj[v1].end()).second << endl;
    //cout << (*adj[v2].end()).first << " " << (*adj[v2].end()).second << endl;
}

void Graph :: erase_edge(int v1, int v2, float probability){
    adj[v1].pop_back();
    adj[v2].pop_back();

    //cout << (*adj[v1].end()).first << " " << (*adj[v1].end()).second << endl;
    //cout << (*adj[v2].end()).first << " " << (*adj[v2].end()).second << endl;
}

float Graph:: shortest_path(int start, int end){
    
    priority_queue<pair<float, int>, vector <pair<float, int>>, greater<pair<float, int>>> pq;
    vector<float> dist(total_vertex, INF);
    pq.push(make_pair(0, start));
    dist[start] = -1;

    while(!pq.empty()){
        int from = pq.top().second;//the target vertex which holds the current min cost in the queue
        //cout << from << endl;
        pq.pop();

        list< pair<int, float> >::iterator i;
        for (i = adj[from].begin(); i != adj[from].end(); ++i){
            int to = (*i).first;
            float probability = (*i).second;

            if(dist[to] > dist[from] * probability * (-1) ){
                dist[to] = dist[from] * probability *(-1) ;
                //cout << "weight = " << probability << endl;
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
    int M, R;
    int v, u;
    float w;
    float max_probability;
    cin >> N >> M >> R;
    Graph g(N);
    while(M > 0){
        M--;
        cin >> v >> u >> w;
        g.add_edge(v, u, w);
    }
    while(R > 0){
        R--;
        cin >> S >> E;
        if(E >= N){
            cout<< "0.00000" <<endl;
            continue;
        } 
        max_probability = g.shortest_path(S, E);
        if(max_probability == INF){
            cout<< "0.00000" <<endl;
            continue;
        }
        max_probability *= -1;
        
        //cout << max_probability << endl;
        cout<< fixed << setprecision(5) << max_probability <<endl;
    }
    //g.print_adj();
    return 0;
} 