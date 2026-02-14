#include "main.h"

/**
* main - Entry point of the shell program
* @argc: Argument count
* @argv: Argument vector
*
* Return: Always 0 (Success)
*/
int main(int argc, char **argv)
{
	(void)argc; /* Unused parameter */
	return (shell_loop(argv[0]));
}
