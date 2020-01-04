
import numpy as np
import pandas as pd
from scipy.io import loadmat
# .............data Manipulation............ #

#path = "E:/courses/Bs. Project/Classification/biopatrec-master/Dataset Features/"

def extract_table(path):
    # x = [loadmat(path + 'user%s-%dth-ft.mat' % (5, 5))]
    x = [loadmat(path)]
    nch = 2;
    nf = 4;
    nM = 5;
    ntrset = 48;
    ntset = 49;
    nvset = 24;
    cl_names = [];

    # define column names if needed
    for i in range(1, nf + 1):
        for j in range(1, nch + 1):
            cl_names.append('f' + str(i) + 'ch' + str(j))
    cl_names.append('Category')
    df = pd.DataFrame(columns=range(0, nf * 2 + 1))

    k = 0
    target = []

    # extracting each feature from .mat file
    r = 0;
    for j in range(0, nM):
        for i in range(0, ntrset):
            r = r + 1;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tmabs"][i][0]
            k= k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["twl"][i][0]
            k = k + 2;
            # df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["trms"][i][0]
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0]
            k = k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tslpch2"][i][0]
            k = 0;
            df.at[r, nf * 2 ] = int(j)

    for j in range(0, nM):
        for i in range(0, ntset):
            r = r + 1;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tmabs"][i][0]
            k = k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["twl"][i][0]
            k = k + 2;
            # df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["trms"][i][0]
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0]
            k = k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["tFeatures"][0, 0][:, j]["tslpch2"][i][0]
            k = 0;
            df.at[r, nf * 2 ] = int(j)

    for j in range(0, nM):
        for i in range(0, nvset):
            r = r + 1;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tmabs"][i][0]
            k = k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["twl"][i][0]
            k = k + 2;
            # df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["trms"][i][0]
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["trFeatures"][0, 0][:, j]["tzc"][i][0]
            k = k + 2;
            df.at[r, [k, k + 1]] = x[0]["sigFeatures"]["vFeatures"][0, 0][:, j]["tslpch2"][i][0]
            k = 0;
            df.at[r, nf * 2] = int(j)

    df.rename(columns = {df.columns[i] : cl_names[i] for i in range(0,nf * 2 + 1)}, inplace=True)

    return df

