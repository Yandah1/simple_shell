#include "shell."

/**
 * print_alias - Alias function
 * @node: Pointer to linked list of type list_t
 *
 * Return: 0 if successful, 1 otherwise
 */

int print_alias(list_t *node);
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = strchr(node->str, '=');
for (a = node->str; a <= p; a++)
putchar(*a);
putchar('\'');
puts(p + 1);
puts("'\n");
return (0);
}
return (1);
}
