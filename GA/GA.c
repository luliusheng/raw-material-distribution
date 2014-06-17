#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void main() 
{
	int j,k;
	int fittnessOrder;    //要求结果输出按适应度大小降序排列的前fittnessOrder位	
	struct factory  factoryInfo[FACTORY_COUNT+1];         //定义每个工厂（包括原材料配送中心）的信息
	struct route  population[INIT_POPULATION_NUM];        //定义种群每个个体的路径
	fittnessOrder=10;   //结果输出按适应度大小降序排列的前fittnessOrder位
	Init_Factory_Information_Function(factoryInfo);       //初始化工厂信息
	Init_Population_Function(population,factoryInfo);                //初始化种群	
    Evaluate_Population_Function(population,factoryInfo);            //评估种群	
	for (k=0;k<GENERATION_NUM;k++)                      //对种群进行GENERATION_NUM次进化
	{
		Crossover_Function(population);	  //对种群亲代进行交叉操作产生新的种群，个体总数为INIT_POPULATION_NUM
		                     //其中，POPULATION_PARENT_NUM为亲代的个体数，POPULATION_PARENT_NUM为子代个体数
                            //每进行一次变异对数量为POPULATION_PARENT_NUM的亲代进行复制，交叉和变异产生的子代数为POPULATION_CHILDREN_NUM
		Evaluate_Population_Function(population,factoryInfo);            //评估种群，对数量为INIT_POPULATION_NUM的种群计算适应度和排序		
		Mutation_Function(population);                      //对子代进行变异操作产生新的种群，个体总数为INIT_POPULATION_NUM
	    Evaluate_Population_Function(population,factoryInfo);     //评估种群,对数量为INIT_POPULATION_NUM的种群计算适应度和排序				
	}
	printf("///////GA////第INIT_POPULATION_NUM/2 个/////////////////////////\n");
	printf("第%d个种群个体: %f\n",POPULATION_PARENT_NUM,((1/population[POPULATION_PARENT_NUM-1].fittness)*1000000*FRICTION_RATIO));     ///输出种群中第POPULATION_PARENT_NUM个个体的适应度
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
		printf("适应度:%d\n",population[POPULATION_PARENT_NUM-1].routeInfo[j]);  //  //输出种群中第POPULATION_PARENT_NUM个个体的路径信息
	}
	printf("////////////GA/////相对最优个体///////////////////////////////\n");
	printf("GAabsolute RouteInfomation:%f\n",((1/population[0].fittness)*1000000*FRICTION_RATIO));     //输出相对最优种群个体的适应度
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
		printf("RouteInfomation[%d]:%d\n",j,population[0].routeInfo[j]);  //输出相对最优种群个体的路径信息
	}	
}