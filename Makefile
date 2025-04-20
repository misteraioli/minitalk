#######################################################
## ARGUMENTS

# NAME

NAME				=	minitalk

NAME_SERVER			=	server
NAME_CLIENT			=	client

NAME_SERVER_BONUS	=	$(addsuffix _bonus, $(NAME_SERVER))
NAME_CLIENT_BONUS	=	$(addsuffix _bonus, $(NAME_CLIENT))

# CC FLAG INC

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iinc

# SRC & OBJ DIR

SRC_DIR	=	src/
OBJ_DIR	=	obj/

# LIB

LIB_PATH	=	./libft
LIB			=	$(LIB_PATH)/libft.a

# RM

RM	=	rm -rf

# HEADERS

HEADER	= \
		inc/minitalk.h \
		inc/minitalk_bonus.h \

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

all : $(LIB) $(NAME)

$(LIB) :
		make -C $(LIB_PATH)

$(NAME) : $(OBJ_DIR) $(NAME_SERVER) $(NAME_CLIENT) Makefile

$(OBJ_DIR) :
		@mkdir -p $(OBJ_DIR)

$(NAME_SERVER) : $(OBJ_SERVER)
		$(CC) $(CFLAGS) $(INC) $(OBJ_SERVER) -o $(NAME_SERVER) $(LIB)

$(NAME_CLIENT) : $(OBJ_CLIENT)
		$(CC) $(CFLAGS) $(INC) $(OBJ_CLIENT) -o $(NAME_CLIENT) $(LIB)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus : all $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS) : $(OBJ_SERVER_BONUS)
		$(CC) $(CFLAGS) $(INC) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS) $(LIB)

$(NAME_CLIENT_BONUS) : $(OBJ_CLIENT_BONUS)
		$(CC) $(CFLAGS) $(INC) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS) $(LIB)

norm :
	norminette libft inc src

clean :
		@make -C $(LIB_PATH) fclean
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re : fclean all

.PHONY: all clean fclean re bonus norm
