#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ACO.h"

void Choose_Route_Function(struct ant *antInfo,double (*distance)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],struct factory *factoryInfo,double *searchChooseConst)
{           //̽����������ȷ����������ѡ��·���ĺ���
	int i,j,k,m;
	int choosePoint,quitFlag,flag,choosePointFalg; //ѡ���    ��  �˳���־��ѡ���־  ѡ����־
	int tabuNumber; //���ɵ�����
	double probalityTable[FACTORY_COUNT+1][FACTORY_COUNT+1]={0.0}; //����һ�������Ա�
	double chooseProbality;  //ѡ�����ȷ����������̽�����������������    
	Calculate_Probality_Function(probalityTable,pheromone,distance,factoryInfo);  //���ɸ���·����Ϣ��              	
	m=0;
       while (m<ANT_COUNT)
       {
		tabuNumber=1;
		for (i=0;i<FACTORY_COUNT;i++)
		{
			chooseProbality=((double)(rand()%10000+1))/10000; //�����������  
			if (chooseProbality<(*searchChooseConst)||tabuNumber==FACTORY_COUNT)  //����ȷ��������
			{				
				choosePoint=1;			//�ҳ��������ĵ�					
				flag=0;
				while (!flag)               //ȷ�������ֵ�һ���������
				{
					choosePointFalg=0;
				    for (k=1;k<=i;k++)    //��������
					{
						if (antInfo[m].tabuRoute[k]==choosePoint)   //���choosePoint���Ѿ�ѡ���ĵ��Ӧ��ȥ��
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
				for (j=1;j<FACTORY_COUNT+1;j++)      //���ʵ�ֵѡ�����
				{
					
					if(probalityTable[antInfo[m].tabuRoute[i]][choosePoint]<probalityTable[antInfo[m].tabuRoute[i]][j]) 
					{
						for (k=1;k<=i;k++)    //��������
						{
							if (antInfo[m].tabuRoute[k]==j)
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
				antInfo[m].tabuRoute[tabuNumber]=choosePoint; 	
				tabuNumber++;			
			}
			else             //����̽��������
			{
				quitFlag=0;
				while (!quitFlag)
				{
					choosePoint=rand()%FACTORY_COUNT+1;     //���ѡ��һ����					
					flag=0;
					for (j=1;j<=i;j++)      //ѡ�������ʵ�ֵ
					{
						if (antInfo[m].tabuRoute[j]==choosePoint)
						{ 
							flag=1;  //flag=1��ʾ��j�Ѿ���ѡ��
							break;    //��ʾ�˳���ǰѭ��
						}
					}
					if (flag!=1)     //���������ɱ��е���ͬ
					{
						antInfo[m].tabuRoute[tabuNumber]=choosePoint;
						tabuNumber++;
						quitFlag=1;
					}
				}			
			}	
		}
		m++;
    }	
	return ;
}
double Calculate_Vision_Function(int startPoint,int endPoint,double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo) //����ɼ���
{
	double result;
	result=(factoryInfo[endPoint].factoryD+TRUCK_WIGHT)/distance[startPoint][endPoint];//�ɼ��ȣ�����Խ�ؿɼ���Խ��
	return result;
}
void Calculate_Probality_Function(double (*probalityTable)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo)                  
{                 //����ȷ����·��ѡ��ʱ�Ŀ�����
	int i,j;
	for (i=0;i<FACTORY_COUNT+1;i++)
	{
		for (j=0;j<FACTORY_COUNT+1;j++)
		{
			if (i!=j)    //i��j��ͬ��ʾһ���㣬����ʾ��
			{
				probalityTable[i][j]=pow(pheromone[i][j],ALPHA)*pow(Calculate_Vision_Function(i,j ,distance,factoryInfo),BETA);  //������ʱ� 
			}			
		}
	}

}

