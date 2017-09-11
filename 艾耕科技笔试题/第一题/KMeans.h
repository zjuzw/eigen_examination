#ifndef KMEANS_H
#define KMEANS_H

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

typedef float DATA_TYPE;
const float INF = 1e20;
const int MAXC = 100;//�����ĸ���


//��ž����ÿ���ص���Ϣ�������������ĺ����ڸôص���������
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
        // ���������ݴ���
        void Transfer(int key, vector<DATA_TYPE> value); //��������
        void Recieve(vector<int> &keys, vector<vector<DATA_TYPE> >&values);//��������
        //������
        void OutputResult();
    private:

        DATA_TYPE **m_points; //�洢��������
        int m_cluster_num; //��������
        int m_max_iter; //����������
        int m_cur_iter; //��ǰ��������
        float m_eps; //Ԥ�������ε���������ֵ�������ж��Ƿ�����
        float m_cur_eps; //����õ���ǰ���������
        int m_point_num; //��������
        int m_point_dimention; //����ά��
        Cluster m_clusters[MAXC]; //������������

        string m_src_path; //��������·��
        string m_output_path;
        ifstream fcin;//
        ofstream fcout;
};

#endif // KMEANS_H
