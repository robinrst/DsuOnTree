#include        "algorithm"
#include        "iostream"
#include        "numeric"
#include        "iomanip"
#include        "cstring"
#include        "math.h"
#include        "bitset"
#include        "string"
#include        "vector"
#include        "ctime"
#include        "queue"
#include        "stack"
#include        "map"
#include        "set"
 
#include        "ext/pb_ds/assoc_container.hpp" // Common file
#include        "ext/pb_ds/tree_policy.hpp" // Including tree_order_statistics_node_update
#include        "ext/pb_ds/detail/standard_policies.hpp"
 
using namespace std;
using namespace __gnu_pbds;
 
 
#define          f first
#define          lgn 25
#define          endl '\n'
#define          sc second
#define          NN (int)2e5+5
#define          pb push_back
#define          mod 1000000007
#define          ld long double
#define          vi vector<int>
#define          eb emplace_back
#define          vpii vector<pii>
#define          int long long 
#define          mii map<int,int>
#define          mp make_pair
#define          pii pair<int,int>
#define          pq priority_queue
#define          BLOCK (int)sqrt(N)
#define          test(x) while(x--)
#define          all(x) begin(x),end(x)
#define          allr(x) rbegin(x),rend(x)
#define          fo(i,a,n) for(int i=a;i<n;i++)
#define          rfo(i,n,a) for(int i=n;i>=a;i--)
#define          FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define          time() cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n"
#define          PI acos(-1.0)
#define 		 bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
 
typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > 
OS ;
 
template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     const char* comma = strchr (names + 1, ',');
     cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}
 
inline void INP()
{
	#ifndef ONLINE_JUDGE
	    freopen("input.txt","r",stdin);   
	    freopen("output.txt","w",stdout);
	#endif 
}
 
const int inf = 0x3f3f3f3f;
const int INF = 0x3f3f3f3f3f3f3f3f;
 
int n,m,q;
string s;
vpii adj[NN];
int in[NN],out[NN],sz[NN],Dep[NN],sumNow[NN],id[NN], ans;
bool big[NN];
mii path;
 
void dfsSize(int  i = 1, int p = 0)
{
	static int clk = 0;
	sz[i] = 1;
	in[i] = ++clk;
	id[clk] = i;
 
	for( auto j : adj[i] )
	{
		if( j.f != p )
		{
			sumNow[j.f] = sumNow[i] + j.sc;
			Dep[j.f] = Dep[i] + 1;
			dfsSize(j.f , i);
			sz[i] += sz[j.f];
		}
	}

	out[i] = clk;
}
 
#define z id[k]
 
void add(int i, int x )
{
	path[sumNow[i]] += x;
}

void update(int i , int j )
{
	int now = m - sumNow[j] + 2*sumNow[i];
	if( path[now]  ) ans += path[now];
}
 
void dfs(int i = 1, int p = 0, bool keep = 0)
{
	int mx = -1;
	int bigChild = -1;
 
	for( auto j : adj[i] )
	{
		if( j.f != p and mx < sz[j.f] ) mx = sz[j.f] , bigChild = j.f;
	}
 
	for( auto j : adj[i] ) 
	{
		if( j.f != p and j.f != bigChild ) dfs(j.f , i , 0);
	}
 
	if( ~bigChild ) dfs(bigChild , i , 1) , big[bigChild] = 1;


	add(i,1);
	int now = sumNow[i] + m;
	if( path[now] ) ans += path[now];


	for( auto j : adj[i] )
	{
		if( j.f != p and !big[j.f] )
		{
			fo(k,in[j.f],out[j.f]+1)
			{
				update(i , z);
			}
			fo(k,in[j.f],out[j.f]+1) add(z , 1 );
		}
	}
  	
 	if( ~bigChild ) big[bigChild] = 0;
	
	if( !keep )
	{
		fo(k,in[i],out[i]+1) add(z,-1);
	}
}
 
void go()
{
	cin >> n >> m;

	fo(i,0,n-1)
	{
		int u , v , w;
		w = 1;
		cin >> u >> v;
		adj[u].pb({ v, w} );
		adj[v].pb({ u , w} );
	}


	dfsSize();
	dfs();


	cout << ans << endl; 
}
int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}