#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "error.h"
# include <libft.h>

/*
typedef struct s_cmd_name		t_cmd_name;
typedef struct s_cmd_prefix		t_cmd_prefix;
typedef	struct s_cmd_suffix		t_cmd_suffix;
typedef	struct s_cmd_word		t_cmd_word;
typedef	struct s_simple_cmd		t_simple_cmd;
typedef	struct s_command		t_command;
typedef struct s_here_end		t_here_end;
typedef struct s_filename		t_filename;
typedef struct s_io_here		t_io_here;
typedef struct s_io_file		t_io_file;
typedef struct s_io_redirect	t_io_redirect;
typedef struct s_redirect_list	t_redirect_list;
typedef struct s_pipeline		t_pipeline;
typedef struct s_and_or			t_and_or;
typedef struct s_complete_cmd	t_complete_cmd;
typedef struct s_rules			t_rules;

// HARD WAY
struct s_cmd_word
{
	//TOKEN_ID == WORD
	t_token	*token;
	t_error	*error;
};

struct s_cmd_name
{
	//TOKEN_ID == WORD
	t_token	*token;
	t_error	*error;
};

struct s_cmd_prefix
{
	//TOKEN_ID == ASSIGNMENT_WORD
	t_token			*token;
	t_io_redirect	*io_redirect;
	t_cmd_prefix	*cmd_prefix;
	t_error			*error;
};

struct s_cmd_suffix
{
	//TOKEN_ID == WORD
	t_token			*token;
	t_io_redirect	*io_redirect;
	t_cmd_suffix	*cmd_suffix;
	t_error			*error;
};

struct s_filename
{
	//TOKEN_ID == WORD
	t_token	*token;
	t_error	*error;
};

struct s_here_end
{
	// TOKEN_ID == WORD
	t_token	*token;
	t_error	*error;
};

struct s_io_here
{
	// TOKEN_ID == DLESS
	t_token		*token;
	t_here_end	*here_end;
	t_error		*error;
};

struct s_io_file
{
	//	TOKEN_ID == GREAT or LESS or DGREAT
	t_token		*token;
	t_filename	*filename;
	t_error		*error;
};

struct s_simple_cmd
{
	// TOKEN_ID == NONE (NULL)
	t_token			*token;
	t_cmd_prefix	*cmd_prefix;
	t_cmd_suffix	*cmd_suffix;
	t_cmd_name		*cmd_name;
	t_cmd_word		*cmd_word;
	t_error			*error;
};

struct s_io_redirect
{
	// TOKEN_ID == NONE (NULL)
	t_token		*token;
	t_io_file	*io_file;
	t_io_here	*io_here;
	t_error		*error;
};

struct s_redirect_list
{
	// TOKEN ID == NONE (NULL)
	t_token			*token;
	t_redirect_list	*redirect_list;
	t_io_redirect	*io_redirect;
	t_error			*error;
};

struct s_command
{
	// TOKEN ID == NONE (NULL)
	t_token			*token;
	t_simple_cmd	*simple_cmd;
	t_subshell		*subshell;
	t_error			*error;
};

struct s_pipeline
{
	// TOKEN ID == '|'
	t_token		*token;
	t_command	*command;
	t_pipeline	*pipeline;
};

struct s_and_or
{
	// TOKEN ID == AND_IF or OR_IF
	t_token		*token;
	t_and_or	*and_or;
	t_pipeline	*pipeline;
};

struct s_complete_cmd
{
	t_and_or	*and_or;
};

struct s_rules
{
	t_cmd_word		*cmd_word;
	t_cmd_name		*cmd_name;
	t_cmd_prefix	*cmd_prefix;
	t_cmd_suffix	*cmd_suffix;
	t_filename		*filename;
	t_here_end		*here_end;
	t_io_here		*io_here;
	t_io_file		*io_file;
	t_simple_cmd	*simple_cmd;
	t_io_redirect	*io_redirect;
	t_redirect_list	*redirect_list;
	t_command		*command;
	t_pipeline		*pipeline;
	t_and_or		*and_or;
	t_complete_cmd	*complete_cmd;
};
*/

// END OF HARDWAY
// EASY WAY

// Node a mettre dans l'arbre binaire
typedef struct s_nodes
{
	enum e_token	type;
	t_token			*token;
	t_tokenlist		*tokenlst;
}	t_nodes;

// Abre binaire AST
typedef struct s_btree
{
	t_nodes			*node;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

/*
// Les regles de syntax 0 == faux et 1 == vrai
typedef struct s_rules
{
	int	cmd_word;
	int	cmd_name;
	int	cmd_prefix;
	int	cmd_suffix;
	int	filename;
	int	here_end;
	int	io_here;
	int	io_file;
	int	simple_cmd;
	int	io_redirect;
	int	redirect_list;
	int	command;
	int	pipeline;
	int	and_or;
	int	complete_cmd;
}	t_rules;
*/

//END OF EASY WAY

// tree_utils.c
void	ft_treeclear(t_btree *tree, void (*del) (void *));
void	ft_treeprint(t_btree *tree, int type);

#endif
