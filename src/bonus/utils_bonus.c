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

void	err_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	clean_int_array(int **arr, int idx)
{
	int	i;

	i = 0;
	while(i < idx)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	memory_clean_exit(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	clean_int_array(cub->img.walls, 4);
	clean_int_array(cub->img.sprites, 5);
	free(cub->img.door);
	free_matrix((void ***)&cub->map.map);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
	return (1);
}
