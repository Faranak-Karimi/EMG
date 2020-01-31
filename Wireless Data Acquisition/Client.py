import socket  # Import socket module
import time
from numpy.core import byte
import numpy as np
import pandas as pd
s = socket.socket()  # Create a socket object
host = "192.168.100.10"  # Get local machine name
port = 65100
# Reserve a port for your service.
i = 0
# x = (0, 1, 2, 3, 4, 5, 43, 12, 180, 255)
socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
data_ = ''
array = []
f = open("saved data.txt", 'w')  # for writing data

def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0:  # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)  # compute negative value
    return val


def shift(seq, n):
    n = n % len(seq)
    return seq[n:] + seq[:n]


def split_channels(ss):
    data1 = (int(twos_comp(int(ss[3] * 65536 + ss[4] * 256 + ss[5]), 24)) / 3355443)
    data2 = (int(twos_comp(int(ss[6] * 65536 + ss[7] * 256 + ss[8]), 24)) / 3355443)
    data3 = (int(twos_comp(int(ss[9] * 65536 + ss[10] * 256 + ss[11]), 24)) / 3355443)
    data4 = (int(twos_comp(int(ss[12] * 65536 + ss[13] * 256 + ss[14]), 24)) / 3355443)
    data5 = (int(twos_comp(int(ss[15] * 65536 + ss[16] * 256 + ss[17]), 24)) / 3355443)
    data6 = (int(twos_comp(int(ss[18] * 65536 + ss[19] * 256 + ss[20]), 24)) / 3355443)
    data7 = (int(twos_comp(int(ss[21] * 65536 + ss[22] * 256 + ss[23]), 24)) / 3355443)
    data8 = (int(twos_comp(int(ss[24] * 65536 + ss[25] * 256 + ss[26]), 24)) / 3355443)
    # data_t = [data1, data2, data3, data4, data5, data6, data7, data8]
    f.write("ch 1: '{:.6f}' \t ch 2: '{:.6f}' \t ch 3: '{:.6f}'"
                 " \t ch 4: '{:.6f}' \t ch 5: '{:.6f}' \t ch 6: '{:.6f}'"
                 " \t ch 7: '{:.6f}' \t ch 8: '{:.6f}'\n"
                 .format(data1,
                         data2, data3, data4, data5,
                         data6, data7, data8))  # perf_counter() - self.start_time,
    # df = pd.DataFrame(data, columns=['ch1', 'ch2', 'ch3', 'ch4', 'ch5', 'ch6', 'ch7', 'ch8'])
i = 0
while True:
    if data_ != b'G':
        t1 = time.time()
        s.sendall(b'G')
        print("sent G")
        data_ = s.recv(1)
        print("read ")
    else:
        i = i+1
        data = s.recv(27)
        check = data.find(0x48)
        check2 = data.count(0x48)
        check3 = data.count(0x49)
        check4 = data.count(0x50)
        print(i)
        if check >= 0 and check2*check3*check4 == 1:
            data = shift(data, check)
            split_channels(data)
            print(data)
        #     print("checked...")
        #     # ss = s.recv(24)

        if time.time() - t1 > 10:
            print("it's beent a long time")
            # s.sendall(b'G')
            break

        # host.write(b'G')
    # print('Received', repr(ss))
s.close()
f.close()
print("connection is closed.....")
