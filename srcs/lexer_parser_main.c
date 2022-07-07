/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:44 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:57:58 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lexer_parser_main(char *input, char **envp, t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	if (lexical_analysis(input, &frame->tokenlst, NULL) < 0)
		return (0);
	frame->root = buildbtree(envp, frame->tokenlst);
	if (!frame->root)
		return (-1);
	if (ft_read_flow(frame->root, &frame->strlst) < 0)
	{
		*d_curr = frame;
		return (2);
	}
	*d_curr = frame;
	return (0);
}
