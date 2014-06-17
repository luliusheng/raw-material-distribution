#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Crossover_Function(struct route *population)     //种群个体交叉操作，产生新的子代
{
	int i;
	int crossvoerIndividualA,crossvoerIndividualB;    //交叉的两个个体	
	int crossoverPosition[2]={0};            //交叉变异的起始地址和长度    		
	for (i=0;i<POPULATION_CHILDREN_NUM/2;i++)      //产生POPULATION_CHILDREN_NUM个子代，POPULATION_CHILDREN_NUM为偶数最后两位数也正确，
		//为奇数则最会一位不能交叉产生,但对结果没有影响
	{
		Generate_Crossover_Position_Function(crossoverPosition); //生成交叉变异的起始地址和长度
		do {                     //产生交叉的两个个体且这两个个体不能相同
			crossvoerIndividualA=Generate_Crossover_Individual_Function();
			crossvoerIndividualB=Generate_Crossover_Individual_Function();
		} while(crossvoerIndividualA==crossvoerIndividualB); 
        Generate_Children_Function(crossvoerIndividualA,crossvoerIndividualB,crossoverPosition,population,POPULATION_PARENT_NUM+i);   //生成子代
		Generate_Children_Function(crossvoerIndividualB,crossvoerIndividualA,crossoverPosition,population,POPULATION_PARENT_NUM+POPULATION_CHILDREN_NUM-1-i);   //生成子代     
	}    
}
                                            //个体A              //个体B                       //交叉位置：起点和长度       
void Generate_Children_Function(int crossvoerIndividualA,int crossvoerIndividualB,int *crossoverPosition,struct route *population,int childrenNumber)   //生成子代
{
	int i,j;
	int childrenRoute;        //用于存储子代的路径
	int routeFlag;           //routeFlag用于判断是否应当写编码到子代中
	childrenRoute=1;        
    for (i=1;i<crossoverPosition[0];i++)  //搜索插入点前面与交叉段内相同的元素
    {
		routeFlag=0;       //清0  
		for (j=crossoverPosition[0];j<crossoverPosition[0]+crossoverPosition[1];j++)
		{                                                                   //插入段
			if (population[crossvoerIndividualA].routeInfo[i]==population[crossvoerIndividualB].routeInfo[j])   //若有以A段交叉点以前的基因相同则不能删除，具体表现为不取
			{
                routeFlag=1;   	//标志位用于起始点前的基因是否与交叉段内的相同，相同为1，没有则为0
			}
		}
		if (routeFlag!=1)     //与交叉段内的基因不同，可以写入子代
		{
			population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualA].routeInfo[i];
			//将搜索插入点前面与交叉段内不同的元素写入子代中；
			childrenRoute++;   //指向下一个路径编码            
		}
    }
	for (i=crossoverPosition[0];i<crossoverPosition[0]+crossoverPosition[1];i++)     //将B段的代码写入子代中
	{
		population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualB].routeInfo[i];  
		//将B段的代码写入子代中
		childrenRoute++;
	}
	for (i=crossoverPosition[0];i<FACTORY_COUNT+1;i++)  //搜索插入段后面与交叉段内不相同的元素
    {
		routeFlag=0;       //清0  
		for (j=crossoverPosition[0];j<crossoverPosition[0]+crossoverPosition[1];j++)
		{                                                                   //插入段
			if (population[crossvoerIndividualA].routeInfo[i]==population[crossvoerIndividualB].routeInfo[j])
			{
				routeFlag=1;  //标志位用于指示起始点后的基因是否与交叉段内的相同，相同为1，没有则为0
			}
		}
		if (routeFlag!=1)   //起始点后的基因是否与交叉段内的不相同就写入子代
		{
			population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualA].routeInfo[i];
			//将搜索插入点前面与交叉段内不同的元素写入子代中；
			childrenRoute++;   //指向下一个路径编码
		}
    }
}
void Generate_Crossover_Position_Function(int *crossoverPosition)    //长生交叉的起始点和长度
{
    do {
		crossoverPosition[0]=rand()%FACTORY_COUNT+1;   //产生随机数1~FACTORY_COUNT的随机数(FACTORY_COUNT=8)做为交叉起始地址
        crossoverPosition[1]=rand()%(FACTORY_COUNT-1)+1;   //产生随机数1~(FACTORY_COUNT-1)的随机数(FACTORY_COUNT=8)做为交叉段的长度              	
    } while(crossoverPosition[0]+crossoverPosition[1]>9);
    return ;
}