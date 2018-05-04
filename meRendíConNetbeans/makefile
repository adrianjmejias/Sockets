run:
	gcc -o servidor server.c libmd5.a
	gcc -o cliente client.c libmd5.a
	./servidor 3035
client:
	./client 127.0.0.1 3036