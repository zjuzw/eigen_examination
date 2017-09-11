#include <iostream>
#include "KMeans.h"
#include <string>
using namespace std;

int main()
{
    string src_path = "xx.data"; //输入数据文件
    string output_path = "result.data"; //输出结果文件
    KMeans kmModel(src_path, output_path, 10); //初始化keans模型
    kmModel.Iteration(); //模型进行迭代优化并输出结果
    return 0;
}
