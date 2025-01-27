/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:07:59 by mcolonna          #+#    #+#             */
/*   Updated: 2024/04/25 16:06:24 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTF_H
# define LIBTF_H

# include <stddef.h>
# include <stdbool.h>

///// STR (part1) /////
/**
 * t_string variables are char* which ends with '\0'.
 */
typedef char		*t_string;

/**
 * Same but the chars are constant.
 */
typedef const char	*t_const_string;

///// ERR /////
// Functions who can raise an error must accept a t_err function
// and call it if an error occurs.

/**
 * Function called when there's an error.
 * The argument identifies what type of error is it (can be NULL).
 * In this library, the possible arguments are:
 * -	"alloc error"	Error when allocating memory.
 * -	"bad value"		The value given to the function is bad.
 * -	"errno"			The error is defined in errno.
 * -	"empty list"	The list is empty and it shouldn't be.
 */
typedef void		(t_err)(t_const_string);

/**
 * Keep the error in memory to get it later with get_error().
 */
void				err_remember(t_const_string msg);

/**
 * If err_remember was called before, return the message of the error
 * then drop it. Return NULL if there is no error to get.
 */
t_const_string		err_get(void);

///// MEM /////
// Awesome malloc manager. When you alloc an address, you have to assign
// a t_memclass (mc) to it. Then, you can free every address assigned to
// a mc using mem_freeall(), or you can free the addresses one by one
// using mem_free() (you still have to use mem_freeall() to free the mc).

/**
 * Represent a class of allocs.
 * Must be created by mem_newclass() and freed by mem_freeall()
 * Don't use after being freed.
 */
typedef void		*t_memclass;

/**
 * Create a t_memclass.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_memclass			mem_newclass(t_err *err);

/**
 * Create a t_memclass and add it to parent.
 * It means if we freeall(parent), this mc is freeall too.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_memclass			mem_subclass(t_err *err, t_memclass parent);

/**
 * Alloc memory of the class 'mc' and of the size 'size'.
 * If mc is NULL, do nothing.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
void				*mem_alloc(t_err *err, t_memclass mc, size_t size);

/**
 * Free all the memory of the specified class.
 * 'mc' becomes unusable.
 */
void				mem_freeall(t_memclass mc);

/**
 * Free a pointer. If pointer is NULL, do nothing.
 * /!\ Must use it only with address alloced with mem_alloc!!
 */
void				mem_free(void *pointer);

///// STR (part2) /////

/**
 * Return the length of the string.
 */
int					str_len(t_const_string str);

/**
 * Clone the string.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_string			str_dup(t_err *err, t_memclass mc, t_const_string str);

/**
 * Check if the char is in the given charset.
 * Return always false if c is '\0'.
 */
bool				char_isin(char c, t_const_string charset);

/**
 * Check if the char is a digit ([0-9]).
 */
bool				char_isdigit(char c);

/**
 * Check if the char is an uppercase letter ([A-Z]).
 */
bool				char_isupper(char c);

/**
 * Check if the char is a lowercase letter ([a-z]).
 */
bool				char_islower(char c);

/**
 * Check if the char is a letter ([A-Za-z]).
 */
bool				char_isalpha(char c);
/**
 * Check if the char is a letter or a digit ([A-Za-z0-9]).
 */
bool				char_isalphanum(char c);

/**
 * Allows reading a string char by char.
 */
typedef struct s_stream
{
	char		(*_read)(const void **);
	char		(*_pop)(const void **);
	const void	*_data;
}			t_stream;

/**
 * Create a stream from a string.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_stream			*streamstr_alloc(
						t_err *err, t_memclass mc, t_const_string str);
/**
 * Set 'stream' to a new stream using 'str'.
 */
void				streamstr_init(t_stream *stream, t_const_string str);

/**
 * Return the current char of the stream, or \0 if it's the end.
 */
char				stream_read(t_stream *stream);

/**
 * Return the current char of the stream, or \0 if it's the end.
 * Go to the next char if it isn't the end.
 */
char				stream_pop(t_stream *stream);

/**
 * Skip specified chars in stream.
 * For example if the stream is at "21012321" and charset is "012",
 * it will skip the first '0', '1' and '2's to be at "321".
 */
void				stream_skip(t_stream *stream, t_const_string charset);

/**
 * Read an unsigned int in decimal, until a non-digit or the end of the stream.
 * If there is no digit, or if it overflows the length of a unsigned int, err
 * is called with "bad value" and 0 is returned.
 * Possible errors: "bad value"
 * Return 0 on error.
 */
unsigned int		stream_readuint(t_err *err, t_stream *stream);

/**
 * Read a signed int in decimal, until a non-digit or the end of the stream.
 * If there is no digit, '+' or '-', or if it overflows the length of a signed
 * int, err is called with "bad value" and -1 is returned.
 * Possible errors: "bad value"
 * Return 0 on error.
 */
int					stream_readint(t_err *err, t_stream *stream);

/**
 * Cast a string to an unsigned int in decimal.
 * The string must match /[0-9]+/, and the result must not overflow the limits
 * of a unsigned int. If it isn't respected, err is called with "bad value"
 * and 0 is returned.
 * Possible errors: "bad value"
 * Return 0 on error.
 */
unsigned int		str_touint(t_err *err, t_const_string str);

/**
 * Cast a string to a signed int in decimal.
 * The string must match /[-+]?[0-9]+/, and the result must not overflow the
 * limits of an int. If it isn't respected, err is called with "bad value" and
 * -1 is returned.
 * Possible errors: "bad value"
 * Return -1 on error.
 */
int					str_toint(t_err *err, t_const_string str);

/**
 * Split the given string by the given separators in charset.
 * Return a list of strings ended by NULL, no empty string.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_string			*str_split(
						t_err *err, t_memclass mc, t_const_string str,
						t_const_string charset);

/**
 * Return a mem_alloc'd concatenation of the two strings.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_string			str_join(t_err *err, t_memclass mc, t_const_string str1,
						t_const_string str2);

/**
 * Write an int as an str in decimal.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_string			str_inttostr(t_err *err, t_memclass mc, int n);

/**
 * Write an unsigned int as an str in decimal.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
t_string			str_uinttostr(t_err *err, t_memclass mc, unsigned int n);

/**
 * Return true if the strings are the same.
 */
bool				str_eq(t_const_string str1, t_const_string str2);

///// IO /////

/**
 * Write a string on fd.
 * Possible errors: "errno"
 */
void				print_str(t_err *err, int fd, t_const_string str);

/**
 * Write a string on fd and finish it with a \n.
 * Possible errors: "errno"
 */
void				print_line(t_err *err, int fd, t_const_string str);

/**
 * Conversions: %c %s %p %d %i %u %x %X %%
 * Return -1 on error.
 */
int					tf_printf(t_const_string format, ...);

/**
 * Return the next line of the 'fd', including the '\n' if it exists.
 * 'fd' must be between 0 and 4095 included.
 * Possible error: "alloc error", "bad value", "errno"
 * Return NULL if error, BUT it's not the only case it could return NULL!
 * To avoid leaks and problems, must be called until it returns NULL.
 */
t_const_string		read_line(t_err err, t_memclass mc, int fd);

///// LIST /////

/**
 * Represents an element of a t_list.
 * - value: mem_alloc'd pointer to the value of the element.
 * - next: next element in the list, or NULL if it's the end of the list.
 * - previous: previous element in the list, or NULL if it's the beginning of the
 *     list.
 */
typedef struct s_list_element
{
	void					*value;
	struct s_list_element	*next;
	struct s_list_element	*previous;
}							t_list_element;

/**
 * Represents a list.
 * - first: first element of the list, or NULL if the list is empty.
 * - last: last element of the list, or NULL if the list is empty.
 * - size: number of elements in the list.
 * - mc: memclass of the elements and their values.
 * [!] All those fields must stay coherent.
 */
typedef struct s_list
{
	t_list_element	*first;
	t_list_element	*last;
	int				size;
	t_memclass		mc;
}			t_list;

/**
 * Create an empty list.
 * The mc is saved to be used y list_addelement. You must do mem_freeall(mc)
 * after finishing using the list.
 */
t_list				list_createempty(t_memclass mc);

/**
 * Add an element to the start of the list.
 * The element is alloc'd with the mc of the list.
 * Possible errors: "alloc error"
 */
void				list_revadd(t_err *err, t_list *list, void *value);

/**
 * Add an element to the end of the list.
 * The element is alloc'd with the mc of the list.
 * err is called with "alloc error" if the alloc doesn't work.
 * Possible errors: "alloc error"
 */
void				list_add(t_err *err, t_list *list, void *value);

/**
 * Get the value at the specified index.
 * Possible errors: "alloc error"
 * Return NULL on error.
 */
void				*list_get(t_err *err, const t_list *list, int index);

/**
 * Return the last value from the list and remove it.
 * Possible errors: "empty list"
 * Return NULL on error.
 */
void				*list_revpop(t_err *err, t_list *list);

/**
 * Return the first value from the list and remove it.
 * Possible errors: "empty list"
 * Return NULL on error.
 */
void				*list_pop(t_err *err, t_list *list);

/**
 * Return the size of the list.
 */
int					list_getsize(const t_list *list);

/**
 * Move the first element to the end of the list.
 * Does nothing if empty.
 */
void				list_rotate(t_list *list);

/**
 * Move the last element to the beginning of the list.
 * Does nothing if empty.
 */
void				list_revrotate(t_list *list);

/**
 * Convert the t_list to a void** ended by NULL.
 */
void				**list_convert(
						t_err *err, t_memclass mc, const t_list *list);

/**
 * Let '<type>' be the type of the value of all elements of the list:
 * convert the t_list to a <type>* list ended by a <type> filled with nul bytes.
 * For example:
 *   If 'list' is {3, 4, 7, 2, 1} wth each element being an int, this function
 *   will return (int*){3, 4, 7, 2, 1, 0}.
 */
void				*list_convert_type(t_err *err,
						t_memclass mc, const t_list *list, int size);

///// DATA /////

/**
 * Copy 'size' bytes of content from src to dest.
 * The ranges CAN overlap.
 */
void				data_cpy(void *dest, const void *src, size_t size);

#endif
