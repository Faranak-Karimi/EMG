import matplotlib.pyplot as plt
import pandas as pd
X = pd.read_csv('saved data.txt', sep="\t", header=None)
df = pd.DataFrame(columns=['ch1', 'ch2', 'ch3', 'ch4', 'ch5', 'ch6', 'ch7', 'ch8', 'time'])

df.at[0, 'ch1'] = 2
for i in range(0, 4316):
    for j in range(0, 8):
        if X[j][i][7] == '-':
            df.at[i, 'ch' + str(j + 1)] = float(X[j][i][7:-2])
        else:
            df.at[i, 'ch' + str(j + 1)] = float(X[j][i][8:-2])
    df.at[i, 'time'] = i/1000
print(df)

ax = plt.gca()

df.plot(kind='line',x='time',y='ch1',ax=ax)
df.plot(kind='line',x='time',y='ch8', color='red', ax=ax)

plt.show()

