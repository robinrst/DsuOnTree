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
vi adj[N];

int sz[N],Dep[N],col[N];
mii mp[N];

void dfs(int i = 1, int p = 0 )
{
	int mx = -1 ,bigChild = -1;

	for( auto j : adj[i] )
	{
		if( j != p and sz[j] > mx ) 
		{
			mx = sz[j];
			bigChild = j;
		}
	}

	for( int j : adj[i] )
	{
		if( j != p and j != bigChild ) dfs( j, i);
	}
	if( ~bigChild ) dfs(bigChild,i);

	mii nmp;
	if( ~bigChild ) mp[i] = mp[bigChild];
	else mp[i] = nmp;

	int now = col[i];

	for( auto j : adj[i] )
	{
		if( j != p and j != bigChild )
		{
			// small to large
			for( auto xx : mp[j] )
			{
				if( (now%xx.f) == 0 and mp[i].count((now/xx.f)) )
				{
					ans += (xx.sc)*(mp[i][now/xx.f]);
				}
			}
			for( auto xx : mp[j] ) mp[i][xx.f] += xx.sc;
		}
	}

	if( mp[i].count(1) ) ans += mp[i][1];
	mp[i][col[i]]++;
}

void dfsSize(int i = 1, int p = 0 )
{
	sz[i] = 1;
	for( auto j : adj[i] )
	{
		if( j != p ) 
		{
			dfsSize(j,i);
			Dep[i] = Dep[j] + 1;
			sz[i] += sz[j];
		}
	}
}



void go()
{
	cin >> n;
	fo(i,0,n-1)
	{
		int u , v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	fo(i,1,n+1) cin >> col[i];

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

 