#ifndef GRAPH_H_
#define GRAPH_H_
//Includes:
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> //USADO EN EL SORT, YA QUE NECESITO ESTO PARA QUE QUEDE EN EL FORMATO DESEADO
#include <stack>
#include <queue>
#include <list>

using namespace std;
class Graph{
    private:
        int bordeList;
		int bordeMat;
		int nodes;
        vector<int> *adjList;
		int *adjMatrix;
    public:
        Graph();
        bool contains(list<int>, int);
        void addList(int, int);
        void addMat(int, int);
        void loadGraphList(string, int);
        void loadGraphMat(string, int, int);
        void sortAdjList();
        string printAdjList();
        string printAdjMat();
        string BFS(int,int);
        string DFS(int, int);
        string Depth(int, int, stack<int>&, list<int>&,vector<vector<int>>&);
        string Breath(int, int, queue<int>&, list<int>&,vector<vector<int>>&);
        string ListVisitados(list<int>);
        string CaminoFinal(vector<vector<int>>&, int, int);

};

Graph::Graph(){
    bordeList=bordeMat=0;
}

bool Graph::contains(list<int> a,int b){ //USO FUNCION VISTA EN CLASE
    	list<int>::iterator it;
		it = find(a.begin(), a.end(), b);
		if(it != a.end())
			return true;
		else
			return false;
}
void Graph::sortAdjList(){
    for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}
void Graph::addList(int u,int v){
    adjList[u].push_back(v);
	adjList[v].push_back(u);
	bordeList++;
}

void Graph::addMat(int u, int v){
    adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	bordeMat++;
}

void Graph::loadGraphList(string n, int nodes_){
    nodes=nodes_;
    adjList= new vector<int>[nodes];
    int a=1;
    int b=3;
    int u,v;

    while(a<n.length()-1){
        u=stoi(n.substr(a,1));
        a+=6;
        v=stoi(n.substr(b,1));
        b+=6;
        addList(u,v);
    }
    sortAdjList();
}
void Graph::loadGraphMat(string n, int nodesa, int nodesb){
    adjMatrix = new int [nodesa*nodesb];
    nodes=nodesa;
    int a=1;
    int b=3;
    int u,v;
    for (int i = 0; i<nodesa*nodesb;i++)
        adjMatrix[i] = 0;
        while(a<n.length()-1){
            u=stoi(n.substr(a,1));
            a+=6;
            v=stoi(n.substr(b,1));
            b+=6;
            addMat(u,v);

    }

}

string Graph::printAdjList(){ //UTILIZE LA FUNCION VISTA EN CLASE
    stringstream aux;
	for (int i = 0; i < nodes; i++){
	    aux << "vertex "
	        << i << " :";
	    for (int j = 0; j < adjList[i].size(); j ++){
			aux << " " << adjList[i][j];
		}
	    aux << " ";
    }
	return aux.str();
}
string Graph::printAdjMat(){
    stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();;
}

string Graph::BFS(int inicio, int obj){
    queue <int> aReccorer;
    list<int> visitados;
    vector<vector<int>> caminos(nodes, vector<int>(1,-1));
    aReccorer.push(inicio);
    string respuesta = Breath(inicio, obj,aReccorer, visitados,caminos);
    return respuesta + CaminoFinal(caminos, inicio, obj);
}

string Graph::Breath(int actual, int obj, queue<int> &buscaren, list<int> &visitados,vector<vector<int>> &caminos){
        if (actual==obj){
        return ListVisitados(visitados);
    }
    else if (buscaren.empty()){
        return "VACIO, NO ENCOTRADO";
    }
    else{
    actual=buscaren.front();
    buscaren.pop();
    visitados.push_back(actual);
    for(int i=0;i<adjList[actual].size();i++)
        if(!contains(visitados, adjList[actual][i])){
            buscaren.push(adjList[actual][i]);
            caminos[adjList[actual][i]][0]=actual;
        }
        return Breath(actual, obj, buscaren, visitados, caminos);
    }
}
string Graph::DFS(int inicio, int obj){
    stack <int> aReccorer;
    list<int> visitados;
    vector<vector<int>> caminos(nodes, vector<int>(1,-1));
    aReccorer.push(inicio);
    string respuesta = Depth(inicio, obj,aReccorer, visitados,caminos);
    return respuesta + CaminoFinal(caminos, inicio, obj);
}
string Graph::Depth(int actual, int obj, stack<int> &buscaren, list<int> &visitados,vector<vector<int>> &caminos){
    if (actual==obj){
        return ListVisitados(visitados);
    }
    else if (buscaren.empty()){
        return "VACIO, NO ENCOTRADO";
    }
    else{
    actual=buscaren.top();
    buscaren.pop();
    visitados.push_back(actual);
    for(int i=0;i<adjList[actual].size();i++)
        if(!contains(visitados, adjList[actual][i])){
            buscaren.push(adjList[actual][i]);
            caminos[adjList[actual][i]][0]=actual;
        }
        return Depth(actual, obj, buscaren, visitados, caminos);
    }
}
string Graph::ListVisitados(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
        aux << q.front() << " ";
        q.pop_front();
    }
	return aux.str();
}

string Graph::CaminoFinal(vector<vector<int>> &camino, int inicio, int final){
    int nodo=camino[final][0];
    stack<int> st;
    st.push(final);
    stringstream a;
    a << "path:";
    while(nodo!=inicio){
        st.push(nodo);
        nodo=camino[nodo][0];
    }
    st.push(inicio);
    while(!st.empty()){
        a << " " << st.top();
        st.pop();
    }
    return a.str();
}

#endif
