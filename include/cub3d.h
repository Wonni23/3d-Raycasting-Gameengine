/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:45:15 by donjung           #+#    #+#             */
/*   Updated: 2025/01/21 20:07:58 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
//# include <sys/time.h>
# include <math.h>
# include <string.h>

# include "minilibx-linux/mlx.h"
# include "libft/include/libft.h"

# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

# define N 0
# define E 1
# define S 2
# define W 3

# define WALL_X 6
# define WALL_Y 9

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define WIDTH 640
# define HEIGHT 480

# define FRAME_RATE 60
# define TBD 69

typedef struct s_ray {
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_texturing {
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_side;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_texturing;

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			line_size;
	int			endian;
	int			w;
	int			h;
	int			buffer[HEIGHT][WIDTH];
	int			**wallimgs;
}	t_img;

typedef struct s_player
{
	int			status;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_map
{
	char		map[10][10]; // debug, should be **map
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor;
	int			ceiling;
	int			map_width;
	int			map_height;
	//int			mcount;
	//int			start;
	//int			ret;
}	t_map;

typedef struct s_cub {
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
}	t_cub;

/* initializing */
void	initialization(t_cub *cub);

/* Parsing */
int		init_image(t_img *img);
void	load_image(t_cub *cub);

/* Mlx related */
int		keypress_hook(int key_code, t_cub *cub);

/* Rendering */
int		loop(t_cub *cub);
void	raycasting(t_cub *cub);

/* Painting */
void	paint_background(t_cub *cub);
void	paint_img(t_cub *cub);

/* Utils */
void	ft_exit(char *msg);

#endif
