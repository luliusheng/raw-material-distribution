#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Evaluate_Population_Function(struct route *population,struct factory *factoryInfo)   //������Ⱥ��������Ӧ�ȺͰ���Ӧ������Ľ��
{
	int i,j,k,routeChange;                    //routeChange����·����Ϣ���м���� 
	double fittnessChange;                    //������Ӧ�ȵ��м����  
	for (j=0;j<INIT_POPULATION_NUM;j++)
	{
		population[j].fittness=Fittness_Function(factoryInfo,population[j].routeInfo);	//������Ⱥ����j����Ӧ��
	} 
	for (i=0;i<INIT_POPULATION_NUM-1;i++)      
	{
		for (j=i+1;j<INIT_POPULATION_NUM;j++)
		{
			if (population[i].fittness<population[j].fittness)
			{
				fittnessChange=population[i].fittness;          // ������Ӧ��	
				population[i].fittness=population[j].fittness;
				population[j].fittness=fittnessChange;
                for (k=0;k<FACTORY_COUNT+2;k++)
                {
					routeChange=population[i].routeInfo[k];			  // ����·����Ϣ	
					population[i].routeInfo[k]=population[j].routeInfo[k];
					population[j].routeInfo[k]=routeChange;
                }				
			}			
		}
		
	}
}
