#include "minishell.h"

static t_token	*tokeninit(char **input, unsigned int qt)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lex = *input;
	token->type = 0;
	token->qt = qt;
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
	if (is_eoi(**input, token))
		token->len = 0;
	else if (is_token_2(*input, token) && !token->qt)
		token->len = 2;
	else if (is_token_1(*input, token) && !token->qt)
		token->len = 1;
	else
		word_token(*input, token);
	*input += token->len;
	if ((token->qt && token->type == E_EOI) || !token->type)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static int	ft_free_handler(t_token **token, t_tokenlist **lst, int code)
{
	ft_tokenclear(lst, free);
	if (code == 2)
		free(*token);
	return (code);
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
		if (!token)
			return (ft_free_handler(&token, lst, 1));
		newlst = ft_tokennew(token);
		if (!newlst)
			return (ft_free_handler(&token, lst, 2));
		ft_tokenadd_back(lst, newlst);
		if (token->type == E_EOI)
			break ;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int			code;
	char		*input;
	t_tokenlist	*lst;
	t_tokenlist *tmp;

	(void)ac;
	(void)av;
	(void)envp;
	//input = "=toto tata= echo toto mo ===nmo||onnai( ssee&&ttoitco)mm|e|||ntc ava>>>>>p < lutot <<biene< ttoia;sdfjas;dfjaspdfji                   world && Hello Bob=";
	//input = " echo>  Hello world Bob";
	input = "ech \" '\"o'bonjo\"\"\"ur' $TOTO 'ls -ls && echo bonjour' && echo 'ls&&$TOTO'";
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
