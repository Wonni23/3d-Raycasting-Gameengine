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

#include "../../include/cub3d.h"

int	ft_mouse(int x, int y, t_cub *cub)
{
	int	mv_pos;

	mlx_mouse_hide(cub->mlx, cub->win);
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	mv_pos = x - (WIDTH / 2);
	if (abs(mv_pos) < 10)
		return (0);
	if (mv_pos > 0)
		rotate_right(cub);
	else
		rotate_left(cub);
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	loop(cub);
	return (0);
}

int	collide_door(t_cub *cub, double x, double y)
{
	if (cub->map.map[(int)(y + 0.5)][(int)(x + 0.5)] == '2' ||
		cub->map.map[(int)(y + 0.5)][(int)(x + 0.5)] == '3')
		return (1);
	if (cub->map.map[(int)(y - 0.5)][(int)(x - 0.5)] == '2' ||
		cub->map.map[(int)(y - 0.5)][(int)(x - 0.5)] == '3')
		return (2);
	if (cub->map.map[(int)(y + 0.5)][(int)(x - 0.5)] == '2' ||
		cub->map.map[(int)(y + 0.5)][(int)(x - 0.5)] == '3')
		return (3);
	if (cub->map.map[(int)(y - 0.5)][(int)(x + 0.5)] == '2' ||
		cub->map.map[(int)(y - 0.5)][(int)(x + 0.5)] == '3')
		return (4);
	return (0);
}

void	door_coordination(t_cub *cub, int *map_x, int *map_y, int res)
{
	if (res == 1)
	{
		*map_x = (int)(cub->player.pos_x + 0.5);
		*map_y = (int)(cub->player.pos_y + 0.5);
	}
	else if (res == 2)
	{
		*map_x = (int)(cub->player.pos_x - 0.5);
		*map_y = (int)(cub->player.pos_y - 0.5);
	}
	else if (res == 3)
	{
		*map_x = (int)(cub->player.pos_x - 0.5);
		*map_y = (int)(cub->player.pos_y + 0.5);
	}
	else
	{
		*map_x = (int)(cub->player.pos_x + 0.5);
		*map_y = (int)(cub->player.pos_y - 0.5);
	}
}

void	interact_door(t_cub *cub)
{
	int	res;
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	res = collide_door(cub, cub->player.pos_x, cub->player.pos_y);
	if (res < 1 || res > 4)
		return ;
	door_coordination(cub, &map_x, &map_y, res);
	if (cub->map.map[(int)cub->player.pos_y][(int)cub->player.pos_x] != '2' && \
	cub->map.map[(int)cub->player.pos_y][(int)cub->player.pos_x] != '3')
	{
		if (cub->map.map[map_y][map_x] == '2')
			cub->map.map[map_y][map_x] = '3';
		else if (cub->map.map[map_y][map_x] == '3')
			cub->map.map[map_y][map_x] = '2';
	}
}

int	keypress_hook(int key_code, t_cub *cub)
{
	printf("%d\n", key_code);
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
	}
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
								&cub->img.line_size, &cub->img.endian);
	// keypress_hook(key_code, cub);
	paint_background(cub);
	raycasting(cub);
	paint_minimap(cub);
	paint_img(cub);
	return (0);
}

void	boot(t_cub *cub)
{
	//if (cub->img.img != NULL)
	//{
	//	mlx_destroy_image(cub->mlx, cub->img.img);
	//	cub->img.img = NULL;
	//}
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
								&cub->img.line_size, &cub->img.endian);
	paint_background(cub);
	raycasting(cub);
	paint_minimap(cub);
	paint_img(cub);
}
