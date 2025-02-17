/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:09:47 by donjung           #+#    #+#             */
/*   Updated: 2025/02/06 14:49:31 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

// void	print_map(t_map *map)
// {
// 	if (!map || !map->map)
// 	{
// 		printf("Error: Map is NULL\n");
// 		return ;
// 	}

// 	printf("\n=== MAP INFO ===\n");
// 	printf("Width: %d\nHeight: %d\n\n", map->map_width, map->map_height);

// 	for (int i = 0; i < map->map_height; i++)
// 	{
// 		if (!map->map[i])
// 		{
// 			printf("Row %d: NULL\n", i);
// 			continue ;
// 		}
		
// 		printf("Row %02d: [", i);
// 		for (int j = 0; j < map->map_width; j++)
// 		{
// 			if (j > 0)
// 				printf(" ");
// 			printf("%c", map->map[i][j]);
// 		}
// 		printf("]\n");
// 	}
// 	printf("\n");
// }

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		printf("Error\nThere must be only two files.\n");
		return (0);
	}
	parse(&cub, argv[1]);
	initialization(&cub);
	// printf("map w, h: %d, %d", cub.map.map_width, cub.map.map_height); //debug
	// print_map(&cub.map); //debug
	//mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, memory_clean_exit, &cub);
	boot(&cub);
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 1L << 0, keypress_hook, &cub);
	mlx_hook(cub.win, 6, 1L << 6, ft_mouse, &cub);
	mlx_loop_hook(cub.mlx, loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
