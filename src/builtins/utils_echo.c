#include <minishell.h>

int	is_echoflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == 45)
	{
		while (str[i])
		{
			if (str[i] == 110)
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int	echo_flagonly(t_expander *expander)
{
	if (is_echoflag(expander->cmd) && !expander->next)
		return (1);
	else
		return (0);
}

void	echo_monitor(t_expander *expander)
{
	if (echo_flagonly(expander))
		rl_redisplay();
	else if (is_echoflag(expander->cmd) && expander->cmd)
	{
		while (!echo_flagonly(expander))
			expander = expander->next;
	}
	else if (expander)
	{
		while (expander)
		{
			printf("%s", expander->cmd);
			expander = expander->next;
			if (expander)
				printf(" ");
		}
		printf("\n");
	}
}

void	ms_echo(t_expander *expander)
{
	if (!ft_strncmp(expander->cmd, "echo", 5))
	{
		expander = expander->next;
		if (!expander)
			return ;
		// echo_monitor(expander);
		if (is_echoflag(expander->cmd) && expander->next)
		{
			while (is_echoflag(expander->cmd) && expander->next)
				expander = expander->next;
			while (expander)
			{
				printf("%s", expander->cmd);
				expander = expander->next;
				if (expander)
					printf(" ");
			}
		}
		else
		{
			while (expander)
			{
				if (is_echoflag(expander->cmd) && expander->next)
					expander = expander->next;		
				printf("%s", expander->cmd);
				expander = expander->next;
				if (expander)
					printf(" ");
			}
			printf("\n");
		}
	}
}
