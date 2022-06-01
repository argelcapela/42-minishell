/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 00:30:53 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_cmd_content2(int i, t_ms *ms, \
	char **cmd_splited, int aux)
{	
	char	*no_dolar;

	if (cmd_splited[i][0] == '"' && \
			cmd_splited[i][1] == '\'' && cmd_splited[i][2] == '$')
	{
		ms_remove_char(cmd_splited[i], '"');
		no_dolar = ft_substr(cmd_splited[i] + 1, \
			1, ft_strlen(cmd_splited[i]));
		if (ms_is_in_env(ms, no_dolar) == 1)
		{
			ft_putstr_fd("\'", aux);
			ft_putstr_fd(ms_find_env_value(ms, no_dolar), aux);
			ft_putstr_fd("\'", aux);
		}
	}
	else if (ft_strchr(cmd_splited[i], '\''))
	{
		ms_remove_char(cmd_splited[i], '\'');
		ft_putstr_fd(cmd_splited[i], aux);
	}
	else
		ft_putstr_fd(cmd_splited[i], aux);
	ft_putstr_fd(" ", aux);
}

static void	print_cmd_content(t_ms *ms, \
	t_cmd *current_cmd, char **cmd_splited, int aux)
{
	char	*no_dolar;
	int		i;

	i = 0;
	while (i++ < current_cmd->args_amount - 1)
	{
		if (cmd_splited[i] && cmd_splited[i][0] == '$')
		{
			no_dolar = ft_substr(cmd_splited[1], 1, ft_strlen(cmd_splited[1]));
			if (ms_is_in_env(ms, no_dolar) == 1)
				ft_putstr_fd(ms_find_env_value(ms, no_dolar), aux);
		}
		print_cmd_content2(i, ms, cmd_splited, aux);
	}
	ft_free_ptr((void **) &no_dolar);
}

void	last_cmd_exit_code(t_ms *ms)
{
	t_history	*code;

	code = ms_last_history(ms->history);
	ft_printf("%d", code->l_c_exit_code);
}

static void	ms_echo_having_flag(t_ms *ms, char	**cmd_splited,
		t_cmd *current_cmd, int aux)
{
	int		has_flag;

	has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
	print_cmd_content(ms, current_cmd, cmd_splited, aux);
	if (has_flag)
		ft_putstr_fd("\n", aux);
	ms->p->cmds->exit_code = 0;
	if (aux != 1)
		close(aux);
}

void	ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	**cmd_splited;
	int		aux;
	int		tmp_fd[2];

	cmd_splited = current_cmd->cmd_splited_by_space;
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	if (!cmd_splited[1])
		ft_putstr_fd("\n", aux);
	else if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
	{
		last_cmd_exit_code(ms);
		ft_putstr_fd("\n", aux);
	}
	else
		ms_echo_having_flag(ms, cmd_splited, current_cmd, aux);
}