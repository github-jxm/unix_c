all:

	gcc -m32 -o cancel cancel.c -lpthread
	gcc -m32 -o create create.c -lpthread
	gcc -m32 -o detach detach.c -lpthread
	gcc -m32 -o equal  equal.c -lpthread
	gcc -m32 -o exit   exit.c -lpthread
	gcc -m32 -o join   join.c -lpthread
	gcc -m32 -o tcpcli tcpcli.c
	gcc -m32 -o tcpsvr tcpsvr.c
	gcc -m32 -o udpcli udpcli.c
	gcc -m32 -o udpsvr udpsvr.c

clean: 
	rm  -rf cancel \
		create  \
		detach  \
		equal   \
		exit    \
		join    \
		tcpcli  \
		tcpsvr  \
		udpcli  \
		udpsvr 
