/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:40:04 by bkwag             #+#    #+#             */
/*   Updated: 2021/02/05 19:04:36 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_texture(t_window *win, t_map **map, char *str, int idx)
{
	char	**split_str;
	t_img	tempimg;

	split_str = ft_split(str, ' ');
	if (!ft_strchr("NEWS", split_str[0][0]))
		print_error("Direction Error.");
	if (!split_str[1] || !(*split_str[1]) || (split_str[2] && *split_str[2]))
		print_error("Can not find data");
	if (idx == 1 && !ft_strncmp(split_str[0], "NO", 3))
		load_image(win, &(*map)->no_texture, ft_strdup(split_str[1]), &tempimg);
	else if (idx == 2 && !ft_strncmp(split_str[0], "SO", 3))
		load_image(win, &(*map)->so_texture, ft_strdup(split_str[1]), &tempimg);
	else if (idx == 3 && !ft_strncmp(split_str[0], "WE", 3))
		load_image(win, &(*map)->we_texture, ft_strdup(split_str[1]), &tempimg);
	else if (idx == 4 && !ft_strncmp(split_str[0], "EA", 3))
		load_image(win, &(*map)->ea_texture, ft_strdup(split_str[1]), &tempimg);
	else if (idx == 5 && !ft_strncmp(split_str[0], "S", 2))
		load_image(win, &(*map)->sprite_texture,
		ft_strdup(split_str[1]), &tempimg);
	else
		print_error("Form Error");
	str_free(split_str);
}

void		check_parse_f(t_map *map, char **color)
{
	int		i;
	int		j;

	i = 0;
	if (!color || !(*color))
		print_error("No color");
	while (color[i])
		i++;
	if (i != 3)
		print_error("Invalid .cub file; Given color not valid");
	if (map->floor_color)
		print_error("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			print_error("Invalid .cub file; check floor color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				print_error("Invalid .cub file; check floor color");
		}
		map->floor_color = map->floor_color * 256 + ft_atoi(color[i++]);
	}
}

void		check_parse_c(t_map *map, char **color)
{
	int		i;
	int		j;

	i = 0;
	if (!color || !(*color))
		print_error("No color");
	while (color[i])
		i++;
	if (i != 3)
		print_error("Invalid .cub file; Given color not valid");
	if (map->ceiling_color)
		print_error("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			print_error("Invalid .cub file; check ceiling color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				print_error("Invalid .cub file; check ceiling color");
		}
		map->ceiling_color = map->ceiling_color * 256 + ft_atoi(color[i++]);
	}
}

void		check_cub_file(t_window *win, t_map **map, char *str, int idx)
{
	char **tmp;
	char **color;

	tmp = ft_split(str, ' ');
	color = ft_split(tmp[1], ',');
	if (idx == 0)
		check_resolution(map, str, idx);
	else if (idx >= 1 && idx <= 5)
		check_texture(win, map, str, idx);
	else if (idx == 6)
	{
		if (ft_strncmp(tmp[0], "F", 2) || (tmp[1] && tmp[2] && *(tmp[2])))
			print_error("Form Error : Floor Color");
		check_parse_f(*map, color);
	}
	else if (idx == 7)
	{
		if (ft_strncmp(tmp[0], "C", 2) || (tmp[1] && tmp[2] && *(tmp[2])))
			print_error("Form Error : Ceiling Color");
		check_parse_c(*map, color);
	}
	str_free(color);
	str_free(tmp);
}

void		parse_cub_file(t_window *window, char *file_path)
{
	char	*file_str;
	char	**split_str;
	int		str_idx;

	str_idx = 0;
	init_map(window);
	if (!(file_str = read_file(file_path)))
		print_error("Cannot read file.");
	split_str = ft_split(file_str, '\n');
	parse_info(window, split_str, &str_idx);
	if (!(window->map->map =
	init_worldmap(window->map->m_size_x, window->map->m_size_y)))
		print_error("Cannot init worldmap data.");
	if (!(window->charac = parse_character(split_str, str_idx)))
		print_error("Fail parse character.");
	parse_map(split_str, str_idx, window->map);
	if (!(window->map->sprites =
		(t_sprite *)malloc(sizeof(t_sprite) * window->map->sp_cnt)))
		print_error("Malloc error");
	parse_sprites(split_str, str_idx, window->map);
	str_free(split_str);
	free(file_str);
}
