#include <iostream>
#include "KMeans.h"
#include <string>
using namespace std;

int main()
{
    string src_path = "xx.data"; //���������ļ�
    string output_path = "result.data"; //�������ļ�
    KMeans kmModel(src_path, output_path, 10); //��ʼ��keansģ��
    kmModel.Iteration(); //ģ�ͽ��е����Ż���������
    return 0;
}
