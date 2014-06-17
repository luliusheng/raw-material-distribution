#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Evaluate_Population_Function(struct route *population,struct factory *factoryInfo)   //评估种群，产生适应度和按适应度排序的结果
{
	int i,j,k,routeChange;                    //routeChange交换路径信息的中间变量 
	double fittnessChange;                    //交换适应度的中间变量  
	for (j=0;j<INIT_POPULATION_NUM;j++)
	{
		population[j].fittness=Fittness_Function(factoryInfo,population[j].routeInfo);	//产生种群个体j的适应度
	} 
	for (i=0;i<INIT_POPULATION_NUM-1;i++)      
	{
		for (j=i+1;j<INIT_POPULATION_NUM;j++)
		{
			if (population[i].fittness<population[j].fittness)
			{
				fittnessChange=population[i].fittness;          // 交换适应度	
				population[i].fittness=population[j].fittness;
				population[j].fittness=fittnessChange;
                for (k=0;k<FACTORY_COUNT+2;k++)
                {
					routeChange=population[i].routeInfo[k];			  // 交换路径信息	
					population[i].routeInfo[k]=population[j].routeInfo[k];
					population[j].routeInfo[k]=routeChange;
                }				
			}			
		}
		
	}
}
