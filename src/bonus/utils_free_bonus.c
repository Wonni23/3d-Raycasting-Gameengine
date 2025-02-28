/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:44:57 by donjung           #+#    #+#             */
/*   Updated: 2025/02/04 18:44:58 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clean_int_array(int **arr, int idx)
{
	int	i;

	i = 0;
	if (!arr || !arr[0])
		return ;
	while (i < idx)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	memory_clean_imgs(t_cub *cub)
{
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->img.walls)
		clean_int_array(cub->img.walls, 4);
	if (cub->img.sprites)
		clean_int_array(cub->img.sprites, 5);
	if (cub->img.door)
		free(cub->img.door);
	if (cub->img.enemy)
		clean_int_array(cub->img.enemy, 3);
}

int	memory_clean_exit_bonus(t_cub *cub, char **path, int status, char *msg)
{
	if (msg)
		printf("Error\n%s\n", msg);
	if (path)
		free_matrix((void ***)&path);
	memory_clean_imgs(cub);
	if (cub->map.map)
		free_matrix((void ***)&cub->map.map);
	if (cub->zbuffer)
		free(cub->zbuffer);
	if (cub->mlx && cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit(status);
	return (1);
}
