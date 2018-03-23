// Mazegameのプログラム
// C++で作成

/*

今後の更新
・複数の盤面を読み込んで、遊ぶコースを選択できるようにする
・新たに「カギ」と「カギで開く扉」を用意し、カギがないと先へ進めない、というルールを追加する

*/

#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

const int INF=1000000;
char cell[1001][1001],s[5];
int h,w,i,j,goal=0,flag;
int sx,sy,gx,gy;
int d[1001][1001];
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int turn=0;
int hintcall=0;
FILE *fp;

typedef pair<int,int> P;


int bfs(){
	queue<P> que;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			d[i][j]=INF;
		}
	}
	que.push(P(gx,gy));
	d[gx][gy]=0;
	
	while(que.size()){
		P p=que.front();
		que.pop();
		for(i=0;i<4;i++){
			int nx=p.first+dx[i];
			int ny=p.second+dy[i];
			if(0<=nx&&nx<h&&0<=ny&&ny<w&&cell[nx][ny]!='#'&&d[nx][ny]==INF){
				que.push(P(nx,ny));
				d[nx][ny]=d[p.first][p.second]+1;
			}
		}
	}
	return d[sx][sy];
}

void hint(int x,int y){
	
	int hint[5];
	int minturn=1000000;
	int hintdir=-1;
	
	for(i=0;i<=3;i++){
		hint[i]=1000001;
	}
	
	if(x+1<h){
		hint[0]=d[x+1][y];
	}
	if(y+1<w){
		hint[1]=d[x][y+1];
	}
	if(x-1>=0){
		hint[2]=d[x-1][y];
	}
	if(y-1>=0){
		hint[3]=d[x][y-1];
	}
	
	for(i=0;i<=3;i++){
		if(hint[i]<minturn){
			hintdir=i;
			minturn=hint[i];
		}
	}
	
	printf("\n");
	
	switch(hintdir){
		case 0:
			printf("次は下へ進むとよいでしょう。");
			break;
		case 1:
			printf("次は右へ進むとよいでしょう。");
			break;
		case 2:
			printf("次は上へ進むとよいでしょう。");
			break;
		case 3:
			printf("次は左へ進むとよいでしょう。");
			break;
	}
	
	hintcall++;
	
	return;
}


void play(int x,int y){
	if(goal==1){
		return;
	}
	
	flag=1;
	printf("上へ移動：U,u\n");
	printf("下へ移動：D,d\n");
	printf("左へ移動：L,l\n");
	printf("右へ移動：R,r\n");
	printf("ヒント：H,h\n");
	printf("途中終了：E,e\n");
	printf("次の行動を選択してください\n\n");
	
	scanf("%s",s);
	if((s[0]=='U'||s[0]=='u')&&(x-1>=0&&cell[x-1][y]!='#')){
		x=x-1;
		turn++;
	}else if((s[0]=='D'||s[0]=='d')&&(x+1<=h-1&&cell[x+1][y]!='#')){
		x=x+1;
		turn++;
	}else if((s[0]=='L'||s[0]=='l')&&(y-1>=0&&cell[x][y-1]!='#')){
		y=y-1;
		turn++;
	}else if((s[0]=='R'||s[0]=='r')&&(y+1<=w-1&&cell[x][y+1]!='#')){
		y=y+1;
		turn++;
	}else if(s[0]=='E'||s[0]=='e'){
		return;
	}else if(s[0]=='H'||s[0]=='h'){
		hint(x,y);
	}else{
		printf("\nもう一度入力してください。\n");
		flag=0;
	}
	
	if(flag){
		printf("\n");
		for(i=0;i<=h-1;i++){
			for(j=0;j<=w-1;j++){
				if(i==x&&j==y){
					printf("@");
				}else{
					printf("%c",cell[i][j]);
				}
			}
			printf("\n");
		}
	}
	
	if(x==gx&&y==gy){
		goal=1;
	}
	play(x,y);
}

int main(void){
	
	fp=fopen("maze.txt","r");
	if(NULL==fp){
		printf("ファイルがありません\n");
		return 0;
	}
	// 入力
	fscanf(fp,"%d %d",&h,&w);
	for(i=0;i<=h-1;i++){
		fscanf(fp,"%s",cell[i]);
		for(j=0;j<=w-1;j++){
			if(cell[i][j]=='s'){	// スタートのマス
				sx=i;
				sy=j;
			}
			if(cell[i][j]=='g'){	// ゴールのマス
				gx=i;
				gy=j;
			}
		}
	}
	fclose(fp);
	
	// 盤面の出力
	printf("\n迷路の盤面です\n");
	for(i=0;i<=h-1;i++){
		printf("%s\n",cell[i]);
	}
	
	// 迷路が解けるかどうか
	int res=bfs();	// 最小の移動回数を求める
	if(res==INF){
		printf("この迷路は解くことができません。ゲームを終了します。\n");	// 解けない場合はプログラムを終了する
		return 0;
	}else{
		printf("この迷路は解くことができます。\n",res);
		printf("最小の移動回数は%d回です。\n",res);
	}
	// ゲームの開始（現在の位置を@で表示）
	printf("\nゲームを開始します\n");
	for(i=0;i<=h-1;i++){
		for(j=0;j<=w-1;j++){
			if(i==sx&&j==sy){
				printf("@");
			}else{
				printf("%c",cell[i][j]);
			}
		}
		printf("\n");
	}
	
	// ゲームを実行
	play(sx,sy);
	
	if(goal){
		printf("クリアです。おめでとうございます。\n");
		printf("移動回数は%d回でした。",turn);
		if(turn==res){
			printf("最小の移動回数でのクリアです。");
		}
		printf("\n");
		printf("ヒントの使用回数は%d回でした。\n",hintcall);
	}
	printf("\nゲームを終了します。\n");
	
	return 0;
}

