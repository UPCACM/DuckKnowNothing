int l = 0, r= 0, sum = 0, ans=n+1;
while(true){
    while(r < n && sum < s) sum+=a[r++];//从前面开始
    if(sum < s) break;//区间和小于s；
    ans = min(r-l,ans);//ans就是最小长度
    sum -= a[l++];//尺取法的前进；
}
