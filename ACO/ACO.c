/****************************************************************
此模型采取信息素局部更新方式，为蚁量模型：蚂蚁在自己所走过的边上释
放的信息素是蚂蚁走过边的长度的倒数
****************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"
void main()
{
	int i,j,interationCount=0;  //定义迭代次数指标并初始化为0
        int robustness=0;   //用于判断是否要减小信息素传递参数rou和确定性性搜索或探索性搜索q0的值
	int stopFlag=0;    //算法停止标志
	int pheromoneRoute[FACTORY_COUNT+2]={0};   //定义信息素浓度最大的路径并初始化为0
	double pheromoneBasedTotalWork;    //按信息素选择的路径的总功
	double pheromoneDeliverConst=ROU_MAX;   //信息素传递参数,初始化为最大值
	double searchChooseConst=SEARCH_CHOOSE_MAX;   //探索性方式选择参数,初始化为最大值    
	double distance[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0};
        double pheromone[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0};	
	struct factory  factoryInfo[FACTORY_COUNT+1];         //定义每个工厂（包括原材料配送中心）的信息	
	struct ant antInfo[ANT_COUNT];      //定义蚂蚁信息的结构体,包括蚂蚁以走的路径信息
	
	Init_Factory_Information_Function(factoryInfo);      //初始化各个下游工厂以及供应商的位置及需求信息
        Init_Distance_Information_Function(factoryInfo,distance);  //初始化各个下游工厂以及供应商的距离矩阵
	Init_Pheromone_Information_Function(pheromone);  //初始化各个下游工厂以及供应商之间的信息素浓度，无单位，为具体值
	Ant_Information_Function(antInfo);   //初始化蚂蚁信息
       while ((stopFlag<CONSTRICTION_CONST)&&(interationCount<=INTERATION_COUNT))
       {
		interationCount++;
		Choose_Route_Function(antInfo,distance,pheromone,factoryInfo,&searchChooseConst);  //路径选择确定性搜索与探索性搜索			
	    Update_Pheromone_Function(factoryInfo,antInfo,pheromone,distance,&pheromoneDeliverConst);//更新每一边路径上的信息素		
		Based_Pheromone_Route_Function(pheromone,pheromoneRoute,&robustness);  //求出基于信息素的相对最优路径信息
		Update_Row_Q_Function(&pheromoneDeliverConst,&searchChooseConst,&robustness,&stopFlag);  //更新信息素传递参数rou和搜索选择q0的值的函数 	
       }
	pheromoneBasedTotalWork=Calculate_Total_Work_Function(factoryInfo,pheromoneRoute);     //根据相对最优路径信息计算总功
	printf("//////ACO//////随机选择一组蚂蚁的总功(功20组)/////////////////////////\n");
	for (i=0;i<20;i++)     //随机选择一组蚂蚁的总功，进行比较
	{		
	    printf("总功[%d]:%f\n",i,antInfo[i].totalWork); //计算i和j之间的距离
	}	
	printf("//////////ACO//相对最优个体//////////////////////\n");
	printf("总功:%f\n",pheromoneBasedTotalWork); //计算i和j之间的距离
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
	    printf("basedPheromone%d:%d\n",j,pheromoneRoute[j]);  //将总功最小的蚂蚁的路径信息输出
	}	
}
void Update_Row_Q_Function(double *pheromoneDeliverConst,double *searchChooseConst,int *robustness,int *stopFlag)  //更新信息素传递参数rou和搜索选择q0的值的函数
{
	if (*robustness==ROBUSTNESS)
	{
		*robustness=0;    //清零
		(*pheromoneDeliverConst)*=ROU_CHANGE_RANGE;   //信息素传递参数乘以ROU_CHANGE_RANGE ，减小 
		if (*pheromoneDeliverConst<=ROU_MIN)
		{
			*pheromoneDeliverConst=ROU_MIN; //ROU不能无限小，确保收敛		
		}		
        (*searchChooseConst)*=ROU_CHANGE_RANGE;       //探索方式参数乘以ROU_CHANGE_RANGE，减小 
		if (*searchChooseConst<=SEARCH_CHOOSE_MIN)
		{
			*searchChooseConst=SEARCH_CHOOSE_MIN; //探索方式选择参数q0不能无限小，确保收敛			
		}
	}
	if (*pheromoneDeliverConst==ROU_MIN)
	{
		(*stopFlag)++;
	}
	return ;
}
void Based_Pheromone_Route_Function(double (*pheromone)[FACTORY_COUNT+1],int *pheromoneRoute,int *robustness) 
{            //找出信息素浓度最大的路径，即蚂蚁最终都会走的路径
	int i,j,k;
	int choosePoint,flag,choosePointFalg,robustnessFlag; //选择点    与  退出标志，选择标志  选择点标志 ,鲁棒性检查标志
	int pheromoneRoutefront[FACTORY_COUNT+2];       //用于装上一次得到的信息素的路径信息
	int tabuNumber; //禁忌的数字	 
	tabuNumber=1;
	robustnessFlag=0;
	for (i=0;i<FACTORY_COUNT+2;i++)
	{
	    pheromoneRoutefront[i]=pheromoneRoute[i]; 	   //存储上一次的路径信息
	}
	for (i=0;i<FACTORY_COUNT;i++)
	{
		choosePoint=1;			//找出概率最大的点					
		flag=0;
		while (!flag)               //确保不出现第一个最大的情况
		{
			choosePointFalg=0;
			for (k=1;k<=i;k++)    //禁忌搜索
			{
				if (pheromoneRoute[k]==choosePoint)   //如果choosePoint是已经选过的点就应当去掉
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
		for (j=1;j<FACTORY_COUNT+1;j++)      //信息素的浓度选择最大
		{	
			if(pheromone[pheromoneRoute[i]][choosePoint]<pheromone[pheromoneRoute[i]][j]) 
			{
				for (k=1;k<=i;k++)    //禁忌搜索
				{
					if (pheromoneRoute[k]==j)
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
		pheromoneRoute[tabuNumber]=choosePoint; 	
	    tabuNumber++;		
	}
    for (i=0;i<FACTORY_COUNT+1;i++)
    {  
		if (pheromoneRoute[i]-pheromoneRoutefront[i])     //若有不同（改变）则放置标志位
		{
			robustnessFlag=1;    
		} 
    }
	if (robustnessFlag==0)
	{
      (*robustness)++;
	}
	else
	{
		*robustness=0;
	}
}
