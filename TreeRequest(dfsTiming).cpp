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
int sz[N],Dep[N],ans[N],in[N],out[N],id[N];
vpii Q[N];
int cnt[N][26];

void dfsSize( int i = 1 )
{
	static int clk = 0;
	sz[i] = 1;
	in[i] = ++clk;
	id[clk] = i;
	for( int j : adj[i] )
	{
		Dep[j] = Dep[i] + 1;
		dfsSize(j);
		sz[i] += sz[j];
	}
	out[i] = clk;
}

#define z id[k]

void dfs( int i = 1, bool keep = 0)
{
	int mx = -1 , bigChild = -1;

	for( int j : adj[i] )
	{
		if( sz[j] > mx ) 
		{
			mx = sz[j];
			bigChild = j;
		}
	}

	for( auto j: adj[i] )
	{
		if( j != bigChild ) dfs(j, 0 );
	}

	if( ~bigChild ) dfs( bigChild , 1 );

	for( auto j : adj[i] )
	{
		if( j != bigChild )
		{
			fo(k,in[j],out[j]+1)
			{
				cnt[Dep[z]][ s[z] - 'a']++;
			}
		}
	}
	cnt[Dep[i]][s[i] - 'a']++;

	for( auto now : Q[i] )
	{
		int o = 0;
		int dep = now.f;
		int qno = now.sc;

		fo(c,0,26)
		{
			o += ( cnt[dep][c]&1 );
		}
		ans[qno] = (o <= 1);
	}

	if( !keep )
	{
		fo(k,in[i],out[i]+1)
		{
			cnt[Dep[z]][s[z] - 'a']--;
		}
	}

}

void go()
{
	cin >> n >> q;

	fo(i,2,n+1)
	{
		int p;
		cin >> p;
		adj[p].pb(i);
	}

	cin >> s;
	s = " " + s;

	fo(i,0,q)
	{
		int v , d;
		cin >> v >> d;
		Q[v].pb({ d - 1 ,i });
	}

	dfsSize();

	dfs();

	fo(i,0,q) cout << ( ans[i] ? "Yes\n" : "No\n" );

}

int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 