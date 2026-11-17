# ft_printf

A reimplementation of `printf` in C using variadic arguments, built as `libftprintf.a`.

## What it does

- Supported conversions: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X` and `%%`.
- Returns the number of characters written, like the real `printf`.
- Prints `(null)` for a `NULL` string and `(nil)` for a null pointer.
- Handles `INT_MIN` for `%d` / `%i`.
- Spaces between `%` and the conversion letter are skipped. There are no other flags, width or precision.

## Build and run

```
make          # builds libftprintf.a
make clean    # removes object files
make fclean   # removes object files and the library
make re       # fclean + all
```

Example:

```
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o demo
```

```c
#include "ft_printf.h"

int main(void)
{
	ft_printf("%s has %d items, hex %x\n", "list", 42, 255);
	return (0);
}
```

## How it works

`ft_printf` walks the format string one character at a time. Normal characters are written directly with `write`. When it meets `%`, it passes the next letter and the `va_list` to `ft_check_type`, which reads the matching argument with `va_arg` and calls a small helper: `ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_printf_unsigned`, `ft_hexa` (recursive, base 16) or `ft_pointer`. Each helper returns how many characters it wrote, and the total is the return value.

## Known issues

- None known. The `va_list` is passed by pointer to `ft_check_type` and `va_end` is called, so mixed conversions work on macOS arm64.

## Project structure

- `ft_printf.c`: format parsing, `%p`, conversion dispatch
- `ft_founctions.c`: output helpers for chars, strings, numbers and hex
- `ft_printf.h`: prototypes
- `Makefile`

This is a 42 İstanbul project.
