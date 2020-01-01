# this file is intended to do the job of data manipulation
from nltk.sentiment.util import split_train_test
from sklearn import datasets
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC, SVC
import numpy as np
from scipy.io import loadmat
from extract_table import extract_table
import pandas as pd
from collections import Counter
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix

path1 = "E:/courses/Bs. Project/Classification/biopatrec-master/Dataset Features/"
# .............data Manipulation............ #
df = extract_table(path1)
X = df.loc[:, 'f1ch1': 'f4ch2']  # petal length, petal width
y = (df.loc[:, 'Category']).astype(np.float64)  # Iris-Virginica
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state = 42, test_size=0.33)
svm_clf = Pipeline([("scaler", StandardScaler()), ("linear_svc", LinearSVC(C=1, loss="hinge")), ])
svm_linear = svm_clf.fit(X_train, y_train)
svm_predictions = svm_linear.predict(X_test)
accuracy = svm_linear.score(X_test, y_test)
cm = confusion_matrix(y_test, svm_predictions)
print(accuracy)
print(cm)
# svm_model_linear = SVC(kernel='linear', C=1).fit(X_train, y_train)
# svm_predictions = svm_model_linear.predict(X_test)
# accuracy = svm_model_linear.score(X_test, y_test)
# titles_options = [("Confusion matrix, without normalization", None),
#                   ("Normalized confusion matrix", 'true')]
# for title, normalize in titles_options:
#     disp = plot_confusion_matrix(svm_linear, X_test, y_test,
#                                  display_labels=df.columns.values,
#                                  cmap=plt.cm.Blues,
#                                  normalize=normalize)
#     disp.ax_.set_title(title)
#
#     print(title)
#     print(disp.confusion_matrix)
#
# plt.show()
# creating a confusion matrix