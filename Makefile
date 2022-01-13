SRCS =		ft_split_for_paths.c ft_split_for_args.c ft_strjoin.c\
			ft_strlen.c ft_substr.c pipex.c exec_cmd.c
OBJS =		$(SRCS:.c=.o)
NAME =		pipex
HEADERS =   pipex.h
GCC =		gcc
RM =		rm -f
CFLAGS =	-Wall -Wextra -Werror

.c.o:
			$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			@$(GCC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME) 

re:			fclean all

.PHONY:		all clean clean fclean re