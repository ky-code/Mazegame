// Mazegame�̃v���O����
// C++�ō쐬

/*

����̍X�V
�E�����̔Ֆʂ�ǂݍ���ŁA�V�ԃR�[�X��I���ł���悤�ɂ���
�E�V���Ɂu�J�M�v�Ɓu�J�M�ŊJ�����v��p�ӂ��A�J�M���Ȃ��Ɛ�֐i�߂Ȃ��A�Ƃ������[����ǉ�����

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
			printf("���͉��֐i�ނƂ悢�ł��傤�B");
			break;
		case 1:
			printf("���͉E�֐i�ނƂ悢�ł��傤�B");
			break;
		case 2:
			printf("���͏�֐i�ނƂ悢�ł��傤�B");
			break;
		case 3:
			printf("���͍��֐i�ނƂ悢�ł��傤�B");
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
	printf("��ֈړ��FU,u\n");
	printf("���ֈړ��FD,d\n");
	printf("���ֈړ��FL,l\n");
	printf("�E�ֈړ��FR,r\n");
	printf("�q���g�FH,h\n");
	printf("�r���I���FE,e\n");
	printf("���̍s����I�����Ă�������\n\n");
	
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
		printf("\n������x���͂��Ă��������B\n");
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
		printf("�t�@�C��������܂���\n");
		return 0;
	}
	// ����
	fscanf(fp,"%d %d",&h,&w);
	for(i=0;i<=h-1;i++){
		fscanf(fp,"%s",cell[i]);
		for(j=0;j<=w-1;j++){
			if(cell[i][j]=='s'){	// �X�^�[�g�̃}�X
				sx=i;
				sy=j;
			}
			if(cell[i][j]=='g'){	// �S�[���̃}�X
				gx=i;
				gy=j;
			}
		}
	}
	fclose(fp);
	
	// �Ֆʂ̏o��
	printf("\n���H�̔Ֆʂł�\n");
	for(i=0;i<=h-1;i++){
		printf("%s\n",cell[i]);
	}
	
	// ���H�������邩�ǂ���
	int res=bfs();	// �ŏ��̈ړ��񐔂����߂�
	if(res==INF){
		printf("���̖��H�͉������Ƃ��ł��܂���B�Q�[�����I�����܂��B\n");	// �����Ȃ��ꍇ�̓v���O�������I������
		return 0;
	}else{
		printf("���̖��H�͉������Ƃ��ł��܂��B\n",res);
		printf("�ŏ��̈ړ��񐔂�%d��ł��B\n",res);
	}
	// �Q�[���̊J�n�i���݂̈ʒu��@�ŕ\���j
	printf("\n�Q�[�����J�n���܂�\n");
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
	
	// �Q�[�������s
	play(sx,sy);
	
	if(goal){
		printf("�N���A�ł��B���߂łƂ��������܂��B\n");
		printf("�ړ��񐔂�%d��ł����B",turn);
		if(turn==res){
			printf("�ŏ��̈ړ��񐔂ł̃N���A�ł��B");
		}
		printf("\n");
		printf("�q���g�̎g�p�񐔂�%d��ł����B\n",hintcall);
	}
	printf("\n�Q�[�����I�����܂��B\n");
	
	return 0;
}

