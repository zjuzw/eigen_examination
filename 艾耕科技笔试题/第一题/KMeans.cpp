#include "KMeans.h"

//初始化变量
KMeans::KMeans(string src_path, string output_path, int cluster_num, int max_iter=100, float eps=1e-3);
{
    m_src_path = src_path;
    m_output_path = output_path;
    m_cluster_num = cluster_num;
    m_max_iter = max_iter;
    m_eps = eps;
    m_cur_iter = 0;
    m_cur_eps = INF;
    Init();
}

//释放申请的内存
KMeans::~KMeans()
{
    for(int i=0;i<m_point_num;++i) {
        delete[] m_points[i];
    }
    delete[] m_points;
}

//进行迭代操作
KMeans::Iteration() {
    //达到最大迭代次数或者两次迭代的聚类中心基本没有差异时退出循环
    while(m_cur_iter<max_iter && m_cur_eps>eps) {
        m_cur_iter++;
        Mapper();
        Reducer();
    }
    OutputResult();
}

KMeans::Init()
{
    //重定向cin, 把文件中的数据读到数组中
    fcin(m_src_path);
    fcout(m_output_path);
    fcin >> m_point_num >> m_point_dimention;
    m_points = new DATA_TYPE*[m_point_num];
    for(int i=0;i<m_point_num;++i) {
        m_points[i] = new DATA_TYPE[m_point_dimention];
        for(int j=0;j<m_point_dimention;++j) {
            fcin >> m_points[i][j];
        }
    }

    //机器间通信获取聚类中心数据
    UpdateCluster();

}

//更新聚类中心以及计算两次聚类中心的误差
KMeans::UpdateCluster() {
    vector<int> keys;
    vector<vector<float> > values;
    Recieve(keys, values);
    //计算两次聚类中心的误差
    if(m_cur_iter>1) {
        m_cur_eps = 0.0f;
        for(int k=0;k<keys.size();++k) {
            for(int j=0;j<m_point_dimention;++j) {
                m_cur_eps += abs(m_clusters[keys[k]].center[j]-values[k][j]);
            }
        }
    }
    //更新聚类中心
    for(int k=0;k<keys.size();++k) {
        m_clusters[keys[k]].member.clear();
        m_clusters[keys[k]].center.assign(values[k].begin(), values[k].end());
    }
}

//计算样本点到某个聚类中心的距离
KMeans::GetDistance(int point_idx, int cluster_idx) {
    float dis = 0.0f;
    for(int i=0;i<m_point_dimention;++i) {
        dis += (m_points[point_idx][j]-m_clusters[cluster_idx].center[j])*(m_points[point_idx][j]-m_clusters[cluster_idx].center[j]);
    }
    return dis;

}

//计算与样本点距离最近的聚类中心
KMeans::Mapper() {

    float small_dis = INF;
    int nearest_cluster_idx;
    for(int i=0;i<m_point_num;++i) {
        for(int k=0;k<m_cluster_num;++k) {
            float dis = GetDistance(i, k);
            if(dis<small_dis) {
                nearest_cluster_idx = k;
                small_dis = dis;
            }
        }
        m_clusters[nearest_cluster_idx].member.push_back(i);
    }
}

//根据聚类中心对样本点进行简单的归并计算
KMeans::Reducer() {
    for(int k=0;k<m_cluster_num;++k) {
        vector<float> f_data(m_point_dimention+1, 0.0f);
        f_data[0] = m_clusters[k].member.size();//第一维存放所属类别的样本数量
        for(int i=1;i<m_point_dimention+1;++i) {
            for(int j=0;j<m_clusters[k].member.size();++j) {
                f_data[i] += m_points[m_clusters[k].member[j]][i];
            }
            f_data[i] /= m_clusters[k].member.size();
        }
        Transfer(k, f_data);
    }
}

// 机器间数据传输：发送数据
KMeans::Transfer(int key, vector<float> value) {

}
// 机器间数据传输：接收数据
KMeans::Recieve(vector<int> &keys, vector<vector<float> >&values) {

}

//输出结果
KMeans::OutputResult() {
    fcout << m_point_num << m_point_dimention << endl;
    for(int k=0;k<m_cluster_num;++k) {
        for(int j=0;j<m_clusters[k].member.size();++j) {
            for(int i=0;i<m_point_dimention-1;++i) {
                fcout << m_points[m_clusters[k].member[j]][i] << ' ';
            }
            fcout << m_points[m_clusters[k].member[j]][m_point_dimention-1] << endl;
        }
    }
}
