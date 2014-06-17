#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GA.H"

double Fittness_Function(struct factory *factoryInfo,int *routeInfo)     //������Ӧ��
{
	int i,externd;                                              //externd����ı�ʶ
	double distance[FACTORY_COUNT+1]={0.0},result=0.0;         //��ʼ������Ϊ0
	distance[0]=Distance_Function(0,routeInfo[1],factoryInfo);   //�ȼ�������������ĵ����һ�����ι����ľ��룬��Ϊ������ӵĻ���
	for (externd=1;externd<FACTORY_COUNT+1;externd++)
	{    
		distance[routeInfo[externd]]=distance[routeInfo[externd-1]]+Distance_Function(routeInfo[externd-1],routeInfo[externd],factoryInfo);   
	}                                 //ͨ�����ӵķ�ʽ��������������������ι����ľ���
	for (i=0;i<FACTORY_COUNT;i++)
	{	
		result+=distance[routeInfo[i]]*(factoryInfo[routeInfo[i+1]].factoryD);	//ȫ�̵Ĺ�Ϊ������Ĺ����ܺ�		
	}
	result=result+distance[routeInfo[i]]*TRUCK_WIGHT;   //�������ι����ľ���������ĳ˻�+����ʱ�������нڵ������Ĺ�
	return ((1/result)*1000000); //����Ӧ������100�򱶣����ڱȽϣ�������Ӧ�ȣ���Ӧ��Ϊȫ���������ܹ��ĵ����������ܹ�Խ�٣���Ӧ��Խ��ֵԽ��
}
double Distance_Function(int source,int destence,struct factory  *factoryInfo)    //��������������ι�����ԭ�����������ĵľ���
{	
	double result;
	result=sqrt(pow((factoryInfo[destence].factoryX-factoryInfo[source].factoryX),2)+pow((factoryInfo[destence].factoryY-factoryInfo[source].factoryY),2)); 
	//��������֮��ľ��� 
	return result;  //��������֮��ľ���
}
void Rand_Route_Function(int *routeInfoC)               //���������·���ĺ���
{	
	int i,j,k,flag=0;
	int randNum[FACTORY_COUNT+2]={0};	//��randNum[j]����ֵ0    
	for (j=1;j<FACTORY_COUNT+1;j++)
    {
		k=rand()%FACTORY_COUNT+1;		   //����1��FACTORY_COUNT�������
		flag=0;                    //���ñ�־λ���ж�randNum��ֵ�Ƿ��ȡ
		for (i=0;i<j;i++)      
		{
			if (k==randNum[i])    //ȷ��randNum[j]��ֵΨһ
			{
				i=j;   
				j--;             //��ʾ��ǰֵ��ȡ
				flag=1;				
			}			
		}
		if(flag==0)		     //��ʾ��ȡ��ֵ����Ҫ�󣬲���ֵ����randNum[j]
		{
			randNum[j]=k;			
		}
		
    }
	for (i=0;i<FACTORY_COUNT+2;i++)
	{
		routeInfoC[i]=randNum[i];       //��ʼ��һ����Ⱥ·����Ϣ
	}	
	return ;
}














