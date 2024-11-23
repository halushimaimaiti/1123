#include "bits/stdc++.h"

using namespace std;

#define FOR_INC(i, start, end) for (int i = start; i < end; ++i)
#define FOR_DEC(i, start, end) for (int i = start; i > end; --i)
#define FOR_INC_EQUAL(i, start, end) for (int i = start; i <= end; ++i)
#define FOR_DEC_EQUAL(i, start, end) for (int i = start; i >= end; --i)
#define int long long

void getNums(string s){
    string t;
    for(char ch:s){
        if(ch=='['){
            t+='{';
        }else if(ch==']'){
            t+='}';
        }else{
            t+=ch;
        }
    }
    cout<<t<<endl;
}
class Fenwick {

public:
    vector<int> f;
    Fenwick(int n) : f(n+1) {
        for(int i=0;i<n;i++){
            add(i+1,f[i]);
        }
    }
    static int lowBit(int n){
        return n&-n;
    }
    void add(int i, int val) {
        for (; i < f.size(); i += lowBit(i)) {
            f[i] += val;
        }
    }

    int query(int i) {
        int res = 0;
        for (; i > 0; i -= lowBit(i)) {
            res += f[i];
        }
        return res;
    }


    int get(int index){
        return f[index];
    }
};

class UnionFind {
    std::vector<int> root;
    std::vector<int> rank;
public:
    explicit UnionFind(int size) {
        root.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; ++i) {
            root[i] = rank[i] = i;
        }
    }

    int find(int x) {
        if (x == root[x])
            return x;
        return root[x] = find(root[x]);
    }

    void connect(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

class NumArray {

private:
    vector<int> nums_;
    Fenwick* fenwick_;
public:


    NumArray(vector<int>& nums) :nums_(nums){
        fenwick_ = new Fenwick(nums.size()+1);
        for(int i=1;i<=nums.size();i++){
            fenwick_->add(i,nums[i-1]);
        }
    }

    void update(int index, int val) {
        fenwick_->add(index+1,val-fenwick_->f[index]);
        fenwick_->f[index] = val;
    }

    int sumRange(int left, int right) {
        return fenwick_->query(right+1)-fenwick_->query(left);
    }
};

class KMP{
private:
    vector<vector<int>> dp;
    string pat_;
    int size = 128;

public:
    KMP(const string& pat){
        this->pat_ = pat;
        int n = pat.length();
        dp.resize(n,vector<int>(size,0));
        dp[0][pat[0]]=1;
        int pre = 0;
        for(int j=1;j<n;j++){
            for(int c=0;c<size;c++){
                dp[j][c] = dp[pre][c];
            }
            dp[j][pat[j]]=j+1;
            pre = dp[pre][pat[j]];
        }
    }

    int search(const string& txt){
        int M = pat_.size();
        int N = txt.size();
        int j = 0;
        for(int i=0;i<N;i++){
            j = dp[j][txt[i]];
            if(j==M){
                return i-M+1;
            }
        }
        return -1;
    }
};
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:

};


bool isPrime(int n){
    if(n<=2){
        return true;
    }
    if(n%2==0){
        return false;
    }
    for(int i=3;i<= sqrt(n);i+=2){
        if(n%i==0){
            return false;
        }
    }
    return true;
}
signed main(){
//    Solution s;
//    vector<vector<int>> grid{{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}};
//    vector<int> nums{1,2,3,4,3,2,5};
//    s.nonSpecialCount(1,2);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin>>n;
    unordered_set<int> set1;
    for(int i=2;i<= sqrt(n);i++){
        if(n%i==0){
            if(set1.find(i)!=set1.end()){
                break;
            }
            if(isPrime(i)){
                set1.insert(i);
            }
            if(isPrime(n/i)){
                set1.insert(n/i);
            }
        }
    }
    cout<<set1.size();
    return 0;
}