// Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists

    // Fills Stack with vertices (in increasing order of finishing times)
    // The top element of stack has the maximum finishing time
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    void addEdge(int v, int w);

    // The main function that finds and prints strongly connected components
    void printSCCs();

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
    
    int findFixP(vector<int> cand) const;
    void cliqueEnumerate(const vector<int>& compsub, vector<int> cand, vector<int> cnot, vector<vector<int> >& result) const;
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v to Stack
    Stack.push(v);
}

// The main function that finds and prints all strongly connected components
void Graph::printSCCs()
{
    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

int cliqueSize(Graph &g, std::vector<int> nodes, std::vector<EdgeID> edges)
{
    std::vector<std::vector<int> > previous_cliques;

    // start with all the singular nodes...
    for (unsigned i = 0; i < nodes.size(); i++)
    {
        std::vector<int> tmp;
        tmp.push_back(nodes[i]);
        previous_cliques.push_back(tmp);
    }

    for (unsigned clique_size = 1; clique_size < nodes.size(); clique_size++)
    {
        std::vector<std::vector<int> > new_cliques;
        // go through all the nodes to try to add to the clique.
        for (unsigned i = 0; i < nodes.size(); i++)
        {
            // try to add node i to clique j.
            for (unsigned j = 0; j < previous_cliques.size(); j++)
            {
                // make sure node j is not already in the clique.
                if (std::find(previous_cliques[j].begin(), previous_cliques[j].end(), nodes[i]) == previous_cliques[j].end()) 
                {
                    std::vector<int> potential_clique(previous_cliques[j]);
                    potential_clique.push_back(nodes[i]);

                    // isClique has no issues, just checks if the given graph is a clique...   
                    if (isClique(g, potential_clique, edges))
                    {
                        new_cliques.push_back(potential_clique);
                    }
                }
            }
        }
        // no new cliques? 
        if (new_cliques.size() == 0) { return clique_size; }
        else { previous_cliques = new_cliques; }
    }
    return nodes.size();
}

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
    Graph g(5);
    
    g.addEdge(3, 0);
    g.addEdge(3, 4);
    g.addEdge(0, 1);
    g.addEdge(2, 0);
    g.addEdge(1, 2);
    
    
    
    //g.addEdge(3, 4);

    cout << "Following are strongly connected components in given graph \n";
    g.printSCCs();

    return 0;
}
