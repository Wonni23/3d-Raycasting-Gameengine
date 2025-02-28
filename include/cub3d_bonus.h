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

# include "cub3d.h"

# define SC 1
# define SZ 8
# define K 0x000000
# define WT 0xffffff
# define B 0x005666
# define Y 0xF7E600
# define RD 0x760c0c

# define FPS 8333
# define X_EVENT_MOUSE_MOVE 6
# define KEY_E 101

/* SC: Scale, SZ: tilesize, K ~ RD: color */

/* Bonus */
void		init_status(t_cub *cub);
void		paint_minimap(t_cub *cub);
void		load_door(t_cub *cub, char **path);

int			collide_door(t_cub *cub, double x, double y);
void		door_coordination(t_cub *cub, int *map_x, int *map_y, int res);
void		interact_door(t_cub *cub);

int			ft_mouse(int x, int y, t_cub *cub);
int			ft_click(int button, int x, int y, void *param);
void		shoot_ray(t_cub *cub, char **map);

int			init_sprite(t_cub *cub);
void		load_sprite_image(t_cub *c, char **path);
void		paint_sprite(t_cub *cub, int idx);

int			sprite(t_cub *cub);

long long	get_current_time_micro(void);

int			memory_clean_exit_bonus(t_cub *cub, char **p, int stat, char *msg);

int			init_enemy(t_cub *cub);
void		load_enemy_image(t_cub *c, char **p_path);
void		render_enemy_sprites(t_cub *cub, double *zBuffer);

void		sort_sprites(t_sprite *sprites, int count);
void		fill_sprite_array(t_cub *cub, t_sprite *sprites, int *sprite_count);
void		transform_sprites(t_cub *cub, t_sprite *sprites, int count);
void		compute_sprite_projection(t_sprite *sprite);

#endif
