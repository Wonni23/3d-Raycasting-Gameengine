/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:09:47 by donjung           #+#    #+#             */
/*   Updated: 2024/04/23 12:28:10 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void)argc;
	(void)argv;
	//if (argc != 2)
	//{
	//	printf("Error\nThere must be only two files.\n");
	//	return (0);
	//}
	//parse(&cub);
	initialization(&cub);
	
	mlx_loop_hook(cub.mlx, loop, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_RELEASE, 1L << 1, keypress_hook, &cub);
	//mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, memory_clean_exit, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
