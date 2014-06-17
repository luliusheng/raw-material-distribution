#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"
void Crossover_Function(struct route *population)     //��Ⱥ���彻������������µ��Ӵ�
{
	int i;
	int crossvoerIndividualA,crossvoerIndividualB;    //�������������	
	int crossoverPosition[2]={0};            //����������ʼ��ַ�ͳ���    		
	for (i=0;i<POPULATION_CHILDREN_NUM/2;i++)      //����POPULATION_CHILDREN_NUM���Ӵ���POPULATION_CHILDREN_NUMΪż�������λ��Ҳ��ȷ��
		//Ϊ���������һλ���ܽ������,���Խ��û��Ӱ��
	{
		Generate_Crossover_Position_Function(crossoverPosition); //���ɽ���������ʼ��ַ�ͳ���
		do {                     //����������������������������岻����ͬ
			crossvoerIndividualA=Generate_Crossover_Individual_Function();
			crossvoerIndividualB=Generate_Crossover_Individual_Function();
		} while(crossvoerIndividualA==crossvoerIndividualB); 
        Generate_Children_Function(crossvoerIndividualA,crossvoerIndividualB,crossoverPosition,population,POPULATION_PARENT_NUM+i);   //�����Ӵ�
		Generate_Children_Function(crossvoerIndividualB,crossvoerIndividualA,crossoverPosition,population,POPULATION_PARENT_NUM+POPULATION_CHILDREN_NUM-1-i);   //�����Ӵ�     
	}    
}
                                            //����A              //����B                       //����λ�ã����ͳ���       
void Generate_Children_Function(int crossvoerIndividualA,int crossvoerIndividualB,int *crossoverPosition,struct route *population,int childrenNumber)   //�����Ӵ�
{
	int i,j;
	int childrenRoute;        //���ڴ洢�Ӵ���·��
	int routeFlag;           //routeFlag�����ж��Ƿ�Ӧ��д���뵽�Ӵ���
	childrenRoute=1;        
    for (i=1;i<crossoverPosition[0];i++)  //���������ǰ���뽻�������ͬ��Ԫ��
    {
		routeFlag=0;       //��0  
		for (j=crossoverPosition[0];j<crossoverPosition[0]+crossoverPosition[1];j++)
		{                                                                   //�����
			if (population[crossvoerIndividualA].routeInfo[i]==population[crossvoerIndividualB].routeInfo[j])   //������A�ν������ǰ�Ļ�����ͬ����ɾ�����������Ϊ��ȡ
			{
                routeFlag=1;   	//��־λ������ʼ��ǰ�Ļ����Ƿ��뽻����ڵ���ͬ����ͬΪ1��û����Ϊ0
			}
		}
		if (routeFlag!=1)     //�뽻����ڵĻ���ͬ������д���Ӵ�
		{
			population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualA].routeInfo[i];
			//�����������ǰ���뽻����ڲ�ͬ��Ԫ��д���Ӵ��У�
			childrenRoute++;   //ָ����һ��·������            
		}
    }
	for (i=crossoverPosition[0];i<crossoverPosition[0]+crossoverPosition[1];i++)     //��B�εĴ���д���Ӵ���
	{
		population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualB].routeInfo[i];  
		//��B�εĴ���д���Ӵ���
		childrenRoute++;
	}
	for (i=crossoverPosition[0];i<FACTORY_COUNT+1;i++)  //��������κ����뽻����ڲ���ͬ��Ԫ��
    {
		routeFlag=0;       //��0  
		for (j=crossoverPosition[0];j<crossoverPosition[0]+crossoverPosition[1];j++)
		{                                                                   //�����
			if (population[crossvoerIndividualA].routeInfo[i]==population[crossvoerIndividualB].routeInfo[j])
			{
				routeFlag=1;  //��־λ����ָʾ��ʼ���Ļ����Ƿ��뽻����ڵ���ͬ����ͬΪ1��û����Ϊ0
			}
		}
		if (routeFlag!=1)   //��ʼ���Ļ����Ƿ��뽻����ڵĲ���ͬ��д���Ӵ�
		{
			population[childrenNumber].routeInfo[childrenRoute]=population[crossvoerIndividualA].routeInfo[i];
			//�����������ǰ���뽻����ڲ�ͬ��Ԫ��д���Ӵ��У�
			childrenRoute++;   //ָ����һ��·������
		}
    }
}
void Generate_Crossover_Position_Function(int *crossoverPosition)    //�����������ʼ��ͳ���
{
    do {
		crossoverPosition[0]=rand()%FACTORY_COUNT+1;   //���������1~FACTORY_COUNT�������(FACTORY_COUNT=8)��Ϊ������ʼ��ַ
        crossoverPosition[1]=rand()%(FACTORY_COUNT-1)+1;   //���������1~(FACTORY_COUNT-1)�������(FACTORY_COUNT=8)��Ϊ����εĳ���              	
    } while(crossoverPosition[0]+crossoverPosition[1]>9);
    return ;
}