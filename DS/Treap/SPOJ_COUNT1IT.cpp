// https://www.spoj.com/problems/COUNT1IT/
#include <bits/stdc++.h>

using namespace std;

typedef int ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;

enum DIR{L,R};

ll getr(ll po){
    ll to_return =0;
    ll ten=1;
    for(int i=0;i<po;i++){
        to_return +=(rand()%10)*ten;
        ten*=10;
    }
    return to_return;
}
ll ra(ll x){
    ll y=getr(10);
    return y%(x)+1 ;
}

struct node ;
extern node *emp;
struct node{
    ll v;
    int p,sz, freq;
    node * child[2];
    node (){
        v=0;
        p=INT_MIN;
        freq=sz=0;
        child[L]=child[R]=this;
    }
    node (ll val, node *l=emp, node*r =emp){
        p=rand();
        v=val;
        freq=1;
        child[L]=l;
        child[R]=r;
        push_up();
    }
    void push_up(){
        sz = (child[L]->sz) + (child[R]->sz) + freq;
    }
};

node *emp = new node();

void split(node * rt, const ll & val, node * & ls, node* & ge){
    if(rt==emp){
        ls=ge=emp;
        return ;
    }
    if(val<rt->v){
        split(rt->child[L], val,ls,rt->child[L]);
        ge=rt;
    }else{
        split(rt->child[R], val, rt->child[R], ge);
        ls = rt;
    }
    rt->push_up();
}

node* mrg(node * ls, node * ge){
    if(ls==emp)return ge;
    if(ge==emp)return ls;
    if(ls->p > ge->p){
        ls->child[R]=mrg(ls->child[R], ge);
        ls->push_up();
        return ls;
    }
    ge->child[L]=mrg(ls, ge->child[L]);
    ge->push_up();
    return ge;

}

void insert(node *&rt, node * nd){
    if(rt==emp){
        rt=nd;
        return ;
    }
    if(rt->p < nd->p){
        split(rt, nd->v, nd->child[L], nd->child[R]);
        rt=nd;
    }else if(nd->v < rt->v){
        insert(rt->child[L], nd);
    }else{
        insert(rt->child[R], nd);
    }
    rt->push_up();
}

bool incremented(node *rt, const ll & val){
    if(rt==emp)return 0;
    bool ret=false;
    if(rt->v==val){
        rt->freq++;
        ret =true;
    }
    else if(rt->v>val)
        ret =  incremented(rt->child[L],val);
    else
        ret = incremented(rt->child[R],val);
    if(ret)rt->push_up();
    return ret;
}


void insert(node *& rt, const ll & val){
    if(!incremented(rt, val))
        insert(rt, new node(val));

}

int lower_bound(node *rt, const ll & val){
    if(rt==emp)return 0;
    if(rt->v==val)return rt->child[L]->sz;
    if(rt->v>val){
        return lower_bound(rt->child[L],val);
    }
    return lower_bound(rt->child[R],val)+(rt->child[L]->sz) + (rt->freq) ;
}
const ll & getByIndex(node *rt, int ind){

    if(ind<rt->child[L]->sz){
        return getByIndex(rt->child[L],ind);
    }
    int sm = rt->child[L]->sz + rt->freq;
    if(ind>=sm){
        return getByIndex(rt->child[R],ind-sm);
    }
    return rt->v;
}

int n,q;
int a[N];
int x,y;

int main() {
    cin >> n >> q;
    node *rt=  emp;
    for(int i=0;i<n;i++){
        cin >> x;
        insert(rt, x);
    }
    while(q--){
        cin >> x >> y;
        if(x==1){
            int z = lower_bound(rt, y+1);
            insert(rt, z+y);
        }else if(x==2){
            cout << lower_bound(rt, y+1) << endl;
        }else{
            if(rt->sz<y){
                cout << "invalid\n";
            }else{
                cout << getByIndex(rt, y-1) << endl;
            }
        }
    }
    return 0;
}
