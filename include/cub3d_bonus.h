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

# define X_EVENT_MOUSE_MOVE 6
# define KEY_E 101

/* SC: Scale, SZ: tilesize, K ~ RD: color */

/* Bonus */
void	init_status(t_cub *cub);
void	paint_minimap(t_cub *cub);
void	load_door(t_cub *cub);

int		ft_mouse(int x, int y, t_cub *cub);

int		ft_click(int button, int x, int y, void *param);

int		init_sprite(t_cub *cub);
void	load_sprite_image(t_cub *cub);

void	paint_sprite(t_cub *cub, int idx);

#endif
