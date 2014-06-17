#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"

double Fittness_Function(struct factory *factoryInfo,int *routeInfo)     //计算适应度
{
	int i,externd;                                              //externd距离的标识
	double distance[FACTORY_COUNT+1]={0.0},result=0.0;         //初始化距离为0
	distance[0]=Distance_Function(0,routeInfo[1],factoryInfo);   //先计算出从配送中心到达第一个下游工厂的距离，做为下面叠加的基础
	for (externd=1;externd<FACTORY_COUNT+1;externd++)
	{    
		distance[routeInfo[externd]]=distance[routeInfo[externd-1]]+Distance_Function(routeInfo[externd-1],routeInfo[externd],factoryInfo);   
	}                                 //通过叠加的方式计算配送中心与各个下游工厂的距离
	for (i=0;i<FACTORY_COUNT;i++)
	{	
		result+=distance[routeInfo[i]]*(factoryInfo[routeInfo[i+1]].factoryD);	//全程的功为各个点的功的总和		
	}
	result=result+distance[routeInfo[i]]*TRUCK_WIGHT;   //各个下游工厂的距离与需求的乘积+空载时遍历所有节点所作的功
	return ((1/result)*1000000); //将适应度扩大100万倍，便于比较，返回适应度，适应度为全过程所作总功的倒数，做的总功越少，适应度越大，值越优
}
double Distance_Function(int source,int destence,struct factory  *factoryInfo)    //以坐标计算两下游工厂和原材料配送中心的距离
{	
	double result;
	result=sqrt(pow((factoryInfo[destence].factoryX-factoryInfo[source].factoryX),2)+pow((factoryInfo[destence].factoryY-factoryInfo[source].factoryY),2)); 
	//计算两点之间的距离 
	return result;  //返回两点之间的距离
}
void Rand_Route_Function(int *routeInfoC)               //生成随机的路径的函数
{	
	int i,j,k,flag=0;
	int randNum[FACTORY_COUNT+2]={0};	//给randNum[j]赋初值0    
	for (j=1;j<FACTORY_COUNT+1;j++)
    {
		k=rand()%FACTORY_COUNT+1;		   //产生1到FACTORY_COUNT的随机数
		flag=0;                    //设置标志位，判断randNum的值是否可取
		for (i=0;i<j;i++)      
		{
			if (k==randNum[i])    //确保randNum[j]的值唯一
			{
				i=j;   
				j--;             //表示当前值不取
				flag=1;				
			}			
		}
		if(flag==0)		     //表示所取的值满足要求，并将值付给randNum[j]
		{
			randNum[j]=k;			
		}
		
    }
	for (i=0;i<FACTORY_COUNT+2;i++)
	{
		routeInfoC[i]=randNum[i];       //初始化一个种群路径信息
	}	
	return ;
}














