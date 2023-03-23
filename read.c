/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:14:28 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:14:30 by msarigul         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(const int fd, t_map *map)
{
	char	*line;
	char	**splitted_line;
	int		width;

	width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		splitted_line = ft_split(line, ' ');
		if (!splitted_line)
			exit_program(READ_MAP_ERROR);
		width = count_words(line, ' ');
		free(line);
		if (!fill_struct(splitted_line, width, map))
			exit_program(READ_MAP_ERROR);
		line = get_next_line(fd);
	}
}

void	increase_capacity(t_map *map)
{
	int	**new_lines;

	map->lines_capacity = map->lines_capacity * 2;
	new_lines = malloc(sizeof(int *) * map->lines_capacity);
	if (!new_lines)
		exit_program(MALLOC_ERROR);
	ft_memcpy(new_lines, map->lines, map->height * sizeof(int *));
	free(map->lines);
	map->lines = new_lines;
}

int	fill_struct(char **splitted_line, int width, t_map *map)
{
	int	*int_line;
	int	i;

	i = -1;
	if (!map->width)
		map->width = width;
	else if (width != map->width)
		return (0);
	int_line = malloc(sizeof(int) * (width));
	if (!int_line)
		return (0);
	while (++i < width)
	{
		int_line[i] = ft_atoi(splitted_line[i]);
		free(splitted_line[i]);
	}
	free(splitted_line);
	if (map->height == map->lines_capacity)
		increase_capacity(map);
	map->lines[map->height++] = int_line;
	return (1);
}
