#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"

void Update_Pheromone_Function(struct factory *factoryInfo,struct ant *antInfo,double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],double *pheromoneDeliverConst)  //更新每条路径上得信息素
{
	int i,j;	
       for (i=0;i<ANT_COUNT;i++)
       {           //计算每一只蚂蚁走过的路径的总功
		antInfo[i].totalWork=Calculate_Total_Work_Function(factoryInfo,antInfo[i].tabuRoute);    
       }
	for (i=0;i<FACTORY_COUNT+1;i++)
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{
			pheromone[i][j]=pheromone[i][j]*(*pheromoneDeliverConst);  //先计算出信息素的消散
		}
	}
	for (i=0;i<ANT_COUNT;i++)    //一次搜索之后的信息素的更新
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{           //某一条路径上的所有边上信息素都加相同值，由这一条路径的总功决定，总功越少，增加的信息素就越多
			pheromone[antInfo[i].tabuRoute[j]][antInfo[i].tabuRoute[j+1]]+=PHEROMONE_ADD_CONST/distance[antInfo[i].tabuRoute[j]][antInfo[i].tabuRoute[j+1]];
		}
	}
	return ;
}
double Calculate_Total_Work_Function(struct factory *factoryInfo,int *tabuRoute)     //计算总功
{
	int i,externd;                                              //externd距离的标识
	double distanceTotal[FACTORY_COUNT+1]={0.0},result=0.0;         //初始化距离为0
	distanceTotal[0]=Distance_Function(0,tabuRoute[1],factoryInfo);   //先计算出从配送中心到达第一个下游工厂的距离，做为下面叠加的基础
	for (externd=1;externd<FACTORY_COUNT+1;externd++)
	{    
		distanceTotal[tabuRoute[externd]]=distanceTotal[tabuRoute[externd-1]]+Distance_Function(tabuRoute[externd-1],tabuRoute[externd],factoryInfo);   
	}                                 //通过叠加的方式计算配送中心与各个下游工厂的距离
	for (i=0;i<FACTORY_COUNT;i++)
	{	
		result+=distanceTotal[tabuRoute[i]]*(factoryInfo[tabuRoute[i+1]].factoryD);	//全程的功为各个点的功的总和		
	}
	result=result+distanceTotal[tabuRoute[i]]*TRUCK_WIGHT;   //各个下游工厂的距离与需求的乘积+空载时遍历所有节点所作的功
	return (result*FRICTION_RATIO);                 //返回蚂蚁走过的一条路径所作的总功
}
double Distance_Function(int source,int destence,struct factory *factoryInfo)    //计算两个坐标点之间的距离
{	
	double result;
	result=sqrt(pow((factoryInfo[destence].factoryX-factoryInfo[source].factoryX),2)+pow((factoryInfo[destence].factoryY-factoryInfo[source].factoryY),2)); 
	//计算两点之间的距离 
	return result;  //返回两点之间的距离
}



