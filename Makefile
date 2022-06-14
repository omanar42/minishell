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
CC		=	gcc -Wall -Wextra -Werror -Iincludes
RM		=	rm -f
LIBFT	=	libs/libft/libft.a
SRCS	=	srcs/minishell.c $(LIBFT)
OBJS	=	$(SRCS:.c=.o)

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

%.o: %.c
	@ $(CC) -c $< -o $@

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libs/libft

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Minishell >\033[0m"
	@$(CC) -lreadline $(OBJS) -o $(NAME)
	@echo "\033[1;32mMinishell has been compiled!\033[0m\n"

clean:
	@$(RM) $(OBJS)
	@make clean -C libs/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libs/libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re