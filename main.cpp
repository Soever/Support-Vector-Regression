#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "svr.cpp"

// 统计一行元素个数
using namespace std ;

int main(int, char**)
{
    vector< vector<double> > traindata = csvRead("/Users/somac/Desktop/train.csv") ;
    vector< vector<double> > testdata = csvRead("/Users/somac/Desktop/train.csv") ;
    // data_info  data = data_scale(traindata1); 
    // vector< vector<double> > traindata =data_scale_v(traindata1);
//    copy(data.traindata.begin(), data.traindata.end(), back_inserter(traindata));
    vector< vector<double> > c ,d;
    for(int i = 0 ; i < traindata.size();i++){
        vector<double> c1 ;
        vector<double> d1 ; 
        for(int j = 0 ; j < traindata[0].size(); j++){
            if(j == traindata[0].size()-1) d1.push_back(traindata[i][j]);
            else c1.push_back(traindata[i][j]);
            cout <<traindata[i][j] << " ";
        }
        cout << endl ;
        c.push_back(c1);
        d.push_back(d1);
    }
    svm_problem problem = problemGenerate(c,d);
    svm_parameter param = paramInit();
    svm_model* model = new svm_model ;
    if(svm_check_parameter(&problem, &param)== nullptr) model = svm_train(&problem, &param);
    else cout << "参数设置错误" << endl ;
    int testNum = c.size();
    int attributeNum = c[0].size();
    for(int i = 0 ; i < testNum ; i ++){
        svm_node* testList = sampleLinkList(attributeNum,c[i]);
        double resultLabel = svm_predict(model,testList);
        cout << resultLabel<< "  "<< d[i][0] <<"    " <<resultLabel -d[i][0]<<endl ;
    }
    return 0 ;
}


