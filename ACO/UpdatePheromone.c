#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"


void Update_Pheromone_Function(struct factory *factoryInfo,struct ant *antInfo,double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],double *pheromoneDeliverConst)  //����ÿ��·���ϵ���Ϣ��
{
	int i,j;	
       for (i=0;i<ANT_COUNT;i++)
       {           //����ÿһֻ�����߹���·�����ܹ�
		antInfo[i].totalWork=Calculate_Total_Work_Function(factoryInfo,antInfo[i].tabuRoute);    
       }
	for (i=0;i<FACTORY_COUNT+1;i++)
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{
			pheromone[i][j]=pheromone[i][j]*(*pheromoneDeliverConst);  //�ȼ������Ϣ�ص���ɢ
		}
	}
	for (i=0;i<ANT_COUNT;i++)    //һ������֮�����Ϣ�صĸ���
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{           //ĳһ��·���ϵ����б�����Ϣ�ض�����ֵͬ������һ��·�����ܹ��������ܹ�Խ�٣����ӵ���Ϣ�ؾ�Խ��
			pheromone[antInfo[i].tabuRoute[j]][antInfo[i].tabuRoute[j+1]]+=PHEROMONE_ADD_CONST/distance[antInfo[i].tabuRoute[j]][antInfo[i].tabuRoute[j+1]];
		}
	}
	return ;
}
double Calculate_Total_Work_Function(struct factory *factoryInfo,int *tabuRoute)     //�����ܹ�
{
	int i,externd;                                              //externd����ı�ʶ
	double distanceTotal[FACTORY_COUNT+1]={0.0},result=0.0;         //��ʼ������Ϊ0
	distanceTotal[0]=Distance_Function(0,tabuRoute[1],factoryInfo);   //�ȼ�������������ĵ����һ�����ι����ľ��룬��Ϊ������ӵĻ���
	for (externd=1;externd<FACTORY_COUNT+1;externd++)
	{    
		distanceTotal[tabuRoute[externd]]=distanceTotal[tabuRoute[externd-1]]+Distance_Function(tabuRoute[externd-1],tabuRoute[externd],factoryInfo);   
	}                                 //ͨ�����ӵķ�ʽ��������������������ι����ľ���
	for (i=0;i<FACTORY_COUNT;i++)
	{	
		result+=distanceTotal[tabuRoute[i]]*(factoryInfo[tabuRoute[i+1]].factoryD);	//ȫ�̵Ĺ�Ϊ������Ĺ����ܺ�		
	}
	result=result+distanceTotal[tabuRoute[i]]*TRUCK_WIGHT;   //�������ι����ľ���������ĳ˻�+����ʱ�������нڵ������Ĺ�
	return (result*FRICTION_RATIO);                 //���������߹���һ��·���������ܹ�
}
double Distance_Function(int source,int destence,struct factory *factoryInfo)    //�������������֮��ľ���
{	
	double result;
	result=sqrt(pow((factoryInfo[destence].factoryX-factoryInfo[source].factoryX),2)+pow((factoryInfo[destence].factoryY-factoryInfo[source].factoryY),2)); 
	//��������֮��ľ��� 
	return result;  //��������֮��ľ���
}



