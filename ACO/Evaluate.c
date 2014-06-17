#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"

void Evaluate_Ant_Route_Function(struct ant *antInfo,struct factory *factoryInfo)       //�������ϵ�·���������ܹ��Ͱ��ܹ�����Ľ��
{
	int i,j,k,routeChange;                    //routeChange����·����Ϣ���м���� 
	double totalWorkChange;                    //�����ܹ����м����  
	for (j=0;j<ANT_COUNT;j++)
	{
		antInfo[j].totalWork=Calculate_Total_Work_Function(factoryInfo,antInfo[j].tabuRoute);	//������Ⱥ����j���ܹ�
	}
	for (i=0;i<ANT_COUNT-1;i++)      
	{
		for (j=i+1;j<ANT_COUNT;j++)
		{
			if (antInfo[i].totalWork>antInfo[j].totalWork)      // ���ܹ���С��С��������
			{
				totalWorkChange=antInfo[i].totalWork;          // �����ܹ�	
				antInfo[i].totalWork=antInfo[j].totalWork;
				antInfo[j].totalWork=totalWorkChange;
                for (k=0;k<FACTORY_COUNT+2;k++)
                {
					routeChange=antInfo[i].tabuRoute[k];			  // ����·����Ϣ	
					antInfo[i].tabuRoute[k]=antInfo[j].tabuRoute[k];
					antInfo[j].tabuRoute[k]=routeChange;
                }				
			}			
		}
		
	}
}

