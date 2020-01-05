# Support Vector Machine
from sklearn.pipeline import Pipeline
from sklearn.model_selection import StratifiedKFold, StratifiedShuffleSplit
from sklearn.model_selection import cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC, SVC
import numpy as np
from scipy.io import loadmat
from extract_table import extract_table
import pandas as pd
from collections import Counter
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, classification_report
import os
from sklearn.model_selection import GridSearchCV
import random

# j = 3
files = []
li_train = []
li_test = []
# files.append('user' + str(1) + '-' + str(1) + '-' + 'ft' + '.csv')
# for j in range(1, 4):
# j = 1
for i in range(1, 13):
    file = 'user' + str(i) + '-' + str(1) + '-' + 'ft' + '.csv'
    # file = 'user' + str(i) + '.csv'
    data = pd.read_csv(os.path.join('Dataset', file))
    # .............data Manipulation............ #
    X = data.loc[:, 'f1ch1': 'f2ch2']
    y = (data.loc[:, 'Category']).astype(np.float64)
    X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42, test_size=0.25)
    svm_clf = Pipeline([("scaler", StandardScaler()),("svm_clf", SVC(kernel="rbf", gamma=0.1, C=100))])
    # svm_clf = Pipeline([("scaler", StandardScaler()), ("linear_svc", LinearSVC(loss="hinge")), ])
    svm_linear = svm_clf.fit(X_train, y_train)
    y_pred = svm_linear.predict(X_test)
    accuracy = svm_linear.score(X_test, y_test)
    # randomizing DataFarme rows
    #data = data.sample(frac=1).reset_index(drop=True)
    li_train.append(data)
    #li_train = random.shuffle(li_train)
    #cm = confusion_matrix(y_test, svm_predictions)
    print('user %s wet : %d '%(i, accuracy*100))


for j in range(1, 8):
    # files.append('user' + str(i) + '-' + str(j) + '-' + 'ft' + '.csv')
    file = 'user' + str(3) + '-' + str(j) + '-' + 'dryft'+'.csv'
# files.append('user' + str(1) + '-' + str(3) + '-' + 'ft' + '.csv')
# files.append('user' + str(1) + '-' + str(1) + '-' + 'ft' + '.csv')
# for n in range(0, 13):
#     data = pd.read_csv(os.path.join('test', file))
    data = pd.read_csv(os.path.join(os.getcwd(), file))
    li_test.append(data)
    # .............data Manipulation............ #
    X = data.loc[:, 'f1ch1': 'f2ch2']
    y = (data.loc[:, 'Category']).astype(np.float64)
    X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=38, test_size=0.25)
    svm_clf = Pipeline([("scaler", StandardScaler()),("svm_clf", SVC(kernel="rbf", gamma=0.1, C=100))])
    # svm_clf = Pipeline([("scaler", StandardScaler()), ("linear_svc", LinearSVC(loss="hinge")), ])
    svm_linear = svm_clf.fit(X_train, y_train)
    y_pred = svm_linear.predict(X_test)
    accuracy = svm_linear.score(X_test, y_test)
    # cm = confusion_matrix(y_test, svm_predictions)
    print('user3_ %s dry: %d ' % (j, accuracy*100))
    # randomizing DataFarme rows
    #data = data.sample(frac=1).reset_index(drop=True)
#
# for n in range(26, 38):
#     data = pd.read_csv(os.path.join('Dataset', files[n]))
#     li_test.append(data)
#     # .............data Manipulation............ #
#     X = data.loc[:, 'f1ch1': 'f4ch2']
#     y = (data.loc[:, 'Category']).astype(np.float64)
#     X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42, test_size=0.25)
#     # svm_clf = Pipeline([("scaler", StandardScaler()), ("svm_clf", SVC(kernel="poly", degree=3, coef0=1, C=5))])
#     # svm_clf = Pipeline([("scaler", StandardScaler()), ("linear_svc", LinearSVC(C=16.8, loss="hinge")), ])
#     svm_linear = svm_clf.fit(X_train, y_train)
#     svm_predictions = svm_linear.predict(X_test)
#     accuracy = svm_linear.score(X_test, y_test)
#     # cm = confusion_matrix(y_test, svm_predictions)
#     print('user %s : %d '%(n, accuracy*100))

# y_data = (pd.concat(li, axis=0, ignore_index=True).loc[:, 'Category']).astype(np.float64)
# X_data = pd.concat(li, axis=0, ignore_index=True).loc[:, 'f1ch1': 'f4ch2']

# for user-dependency test uncomment the bellow block

# X_data = pd.concat(li_train, axis=0, ignore_index=True).loc[:, 'f1ch1': 'f4ch2']
# li_test = random.shuffle(li_test)
# li_train = random.shuffle(li_train)
X_test_data = pd.concat(li_test, axis=0, ignore_index=True).loc[:, 'f1ch1': 'f2ch2']
X_train_data = pd.concat(li_train, axis=0, ignore_index=True).loc[:, 'f1ch1': 'f2ch2']
# y_data = (pd.concat(li_train, axis=0, ignore_index=True).loc[:, 'Category']).astype(np.float64)
y_test_data = (pd.concat(li_test, axis=0, ignore_index=True).loc[:, 'Category']).astype(np.float64)
y_train_data = (pd.concat(li_train, axis=0, ignore_index=True).loc[:, 'Category']).astype(np.float64)
# X_train_data, X_test = train_test_split(X, random_state=52, test_size=0)

# X_train_data, X_test_data, y_train_data, y_test_data = train_test_split(X_data, y_data, random_state=39, test_size=0.25)

svm_linear = svm_clf.fit(X_train_data, y_train_data)
svm_predictions = svm_linear.predict(X_test_data)
accuracy_data = svm_linear.score(X_test_data, y_test_data)
print("Global Accuracy: %s" % accuracy_data)


# C_range = np.logspace(-2, 10, 13)
# gamma_range = np.logspace(-9, 3, 13)
# param_grid =  C_range
# cv = StratifiedShuffleSplit(n_splits=5, test_size=0.2, random_state=42)
# grid = GridSearchCV(estimator=SVC(),
#              param_grid={'C': [30,40 ], 'kernel': ('linear', 'rbf')})
# grid.fit(X_data, y_data)
#
# print("The best parameters are %s with a score of %0.2f"
#       % (grid.best_params_, grid.best_score_))
#
# K_fold = StratifiedKFold(n_splits=5)
# scores = []
# scores = cross_val_score(svm_clf, X_data, y_data, cv=K_fold,n_jobs = 1, scoring = 'accuracy')
# print(scores)
# print("Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))
cm = confusion_matrix(y_test_data, svm_predictions)
cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
cm_d = cm.diagonal() * 100
print(cm_d)
