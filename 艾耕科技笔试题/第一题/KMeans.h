#ifndef KMEANS_H
#define KMEANS_H

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

typedef float DATA_TYPE;
const float INF = 1e20;
const int MAXC = 100;//最大类的个数


//存放聚类后每个簇的信息，包括聚类中心和属于该簇的样本索引
struct Cluster {
    vector<DATA_TYPE> center;
    vector<int> member;
};

class KMeans
{
    public:
        KMeans(string src_path, string output_path, int cluster_num, int max_iter=100, float eps=1e-3);
        virtual ~KMeans();
        void Init();
        void Iteration();
        void Mapper();
        void Reducer();
        // 机器间数据传输
        void Transfer(int key, vector<DATA_TYPE> value); //发送数据
        void Recieve(vector<int> &keys, vector<vector<DATA_TYPE> >&values);//接收数据
        //输出结果
        void OutputResult();
    private:

        DATA_TYPE **m_points; //存储所有样本
        int m_cluster_num; //聚类数量
        int m_max_iter; //最大迭代数量
        int m_cur_iter; //当前迭代次数
        float m_eps; //预定义两次迭代误差的阈值，用来判断是否收敛
        float m_cur_eps; //计算得到当前迭代的误差
        int m_point_num; //样本数量
        int m_point_dimention; //样本维度
        Cluster m_clusters[MAXC]; //聚类后类别数据

        string m_src_path; //数据输入路径
        string m_output_path;
        ifstream fcin;//
        ofstream fcout;
};

#endif // KMEANS_H
