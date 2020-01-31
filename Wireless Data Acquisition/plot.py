import matplotlib.pyplot as plt
import pandas as pd
X = pd.read_csv('saved data.txt', sep="\t", header=None)
df = pd.DataFrame(columns=['ch1', 'ch2', 'ch3', 'ch4', 'ch5', 'ch6', 'ch7', 'ch8', 'time'])

for i in range(0, X.shape[0]-1):
    for j in range(0, 8):

            if X[j][i][7] == '-':
                if abs(float(X[j][i][8:-2])) > 20 * abs(float(X[j][i+1][8:-2])):
                    df.at[i, 'ch' + str(j + 1)] = float(X[j][i+1][7:-2])
                else:
                    df.at[i, 'ch' + str(j + 1)] = float(X[j][i][7:-2])
            else:
                if abs(float(X[j][i][8:-2])) > 20 * abs(float(X[j][i+1][8:-2])):
                    df.at[i, 'ch' + str(j + 1)] = float(X[j][i+1][8:-2])
                else:
                    df.at[i, 'ch' + str(j + 1)] = float(X[j][i][8:-2])

    df.at[i, 'time'] = i/1000
print(df)

ax = plt.gca()
#
# df.plot(kind='line',x='time',y='ch2',ax=ax)
# df.plot(kind='line',x='time',y='ch3',ax=ax)
df.plot(kind='line',x='time',y='ch8', color='cyan', ax=ax)
# df.plot(kind='line',x='time',y='ch4', color='red', ax=ax)
# df.plot(kind='line',x='time',y='ch5', color='gray', ax=ax)
# df.plot(kind='line',x='time',y='ch6', color='pink', ax=ax)
# df.plot(kind='line',x='time',y='ch7', color='green', ax=ax)


plt.show()
plt.savefig('InternalTest.png')
