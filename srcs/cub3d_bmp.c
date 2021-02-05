/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:09:18 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 17:52:53 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void		write_bmp_header(t_window *window, int fd, int size)
{
	unsigned char		header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, window->map->sizex);
	set_int_in_char(header + 22, window->map->sizey);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void		write_data(t_window *window, int fd)
{
	int		*zero;
	int		i;
	int		j;
	int		pad;

	zero = (int[3]){0, 0, 0};
	i = window->map->sizey - 1;
	pad = (4 - (window->map->sizex * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < window->map->sizex)
		{
			write(fd, &(window->map->proj_img.data[i *
			window->map->proj_img.size_l / 4 + j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

void		save_bmp(t_window *window)
{
	int		fd;
	int		size;

	size = 54 + 3 * window->map->sizex * window->map->sizey;
	if ((fd = open("./screenshot.bmp", O_WRONLY | O_CREAT |
						O_TRUNC | O_APPEND, 00755)) < 0)
		print_error("open error");
	write_bmp_header(window, fd, size);
	write_data(window, fd);
	close(fd);
}

void		bmp_mode(t_window *window, char *path)
{
	parse_cub_file(window, path);
	window->map->proj_img.img_ptr = img_init(window,
	window->map->sizex, window->map->sizey);
	window->map->proj_img.data =
	(int *)mlx_get_data_addr(window->map->proj_img.img_ptr,
	&window->map->proj_img.bpp, &window->map->proj_img.size_l,
	&window->map->proj_img.endian);
	draw_skyceil(window->map);
	raycast(window->map, window->charac);
	draw_sprite(window->charac, window->map);
	save_bmp(window);
	mlx_destroy_image(window->mlx, window->map->proj_img.img_ptr);
	exit(0);
}
