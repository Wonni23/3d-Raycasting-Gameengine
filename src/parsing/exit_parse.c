/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:12:10 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/06 14:18:12 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_parse(t_cub *cub, int status, char *str, t_parse *parse)
{
	if (parse->file)
		free_matrix((void **)parse->file);
	if (parse->path_to_img)
		free_matrix((void **)parse->path_to_img);
	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (cub)
	{
		if (cub->map.map)
			free_matrix((void **)cub->map.map);
	}
	exit(status);
}
