# define INIT_POPULATION_NUM   200            //定义初始化种群个体数    800
# define GENERATION_NUM       8000              //定义进化代数    1000
# define POPULATION_PARENT_NUM       100      //定义每一代进行复制、交叉、变异的亲代的种群个体数
# define POPULATION_CHILDREN_NUM     100      //定义每一代由交叉、变异的亲代产生的子代的种群个体数
                                              //POPULATION_CHILDREN_NUM=INIT_POPULATION_NUM-POPULATION_PARENT_NUM
                                              //储存在population的POPULATION_PARENT_NUM~INIT_POPULATION_NUM种群个体中
# define FACTORY_COUNT        100             //定义下游工厂数
# define TRUCK_WIGHT          8               //定义卡车重量为2吨   100设定为8T
# define FRICTION_RATIO      0.8               //   摩察系数u=0.8

# define MUTATION_NUM         3              //定义一条染色体上变异次数的取值范围：0~MUTATION_NUM       50

struct factory                   //定义工厂的结构体
{
	double factoryX;                 //下游工厂的X坐标
	double factoryY;                 //下游工厂的Y坐标
	double factoryD;                 //下游工厂的原材料需求量
};
struct route                  //定义路径信息的结构体
{
	int routeInfo[FACTORY_COUNT+2];                 //种群个体每次的行走路径,遍历所有下游工厂并回到原材料配送中心
	double fittness;	                                //适应度	
};

void Rand_Route_Function(int *routeInfoC);               //生成随机的路径的函数
void Init_Factory_Information_Function(struct factory  *factoryInfo);    //初始化工厂信息
double Fittness_Function(struct factory *factoryInfo,int *routeInfo);   //计算适应度
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //以坐标计算两下游工厂和原材料配送中心的距离
void Init_Population_Function(struct route  *population,struct factory *factoryInfo);   //初始化种群个体
void Evaluate_Population_Function(struct route *population,struct factory *factoryInfo);       //评估种群
void Crossover_Function(struct route *population);     //种群个体交叉，产生新的子代
void Generate_Crossover_Position_Function(int *crossoverPosition);    //长生交叉的起始点和长度
int Generate_Crossover_Individual_Function(void);       //产生交叉的个体
void Generate_Children_Function(int crossvoerIndividualA,int crossvoerIndividualB,int *crossoverPosition,struct route *population,int childrenNumber);   //生成子代
void Mutation_Function(struct route *population);    //对子代进行变异操作


