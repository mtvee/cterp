
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include <math.h>
#include <time.h>

#include "lib.h"

// keyword def.h
_keyword_table keyword_table[] = {
        "void", VOID,
        "char", CHAR,
        "int", INT,
        "float", FLOAT,
        "double", DOUBLE,
        "const", CONST,
        "enum", ENUM,
        "struct", STRUCT,
        "sizeof", SIZEOF,
        "return", RETURN,
        "if", IF,
        "then", THEN,
        "else", ELSE,
        "for", FOR,
        "do", DO,
        "break", BREAK,
        "continue", CONTINUE,
        "while", WHILE,
        "switch", SWITCH,
        "case", CASE,
        "default", DEFAULT,
        "include", INCLUDE,
        "", 0
};


// variable declaration def.h
char *error_table[] = {
        "syntax error",
        "syntax error: opening parenthesis expected",
        "syntax error: closing parenthesis expected",
        "syntax error: opening brace expected",
        "syntax error: closing brace expected",
        "syntax error: opening bracket expected",
        "syntax error: closing bracket expected",
        "syntax error: comma expected",
        "syntax error: semicolon expected",
        "syntax error: variable type expected in the declaration",
        "syntax error: identifier expected",
        "global variable limit reached (max = 100)",
        "function declaration limit reached (max = 100)",
        "syntax error: only variable and function declarations are allowed outside of functions",
        "main funtion not found",
        "undeclared function",
        "syntax error: single quote expected",
        "syntax error: double quotes expected",
        "undeclared variable or unkown constant",
        "maximum number of function paramters reached (max = 10)",
        "maximum number of program-defined function calls reached (max = 100)",
        "local variables limit reached (max = 200)",
        "returning value from void function",
        "invalid expression",
        "invalid argument for the bitwise not operation",
        "while part of do-while loop expected",
        "duplicate global variable declared",
        "duplicate local variable declared",
        "string constant expected",
        "pointer expected",
        "insufficient function arguments",
        "pointer syntax error",
        "declared matrix exceeds the maximum number of dimensions (max = 10)",
        "invalid matrix dimension",
        "memory allocation failure",
        "matrix index outside bounds",
        "invalid matrix attribution",
        "matrix expected",
        "unknown library",
        "unknown directive",
        "directive syntax error",
        "incompatible function argument",
        "constant variable assignment",
        "invalid binary operands",
        "struct expected",
        "struct name expected but token is not an identifier for any structs",
        "undeclared struct",
        "invalid printf format code",
        "invalid type conversion"
};


_CONST math_const_table[] = {
        "_PI", DT_DOUBLE, 0, 0, 0, {.d = 3.14159265358979323846264338327950288}, 0,
        "_PI_2", DT_DOUBLE, 0, 0, 0, {.d = 1.5707963267948966}, 0,
        "_PI_4", DT_DOUBLE, 0, 0, 0, {.d = 0.7853981633974483}, 0,
        "_E", DT_DOUBLE, 0, 0, 0, {.d = 2.71828182845904523536028747135266249}, 0,
        "_SQRT2", DT_DOUBLE, 0, 0, 0, {.d = 1.41421356237309504880168872420969807}, 0,
        "_SQRT3", DT_DOUBLE, 0, 0, 0, {.d = 1.73205080756887729352744634150587236}, 0,
        "_SQRT5", DT_DOUBLE, 0, 0, 0, {.d = 2.23606797749978969640917366873127623}, 0,
        "_EULER_GAMMA", DT_DOUBLE, 0, 0, 0, {.d = 0.57721566490153286060651209008240243}, 0,
        "_GOLDEN_RATIO", DT_DOUBLE, 0, 0, 0, {.d = 1.61803398874989484820458683436563811}, 0,
        "_ZETA2", DT_DOUBLE, 0, 0, 0, {.d = 1.64493406684822643647241516664602518}, 0,
        "_ZETA3", DT_DOUBLE, 0, 0, 0, {.d = 1.20205690315959428539973816151144999}, 0,
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST stdio_const_table[] = {
        "NULL", DT_VOID, 0, 0, 0, {.p = NULL}, 1,
        "EOF", DT_INT, 0, 0, 0, {.i = EOF}, 0,
        "FOPEN_MAX", DT_INT, 0, 0, 0, {.i = FOPEN_MAX}, 0,
        "SEEK_SET", DT_INT, 0, 0, 0, {.i = SEEK_SET}, 0,
        "SEEK_CUR", DT_INT, 0, 0, 0, {.i = SEEK_CUR}, 0,
        "SEEK_END", DT_INT, 0, 0, 0, {.i = SEEK_END}, 0,
        "FILENAME_MAX", DT_INT, 0, 0, 0, {.i = FILENAME_MAX}, 0,
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST stdlib_const_table[] = {
        "RAND_MAX", DT_INT, 0, 0, 0, {.i = RAND_MAX}, 0,
        "EXIT_SUCCESS", DT_INT, 0, 0, 0, {.i = EXIT_SUCCESS}, 0,
        "EXIT_FAILURE", DT_INT, 0, 0, 0, {.i = EXIT_FAILURE}, 0,
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST stdbool_const_table[] = {
        "true", DT_INT, 0, 0, 0, {.i = 1}, 0,
        "false", DT_INT, 0, 0, 0, {.i = 0}, 0,
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST time_const_table[] = {
        "CLOCKS_PER_SEC", DT_INT, 0, 0, 0, {.i = CLOCKS_PER_SEC}, 0,
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST conio_const_table[] = {
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};

_CONST string_const_table[] = {
        "", DT_INT, 0, 0, 0, {.i = 0}, 0
};


_LIB stdio_lib[] = {
        "putchar", call_putchar,
        "getchar", call_getchar,
        "puts", call_puts,
        "printf", call_printf,
        "scanf", call_scanf,
        "gets", call_gets,
        "fopen", call_fopen,
        "fclose", call_fclose,
        "feof", call_feof,
        "fputc", call_fputc,
        "fgetc", call_fgetc,
        "fseek", call_fseek,
        "ftell", call_ftell,
        "ferror", call_ferror,
        "rewind", call_rewind,
        "remove", call_remove,
        "fflush", call_fflush,
        "", 0
};

_LIB stdlib_lib[] = {
        "malloc", call_malloc,
        "free", call_free,
        "system", call_system,
        "rand", call_rand,
        "", 0
};

_LIB math_lib[] = {
        "sin", call_sin,
        "asin", call_asin,
        "cos", call_cos,
        "acos", call_acos,
        "tan", call_tan,
        "atan", call_atan,
        "atan2", call_atan2,

        "sinh", call_sinh,
        "asinh", call_asinh,
        "cosh", call_cosh,
        "acosh", call_acosh,
        "tanh", call_tanh,

        "sqrt", call_sqrt,
        "pow", call_pow,

        "ln", call_ln,
        "log", call_log,
        "exp", call_exp,

        "trunc", call_trunc,
        "round", call_round,
        "abs", call_abs,
        "ceil", call_ceil,
        "floor", call_floor,
        "max", call_max,
        "min", call_min,

        "eval", call_eval,

        "gamma", call_gamma,
        "erf", call_erf,
        "zeta", call_zeta,

        "avrg", call_avrg,

        "todeg", call_todeg,
        "torad", call_torad,
        "fact", call_fact,
        "signum", call_signum,
        "isodd", call_isodd,
        "iseven", call_iseven,
        "isprime", call_isprime,
        "nCk", call_nCk,

        "", 0
};

_LIB string_lib[] = {
        "strlen", call_strlen,
        "strchr", call_strchr,
        "strstr", call_strstr,
        "strcat", call_strcat,
        "strcpy", call_strcpy,
        "strcmp", call_strcmp,
        "", 0
};

#ifdef _WIN32
_LIB conio_lib[] = {
    "kbhit", call_kbhit,
    "getch", call_getch,
    "putch", call_putch,
    "getche", call_getche,
    "clrscr", call_clrscr,
    "", 0
};
#endif

_LIB time_lib[] = {
        "asctime", call_asctime,
        "clock", call_clock,
        "time", call_time,
        "", 0
};

_LIB stdbool_lib[] = {
        "", 0
};

lib_table libs[] = {
        "stdio", stdio_lib, stdio_const_table,
        "stdlib", stdlib_lib, stdlib_const_table,
        "math", math_lib, math_const_table,
        "string", string_lib, string_const_table,
#ifdef _WIN32
        "conio", conio_lib, conio_const_table,
#endif
        "time", time_lib, time_const_table,
        "stdbool", stdbool_lib, stdbool_const_table,
        "", NULL, NULL
};


void call_rand(void)
{
    get_token();
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = rand();
}

void call_fopen(void)
{
    char *filename, *mode;
    _DATA expr;

    eval(&expr);
    filename = expr.value.p;

    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&expr);
    mode = expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_VOID;
    func_ret.ind_level = 1;
    func_ret.value.p = (void *) fopen(filename, mode);
}

void call_fclose(void)
{
    _DATA fp;

    eval(&fp);

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = fclose(fp.value.p);
}

void call_fputc(void)
{
    FILE *fp;
    int ch;
    _DATA expr;

    eval(&expr);
    convert_data(&expr, DT_INT);
    ch = expr.value.i;

    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&expr);
    fp = (FILE *) expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = fputc(ch, fp);
}

void call_fgetc(void)
{
    FILE *fp;
    int ch;
    _DATA expr;

    eval(&expr);
    fp = (FILE *) expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = fgetc(fp);
}

void call_feof(void)
{
    FILE *fp;
    _DATA expr;

    eval(&expr);
    fp = (FILE *) expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = feof(fp);
}

void call_ferror(void)
{
    FILE *fp;
    _DATA expr;

    eval(&expr);
    fp = (FILE *) expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = ferror(fp);
}

void call_fseek(void)
{
    FILE *fp;
    _DATA file, numbytes, origin;

    eval(&file);
    fp = (FILE *) file.value.p;
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&numbytes);
    convert_data(&numbytes, DT_INT);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&origin);
    convert_data(&origin, DT_INT);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = fseek(fp, numbytes.value.i, origin.value.i);
}

void call_fflush(void)
{
    FILE *fp;
    _DATA expr;

    eval(&expr);
    fp = (FILE *) expr.value.p;

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = fflush(fp);
}

void call_remove(void)
{
    _DATA filename;

    eval(&filename);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = remove(filename.value.p);
}

void call_ftell(void)
{
    _DATA file;

    eval(&file);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = ftell((FILE *) file.value.p);
}

void call_rewind(void)
{
    _DATA file;

    eval(&file);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = 0;
    rewind((FILE *) file.value.p);
}

void call_asctime(void)
{
    struct tm *ptr;
    time_t lt;

    get_token();
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    lt = time(NULL);
    ptr = localtime(&lt);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;

    func_ret.value.p = asctime(ptr);
}

void call_clock(void)
{
    get_token();
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = clock();
}

void call_time(void)
{
    _DATA ptr;

    eval(&ptr);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;
    func_ret.value.i = time((time_t *) ptr.value.p);
}

void call_gets(void)
{
    _DATA sp;

    eval(&sp);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;
    func_ret.value.p = gets(sp.value.p);
}

void call_strlen(void)
{
    _DATA p;

    eval(&p);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.value.i = strlen(p.value.p);
}

void call_strchr(void)
{
    _DATA s, c;

    eval(&s);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&c);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&c, DT_CHAR);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;
    func_ret.value.p = strchr(s.value.p, c.value.c);
}

void call_strstr(void)
{
    _DATA s1, s2;

    eval(&s1);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&s2);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;
    func_ret.value.p = strstr(s1.value.p, s2.value.p);
}

void call_strcat(void)
{
    _DATA s1, s2;

    eval(&s1);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&s2);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;
    func_ret.value.p = strcat(s1.value.p, s2.value.p);
}

void call_strcpy(void)
{
    _DATA s1, s2;

    eval(&s1);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&s2);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_CHAR;
    func_ret.ind_level = 1;
    func_ret.value.p = strcpy(s1.value.p, s2.value.p);
}

void call_strcmp(void)
{
    _DATA s1, s2;

    eval(&s1);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&s2);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_INT;
    func_ret.value.i = strcmp(s1.value.p, s2.value.p);
}

void call_printf(void)
{
    _DATA formatstr, expr;
    char *p, *q;
    static char format[CONST_LEN + 1];

    func_ret.value.i = 0;
    func_ret.ind_level = 0;
    func_ret.type = DT_INT;

    eval(&formatstr); // gets a pointer to the format string
    if (tok == CLOSING_PAREN) {
        func_ret.value.i = printf(formatstr.value.p);
        return;
    }

    p = formatstr.value.p;
    q = format;

    while (*p) {
        if (*p == '%') {
            p++;
            *q++ = '%';
            while (*p && *p != '%' && *p != 'c' && *p != 'd' && *p != 'i' && *p != 'e' && *p != 'E' && *p != 'f' &&
                   *p != 'p' && *p != 's')
                *q++ = *p++;
            if (!*p) show_error(INVALID_PRINTF_FORMAT_CODE);
            *q++ = *p++;
            *q = '\0';
            switch (*(q - 1)) {
                case '%':
                    func_ret.value.i += putchar('%');
                    break;
                case 'c':
                    eval(&expr);
                    convert_data(&expr, DT_CHAR);
                    func_ret.value.i += putchar(expr.value.c);
                    break;
                case 'i':
                case 'd':
                    eval(&expr);
                    convert_data(&expr, DT_INT);
                    func_ret.value.i += printf(format, expr.value.i);
                    break;
                case 's':
                    eval(&expr);
                    func_ret.value.i += printf(format, expr.value.p);
                    break;
                case 'p':
                    eval(&expr);
                    func_ret.value.i += printf(format, expr.value.p);
                    break;
                case 'f':
                case 'E':
                case 'e':
                    eval(&expr);
                    convert_data(&expr, DT_DOUBLE);
                    func_ret.value.i += printf(format, expr.value.d);
            }
            q = format;
        } else {
            putchar(*p);
            p++;
        }
    }
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
}

void call_scanf(void)
{
    _DATA formatstr, pointer;

    func_ret.type = DT_INT;

    eval(&formatstr); // gets a pointer to the format string
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);

    eval(&pointer);
    scanf(formatstr.value.p, pointer.value.p);

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
}

void call_malloc(void)
{
    _DATA size;

    eval(&size);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&size, DT_INT);

    func_ret.type = DT_VOID;
    func_ret.ind_level = 1;
    func_ret.value.p = malloc(size.value.i);
}

void call_free(void)
{
    _DATA p;

    eval(&p);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    if (!is_pointer(&p)) show_error(POINTER_EXPECTED);

    free(p.value.p);
}

void call_system(void)
{
    _DATA s;

    eval(&s);

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    system(s.value.p);
}

void call_clrscr(void)
{
    get_token();
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    system("cls");
}

void call_puts(void)
{
    _DATA s;

    eval(&s);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    puts(s.value.p);
}

void call_putchar(void)
{
    eval(&func_ret);
    convert_data(&func_ret, DT_CHAR);

    putchar(func_ret.value.c);
}

void call_sin(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = sin(func_ret.value.d);
}

void call_asin(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = asin(func_ret.value.d);
}

void call_cos(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = cos(func_ret.value.d);
}

void call_acos(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = acos(func_ret.value.d);
}

void call_tan(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = tan(func_ret.value.d);
}

void call_atan(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = atan(func_ret.value.d);
}

void call_atan2(void)
{
    _DATA x, y;

    eval(&y);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    eval(&x);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&y, DT_DOUBLE);
    convert_data(&x, DT_DOUBLE);

    func_ret.type = DT_DOUBLE;
    func_ret.value.d = atan2(y.value.d, x.value.d);
    func_ret.ind_level = 0;
}

void call_sinh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = sinh(func_ret.value.d);
}

void call_asinh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = asinh(func_ret.value.d);
}

void call_cosh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = cosh(func_ret.value.d);
}

void call_acosh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = acosh(func_ret.value.d);
}

void call_tanh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = tanh(func_ret.value.d);
}

void call_atanh(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = atanh(func_ret.value.d);
}

void call_floor(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = floor(func_ret.value.d);
}

void call_ceil(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = ceil(func_ret.value.d);
}

void call_pow(void)
{
    _DATA base, exp;

    eval(&base);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    eval(&exp);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&base, DT_DOUBLE);
    convert_data(&exp, DT_DOUBLE);

    func_ret.type = DT_DOUBLE;
    func_ret.value.d = pow(base.value.d, exp.value.d);
    func_ret.ind_level = 0;
}

void call_sqrt(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = sqrt(func_ret.value.d);
}

void call_erf(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = erf(func_ret.value.d);
}

void call_gamma(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = tgamma(func_ret.value.d);
}

void call_ln(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = log(func_ret.value.d);
}

void call_exp(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = exp(func_ret.value.d);
}

void call_log(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = log10(func_ret.value.d);
}

void call_abs(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = abs(func_ret.value.d);
    func_ret.ind_level = 0;
}

void call_todeg(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = 360 * func_ret.value.d / (2 * 3.14159265358979323846264338327950288);
    func_ret.ind_level = 0;
}

void call_torad(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    func_ret.value.d = 2 * 3.14159265358979323846264338327950288 * (func_ret.value.d / 360.0);
    func_ret.ind_level = 0;
}

void call_signum(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_DOUBLE);

    if (func_ret.value.d > 0.0) func_ret.value.d = 1.0;
    else if (func_ret.value.d < 0.0) func_ret.value.d = -1.0;

    func_ret.ind_level = 0;
}

void call_isodd(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_INT);

    if (func_ret.value.i % 2) func_ret.value.i = 1;
    else func_ret.value.i = 0;

    func_ret.ind_level = 0;
}

void call_iseven(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_INT);

    if (func_ret.value.i % 2) func_ret.value.i = 0;
    else func_ret.value.i = 1;

    func_ret.ind_level = 0;
}

void call_isprime(void)
{
    register int i;
    int isprime;

    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&func_ret, DT_INT);

    isprime = 0;
    for (i = 2; i <= trunc(sqrt(func_ret.value.i)); i++) {
        if (!(func_ret.value.i % i)) {
            isprime = i;
            break;
        }
    }

    func_ret.value.i = isprime;

    func_ret.ind_level = 0;
}

void call_fact(void)
{
    eval(&func_ret);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    convert_data(&func_ret, DT_INT);

    if (func_ret.value.i < 0) func_ret.value.i = 0;
    else func_ret.value.i = factorial(func_ret.value.i);
    func_ret.ind_level = 0;
}

int factorial(int N)
{
    if (N == 1 || N == 0) return 1;
    else return N * factorial(N - 1);
}

void call_nCk(void)
{
    _DATA n, k;

    eval(&n);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    convert_data(&n, DT_INT);

    eval(&k);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&k, DT_INT);

    func_ret.type = DT_INT;
    func_ret.ind_level = 0;

    func_ret.value.i = factorial(n.value.i) / (factorial(n.value.i - k.value.i) * factorial(k.value.i));
}


void call_avrg(void)
{
    _DATA expr;
    double d = 0;
    int i = 0;

    do {
        eval(&expr);
        convert_data(&expr, DT_DOUBLE);
        d += expr.value.d;
        i++;
    } while (tok == COMMA);

    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_DOUBLE;
    func_ret.value.d = d / i;
    func_ret.ind_level = 0;
}

void call_zeta(void)
{
    register int i;
    int n;
    _DATA s, iterations;

    eval(&s);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    eval(&iterations);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&s, DT_DOUBLE);
    convert_data(&iterations, DT_INT);

    func_ret.type = DT_DOUBLE;
    func_ret.value.d = 0.0;
    func_ret.ind_level = 0;

    for (i = 1; i <= iterations.value.i; i++)
        func_ret.value.d += 1.0 / pow(i, s.value.d);
}

void call_eval(void)
{
    char *t;
    _DATA expr_str, result;

    eval(&expr_str);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    t = prog;

    prog = expr_str.value.p;
    eval(&result);

    prog = t;

    func_ret = result;
}

void call_trunc(void)
{
    _DATA expr;

    eval(&expr);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    if (expr.type == DT_FLOAT) {
        func_ret.value.f = truncf(expr.value.f);
        func_ret.type = DT_FLOAT;
    } else if (expr.type == DT_DOUBLE) {
        func_ret.value.d = trunc(expr.value.d);
        func_ret.type = DT_DOUBLE;
    } else {
        func_ret.type = expr.type;
    }
}

void call_round(void)
{
    _DATA expr;

    eval(&expr);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    if (expr.type == DT_FLOAT) {
        func_ret.value.f = roundf(expr.value.f);
        func_ret.type = DT_FLOAT;
    } else if (expr.type == DT_DOUBLE) {
        func_ret.value.d = round(expr.value.d);
        func_ret.type = DT_DOUBLE;
    } else {
        func_ret.type = expr.type;
    }
}

void call_max(void)
{
    _DATA x, y;

    eval(&x);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    convert_data(&x, DT_DOUBLE);

    eval(&y);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&y, DT_DOUBLE);

    func_ret.type = DT_DOUBLE;
    func_ret.ind_level = 0;

    if (x.value.d >= y.value.d) func_ret.value.d = x.value.d;
    else func_ret.value.d = y.value.d;
}

void call_min(void)
{
    _DATA x, y;

    eval(&x);
    if (tok != COMMA) show_error(INSUFFICIENT_ARGUMENTS);
    convert_data(&x, DT_DOUBLE);

    eval(&y);
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);
    convert_data(&y, DT_DOUBLE);

    func_ret.type = DT_DOUBLE;
    func_ret.ind_level = 0;

    if (x.value.d <= y.value.d) func_ret.value.d = x.value.d;
    else func_ret.value.d = y.value.d;
}

void call_getchar(void)
{
    get_token();
    if (tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.type = DT_CHAR;
    func_ret.value.c = getchar();
}

#ifdef _WIN32
void call_kbhit(void){
    get_token();
    if(tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.value.i = kbhit();
    func_ret.type = DT_INT;
}

void call_getch(void){
    get_token();
    if(tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.value.c = getch();
    func_ret.type = DT_CHAR;
}

void call_getche(void){
    get_token();
    if(tok != CLOSING_PAREN) show_error(CLOSING_PAREN_EXPECTED);

    func_ret.value.c = getche();
    func_ret.type = DT_CHAR;
}

void call_putch(void){
    eval(&func_ret);
    convert_data(&func_ret, DT_CHAR);

    putch(func_ret.value.c);
}
#endif