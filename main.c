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
	shell_context_t ctx;
	int result;
	(void)argc; /* Unused parameter */

	ctx.program_name = argv[0];
	ctx.last_exit_status = 0;
	ctx.my_environ = NULL;
	result = shell_loop(&ctx);
	free_my_environ(&ctx);
	return (result);
}
