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

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include <string.h>

# include "minilibx-linux/mlx.h"
# include "libft/include/libft.h"

# define X_EVENT_KEY_PRESS	2
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
# define S 1
# define W 2
# define E 3

# define WALL_X 6
# define WALL_Y 9

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define WIDTH 1080
# define HEIGHT 720

# define FRAME_RATE 60
# define TBD 69

# define FLOOR 0
# define CEILING 1

# define MVSPEED 0.2
# define RTSPEED_R 0.05
# define RTSPEED_L -0.05

# define SC 1
# define SZ 8
# define K 0x000000
# define WT 0xffffff
# define B 0x005666
# define Y 0xF7E600
# define RD 0x760c0c

# define X_EVENT_MOUSE_MOVE 6
# define KEY_E 101

# define SPSIZE (WIDTH / 3)
# define SP_X (WIDTH - SPSIZE * 1.2)
# define SP_Y (HEIGHT - SPSIZE)

/* SC: Scale, SZ: tilesize, K ~ RD: color */

typedef struct s_parse
{
	char	**file;
	char	**path_to_img;
	int		num_vars;
}	t_parse;

typedef struct s_ray
{
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
	int		hit;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_texturing
{
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
	int			**walls;
	int			*door;
	int			**sprites;
	int			color_i;
	int			colors[2];
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
	char		**map;
	int			map_width;
	int			map_height;

}	t_map;

typedef struct s_cub {
	void		*mlx;
	void		*win;
	int			num_player;
	int			mouse_x;
	int			mouse_y;
	int			anim_on;
	int			anim_frame;
	long long	anim_lasttime;
	t_img		img;
	t_player	player;
	t_map		map;
}	t_cub;

/* initializing */
void	init_mlx(t_cub *cub);
void	init_player(t_player *player);
void	init_player_2(t_player *player);

/* Mlx related */
int		keypress_hook(int key_code, t_cub *cub);

/* Rendering */
void	boot(t_cub *cub);
int		loop(t_cub *cub);

/* Ray Casting */
void	setup_dda(t_cub *cub, t_ray *ray);
void	perform_dda(t_ray *ray, char **map);
void	raycasting(t_cub *cub);

/* Movements */
void	move_w(t_cub *cub);
void	move_s(t_cub *cub);
void	move_a(t_cub *cub);
void	move_d(t_cub *cub);
void	rotate_left(t_cub *cub);
void	rotate_right(t_cub *cub);

/* Painting */
void	paint_background(t_cub *cub);
void	buffer_to_img_n_window(t_cub *cub);

/* Utils */
void	err_exit(char *msg);
int		memory_clean_exit(t_cub *cub);

/* Parsing */
void	parse(t_cub *cub, char *argv);
char	**parse_main(t_cub *cub, char *name);
void	parse_file(t_cub *cub, t_parse *parse);
int		get_vars(t_cub *cub, t_parse *parse);
int		orientation_player(char c);
void	check_including_letter(t_parse *parse, char *s);
void	check_image_order(t_parse *parse, char *s);
void	check_map(t_cub *cub, char **path);
void	check_map_closed(t_cub *cub, char **path);
void	check_map_empty(t_cub *cub, char **path);
void	free_matrix(void ***matrix);
void	free_parse(t_parse *parse);
void	free_array(char *array);
void	exit_parse(t_cub *cub, int status, char *str, t_parse *parse);
void	ft_exit(t_cub *cub, char **path, int status);
int		init_image(t_img *img);
void	load_image(t_cub *cub, char **path_to_image);

/* Bonus */
void	paint_minimap(t_cub *cub);
void	load_door(t_cub *cub);

int		ft_mouse(int x, int y, t_cub *cub);

int		ft_click(int button, int x, int y, void *param);

int		init_sprite(t_img *img);
void	load_sprite_image(t_cub *cub);

void	paint_sprite(t_cub *cub, int idx);

#endif
