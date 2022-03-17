# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:49:38 by cdiaz-fl          #+#    #+#              #
#    Updated: 2022/02/21 12:01:32 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCS	=	main.c				\
			./source/aux.c		\
			./source/buildins.c	\
			./source/error.c	\
			./source/input.c	\
			./source/input2.c	\
			./source/process.c	\
			./source/split_ms.c	\
			./source/temp.c		\
			./source/utils.c	\
			./source/input3.c
		
OBJS	= ${SRCS:.c=.o}
SNAME	= -fsanitize=address
RM		= rm -rf
CC		= gcc
RED		= \033[0;31m
GREEN	= \033[0;32m
WHITE	= \033[0;37m
LIBFT	= -C ./libft
#LDFLAGS =  -I/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include\
            -lreadline\
            -L/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib\
SFLAGS  = -fsanitize=address -g3
CFLAGS  = -g3 -Wall -Werror -Wextra
LDFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
CPPFLAGS= -I/Users/$(USER)/.brew/opt/readline/include
all: $(NAME)
$(NAME) : $(OBJS)
		echo "$(RED)Compiling...				⏳$(WHITE)"
		make  ${LIBFT}/
		$(CC) ${CFLAGS} ${LDFLAGS} $(CPPFLAGS) $(SNAME) $^ -I. ./libft/libft.a -o $@    
%.o: %.c
	$(CC) ${CFLAGS} $(CPPFLAGS) -c $< -o $@

clean:
		@ echo "$(RED)Clean in progress...		⏳$(WHITE)"
		@ $(RM) *.dSYM
		@ $(RM) $(OBJS)
		@ ${MAKE} clean ${LIBFT}
		@ echo "$(GREEN)Clean done				✅$(WHITE)"

fclean: clean
		@ echo "$(RED)Fclean in progress...		⏳$(WHITE)"
		@ $(RM) *.dSYM
		@ $(RM) $(NAME)
		@ ${MAKE} fclean ${LIBFT}
		@ echo "$(GREEN)Fclean done				✅$(WHITE)"

re:		fclean all
.PHONY: all s clean fclean re