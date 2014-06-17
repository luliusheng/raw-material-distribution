/****************************************************************
��ģ�Ͳ�ȡ��Ϣ�ؾֲ����·�ʽ��Ϊ����ģ�ͣ��������Լ����߹��ı�����
�ŵ���Ϣ���������߹��ߵĳ��ȵĵ���
****************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"
void main()
{
	int i,j,interationCount=0;  //�����������ָ�겢��ʼ��Ϊ0
        int robustness=0;   //�����ж��Ƿ�Ҫ��С��Ϣ�ش��ݲ���rou��ȷ������������̽��������q0��ֵ
	int stopFlag=0;    //�㷨ֹͣ��־
	int pheromoneRoute[FACTORY_COUNT+2]={0};   //������Ϣ��Ũ������·������ʼ��Ϊ0
	double pheromoneBasedTotalWork;    //����Ϣ��ѡ���·�����ܹ�
	double pheromoneDeliverConst=ROU_MAX;   //��Ϣ�ش��ݲ���,��ʼ��Ϊ���ֵ
	double searchChooseConst=SEARCH_CHOOSE_MAX;   //̽���Է�ʽѡ�����,��ʼ��Ϊ���ֵ    
	double distance[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0};
        double pheromone[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0};	
	struct factory  factoryInfo[FACTORY_COUNT+1];         //����ÿ������������ԭ�����������ģ�����Ϣ	
	struct ant antInfo[ANT_COUNT];      //����������Ϣ�Ľṹ��,�����������ߵ�·����Ϣ
	
	Init_Factory_Information_Function(factoryInfo);      //��ʼ���������ι����Լ���Ӧ�̵�λ�ü�������Ϣ
        Init_Distance_Information_Function(factoryInfo,distance);  //��ʼ���������ι����Լ���Ӧ�̵ľ������
	Init_Pheromone_Information_Function(pheromone);  //��ʼ���������ι����Լ���Ӧ��֮�����Ϣ��Ũ�ȣ��޵�λ��Ϊ����ֵ
	Ant_Information_Function(antInfo);   //��ʼ��������Ϣ
       while ((stopFlag<CONSTRICTION_CONST)&&(interationCount<=INTERATION_COUNT))
       {
		interationCount++;
		Choose_Route_Function(antInfo,distance,pheromone,factoryInfo,&searchChooseConst);  //·��ѡ��ȷ����������̽��������			
	    Update_Pheromone_Function(factoryInfo,antInfo,pheromone,distance,&pheromoneDeliverConst);//����ÿһ��·���ϵ���Ϣ��		
		Based_Pheromone_Route_Function(pheromone,pheromoneRoute,&robustness);  //���������Ϣ�ص��������·����Ϣ
		Update_Row_Q_Function(&pheromoneDeliverConst,&searchChooseConst,&robustness,&stopFlag);  //������Ϣ�ش��ݲ���rou������ѡ��q0��ֵ�ĺ��� 	
       }
	pheromoneBasedTotalWork=Calculate_Total_Work_Function(factoryInfo,pheromoneRoute);     //�����������·����Ϣ�����ܹ�
	printf("//////ACO//////���ѡ��һ�����ϵ��ܹ�(��20��)/////////////////////////\n");
	for (i=0;i<20;i++)     //���ѡ��һ�����ϵ��ܹ������бȽ�
	{		
	    printf("�ܹ�[%d]:%f\n",i,antInfo[i].totalWork); //����i��j֮��ľ���
	}	
	printf("//////////ACO//������Ÿ���//////////////////////\n");
	printf("�ܹ�:%f\n",pheromoneBasedTotalWork); //����i��j֮��ľ���
	for (j=0;j<FACTORY_COUNT+2;j++)
	{
	    printf("basedPheromone%d:%d\n",j,pheromoneRoute[j]);  //���ܹ���С�����ϵ�·����Ϣ���
	}	
}
void Update_Row_Q_Function(double *pheromoneDeliverConst,double *searchChooseConst,int *robustness,int *stopFlag)  //������Ϣ�ش��ݲ���rou������ѡ��q0��ֵ�ĺ���
{
	if (*robustness==ROBUSTNESS)
	{
		*robustness=0;    //����
		(*pheromoneDeliverConst)*=ROU_CHANGE_RANGE;   //��Ϣ�ش��ݲ�������ROU_CHANGE_RANGE ����С 
		if (*pheromoneDeliverConst<=ROU_MIN)
		{
			*pheromoneDeliverConst=ROU_MIN; //ROU��������С��ȷ������		
		}		
        (*searchChooseConst)*=ROU_CHANGE_RANGE;       //̽����ʽ��������ROU_CHANGE_RANGE����С 
		if (*searchChooseConst<=SEARCH_CHOOSE_MIN)
		{
			*searchChooseConst=SEARCH_CHOOSE_MIN; //̽����ʽѡ�����q0��������С��ȷ������			
		}
	}
	if (*pheromoneDeliverConst==ROU_MIN)
	{
		(*stopFlag)++;
	}
	return ;
}
void Based_Pheromone_Route_Function(double (*pheromone)[FACTORY_COUNT+1],int *pheromoneRoute,int *robustness) 
{            //�ҳ���Ϣ��Ũ������·�������������ն����ߵ�·��
	int i,j,k;
	int choosePoint,flag,choosePointFalg,robustnessFlag; //ѡ���    ��  �˳���־��ѡ���־  ѡ����־ ,³���Լ���־
	int pheromoneRoutefront[FACTORY_COUNT+2];       //����װ��һ�εõ�����Ϣ�ص�·����Ϣ
	int tabuNumber; //���ɵ�����	 
	tabuNumber=1;
	robustnessFlag=0;
	for (i=0;i<FACTORY_COUNT+2;i++)
	{
	    pheromoneRoutefront[i]=pheromoneRoute[i]; 	   //�洢��һ�ε�·����Ϣ
	}
	for (i=0;i<FACTORY_COUNT;i++)
	{
		choosePoint=1;			//�ҳ��������ĵ�					
		flag=0;
		while (!flag)               //ȷ�������ֵ�һ���������
		{
			choosePointFalg=0;
			for (k=1;k<=i;k++)    //��������
			{
				if (pheromoneRoute[k]==choosePoint)   //���choosePoint���Ѿ�ѡ���ĵ��Ӧ��ȥ��
				{ 
					choosePointFalg=1;  
					break;    //��ʾ�˳���ǰѭ��
				}   //���ñ�ǣ�����������иü�¼��ȡ��ֵ							
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
		flag=0;  //��־λ��0				
		for (j=1;j<FACTORY_COUNT+1;j++)      //��Ϣ�ص�Ũ��ѡ�����
		{	
			if(pheromone[pheromoneRoute[i]][choosePoint]<pheromone[pheromoneRoute[i]][j]) 
			{
				for (k=1;k<=i;k++)    //��������
				{
					if (pheromoneRoute[k]==j)
					{ 
						flag=1;//���ñ�ǣ�����������иü�¼��ȡ��ֵ							
						break;    //��ʾ�˳���ǰѭ��  
					}   
				}
				if (flag!=1)   //���flag=0��ȡjֵ  ֵΪ1������
				{
					choosePoint=j; 							
				}					 
			}
			flag=0;  //��־λ��0
		}
		pheromoneRoute[tabuNumber]=choosePoint; 	
	    tabuNumber++;		
	}
    for (i=0;i<FACTORY_COUNT+1;i++)
    {  
		if (pheromoneRoute[i]-pheromoneRoutefront[i])     //���в�ͬ���ı䣩����ñ�־λ
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
