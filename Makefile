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
RM		=	rm -f
CC		=	gcc -Wall -Wextra -Werror -Iincludes -I libs/libft/includes -g -fsanitize=address
RLFLG	=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT	=	libs/libft/libft.a
SRCS	=	srcs/minishell.c srcs/lexer.c srcs/token.c srcs/next_token.c $(LIBFT)

define HEADER_M
    __  ___ ____ _   __ ____   _____  __  __ ______ __     __ 
   /  |/  //  _// | / //  _/  / ___/ / / / // ____// /    / / 
  / /|_/ / / / /  |/ / / /    \__ \ / /_/ // __/  / /    / /  
 / /  / /_/ / / /|  /_/ /    ___/ // __  // /___ / /___ / /___
/_/  /_//___//_/ |_//___/   /____//_/ /_//_____//_____//_____/
endef
export HEADER_M

all: header_m $(NAME)

header_m:
	@echo "\033[0;32m$$HEADER_M\033[0m\n"

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libs/libft

$(NAME): $(SRCS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Minishell >\033[0m"
	@$(CC) $(RLFLG) $(SRCS) -o $(NAME)
	@echo "\033[1;32mMinishell has been compiled!\033[0m\n"

clean:
	@make clean -C libs/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libs/libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re header_m