# *********************************************** #
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2022/06/13 04:40:50 by omanar       #
#                                                 #
# *********************************************** #

NAME	=	minishell
CC		=	gcc
RM		=	rm -f
LIBFT	=	libft/libft.a
SRCS	=	srcs/minishell.c $(LIBFT)
OBJS	=	$(SRCS:.c=.o)

define HEADER_M
        _       _     _          _ _ 
  /\/\ (_)_ __ (_)___| |__   ___| | |
 /    \| | '_ \| / __| '_ \ / _ \ | |
/ /\/\ \ | | | | \__ \ | | |  __/ | |
\/    \/_|_| |_|_|___/_| |_|\___|_|_|
endef
export HEADER_M

all: header_m $(NAME)

header_m:
	@echo "\033[0;32m$$HEADER_M\033[0m\n"

%.o: %.c
	@ $(CC) -Wall -Wextra -Werror -c $< -o $@

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libft

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Minishell >\033[0m"
	@$(CC) $(OBJS) -o $(NAME)
	@echo "\033[1;32mMinishell has been compiled!\033[0m\n"

clean:
	@$(RM) $(OBJS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re