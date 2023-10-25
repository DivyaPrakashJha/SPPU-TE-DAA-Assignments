// Problem Statement

// Write a program to implement Fractional knapsack using Greedy algorithm and 0/1 knapsack using dynamic programming

#include<bits/stdc++.h>

using namespace std;

double fractionalKnapsack(int n, int w, vector<int>weight, vector<int>value){
    vector<pair<double, int>>v;

    for(int i = 0; i < n; i++){
        double valPerUnitWeight = (double)value[i]/weight[i];
        v.push_back({valPerUnitWeight, i});
    }

    sort(v.begin(), v.end(), greater<pair<double, int>>());

    double maxVal = 0.0;
    
    for(auto it : v){
        double vpuw = it.first;
        int ind = it.second;

        int weightPossible = min(weight[ind], w);
        w -= weightPossible;

        maxVal += (weightPossible * vpuw);
    }

    return maxVal;
}

int knapsack01(int n, int w, vector<int>weight, vector<int>value){
    vector<vector<int>>dp(n, vector<int>(w+1, 0));

    for(int wt = weight[0]; wt < w; wt++){
        dp[0][wt] = value[0];
    }

    for(int i = 1; i < n; i++){
        for(int j = 0; j <= w; j++){
            if (weight[i] <= j){
                dp[i][j] = max(dp[i-1][j], value[i] + dp[i-1][j-weight[i]]);
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n-1][w];
}

void takeInput(int &n, int &w, vector<int>&weight, vector<int>&value){
        cout<<"\nEnter the number of items (n) : ";
        cin>>n;

        cout<<"\nEnter the capacity of the knapsack : ";
        cin>>w;

        weight.resize(n, 0);
        value.resize(n, 0);

        cout<<"\nEnter the weights of n items : ";
        for(int i = 0; i < n; i++){
            cin>>weight[i];
        }

        cout<<"\nEnter the value of n items : ";
        for(int i = 0; i < n; i++){
            cin>>value[i];
        }
}

int main(){
    bool run = true;

    while(run){
        int op = 0;
        cout<<"\n******Choose the desired option*******\n";
        cout<<"1. Fractional Knapsack (Greedy)\n";
        cout<<"2. 0/1 Knapsack (DP)\n";
        cout<<"3. Exit\n";

        cin>>op;

        int n  = 0, w = 0;
        vector<int>weight, value;

        switch(op){
            case 1:
                takeInput(n, w, weight, value);
                
                cout<<"Maximum Value : "<<fractionalKnapsack(n, w, weight, value)<<endl;
                break;

            case 2:
                takeInput(n, w, weight, value);

                cout<<"Maximum Value : "<<knapsack01(n, w, weight, value)<<endl;
                break;

            default:
                run = false;  
        }
    }
}