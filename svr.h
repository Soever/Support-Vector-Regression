#ifndef svr
#define svr

#include <vector>
#include "svm.h"

using namespace std;

struct data_info{
    vector< vector<double> > traindata;
    vector<double> mean ;
    vector<double> std ;
};

int getLong(string line) ;
vector<vector<double> > csvRead(string filename);
vector<vector<double> > csvRead2(string filename);
svm_node* sampleLinkList(int attributeNum,vector<double> trainsample);
svm_problem problemGenerate(vector< vector<double> > traindata_x,vector<vector<double> > traindata_y);
svm_parameter paramInit(int svm_type,int kernel_type,   int degree,   double gamma,
                        double coef0 ,double cache_size,double eps, double C,
                        double p  ,int shrinking  ,int probability);
void datasetProcess(vector< vector<double> > traindata ,vector< vector<double> > &c ,vector< vector<double> > &d);
data_info data_scale(vector< vector<double> > data);
vector< vector<double> >  data_scale_v(vector< vector<double> > data);

#endif