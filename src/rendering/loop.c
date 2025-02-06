/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:34:37 by donjung           #+#    #+#             */
/*   Updated: 2025/01/26 19:04:49 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	keypress_hook(int key_code, t_cub *cub)
{
	if (key_code == KEY_W)
		move_w(cub);
	else if (key_code == KEY_A)
		move_a(cub);
	else if (key_code == KEY_S)
		move_s(cub);
	else if (key_code == KEY_D)
		move_d(cub);
	else if (key_code == KEY_LEFT)
		rotate_left(cub);
	else if (key_code == KEY_RIGHT)
		rotate_right(cub);
	else if (key_code == KEY_ESC)
	{
		printf("Exiting cub3D.\n");
		//memory_clean_exit
		exit(0);
	}
	return (0);
}

int	loop(t_cub *cub)
{
	if (cub->img.img)
	{
		mlx_destroy_image(cub->mlx, cub->img.img);
		cub->img.img = NULL;
	paint_background(cub);
	raycasting(cub);
	paint_img(cub);
	return (0);
}
