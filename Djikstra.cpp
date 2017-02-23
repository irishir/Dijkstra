//#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
//#include <stack>
using namespace std;

int s;
const int INF= 1000000;
vector<int> pred;

void printway(int t)
{
	
	if (pred[t] != s)
		printway(pred[t]);
	cout<<" "<<pred[t];
}

int main()
{
	int n,m,s,t,i,j,v,w,a,b;
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

	for(i=0; i<n; ++i)
	{
		v=-1;
		for(j=0; j<n; ++j)
			if(!u[j] && (v==-1 || d[j]<d[v]))
				v=j;

	if(d[v]== INF) break;
	u[v]=true;
	for(size_t j=0; j<g[v].size(); ++j)
		{
			int t1= g[v][j].first, len = g[v][j].second;
				if(d[v]+len < d[t1])
				{
					d[t1]=d[v]+len;
					pred[t1]=v;
				}
		}
	}

cout<<"shortest way from "<<s<<" to "<<t<<" is\n";
printway(t);
cout<<" "<<t<<endl;
cout<<"it's length is "<<d[t]<<endl;
return 0;
}