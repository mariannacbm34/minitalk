# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marmonte <marmonte@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 15:52:52 by marmonte          #+#    #+#              #
#    Updated: 2023/06/14 16:45:01 by marmonte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk
CLIENT		=	client
SERVER		=	server
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address
RM			=	rm -f

SRC	=	client.c	\
		server.c

OBJ	=  $(SRC:.c=.o)

all: $(NAME)


$(SERVER) : server.o
	$(CC) $(CFLAGS) server.o -o $(SERVER)

$(CLIENT) : client.o
	$(CC) $(CFLAGS) client.o -o $(CLIENT)

$(NAME) : $(CLIENT) $(SERVER)

clean:
	$(RM) -rf $(OBJ)

fclean: clean
		$(RM) $(NAME)
		$(RM) $(CLIENT)
		$(RM) $(SERVER)

re: fclean all

.PHONY:	all clean fclean re