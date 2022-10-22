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
    vector< vector<double> > trainSet = csvRead("/Users/somac/Desktop/train.csv") ;
    vector< vector<double> > testSet  = csvRead("/Users/somac/Desktop/train.csv") ;
    //注意读取的时候第一列的处理
    vector< vector<double> > train_X,train_Y;
    datasetProcess(trainSet,train_X,train_Y);
    trainSet_Info trainData = get_stdData(train_X);
    svm_problem problem = problemGenerate(trainData.data,train_Y);
    svm_parameter param = paramInit();
    svm_model* model = new svm_model ;
    if(svm_check_parameter(&problem, &param)== nullptr) model = svm_train(&problem, &param);
    else cout << "参数设置错误" << endl ;

    vector< vector<double> > test_X,test_Y;
    datasetProcess(testSet,test_X,test_Y);

    int testNum = test_X.size();
    int attributeNum = test_X[0].size();
    test_X= data_scale(test_X,trainData.mean,trainData.std) ;
        for(int i = 0 ; i < testNum ; i ++){
            svm_node* testList = sampleLinkList(test_X[i]);
            double resultLabel = svm_predict(model,testList);
            cout << resultLabel<< " "<< test_Y[i][0] <<" " <<resultLabel -train_Y[i][0]<<endl ;
        }
    return 0 ;
}


