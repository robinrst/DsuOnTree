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
#define          N (int)2e5+5
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
 
int n,m,k,q,ans;
string s;
vi adj[N],store[N];
int in[N], out[N],up[N][lgn] , Dep[N];
 
 
void dfs(int i = 0, int level = 0)
{
	static int clk = 0;
	Dep[i] = level;
	store[level].pb(clk);
	in[i] = clk;
	++clk;
 
	for( auto j: adj[i] ) dfs(j,level+1);
 
	out[i] = clk;
}
 
#define lb lower_bound
 
void go()
{
	cin >> n;
	fo(i,1,n+1)
	{
		int p;
		cin >> p;
		up[i][0] = p;
		adj[p].pb(i);
	}
 
	fo(i,1,n+1)
	{
		fo(j,1,lgn) up[i][j] = up[ up[i][j-1] ][j-1];
	}
 
	fo(i,1,n+1)
	{
		if( up[i][0] == 0 ) dfs(i,0);
	}
 
	cin >> m;
 
	while(m--)
	{
		int v, pth;
		cin >> v >> pth;
		int vv = v;
		fo(i,0,lgn)
		{
			if( (pth>>i)&1 ) v = up[v][i];
		}
 
		int ans = lb( all(store[Dep[vv]]) , out[v] ) - lb( all(store[Dep[vv]]) , in[v] ) - 1;
		ans = max( 0LL , ans );
 
		cout << ans << ' ';
	}
}
 
int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}