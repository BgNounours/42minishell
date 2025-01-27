/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:46:15 by mcolonna          #+#    #+#             */
/*   Updated: 2024/04/24 13:16:41 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <limits.h>

///// CHAR /////

// (In libc) Return 1 if the char 'c' is a specific type of char, or else 0.
int		ft_isalpha(int c); // A-Za-z
int		ft_isdigit(int c); // 0-9
int		ft_isalnum(int c); // A-Za-z0-9
int		ft_isascii(int c); // (0)-(127)
int		ft_isprint(int c); // (32)-(126)

// (In libc) Return the uppercase/lowercase version of the letter,
//           or the char itself if it's not a letter.
int		ft_toupper(int c);
int		ft_tolower(int c);

///// STR /////

// (In libc) Compare 2 strings until n
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// (In libc) Return the length of the string 's'.
size_t	ft_strlen(const char *s);

// (In libc) Copy/Append src on dst.
//           'dst' will be 'size' chars max, including \0,
//           except if 'dst' is already longer for strlcat().
//           1. Never do more than size.
//           2. Always end by \0, except if it doesn't respect 1.
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// (In libc) Return a pointer to the first of last char 'c' in 's',
//           or return NULL if there aren't any.
char	*ft_strchr(const char *s, int c); // First char.
char	*ft_strrchr(const char *s, int c); // Last char.

// (In libc) Return a pointer to the first occurence
//           of string 'little' in string 'big'.
//           Don't look chars after 'size'.
char	*ft_strnstr(const char *big, const char *little, size_t len);

// (In libc) Return an malloced duplicate of 's'.
// Uses: malloc
// Error: return NULL
char	*ft_strdup(const char *s);

// (Perso) Apply 'f' on each char of the string 's' and returns the result.
// Uses: malloc
// Error: return NULL
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// (Perso) Call 'f' for each char of 's'.
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

// (Perso) Return the substring of 's' which starts at 'start'
//         and is of length 'len'.
//         Don't take chars after the end of the string.
// Uses: malloc
// Error: return NULL
char	*ft_substr(char const *s, unsigned int start, size_t len);

// (Perso) Concatenate the two strings.
// Uses: malloc
// Error: return NULL
char	*ft_strjoin(char const *s1, char const *s2);

// (Perso) Remove the characters 'set' from the beginning
//         and the end of the string.
// Uses: malloc
// Error: return NULL
char	*ft_strtrim(char const *s1, char const *set);

// (Perso) Split 's' by the chars 'c'.
//         Return an array ended by NULL.
// Uses: malloc
// Error: return NULL
char	**ft_split(char const *s, char c);

///// MEM /////

// (In libc) Fills 's' with 'n' times the char 'c'.
//           Return 'c'.
void	*ft_memset(void *s, int c, size_t n);

// (In libc) Just ft_memset(s, '\0', n) lol.
void	ft_bzero(void *s, size_t n);

// (In libc) Copy 'n' bytes from 'src' to 'dest'.
//           The 'src' and 'dest' areas mustn't overlap.
//           Return 'dest'.
void	*ft_memcpy(void *dest, const void *src, size_t n);

// (In libc) Same, but the areas can overlap.
//           Return 'dest'.
void	*ft_memmove(void *dest, const void *src, size_t n);

// (In libc) Find the character 'c' in 's', 's' being of length 'n'.
//           NULL if none.
void	*ft_memchr(const void *s, int c, size_t n);

// (In libc) Compare 'n' bytes of 's1' and 's2'.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// (In libc) Alloc an array of 'size' elements with each element
//           being of size 'size'.
// Uses: malloc
// Error: return NULL
void	*ft_calloc(size_t nmemb, size_t size);

///// CAST /////

// (In libc) Cast a string to an int.
//           /[ \f\n\r\t\v]*[-+]?[0-9]*.*/
int		ft_atoi(const char *nptr);

// (Perso) Cast an int to a string.
// Uses: malloc
// Error: return NULL
char	*ft_itoa(int n);

///// WRITE /////

// (Perso) Write the char/string on the file descriptor 'fd'.
// Uses: write
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

// (Perso) Write the string 's' followed by a newline.
// Uses: write
void	ft_putendl_fd(char *s, int fd);

// (Perso) Write the number 'n'.
// Uses: write
void	ft_putnbr_fd(int n, int fd);

#endif
