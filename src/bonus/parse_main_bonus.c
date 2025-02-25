/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:10:10 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/05 23:40:26 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static char	**read_file(char **map, int fd, int counter)
{
	char	*str;

	str = get_next_line(fd);
	if (str)
		map = read_file(map, fd, 1 + counter);
	else if (!map && counter != 0)
		map = ft_calloc(counter + 1, sizeof(char *));
	if (!map)
		return (NULL);
	map[counter] = str;
	return (map);
}

static int	open_file(t_cub *cub, char *name, t_parse *parse)
{
	int	fd;

	fd = open(name, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit_parse(cub, 1, \
		"The argument passed must not be a directory", parse);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit_parse(cub, 1, "The argument passed must exist", parse);
	return (fd);
}

static void	check_image_exist(t_cub *cub, char **path)
{
	int	i;
	int	fd;

	i = -1;
	while (path[++i])
	{
		fd = open(path[i], O_RDONLY);
		if (fd == -1)
		{
			printf("Error\nThe argument passed must exist\n");
			free_matrix((void ***)&path);
			free_matrix((void ***)&cub->map.map);
			exit(1);
		}
	}
}

char	**parse_main(t_cub *cub, char *name)
{
	t_parse	parse;
	char	**path;
	int		fd;

	parse.file = NULL;
	parse.path_to_img = NULL;
	parse.num_vars = -1;
	if (ft_strcmp(ft_strrchr(name, '.'), ".cub"))
		exit_parse(NULL, 1, "The argument must end with .cub", &parse);
	fd = open_file(cub, name, &parse);
	parse.file = read_file(NULL, fd, 0);
	close(fd);
	if (!parse.file)
		exit_parse(cub, 1, "The file must not be empty", &parse);
	parse_file(cub, &parse);
	path = parse.path_to_img;
	parse.path_to_img = NULL;
	if (parse.file)
		free_matrix((void ***)&parse.file);
	return (path);
}

void	parse(t_cub *cub, char *name)
{
	char	**path;

	path = parse_main(cub, name);
	check_image_exist(cub, path);
	check_map(cub, path);
	init_mlx(cub);
	init_image(&cub->img);
	load_image(cub, path);
	init_sprite(cub);
	load_sprite_image(cub);
	load_door(cub);
	free_matrix((void ***)&path);
}
