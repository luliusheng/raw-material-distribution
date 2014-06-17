# define FACTORY_COUNT        100           //�������ι�����
# define TRUCK_WIGHT          8               //���忨������Ϊ8��
# define FRICTION_RATIO      0.8               //   Ħ��ϵ��u=0.8
# define ALPHA    1    //��Ϣ���ڸ��ʼ����е�Ȩ�أ�ֵԽ����Ϣ��������ѡ����һ����Ҫ����ĵ������Խ��
# define BETA     2    //���������ڸ��ʼ����е�Ȩ�أ�ֵԽ����������������ѡ����һ����Ҫ����ĵ������Խ�� 
# define ANT_COUNT     100    //������������800
# define CONSTRICTION_CONST    10    //�������ǰ������״��
# define PHEROMONE_ADD_CONST  8  //��Ϣ�ش��ݲ�������ʱֵ���Ժ���Qֵ  
# define ROBUSTNESS   8    //��Ϣ�ؾ�����·������δ�仯�������������ﵽ��ֵ�����޸�rou��q0. 
 
# define SEARCH_CHOOSE_MAX   0.68    //ȷ����������̽����������ѡ��Χ�ľ���ֵ������, ȷ���㷨�ܹ�����
# define SEARCH_CHOOSE_MIN   0.1    ////ȷ����������̽����������ѡ��Χ�ľ���ֵ�����ޣ� ȷ���㷨�ܹ�����  
# define ROU_MAX    0.68    //��Ϣ�ش��ݲ��������ֵ�� �����㷨����ϲ�ľֲ�����
# define ROU_MIN    0.1    //��Ϣ�ش��ݲ�������Сֵ����ֹ˥����0, ȷ���㷨�ܹ�����
# define ROU_CHANGE_RANGE    0.9    //��Ϣ�ش��ݲμ�С�ķ���ֵ����ΧΪ0~1.
# define SEARCH_CHOOSE_RANGE    0.9   //ȷ����������̽����������ѡ��Χ�ľ���ֵ��С�ķ���ֵ����ΧΪ0~1.

# define INIT_PHEROMONE  0     //��ʼ����Ϣ�ص�Ũ��ֵ����ÿ���߶�����Ӧһ����Ϣ�ص�Ũ��ֵ
# define INTERATION_COUNT  8000     //������������������ʱ��û�������������ݵ��������˳�

struct factory                   //���幤���Ľṹ��
{
	double factoryX;                 //���ι�����X����	
	double factoryY;                 //���ι�����Y����
	double factoryD;                 //���ι�����ԭ����������
};
struct ant 
{
	int tabuRoute[FACTORY_COUNT+2];     //���������Ѿ��߹��ĵ㣬�������������е�ص��������ĺ󣬾��γ���һ��·��,��ʼ��Ϊ0
	double totalWork;   	           //һ��·�����������ܹ�   
};

void Init_Factory_Information_Function(struct factory *factoryInfo);   //��ʼ��������Ϣ 
void Init_Distance_Information_Function(struct factory  *factoryInfo,double (*distance)[FACTORY_COUNT+1]);  //��ʼ���������ι����Լ���Ӧ�̵ľ������
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //�������������֮��ľ���
void Init_Pheromone_Information_Function(double (*pheromone)[FACTORY_COUNT+1]);  //��ʼ���������ϵ���Ϣ��Ũ��
void Ant_Information_Function(struct ant *antInfo);   //��ʼ��������Ϣ

void Update_Pheromone_Function(struct factory *factoryInfo,struct ant *antInfo,double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],double *pheromoneDeliverConst);  //����ÿ��·���ϵ���Ϣ��
double Calculate_Total_Work_Function(struct factory *factoryInfo,int *tabuRoute);     //�����ܹ�
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //��������������ι�����ԭ�����������ĵľ���

double Calculate_Vision_Function(int startPoint,int endPoint,double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo); //����ɼ���
void Calculate_Probality_Function(double (*probalityTable)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo);
              //����ȷ����·��ѡ��ʱ�Ŀ�����
void Choose_Route_Function(struct ant *antInfo,double (*distance)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],struct factory *factoryInfo,double *searchChooseConst);
 //ѡ��·���ĺ���
void Based_Pheromone_Route_Function(double (*pheromone)[FACTORY_COUNT+1],int *pheromoneRoute,int *robustness);        //�ҳ���Ϣ��Ũ������·�������������ն����ߵ�·��

void Update_Row_Q_Function(double *pheromoneDeliverConst,double *searchChooseConst,int *robustness,int *stopFlag); //������Ϣ�ش��ݲ���rou������ѡ��q0��ֵ�ĺ���
