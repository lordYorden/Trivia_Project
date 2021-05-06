import socket

EXIT_MSG = """90001{"message": "exit"}"""
SERVER_IP = "127.0.0.1"
SERVER_PORT = 200


def padding_maker(num):
    if len(num) < 4:
        return ("0" * (4 - len(num))) + num
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
        option = ""
        while option != "exit":
            flag = False
            option = input("Login or SignUp?").lower()
            if option == "login":
                msg = """{"username": "user1", "password": "1234"}"""
                length = len(msg)
                msg = "1" + padding_maker(str(length)) + msg
            elif option == "signup":
                msg = """{"username": "user1", "password": "1234", "mail":"user1@gmail.com"}"""
                length = len(msg)
                msg = "2" + padding_maker(str(length)) + msg
            elif option == "exit":
                msg = EXIT_MSG
            else:
                msg = "Error...wrong input!"
                flag = True
            print(msg)
            if not flag:
                sock.sendall((msg.encode()))
                msg = sock.recv(1024)
                print(msg.decode())
        sock.close()


if __name__ == '__main__':
    main()
