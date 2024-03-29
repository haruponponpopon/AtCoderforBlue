//転倒数を求める例
#include <vector>
#include <iostream>
using namespace std;
//数列a(a[0],a[1],…,a[n-1])についての区間和と点更新を扱う
//区間和,点更新,二分探索はO(log{n})で動作する
class BIT {
public:
    vector<int> graph;
    int n;
    void init(int sz) {
	graph.resize(sz+1, 0);//0で初期化
        n = sz;
    }

    //a[i]にxを加算する
    void add(int i, int x){
        i++;
        if (i==0) return;
        for (int k=i; k<=n; k+=(k & -k)){
            graph[k]+=x;
        }
    }

    //a[i]+a[i+1]+…+a[j]を求める
    int sum(int i, int j){
        return sum_sub(j)-sum_sub(i-1);
    }

    //a[0]+a[1]+…+a[i]を求める
    int sum_sub(int i){
        i++;
        int s = 0;
        if (i==0) return s;
        for (int k=i; k>0; k-=(k & -k)){
            s+=graph[k];
        }
        return s;
    }

    //a[0]+a[1]+…+a[i]>=xとなる最小のiを求める(任意のkでa[k]>=0が必要)
    int lower_bound(int x){
        if(x<=0){
            //xが0以下の場合は該当するものなし→0を返す
            return 0;
        }else{
            int i=0;int r=1;
            //最大としてありうる区間の長さを取得する
            //n以下の最小の二乗のべき(BITで管理する数列の区間で最大のもの)を求める
            while(r<n) r=r<<1;
            //区間の長さは調べるごとに半分になる
            for(int len=r;len>0;len=len>>1) {
                //その区間を採用する場合
                if(i+len<n && graph[i+len]<x){
                    x-=graph[i+len];
                    i+=len;
                }
            }
            return i;
        }
    }
};
template <typename T>
struct fenwick {
    int n;
    vector<T> node;
 
    fenwick(int _n) : n(_n) {
        node.resize(n);
    }
 
    void add(int x, T v) {
        while (x < n) {
            node[x] += v;
            x |= (x + 1);
        }
    }
 
    T get(int x) {  // [0, x]
        T v = 0;
        while (x >= 0) {
            v += node[x];
            x = (x & (x + 1)) - 1;
        }
        return v;
    }
 
    T get(int x, int y) {  // [x, y]
        return (get(y) - (x ? get(x - 1) : 0));
    }
 
    int lower_bound(T v) {
        int x = 0;
        int h = 1;
        while (n >= (h << 1)) {
            h <<= 1;
        }
        for (int k = h; k > 0; k >>= 1) {
            if (x + k <= n && node[x + k - 1] < v) {
                v -= node[x + k - 1];
                x += k;
            }
        }
        return x;
    }
};
int main(){
    int n=7;
    int a[5] = {3,1,5,4,2};
    BIT bit;
    bit.init(n);aの最大値より2大きい数にしないとoverflow
    int ans = 0;
    for (int i=0; i<n; i++){
        ans += i - bit.sum_sub(a[i]);
        bit.add(a[i],1);
    }
    cout<<ans<<endl;
    fenwick<int> row(n), col(n);
}
