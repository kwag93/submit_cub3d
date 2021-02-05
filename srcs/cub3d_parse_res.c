/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse_res.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:51:04 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:20:47 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char		*read_file(const char *path)
{
	int		file_fd;
	char	*line;
	char	*result;
	char	*tempstr;

	if (!(result = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	if ((file_fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	result[0] = '\0';
	while (get_next_line(file_fd, &line) > 0 || *line)
	{
		tempstr = ft_strjoin(result, line);
		free(result);
		result = ft_strjoin(tempstr, "\n");
		free(tempstr);
		free(line);
	}
	close(file_fd);
	free(line);
	return (result);
}

int			convert_to_number(t_map **map, char *str, t_bool is_x)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + (str[i++] - '0');
	}
	if (is_x)
		(*map)->sizex = number;
	else
		(*map)->sizey = number;
	return (i);
}

void		check_resolution(t_map **map, char *str, int idx)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str || !ft_strchr("R", str[i]) || idx != 0)
		print_error("Resolution Error");
	i = i + 1;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		print_error("Resolution Error");
	i += convert_to_number(map, &str[i], TRUE);
	if (str[i] != ' ')
		print_error("Resolution Error");
	while (str[i] == ' ')
		i++;
	i += convert_to_number(map, &str[i], FALSE);
	while (str[i] == ' ')
		i++;
	if ((str[i] != ' ') && (str[i] != '\0'))
		print_error("Resolution Error");
}
