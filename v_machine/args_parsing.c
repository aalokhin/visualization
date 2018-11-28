/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:43 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/14 14:56:48 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	get_t_dir_value(t_proc *processes, unsigned char *map,
	int arg_ind, int *id_counter)
{
	short			tmp_2;
	unsigned int	tmp_4;

	tmp_2 = 0;
	tmp_4 = 0;
	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		if (!g_op_tab[(int)(*processes).cmd - 1].label)
		{
			tmp_4 = (unsigned int)(((map[((*id_counter) + 1) % MEM_SIZE] << 24)
			+ (map[((*id_counter) + 2) % MEM_SIZE] << 16) + (map[((*id_counter)
			+ 3) % MEM_SIZE] << 8) + map[((*id_counter) + 4) % MEM_SIZE]));
			(*processes).argv[arg_ind][1] = tmp_4;
			(*id_counter) += 4;
		}
		else
		{
			tmp_2 = (short)((map[((*id_counter) + 1) % MEM_SIZE] << 8) +
			map[((*id_counter) + 2) % MEM_SIZE]);
			(*processes).argv[arg_ind][1] = tmp_2;
			(*id_counter) += 2;
		}
	}
	(*processes).arg_counter++;
}

void	get_t_ind_value(t_proc *processes, unsigned char *map, int arg_ind,
	int *id_counter)
{
	short tmp;

	tmp = 0;
	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		tmp = (short)((map[((*id_counter) + 1) % MEM_SIZE] << 8) +
			map[((*id_counter) + 2) % MEM_SIZE]);
		(*processes).argv[arg_ind][1] = tmp;
		(*id_counter) += 2;
	}
	(*processes).arg_counter++;
}

void	get_t_reg_value(t_proc *processes, unsigned char *map, int arg_ind,
	int *id_counter)
{
	unsigned char tmp;

	if ((*processes).arg_counter < g_op_tab[(*processes).cmd - 1].arg_nbr)
	{
		tmp = (unsigned char)(map[((*id_counter) + 1) % MEM_SIZE]);
		(*processes).argv[arg_ind][1] = tmp;
		(*id_counter)++;
	}
	(*processes).arg_counter++;
}

void	get_args_values(t_proc *processes, unsigned char *map, int *id_counter)
{
	if ((*processes).argv[0][0])
		g_get_arg_vals[(*processes).argv[0][0] - 1](processes, map, 0,
			id_counter);
	if ((*processes).argv[1][0])
		g_get_arg_vals[(*processes).argv[1][0] - 1](processes, map, 1,
			id_counter);
	if ((*processes).argv[2][0])
		g_get_arg_vals[(*processes).argv[2][0] - 1](processes, map, 2,
			id_counter);
}

void	take_args(unsigned char codage, t_proc *processes)
{
	if ((codage & 192) == 64)
		(*processes).argv[0][0] = REG_CODE;
	else if ((codage & 192) == 192)
		(*processes).argv[0][0] = IND_CODE;
	else if ((codage & 192) == 128)
		(*processes).argv[0][0] = DIR_CODE;
	if ((codage & 48) == 32)
		(*processes).argv[1][0] = DIR_CODE;
	else if ((codage & 48) == 48)
		(*processes).argv[1][0] = IND_CODE;
	else if ((codage & 48) == 16)
		(*processes).argv[1][0] = REG_CODE;
	if ((codage & 12) == 8)
		(*processes).argv[2][0] = DIR_CODE;
	else if ((codage & 12) == 12)
		(*processes).argv[2][0] = IND_CODE;
	else if ((codage & 12) == 4)
		(*processes).argv[2][0] = REG_CODE;
}
