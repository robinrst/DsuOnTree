#include        "iostream"
#include        "algorithm"
#include		"numeric"
#include        "cstring"
#include        "math.h"
#include        "string"
#include        "vector"
#include        "ctime"
#include        "queue"
#include        "stack"
#include        "map"
#include        "set"
 
#include        <ext/pb_ds/assoc_container.hpp> // Common file
#include        <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include        <ext/pb_ds/detail/standard_policies.hpp>
 
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
#define          test(x) while(x--)
#define          all(x) begin(x),end(x)
#define          allr(x) rbegin(x),rend(x)
#define          fo(i,a,n) for(int i=a;i<n;i++)
#define          rfo(i,n,a) for(int i=n;i>=a;i--)
#define          db(x) cout<<#x <<" : "<< x <<endl;
#define          FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define          time() cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n"
#define          PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
 
typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > 
OS ;
 
inline void INP()
{
	#ifndef ONLINE_JUDGE
	    freopen("in.txt","r",stdin);   
	    freopen("ou.txt","w",stdout);
	#endif 
}
 
const int inf = 0x3f3f3f3f;
const int INF = 0x3f3f3f3f3f3f3f3f;
 
int n,q;
string s;
vi adj[N];
int cnt[26][N],sz[N],ans[N],Depth[N];
vpii Q[N];
bool big[N];
 
void rmv( int i , int p , int x )
{
	cnt[ s[i] - 'a' ][ Depth[i] ]--;
 
	for( auto j : adj[i] ) 
	{
		if( ( j != p ) and (!big[j]) ) rmv(j,i,x);
	}
}
 
void add( int i, int p ,int x)
{
	cnt[ s[i] - 'a' ][ Depth[i] ]++;
 
	for( auto j : adj[i] )
	{
		if( ( j != p ) and ( !big[j] ) ) add( j, i, x);
	}
}
 
void dfs( int i , int p = 0, bool keep = 1 )
{
	int mx = -1 , bigChild = -1;
 
	for( auto j : adj[i] )
	{
		if( (j != p) and sz[j] > mx ) mx = sz[j] , bigChild = j;
	}
 
	for( auto j : adj[i] )
	{
		if( ( j != p ) and ( j != bigChild ) ) dfs( j, i, 0 );
	}
 
	if( bigChild != -1 ) dfs( bigChild , i , 1 ) , big[ bigChild ] = 1;
 
	add( i , p , 1 );
 
	//
	for( auto xx : Q [i])
	{
		int odd  = 0;
		fo(i,0,26)
		{
			odd += (cnt[ i ][ xx.f ]&1);
		}
		ans[ xx.sc ] = ( odd <= 1);
	}
	// cout << i << ' ' << odd << endl;
 
	//
 
	if( bigChild != -1 ) big[ bigChild ] = 0;
 
	if( keep == 0 ) rmv( i, p, -1 );
}
 
void dfsSize(int i , int p = 0)
{
	sz[i] = 1;
 
	for( auto j : adj[i] ) 
	{
		if( ( j != p ) ) 
		{
			Depth[j] = Depth[i] + 1;
			dfsSize(j,i);
			sz[i] += sz[j];
		}
	}
}
 
void go()
{
	cin >> n >> q;
 
	fo(i,2,n+1)
	{
		int j;
		cin >> j;
 
		adj[i].pb(j);
		adj[j].pb(i);
	}
	cin >> s;
	s = " " + s;
 
	Depth[1] = 1;
	dfsSize(1);
 
	// fo(i,1,n+1) cout << sz[i] << endl;
 
	fo(i,1,q+1)
	{
		int x , y; 
		cin >> x >> y;
 
		Q[x].pb( { y , i } );
	}
 
	dfs(1);
 
	fo(i,1,q+1)
	{
		if( ans[i] ) cout << "Yes\n";
		else cout << "No\n";
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