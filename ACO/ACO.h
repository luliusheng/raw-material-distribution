# define FACTORY_COUNT        100           //定义下游工厂数
# define TRUCK_WIGHT          8               //定义卡车重量为8吨
# define FRICTION_RATIO      0.8               //   摩察系数u=0.8
# define ALPHA    1    //信息素在概率计算中的权重，值越大，信息素在蚂蚁选择下一个所要到达的点的作用越大
# define BETA     2    //启发因子在概率计算中的权重，值越大，启发因子在蚂蚁选择下一个所要到达的点的作用越大 
# define ANT_COUNT     100    //定义蚂蚁数量800
# define CONSTRICTION_CONST    10    //计算结束前的收敛状况
# define PHEROMONE_ADD_CONST  8  //信息素传递参数的暂时值，以后会变Q值  
# define ROBUSTNESS   8    //信息素决定的路径连续未变化的最大次数，若达到该值，就修改rou和q0. 
 
# define SEARCH_CHOOSE_MAX   0.68    //确定性搜索和探索性搜索的选择范围的决定值的上限, 确保算法能够收敛
# define SEARCH_CHOOSE_MIN   0.1    ////确定性搜索和探索性搜索的选择范围的决定值的下限， 确保算法能够收敛  
# define ROU_MAX    0.68    //信息素传递参数的最大值， 避免算法陷入较差的局部最优
# define ROU_MIN    0.1    //信息素传递参数的最小值，防止衰减到0, 确保算法能够收敛
# define ROU_CHANGE_RANGE    0.9    //信息素传递参减小的幅度值，范围为0~1.
# define SEARCH_CHOOSE_RANGE    0.9   //确定性搜索和探索性搜索的选择范围的决定值减小的幅度值，范围为0~1.

# define INIT_PHEROMONE  0     //初始化信息素的浓度值，即每条边都都对应一个信息素的浓度值
# define INTERATION_COUNT  8000     //定义迭代次数，如果长时间没有收敛，则依据迭代次数退出

struct factory                   //定义工厂的结构体
{
	double factoryX;                 //下游工厂的X坐标	
	double factoryY;                 //下游工厂的Y坐标
	double factoryD;                 //下游工厂的原材料需求量
};
struct ant 
{
	int tabuRoute[FACTORY_COUNT+2];     //定义蚂蚁已经走过的点，当蚂蚁走完所有点回到配送中心后，就形成了一条路径,初始化为0
	double totalWork;   	           //一条路径上所作的总功   
};

void Init_Factory_Information_Function(struct factory *factoryInfo);   //初始化工厂信息 
void Init_Distance_Information_Function(struct factory  *factoryInfo,double (*distance)[FACTORY_COUNT+1]);  //初始化各个下游工厂以及供应商的距离矩阵
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //计算两个坐标点之间的距离
void Init_Pheromone_Information_Function(double (*pheromone)[FACTORY_COUNT+1]);  //初始化各条边上的信息素浓度
void Ant_Information_Function(struct ant *antInfo);   //初始化蚂蚁信息

void Update_Pheromone_Function(struct factory *factoryInfo,struct ant *antInfo,double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],double *pheromoneDeliverConst);  //更新每条路径上得信息素
double Calculate_Total_Work_Function(struct factory *factoryInfo,int *tabuRoute);     //计算总功
double Distance_Function(int source,int destence,struct factory  *factoryInfo);    //以坐标计算两下游工厂和原材料配送中心的距离

double Calculate_Vision_Function(int startPoint,int endPoint,double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo); //计算可见度
void Calculate_Probality_Function(double (*probalityTable)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],double (*distance)[FACTORY_COUNT+1],struct factory *factoryInfo);
              //计算确定性路径选择时的可能性
void Choose_Route_Function(struct ant *antInfo,double (*distance)[FACTORY_COUNT+1],double (*pheromone)[FACTORY_COUNT+1],struct factory *factoryInfo,double *searchChooseConst);
 //选择路径的函数
void Based_Pheromone_Route_Function(double (*pheromone)[FACTORY_COUNT+1],int *pheromoneRoute,int *robustness);        //找出信息素浓度最大的路径，即蚂蚁最终都会走的路径

void Update_Row_Q_Function(double *pheromoneDeliverConst,double *searchChooseConst,int *robustness,int *stopFlag); //更新信息素传递参数rou和搜索选择q0的值的函数
