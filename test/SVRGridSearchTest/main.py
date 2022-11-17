
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split 
from sklearn.svm import SVR
from sklearn.metrics import r2_score
from sklearn import preprocessing
from sklearn.model_selection import GridSearchCV
def openreadtxt(file_name):
    data = []
    file = open(file_name,'r')  #打开文件
    file_data = file.readlines() #读取所有行
    for row in file_data:
        tmp_list = row.split(',') #按‘，’切分每行的数据
        data_list = []
        tmp_list[-1] = tmp_list[-1].replace('\n','') #去掉换行符
        for str in tmp_list:
            data_list.append(float(str)) #将每行数据插入data中
        data.append(data_list)
    return data
zscore_scaler=preprocessing.StandardScaler()


if __name__ == '__main__' :
    f = openreadtxt("/Users/somac/Downloads/data05.csv")
    f = np.array(f)
    np.random.seed(0)
    train_scale_x =zscore_scaler.fit_transform(f[:200,:-1])
    x_tran,x_test,y_train,y_test = train_test_split(train_scale_x, f[:200,-1], test_size=0.25)
    parameters = {'gamma': [0.001, 0.01, 0.1, 1], 'C':[0.001, 0.01, 0.1, 1,10,50,100]}
    gs = GridSearchCV(SVR(), parameters, refit = True, cv = 5, verbose = 1, n_jobs = 1)
    gs.fit(x_tran, y_train)
    y_hat = gs.predict(x_test)

    r = len(x_test) + 1
    plt.plot(np.arange(1,r), y_hat,  label="predict")
    plt.plot(np.arange(1,r), y_test, label="real")

    plt.legend()
    print('最优参数: ',gs.best_params_)
    print('最佳性能: ', gs.best_score_)
    plt.show()