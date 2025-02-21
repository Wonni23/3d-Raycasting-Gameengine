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

int	memory_clean_exit(t_cub *cub)
{
	if (cub->img.sprites)
		free_matrix((void ***)&cub->img.sprites);
	if (cub->img.door)
		free(cub->img.door);
	free(cub->img.data);
	free_matrix((void ***)&cub->img.walls);
	free_matrix((void ***)&cub->map.map);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
	return (1);
}
