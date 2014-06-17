#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"

void Choose_Route_Function(struct ant *antInfo,double (*distance)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],struct factory *factoryInfo,double *searchChooseConst)
{           //探索性搜索与确定性搜索的选择路径的函数
	int i,j,k,m;
	int choosePoint,quitFlag,flag,choosePointFalg; //选择点    与  退出标志，选择标志  选择点标志
	int tabuNumber; //禁忌的数字
	double probalityTable[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0}; //建立一个可能性表
	double chooseProbality;  //选择进行确定性搜索或探索性搜索的随机概率    
	Calculate_Probality_Function(probalityTable,pheromone,distance,factoryInfo);  //生成概率路径信息表              	
	m=0;
       while (m<ANT_COUNT)
       {
		tabuNumber=1;
		for (i=0;i<FACTORY_COUNT;i++)
		{
			chooseProbality=((double)(rand()%10000+1))/10000; //产生随机概率  
			if (chooseProbality<(*searchChooseConst)||tabuNumber==FACTORY_COUNT)  //进行确定性搜索
			{				
				choosePoint=1;			//找出概率最大的点					
				flag=0;
				while (!flag)               //确保不出现第一个最大的情况
				{
					choosePointFalg=0;
				    for (k=1;k<=i;k++)    //禁忌搜索
					{
						if (antInfo[m].tabuRoute[k]==choosePoint)   //如果choosePoint是已经选过的点就应当去掉
						{ 
							choosePointFalg=1;  
						    break;    //表示退出当前循环
						}   //设置标记，如果禁忌中有该记录则不取该值							
					}
					if (choosePointFalg==1)
					{
						choosePoint++;
					}
					else 
					{
						flag=1;						
					}
				}
				flag=0;  //标志位清0				
				for (j=1;j<FACTORY_COUNT+1;j++)      //概率的值选择最大
				{
					
					if(probalityTable[antInfo[m].tabuRoute[i]][choosePoint]<probalityTable[antInfo[m].tabuRoute[i]][j]) 
					{
						for (k=1;k<=i;k++)    //禁忌搜索
						{
							if (antInfo[m].tabuRoute[k]==j)
							{ 
								flag=1;//设置标记，如果禁忌中有该记录则不取该值							
                                break;    //表示退出当前循环  
							}   
						}
						if (flag!=1)   //如果flag=0则取j值  值为1则跳过
						{
							choosePoint=j; 							
						}					 
					}
					flag=0;  //标志位清0
				}
				antInfo[m].tabuRoute[tabuNumber]=choosePoint; 	
				tabuNumber++;			
			}
			else             //进行探索性搜索
			{
				quitFlag=0;
				while (!quitFlag)
				{
					choosePoint=rand()%FACTORY_COUNT+1;     //随机选择一个点					
					flag=0;
					for (j=1;j<=i;j++)      //选择最大概率的值
					{
						if (antInfo[m].tabuRoute[j]==choosePoint)
						{ 
							flag=1;  //flag=1表示该j已经被选了
							break;    //表示退出当前循环
						}
					}
					if (flag!=1)     //如果不与禁忌表中的相同
					{
						antInfo[m].tabuRoute[tabuNumber]=choosePoint;
						tabuNumber++;
						quitFlag=1;
					}
				}			
			}	
		}
		m++;
    }	
	return ;
}
double Calculate_Vision_Function(int startPoint,int endPoint,double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo) //计算可见度
{
	double result;
	result=(factoryInfo[endPoint].factoryD+TRUCK_WIGHT)/distance[startPoint][endPoint];//可见度，重量越重可见度越大
	return result;
}
void Calculate_Probality_Function(double (*probalityTable)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo)                  
{                 //计算确定性路径选择时的可能性
	int i,j;
	for (i=0;i<FACTORY_COUNT+1;i++)
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{
			if (i!=j)    //i和j相同表示一个点，不表示边
			{
				probalityTable[i][j]=pow(pheromone[i][j],ALPHA)*pow(Calculate_Vision_Function(i,j ,distance,factoryInfo),BETA);  //计算概率表 
			}			
		}
	}

}

