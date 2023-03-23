/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarigul <msarigul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:14:05 by msarigul          #+#    #+#             */
/*   Updated: 2023/03/23 00:26:30 by msarigul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "gnl/get_next_line.h"
# include "mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MLX_ERROR "MLX error."
# define IMG_ERROR "Image initialization error."
# define USAGE_ERROR "Usage: ./fdf <map_file>"
# define OPEN_MAP_ERROR "Failed to open a map."
# define INIT_MAP_ERROR "Failed to initialize a map."
# define READ_MAP_ERROR "Failed to read a map."
# define MALLOC_ERROR "Failed to allocate memory."

# define EVENT_ON_KEYDOWN 2
# define EVENT_ON_KEYUP 3
# define EVENT_ON_MOUSEDOWN 4
# define EVENT_ON_MOUSEUP 5
# define EVENT_ON_MOUSEMOVE 6
# define EVENT_ON_DESTROY 17
# define NO_MASK 0

# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SCROLLUP 4
# define MOUSE_SCROLLDOWN 5

# define KEY_ESC 53
// Offset X +-
# define KEY_ARROWLEFT 123
# define KEY_ARROWRIGHT 124
// Offset Y +-
# define KEY_ARROWUP 126
# define KEY_ARROWDOWN 125
// Rotate X-axis
# define KEY_W 13
# define KEY_S 1
// Rotate Y-axis
# define KEY_Q 12
# define KEY_E 14
// Rotate Z-axis
# define KEY_A 0
# define KEY_D 2
// Raise Z, Lower Z
# define KEY_Z 6
# define KEY_X 7

// Projection switch paralel, iso
# define KEY_ONE 18

typedef struct s_angle
{
	double		x_angle;
	double		y_angle;
	double		z_angle;
}				t_angle;

typedef struct s_map
{
	int			width;
	int			height;
	int			**lines;
	t_angle		*angles;
	int			lines_capacity;
	int			zoom;
	int			offset_x;
	int			offset_y;
	float		raise_z;
	int			projection;
}				t_map;

typedef struct s_mouse
{
	int			x;
	int			y;
	int			onclick;
}				t_mouse;

typedef struct s_z
{
	int			z1;
	int			z2;
	int			color;
}				t_z;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	t_mouse		*mouse;

}				t_mlx;

typedef struct s_p
{
	int			x;
	int			y;
}				t_p;

t_map			*init_map(void);
t_mlx			*init_mlx(t_map *map);

void			read_map(const int fd, t_map *map);
int				fill_struct(char **splitted_line, int width, t_map *map);

void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int				deal_key(int keycode, void *param);
int				escape(void *param);
void			keyboard_key(int keycode, t_mlx *mlx);
void			projection_key(int keycode, t_mlx *mlx);
void			rotate_x(t_p *p1, t_p *p2, t_z *z, double x_angle);
void			rotate_y(t_p *p1, t_p *p2, t_z *z, double x_angle);
void			rotate_z(t_p *p1, t_p *p2, t_z *z, double x_angle);
void			apply_iso(t_p *p1, t_p *p2, t_z *z);

void			setup_controls(t_mlx *mlx);

int				err_calculation(t_p *delta);
void			bresenham(t_p p1, t_p p2, t_mlx *mlx);
void			init_coordinates(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx);

void			zoom(t_p *p1, t_p *p2, t_mlx *mlx);
t_p				point(int x, int y);
void			draw(t_mlx *mlx);
int				color(t_z *z);

void			init_img(t_mlx *mlx);

int				mouse(int button, int x, int y, t_mlx *mlx);
int				mouse_move(int x, int y, t_mlx *mlx);
int				mouse_release(int button, int x, int y, t_mlx *mlx);

long int		ft_atoi(const char *str);
char			**ft_split(char const *str, char c);
unsigned int	count_words(const char *str, char sep);

void			exit_program(char *str);

#endif
