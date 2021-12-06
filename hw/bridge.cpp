#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <stack>
using namespace std;
#define INF 0x3f3f3f3f
class Graph{
    int total_vertex;
    list<pair<int, int>> *adj;
    int *previous;
    vector<int> *dist;
public:
    
    Graph(int vertex);//constructor
    void add_edge(int v1, int v2, int weight);
    void erase_edge(int v1, int v2, int weight);
    int shortest_path(int start, int end);
    int choose_bridge(int from, int to, int weight, int start, int end);
    void print_adj();

};

Graph::Graph(int total_vertex){
    this->total_vertex = total_vertex+1;
    adj = new list<pair<int, int>> [total_vertex+1];
    previous = (int*)malloc((total_vertex+1) *sizeof(int));
    dist = new vector<int> (total_vertex+1, INF);
}

void Graph :: add_edge(int v1, int v2, int weight){
    adj[v1].push_back(make_pair(v2, weight));
    adj[v2].push_back(make_pair(v1, weight));

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
    pq.push(make_pair(0, start));
    (*dist)[start] = 0;
    previous[start] = -1;
    while(!pq.empty()){
        int from = pq.top().second;//the target vertex which holds the current min cost in the queue
        //cout << from << endl;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[from].begin(); i != adj[from].end(); ++i){
            int to = (*i).first;
            int weight = (*i).second;

            if((*dist)[to] > (*dist)[from] + weight){
                (*dist)[to] = (*dist)[from] + weight;
                previous[to] = from;
                //cout << "weight = " << weight << endl;
                //cout << "dist[" << to << "] > dist[" << from << "]+ weight : " << dist[to] << endl;
                pq.push(make_pair((*dist)[to], to));
            }
        }
    }

    return (*dist)[end];
}

int Graph:: choose_bridge(int from, int to, int weight, int start, int end){
    stack <int> Stack;
    int distance = 0;
    int flag = 0;
    for(auto i:(*dist)){
        std:: cout << i << endl;
    }
    list< pair<int, int> >::iterator i;
    for (i = adj[from].begin(); i != adj[from].end(); ++i){
        if((*i).first == to){
            flag = 1;
            break;
        }
    }
    //we cannot assure whether the start node is closer to the from node, so do the end node and the to node
    if(flag == 0)return ((*dist)[from] - (*dist)[start])+ weight + ((*dist)[end] - (*dist)[to]);
    for(int i = end; i != -1; i = previous[i]){
        if(to != i && from != i){
            Stack.push((*dist)[i]-(*dist)[previous[i]]);
        }
        else if(to == i && (*dist)[i] > (*dist)[from] + weight){
            distance += (*dist)[from] + weight;
            break;
        }
        else if(from == i && (*dist)[i] > (*dist)[to] + weight){
            distance += (*dist)[to] + weight;
            break;
        }
        else return (*dist)[end];
    }
    while(!Stack.empty()){
            distance += Stack.top();
            Stack.pop();
    }
    return distance;
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
    int min;
    cin >> N >> S >> E;
    Graph g(N);
    cin >> T;
    while(T > 0){
        T--;
        cin >> v >> u >> w;
        g.add_edge(v, u, w);
    }
    //g.print_adj();
    min = g.shortest_path(S, E);
    std::cout << "Initial distance: " << min << endl;
    cin >> B;
    while(B > 0){
        int tmp;
        B--;
        cin >> v >> u >> w;
        if((tmp = g.choose_bridge(v, u, w, S, E)) < min){
            min = tmp;
        }
    }
    std::cout << min << endl;
    return 0;
}