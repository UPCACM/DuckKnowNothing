//点v，边e
//邻接矩阵O(v^2)，邻接表O(e log_{2}v)
int prime(int cur) {//當前的根
    int index; //用來臨時存儲最小邊對應的下標
    int sum = 0; //當前數的權值
    memset(visit, false, sizeof(visit)); //初始化節點訪問情況
    visit[cur] = true; //將根節點設置為已訪問
    for(int i = 0; i < m; i ++){
        dist[i] = graph[cur][i]; //dist记录的是树到点i的距离
        //将树根cur视为一颗树，将树到未连接点之间的距离存入dist中
    }
    for(int i = 1; i < m; i ++){
        int mincost = INF; //初始化最小值為INF
        for(int j = 0; j < m; j ++){
            if(!visit[j] && dist[j] < mincost){
            //如果當前邊的另一個點不在生成樹中而且距離小於mincost
                mincost = dist[j]; //更新mincost和其對應邊和點的下標
                index = j;
            }
        }
        visit[index] = true; //標記當前最小的邊為已訪問
        sum += mincost; //最小生成樹的權+=當前這條最小邊的權
        for(int j = 0; j < m; j ++){
            if(!visit[j] && graph[index][j] < dist[j]){
            //如果新加入的这个点到j点的距离小于当前的树到j点的距离
                dist[j] = graph[index][j]; //更新新生成树到j点的距离
            }
        }
    }
    return sum; //返回當前根對應最小生成樹的權值
}
