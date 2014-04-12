#include <cstdio>
#include <algorithm>
int A[999999], W[999999];
long long merge_and_count(int l, int r) { // range [l,r)
	if (l+1 >= r) return 0; // empty
	if (l+2 == r) { // [l,r) == [l,l+1] 要素2つだけ
		if (A[l] <= A[l+1]) return 0; // 逆転はなし
		std::swap(A[l], A[l+1]);
		return 1; // 逆転一つ
	}
	int m = (l+r)/2; // [l,r) == [l,m) + [m,r)
	long long cl = merge_and_count(l, m); // 左半分を再帰的に数える
	long long cr = merge_and_count(m, r); // 右半分を再帰的に数える
	long long c = 0; // 左と右を混ぜるときの逆点数
	int i=l, j=m; // iは[l,m)を動き, jは[m,r)を動いて、
	int k=l; // 小さいものから W[k] に書き込む
	while (i<m && j<r) { // A[i]とA[j]を比べながら進む
		if (A[i] <= A[j]) W[k++] = A[i++]; // 左半分の方が小さく逆転なし
		else {
			W[k++] = A[j++];
			c += m-i; // 左半分の方が大きい、左半分で未処理の要素だけ飛び越える
		}
	}
	while (i<m) W[k++] = A[i++]; // 左半分が余った場合
	while (j<r) W[k++] = A[j++]; // 右半分が余った場合
	//assert(k == r);
	std::copy(W+l, W+r, A+l);
	return cl + cr + c;
}
int main(){
	int T,i,N;
	//PKU2299,aizu0167
	//for(;scanf("%d",&N),N;printf("%lld\n",merge_and_count(0,N)))for(i=0;i<N;i++)scanf("%d",A+i);
	//hackerrank~runningtime
	//scanf("%d",&N);for(i=0;i<N;i++)scanf("%d",A+i);printf("%lld\n",merge_and_count(0,N));
	//spojINVCNT,hackerrank~insertionsort
	//for(scanf("%d",&T);T--;printf("%lld\n",merge_and_count(0,N)))for(scanf("%d",&N),i=0;i<N;++i)scanf("%d",A+i);
	//codeiq432
	for(N=0;~scanf("%d",A+N);N++);printf("%lld\n",merge_and_count(0,N));
	//kcs1009K
	//for(i=0;~(N=getchar());)if('0'<N&&N<'9')A[i++]=N-'0';
	//puts(merge_and_count(0,i)%2?"lmpossible":"Possible"); //lol
}

/*
24689222839,0
ENV: C++

以前15パズルの可解性について調べていた時に「転倒数/転位数」という言葉を知った。
この問題の「交差数」とは、この転倒数に他ならない。
そして転倒数は分割統治法を用いることでO(nlogn)で求めることができる。
ハマりどころとしては、long longを用いなければオーバーフローを起こしてしまうところだろうか。

timeコマンドの出力によるreal(実時間)が常に0.1s未満であったので速度は十分とした。
なお、ナイーブ解法(O(n^2))だとg++ -O3でも44秒要してしまった。
---
#include <cstdio>
#include <vector>
using namespace std;
int main(){
	int n,i;
	long long r=0;
	vector<int>v;
	for(;~scanf("%d",&n);){
		for(i=0;i<v.size();i++)if(v[i]>n)r++;
		v.push_back(n);
	}
	printf("%lld\n",r);
}
---

ロジックのテストは http://poj.org/problem?id=2299 で行なっている。
*/