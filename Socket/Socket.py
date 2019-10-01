import socket

s = socket.socket()
host = socket.gethostname() # Get local machine name

s.bind(("0.0.0.0", 8090))
s.listen(2)

while True:

    client, addr = s.accept()

    while True:
        content = client.recv(50)

        if len(content) == 0:
            break

        else:
            print(content)
   # client.send('Thank you for connecting')
    print("Closing connection")
    client.close()
