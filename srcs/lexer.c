/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:41 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:57:21 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*tokeninit(char **input, unsigned int qt)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
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
	get_token(input, token);
	*input += token->len;
	if (token->qt)
	{
		token->type = E_ERROR;
		ft_perror(NULL, E_UNC_QUO);
	}
	if (token->type == E_ERROR
		|| !token->type)
		token->lex = NULL;
	return (token);
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
int	lexical_analysis(char *input, t_tokenlist **lst, t_token *token)
{
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
			return (ft_perror_ret(NULL, E_TOK_CREA, -1));
		if (!token->lex)
		{
			free(token);
			return (-1);
		}
		newlst = ft_tokennew(token);
		if (!newlst)
			return (ft_perror_ret(NULL, E_TOK_CREA, -1));
		ft_tokenadd_back(lst, newlst);
		if (token->type == E_EOI)
			break ;
	}
	return (0);
}
