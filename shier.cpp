#include<stdio.h>
#include<stdlib.h>
#define Max_Vertex_Num 100//图中顶点数目的最大值 
//图的邻接表存储结构定义 
typedef struct AcrNode{//边表结点 
	int adjvex;//该弧所指向的顶点的位置
	struct AcrNode *nextarc;//指向下一条弧的指针 
}ArcNode;
//表头结点
typedef struct  VNode{//顶点表结点 
	int vertex;//顶点信息 
	AcrNode *firstarc;//指向第一条依附于该顶点的弧的指针 
}VNode,Adjlist[Max_Vertex_Num];
typedef struct{
	Adjlist adjlist;//邻接表
	int vexnum,arcnum;//图的顶点数和弧数 
}ALGraph;             //ALGraph是以邻接表存储的图的类型 
int findVex(ALGraph *G,int v){
	int i;
	for(i=0;i<G->vexnum;++i){
		if(G->adjlist[i].vertex==v){
			return i;     //找到在链表的第i行 
		}
	}
	return -1;//没有 
} 
void create(ALGraph *G){//构造有向图 
	ArcNode *p;
	int i,j,k;
	int v1,v2;
	scanf("%d %d",&G->vexnum,&G->arcnum);//顶点数，边数
	for(k=0;k<G->vexnum;k++){
		G->adjlist[k].vertex=k;
		G->adjlist[k].firstarc=NULL;//初始化 
	} 
	k=0;
	while(k<G->arcnum){
            scanf("%d,%d",&v1,&v2);
            k++;
            i = findVex(G,v1);
            j = findVex(G,v2);
            //给第i的表头添加数据是j的节点
            p=(ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->nextarc = G->adjlist[i].firstarc;
            G->adjlist[i].firstarc = p;
        }
	}
void outdegree(ALGraph *G){//计算出度 
	int i;
	int count =0;
	ArcNode *p;
	for(i=0;i<G->vexnum;i++){
		int degree = 0;
        p = G->adjlist[i].firstarc;
        while(p!=NULL)//只需要计算某一个定顶点其邻接表中的结点的个数即可 
        {
            degree++;
            p=p->nextarc;
        }
            printf("%d ",degree);
	}
	printf("\n");
}
void indegree(ALGraph *G)
{//有向图求顶点的入度，需要遍历全部的邻接表 
    ArcNode *p;
    int i;
    //数组存放每个顶点的入度数量
    int arr[1000];
    for(i=0;i<G->vexnum;i++)
    {
        arr[i]=0;//赋初值 
    }
    for(i = 0;i<G->vexnum;i++)
    {
        p = G->adjlist[i].firstarc;
        while(p!=NULL)
        {   //在边表中出现的数据出现一次就作为入度一次 
            arr[p->adjvex]++;
            p=p->nextarc;
        }
    }
    for(i=0;i<G->vexnum;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void adjacentedge(ALGraph *G)//邻接边 
{//读取顶点V的出边表结点即可  
    int i;
    ArcNode *p;
    for(i=0;i<G->vexnum;i++)
    {
        p = G->adjlist[i].firstarc;
		printf("第%d个顶点的所有邻接边\n",i+1);
        while(p!=NULL)
        {
			
            printf("<%d,%d> ",G->adjlist[i].vertex,p->adjvex);//输出邻接边 
            p=p->nextarc;
			printf("\n");
        }
		printf("\n");
	}
}
int main()
{
    ALGraph G;
    create(&G);
    printf("有向图输出邻接边\n");
    adjacentedge(&G);
    printf("\n");
    printf("有向图则依次输出每个顶点的入度:\n");//计算入度
    indegree(&G);
	printf("有向图则依次输出每个顶点的出度:\n");//计算出度
    outdegree(&G);
    return 0;
}