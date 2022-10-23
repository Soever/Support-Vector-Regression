#include "svr.h"
#include "svm.cpp"
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

int getLong(string line) {
    int numsize = 0;
    int s = line.size();
    for (int a = 0 ; a < s;a++)
        if (line[a] == ',') numsize++;
    return numsize + 1;
}
 
vector<vector<double> > csvRead(string filename){
	vector<vector<double> > result;
	ifstream infile(filename, ios::in);
	string line;
	getline(infile, line);
	int sizex = getLong(line);
	while (getline(infile, line)) {
		stringstream ss(line);
		string str;
		vector<double> lineReader;
		for (int i = 0; i < sizex; i++) {
			getline(ss, str, ',');
		    lineReader.push_back(stod(str));
		}
		result.push_back(lineReader);
	}
	return result;
}

vector<vector<double> > csvRead2(string filename){
	vector<vector<double> > result;
	ifstream infile(filename, ios::in);
	string line;
	getline(infile, line);
	int sizex = getLong(line);
	while (getline(infile, line)) {
		stringstream ss(line);
		string str;
		vector<double> lineReader;
		for (int i = 0; i < sizex; i++) {
			getline(ss, str, ',');
			if(i) lineReader.push_back(stod(str));
		}
		result.push_back(lineReader);
	}
	return result;
}
svm_node* sampleLinkList(vector<double> trainSample)
{
    int attributeNum  = trainSample.size();
    svm_node* nod=new svm_node[attributeNum+1];
    for(int j = 0 ; j < attributeNum ; j++){
        nod[j].index=j+1;
        nod[j].value=trainSample[j];
    }
    nod[attributeNum].index = -1;
    return nod;
}

svm_problem problemGenerate(vector< vector<double> > traindata_x,vector<vector<double> > traindata_y){
    int sampleNum = traindata_x.size() ;
    int labelNum = traindata_y.size();
    int attributeNum = traindata_x[0].size();
    double y_singel_label[labelNum];
    svm_problem softsensor_problem;
    for(int i = 0 ; i <labelNum;i++)
        y_singel_label[i] = traindata_y[i][0] ;
    softsensor_problem.l = labelNum   ;
    softsensor_problem.x = new svm_node*[sampleNum]  ;
    softsensor_problem.y = new double[sampleNum]  ;
    for(int i = 0 ; i < labelNum ; i++){
        softsensor_problem.x[i] = sampleLinkList(traindata_x[i]);
        for(int j = 0 ; j < labelNum ; j++)
            softsensor_problem.y[i] = y_singel_label[i];
    }
    return softsensor_problem;
}

svm_parameter paramInit(int svm_type=3 ,int kernel_type=2,   int degree=0,   double gamma=0.01,
                        double coef0=0 ,double cache_size=10,double eps=0.001, double C=10,
                        double p = 0.1 ,int shrinking = 0,   int probability=0)
{
    svm_parameter param;
    param.svm_type=svm_type;
    param.kernel_type=kernel_type;
    param.degree=degree;
    param.gamma=gamma;
    param.coef0=coef0;
    param.cache_size=cache_size;
    param.eps=eps;
    param.C=C;
    param.nr_weight=0;
    param.weight_label=nullptr;
    param.weight=nullptr;
    param.nu=0;
    param.p=p;
    param.shrinking=shrinking;
    param.probability=probability;
    return param;
}

//如果数据集训练集和标签集
void datasetProcess(vector< vector<double> > traindata ,vector< vector<double> > &c ,vector< vector<double> > &d)
{
    int sampleNum = traindata.size() ;
    int attriNum ;
    if(sampleNum) attriNum = traindata[0].size() ;
    for(int i = 0 ; i < sampleNum;i++){
        vector<double> c1 ;
        vector<double> d1 ; 
        for(int j = 0 ; j < attriNum; j++){
            if(j == attriNum-1) d1.push_back(traindata[i][j]);
            else c1.push_back(traindata[i][j]);
        }
        c.push_back(c1);
        d.push_back(d1);
    }
}

trainSet_Info get_stdData(vector< vector<double> > data)
{
    trainSet_Info info  ;
    int n = data.size();
    int m =0 ;
    if(n) m = data[0].size();
    for(int i = 0 ; i < m ; i++)
    {
        double mean = 0;
        double std = 0 ;
        for(int j = 0; j < n;j++) mean += data[j][i];
        mean = mean/n;
        info.mean.push_back(mean);
        for(int j = 0; j < n;j++)
        {
            double diff =data[j][i] - mean ;
            std += pow(diff,2) ;
        }
        std = std/(n-1) ;
        std = pow(std,0.5);
        info.std.push_back(std); 
    }
    data = data_scale(data,info.mean,info.std);
    copy(data.begin(), data.end(), back_inserter(info.data));
    return info ;
}
vector< vector<double> >  data_scale(vector< vector<double> > data,vector<double>mean ,vector<double>std) 
{
    int n = data.size();
    int m =0 ;
    if(n) m = data[0].size();
    for(int i = 0 ; i < m ; i++)
        for(int j = 0; j < n ; j++)
            data[j][i] =(data[j][i] - mean[i])/std[i];
    return data;
}