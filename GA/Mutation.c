#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Mutation_Function(struct route *population)    //对子代进行变异操作
{
	int i,j,k;  
	int geneChangePointA,geneChangePointB;  //基因交换点A和B
	int changeVariable;               // 基因交换的中间变量
	int mutationIndividual;       //变异的个体
    int mutationNum;      //随机数，确定变异次数  
    for (i=0;i<POPULATION_CHILDREN_NUM;i++)//POPULATION_CHILDREN_NUM
    {
		mutationIndividual=Generate_Crossover_Individual_Function();  //确定产生变异的个体
		for (k=1;k<FACTORY_COUNT+1;k++)   //首先对亲代进行复制
		{
			population[POPULATION_PARENT_NUM+i].routeInfo[k]=population[mutationIndividual].routeInfo[k];
		}
		mutationNum=rand()%MUTATION_NUM+1;  //随机数，确定变异次数:1~MUTATION_NUM,对结果的影响较大
		for (j=0;j<mutationNum;j++)
		{
			do {                     //产生交叉的两个个体且这两个个体不能相同
				geneChangePointA=rand()%FACTORY_COUNT+1;
				geneChangePointB=rand()%FACTORY_COUNT+1;
			} while(geneChangePointA==geneChangePointB); 			
			changeVariable=population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointA];      //交换基因
			population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointA]=population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointB];
			population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointB]=changeVariable;
		}
    }
	
}


int Generate_Crossover_Individual_Function(void)       //产生进行交叉或变异的个体
{
	int i,j,randomNum;        //randomNum1~5050的随机数
	int cumulativeValue,chooseNumber,randBase;	
	randBase=0;                      //初始化随机数基数的值 
	for (j=1;j<POPULATION_PARENT_NUM+1;j++)
	{
		randBase+=j;                 //自然数的累加作为概率的基数
	}
    randomNum=rand()%randBase+1;                 //产生随机数1~5050(当POPULATION_PARENT_NUM=100S时)
	i=0;                                //初始化i的值
	cumulativeValue=0;                  //初始化累加数的值 
	while (cumulativeValue<randomNum)   //累加值不随机值小，有此判定这次随机选择了哪一个种群个体作为亲代进行变异或交叉操作   
	{
		i++;
		cumulativeValue+=i;		   //自然数的累加
	}   
	chooseNumber=100-i;	       //转换i值为种群个体数组的下标值
	return chooseNumber;       //返回被选择的数字做为进行交叉变异种群个体的亲代标识
}