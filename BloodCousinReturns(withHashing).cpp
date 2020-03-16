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

int n,m,k,q,mxDep;
string s;
vi adj[N];
int sz[N],Dep[N],col[N],ans[N];
mii cnt[N];
vpii Q[N];
bool big[N];
vi subtree;
int hashes[N];

int computeHash( const string &now )
{
	const int p = 31;
	const int m = 1e9 + 9;
	int po = 1;
	int hash = 0;

	for(char c : now)
	{
		hash = ( hash + (c - 'a' + 1) * po )%m;
		po = ( po * p )%m;
	}
	return hash;
}

void rem(int i , int p , int x)
{
	if( cnt[Dep[i]].count(hashes[i]) )
	{
		cnt[Dep[i]][hashes[i]]--;
		if( cnt[Dep[i]][hashes[i]] == 0 ) cnt[Dep[i]].erase(hashes[i]);
	}
	for( auto j : adj[i] )
	{
		if( j != p and !big[j] ) rem(j,i,x);
	}
}

void add(int i, int p, int x)
{
	cnt[Dep[i]][hashes[i]]++;

	for( auto j : adj[i] )
	{
		if( j != p and !big[j] ) add(j,i,x);
	}
}

void dfs(int i = 1, int p = 0 , bool keep = 0 ) // keep ->0 ==> small child
{
	int mx = -1, bigChild = -1;

	for( auto j : adj[i] )
	{
		if( j != p and sz[j] > mx )
		{
			mx = sz[j];
			bigChild = j;
		}
	}

	for( auto j : adj[i] )
	{
		if( j != p and j != bigChild ) dfs(j,i,0);
	}

	if( ~bigChild ) dfs(bigChild,i,1) , big[bigChild] = 1;

	add(i,p,1);

	for( auto j : Q[i] )
	{
		int dep = j.f;
		int qno = j.sc;
		ans[qno] = (int)cnt[Dep[i] + dep].size();
	}

	if ( ~bigChild ) big[bigChild] = 0;

	if( keep == 0 ) rem(i,p,-1);

}

void dfsSize(int i = 1, int p = 0 )
{
	sz[i] = 1;
	for( auto j : adj[i] )
	{
		if( j != p ) 
		{
			Dep[j] = Dep[i] + 1;
			mxDep = max( mxDep , Dep[j] );
			dfsSize(j,i);
			sz[i] += sz[j];
		}
	}
}


void go()
{
	cin >> n;

	fo(i,1,n+1)
	{
		Dep[i] = -1;
		int p;
		cin >> s >> p;
		hashes[i] = computeHash(s);
		if( p == 0 ) 
		{
			adj[i].pb(i);
			subtree.pb(i);
		}
		else adj[p].pb(i);
	}

	cin >> q;

	fo(i,0,q)
	{
		int v , dep;
		cin >> v >> dep;
		Q[v].pb({ dep , i});
	}

	for( auto j : subtree )
	{
		mxDep = 0;
		dfsSize(j);
		dfs(j);
		fo(i,0,mxDep+1) cnt[i].clear();
	}

	fo(i,0,q) cout << ans[i] << endl;
}

int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 