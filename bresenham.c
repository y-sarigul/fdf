/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:13:56 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:28:13 by msarigul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color(t_z *z)
{
	int	d;

	if (abs(z->z2) > abs(z->z1))
		d = abs(z->z2);
	else
		d = abs(z->z1);
	if (d <= 0)
		z->color = 0x3264B8;
	else if (d > 0 && d <= 10)
		z->color = 0x32B864;
	else if (d > 10 && d <= 20)
		z->color = 0x96C896;
	else if (d > 20 && d <= 50)
		z->color = 0xFAFAC8;
	else if (d > 50 && d <= 70)
		z->color = 0x966450;
	else if (d > 70)
		z->color = 0xEFEFEF;
	return (z->color);
}

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx)
{
	p1->x = (p1->x - (mlx->map->width / 2)) * mlx->map->zoom;
	p2->x = (p2->x - (mlx->map->width / 2)) * mlx->map->zoom;
	p1->y = (p1->y - (mlx->map->height / 2)) * mlx->map->zoom;
	p2->y = (p2->y - (mlx->map->height / 2)) * mlx->map->zoom;
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	int		x_calc;
	int		y_calc;

	x_calc = x + mlx->map->offset_x;
	y_calc = y + mlx->map->offset_y;
	if (x_calc >= 0 && y_calc >= 0 && x_calc < WIN_WIDTH && y_calc < WIN_HEIGHT)
	{
		dst = mlx->addr + (y_calc * mlx->line_length + x_calc
				* (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	init_coordinates(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx)
{
	z->z1 = -mlx->map->lines[p1->y][p1->x] * mlx->map->raise_z;
	z->z2 = -mlx->map->lines[p2->y][p2->x] * mlx->map->raise_z;
	color(z);
	zoom(p1, p2, mlx);
	rotate_x(p1, p2, z, mlx->map->angles->x_angle);
	rotate_y(p1, p2, z, mlx->map->angles->y_angle);
	rotate_z(p1, p2, z, mlx->map->angles->z_angle);
	if (mlx->map->projection == 1)
		apply_iso(p1, p2, z);
}

void	bresenham(t_p p1, t_p p2, t_mlx *mlx)
{
	t_z	z;
	t_p	delta;
	int	err;
	int	e2;

	init_coordinates(&p1, &p2, &z, mlx);
	delta = point(abs(p1.x - p2.x), abs(p1.y - p2.y));
	err = err_calculation(&delta);
	while (1)
	{
		my_mlx_pixel_put(mlx, p1.x, p1.y, z.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err;
		if (e2 > -delta.x)
		{
			err -= delta.y;
			p1.x += (p1.x < p2.x) - (p1.x >= p2.x);
		}
		if (e2 < delta.y)
		{
			err += delta.x;
			p1.y += (p1.y < p2.y) - (p1.y >= p2.y);
		}
	}
}
