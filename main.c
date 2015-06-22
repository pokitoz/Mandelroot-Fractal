#define _GNU_SOURCE
#include "gfx.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Size of the window
#define WIDTH 1280
#define HEIGHT 960

int leave = 0; // Global int for exit master thread //

/**
 *   Struct of the parameters of the map
 *   @xc x position in the complex plane
 *   @yc y position in the complex plane
 *   @size size of the window in the complex plane
 *   @max_iter maximum number of iterations
 *   @dcol color increment (> 0)
 */
struct Params_st {
    double xc;
    double yc;
    double size;
    long max_iter;
    double dcol;
};
typedef struct Params_st Params_t;

/**
 *   Struct of the color_map
 *   @map 32 bit value of map
 *   @length int length of the map
 */
struct Colormap_st {
    uint32 *map;
    int length;
};
typedef struct Colormap_st Colormap_t;

/**
 *   Struct of paramateres for a thread worker
 *   @surface surface of working
 *   @colmap color_map
 *   @width_min Witdh_min for the working thread
 *   @width_max Witdh_max for the working thread
 *   @p p pointers on Params_t
 */
struct Param_worker {
    int blocks;
    double ratio;
    Params_t *p;
    SURFACE *surface;
    Colormap_t *colmap;
};
typedef struct Param_worker Param_worker;

typedef struct Bloc {
    int bloc_id;
    int width_min;
    int width_max;
} Bloc;

/** GLOBALE ALL THE THREADS CAN ACCESS THOSE DATA <3 !! */

Bloc* blocs = NULL;
int shared_index = 0;

pthread_mutex_t lock;

int getIndex(int blocks) {


    pthread_mutex_lock(&lock);
    int tmp = shared_index;
    if (shared_index < blocks) {
	printf("%d -- ", shared_index);	
	shared_index++;
	pthread_mutex_unlock(&lock);
        return tmp;
    }

    pthread_mutex_unlock(&lock);
    return tmp;
}

/*********************************************************/

/**
 *   Struct wich will be pass in parameter in the main thread
 *   @workers number of workers
 *   @blocks numbers of blocks
 *   @width_img width of the img (WIDTH)
 *   @width_blocks widths for each blocks
 */
struct Param_master {
    int workers;
    int blocks;
    int width_img;
    Params_t *p;
    SURFACE *surface;
    Colormap_t *colmap;
};
typedef struct Param_master Param_master;

/**
 * Create the colormap.
 * This tool can be used to visualize gradients: http://angrytools.com/gradient/
 */
void create_colormap(Colormap_t *colmap) {

}

/**
 * Free the memory used by the color map.
 */
void free_colormap(Colormap_t *colmap) {

}

/**
 * Exit when ESC is pressed
 */
void* exit_esc(void* arg) {

}

void* present_25hz(void* arg) {

}

/**
 * Render the Mandelbrot set.
 */
void* mandelbrot(void *arg) {


}

void* master_func(void *arg) {

}

/*
 *
 */
int main(int argc, char** argv) {
    // We set Param_master for initializing some int
    Param_master *param_master = malloc(sizeof (Param_master));

    pthread_t escape;
    pthread_t present;
    pthread_t master;

    param_master->width_img = WIDTH;
    param_master->workers =  atoi(argv[1]);
    param_master->blocks = atoi(argv[2]); 

    // Creation of the thread which is checking for the ESC
    if (pthread_create(&escape, NULL, exit_esc, NULL) != 0) {
        fprintf(stderr, "Erreur dans la creation du thread\n");
        return EXIT_FAILURE;
    }

    Colormap_t colmap; // Set colormap_t
    create_colormap(&colmap); // Create colormap_t

    SURFACE *surface = gfx_init("Mandelbrot", WIDTH, HEIGHT);

    if (surface == NULL) {
        fprintf(stderr, "Failed initializing video mode!\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&present, NULL, present_25hz, surface) != 0) {
        fprintf(stderr, "Erreur dans la creation du thread\n");
        return EXIT_FAILURE;
    }

    param_master->p = &p; // We take Params_st
    param_master->colmap = &colmap; // We take colmap
    param_master->surface = surface; // We take surface

    // Creation of thread master
    if (pthread_create(&master, NULL, master_func, param_master) != 0) {
        fprintf(stderr, "Erreur dans la creation du thread\n");
        return EXIT_FAILURE;
    }

    // Execute thread master
    if (pthread_join(master, NULL) != 0) {
        perror("Join error");
        return 0;
    }


    
    free(blocs);
    while(leave != 1){
    	usleep(10);
    }
    gfx_close();
    free_colormap(&colmap);

    return 0;
}
