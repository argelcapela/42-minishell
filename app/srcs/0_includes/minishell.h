/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/18 17:31:56 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include			"../../libs/libft/app/srcs/libft.h"
# include			"../1_design/design.h"
# include			"structs.h"

/* design */
void		print_banner(void);

/* init */
t_ms		*ms_init(int argc, char **argv, char **envp);
void		ms_read_input(t_ms *ms);
void		init_env(t_ms *ms);

/* read_input */
void		ms_signals(t_ms *ms);

/* tokenizer */
void		ms_tokenizer(t_ms *ms);

/* parse */
int			ms_parse(t_ms *ms);
void		ms_prepare_command (t_ms *ms);

/* execute */
int			is_builtin(char *cmd);
void		execute_builtin(t_ms *ms);
void		ms_execute(t_ms *ms);

// builtins
int			ms_cd(t_ms *ms);
int			ms_echo(t_ms *ms);
int			ms_env(t_ms *ms);
void		ms_exit(t_ms *ms);
int			ms_export(t_ms *ms);
int			ms_pwd(t_ms *ms);
int			ms_unset(t_ms *ms);

/* utils */
void		ms_clear(t_ms *ms);
// dll_cmd
t_cmd		*ft_dll_cmd_last(t_cmd *cmds);
void		ft_dll_cmd_add_back(t_cmd *cmd, char *name);
void		ms_clear(t_ms *ms);

/* ms */
void		minishell(t_ms *ms);

#endif