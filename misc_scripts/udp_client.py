import socket

UDP_IP = "10.58.228.228"
UDP_PORT = 53000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(b"/left 10", (UDP_IP, UDP_PORT))
sock.close()