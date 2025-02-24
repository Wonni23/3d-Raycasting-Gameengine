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

#include "../../include/cub3d.h"

void	free_array(char *array)
{
	if (!array)
		return ;
	free(array);
	array = NULL;
	array = NULL;
}

void	ft_exit(t_cub *cub, char **path, int status)
{
	if (status)
	{
		if (status == 1)
			printf("The map must closed by a wall\n");
		if (status == 2)
			printf("Empty space mut not exist in the map\n");
		free_matrix((void ***)&path);
		free_matrix((void ***)&cub->map.map);
		exit(1);
	}
	else
	{
		free_matrix((void ***)&path);
		free_matrix((void ***)&cub->map.map);
		exit(1);
	}
}

void	free_matrix(void ***matrix)
{
	int	i;

	if (!matrix || !(*matrix))
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_parse(t_parse *parse)
{
	if (parse->file)
		free_matrix((void ***)&parse->file);
	if (parse->path_to_img)
		free_matrix((void ***)&parse->path_to_img);
}

void	exit_parse(t_cub *cub, int status, char *str, t_parse *parse)
{
	if (parse)
		free_parse(parse);
	if (status)
		printf("Error: %s\n", str);
	else
		printf("%s\n", str);
	if (cub)
	{
		if (cub->map.map)
			free_matrix((void ***)&cub->map.map);
	}
	exit(status);
}
