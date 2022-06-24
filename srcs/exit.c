#include "minishell.h"

/* :0 */

void	ft_exit(t_data **d_curr, int status)
{
	write(1, "exit\n", 5);
	exit_group(d_curr);
	exit(status);
}
