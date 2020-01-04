from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import confusion_matrix
from sklearn.decomposition import PCA
from sklearn.pipeline import Pipeline
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

from sklearn.preprocessing import StandardScaler
import os
import numpy as np
import pandas as pd
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis
from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import GridSearchCV, KFold, LeaveOneOut as loo




files = []
j = 3
for i in range (1,14):
    # for j in range(1,4):
     files.append('user' + str(i) + '-' + str(j) + '-' + 'ft' + '.csv')

users = []
mov_acc = []

for i in range (0, 13):

    data = pd.read_csv(os.path.join('Dataset' , files[i]))
    # data = pd.read_csv(os.path.join(os.getcwd(), files[i]))
    # print(data)
    users.append(data)
    # X = data.loc[:, 'f1ch1':'f4ch2']
    # y = np.asarray(data['Category'], dtype="|S6")
    #
    # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
    #
    # clf = LinearDiscriminantAnalysis()
    # clf.fit(X_train, y_train)
    # y_pred = clf.predict(X_test)
    #
    # print("User" + str(i+1) + " Test score: ", clf.score(X_test, y_test) * 100)
    # # print("Train score", clf.score(X_train, y_train))
    # cm = confusion_matrix(y_test, y_pred)
    # cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
    # cm_d = cm.diagonal() * 100
    # print(cm_d)


y_data = np.asarray((pd.concat(users, axis=0, ignore_index=True).loc[:, 'Category']), dtype="|S6")
X_data = pd.concat(users, axis=0, ignore_index=True).loc[:, 'f1ch1': 'f4ch2']


scaler = StandardScaler().fit(X_data)
X_train_transformed = scaler.transform(X_data)
X_train_data, X_test_data, y_train_data, y_test_data = train_test_split(X_data, y_data, random_state=42, test_size=0.33)
#
# pca = PCA(2)
# pca.fit(X_train_data)
# pca.fit(X_test_data)
# print(pca.n_components)
# X_train_data = pca.transform(X_train_data)
# X_test_data = pca.transform(X_test_data)

clf = LinearDiscriminantAnalysis(solver='lsqr', shrinkage='auto')
# clf = LinearDiscriminantAnalysis()
clf.fit(X_train_data, y_train_data)
y_pred = clf.predict(X_test_data)
#
accuracy_data = clf.score(X_test_data, y_test_data)
print("Global Accuracy: %s" % accuracy_data)
K_fold = StratifiedKFold(n_splits=5)
scores = []
scores = cross_val_score(clf, X_train_transformed, y_data, cv=K_fold,n_jobs = 4, scoring = 'accuracy')
print(scores)
print("Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))
cm = confusion_matrix(y_test_data, y_pred)
cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
cm_d = cm.diagonal() * 100
print(cm_d)