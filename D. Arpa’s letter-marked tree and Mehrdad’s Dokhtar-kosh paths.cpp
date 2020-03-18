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
#define          N (int)5e5+5
#define          pb push_back
#define          mod 1000000007
#define          ld long double
#define          vi vector<int>
#define          eb emplace_back
#define          vpii vector<pii>
#define          mii map<int,int>
#define          int long long 
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
 
int n,m,k,q;
string s;
vi adj[N];
int in[N] , out[N] , ans[N] , sz[N] , Dep[N] , mask[N] , id[N] , val[N];
int cnt[1LL<<23];
 
 
void dfsSize(int i = 1)
{
	static int clk = 0;
	sz[i] = 1;
	in[i] = ++clk;
	id[clk] = i;
 
	for( auto j : adj[i] )
	{
		Dep[j] = Dep[i] + 1;
		mask[j] = mask[i]^(1LL<<val[j]);
		dfsSize(j);
		sz[i] += sz[j];
	}
 
	out[i] = clk;
}
#define z id[k]
 
void update(int i, int j)
{
	fo(t,0,22)
	{
		int now = mask[j]^(1LL<<t);
		if( ~cnt[now] )ans[i] = max( ans[i] , cnt[ now ] + Dep[j] - 2*Dep[i] );
	}
	if( ~cnt[mask[j]] )ans[i] = max( ans[i] , cnt[ mask[j] ] + Dep[j] - 2*Dep[i] );
}
 
void change(int j)
{
	cnt[ mask[j] ] = max( cnt[ mask[j] ] , Dep[j] );
}
 
void rmv(int j)
{
	cnt[ mask[j] ] = -1;
}
 
void dfs(int i = 1, bool keep = 0 )
{
	int mx = -1 , bigChild = -1;
 
	for( int j : adj[i] )
	{
		if( mx < sz[j] ) mx = sz[j] , bigChild = j;
	}
 
	for( int j : adj[i] ) 
	{
		if( j != bigChild ) dfs(j, 0) , ans[i] = max( ans[i] , ans[j]);
	}
 
	if( ~bigChild ) dfs(bigChild ,1) , ans[i] = max( ans[i] , ans[bigChild]);
 
	for( auto j : adj[i] )
	{
		if( j != bigChild )
		{
			fo(k,in[j],out[j]+1) update(i,z);
			fo(k,in[j],out[j]+1) change(z);
		}
	}
 
	fo(t,0,22)
	{
		int now = mask[i]^(1LL<<t);
		if( ~cnt[now] ) ans[i] = max( ans[i] , cnt[ now ] - Dep[i] );
	}
	if( ~cnt[ mask[i] ] ) ans[i] = max( ans[i] , cnt[ mask[i] ] - Dep[i] );
 
	change(i);
 
	if( !keep ) 
	{
		fo(k,in[i],out[i]+1) rmv(z);
	}
 
}
 
void go()
{
	cin >> n;
	fo(i,2,n+1)
	{
		int p;
		cin >> p >> s;
		adj[p].pb(i);
		val[i] = s[0] - 'a';
	}
 	
 	memset( cnt , -1 , sizeof cnt);
	dfsSize();
	dfs();
 
	fo(i,1,n+1) cout << ans[i] << " \n"[ i == n];
 
}
 
int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}