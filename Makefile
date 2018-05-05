# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/01 15:31:54 by vpopovyc          #+#    #+#              #
#    Updated: 2018/04/01 15:31:55 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = avm

SRCFILENAME := Parser.cpp Lexer.cpp Lexeme.cpp AVMException.cpp main.cpp

SRC = $(addprefix src/, $(SRCFILENAME))

OBJ = $(SRC:.cpp=.o)

CC = clang++

CCFLAGS = -Wall -Wextra -Werror -std=c++1z

AVMINC = -Iincludes

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(EXEC)

%.o:%.cpp
	$(CC) $(CCFLAGS) $(AVMINC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(EXEC)

re: fclean all

.phony: all clean fclean re