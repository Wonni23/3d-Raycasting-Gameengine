/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:34:37 by donjung           #+#    #+#             */
/*   Updated: 2025/02/10 21:05:37 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
	else if (key_code == KEY_E)
		interact_door(cub);
	else if (key_code == KEY_ESC)
	{
		printf("Exiting cub3D.\n");
		memory_clean_exit(cub);
	}
	loop(cub);
	return (0);
}

int	loop(t_cub *cub)
{
	long long	curr_time;

	curr_time = get_current_time_micro();
	if (cub->anim_on)
	{
		if (curr_time - cub->anim_lasttime >= 50000)
		{
			cub->anim_frame++;
			cub->anim_lasttime = curr_time;
			if (cub->anim_frame >= 5)
				cub->anim_on = 0;
		}
	}
	paint_background(cub);
	raycasting(cub);
	paint_minimap(cub);
	if (cub->anim_on)
		paint_sprite(cub, cub->anim_frame);
	else
		paint_sprite(cub, 0);
	buffer_to_img_n_window(cub);
	return (0);
}

void	boot(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.line_size, &cub->img.endian);
	paint_background(cub);
	raycasting(cub);
	paint_minimap(cub);
	paint_sprite(cub, 0);
	buffer_to_img_n_window(cub);
}
