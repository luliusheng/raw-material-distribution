#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Mutation_Function(struct route *population)    //���Ӵ����б������
{
	int i,j,k;  
	int geneChangePointA,geneChangePointB;  //���򽻻���A��B
	int changeVariable;               // ���򽻻����м����
	int mutationIndividual;       //����ĸ���
    int mutationNum;      //�������ȷ���������  
    for (i=0;i<POPULATION_CHILDREN_NUM;i++)//POPULATION_CHILDREN_NUM
    {
		mutationIndividual=Generate_Crossover_Individual_Function();  //ȷ����������ĸ���
		for (k=1;k<FACTORY_COUNT+1;k++)   //���ȶ��״����и���
		{
			population[POPULATION_PARENT_NUM+i].routeInfo[k]=population[mutationIndividual].routeInfo[k];
		}
		mutationNum=rand()%MUTATION_NUM+1;  //�������ȷ���������:1~MUTATION_NUM,�Խ����Ӱ��ϴ�
		for (j=0;j<mutationNum;j++)
		{
			do {                     //����������������������������岻����ͬ
				geneChangePointA=rand()%FACTORY_COUNT+1;
				geneChangePointB=rand()%FACTORY_COUNT+1;
			} while(geneChangePointA==geneChangePointB); 			
			changeVariable=population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointA];      //��������
			population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointA]=population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointB];
			population[POPULATION_PARENT_NUM+i].routeInfo[geneChangePointB]=changeVariable;
		}
    }
	
}


int Generate_Crossover_Individual_Function(void)       //�������н�������ĸ���
{
	int i,j,randomNum;        //randomNum1~5050�������
	int cumulativeValue,chooseNumber,randBase;	
	randBase=0;                      //��ʼ�������������ֵ 
	for (j=1;j<POPULATION_PARENT_NUM+1;j++)
	{
		randBase+=j;                 //��Ȼ�����ۼ���Ϊ���ʵĻ���
	}
    randomNum=rand()%randBase+1;                 //���������1~5050(��POPULATION_PARENT_NUM=100Sʱ)
	i=0;                                //��ʼ��i��ֵ
	cumulativeValue=0;                  //��ʼ���ۼ�����ֵ 
	while (cumulativeValue<randomNum)   //�ۼ�ֵ�����ֵС���д��ж�������ѡ������һ����Ⱥ������Ϊ�״����б���򽻲����   
	{
		i++;
		cumulativeValue+=i;		   //��Ȼ�����ۼ�
	}   
	chooseNumber=100-i;	       //ת��iֵΪ��Ⱥ����������±�ֵ
	return chooseNumber;       //���ر�ѡ���������Ϊ���н��������Ⱥ������״���ʶ
}