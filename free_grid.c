#include "shell.h"
/**
 * free_grid - frees the memory allocated ffor a gridx
 * @grid: pointer to the grid of strings
 * @height: height of the grid
 * Return: nothing
 */
void free_grid(char **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}
