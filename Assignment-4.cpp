// Problem Statement

// Write a program to solve the travelling salesman problem and to print the path and the cost using LC Branch and Bound

#include<bits/stdc++.h>

using namespace std;

#define inf 1e8

class Node{
	public: 
		int cost;
		vector<vector<int>>matrix;
		vector<int>path;

		Node(vector<vector<int>>matrix, vector<int>path){
			this->matrix = matrix;
			this->path = path;
		}
};

class ComparisonClass{
	public:
	bool operator()(Node* a, Node *b){
		return a->cost > b->cost;
	}
};

int reduceMatrix(vector<vector<int>>&matrix){
	int n = matrix.size();
	int cost = 0;

	// Row Reduction

	for(int i = 0; i < n; i++){
		int mn = inf;
		// Finding the minimum value in the row
		for(int j = 0; j < n; j++) mn = min(mn, matrix[i][j]);
		
		if (mn == inf or mn == 0) continue;
		
		cost += mn;
		for(int j = 0; j < n; j++){
			if (matrix[i][j] != inf) matrix[i][j] -= mn;
		}
	}
	
	// Column Reduction

	for(int j = 0; j < n; j++){
		int mn = inf;
		for(int i = 0; i < n; i++) mn = min(mn, matrix[i][j]);

		if (mn == inf or mn == 0) continue;

		cost += mn;
		for(int i = 0; i < n; i++){
			if (matrix[i][j] != inf) matrix[i][j] -= mn;
		}
	}

	return cost;
}

Node* createNode(vector<vector<int>>matrix, vector<int>path, int vertex){
	Node* newNode = new Node(matrix, path);

	newNode->path.push_back(vertex);
	newNode->matrix[vertex][0] = inf;

	int n = matrix.size();
	if (newNode->path.size() > 1){
		// Node x -> Node y => Making row x and column y as inf
		int x = path.back();
		for(int i = 0; i < n; i++){
			newNode->matrix[x][i] = inf;
			newNode->matrix[i][vertex] = inf;
		}
	}

	return newNode;
}

void solve(vector<vector<int>>costMatrix){
	int n = costMatrix.size();

	// LC Branch & Bound : Using Min Priority Queue
	priority_queue<Node*, vector<Node*>, ComparisonClass>pq;

	vector<int>path;
	Node *root = createNode(costMatrix, path, 0);
	root->cost = reduceMatrix(root->matrix);

	pq.push(root);
	
	while(!pq.empty()){
		Node* eNode = pq.top();
		pq.pop();

		if (eNode->path.size() == n){
			cout<<"Path Taken : ";
			for(auto it : eNode->path) cout<<it<<"->";
			cout<<0<<endl;

			cout<<"Cost : "<<eNode->cost;
			return;
		}

		int vertex = eNode->path.back();

		for(int i = 0; i < n; i++){
			if (eNode->matrix[vertex][i] != inf){
				Node* child = createNode(eNode->matrix, eNode->path, i);
				child->cost = eNode->matrix[vertex][i] + eNode->cost + reduceMatrix(child->matrix);
				pq.push(child);
			}
		}
	}
}

int main(){
	int n = 0;
	cout<<"Enter the number of vertices : ";
	cin>>n;

	vector<vector<int>>costMatrix(n, vector<int>(n, inf));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin>>costMatrix[i][j];
		}
	}

	for(int i = 0; i < n; i++) costMatrix[i][i] = inf;

	solve(costMatrix);
}


/*Test Cases
5
0 10 8 9 7
10 0 10 5 6
8 10 0 8 9
9 5 8 0 6
7 6 9 6 0

Output
Path Taken : 0->2->3->1->4->0
Cost : 34

4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

Output
Path Taken : 0->2->3->1->0
Cost : 80

5
0 20 30 10 11
15 0 30 10 11
3 5 0 2 4
19 6 18 0 3
16 4 7 16 0

Output
Path Taken : 0->3->1->4->2->0
Cost : 37
*/