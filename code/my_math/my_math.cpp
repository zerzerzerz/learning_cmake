int power(const int&a, const int&n){
    int res = 1;
    for(int i=0; i<n; ++i){
        res *= a;
    }
    return res;
}