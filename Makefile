#######################################################
## ARGUMENTS

NAME =	minitalk

NAME_SERVER	=	server
NAME_CLIENT	=	client

NAME_SERVER_BONUS	=	$(addsuffix _bonus, $(NAME_SERVER))
NAME_CLIENT_BONUS	=	$(addsuffix _bonus, $(NAME_CLIENT))

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
HEADER		=	-Iinc

SRC_DIR		=	src/
OBJ_DIR		=	obj/

LIB_PATH	=	./libft
LIBA		=	$(LIB_PATH)/libft.a

RM			=	rm -rf

#######################################################
## SRCS & OBJS

SRC_SERVER	=	$(addprefix $(SRC_DIR), $(addsuffix _bonus.c, $(NAME_SERVER)))
SRC_CLIENT	=	$(addprefix $(SRC_DIR), $(addsuffix _bonus.c, $(NAME_CLIENT)))

OBJ_SERVER	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(NAME_SERVER)))
OBJ_CLIENT	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(NAME_CLIENT)))

OBJ_SERVER_BONUS	=	$(addprefix $(OBJ_DIR), $(addsuffix _bonus.o, $(NAME_SERVER)))
OBJ_CLIENT_BONUS	=	$(addprefix $(OBJ_DIR), $(addsuffix _bonus.o, $(NAME_CLIENT)))

#######################################################
## RULES

all : $(NAME)

$(LIBA) :
		make -C $(LIB_PATH)

$(NAME) : $(LIBA) $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJ_SERVER)
		$(CC) $(CFLAGS) $(HEADER) $(OBJ_SERVER) -o $(NAME_SERVER) $(LIBA)

$(NAME_CLIENT) : $(OBJ_CLIENT)
		$(CC) $(CFLAGS) $(HEADER) $(OBJ_CLIENT) -o $(NAME_CLIENT) $(LIBA)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

bonus : all $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS) : $(OBJ_SERVER_BONUS)
		$(CC) $(CFLAGS) $(HEADER) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS) $(LIBA)

$(NAME_CLIENT_BONUS) : $(OBJ_CLIENT_BONUS)
		$(CC) $(CFLAGS) $(HEADER) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS) $(LIBA)

$(OBJ_DIR) :
		@mkdir -p $(OBJ_DIR)

clean :
		@make -C $(LIB_PATH) fclean
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re : fclean all

.PHONY: all clean fclean re bonus
