/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:10:48 by lmoran            #+#    #+#             */
/*   Updated: 2024/09/18 15:55:40 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# define M_PI 3.14159265358979323846
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <float.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAIL 0

// mouse
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// keyboard
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_I 34
# define KEY_O 31
# define KEY_P 35
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_FOWARD 126
# define KEY_BACKWARD 125

# define KEY_TAB 48
# define KEY_MAJ 257
# define KEY_ESC 53
# define KEY_TAB 48

// key press detect
# define KEY_RELEASE 0
# define KEY_PRESS 1
# define KEY_REPEAT 2

// colors
# define BLACK 0x000000FF
# define GREY 0x808080FF
# define BLUE 0x87CEEBFF
# define GREEN 0x008000FF
# define ORANGE 0xFF9300FF
# define RED 0xFF0000FF
# define WHITE 0xFFFFFFFF

// movement

# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define NO 1
# define SO 2
# define EA 3
# define WE 4

# define TILE_SIZE 30
# define FOV (60 * M_PI / 180) // field of view = 60
# define NUM_RAYS 320          // Number of rays to cast

typedef struct s_player // the player structure
{
	int ply_x; // player x position in pixels
	int ply_y; // player y position in pixels
	int rot;   // rotation flag(movement)
	int l_r;   // left right flag(movement)
	int u_d;   // up down flag(movement)
	double angle;
	float fov_radian;
}					t_player;

typedef struct s_file
{
	char			*s;
	struct s_file	*next;
}					t_file;

typedef struct s_data
{
	int				exit;
	int				map_w;
	int				map_h;
	int				p_x;
	int				p_y;
	char			*file;
	t_file			*linked_file;
	char			**map2d;
	char			**square_map;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
}					t_data;

typedef struct s_ray
{
	double		ray_angle;
	double 		distance; // distance to wall
	int			wall_flag;
	int 		index; // for rendering
}					t_ray;

// typedef struct s_texture
// {
// 	uint32_t	width;
// 	uint32_t	height;
// 	uint8_t		bytes_per_pixel;
// 	uint8_t*	pixels;
// }	t_texture;

typedef struct s_instance
{
	int32_t			x;
	int32_t			y;
	int32_t			z;
}					t_instance;

typedef struct s_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t			*pixels;
	t_instance		*instances;
}					t_image;

typedef struct s_texture
{
	t_image			*no_img;
	t_image			*so_img;
	t_image			*we_img;
	t_image			*ea_img;
}					t_texture;

typedef struct s_mlx // the mlx structure
{
	void 		*win;
	void 		*mlx_p;  // the mlx pointer
	t_ray 		*ray;    // the ray structure
	t_data 		*data;  // the data structure
	t_player	*ply; // the player structure
	t_image		*img;  // the image
	t_file		*file;
	t_texture *tex;
}					t_mlx;

typedef struct s_keydata
{
	int32_t			key;
	int32_t action; // key press detect
}					t_keydata;

// ! INITS
t_mlx				*init_mlx(void);
t_data				*init_data(char **av);
t_ray				*init_ray(void);
t_player			*init_player(t_data *data);

// ! MOVEMENT
void				rotate_view(t_mlx *mlx, int i);
void				ft_release(t_keydata keydata, t_mlx *mlx);
int					key_press(t_keydata keydata, void *ml);
void				move_player(t_mlx *mlx, double move_x, double move_y);
void				handle_ply_movement(t_mlx *mlx, double move_x, double move_y);
int					wall_hit(t_mlx *mlx, double x, double y);
int					check_direction(double angle, char c);

// ! PARSING
int					check_file(t_data *data);
int					check_map(char **map);
int					check_rgb(t_data *data, t_file *tmp, char c);
int					check_textures(t_data *data, t_file *file);

// ! RAYCASTING
void				cast_rays(t_mlx *mlx);
double				normalize_angle(double angle);
double				get_v_inter(t_mlx *mlx, double angle);
double				get_h_inter(t_mlx *mlx, double angle);
double				adjust_inter(double angle, double inter, double step,
						int h);

// ! RENDERING
void				rendering(t_mlx *mlx, int ray);
void				render_walls(t_mlx *mlx, double t_pixel, double b_pixel,
						double wall_h);
t_image				*get_texture(t_mlx *mlx, int wall_flag);
void				render_floor_ceiling(t_mlx *mlx, int ray, double t_pixel,
						double b_pixel);
void				new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

// ! UTILS
// * extension_utils
int					is_xpm(char *s);
int					is_cub(char *s);
int					is_png(char *s);

// * frees
void				free_file_list(t_file *file);
void				*free_during_init(t_data *data);
void				free_mlx(t_mlx *game, int exit_code);
void				ft_exit(t_mlx *mlx);

// * init_utils
char				**return_map(t_data *data);
int					count_lines(t_file *file);
t_file				*return_map_start(t_file *file);
int					check_if_map(char *s);

// * list_utils
void				add_to_list(t_file **lst, t_file *new);
void				string_to_list(t_data *data);

// * parse_utils
void				pr_str(t_file *f);
void				print_data(t_data *data);
void				print_textures(t_data *data, int i);

#endif
