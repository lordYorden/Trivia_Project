import socket

EXIT_MSG = """90001{"message": "exit"}"""
SERVER_IP = "127.0.0.1"
SERVER_PORT = 200


def padding_maker(num):
    if len(num) < 4:
        return ("0" * (4 - len(num))) + num
    else:
        return num


def print_menu():
    menu = """
    choose error
    1 - you have to be signup in order to login
    2 - can't register with the same name twice
    3 - can't login if you are already logged in  
    4 - uname is invalid
    """
    print(menu)


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # creates socket
    server_address = (SERVER_IP, SERVER_PORT)
    try:
        sock.connect(server_address)  # try to connect, if its close, exception...
    except:
        print("The server is closed, try later")
        sock.close()  # closes socket
    else:
        option = 0
        msg = ""
        print_menu()
        option = int(input("pick one: "))
        if option == 1:
            msg = """{"username": "user2", "password": "1234"}"""
            length = len(msg)
            msg = "1" + padding_maker(str(length)) + msg
            sock.sendall(msg.encode())
            msg = sock.recv(1024)
        elif option == 2:
            for i in range(2):
                msg = """{"username": "user2", "password": "1234", "mail":"user1@gmail.com"}"""
                length = len(msg)
                msg = "2" + padding_maker(str(length)) + msg
                sock.sendall(msg.encode())
                msg = sock.recv(1024)
        elif option == 3:
            for i in range(2):
                msg = """{"username": "user2", "password": "1234"}"""
                length = len(msg)
                msg = "1" + padding_maker(str(length)) + msg
                sock.sendall(msg.encode())
                msg = sock.recv(1024)
        elif option == 4:
            msg = """{"username": "user2%&", "password": "1234", "mail":"user1@gmail.com"}"""
            length = len(msg)
            msg = "2" + padding_maker(str(length)) + msg
            sock.sendall(msg.encode())
            msg = sock.recv(1024)
        print(msg.decode())


if __name__ == '__main__':
    main()
