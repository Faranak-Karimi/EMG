
import extract_table as t
import numpy as np
import re
import pandas as pd
import os

dir =r"C:\Users\Vida\Dropbox\BS Thesis\Datasets\Dataset Features"
j = 3
files = []
# for j in range(1,4)
for i in range (1,14):
    files.append('user' + str(i) + '-' + str(j) + '-' + 'ft')
    path = (os.path.join(dir , files[i-1] + '.mat'))
    df = t.extract_table(path)
    df.to_csv(files[i-1] + '.csv', index=False)

