all: clean server client

server:
	g++ -o server server.cpp

client:
	g++ -o client client.cpp

clean:
	rm -f server client

# Run server arguments
# - PORT 			8888
# - #CON			40
# - TIMEOUT		10000
# - DIR				${shell pwd}
PORT = 8888
CON = 40
TIMEOUT = 10000
slash := /
DIR = ${shell pwd}$(slash)

s:
	./server $(PORT) $(CON) $(TIMEOUT) $(DIR)

c:
	./client