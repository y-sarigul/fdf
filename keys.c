/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:13:29 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:13:32 by msarigul         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	escape(void *param)
{
	(void)param;
	exit(0);
}

void	keyboard_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_Z)
		mlx->map->raise_z += 0.1;
	else if (keycode == KEY_X)
		mlx->map->raise_z -= 0.1;
	else if (keycode == KEY_A)
		mlx->map->angles->z_angle += 0.025;
	else if (keycode == KEY_D)
		mlx->map->angles->z_angle -= 0.025;
	else if (keycode == KEY_Q)
		mlx->map->angles->y_angle += 0.025;
	else if (keycode == KEY_E)
		mlx->map->angles->y_angle -= 0.025;
	else if (keycode == KEY_W)
		mlx->map->angles->x_angle += 0.025;
	else if (keycode == KEY_S)
		mlx->map->angles->x_angle -= 0.025;
}

void	projection_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ONE)
	{
		mlx->map->projection ^= 1;
		mlx->map->angles->x_angle = 0;
		mlx->map->angles->y_angle = 0;
		mlx->map->angles->z_angle = 0;
	}
	else if (keycode == KEY_ARROWUP)
		mlx->map->offset_y -= 16;
	else if (keycode == KEY_ARROWDOWN)
		mlx->map->offset_y += 16;
	else if (keycode == KEY_ARROWRIGHT)
		mlx->map->offset_x += 16;
	else if (keycode == KEY_ARROWLEFT)
		mlx->map->offset_x -= 16;
}

int	deal_key(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	keyboard_key(keycode, mlx);
	projection_key(keycode, mlx);
	draw(mlx);
	return (0);
}

void	setup_controls(t_mlx *mlx)
{
	mlx_hook(mlx->window, EVENT_ON_KEYDOWN, NO_MASK, deal_key, mlx);
	mlx_hook(mlx->window, EVENT_ON_DESTROY, NO_MASK, escape, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEDOWN, NO_MASK, mouse, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEMOVE, NO_MASK, mouse_move, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEUP, NO_MASK, mouse_release, mlx);
}
