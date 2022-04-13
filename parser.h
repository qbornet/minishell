#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "error.h"
# include <libft.h>

typedef s_cmd_name		t_cmd_name;
typedef s_cmd_prefix	t_cmd_prefix;
typedef s_here_end		t_here_end;
typedef s_io_here		t_io_here;

struct s_cmd_name
{
	int		token_id;
	t_error	error;
};

struct s_cmd_prefix
{
	/* TOKEN_ID == ASSIGNMENT_WORD */
	int				token_id;
	t_io_redirect	*io_redirect;
	t_cmd_prefix	*cmd_prefix;
	t_error			error;
};

struct s_here_end
{
	/* TOKEN_ID == WORD */
	int		token_id;
	t_error	error;
};

struct s_io_here
{
	/* TOKEN_ID == DLESS */
	int			token_id;
	t_here_end	*here_end;
	t_error		error;
};

struct 

