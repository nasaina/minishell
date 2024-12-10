#include <minishell.h>

char	**init_builtins(void)
{
	static char	*builtins[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset",
	NULL
	};
	return (builtins);
}