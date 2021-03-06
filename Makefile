# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuppers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 13:04:10 by skuppers          #+#    #+#              #
#    Updated: 2020/02/15 13:10:12 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------- GENERAL -----------------------------------#

.SUFFIXES:

NAME=ft_traceroute
BONUS=ft_traceroute_bonus

CC=clang

PATH_LIB=libft/

LIBFT= $(PATH_LIB)libft.a

CFLAGS += -Wall
CFLAGS += -Wextra

# Compiler Debug Flags
ifeq ($(d), 0)
	CFLAGS += -g3
else ifeq ($(d), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
else ifeq ($(d), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
else ifeq ($(d), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
	CFLAGS += -Weverything
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif

# Debug Dir
DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM
#---------------------------------- INCLUDES ----------------------------------#

INCLUDES_LIBFT = $(PATH_LIB)includes/
INCLUDES_TRACEROUTE = includes/

I_INCLUDES += -I $(INCLUDES_LIBFT)
I_INCLUDES += -I $(INCLUDES_TRACEROUTE)

#---------------------------------- HEADERS -----------------------------------#

vpath %.h $(INCLUDES_LIBFT)
vpath %.h $(INCLUDES_TRACEROUTE)

HEADER += libft.h
HEADER += ft_traceroute.h

#----------------------------------- SOURCS -----------------------------------#

PATH_SRCS = src/

SRCS += main.c
SRCS += usage.c
SRCS += options.c
SRCS += resolve.c
SRCS += ft_traceroute.c
SRCS += socket.c
SRCS += utils.c
SRCS += display.c
SRCS += send.c
SRCS += receive.c
SRCS += option_tools.c

vpath %.c $(PATH_SRCS)

#----------------------------------- OBJECTS ----------------------------------#

PATH_OBJS = objs/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

PATH_OBJS_B = objs_b/
OBJS_BONUS = $(patsubst %.c, $(PATH_OBJS_B)%.o, $(SRCS))


#---------------------------------- THA RULES ---------------------------------#

all: $(PATH_OBJS) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(I_INCLUDES) $(OBJS) $(LIBFT) -o $@
	printf "$@ is ready.\n"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(I_INCLUDES) -c $< -o $@

$(PATH_OBJS):
	mkdir $@

bonus: $(PATH_OBJS_B) $(BONUS)

$(BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(I_INCLUDES) $(OBJS_BONUS) $(LIBFT) -o $@
	printf "$@ is ready.\n"

$(OBJS_BONUS): $(PATH_OBJS_B)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -DBONUS_H $(I_INCLUDES) -c $< -o $@

$(PATH_OBJS_B):
	mkdir $@

$(LIBFT): FORCE 
	$(MAKE) -C $(PATH_LIB)

#---------------------------------- CLEANING ----------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(PATH_OBJS_B)
	$(RM) -R $(DSYM)
	$(MAKE) -C $(PATH_LIB) clean
	printf "Objs from $(NAME) removed\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	$(MAKE) -C $(PATH_LIB) fclean
	printf "$(NAME) removed\n"

re: fclean all

FORCE:

#------------------------------------- MISC -----------------------------------#

.PHONY: clean fclean re all
.SILENT:
