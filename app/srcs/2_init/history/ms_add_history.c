#include    <minishell.h>

void    ms_add_history(t_ms *ms, char *line)
{
    t_history   *aux;

    aux = ms->p.history;
	ms->p.history_i++;
	if (!aux)
	{
		aux = (t_history *) malloc(sizeof(struct s_history));
		aux->index = ms->p.history_i;
		aux->line = line;
		aux->next = NULL;
		aux->prev = NULL;
	}
	else
	{
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = (t_history *) malloc(sizeof(struct s_history));
		aux->next->index = ms->p.history_i;
		if (line != NULL)
			aux->next->line = line;
		else
			aux->next->line = ft_printf_to_var("%s\n", ms->p.line);
		aux->next->next = NULL;
		aux->next->prev = aux;
	}
}
