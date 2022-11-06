NAME =	lem-in
GENER_NAME = generator
VISU_NAME = visualizer


SRCS =			$(wildcard src/*.c) $(wildcard lib/libft/*.c)
GENER_SRCS = 	$(wildcard generate/*.c) $(wildcard lib/libft/*.c)
VISU_SRCS =		$(wildcard visualize/*.c) $(wildcard lib/libft/*.c) \
				src/rooms_utils.c src/parser.c


OBJS =	$(SRCS:.c=.o)
GENER_OBJS = $(GENER_SRCS:.c=.o)
VISU_OBJS = $(VISU_SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f

all: $(NAME) generator visualizer

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

generator:	${GENER_OBJS}
			${CC} ${CFLAGS} ${GENER_OBJS} -o ${GENER_NAME}

visualizer:	${VISU_OBJS}
			${CC} ${CFLAGS} -I ~/.brew/opt/sdl2/include -L ~/.brew/opt/sdl2/lib -l SDL2-2.0.0 ${VISU_OBJS} -o ${VISU_NAME}

clean:
			${RM} $(OBJS)
			${RM} ${GENER_OBJS}
			${RM} ${VISU_OBJS}

fclean:		clean
			${RM} $(NAME)
			${RM} ${GENER_NAME}
			${RM} ${VISU_NAME}

re:			fclean all

.PHONY:		clean fclean re all
