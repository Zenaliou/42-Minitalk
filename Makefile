CLIENT			= client
SERVER			= server

LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR	= ./ft_printf
FT_PRINTF		= $(FT_PRINTF_DIR)/libftprintf.a

SRCS_CLIENT		= client.c
SRCS_SERVER		= server.c
OBJS_CLIENT		= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER		= $(SRCS_SERVER:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f

all:			$(LIBFT) $(FT_PRINTF) $(CLIENT) $(SERVER)

$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
				$(MAKE) -C $(FT_PRINTF_DIR)

$(CLIENT):		$(OBJS_CLIENT) $(LIBFT) $(FT_PRINTF)
				$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(CLIENT)

$(SERVER):		$(OBJS_SERVER) $(LIBFT) $(FT_PRINTF)
				$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(SERVER)

clean:
				$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
				$(MAKE) clean -C $(LIBFT_DIR)
				$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean:			clean
				$(RM) $(CLIENT) $(SERVER)
				$(MAKE) fclean -C $(LIBFT_DIR)
				$(MAKE) fclean -C $(FT_PRINTF_DIR)

re:				fclean all

.PHONY:			all clean fclean re
