#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"

void Evaluate_Ant_Route_Function(struct ant *antInfo,struct factory *factoryInfo)       //评估蚂蚁的路径，产生总功和按总功排序的结果
{
	int i,j,k,routeChange;                    //routeChange交换路径信息的中间变量 
	double totalWorkChange;                    //交换总功的中间变量  
	for (j=0;j<ANT_COUNT;j++)
	{
		antInfo[j].totalWork=Calculate_Total_Work_Function(factoryInfo,antInfo[j].tabuRoute);	//产生种群个体j的总功
	}
	for (i=0;i<ANT_COUNT-1;i++)      
	{
		for (j=i+1;j<ANT_COUNT;j++)
		{
			if (antInfo[i].totalWork>antInfo[j].totalWork)      // 按总功大小从小到大排序
			{
				totalWorkChange=antInfo[i].totalWork;          // 交换总功	
				antInfo[i].totalWork=antInfo[j].totalWork;
				antInfo[j].totalWork=totalWorkChange;
                for (k=0;k<FACTORY_COUNT+2;k++)
                {
					routeChange=antInfo[i].tabuRoute[k];			  // 交换路径信息	
					antInfo[i].tabuRoute[k]=antInfo[j].tabuRoute[k];
					antInfo[j].tabuRoute[k]=routeChange;
                }				
			}			
		}
		
	}
}

