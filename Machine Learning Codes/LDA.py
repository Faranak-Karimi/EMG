from sklearn.metrics import confusion_matrix
from sklearn.pipeline import Pipeline
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

from sklearn.preprocessing import StandardScaler
import os
import numpy as np
import pandas as pd
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.model_selection import train_test_split

j = 3
files = []
# for j in range(1,4)
for i in range (1,14):
    files.append('user' + str(i) + '-' + str(j) + '-' + 'ft' + '.csv')

data = pd.read_csv(os.path.join('Dataset' , files[1]))

X = data.loc[:, 'f1ch1':'f4ch2']
y = np.asarray(data['Category'], dtype="|S6")
# print(y)
scaler = StandardScaler()
scaler.fit(X)
X=scaler.transform(X)
# X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
# print(X_train)

for i in range(0,5):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33)
    clf = LinearDiscriminantAnalysis()
    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    print("Test score", clf.score(X_test, y_test))
    print("Train score", clf.score(X_train, y_train))
    cm = confusion_matrix(y_test, y_pred)
    cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
    cm_d = cm.diagonal()
    print(cm_d)


# Visualising the Training set results
