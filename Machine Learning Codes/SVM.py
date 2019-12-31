from sklearn import datasets
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
import numpy as np
from scipy.io import loadmat
import pandas as pd
from collections import Counter

# .............data Manipulation............ #

path = "E:/courses/Bs. Project/Classification/biopatrec-master/Dataset Features/"
def extract_table(path):
    x = [loadmat(path + 'user%s-%dth-ft.mat' % (5, 5))]
    # for i in range(1, 5):
    #     x.append(loadmat('user%s-%d.mat' % (i, 3)))

    # print(x["sigFeatures"]["trFeatures"][0, 0][0, 0]["tfd"][0, 0])
    #
    # #print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"])

    tmabs6 = []
    tmabs8 = []
    twl6 = []
    twl8 = []
    tzc6 = []
    tzc8 = []
    tslpch2_6 = []
    tslpch2_8 = []

    target = []
    # extracting each feature from .mat file

    for j in range(0, 5):
        for i in range(0, 48):
            #  print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"][i][0, 0])  # channel_6 48tr_windows
            tmabs6.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tmabs"][i][0][0])  # tmabs of channel 6
            tmabs8.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tmabs"][i][0][1])
            twl6.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["twl"][i][0][0])   # 1 channel
            twl8.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["twl"][i][0][1])   # 1 channel
            tzc6.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0][0])
            tzc8.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0][1])
            tslpch2_6.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tslpch2"][i][0][0])
            tslpch2_8.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tslpch2"][i][0][1])
            target.append(j)

    for j in range(0, 5):
        for i in range(0, 49):
            #  print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"][i][0, 0])  # channel_6 48tr_windows
            tmabs6.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tmabs"][i][0][0])  # tmabs of channel 6
            tmabs8.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tmabs"][i][0][1])  # tmabs of channel 8
            twl6.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["twl"][i][0][0])   # twl of channel 6
            twl8.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["twl"][i][0][1])   # twl of channel 8
            tzc6.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tzc"][i][0][0])
            tzc8.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tzc"][i][0][1])
            tslpch2_6.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tslpch2"][i][0][0])
            tslpch2_8.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tslpch2"][i][0][1])
            target.append(j)

    for j in range(0, 5):
        for i in range(0, 24):
            #  print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"][i][0, 0])  # channel_6 48tr_windows
            tmabs6.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tmabs"][i][0][0])  # tmabs of channel 6
            tmabs8.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tmabs"][i][0][1])  # tmabs of channel 8
            twl6.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["twl"][i][0][0])   # twl of channel 6
            twl8.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["twl"][i][0][1])   # twl of channel 8
            tzc6.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tzc"][i][0][0])
            tzc8.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tzc"][i][0][1])
            tslpch2_6.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tslpch2"][i][0][0])
            tslpch2_8.append(x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tslpch2"][i][0][1])
            target.append(j)

    tags = np.array(target)
    tmabs6 = np.array(tmabs6)
    twl6 = np.array(twl6)
    tzc6 = np.array(tzc6)
    tslpch2_6 = np.array(tslpch2_6)
    tmabs8 = np.array(tmabs8)
    twl8 = np.array(twl8)
    tzc8 = np.array(tzc8)
    tslpch2_8 = np.array(tslpch2_8)

    # print(twl.size)
    # print()
    print(tmabs6)
    print(tmabs8)
    # # number of each tag
    # print(dict(Counter(target)))
    print(tags)
    # print((x[0]["sigFeatures"]["trFeatures"][0, 0][:, 0]["tmabs"][0][0]))

    # X = tmabs
    # y = (tags == 2).astype(np.float64)
    # iris = datasets.load_iris()
    # print(x[0]["sigFeatures"]["trFeatures"][0, 0][:, 0]["tmabs"])
    # X = iris["data"][:, (2, 3)]  # petal length, petal width
    # y = (iris["target"] == 2).astype(np.float64)  # Iris-Virginica
    #print(iris)
    # svm_clf = Pipeline([("scaler", StandardScaler()), ("linear_svc", LinearSVC(C=1, loss="hinge")),])
    # svm_clf.fit(X, y)
    #print(svm_clf.predict(x[0]["sigFeatures"]["trFeatures"][0, 0][1, 1]["tmabs"][i][0, 0]))
    # boston = datasets.load_iris()
    # print(list(boston.keys()))
    # print(boston["data"][0, :])
    # print(boston["target"])
    #print(iris["data"][2, :])

    # emg = "adsbias.csv"
    # df = pd.read_csv(emg, sep=',', dtype=float)
    # print(df.ix[0, :])
extract_table(path)

