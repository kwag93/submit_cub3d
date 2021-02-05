/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:56:25 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:20:37 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_window *win, t_texture **texture, char *path, t_img *img)
{
	int y;
	int x;

	y = 0;
	if (!((*texture) = (t_texture *)malloc(sizeof(t_texture))))
		print_error("Cannot malloc data");
	if (!(img->img_ptr = mlx_xpm_file_to_image(win->mlx, path,
	&((*texture)->tex_width), &((*texture)->tex_height))) ||
	!((*texture)->data = (int *)malloc(sizeof(int) *
	(*texture)->tex_width * (*texture)->tex_height)))
		print_error("Cannot find img file");
	img->data = (int *)mlx_get_data_addr(img->img_ptr,
	&img->bpp, &img->size_l, &img->endian);
	while (y < (*texture)->tex_height)
	{
		x = -1;
		while (++x < (*texture)->tex_width)
		{
			(*texture)->data[(*texture)->tex_width * y + x] =
			img->data[img->size_l / 4 * y + x];
		}
		y++;
	}
	free(path);
	mlx_destroy_image(win->mlx, img->img_ptr);
}

void	draw_ray(t_img *img, t_character *cha, double x2, double y2)
{
	double	deltax;
	double	deltay;
	double	step;
	double	x1;
	double	y1;

	x1 = cha->pos_x;
	y1 = cha->pos_y;
	deltax = x2 - x1;
	deltay = y2 - y1;
	step = (fabs(deltax) > fabs(deltay)) ? fabs(deltax) : fabs(deltay);
	deltax /= step;
	deltay /= step;
	while (fabs(x2 - x1) >= fabs(deltax + 0.00000001) ||
	fabs(y2 - y1) >= fabs(deltay + 0.00000001))
	{
		img->data[((int)floor(y1) * img->size_l / 4) +
		(int)floor(x1)] = 0xb3b3b3;
		x1 += deltax;
		y1 += deltay;
	}
	img->data[((int)floor(y1) * img->size_l / 4) +
	(int)floor(x1)] = 0xb3b3b3;
}
