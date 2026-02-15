#include "main.h"

/**
 * builtin_exit_shell - Exit the shell program
 *
 * Return: Always returns 0, but exits before return
 */
int builtin_exit_shell(void)
{
	exit(last_exit_status);
	return (0);
}
