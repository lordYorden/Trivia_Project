import socket
SERVER_IP = "127.0.0.1"
SERVER_PORT = 200


def padding_maker(num):
    if len(num) < 4:
        return ("0"*(4-len(num)))+num
    else:
        return num


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # creates socket
    server_address = (SERVER_IP, SERVER_PORT)
    try:
        sock.connect(server_address)  # try to connect, if its close, exception...
    except:
        print("The server is closed, try later")
        sock.close()  # closes socket
    else:
        option = input("Login or SignUp?")
        if option == "Login":
            msg = """{"username": "user1", "password": "1234"}"""
            length = len(msg)
            msg = "1" + padding_maker(str(length)) + msg
            print(msg)
        elif option == "SignUp":
            msg = """{"username": "user1", "password": "1234", "mail":"user1@gmail.com"}"""
            length = len(msg)
            msg = "2" + str(length) + msg
        sock.sendall((msg.encode()))
        msg = sock.recv(1024)
        print(msg.decode())


if __name__ == '__main__':
    main()
