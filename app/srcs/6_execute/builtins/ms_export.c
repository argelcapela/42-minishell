/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 01:20:07 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

static char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * 500);
	i = 0;
	while (env)
	{
		arr[i] = ft_printf_to_var("%s=%s", env->key, env->value);
		i++;
		env = env->next;
	}
	return (arr);
}

static void	add_env_by_key(t_ms *ms, const t_cmd *current_cmd)
{
	char	*key;
	char	*value;
	char	**cmd_env_splitted;

	cmd_env_splitted = ft_split(current_cmd->cmd_splited_by_space[1], '=');
	key = cmd_env_splitted[0];
	if (cmd_env_splitted[1] != NULL)
		value = cmd_env_splitted[1];
	else
		value = "";
	ms_add_env(ms, key, value);
	ms->p->cmds->exit_code = 0;
}

static void	print_sorted_env(t_ms *ms)
{
	t_env	*env;
	char	**str;
	int		i;
	t_qs	*qs;

	i = 0;
	env = ms->envs;
	str = env_to_array(env);
	qs = ft_calloc (1, sizeof(t_qs));
	qs->v = str;
	qs->size = sizeof(char *);
	quicksort(qs, 0, ft_mtx_size((void **) str) - 1, \
			(int (*)(void *, void *))(cmpstr));
	i = 0;
	while (str[i])
	{
		if (str[i])
			ft_printf("declare -x %s\n", str[i]);
		i++;
	}
}

void	ms_export(t_ms *ms, t_cmd *current_cmd)
{
	if (!current_cmd->cmd_splited_by_space[1]
		|| *current_cmd->cmd_splited_by_space[1] == '\0'
		|| *current_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms);
	if (ft_strnstr(current_cmd->cmd_splited_by_space[1], "=",
			ft_strlen(current_cmd->cmd_splited_by_space[1])) == NULL)
	{
		ms->p->cmds->exit_code = 0;
		return ;
	}
	if (ft_isdigit(current_cmd->cmd_splited_by_space[1][0]))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(current_cmd->cmd_splited_by_space[1], 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		ms->p->cmds->exit_code = 1;
		return ;
	}
	add_env_by_key(ms, current_cmd);
}
