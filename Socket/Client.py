import socket               # Import socket module

from numpy.core import byte

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 8090                # Reserve a port for your service.
x = (0, 1, 2, 3, 4, 5, 43, 12)
print(host)
s.connect((host, port))
#for i in range(36):
s.send(bytearray("123456789010", "utf-8"))

  #  print(i, "send")
print (s.recv(9))
s.close                     # Close the socket when done