#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void main() 
{
	int j,k;
	int fittnessOrder;    //Ҫ�����������Ӧ�ȴ�С�������е�ǰfittnessOrderλ	
	struct factory  factoryInfo[FACTORY_COUNT+1];         //����ÿ������������ԭ�����������ģ�����Ϣ
	struct route  population[INIT_POPULATION_NUM];        //������Ⱥÿ�������·��
	fittnessOrder=10;   //����������Ӧ�ȴ�С�������е�ǰfittnessOrderλ
	Init_Factory_Information_Function(factoryInfo);       //��ʼ��������Ϣ
	Init_Population_Function(population,factoryInfo);                //��ʼ����Ⱥ	
    Evaluate_Population_Function(population,factoryInfo);            //������Ⱥ	
	for (k=0;k<GENERATION_NUM;k++)                      //����Ⱥ����GENERATION_NUM�ν���
	{
		Crossover_Function(population);	  //����Ⱥ�״����н�����������µ���Ⱥ����������ΪINIT_POPULATION_NUM
		                     //���У�POPULATION_PARENT_NUMΪ�״��ĸ�������POPULATION_PARENT_NUMΪ�Ӵ�������
                            //ÿ����һ�α��������ΪPOPULATION_PARENT_NUM���״����и��ƣ�����ͱ���������Ӵ���ΪPOPULATION_CHILDREN_NUM
		Evaluate_Population_Function(population,factoryInfo);            //������Ⱥ��������ΪINIT_POPULATION_NUM����Ⱥ������Ӧ�Ⱥ�����		
		Mutation_Function(population);                      //���Ӵ����б�����������µ���Ⱥ����������ΪINIT_POPULATION_NUM
	    Evaluate_Population_Function(population,factoryInfo);     //������Ⱥ,������ΪINIT_POPULATION_NUM����Ⱥ������Ӧ�Ⱥ�����				
	}
	printf("///////GA////��INIT_POPULATION_NUM/2 ��/////////////////////////\n");
	printf("��%d����Ⱥ����: %f\n",POPULATION_PARENT_NUM,((1/population[POPULATION_PARENT_NUM-1].fittness)*1000000*FRICTION_RATIO));     ///�����Ⱥ�е�POPULATION_PARENT_NUM���������Ӧ��
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
		printf("��Ӧ��:%d\n",population[POPULATION_PARENT_NUM-1].routeInfo[j]);  //  //�����Ⱥ�е�POPULATION_PARENT_NUM�������·����Ϣ
	}
	printf("////////////GA/////������Ÿ���///////////////////////////////\n");
	printf("GAabsolute RouteInfomation:%f\n",((1/population[0].fittness)*1000000*FRICTION_RATIO));     //������������Ⱥ�������Ӧ��
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
		printf("RouteInfomation[%d]:%d\n",j,population[0].routeInfo[j]);  //������������Ⱥ�����·����Ϣ
	}	
}