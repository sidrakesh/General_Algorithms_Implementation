#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;
// Constants
//-------------------------------
const char FILENAME[] = "SCC.txt";

// Prototypes
//-------------------------------

map< int, vector<int> > compute_scc(vector< vector<int> > &graph);
vector< vector<int> > reverse_graph(const vector< vector<int> > &graph);
void dfs_loop(const vector< vector<int> > &graph, vector<int> &finishTime, vector<int> &leader);
int dfs(const vector< vector<int> > &graph, int nodeIndex, vector<bool> &expanded, vector<int> &finishTime, int t, vector<int> &leader, int s);
list<int> get_largest_components(const map< int, vector<int> > scc, int size);


/**
 * Main
 */
int arr[20000][20]; 
int size[20];

bool check_disjoint(int i,int j) 
{
	int arr[20001];
	int k;
	for(k=0;k<size[i];k++)
	{
		arr[i] = 1;
	}
	
	for(k=0;k<size[j];k++)
	if(arr[k]==1)
		return false;
	
	return true;
}

int main() {
    // Get the sequential graph representation from the file
    int i,n,j,k,t,m;
    
    cin>>n>>m;
    vector< vector<int> >graph(m);
    /*
    for(i=0;i<m;i++)
    {
		scanf("%d",&size[i]);
		
		for(j=0;j<size[i];j++)
		{
			scanf("%d",&arr[i][j]);
		}	
	}

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(check_disjoint(i,j)==true)
				graph[i].push_back(j);
		}
	}
	*/
	graph[0].push_back(1);
	graph[0].push_back(2);
	graph[0].push_back(3);
	graph[1].push_back(2);
	graph[2].push_back(3);
	graph[2].push_back(4);
	graph[3].push_back(4);
	
    // Compute the strongly-connected components
    map< int, vector<int> > scc = compute_scc(graph);

    // Compute the largest 5 components and print them out
    list<int> largestComponents = get_largest_components(scc, 1);

    list<int>::iterator it;
    for (it = largestComponents.begin(); it != largestComponents.end(); it++) {
    	cout<<*it<<"\n";
        for(i=0;i<scc[*it].size();i++)
			cout<<scc[*it][i]<<" ";
    }
    cout << endl;

    return 0;
}


/**
 * Parse an input file as a graph, and return the graph.
*/


/**
 * Get the count of nodes from a graph file representation
 */



/**
 * Compute all of the strongly-connected components of a graph
 * using depth-first search, Kosaraju's 2-pass method
 */
map< int, vector<int> > compute_scc(vector< vector<int> > &graph) {
    // Create finishing time and leader vectors to record the data
    // from the search
    vector<int> finishTime(graph.size(), 0);
    vector<int> leader(graph.size(), 0);

    // Initialize the finish time initially to be the numbers of the graph
    vector<int>::iterator it;
    int index = 0;
    for (it = finishTime.begin(); it != finishTime.end(); it++) {
        *it = index;
        index++;
    }

    // Reverse the graph, to compute the 'magic' finishing times
    vector< vector<int> > reversed = reverse_graph(graph);
    dfs_loop(reversed, finishTime, leader);

    // Compute the SCC leaders using the finishing times
    dfs_loop(graph, finishTime, leader);

    // Distribute nodes to SCCs
    map< int, vector<int> > scc;
    vector<int>::iterator lit;

    for (lit = leader.begin(); lit != leader.end(); lit++) {
        int nodeIndex = lit - leader.begin();

        // Append node to SCC
        scc[*lit].push_back(nodeIndex);
    }

    return scc;
}


/**
 * Reverse a directed graph by looping through each node/edge pair
 * and recording the reverse
 */
vector< vector<int> > reverse_graph(const vector< vector<int> > &graph) {
    // Create new graph
    vector< vector<int> > reversed(graph.size());

    // Loop through all elements and fill new graph with reversed endpoints
    vector< vector<int> >::const_iterator it;
    for (it = graph.begin(); it != graph.end(); it++) {
        int nodeIndex = it - graph.begin();

        // Loop through all outgoing edges, and reverse them in new graph
        vector<int>::const_iterator eit;
        for (eit = graph[nodeIndex].begin(); eit != graph[nodeIndex].end(); eit++) {
            reversed[*eit].push_back(nodeIndex);
        }
    }

    return reversed;
}


/**
 * Compute a depth-first search through all nodes of a graph
 */
void dfs_loop(const vector< vector<int> > &graph, vector<int> &finishTime, vector<int> &leader) {
    // Create expanded tracker and copied finishing time tracker
    vector<bool> expanded(graph.size(), 0);
    vector<int> loopFinishTime = finishTime;

    int t = 0;
    vector<int>::reverse_iterator it;

    // Outer loop through all nodes in order to cover disconnected
    // sections of the graph
    for (it = loopFinishTime.rbegin(); it != loopFinishTime.rend(); it++) {
        // Compute a depth-first search if the node hasn't
        // been expanded yet
        if (!expanded[*it]) {
            t = dfs(graph, *it, expanded, finishTime, t, leader, *it);
        }
    }
}


/**
 * Search through a directed graph recursively, beginning at node 'nodeIndex',
 * until no more node can be searched, recording the finishing times and the 
 * leaders
 */
int dfs(
    const vector< vector<int> > &graph,
    int nodeIndex,
    vector<bool> &expanded,
    vector<int> &finishTime,
    int t,
    vector<int> &leader,
    int s
) {
    // Mark the current node as explored
    expanded[nodeIndex] = true;

    // Set the leader to the given leader
    leader[nodeIndex] = s;

    // Loop through outgoing edges
    vector<int>::const_iterator it;
    for (it = graph[nodeIndex].begin(); it != graph[nodeIndex].end(); it++) {
        // Recursively call DFS if not explored
        if (!expanded[*it]) {
            t = dfs(graph, *it, expanded, finishTime, t, leader, s);
        }
    }

    // Update the finishing time
    finishTime[t] = nodeIndex;
    t++;

    return t;
}


/**
 * Computes the largest 'n' of a strongly-connected component list
 * and return them
 */
list<int> get_largest_components(const map< int, vector<int> > scc, int size) {
    // Create vector to hold the largest components
    list<int> largest(size, 0);

    // Iterate through map and keep track of largest components
    map< int, vector<int> >::const_iterator it;
    for (it = scc.begin(); it != scc.end(); it++) {
        // Search through the current largest list to see if there exists
        // an SCC with less elements than the current one
        list<int>::iterator lit;
        for (lit = largest.begin(); lit != largest.end(); lit++) {
            // Compare size and change largest if needed, inserting
            // the new one at the proper position, and popping off the old
            if (*lit < it->second.size()) {
                largest.insert(lit, it->second.size());
                largest.pop_back();
                break;
            }
        }
    }

    return largest;
}
