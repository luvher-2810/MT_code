#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

int n, k;
string lst;
string s;

int process(){
	string b = s;
	
	for (int i = 0; i < s.size(); i ++ )
		if (i > 0 && i < s.size() - 1)
			if (s[i - 1] == '1' && s[i + 1] == '1'){
				if (b[i] == '0') b[i] = '1';
				else
				if (b[i] == '1') b[i] = '0';
			}
	
	if (lst == b) return 1;
	if (s == b) return 2;
	lst = s;
	s = b;
	return 0;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> k;
	
	cin >> s;
	
	for (int i = 1; i <= k; i ++ ){
		int h = process();
		if (h != 0){
			if (h == 1){
				if ((k - i)%2) cout << s;
				else cout << lst;
			}
			if (h == 2){
				cout << s;
			}
			return 0;
		}
		//cout << s <<endl;
	}
	
	cout << s;
}
/*
6 4
110111
*/
