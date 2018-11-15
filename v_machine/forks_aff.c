/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:37:55 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/15 17:52:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	inst_vars_init(t_instr *inst_vars, t_proc *processes)
{
	(*inst_vars).i = 0;
	(*inst_vars).one = 0;
	(*inst_vars).two = 0;
	(*inst_vars).tmp = processes;
	(*inst_vars).new_ind = 0;
}

int		ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;
	t_proc	*head;

	i = 0;
	tmp = processes;
	head = processes;
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | fork %d (%d)\n", (*tmp).id + 1, (*tmp).argv[0][1], i);
	return (1);
}

int		long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;
	t_proc	*head;

	i = 0;
	tmp = processes;
	head = processes;
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).argv[0][1] + (*tmp).current_position;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | lfork %d (%d)\n", (*tmp).id + 1,
		(*tmp).argv[0][1], i);
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	return (1);
}

int		aff(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 ||
	(*tmp).argv[0][1] > 16 || (*tmp).argv[1][0] || (*tmp).argv[2][0])
		return (0);
	ft_printf("%s", "Aff: ");
	ft_printf("%c\n", ((*tmp).regs[(*tmp).argv[0][1] - 1] % 256));
	(*main_cycle).cycles = (*main_cycle).cycles;
	cur_proc = map[0];
	return (1);
}
