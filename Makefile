INC = minitalk.h
INC_BONUS = minitalk_bonus.h

CFLAGS = -Wall -Wextra -Werror


all : server client

bonus: server_bonus client_bonus

server: server.c utils.c $(INC)
	cc $(CFLAGS) server.c utils.c -o server

client: client.c utils.c $(INC)
	cc $(CFLAGS) client.c utils.c -o client
	
server_bonus: server_bonus.c utils.c $(INC_BONUS)
	cc $(CFLAGS) server_bonus.c utils.c -o server_bonus

client_bonus: client_bonus.c utils.c $(INC_BONUS)
	cc $(CFLAGS)  client_bonus.c utils.c -o client_bonus

clean:
	
fclean : clean
	rm -rf server server_bonus client client_bonus

re : fclean all