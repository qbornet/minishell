/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:46 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:47 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **input, t_token *token)
{
	if (!**input)
	{
		token->type = E_EOI;
		token->len = 0;
	}
	if (is_token_2(*input, token))
		return (2);
	if (is_token_1(*input, token))
		return (1);
	word_token(*input, token);
	return (0);
}

/* Fonction pour detecter un char qui pourrait
 * etre le debut d'un token autre que E_WORD
 * @param: c
 * - Le caracter a evaluer
 *
 * @return: char
 * - Le char detecte, 0 sinon
 * */
int	is_special_token(char c, t_token *token)
{
	if (token->qt)
		return (0);
	if (c == '&'
		|| c == '|'
		|| c == ';'
		|| c == '\\'
		|| c == '>'
		|| c == '<'
		|| c == ')'
		|| c == '(')
		return (c);
	return (0);
}

/* Fonction pour generer les tokens E_WORD
 * @param: input
 * - La chaine a tokeniser
 *
 * @param: token
 * - L'adresse du token a utiliser
 *
 * @return: void
 * - Pas de valeur de retour necessaire pour le moment
 *   (a voir pour la gestion de erreurs)
 * */
void	word_token(char *input, t_token *token)
{
	char	*tmp;

	tmp = input;
	while (*input && (*input != ' ' || token->qt)
		&& !is_special_token(*input, token))
	{
		if (*input == '\"' && !token->qt)
			token->qt = E_DOUBLE;
		else if (*input == '\"' && token->qt == E_DOUBLE)
			token->qt = 0;
		if (*input == '\'' && !token->qt)
			token->qt = E_SINGLE;
		else if (*input == '\'' && token->qt == E_SINGLE)
			token->qt = 0;
		input++;
	}
	token->len = input - tmp;
	token->type = E_WORD;
}

/* Fonction pour gerer les tokens E_SEP
 * @param: input
 * - La chaine a tokeniser
 *
 * @param: token
 * - L'adresse du token a utiliser
 *
 * @return: void
 * - Pas de valeur de retour necessaire pour le moment
 *   (a voir pour la gestion de erreurs)
 * */
/*
void	sep_token(char *input, t_token *token)
{
	char *tmp;

	tmp = input;
	while (*input == ' ')
		input++;
	token->len = input - tmp;
	token->type = E_SEP;
}
*/

/* Deux fonction pour differencier les tokens != E_WORD
 * @param: input
 * - La chaine a tokeniser
 *
 * @param: token
 * - L'adresse du token a utiliser
 *
 * @return: int (unsigned int ?)
 * - Type du token
 * */
int	is_token_1(char *input, t_token *token)
{
	if (*input == '>')
		token->type = E_GREAT;
	else if (*input == '<')
		token->type = E_LESS;
	else if (*input == '|')
		token->type = E_PIPE;
	else if (*input == '('
		|| *input == ')'
		|| *input == '&'
		|| *input == '\\'
		|| *input == ';')
		token->type = E_ERROR;
	if (token->type && !token->qt)
	{
		token->len = 1;
		return (1);
	}
	return (0);
}

int	is_token_2(char *input, t_token *token)
{
	if (!ft_strncmp("||", input, 2))
		token->type = E_ERROR;
	else if (!ft_strncmp("<<", input, 2))
		token->type = E_DLESS;
	else if (!ft_strncmp(">>", input, 2))
		token->type = E_DGREAT;
	if (token->type && !token->qt)
	{
		token->len = 2;
		return (2);
	}
	return (0);
}
