#include <minishell.h>

int	ms_cd(t_ms *ms)
{
	char cwd[1000];
	char	**cmd;
	char	*dir;

	cmd = ms->p.cmds->cmd_splited;
	if (!cmd[1] || ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])) == 0
			|| ft_strncmp(cmd[1], "--", ft_strlen(cmd[1])) == 0)
	{
		chdir(getenv("HOME"));
		ms->p.cmds->exit_status = 0;
	} else {
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			// dir = ft_strlcat(cwd, cmd[1], ft_strlen(cwd));
			chdir(dir);
		}
	}

	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}