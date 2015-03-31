import time
import socket
import sys

HOST, PORT = "localhost", 9999
data = " ".join(sys.argv[1:])

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
	# Connect to server and send data


	print "connecting..."
	sock.connect((HOST, PORT))
	print "done!"

	i = 1
	while True:
		data = str(i)
		i = i + 1
		sock.send(data + "\n")
		received = sock.recv(1024)

		print "Sent:     {}".format(data)
		print "Received: {}".format(received)

		time.sleep(1)

finally:
	sock.close()

	
