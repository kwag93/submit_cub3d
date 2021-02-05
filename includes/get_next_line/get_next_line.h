/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:48:13 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/01/09 15:03:51 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

int					ft_strlen_gnl(char *str);
int					check_newline(char *backup);
int					split_line(char **backup, char **line, int newline_idx);
int					return_all(char **backup, char **line, int r_size);
int					get_next_line(int fd, char **line);
char				*ft_strdup_gnl(char *s1);
char				*ft_strjoin_gnl(char *s1, char *s2);

#endif
