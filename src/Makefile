CC = clang++
LD = clang++
CFLAGS = -stdlib=libc++ -std=c++11 -c -g
LDFLAGS = -stdlib=libc++ -lc++ -lc++abi
EXEC = test
OBJS = main.o \
	   ./EventLoop.o \
	   ./Channel.o \
	   ./Poller.o \
	   ./EpollPoller.o \
	   ./Socket.o \
	   ./InetAddress.o \
	   ./Acceptor.o \
	   ./TcpServer.o \
	   ./TcpConnection.o

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(LD) $(LDFLAGS) $(^) -o $(@)

%.o: %.cc
	$(CC) $(CFLAGS) $(<) -o $(@)

.PHONY: clean
clean:
	-rm -f $(EXEC)
	-rm -f $(OBJS)
