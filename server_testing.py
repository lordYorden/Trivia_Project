import socket
SERVER_IP = "127.0.0.1"
SERVER_PORT = 200
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # creates socket
server_address = (SERVER_IP, SERVER_PORT)
try:
    sock.connect(server_address)  # try to connect, if its close, exception...

except:
    print("The server is closed, try later")
    sock.close()  # closes socket
else:
    msg =  sock.recv(1024)
    if(msg.decode() == "Hello"):
        MSG = "Hello"
        sock.sendall(MSG.encode())
        sock.close()
    else:
        sock.close()