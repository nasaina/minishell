#include <minishell.h>

const char	**init_builtins(void)
{
	static const char	*builtins[] = {
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