#ifndef svr
#define svr

#include <vector>
#include "svm.h"

using namespace std;

struct trainSet_Info{
    vector< vector<double> > data;
    vector<double> mean ;
    vector<double> std ;
};

int getLong(string line) ;
vector<vector<double> > csvRead(string filename);
vector<vector<double> > csvRead2(string filename);
svm_node* sampleLinkList(vector<double> trainsample);
svm_problem problemGenerate(vector< vector<double> > traindata_x,vector<vector<double> > traindata_y);
svm_parameter paramInit(int svm_type,int kernel_type,   int degree,   double gamma,
                        double coef0 ,double cache_size,double eps, double C,
                        double p  ,int shrinking  ,int probability);
void datasetProcess(vector< vector<double> > traindata ,vector< vector<double> > &c ,vector< vector<double> > &d);
trainSet_Info get_stdData(vector< vector<double> > data);
vector< vector<double> > data_scale(vector< vector<double> > data,vector<double>mean ,vector<double>std) ;


#endif