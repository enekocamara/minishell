# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:49:38 by cdiaz-fl          #+#    #+#              #
#    Updated: 2022/02/14 11:44:01 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:49:38 by cdiaz-fl          #+#    #+#              #
#    Updated: 2022/02/14 11:07:50 by oholgado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	= minishell
SRCS	=	main.c\
			minishell_utils.c \
			aux.c\
			functions.c\
		
OBJS	= ${SRCS:.c=.o}
SNAME	= fsanitize
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
CFLAGS  = -Wall -Werror -Wextra 
LDFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/ -I/Users/$(USER)/.brew/opt/readline/include/readline/
all: $(NAME)
$(NAME) : $(OBJS)
		echo "$(RED)Compiling...				⏳$(WHITE)"
		make  ${LIBFT}/
		$(CC) ${CFLAGS} ${LDFLAGS} $^ -I. ./libft/libft.a -o $@    
%.o: %.c
	$(CC) ${CFLAGS} -I/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include -I/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib -c $< -o $@

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