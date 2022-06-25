/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:44 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 12:13:01 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lexer_parser_main(char *input, char **envp, t_data **d_curr)
{
	int		code;
	t_data	*frame;

	frame = *d_curr;
	code = lexical_analysis(input, &frame->tokenlst);
	if (code == 1)
		printf("lexer error: make sure not to use ) ( & \\ ;\n");
	else if (code == 2)
		printf("lexer error: make sure not to use ||\n");
	else if (code == 3 || code == 4)
		printf("lexer error: something wrong in token creation\n");
	if (code)
		return (-1);
	frame->root = buildbtree(envp, frame->tokenlst);
	if (ft_read_flow(frame->root, &frame->strlst) < 0)
		return (-1);
	*d_curr = frame;
	return (0);
}
