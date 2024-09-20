/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:52:48 by lmoran            #+#    #+#             */
/*   Updated: 2024/09/20 17:55:46 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void img_set(t_mlx *mlx, t_image *img, int height, int width)
{
	img->img = 0;
	img->width = 0;
	img->height = 0;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
	img->pixels = 0;
	img->instances = 0;

	img->img = mlx_new_image(mlx->mlx_p, width, height);
	img->pixels = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, \
	&img->size_line, &img->endian);
}

void put_pixels(t_mlx *mlx, t_img *img, int x, int y)
{
	if ()
}

int	draw_map_pixel(void *ml) //new add
{
	t_mlx	*mlx;
	t_image image;
	int x = 0;
	int y = 0;

	mlx = ml;
	image.img = NULL;
	img_set(mlx, &image, S_H, S_W);
	y = 0;
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			
		}
	}
	handle_ply_movement(mlx, 0, 0);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->tex->no_img->img, 0, 0);
	return (1);
}

t_texture *init_tex()
{
	t_texture *tex;

	tex = malloc(sizeof(t_texture));
	tex->no_img = 0;
	tex->so_img = 0;
	tex->ea_img = 0;
	tex->we_img = 0;
	tex->no_img = malloc(sizeof(t_image));
	tex->so_img = malloc(sizeof(t_image));
	tex->ea_img = malloc(sizeof(t_image));
	tex->we_img = malloc(sizeof(t_image));
	tex->no_img->height = 512;
	tex->so_img->height = 512;
	tex->ea_img->height = 512;
	tex->we_img->height = 512;
	tex->no_img->width = 512;
	tex->so_img->width = 512;
	tex->ea_img->width = 512;
	tex->we_img->width = 512;
	tex->no_img->instances = malloc(sizeof(t_instance));
	tex->so_img->instances = malloc(sizeof(t_instance));
	tex->ea_img->instances = malloc(sizeof(t_instance));
	tex->we_img->instances = malloc(sizeof(t_instance));
	return (tex);
}

void	cub_three_d(char **av)
{
	t_mlx	*game;

	game = init_mlx();
	game->tex = init_tex();
	game->data = init_data(av);
	if (!game->data)
		free_mlx(game, 1);
	set_mlx_images(game);
	game->ray = init_ray();
	game->ply = init_player(game->data);
	if (!game || !game->data)
		return ;
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx_p, draw_map_pixel, game);
	ft_printf("here");
	mlx_loop(game->mlx_p);
	ft_exit(game);
}

int	main(int ac, char **av)
{
	if ((ac != 2 || !is_cub(av[1])))
		return (ft_printf("Argument error: format: ./cub3d map.cub\n"), 0);
	cub_three_d(av);
	return (0);
}
