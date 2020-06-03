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

NAME=ft_traceroute
DEBUG_NAME=ft_traceroutedbg

CC=clang

PATH_LIB=libft/

LIBFT= $(PATH_LIB)libft.a
LIBFTDB= $(PATH_LIB)libftdb.a

CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -Werror

DBFLAGS += $(CFLAGS)
DBFLAGS += -fsanitize=address,undefined
DBFLAGS += -ggdb3

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

vpath %.c $(PATH_SRCS)

#----------------------------------- OBJECTS ----------------------------------#

PATH_OBJS = objs/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

DEBUG_PATH_OBJS = objs_debug/
DEBUG_OBJS = $(patsubst %.c, $(DEBUG_PATH_OBJS)%.o, $(SRCS))


#---------------------------------- THA RULES ---------------------------------#

all: $(PATH_OBJS) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(I_INCLUDES) $(OBJS) $(LIBFT) -o $@
	printf "$@ is ready.\n"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(I_INCLUDES) -c $< -o $@

$(PATH_OBJS):
	mkdir $@

$(LIBFT): FORCE 
	$(MAKE) -C $(PATH_LIB)

#---------------------------------- DEBUGGING ---------------------------------#


debug: $(DEBUG_PATH_OBJS) $(DEBUG_NAME)

$(DEBUG_NAME): $(LIBFTDB) $(DEBUG_OBJS)
	$(CC) $(DBFLAGS) $(I_INCLUDES) $(DEBUG_OBJS) $(LIBFTDB) -o $@
	printf "$@ is ready.\n"

$(DEBUG_OBJS): $(DEBUG_PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(DBFLAGS) $(I_INCLUDES) -c $< -o $@

$(DEBUG_PATH_OBJS):
	mkdir $@

$(LIBFTDB): FORCE
	$(MAKE) debug -C $(PATH_LIB)

#---------------------------------- CLEANING ----------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) $(DEBUG_OBJS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(DEBUG_PATH_OBJS)
	$(RM) -R $(DSYM)
	$(MAKE) -C $(PATH_LIB) clean
	printf "Objs from $(NAME) removed\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	$(MAKE) -C $(PATH_LIB) fclean
	printf "$(NAME) removed\n"

re: fclean all

FORCE:

#------------------------------------- MISC -----------------------------------#

.PHONY: clean fclean re all
.SILENT:
