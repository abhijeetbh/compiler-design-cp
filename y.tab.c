/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "y.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_no;
extern FILE* yyin;
FILE* out_fp;

void yyerror(const char *s);

struct Symbol {
    char name[50];
    int type;
    // 0 is int, 1 is float, 2 is void, and 3 is class object
    int scope;
    // 0 global, 1 class, 2 local
} sym_table[100];

int sym_count = 0;
int current_scope = 0;
int expected_return_type = -1;
int errors = 0;

void add_symbol(char* name, int type) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(sym_table[i].name, name) == 0 && sym_table[i].scope == current_scope) {
            fprintf(out_fp, "Semantic Error at line %d: variable '%s' already declared in this scope\n", line_no, name);
            errors++;
            return;
        }
    }
    strcpy(sym_table[sym_count].name, name);
    sym_table[sym_count].type = type;
    sym_table[sym_count].scope = current_scope;
    sym_count++;
}

int get_symbol_type(char* name) {
    for (int i = sym_count - 1; i >= 0; i--) {
        if (strcmp(sym_table[i].name, name) == 0) {
            return sym_table[i].type;
        }
    }
    fprintf(out_fp, "Semantic Error at line %d: undeclared variable '%s'\n", line_no, name);
    errors++;
    return -1; 
}

void check_assignment(char* name, int rhs_type) {
    int lhs_type = get_symbol_type(name);
    if (lhs_type == 0 && rhs_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: cannot assign float value to int variable '%s'\n", line_no, name);
        errors++;
    }
}

void check_array_index(int idx_type) {
    if (idx_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: array index must be an integer\n", line_no);
        errors++;
    }
}

void check_return_type(int ret_type) {
    if (expected_return_type == 0 && ret_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: return type mismatch: function declared as 'int' but returns 'float'\n", line_no);
        errors++;
    }
}

void print_symbol_table() {
    fprintf(out_fp, "\n--- SYMBOL TABLE ---\n");
    fprintf(out_fp, "Name\t\tType\tScope\n");
    fprintf(out_fp, "--------------------------------\n");
    for (int i = 0; i < sym_count; i++) {
        char* type_str = (sym_table[i].type == 0) ? "int" : (sym_table[i].type == 1) ? "float" : "other";
        char* scope_str = (sym_table[i].scope == 0) ? "global" : (sym_table[i].scope == 1) ? "class" : "local";
        fprintf(out_fp, "%-15s %-7s %-7s\n", sym_table[i].name, type_str, scope_str);
    }
    fprintf(out_fp, "--------------------------------\n\n");
}

#line 156 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    HEADER = 258,                  /* HEADER  */
    PREPROCESSOR = 259,            /* PREPROCESSOR  */
    CLASS = 260,                   /* CLASS  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    VOID = 263,                    /* VOID  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    FOR = 266,                     /* FOR  */
    WHILE = 267,                   /* WHILE  */
    RETURN = 268,                  /* RETURN  */
    MAIN = 269,                    /* MAIN  */
    PRINTF = 270,                  /* PRINTF  */
    INT_CONST = 271,               /* INT_CONST  */
    FLOAT_CONST = 272,             /* FLOAT_CONST  */
    ID = 273,                      /* ID  */
    STRING_LITERAL = 274,          /* STRING_LITERAL  */
    OP_ARITH = 275,                /* OP_ARITH  */
    OP_REL = 276,                  /* OP_REL  */
    OP_ASSIGN = 277                /* OP_ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 86 "y.y"

    int type; 
    // 0 aahe int, 1 float
    char* str;

#line 234 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_HEADER = 3,                     /* HEADER  */
  YYSYMBOL_PREPROCESSOR = 4,               /* PREPROCESSOR  */
  YYSYMBOL_CLASS = 5,                      /* CLASS  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_VOID = 8,                       /* VOID  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_MAIN = 14,                      /* MAIN  */
  YYSYMBOL_PRINTF = 15,                    /* PRINTF  */
  YYSYMBOL_INT_CONST = 16,                 /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 17,               /* FLOAT_CONST  */
  YYSYMBOL_ID = 18,                        /* ID  */
  YYSYMBOL_STRING_LITERAL = 19,            /* STRING_LITERAL  */
  YYSYMBOL_OP_ARITH = 20,                  /* OP_ARITH  */
  YYSYMBOL_OP_REL = 21,                    /* OP_REL  */
  YYSYMBOL_OP_ASSIGN = 22,                 /* OP_ASSIGN  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '}'  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '['  */
  YYSYMBOL_30_ = 30,                       /* ']'  */
  YYSYMBOL_31_ = 31,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_Elements = 34,                  /* Elements  */
  YYSYMBOL_Element = 35,                   /* Element  */
  YYSYMBOL_ClassDef = 36,                  /* ClassDef  */
  YYSYMBOL_37_1 = 37,                      /* $@1  */
  YYSYMBOL_ClassMembers = 38,              /* ClassMembers  */
  YYSYMBOL_ClassMember = 39,               /* ClassMember  */
  YYSYMBOL_ConstructorDef = 40,            /* ConstructorDef  */
  YYSYMBOL_MethodDef = 41,                 /* MethodDef  */
  YYSYMBOL_42_2 = 42,                      /* $@2  */
  YYSYMBOL_FunctionDef = 43,               /* FunctionDef  */
  YYSYMBOL_44_3 = 44,                      /* $@3  */
  YYSYMBOL_MainFunc = 45,                  /* MainFunc  */
  YYSYMBOL_46_4 = 46,                      /* $@4  */
  YYSYMBOL_Type = 47,                      /* Type  */
  YYSYMBOL_Params = 48,                    /* Params  */
  YYSYMBOL_ParamList = 49,                 /* ParamList  */
  YYSYMBOL_Param = 50,                     /* Param  */
  YYSYMBOL_Statements = 51,                /* Statements  */
  YYSYMBOL_Statement = 52,                 /* Statement  */
  YYSYMBOL_ScopeStmt = 53,                 /* ScopeStmt  */
  YYSYMBOL_Declaration = 54,               /* Declaration  */
  YYSYMBOL_Assignment = 55,                /* Assignment  */
  YYSYMBOL_IfStmt = 56,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 57,                 /* WhileStmt  */
  YYSYMBOL_ForStmt = 58,                   /* ForStmt  */
  YYSYMBOL_PrintfStmt = 59,                /* PrintfStmt  */
  YYSYMBOL_ReturnStmt = 60,                /* ReturnStmt  */
  YYSYMBOL_MethodCallStmt = 61,            /* MethodCallStmt  */
  YYSYMBOL_Expression = 62,                /* Expression  */
  YYSYMBOL_Term = 63,                      /* Term  */
  YYSYMBOL_Factor = 64,                    /* Factor  */
  YYSYMBOL_MethodCall = 65                 /* MethodCall  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,     2,     2,    28,     2,    31,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   103,   103,   105,   105,   107,   107,   107,   107,   107,
     109,   109,   111,   111,   113,   113,   113,   115,   117,   117,
     119,   119,   121,   121,   123,   123,   123,   125,   125,   126,
     126,   127,   129,   129,   129,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   133,   135,   136,   137,   138,   140,
     141,   142,   144,   145,   147,   149,   151,   152,   154,   156,
     157,   158,   160,   161,   162,   164,   166,   167,   168,   169,
     170,   172
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "HEADER",
  "PREPROCESSOR", "CLASS", "INT", "FLOAT", "VOID", "IF", "ELSE", "FOR",
  "WHILE", "RETURN", "MAIN", "PRINTF", "INT_CONST", "FLOAT_CONST", "ID",
  "STRING_LITERAL", "OP_ARITH", "OP_REL", "OP_ASSIGN", "'{'", "'}'", "';'",
  "'('", "')'", "','", "'['", "']'", "'.'", "$accept", "Program",
  "Elements", "Element", "ClassDef", "$@1", "ClassMembers", "ClassMember",
  "ConstructorDef", "MethodDef", "$@2", "FunctionDef", "$@3", "MainFunc",
  "$@4", "Type", "Params", "ParamList", "Param", "Statements", "Statement",
  "ScopeStmt", "Declaration", "Assignment", "IfStmt", "WhileStmt",
  "ForStmt", "PrintfStmt", "ReturnStmt", "MethodCallStmt", "Expression",
  "Term", "Factor", "MethodCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,  -125,  -125,   -10,    22,  -125,  -125,    53,  -125,    77,
    -125,  -125,  -125,    72,    43,    28,  -125,  -125,    78,  -125,
      65,   103,    24,    75,  -125,    76,    94,  -125,    95,    15,
      98,    24,  -125,  -125,    88,  -125,  -125,  -125,   101,   103,
     100,   103,   104,  -125,    38,    11,  -125,  -125,    96,   105,
    -125,    96,  -125,   103,   107,   108,   109,   110,    96,   111,
      17,    11,   112,   114,    11,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,    11,  -125,  -125,    71,    29,  -125,
    -125,  -125,   116,    31,   106,    97,    96,   113,    96,    66,
     121,    96,   123,   124,   119,    36,  -125,  -125,   120,   118,
     128,    96,    96,    96,    11,  -125,   125,   122,    48,   127,
      50,  -125,   126,    68,   129,   130,  -125,    99,  -125,  -125,
     131,  -125,  -125,    52,   133,  -125,  -125,    11,   134,    11,
     135,  -125,   136,   137,    70,  -125,   138,  -125,    11,   141,
     140,  -125,    47,   102,   142,   -16,   144,  -125,   145,    11,
     148,   143,   152,    79,    82,  -125,   132,   146,  -125,  -125,
     150,  -125,   147,   155,  -125,   139,   149,   156,   151,   153,
     154,   157,   159,   160,   166,   162,  -125,   161,  -125,   170,
    -125,   169,   165,   171,  -125,   167,    11,  -125
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     6,     0,    24,    25,    26,     0,     2,     4,
       7,     8,     9,     0,     0,     0,     1,     3,     0,    10,
       0,    28,     0,     0,    24,     0,     0,    27,    30,     0,
       0,    13,    15,    16,     0,    14,    22,    31,     0,     0,
       0,    28,     0,    12,     0,    34,    20,    29,     0,     0,
      11,     0,    45,    28,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,    33,    43,    35,    36,    37,    38,
      39,    40,    41,    42,    34,    67,    68,    66,     0,    64,
      65,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    32,     0,     0,
       0,     0,     0,     0,    34,    46,     0,     0,     0,     0,
       0,    58,     0,     0,     0,     0,    44,     0,    21,    71,
       0,    62,    63,     0,     0,    18,    47,     0,     0,     0,
       0,    49,     0,     0,    66,    69,     0,    17,    34,    53,
       0,    54,     0,     0,     0,     0,     0,    48,     0,     0,
       0,     0,     0,    66,     0,    59,     0,     0,    19,    52,
       0,    56,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,    60,     0,    57,     0,
      61,     0,     0,     0,    51,     0,     0,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,   183,  -125,  -125,  -125,   164,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,     6,   -32,    89,  -125,   -60,
    -124,  -125,   -15,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
     -48,   -89,  -125,  -125
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    22,    30,    31,    32,    33,
     138,    11,    74,    12,    45,    62,    26,    27,    28,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      83,    79,    80,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      78,    94,   156,   139,    97,   141,    13,    35,    14,    49,
      89,   119,   121,   122,    98,    13,    35,    24,     5,     6,
      55,    84,    56,    57,    58,   159,    59,    25,    34,    60,
      24,     5,     6,    40,    61,    40,    15,    34,   108,    91,
     110,    41,    29,   113,   124,    25,    92,    25,    93,   101,
     102,   101,   102,    16,    20,   123,   105,   103,   117,    25,
      51,    52,   187,    52,    53,    54,    19,    54,   101,   102,
     101,   102,   101,   102,   151,   127,   152,   129,   148,   136,
       1,     2,     3,     4,     5,     6,   101,   102,   101,   102,
      18,   111,    23,   131,    37,   154,   145,    99,    36,   100,
     100,   146,   101,   102,    21,    99,    44,   164,   163,    24,
       5,     6,    75,    76,    77,    75,    76,   134,    75,    76,
     153,    38,    42,    39,    46,    85,    48,   107,    47,    50,
      95,   109,    82,   106,    86,    87,    88,    90,    96,   104,
     112,   114,   115,   116,   118,   119,   120,   126,   125,   128,
     140,   149,     0,   142,   130,   170,   133,   137,   143,   132,
     165,   135,   157,   147,   144,   150,   160,   155,   161,   158,
     162,   167,   166,   169,   172,     0,   171,   168,   173,   181,
       0,   175,   176,   174,   177,   178,   179,   180,   182,   183,
     184,   185,    17,     0,   186,    43
};

static const yytype_int16 yycheck[] =
{
      48,    61,    18,   127,    64,   129,     0,    22,    18,    41,
      58,    27,   101,   102,    74,     9,    31,     6,     7,     8,
       9,    53,    11,    12,    13,   149,    15,    21,    22,    18,
       6,     7,     8,    18,    23,    18,    14,    31,    86,    22,
      88,    26,    18,    91,   104,    39,    29,    41,    31,    20,
      21,    20,    21,     0,    26,   103,    25,    28,    22,    53,
      22,    25,   186,    25,    26,    29,    23,    29,    20,    21,
      20,    21,    20,    21,    27,    27,    29,    27,   138,    27,
       3,     4,     5,     6,     7,     8,    20,    21,    20,    21,
      18,    25,    27,    25,    18,   143,    26,    26,    23,    29,
      29,    31,    20,    21,    26,    26,    18,    25,    29,     6,
       7,     8,    16,    17,    18,    16,    17,    18,    16,    17,
      18,    27,    24,    28,    23,    18,    26,    30,    39,    25,
      18,    18,    27,    27,    26,    26,    26,    26,    24,    23,
      19,    18,    18,    24,    24,    27,    18,    25,    23,    22,
      16,    10,    -1,    18,    28,    16,    26,    24,    22,    30,
      28,    30,    18,    25,    27,    25,    18,    25,    25,    24,
      18,    21,    26,    18,    18,    -1,    27,    30,    27,    18,
      -1,    27,    25,    30,    25,    25,    20,    25,    18,    20,
      25,    20,     9,    -1,    27,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    33,    34,    35,
      36,    43,    45,    47,    18,    14,     0,    34,    18,    23,
      26,    26,    37,    27,     6,    47,    48,    49,    50,    18,
      38,    39,    40,    41,    47,    54,    23,    18,    27,    28,
      18,    26,    24,    38,    18,    46,    23,    49,    26,    48,
      25,    22,    25,    26,    29,     9,    11,    12,    13,    15,
      18,    23,    47,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    44,    16,    17,    18,    62,    63,
      64,    65,    27,    62,    48,    18,    26,    26,    26,    62,
      26,    22,    29,    31,    51,    18,    24,    51,    51,    26,
      29,    20,    21,    28,    23,    25,    27,    30,    62,    18,
      62,    25,    19,    62,    18,    18,    24,    22,    24,    27,
      18,    63,    63,    62,    51,    23,    25,    27,    22,    27,
      28,    25,    30,    26,    18,    30,    27,    24,    42,    52,
      16,    52,    18,    22,    27,    26,    31,    25,    51,    10,
      25,    27,    29,    18,    62,    25,    18,    18,    24,    52,
      18,    25,    18,    29,    25,    28,    26,    21,    30,    18,
      16,    27,    18,    27,    30,    27,    25,    25,    25,    20,
      25,    18,    18,    20,    25,    20,    27,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      37,    36,    38,    38,    39,    39,    39,    40,    42,    41,
      44,    43,    46,    45,    47,    47,    47,    48,    48,    49,
      49,    50,    51,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    54,    54,    54,    55,
      55,    55,    56,    56,    57,    58,    59,    59,    60,    61,
      61,    61,    62,    62,    62,    63,    64,    64,    64,    64,
      64,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       0,     7,     2,     1,     1,     1,     1,     7,     0,     9,
       0,     9,     0,     8,     1,     1,     1,     1,     0,     3,
       1,     2,     2,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     6,     8,     4,
       7,    12,     7,     5,     5,    15,     7,    10,     3,     6,
       9,    10,     3,     3,     1,     1,     1,     1,     1,     4,
       1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 10: /* $@1: %empty  */
#line 109 "y.y"
                       { current_scope = 1; }
#line 1394 "y.tab.c"
    break;

  case 11: /* ClassDef: CLASS ID '{' $@1 ClassMembers '}' ';'  */
#line 109 "y.y"
                                                                   { current_scope = 0; }
#line 1400 "y.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 117 "y.y"
                                      { expected_return_type = (yyvsp[-5].type); current_scope = 2; }
#line 1406 "y.tab.c"
    break;

  case 19: /* MethodDef: Type ID '(' Params ')' '{' $@2 Statements '}'  */
#line 117 "y.y"
                                                                                                       { current_scope = 1; }
#line 1412 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 119 "y.y"
                                        { expected_return_type = (yyvsp[-5].type); current_scope = 2; }
#line 1418 "y.tab.c"
    break;

  case 21: /* FunctionDef: Type ID '(' Params ')' '{' $@3 Statements '}'  */
#line 119 "y.y"
                                                                                                         { current_scope = 0; }
#line 1424 "y.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 121 "y.y"
                               { expected_return_type = 0; current_scope = 2; }
#line 1430 "y.tab.c"
    break;

  case 23: /* MainFunc: INT MAIN '(' ')' '{' $@4 Statements '}'  */
#line 121 "y.y"
                                                                                               { current_scope = 0; }
#line 1436 "y.tab.c"
    break;

  case 24: /* Type: INT  */
#line 123 "y.y"
          { (yyval.type) = 0; }
#line 1442 "y.tab.c"
    break;

  case 25: /* Type: FLOAT  */
#line 123 "y.y"
                              { (yyval.type) = 1; }
#line 1448 "y.tab.c"
    break;

  case 26: /* Type: VOID  */
#line 123 "y.y"
                                                 { (yyval.type) = 2; }
#line 1454 "y.tab.c"
    break;

  case 31: /* Param: Type ID  */
#line 127 "y.y"
               { add_symbol((yyvsp[0].str), (yyvsp[-1].type)); }
#line 1460 "y.tab.c"
    break;

  case 45: /* Declaration: Type ID ';'  */
#line 135 "y.y"
                         { add_symbol((yyvsp[-1].str), (yyvsp[-2].type)); }
#line 1466 "y.tab.c"
    break;

  case 46: /* Declaration: Type ID OP_ASSIGN Expression ';'  */
#line 136 "y.y"
                                              { add_symbol((yyvsp[-3].str), (yyvsp[-4].type)); check_assignment((yyvsp[-3].str), (yyvsp[-1].type)); }
#line 1472 "y.tab.c"
    break;

  case 47: /* Declaration: Type ID '[' ID ']' ';'  */
#line 137 "y.y"
                                    { add_symbol((yyvsp[-4].str), (yyvsp[-5].type)); }
#line 1478 "y.tab.c"
    break;

  case 48: /* Declaration: ID ID '(' Expression ',' Expression ')' ';'  */
#line 138 "y.y"
                                                         { add_symbol((yyvsp[-6].str), 3); /* Class instance */ }
#line 1484 "y.tab.c"
    break;

  case 49: /* Assignment: ID OP_ASSIGN Expression ';'  */
#line 140 "y.y"
                                        { check_assignment((yyvsp[-3].str), (yyvsp[-1].type)); }
#line 1490 "y.tab.c"
    break;

  case 50: /* Assignment: ID '[' ID ']' OP_ASSIGN Expression ';'  */
#line 141 "y.y"
                                                   { check_array_index(get_symbol_type((yyvsp[-4].str))); }
#line 1496 "y.tab.c"
    break;

  case 51: /* Assignment: ID '[' ID ']' OP_ASSIGN ID '[' ID ']' OP_ARITH ID ';'  */
#line 142 "y.y"
                                                                  { check_array_index(get_symbol_type((yyvsp[-9].str))); check_array_index(get_symbol_type((yyvsp[-4].str))); }
#line 1502 "y.tab.c"
    break;

  case 58: /* ReturnStmt: RETURN Expression ';'  */
#line 154 "y.y"
                                  { check_return_type((yyvsp[-1].type)); }
#line 1508 "y.tab.c"
    break;

  case 60: /* MethodCallStmt: Type ID OP_ASSIGN ID '.' ID '(' ')' ';'  */
#line 157 "y.y"
                                                        { add_symbol((yyvsp[-7].str), (yyvsp[-8].type)); }
#line 1514 "y.tab.c"
    break;

  case 61: /* MethodCallStmt: Type ID OP_ASSIGN ID '(' ID ',' INT_CONST ')' ';'  */
#line 158 "y.y"
                                                                  { add_symbol((yyvsp[-8].str), (yyvsp[-9].type)); }
#line 1520 "y.tab.c"
    break;

  case 62: /* Expression: Expression OP_ARITH Term  */
#line 160 "y.y"
                                     { (yyval.type) = ((yyvsp[-2].type) == 1 || (yyvsp[0].type) == 1) ? 1 : 0; }
#line 1526 "y.tab.c"
    break;

  case 63: /* Expression: Expression OP_REL Term  */
#line 161 "y.y"
                                   { (yyval.type) = 0; }
#line 1532 "y.tab.c"
    break;

  case 64: /* Expression: Term  */
#line 162 "y.y"
                 { (yyval.type) = (yyvsp[0].type); }
#line 1538 "y.tab.c"
    break;

  case 65: /* Term: Factor  */
#line 164 "y.y"
             { (yyval.type) = (yyvsp[0].type); }
#line 1544 "y.tab.c"
    break;

  case 66: /* Factor: ID  */
#line 166 "y.y"
           { (yyval.type) = get_symbol_type((yyvsp[0].str)); }
#line 1550 "y.tab.c"
    break;

  case 67: /* Factor: INT_CONST  */
#line 167 "y.y"
                  { (yyval.type) = 0; }
#line 1556 "y.tab.c"
    break;

  case 68: /* Factor: FLOAT_CONST  */
#line 168 "y.y"
                    { (yyval.type) = 1; }
#line 1562 "y.tab.c"
    break;

  case 69: /* Factor: ID '[' ID ']'  */
#line 169 "y.y"
                      { (yyval.type) = get_symbol_type((yyvsp[-3].str)); check_array_index(get_symbol_type((yyvsp[-1].str))); }
#line 1568 "y.tab.c"
    break;

  case 70: /* Factor: MethodCall  */
#line 170 "y.y"
                   { (yyval.type) = (yyvsp[0].type); }
#line 1574 "y.tab.c"
    break;

  case 71: /* MethodCall: ID '(' ')'  */
#line 172 "y.y"
                       { (yyval.type) = 0; }
#line 1580 "y.tab.c"
    break;


#line 1584 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 174 "y.y"


void yyerror(const char *s) {}

int main() {
    out_fp = fopen("outputNoErrors.txt", "w");
    if (!out_fp) {
        printf("Error opening output file!\n");
        return 1;
    }
    
    fprintf(out_fp, "TOKENS\n");
    yyin = fopen("noErrors.txt", "r");
    yyparse();
    
    print_symbol_table();
    
    fprintf(out_fp, "\nERRORS\n");
    if (errors > 0) {
        fprintf(out_fp, "Errors: %d\n", errors);
        fprintf(out_fp, "Program not accepted.\n");
    } else {
        fprintf(out_fp, "Output: No error\n");
        fprintf(out_fp, "Code accepted\n");
    }
    
    fclose(out_fp);
    return 0;
}
