import time
import socket
import threading
import SocketServer

class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):

	# def handle(self):
	# 	data = self.request.recv(1024)
	# 	cur_thread = threading.current_thread()
	# 	response = "{}: {}".format(cur_thread.name, data)
	# 	self.request.sendall(response)

    def handle(self):
        # self.request is the TCP socket connected to the client
		while True:
			self.data = self.request.recv(1024).strip()
			# self.r

			prinlt "{} wrote:".format(self.client_address[0])

			if not self.data: break


			cur_thread = threading.current_thread()
			response = "{}: {}".format(cur_thread.name, self.data)


			print response.
			# just send back the same data, but upper-cased
			self.request.send(self.data.upper())


class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
	pass

def client(ip, port, message):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((ip, port))
	try:
		sock.sendall(message)
		response = sock.recv(1024)
		print "Received: {}".format(response)
	finally:
		sock.close()

if __name__ == "__main__":
	# Port 0 means to select an arbitrary unused port
	HOST, PORT = "localhost", 9999

	server = ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
	ip, port = server.server_address

	# Start a thread with the server -- that thread will then start one
	# more thread for each request
	server_thread = threading.Thread(target=server.serve_forever)
	# Exit the server thread when the main thread terminates
	server_thread.daemon = True
	server_thread.start()
	print "Server loop running in thread:", server_thread.name

	# client(ip, port, "Hello World 1")
	# client(ip, port, "Hello World 2")
	# client(ip, port, "Hello World 3")

	time.sleep(5000)

	server.shutdown()

# import SocketServer

# class MyTCPHandler(SocketServer.BaseRequestHandler):
#     """
#     The RequestHandler class for our server.

#     It is instantiated once per connection to the server, and must
#     override the handle() method to implement communication to the
#     client.
#     """

#     def handle(self):
#         # self.request is the TCP socket connected to the client
# 		while True:
# 			self.data = self.request.recv(1024).strip()
# 			print "{} wrote:".format(self.client_address[0])

# 			if not self.data: break

# 			print self.data
# 			# just send back the same data, but upper-cased
# 			self.request.send(self.data.upper())

# if __name__ == "__main__":
#     HOST, PORT = "localhost", 9999

#     # Create the server, binding to localhost on port 9999
#     server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)

#     # Activate the server; this will keep running until you
#     # interrupt the program with Ctrl-C
#     server.serve_forever()
