/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:44:28 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/15 15:58:49 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"
# include "ncurses_env.h"

# define TRUE 1
# define FALSE 0

# define LEFT(x) ((((x) & 0xFF) << 24) | ((((x) & 0xFF00) << 8)))
# define RIGHT(x) (((((x) & 0xFF0000) >> 8)) | (((x) & 0xFF000000) >> 24))
# define REVERSE_4_BYTES(x) (LEFT(x) | RIGHT(x))
# define REVERSE_2_BYTES(x) (((x) << 8) | ((x) >> 8))

/*
** Macros for read from file
*/

# define START_NAME 4
# define START_COMM (PROG_NAME_LENGTH + 12)
# define START_CODE (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
# define SIZE_OF_ALL_FILE (START_CODE + CHAMP_MAX_SIZE)

/*
** Macros for VM
*/

# define IS_T_DIR_FIRST(octal) (((octal) & 0xc0) == 0x80)
# define IS_T_DIR_SECOND(octal) (((octal) & 0x30) == 0x20)
# define IS_T_DIR_THIRD(octal) (((octal) & 0x0c) == 0x08)
# define IS_T_IND_FIRST(octal) (((octal) & 0xc0) == 0xc0)
# define IS_T_IND_SECOND(octal) (((octal) & 0x30) == 0x30)
# define IS_T_IND_THIRD(octal) (((octal) & 0x0c) == 0x0c)
# define IS_T_REG_FIRST(octal) (((octal) & 0xc0) == 0x40)
# define IS_T_REG_SECOND(octal) (((octal) & 0x30) == 0x10)
# define IS_T_REG_THIRD(octal) (((octal) & 0x0c) == 0x04)

# define NON_VALID_PARAMS 42
# define DEFAULT_ERRNO 0

# define FREE_CMD (-1)
# define LIVE 0x1
# define LD 0x2
# define ST 0x3
# define ADD 0x4
# define SUB 0x5
# define AND 0x6
# define OR 0x7
# define XOR 0x8
# define ZJMP 0x9
# define LDI 0xa
# define STI 0xb
# define FORK 0xc
# define LLD 0xd
# define LLDI 0xe
# define LFORK 0xf
# define AFF 0x10

/*
** Macros for size of T_DIR (BIG - 4 bytes | SMALL - 2 bytes)
*/

# define BIG_DIR TRUE
# define SMALL_DIR FALSE

/*
** FLAG for logs of live
*/

# define LOG_LIVE FALSE

t_game			*g_game;

void			ft_error(char *err, t_field *field,\
						void (free_mem)(t_field *field));
void			print_usage(void);
void			free_mem(t_field *field);
void			run_visual(t_field *field);
_Bool			ft_read_commands(int argc, char **argv, t_field *field);
char			*read_from_file(char *filename);
_Bool			handle_param(t_field *field, char **argv, unsigned *index);
int				get_num_of_players(int argc, char **argv);
t_game			*generate_game_info(void);
t_field			*generate_field(void);
t_process		*generate_process(unsigned pos);
t_player		*generate_player(char *name, char *comment);
_Bool			ft_update_mem(t_field *field);
_Bool			cycles_waiting(t_process *process);
void			dell_process(t_field *field, t_process **process,\
													t_process **prev);
void			copy_process_to_dir(t_process *process, unsigned new_pos,\
													t_field *field);
int32_t			read_from_memory_4_bytes(void *mem, int32_t index);
int16_t			read_from_memory_2_bytes(void *mem, int32_t index);
void			write_to_memory_4_bytes(void *mem, int32_t index, int32_t val);
void			write_to_memory_2_bytes(void *mem, int32_t index, int16_t val);
void			write_color(t_field *field, int32_t index, uint8_t color);
void			ft_indirect_load(t_field *field, t_process *process,\
															int16_t idx_mod);
void			ft_indirect_load2(t_field *field, t_process *process,\
															int16_t idx_mod);
unsigned		ft_indirect_load_i(t_field *field, t_process *process,\
															int16_t idx_mod);
void			unknown_command(t_field *field, t_process *process);
void			ft_live(t_field *field, t_process *process);
void			ft_ld(t_field *field, t_process *process);
void			ft_st(t_field *field, t_process *process);
void			ft_add(t_field *field, t_process *process);
void			ft_sub(t_field *field, t_process *process);
void			ft_and(t_field *field, t_process *process);
void			ft_or(t_field *field, t_process *process);
void			ft_xor(t_field *field, t_process *process);
void			ft_zjump(t_field *field, t_process *process);
void			ft_ldi(t_field *field, t_process *process);
void			ft_sti(t_field *field, t_process *process);
void			ft_lld(t_field *field, t_process *process);
void			ft_lldi(t_field *field, t_process *process);
void			ft_fork(t_field *field, t_process *process);
void			ft_lfork(t_field *field, t_process *process);
void			ft_aff(t_field *field, t_process *process);
int32_t			get_first_param(t_field *field, t_process *process,\
											unsigned *iter, _Bool dir_mod);
int32_t			get_sec_param(t_field *field, t_process *process,\
											unsigned *iter, _Bool dir_mod);
int32_t			get_third_param(t_field *field, t_process *process,\
											unsigned *iter, _Bool dir_mod);
int32_t			get_handled_index(t_process *process, int32_t index,\
														int32_t idx_mode);
void			change_carry(t_process *process, int32_t val);
_Bool			ft_is_nonvalid_ldi(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_ld(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_sti(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_st(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_addsub(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_conds(uint8_t *map, t_process *process);
_Bool			ft_is_nonvalid_aff(uint8_t *map, t_process *process);
void			run_dump(t_field *field, int value);
void			run_default(t_field *field);
void			recreate(void);
void			handle_speed(t_field *field, int key);
void			end_of_game(t_field *field);
void			handle_key(t_field *field, int key);
void			print_log_live(t_field *field, unsigned index_player);

#endif
