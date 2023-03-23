/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:14:20 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:14:22 by msarigul         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == MOUSE_SCROLLDOWN)
		mlx->map->zoom -= 1;
	else if (keycode == MOUSE_SCROLLUP)
		mlx->map->zoom += 1;
	else if (keycode == MOUSE_LEFT || keycode == MOUSE_RIGHT
		|| keycode == MOUSE_MIDDLE)
	{
		mlx->mouse->x = x;
		mlx->mouse->y = y;
		if (keycode == MOUSE_LEFT)
			mlx->mouse->onclick = 1;
		else if (keycode == MOUSE_RIGHT)
			mlx->mouse->onclick = 2;
		else if (keycode == MOUSE_MIDDLE)
			mlx->mouse->onclick = 3;
	}
	draw(mlx);
	return (0);
}

int	mouse_release(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (button == MOUSE_LEFT || button == MOUSE_RIGHT || button == MOUSE_MIDDLE)
		mlx->mouse->onclick = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	int	prev_x;
	int	prev_y;

	if (!mlx->mouse->onclick)
		return (0);
	prev_x = mlx->mouse->x;
	prev_y = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->onclick == 1)
	{
		mlx->map->offset_x += x - prev_x;
		mlx->map->offset_y += y - prev_y;
	}
	else if (mlx->mouse->onclick == 2)
	{
		mlx->map->angles->x_angle += (y - prev_y) / 360.0;
		mlx->map->angles->y_angle += (x - prev_x) / 360.0;
	}
	else if (mlx->mouse->onclick == 3)
		mlx->map->angles->z_angle += ((y - prev_y) + (x - prev_x)) / 360.0;
	draw(mlx);
	return (0);
}
