//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <omp.h>
#include <stdlib.h>
#include <cstdio>
//#include <stack>
using namespace std;

const int NUM_threads = 4; // количество потоков
const int INF= 1000000;
int s;
vector<int> pred;

bool checkway(int t)
{
	if(t==-1) return false;
	if (pred[t] != s)
		return checkway(pred[t]);
	return true;
};

void printway(int t)
{
	if (pred[t] != s)
		printway(pred[t]);
	cout<<" "<<pred[t];
};

int main()
{
	int n,m,t,i,j,v,w,a,b;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin>>n>>m>>s>>t;
	vector <vector <pair <int,int> > >g(n);
	for(i=0; i<m;i++)
	{
		cin>>w>>a>>b;
		g[a].push_back(make_pair(b,w));
	}
	
	vector <int> d(n,INF);
	pred.assign(n,-1);
	d[s]=0;
	vector <bool> u(n);

	int t1, len; 
	
	long double clockStart, clockStop;
	clockStart = omp_get_wtime();	
	
	#pragma omp parallel for private (j, v, t1, len) shared (i, n, u, d, pred, g) num_threads (NUM_threads)
	for(i=0; i<n; ++i)
	{
		v=-1;
		for(j=0; j<n; ++j)
			
			#pragma omp critical (value1)	
			{
				if(!u[j] && (v==-1 || d[j]<d[v]))
					v=j;
			}
		
		if(d[v]== INF) {}
		else {
		u[v]=true;
		for(size_t j=0; j<g[v].size(); ++j)
		{
			t1= g[v][j].first;
			len = g[v][j].second;
			if(d[v]+len < d[t1])
			{
				#pragma omp critical (value2) 
				{
					d[t1]=d[v]+len;
					pred[t1]=v;
				}
				
			}
		}
	}
	
	}
clockStop = omp_get_wtime();
cout<<"shortest way from "<<s<<" to "<<t<<" is\n";
if(checkway(t))
{
	printway(t);
	cout<<" "<<t<<endl;
	cout<<"it's length is "<<d[t]<<endl;
}
else
{
	cout<<"not exist"<<endl;
}
cout << "seconds: " << (clockStop - clockStart) << endl;
return 0;
}