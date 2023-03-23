/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:23:57 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:24:00 by msarigul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		exit_program(MALLOC_ERROR);
	map->angles = malloc(sizeof(t_angle));
	map->angles->x_angle = 0;
	map->angles->y_angle = 0;
	map->angles->z_angle = 0;
	map->width = 0;
	map->height = 0;
	map->lines_capacity = 16;
	map->offset_x = WIN_WIDTH / 2;
	map->offset_y = WIN_HEIGHT / 2;
	map->raise_z = 1;
	map->projection = 1;
	map->lines = malloc(sizeof(int *) * map->lines_capacity);
	if (!map->lines)
		exit_program(MALLOC_ERROR);
	return (map);
}

t_mlx	*init_mlx(t_map *map)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		exit_program(MLX_ERROR);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_program(MLX_ERROR);
	mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	if (!mlx->window)
		exit_program(MLX_ERROR);
	mlx->mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (!mlx->mouse)
		exit_program(MALLOC_ERROR);
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->mouse->onclick = 0;
	mlx->map = map;
	mlx->map->zoom = WIN_WIDTH / (mlx->map->width + mlx->map->height);
	return (mlx);
}
