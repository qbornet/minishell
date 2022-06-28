#include "minishell.h"

static t_token	*tokeninit(char **input, unsigned int qt)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->lex = *input;
	token->type = 0;
	token->qt = qt;
	token->error = 0;
	token->len = 0;
	return (token);
}

/* Fonction pour recuperer le prochain token dans la string
 * @param: input
 * - La chaine de caracter a tokeniser
 *
 * @return: NULL
 * - En cas d'erreur 
 *
 * @return: t_token *
 * - Le token malloc (penser a le free)
 * */
static t_token	*get_next_token(char **input, unsigned int qt)
{
	t_token	*token;

	while (**input == ' ')
		(*input)++;
	token = tokeninit(input, qt);
	if (!token)
		return (NULL);
	token->error = get_token(input, token);
	*input += token->len;
	if (token->qt)
	{
		token->type = E_ERROR;
		g_exit_status = 505;
	}
	if (token->type == E_ERROR
		|| !token->type)
		token->lex = NULL;
	return (token);
}

static int	ft_free_handler(t_token **token, t_tokenlist **lst)
{
	if (!*lst)
		g_exit_status = 504;
	else
		ft_tokenclear(lst, free);
	if (!*token)
	{
		g_exit_status = 503;
		return (-1);
	}
	else if ((*token)->error)
		g_exit_status = (*token)->error;
	free(*token);
	return (2);
}

/* Fonction pour generer une liste chaine de token
 * @param: input
 * - La chaine de caracter a tokeniser
 *
 * @param: lst
 * - Point vers la HEAD de la liste chaine que l'on veut modifier
 *
 * @return: void
 * - La valeur de retour sera determine plus tard pour gerer les cas d'erreurs
 * */
int	lexical_analysis(char *input, t_tokenlist **lst)
{
	t_token		*token;
	t_tokenlist	*newlst;

	*lst = NULL;
	newlst = NULL;
	while (1)
	{
		if (newlst)
			token = get_next_token(&input, ft_tokenlast(newlst)->token->qt);
		else
			token = get_next_token(&input, 0);
		if (!token || !token->lex)
			return (ft_free_handler(&token, lst));
		newlst = ft_tokennew(token);
		if (!newlst)
			return (ft_free_handler(&token, lst));
		ft_tokenadd_back(lst, newlst);
		if (token->type == E_EOI)
			break ;
	}
	return (0);
}

/*
int	main(int ac, char **av, char **envp)
{
	int			code;
	char		*input;
	t_tokenlist	*lst;
	t_tokenlist	*tmp;

	(void)ac;
	(void)av;
	(void)envp;
	//input = "=toto tata= echo toto mo ===nmo||onnai( ssee&&ttoitco)mm|e|||ntc ava>>>>>p < lutot <<biene< ttoia;sdfjas;dfjaspdfji                   world && Hello Bob=";
	//input = " echo>  Hello world Bob";
	input = "ecl a \" '\"o'bonjo\"\"\"ur' $TOTO 'ls -ls echo bonjour' echo 'ls$TOTO'";
	if (!input)
		return (-1);
	code = lexical_analysis(input, &lst);
	if (code == 1)
		return (printf("some error in token creation\n"));
	else if (code == 2)
		return (printf("some malloc error in tokenlist node creation\n"));
	while (lst)
	{
		tmp = lst;
		printf("lex : %s\nlen : %ld\ntype %d\n-------------------------------\n", lst->token->lex, lst->token->len, lst->token->type);
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
	return (0);
}
*/
