# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkwaghybkwagtudent.42                +#    +  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/07 16:01:28 by hyunyoo           #+#    #+#              #
#    Updated: 2021/02/05 11:24:27 by bkwag h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.c \
					includes/get_next_line/get_next_line.c \
					includes/get_next_line/get_next_line_utils.c \
					srcs/cub3d_bmp.c srcs/cub3d_character.c\
					srcs/cub3d_draw_wall.c srcs/cub3d_init_utils.c \
					srcs/cub3d_minimap.c srcs/cub3d_parse_res.c\
					srcs/cub3d_parse.c srcs/cub3d_print_error.c \
					srcs/cub3d_queue.c srcs/cub3d_queue_util.c\
					srcs/cub3d_raycast.c srcs/cub3d_sprite.c \
					srcs/cub3d_texture.c srcs/cub3d_utils.c\
					srcs/cub3d_utils2.c srcs/cub3d_raycast_utils.c \
					srcs/cub3d_character_util.c \

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -ggdb
LIBS			= -L. -lmlx -framework OpenGL -framework Metal -framework AppKit -lm ./Libft/libft.a
MLX				= libmlx.dylib
LIBFT			= libft.a

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(LIBFT) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
				
$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .
$(LIBFT):
				@$(MAKE) -C Libft
clean:
				@$(MAKE) -C mlx clean
				@$(MAKE) -C Libft clean
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)
				@$(MAKE) fclean -C Libft 

re:				fclean $(NAME)

bonus:			$(NAME)

.PHONY:			all clean fclean re bonus