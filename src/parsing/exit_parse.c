/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:12:10 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/06 14:19:13 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_matrix(void **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	matrix = NULL;
}

void	free_parse(t_parse *parse)
{
	if (parse->file)
		free_matrix((void **)parse->file);
	if (parse->path_to_img)
		free_matrix((void **)parse->path_to_img);
}

void	exit_parse(t_cub *cub, int status, char *str, t_parse *parse)
{
	free_parse(parse);
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
