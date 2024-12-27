#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512

static void error(void)
{
    puts(mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

int32_t main(void)
{
    // Inicializar MLX
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Prueba Textura", true);
    if (!mlx)
        error();

    // Cargar la imagen XPM42
    xpm_t* xpm = mlx_load_xpm42("textures/wood.xpm42");
    if (!xpm)
        error();

    // Convertir la textura a imagen
    mlx_image_t* img = mlx_texture_to_image(mlx, &xpm->texture);
    if (!img)
        error();

    // Cambiar el tamaño de la imagen
    if (!mlx_resize_image(img, WIDTH, HEIGHT))
        error();

    // Mostrar la imagen en la ventana
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

    // Bucle principal
    mlx_loop(mlx);

    // Limpiar
    mlx_delete_image(mlx, img);
    mlx_delete_xpm42(xpm);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}