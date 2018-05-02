# Echo server program
import socket

HOST = '192.168.1.40'                 # Symbolic name meaning the local host
PORT = 1099              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
print 'Connected by', addr
while 1:
    s.listen(5)
    client, address = s.accept()
    print "{} connected".format( address )
    
    response = client.recv(255)
    print(response)
    if response != "":
        client.send("Hello")
        print 'Message envoyer'

client.send("Comment ca va ?")
client.close()

