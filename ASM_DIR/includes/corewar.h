/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssarkisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:21:47 by ssarkisi          #+#    #+#             */
/*   Updated: 2018/04/20 12:21:49 by ssarkisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "get_next_line.h"
# include "op.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# define LIVE "live"
# define LD "ld"
# define ST "st"
# define ADD "add"
# define SUB "sub"
# define AND "and"
# define OR "or"
# define XOR "xor"
# define ZJMP "zjmp"
# define LDI "ldi"
# define STI "sti"
# define FORK "fork"
# define LLD "lld"
# define LLDI "lldi"
# define LFORK "lfork"
# define AFF "aff"
# define CHECK_BOT_SIZE 0
# define R1(x) (((x) & 0xFF) << 24) | ((((x) & 0xFF00) << 8))
# define R2(x) ((((x) & 0xFF0000) >> 8)) | (((x) & 0xFF000000) >> 24)
# define REVERSE_4_BYTES(x) (R1(x) | R2(x))
# define REVERSE_2_BYTES(x) ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))

typedef struct		s_ol
{
	char			**label_name;
	int				opcode;
	int				argn;
	char			*arg1;
	char			*arg2;
	char			*arg3;
	int				strn;
	int				size;
	int				*code;
	int				p_order;
	int				val1;
	int				val2;
	int				val3;
	struct s_ol		*next;
	struct s_ol		*first;
}					t_ol;

char				*g_bin_file_name;
t_ol				*g_list;

int					bit_to_num(int *bit);
int					get_param_order(int p1, int p2, int p3);
int					check_dir_size(int	n);
int					get_param_type(char *arg);
int					get_command_size(t_ol *ol, int a1, int a2, int a3);
void				get_line_code(t_ol *ol);
void				set_code_param(t_ol *ol);
int					ft_atoin(char *str, int n);
int					*ft_get_zero_arr(int n);
void				write_to_file(t_ol *ol, char *name, char *comment);
void				write_code(int fd, t_ol *ol);
void				write_code_size(int fd, int size);
void				write_magic(int fd);
void				write_name(int fd, char *name);
void				write_comment(int fd, char *comment);
int					get_total_code_size (t_ol *ol);
int					check_dir_size(int	n);
int					get_arg_size(t_ol *ol, int a);
void				set_arg_val(t_ol *ol);
long				get_byte_to_lable(t_ol *ol, char *l, int size);
int					ft_str_in_array(char *str, char **arr);
int					get_val_treg(char *arg);
int					get_val_tdir(char *arg, int size);
int					get_val_tind(char *arg);
int					get_val_lable(t_ol *ol, char *arg, int size);
void				set_val(t_ol *ol, int a);
int					get_arg_size(t_ol *ol, int a);
char				*get_arg(t_ol *ol, int a);
int					get_arg_type(t_ol *ol, int a);
void				set_arg_val(t_ol *ol);
int					get_total_code_size(t_ol *ol);
int					check_dir_size(int n);
int					get_command_size(t_ol *ol, int a1, int a2, int a3);
void				free_all(t_ol *ol, char **name, char **comment);
void				asmembler(t_ol *ol, char **all, char **tmp);
int					free_all_ar(char ***all);
int					ft_istrstr(char *str, const char *to_find);
int					ft_istrchr(const char *s, int c);
int					get_print(char *str, int s, int e);
char				*in_brackets(char **all, int s, int *row, char **tmp);
char				*in_br_long(char **all, int *row, int s, char **tmp);
int					in_br_errors(int e, char ***all_p, int t, char **tmp);
int					skip_comments(char **all, int s);
int					get_arr_size(char **arr);
int					istr_isd(char *str, int s, int e);
int					t_dir_v(char *str, int s);
int					t_ind_val(char *str, int s);
int					t_reg_val(char *str, int s);
void				exterminate_comments(char **str);
char				*is_label(char *all, int *lbc);
int					label_validate(char *str, int s, int e);
int					s_is_comand(char *str, int s, int ret, int e);
int					str_is_com2(char *tmp);
void				list_filling(char **all, int i, size_t m);
t_ol				*new_e(char **label, char **args, int strn, int argn);
void				push(t_ol *new, int opcode);
char				**v_lzfl(char *line, char *com, int isl, int nstr);
char				**v_add_sub(char *line, char *com, int isl, int nstr);
int					get_nonprint(char *str, int s, int per);
char				**v_and_or_xor(char *line, char *com, int isl, int n);
char				**v_ld_lld(char *line, char *com, int isl, int n);
char				**v_ldi_lldi(char *line, char *com, int isl, int n);
char				**v_aff(char *line, char *com, int isl, int n);
char				**v_sti(char *line, char *com, int isl, int n);
char				**v_st(char *line, char *com, int isl, int n);
char				**get_arr(char *line, char *com, char *is_l);
int					lable_com(char **labels, char **arr, int nstr, char **tmp);
void				list_null(t_ol *elem, int argn, int strn);
void				exterm_arr_com(char ***all);
void				check_labels(t_ol *ol, char **all);
void				validate_all(char **all, int rows, int i, int p);
int					striscom(char *str);
int					check_size(char *name, char *cmment);
void				*free_ex(t_ol *ol, char **tmp, char **all, int ex);
char				**get_null_arr(unsigned int len);
char				**arg_error(int argnbr, int line_nbr, char **spl);
unsigned short		get_opcode(char *command);
unsigned short		get_opcode_co(char *command);
void				free_str_arr(char **arr);
char				*get_c_op(int op);
char				**unex_error(int n);
char				**arg_nbr_er(char **spl, int get, int n, int exp);
int					get_c_nbr(char *str, char c);
void				er_exit(char *text, int r, int c, void *trash);
void				*fr_fl(t_ol *ol, char *line, char **all, int ex);
char				*fjoin(char *s1, char *s2);
int					is_lb_ch(char c);
int					ft_istab(int c);

#endif
