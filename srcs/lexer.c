/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:41 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 12:19:07 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (token->type == E_ERROR
		|| (token->qt && token->type == E_EOI)
		|| !token->type)
	{
		token->lex = NULL;
		return (token);
	}
	return (token);
}

static int	ft_free_handler(t_token **token, t_tokenlist **lst)
{
	int	code;

	if (!*lst)
		code = 4;
	else
		ft_tokenclear(lst, free);
	if (!*token)
		code = 3;
	else if ((*token)->error)
		code = (*token)->error;
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
