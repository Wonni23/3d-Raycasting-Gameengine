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

#include "../../include/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		printf("Error\nThere must be only two files.\n");
		return (1);
	}
	init_status(&cub);
	parse(&cub, argv[1]);
	init_player(&cub.player);
	boot(&cub);
	mlx_hook(cub.win, X_EVENT_KEY_EXIT, 0, memory_clean_exit_bonus, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 1L << 0, keypress_hook, &cub);
	mlx_hook(cub.win, X_EVENT_MOUSE_MOVE, 1L << 6, ft_mouse, &cub);
	mlx_mouse_hook(cub.win, ft_click, &cub);
	mlx_loop_hook(cub.mlx, sprite, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
