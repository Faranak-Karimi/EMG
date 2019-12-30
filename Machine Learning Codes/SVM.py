from sklearn import datasets
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
import numpy as np
from scipy.io import loadmat
import pandas as pd
from collections import Counter

# .............data Manipulation............ #
x = [loadmat('user%s-%dth-ft.mat' % (5, 5))]
for i in range(1, 5):
    x.append(loadmat('user%s-%d.mat' % (i, 3)))

# print(x["sigFeatures"]["trFeatures"][0, 0][0, 0]["tfd"][0, 0])
#
# #print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"])

tmabs = []
twl = []
tzc = []
tslpch2 = []
target = []
# extracting each feature from .mat file

for j in range(0, 5):
    for i in range(0, 48):
        #  print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"][i][0, 0])  # channel_6 48tr_windows
        tmabs.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tmabs"][i][0, 0])  # 2 channels
        twl.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["twl"][i][0, 0])   # 1 channel
        tzc.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0, 0])
        tslpch2.append(x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tslpch2"][i][0, 0])
        target.append(j)

for j in range(0, 5):
    for i in range(0, 48):
        #  print(x["sigFeatures"]["trFeatures"][0, 0][:, 0]["tfd"][i][0, 0])  # channel_6 48tr_windows
        tmabs.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tmabs"][i][0, 0])  # 2 channels
        twl.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["twl"][i][0, 0])   # 1 channel
        tzc.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tzc"][i][0, 0])
        tslpch2.append(x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tslpch2"][i][0, 0])
        target.append(j)
tags = np.array(target)
tmabs = np.array(tmabs)
twl = np.array(twl)
tzc = np.array(tzc)
tslpch2 = np.array(tslpch2)
# print(twl.size)
# print()
print(tmabs)
# # number of each tag
# print(dict(Counter(target)))
print(twl)
print(tags)
# print((x[0]["sigFeatures"]["trFeatures"][0, 0][:, 0]["tmabs"][0][0]))

X = tmabs
y = (tags == 2).astype(np.float64)
iris = datasets.load_iris()
print(x[0]["sigFeatures"]["trFeatures"][0, 0][:, 0]["tmabs"])
# X = iris["data"][:, (2, 3)]  # petal length, petal width
# y = (iris["target"] == 2).astype(np.float64)  # Iris-Virginica
print(iris)
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


