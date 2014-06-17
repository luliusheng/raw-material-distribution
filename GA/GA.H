# define INIT_POPULATION_NUM   200            //�����ʼ����Ⱥ������    800
# define GENERATION_NUM       8000              //�����������    1000
# define POPULATION_PARENT_NUM       100      //����ÿһ�����и��ơ����桢������״�����Ⱥ������
# define POPULATION_CHILDREN_NUM     100      //����ÿһ���ɽ��桢������״��������Ӵ�����Ⱥ������
                                              //POPULATION_CHILDREN_NUM=INIT_POPULATION_NUM-POPULATION_PARENT_NUM
                                              //������population��POPULATION_PARENT_NUM~INIT_POPULATION_NUM��Ⱥ������
# define FACTORY_COUNT        100             //�������ι�����
# define TRUCK_WIGHT          8               //���忨������Ϊ2��   100�趨Ϊ8T
# define FRICTION_RATIO      0.8               //   Ħ��ϵ��u=0.8

# define MUTATION_NUM         3              //����һ��Ⱦɫ���ϱ��������ȡֵ��Χ��0~MUTATION_NUM       50

struct factory                   //���幤���Ľṹ��
{
	double factoryX;                 //���ι�����X����
	double factoryY;                 //���ι�����Y����
	double factoryD;                 //���ι�����ԭ����������
};
struct route                  //����·����Ϣ�Ľṹ��
{
	int routeInfo[FACTORY_COUNT+2];                 //��Ⱥ����ÿ�ε�����·��,�����������ι������ص�ԭ������������
	double fittness;	                                //��Ӧ��	
};

void Rand_Route_Function(int *routeInfoC);               //���������·���ĺ���
void Init_Factory_Information_Function(struct factory  *factoryInfo);    //��ʼ��������Ϣ
double Fittness_Function(struct factory *factoryInfo,int *routeInfo);   //������Ӧ��
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //��������������ι�����ԭ�����������ĵľ���
void Init_Population_Function(struct route  *population,struct factory *factoryInfo);   //��ʼ����Ⱥ����
void Evaluate_Population_Function(struct route *population,struct factory *factoryInfo);       //������Ⱥ
void Crossover_Function(struct route *population);     //��Ⱥ���彻�棬�����µ��Ӵ�
void Generate_Crossover_Position_Function(int *crossoverPosition);    //�����������ʼ��ͳ���
int Generate_Crossover_Individual_Function(void);       //��������ĸ���
void Generate_Children_Function(int crossvoerIndividualA,int crossvoerIndividualB,int *crossoverPosition,struct route *population,int childrenNumber);   //�����Ӵ�
void Mutation_Function(struct route *population);    //���Ӵ����б������

