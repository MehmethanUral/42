*This project has been created as part of the 42 curriculum by mural.*

# ft_printf

## Description

`ft_printf` is a re-implementation of the standard C library function `printf()`.
The goal of the project is to understand how a function with a **variable number
of arguments** (a *variadic function*) works in C, and to build a small, reusable
output library that can later be added to `libft`.

The project produces a static library, `libftprintf.a`, which exposes a single
public function:

```c
int	ft_printf(const char *format, ...);
```

`ft_printf` reads the `format` string character by character. Normal characters
are written as they are. When a `%` is found, the next character (the
*conversion specifier*) tells the function how to read and print the next
argument. The function returns the total number of characters written.

### Supported conversions

| Specifier | Argument type   | Output                                         |
|-----------|-----------------|------------------------------------------------|
| `%c`      | `int` (char)    | A single character                             |
| `%s`      | `char *`        | A string (`(null)` if the pointer is `NULL`)   |
| `%p`      | `void *`        | Pointer address in hexadecimal, prefixed `0x` (`(nil)` if `NULL`) |
| `%d`      | `int`           | Signed decimal number                          |
| `%i`      | `int`           | Signed integer in base 10                      |
| `%u`      | `unsigned int`  | Unsigned decimal number                        |
| `%x`      | `unsigned int`  | Hexadecimal, lowercase                         |
| `%X`      | `unsigned int`  | Hexadecimal, uppercase                         |
| `%%`      | none            | A literal `%`                                  |

As required by the subject, the buffer management of the original `printf()` is
not implemented: every character is written directly with `write(1, ...)`.

## Instructions

### Compilation

```sh
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + all
```

The library is compiled with `cc` and the flags `-Wall -Wextra -Werror`, and it
is created with `ar rcs`.

### Usage

Include the header and link the library when compiling your program:

```c
#include "ft_printf.h"

int	main(void)
{
	int	len;

	len = ft_printf("Hello %s, you are %d years old (%x in hex)\n", "42", 21, 21);
	ft_printf("%d characters were printed\n", len);
	return (0);
}
```

```sh
cc main.c -L. -lftprintf -o test
./test
```

## Algorithm and data structure

### Overall structure

The code is split into one file per conversion type, so each part is small and
easy to test:

| File               | Role                                                   |
|--------------------|--------------------------------------------------------|
| `ft_printf.c`      | Entry point, format-string parsing and dispatching     |
| `ft_print_char.c`  | Writes one character with `write`                      |
| `ft_print_str.c`   | Writes a string (`%s`)                                 |
| `ft_print_nbr.c`   | Writes a signed integer (`%d`, `%i`)                   |
| `ft_print_unnbr.c` | Writes an unsigned integer (`%u`)                      |
| `ft_print_hex.c`   | Writes an unsigned integer in base 16 (`%x`, `%X`)     |
| `ft_print_ptr.c`   | Writes a pointer address (`%p`)                        |

### Parsing and dispatching

1. `ft_printf` calls `va_start` to initialise a `va_list`.
2. It walks through the string with an index `i`. A normal character is sent to
   `ft_print_char`. A `%` makes it move to the next character and call
   `ft_format`.
3. `ft_format` is a simple dispatcher: an `if / else if` chain compares the
   specifier with each supported letter and calls the matching function,
   reading the argument with `va_arg` in the correct type.
4. Every function returns the number of characters it printed. These numbers
   are added to `count`, which is returned at the end.
5. `va_end` is called before returning.

**Why a pointer to `va_list` (`va_list *args`)?** The `va_list` is passed by
address to the helper functions so that all of them read from the same position
in the argument list. Passing a `va_list` by value to another function and then
using it again is not portable, so a pointer is the safe choice.

**Why `va_arg(args, int)` for `%c`?** In a variadic call, arguments smaller than
`int` (such as `char` and `short`) are automatically promoted to `int`. Reading
them as `char` would be undefined behaviour.

### Printing numbers: recursive base conversion

All numeric conversions use the same idea:

- If the number is greater than or equal to the base, first print `n / base`
  recursively (this prints the left-most digits first).
- Then print the last digit, `base_digits[n % base]`.

The base is `"0123456789"` for decimal and `"0123456789abcdef"` /
`"0123456789ABCDEF"` for hexadecimal. Recursion was chosen because it prints the
digits in the correct order without needing a temporary buffer or `malloc`, and
the recursion depth is very small (at most 10 for a 32-bit decimal number and
16 for a 64-bit hexadecimal address).

Special cases:

- **`INT_MIN`** (`-2147483648`) cannot be made positive inside an `int`, so it
  is printed directly as a string.
- **Negative numbers** print a `-` first, then the positive value.
- **`%u` and `%x`** take an `unsigned int`, so a negative value such as `-1` is
  printed as its unsigned representation (`4294967295` / `ffffffff`), exactly
  like the original `printf`.
- **`%p`** casts the pointer to `unsigned long` (64 bits on Linux) and prints it
  in lowercase hexadecimal after `0x`. A `NULL` pointer prints `(nil)`, which is
  the behaviour of the glibc `printf` on Linux.
- **`%s`** with a `NULL` pointer prints `(null)`.

### Data structures

No dynamic memory and no custom data structure are needed: the program only
uses the `va_list` provided by `<stdarg.h>`, string literals for the digit
bases, and integers for the character counts. This keeps the library simple,
with no risk of memory leaks.

## Resources

- `man 3 printf` – behaviour and return value of the original function
- `man 3 stdarg` – `va_start`, `va_arg`, `va_copy`, `va_end`
- `man 2 write`
- [cppreference – printf](https://en.cppreference.com/w/c/io/fprintf)
- [cppreference – Variadic functions](https://en.cppreference.com/w/c/variadic)
- [GNU C Library – Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)

### Use of AI

AI was used for two purposes:

- **Learning the topic:** to get explanations about variadic functions,
  argument promotion and the behaviour of `printf` in edge cases.
- **Writing this README.md:** to help prepare and structure the documentation.
