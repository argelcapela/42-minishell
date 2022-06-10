/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/09 21:16:05 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_env_values(t_ms *ms, t_cmd *current_cmd, \
	char **cmd, int aux)
{
	char		pwd[999];
	char		*oldpwd;
	char		*line;

	oldpwd = ms_find_env_value(ms, "PWD");
	if (oldpwd)
	{
		if (chdir(cmd[1]) == -1)
		{
			line = ft_printf_to_var("cd: %s: \
				No such file or directory\n", cmd[1]);
			ft_putstr_fd(line, aux);
			current_cmd->exit_code = 1;
		}
		else
		{
			getcwd(pwd, 999);
			update_env_value(ms, "OLDPWD", oldpwd);
			update_env_value(ms, "PWD", pwd);
		}
	}
}

static void	update_env_value_according_arg(t_ms *ms, \
t_cmd *current_cmd, int aux)
{
	char		pwd[999];
	char		*line;
	char		**cmd;

	cmd = current_cmd->cmd_splited_by_space;
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", ft_strlen(cmd[1]))
		|| !ft_strncmp(cmd[1], "--", 2))
	{
		chdir(getenv("HOME"));
		update_env_value(ms, "OLDPWD", getenv("PWD"));
		update_env_value(ms, "PWD", getenv("HOME"));
	}
	else if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
	{
		line = ft_printf_to_var("%s\n", ms_find_env_value(ms, "OLDPWD"));
		ft_putstr_fd(line, aux);
		chdir(ms_find_env_value(ms, "OLDPWD"));
		update_env_value(ms, "OLDPWD", getenv("PWD"));
		update_env_value(ms, "PWD", getcwd(pwd, 999));
	}
	else
		update_env_values(ms, current_cmd, cmd, aux);
}

static int	pipe_fd(t_p *prompt, int tmp_fd[])
{
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	return (tmp_fd[1]);
}

void	ms_cd(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int			aux;
	int			tmp_fd[2];

	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	else
		aux = pipe_fd(prompt, tmp_fd);
	current_cmd->exit_code = 0;
	if (!ms_is_in_env(ms, "OLDPWD"))
		ms_add_env(&ms->envs, "OLDPWD", ms_find_env_value(ms, "HOME"));
	update_env_value_according_arg(ms, current_cmd, aux);
	if (aux != 1)
	{
		close (tmp_fd[0]);
		close (tmp_fd[1]);
	}
	else if (aux == 1)
		close(aux);
}
