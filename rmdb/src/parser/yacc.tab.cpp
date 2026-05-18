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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 86 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"

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

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SHOW = 3,                       /* SHOW  */
  YYSYMBOL_TABLES = 4,                     /* TABLES  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_DROP = 7,                       /* DROP  */
  YYSYMBOL_DESC = 8,                       /* DESC  */
  YYSYMBOL_INSERT = 9,                     /* INSERT  */
  YYSYMBOL_INTO = 10,                      /* INTO  */
  YYSYMBOL_VALUES = 11,                    /* VALUES  */
  YYSYMBOL_DELETE = 12,                    /* DELETE  */
  YYSYMBOL_FROM = 13,                      /* FROM  */
  YYSYMBOL_ASC = 14,                       /* ASC  */
  YYSYMBOL_ORDER = 15,                     /* ORDER  */
  YYSYMBOL_BY = 16,                        /* BY  */
  YYSYMBOL_WHERE = 17,                     /* WHERE  */
  YYSYMBOL_UPDATE = 18,                    /* UPDATE  */
  YYSYMBOL_SET = 19,                       /* SET  */
  YYSYMBOL_SELECT = 20,                    /* SELECT  */
  YYSYMBOL_INT = 21,                       /* INT  */
  YYSYMBOL_CHAR = 22,                      /* CHAR  */
  YYSYMBOL_FLOAT = 23,                     /* FLOAT  */
  YYSYMBOL_INDEX = 24,                     /* INDEX  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_JOIN = 26,                      /* JOIN  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_DEFAULT = 29,                   /* DEFAULT  */
  YYSYMBOL_PRIMARY = 30,                   /* PRIMARY  */
  YYSYMBOL_KEY = 31,                       /* KEY  */
  YYSYMBOL_AUTO_INCREMENT = 32,            /* AUTO_INCREMENT  */
  YYSYMBOL_AS = 33,                        /* AS  */
  YYSYMBOL_CONCAT = 34,                    /* CONCAT  */
  YYSYMBOL_VIEW = 35,                      /* VIEW  */
  YYSYMBOL_UNIQUE = 36,                    /* UNIQUE  */
  YYSYMBOL_DATE = 37,                      /* DATE  */
  YYSYMBOL_TEXT = 38,                      /* TEXT  */
  YYSYMBOL_TXN_BEGIN = 39,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 40,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 41,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 42,              /* TXN_ROLLBACK  */
  YYSYMBOL_ENABLE_NESTLOOP = 43,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 44,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_AVG = 45,                       /* AVG  */
  YYSYMBOL_BETWEEN = 46,                   /* BETWEEN  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_DISTINCT = 48,                  /* DISTINCT  */
  YYSYMBOL_FULL = 49,                      /* FULL  */
  YYSYMBOL_GROUP = 50,                     /* GROUP  */
  YYSYMBOL_HAVING = 51,                    /* HAVING  */
  YYSYMBOL_IN = 52,                        /* IN  */
  YYSYMBOL_INNER = 53,                     /* INNER  */
  YYSYMBOL_IS = 54,                        /* IS  */
  YYSYMBOL_LEFT = 55,                      /* LEFT  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_LIMIT = 57,                     /* LIMIT  */
  YYSYMBOL_MAX = 58,                       /* MAX  */
  YYSYMBOL_MIN = 59,                       /* MIN  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_OFFSET = 61,                    /* OFFSET  */
  YYSYMBOL_ON = 62,                        /* ON  */
  YYSYMBOL_OR = 63,                        /* OR  */
  YYSYMBOL_RIGHT = 64,                     /* RIGHT  */
  YYSYMBOL_SUM = 65,                       /* SUM  */
  YYSYMBOL_LEQ = 66,                       /* LEQ  */
  YYSYMBOL_NEQ = 67,                       /* NEQ  */
  YYSYMBOL_GEQ = 68,                       /* GEQ  */
  YYSYMBOL_T_EOF = 69,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 70,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 71,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 72,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 73,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 74,                /* VALUE_BOOL  */
  YYSYMBOL_VALUE_NULL = 75,                /* VALUE_NULL  */
  YYSYMBOL_76_ = 76,                       /* ';'  */
  YYSYMBOL_77_ = 77,                       /* '='  */
  YYSYMBOL_78_ = 78,                       /* '('  */
  YYSYMBOL_79_ = 79,                       /* ')'  */
  YYSYMBOL_80_ = 80,                       /* ','  */
  YYSYMBOL_81_ = 81,                       /* '+'  */
  YYSYMBOL_82_ = 82,                       /* '-'  */
  YYSYMBOL_83_ = 83,                       /* '*'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_85_ = 85,                       /* '%'  */
  YYSYMBOL_86_ = 86,                       /* '.'  */
  YYSYMBOL_87_ = 87,                       /* '<'  */
  YYSYMBOL_88_ = 88,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_start = 90,                     /* start  */
  YYSYMBOL_stmt = 91,                      /* stmt  */
  YYSYMBOL_txnStmt = 92,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 93,                    /* dbStmt  */
  YYSYMBOL_setStmt = 94,                   /* setStmt  */
  YYSYMBOL_ddl = 95,                       /* ddl  */
  YYSYMBOL_dml = 96,                       /* dml  */
  YYSYMBOL_fieldList = 97,                 /* fieldList  */
  YYSYMBOL_colNameList = 98,               /* colNameList  */
  YYSYMBOL_optColList = 99,                /* optColList  */
  YYSYMBOL_field = 100,                    /* field  */
  YYSYMBOL_type = 101,                     /* type  */
  YYSYMBOL_valueList = 102,                /* valueList  */
  YYSYMBOL_valueTupleList = 103,           /* valueTupleList  */
  YYSYMBOL_value = 104,                    /* value  */
  YYSYMBOL_condition = 105,                /* condition  */
  YYSYMBOL_cond_or = 106,                  /* cond_or  */
  YYSYMBOL_cond_and = 107,                 /* cond_and  */
  YYSYMBOL_cond_not = 108,                 /* cond_not  */
  YYSYMBOL_cond_base = 109,                /* cond_base  */
  YYSYMBOL_optWhereClause = 110,           /* optWhereClause  */
  YYSYMBOL_optHaving = 111,                /* optHaving  */
  YYSYMBOL_expr = 112,                     /* expr  */
  YYSYMBOL_expr_add_sub = 113,             /* expr_add_sub  */
  YYSYMBOL_expr_mul_div = 114,             /* expr_mul_div  */
  YYSYMBOL_expr_unary = 115,               /* expr_unary  */
  YYSYMBOL_expr_base = 116,                /* expr_base  */
  YYSYMBOL_aggType = 117,                  /* aggType  */
  YYSYMBOL_aggExpr = 118,                  /* aggExpr  */
  YYSYMBOL_optDistinct = 119,              /* optDistinct  */
  YYSYMBOL_selectItems = 120,              /* selectItems  */
  YYSYMBOL_selectItemList = 121,           /* selectItemList  */
  YYSYMBOL_opt_alias = 122,                /* opt_alias  */
  YYSYMBOL_optAliasStr = 123,              /* optAliasStr  */
  YYSYMBOL_fromList = 124,                 /* fromList  */
  YYSYMBOL_optJoinList = 125,              /* optJoinList  */
  YYSYMBOL_joinList = 126,                 /* joinList  */
  YYSYMBOL_joinType = 127,                 /* joinType  */
  YYSYMBOL_joinClause = 128,               /* joinClause  */
  YYSYMBOL_optGroupBy = 129,               /* optGroupBy  */
  YYSYMBOL_optLimit = 130,                 /* optLimit  */
  YYSYMBOL_col = 131,                      /* col  */
  YYSYMBOL_colList = 132,                  /* colList  */
  YYSYMBOL_op = 133,                       /* op  */
  YYSYMBOL_setClauses = 134,               /* setClauses  */
  YYSYMBOL_setClause = 135,                /* setClause  */
  YYSYMBOL_opt_order_clause = 136,         /* opt_order_clause  */
  YYSYMBOL_order_clause = 137,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 138,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 139,            /* set_knob_type  */
  YYSYMBOL_expr_list = 140,                /* expr_list  */
  YYSYMBOL_tbName = 141,                   /* tbName  */
  YYSYMBOL_colName = 142                   /* colName  */
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
typedef yytype_int16 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       2,     2,     2,     2,     2,     2,     2,    85,     2,     2,
      78,    79,    83,    81,    80,    82,    86,    84,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    76,
      87,    77,    88,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    84,    89,    94,   102,   103,   104,   105,
     106,   110,   114,   118,   122,   129,   136,   143,   147,   151,
     155,   159,   164,   168,   172,   176,   183,   187,   191,   195,
     231,   235,   242,   246,   254,   257,   264,   268,   272,   276,
     280,   284,   290,   296,   302,   312,   316,   321,   326,   330,
     334,   338,   346,   350,   357,   361,   368,   372,   376,   380,
     384,   396,   400,   401,   409,   410,   418,   419,   427,   431,
     435,   439,   443,   447,   451,   455,   459,   463,   467,   471,
     479,   482,   490,   493,   504,   508,   509,   513,   520,   521,
     525,   529,   536,   537,   544,   548,   552,   556,   560,   564,
     575,   576,   577,   578,   579,   583,   587,   603,   604,   608,
     612,   616,   620,   627,   628,   629,   630,   631,   632,   633,
     634,   638,   639,   640,   641,   642,   643,   644,   645,   649,
     654,   663,   666,   673,   677,   684,   685,   686,   687,   691,
     695,   699,   703,   711,   714,   722,   725,   729,   736,   740,
     747,   751,   758,   762,   766,   770,   774,   778,   785,   789,
     796,   803,   807,   811,   815,   822,   823,   824,   828,   829,
     833,   837,   843,   845
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SHOW", "TABLES",
  "CREATE", "TABLE", "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE",
  "FROM", "ASC", "ORDER", "BY", "WHERE", "UPDATE", "SET", "SELECT", "INT",
  "CHAR", "FLOAT", "INDEX", "AND", "JOIN", "EXIT", "HELP", "DEFAULT",
  "PRIMARY", "KEY", "AUTO_INCREMENT", "AS", "CONCAT", "VIEW", "UNIQUE",
  "DATE", "TEXT", "TXN_BEGIN", "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK",
  "ENABLE_NESTLOOP", "ENABLE_SORTMERGE", "AVG", "BETWEEN", "COUNT",
  "DISTINCT", "FULL", "GROUP", "HAVING", "IN", "INNER", "IS", "LEFT",
  "LIKE", "LIMIT", "MAX", "MIN", "NOT", "OFFSET", "ON", "OR", "RIGHT",
  "SUM", "LEQ", "NEQ", "GEQ", "T_EOF", "IDENTIFIER", "VALUE_STRING",
  "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "VALUE_NULL", "';'", "'='",
  "'('", "')'", "','", "'+'", "'-'", "'*'", "'/'", "'%'", "'.'", "'<'",
  "'>'", "$accept", "start", "stmt", "txnStmt", "dbStmt", "setStmt", "ddl",
  "dml", "fieldList", "colNameList", "optColList", "field", "type",
  "valueList", "valueTupleList", "value", "condition", "cond_or",
  "cond_and", "cond_not", "cond_base", "optWhereClause", "optHaving",
  "expr", "expr_add_sub", "expr_mul_div", "expr_unary", "expr_base",
  "aggType", "aggExpr", "optDistinct", "selectItems", "selectItemList",
  "opt_alias", "optAliasStr", "fromList", "optJoinList", "joinList",
  "joinType", "joinClause", "optGroupBy", "optLimit", "col", "colList",
  "op", "setClauses", "setClause", "opt_order_clause", "order_clause",
  "opt_asc_desc", "set_knob_type", "expr_list", "tbName", "colName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-173)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     276,    16,    63,    89,   -45,    33,    48,   -45,    50,    17,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,    77,     9,  -192,
    -192,  -192,  -192,  -192,  -192,   -45,   -45,   -45,    72,   -45,
     -45,   -45,  -192,  -192,   -45,   -45,    86,  -192,  -192,    35,
    -192,   255,  -192,  -192,    37,   -28,    93,   -45,  -192,    51,
    -192,    53,   119,    84,    65,    64,  -192,  -192,  -192,  -192,
    -192,    75,  -192,  -192,  -192,  -192,  -192,   200,   310,  -192,
    -192,   -15,   -66,   157,  -192,  -192,    87,  -192,   180,   115,
    -192,   121,  -192,    84,   -45,    84,   205,   149,    84,    84,
     208,   289,  -192,  -192,    -8,  -192,   147,  -192,   310,   150,
     159,  -192,    62,  -192,  -192,   310,   310,   310,   310,   310,
     -12,   -45,   310,    84,    69,  -192,   168,   148,    92,  -192,
    -192,   -45,    94,    97,   177,   289,   110,  -192,   203,   242,
    -192,  -192,    79,   245,    84,  -192,   129,  -192,   152,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,   157,   157,  -192,
    -192,  -192,   189,   190,     4,   -14,   -15,  -192,  -192,    84,
    -192,   198,   199,  -192,  -192,    22,    84,  -192,    84,   202,
    -192,  -192,   129,   206,  -192,   211,   169,   289,   289,  -192,
    -192,  -192,  -192,  -192,  -192,   310,   129,   209,   -46,   221,
     107,  -192,  -192,  -192,   310,  -192,  -192,   -45,  -192,  -192,
    -192,  -192,   -45,   119,    88,   267,  -192,   163,  -192,  -192,
    -192,  -192,   226,   234,   129,   277,  -192,   232,  -192,   164,
    -192,    84,   170,  -192,   231,  -192,   242,  -192,  -192,   285,
      29,   236,  -192,  -192,   129,   241,   250,  -192,   -14,   -14,
     262,  -192,   -45,  -192,  -192,  -192,  -192,  -192,  -192,   243,
     244,  -192,   299,    31,  -192,   172,  -192,   129,   129,   129,
     253,   174,  -192,   314,    29,  -192,   273,  -192,   324,   290,
     -14,  -192,   270,  -192,   129,  -192,  -192,  -192,   181,  -192,
    -192,  -192,   129,   264,   183,   289,   280,   289,   331,   291,
     272,  -192,  -192,  -192,  -192,  -192,  -192,  -192,   278,  -192,
     336,   308,   289,  -192,   280,   280,   284,  -192,  -192,  -192,
       3,   286,   309,  -192,  -192,  -192,   280,   300,     3,  -192,
    -192
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       4,     3,    11,    12,    13,    14,     5,     0,     0,     9,
       6,    10,     7,     8,    15,     0,     0,     0,     0,     0,
       0,     0,   172,    19,     0,     0,     0,   168,   169,     0,
     108,     0,     1,     2,     0,     0,     0,     0,    18,     0,
      25,    34,    80,     0,     0,     0,   102,   100,   103,   104,
     101,   173,    58,    56,    57,    59,    60,     0,     0,   109,
      94,   113,    84,    85,    88,    92,     0,    96,     0,   110,
      95,     0,   149,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,   173,    80,   158,     0,    16,     0,     0,
       0,    93,     0,   114,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,    32,
      24,     0,     0,     0,     0,     0,     0,    81,    61,    62,
      64,    66,     0,    95,     0,    28,     0,   170,     0,    98,
      99,   117,   116,   119,   120,   118,   115,    86,    87,    89,
      90,    91,     0,     0,   131,   121,   113,   148,    17,     0,
      45,    47,    50,    48,    49,    36,     0,    20,     0,     0,
      23,    35,     0,    26,    67,     0,     0,     0,     0,   156,
     155,   157,   152,   153,   154,     0,     0,     0,     0,     0,
       0,   159,   160,    97,     0,   106,   105,     0,   138,   135,
     136,   137,     0,    80,   132,     0,   133,     0,   122,   129,
     112,    31,     0,     0,     0,     0,    42,     0,    37,     0,
      33,     0,     0,    52,     0,    79,    63,    65,    68,     0,
       0,     0,    69,    71,     0,     0,     0,   171,   121,   121,
     143,   134,     0,   125,   124,   127,   128,   126,   123,     0,
       0,    39,    41,    38,    21,     0,    54,     0,     0,     0,
       0,     0,    70,     0,     0,    72,   142,   130,     0,    82,
     121,    46,     0,    44,     0,    43,    22,    53,     0,    73,
      77,    75,     0,     0,     0,     0,     0,     0,   162,   141,
       0,    40,    55,    74,    78,    76,   140,   150,   144,    83,
       0,   145,     0,    51,     0,     0,     0,    29,   139,   151,
     167,   161,   146,   166,   165,   163,     0,     0,   167,   147,
     164
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,  -192,  -192,  -192,     0,  -192,   -83,
    -192,   214,  -192,  -191,  -192,  -124,  -123,  -192,   197,  -112,
    -192,   -86,  -192,   -34,  -192,    81,   -33,  -192,  -192,  -192,
    -192,  -192,  -192,   220,  -159,  -192,  -192,  -192,  -192,   173,
    -192,  -192,   -89,  -192,  -192,  -192,   252,  -192,  -192,    60,
    -192,  -192,    -3,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    17,    18,    19,    20,    21,    22,    99,   114,   118,
      90,   115,   165,   222,   173,    70,   127,   128,   129,   130,
     131,    92,   288,   132,    72,    73,    74,    75,    76,    77,
      41,    78,    79,   104,   209,   154,   203,   204,   205,   206,
     269,   307,    80,   298,   185,    94,    95,   301,   311,   315,
      39,   138,    81,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    33,   133,   175,    36,   122,   123,    71,   135,    91,
      96,   313,   192,   174,   231,   105,   106,   314,   102,   207,
      24,   153,    44,    45,    46,    32,    48,    49,    50,   232,
     197,    51,    52,   100,    84,   101,   133,   133,     5,   261,
     116,     6,   119,    34,    87,   119,   119,     7,   223,     9,
      85,   214,   215,   198,   216,   103,   208,   199,    61,   200,
     274,    35,   229,   275,   137,    40,   227,   278,   201,    25,
     157,   152,   134,   284,   149,   150,   151,    42,   156,   266,
     267,   117,   217,   219,   202,    43,   120,    26,   133,   133,
     251,    96,   176,    37,    38,    29,    47,   218,    27,    28,
      62,    63,    64,    65,    66,    53,   223,   141,   155,   142,
     263,   289,    54,    30,   197,    83,   116,   240,   169,     5,
     143,   144,     6,   119,    31,   220,    86,   145,     7,    88,
       9,    89,   146,   277,   223,   279,    91,   198,   255,    97,
     223,   199,    98,   200,    55,   179,   180,   181,   158,   159,
     291,   228,   201,   234,    93,    56,   182,    57,   293,   235,
     237,  -172,   296,   236,   299,   110,   183,   184,    58,    59,
     125,   167,   168,   170,   168,    60,   171,   168,   119,   308,
      61,    62,    63,    64,    65,    66,   147,   148,   126,   160,
     161,   162,    68,   111,   238,   112,   133,   297,   133,   239,
      62,    63,    64,    65,    66,   163,   164,   113,   243,     5,
     244,   121,     6,   133,     5,   309,   310,     6,     7,   124,
       9,   245,   246,     7,   136,     9,   166,   318,   247,   139,
     260,   193,   194,   248,    55,   179,   180,   181,   140,   270,
     107,   108,   109,   254,   168,    56,   182,    57,   140,   256,
     257,   276,   168,   281,   257,   172,   183,   184,    58,    59,
     292,   257,   295,   257,   283,    60,   177,   178,   195,   196,
      61,    62,    63,    64,    65,    66,   212,   213,    67,     1,
     221,     2,    68,     3,     4,     5,   224,   230,     6,    55,
     225,   186,   233,   242,     7,     8,     9,   187,   249,   188,
      56,   189,    57,    10,    11,   190,   250,   253,   252,   258,
     259,   262,   268,    58,    59,    12,    13,    14,    15,   264,
      60,   265,   271,    55,   272,    61,    62,    63,    64,    65,
      66,   273,   280,    67,    56,   285,    57,    68,    69,   282,
     286,   287,   290,   294,    55,    16,   300,    58,    59,   125,
      61,   303,   305,   302,    60,    56,   312,    57,   304,    61,
      62,    63,    64,    65,    66,   306,   316,   126,    58,    59,
     317,    68,   319,   211,   226,    60,   210,   241,   320,     0,
      61,    62,    63,    64,    65,    66,   191,     0,    67,     0,
       0,     0,    68
};

static const yytype_int16 yycheck[] =
{
       0,     4,    91,   126,     7,    88,    89,    41,    94,    17,
      53,     8,   136,   125,    60,    81,    82,    14,    33,    33,
       4,   110,    25,    26,    27,    70,    29,    30,    31,    75,
      26,    34,    35,    67,    62,    68,   125,   126,     9,   230,
      83,    12,    85,    10,    47,    88,    89,    18,   172,    20,
      78,    29,    30,    49,    32,    70,    70,    53,    70,    55,
      29,    13,   186,    32,    98,    48,   178,   258,    64,     6,
     113,    83,    80,   264,   107,   108,   109,     0,   112,   238,
     239,    84,    60,   166,    80,    76,    86,    24,   177,   178,
     214,   134,   126,    43,    44,     6,    24,    75,    35,    36,
      71,    72,    73,    74,    75,    19,   230,    45,   111,    47,
     234,   270,    77,    24,    26,    78,   159,   203,   121,     9,
      58,    59,    12,   166,    35,   168,    33,    65,    18,    78,
      20,    78,    70,   257,   258,   259,    17,    49,   221,    74,
     264,    53,    78,    55,    34,    66,    67,    68,    79,    80,
     274,   185,    64,    46,    70,    45,    77,    47,   282,    52,
     194,    86,   285,    56,   287,    78,    87,    88,    58,    59,
      60,    79,    80,    79,    80,    65,    79,    80,   221,   302,
      70,    71,    72,    73,    74,    75,   105,   106,    78,    21,
      22,    23,    82,    13,   197,    80,   285,   286,   287,   202,
      71,    72,    73,    74,    75,    37,    38,    86,    45,     9,
      47,    62,    12,   302,     9,   304,   305,    12,    18,    11,
      20,    58,    59,    18,    77,    20,    78,   316,    65,    79,
     230,    79,    80,    70,    34,    66,    67,    68,    79,   242,
      83,    84,    85,    79,    80,    45,    77,    47,    79,    79,
      80,    79,    80,    79,    80,    78,    87,    88,    58,    59,
      79,    80,    79,    80,   264,    65,    63,    25,    79,    79,
      70,    71,    72,    73,    74,    75,    78,    78,    78,     3,
      78,     5,    82,     7,     8,     9,    80,    78,    12,    34,
      79,    46,    71,    26,    18,    19,    20,    52,    72,    54,
      45,    56,    47,    27,    28,    60,    72,    75,    31,    78,
      25,    75,    50,    58,    59,    39,    40,    41,    42,    78,
      65,    71,    79,    34,    80,    70,    71,    72,    73,    74,
      75,    32,    79,    78,    45,    62,    47,    82,    83,    25,
      16,    51,    72,    79,    34,    69,    15,    58,    59,    60,
      70,    79,    16,    62,    65,    45,    72,    47,    80,    70,
      71,    72,    73,    74,    75,    57,    80,    78,    58,    59,
      61,    82,    72,   159,   177,    65,   156,   204,   318,    -1,
      70,    71,    72,    73,    74,    75,   134,    -1,    78,    -1,
      -1,    -1,    82
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    39,    40,    41,    42,    69,    90,    91,    92,
      93,    94,    95,    96,     4,     6,    24,    35,    36,     6,
      24,    35,    70,   141,    10,    13,   141,    43,    44,   139,
      48,   119,     0,    76,   141,   141,   141,    24,   141,   141,
     141,   141,   141,    19,    77,    34,    45,    47,    58,    59,
      65,    70,    71,    72,    73,    74,    75,    78,    82,    83,
     104,   112,   113,   114,   115,   116,   117,   118,   120,   121,
     131,   141,   142,    78,    62,    78,    33,   141,    78,    78,
      99,    17,   110,    70,   134,   135,   142,    74,    78,    96,
     112,   115,    33,    70,   122,    81,    82,    83,    84,    85,
      78,    13,    80,    86,    97,   100,   142,   141,    98,   142,
      96,    62,    98,    98,    11,    60,    78,   105,   106,   107,
     108,   109,   112,   131,    80,   110,    77,   112,   140,    79,
      79,    45,    47,    58,    59,    65,    70,   114,   114,   115,
     115,   115,    83,   131,   124,   141,   112,   142,    79,    80,
      21,    22,    23,    37,    38,   101,    78,    79,    80,   141,
      79,    79,    78,   103,   108,   105,   112,    63,    25,    66,
      67,    68,    77,    87,    88,   133,    46,    52,    54,    56,
      60,   135,   104,    79,    80,    79,    79,    26,    49,    53,
      55,    64,    80,   125,   126,   127,   128,    33,    70,   123,
     122,   100,    78,    78,    29,    30,    32,    60,    75,    98,
     142,    78,   102,   104,    80,    79,   107,   108,   112,   104,
      78,    60,    75,    71,    46,    52,    56,   112,   141,   141,
     110,   128,    26,    45,    47,    58,    59,    65,    70,    72,
      72,   104,    31,    75,    79,    98,    79,    80,    78,    25,
      96,   102,    75,   104,    78,    71,   123,   123,    50,   129,
     141,    79,    80,    32,    29,    32,    79,   104,   102,   104,
      79,    79,    25,    96,   102,    62,    16,    51,   111,   123,
      72,   104,    79,   104,    79,    79,   105,   131,   132,   105,
      15,   136,    62,    79,    80,    16,    57,   130,   105,   131,
     131,   137,    72,     8,    14,   138,    80,    61,   131,    72,
     138
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    90,    90,    91,    91,    91,    91,
      91,    92,    92,    92,    92,    93,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    96,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   105,   106,   106,   107,   107,   108,   108,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   110,   111,   111,   112,   113,   113,   113,   114,   114,
     114,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124,   125,   125,   126,   126,   127,   127,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   130,   130,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   133,   134,   134,
     135,   136,   136,   137,   137,   138,   138,   138,   139,   139,
     140,   140,   141,   142
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     6,     3,     2,
       6,     8,     9,     6,     5,     3,     6,     4,     5,    11,
       1,     3,     1,     3,     0,     3,     2,     3,     4,     4,
       6,     4,     3,     5,     5,     1,     4,     1,     1,     1,
       1,     6,     1,     3,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     2,     3,     3,
       4,     3,     4,     5,     6,     5,     6,     5,     6,     3,
       0,     2,     0,     2,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     1,     1,     1,     4,     3,     3,
       1,     1,     1,     1,     1,     4,     4,     0,     1,     1,
       1,     2,     4,     0,     1,     2,     2,     2,     2,     2,
       2,     0,     1,     2,     2,     2,     2,     2,     2,     2,
       4,     0,     1,     1,     2,     1,     1,     1,     1,     6,
       5,     4,     3,     0,     3,     0,     2,     4,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     2,     4,     1,     1,     0,     1,     1,
       1,     3,     1,     1
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: stmt ';'  */
#line 80 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1862 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 85 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1871 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 90 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1880 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 95 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1889 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 111 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1897 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 115 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1905 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 119 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1913 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 123 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1921 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 130 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1929 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 137 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1937 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 144 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1945 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18: /* ddl: DROP TABLE tbName  */
#line 148 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1953 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19: /* ddl: DESC tbName  */
#line 152 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1961 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 156 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1969 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21: /* ddl: CREATE INDEX tbName ON tbName '(' colNameList ')'  */
#line 160 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Alternative: CREATE INDEX name ON table (cols)
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1978 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22: /* ddl: CREATE UNIQUE INDEX tbName ON tbName '(' colNameList ')'  */
#line 165 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1986 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 169 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1994 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24: /* ddl: CREATE VIEW tbName AS dml  */
#line 173 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateView>((yyvsp[-2].sv_str), (yyvsp[0].sv_node));
    }
#line 2002 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25: /* ddl: DROP VIEW tbName  */
#line 177 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropView>((yyvsp[0].sv_str));
    }
#line 2010 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26: /* dml: INSERT INTO tbName optColList VALUES valueTupleList  */
#line 184 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-3].sv_str), (yyvsp[-2].sv_strs), (yyvsp[0].sv_vals_list));
    }
#line 2018 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27: /* dml: DELETE FROM tbName optWhereClause  */
#line 188 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_cond));
    }
#line 2026 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 192 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_cond));
    }
#line 2034 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29: /* dml: SELECT optDistinct selectItems FROM fromList optJoinList optWhereClause optGroupBy optHaving opt_order_clause optLimit  */
#line 197 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto stmt = std::make_shared<SelectStmt>();
        stmt->has_distinct = (yyvsp[-9].sv_bool);
        // separate columns, aggregates, and expressions from select items
        for (auto &e : (yyvsp[-8].sv_exprs)) {
            if (auto c = std::dynamic_pointer_cast<Col>(e)) {
                stmt->cols.push_back(c);
            } else if (auto a = std::dynamic_pointer_cast<AggExpr>(e)) {
                stmt->aggs.push_back(a);
                stmt->is_agg = true;
            } else {
                stmt->exprs.push_back(e);
            }
        }
        stmt->tabs = (yyvsp[-6].sv_strs);
        stmt->joins = (yyvsp[-5].sv_joins);
        // Collect join table names and aliases (alias AFTER table, like fromList)
        for (auto &j : stmt->joins) {
            stmt->tabs.push_back(j->tab_name);
            if (!j->alias.empty()) {
                stmt->table_aliases[j->alias] = j->tab_name;
                stmt->tabs.push_back(j->alias);
            }
        }
        stmt->cond = (yyvsp[-4].sv_cond);
        stmt->group_by = (yyvsp[-3].sv_groupby);
        stmt->having = (yyvsp[-2].sv_cond);
        stmt->order = (yyvsp[-1].sv_orderby);
        stmt->limit = (yyvsp[0].sv_limit);
        (yyval.sv_node) = stmt;
    }
#line 2070 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30: /* fieldList: field  */
#line 232 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2078 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31: /* fieldList: fieldList ',' field  */
#line 236 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2086 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32: /* colNameList: colName  */
#line 243 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2094 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33: /* colNameList: colNameList ',' colName  */
#line 247 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2102 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34: /* optColList: %empty  */
#line 254 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{};
    }
#line 2110 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35: /* optColList: '(' colNameList ')'  */
#line 258 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = (yyvsp[-1].sv_strs);
    }
#line 2118 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36: /* field: colName type  */
#line 265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len), false, nullptr);
    }
#line 2126 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37: /* field: colName type VALUE_NULL  */
#line 269 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
    }
#line 2134 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38: /* field: colName type NOT VALUE_NULL  */
#line 273 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
    }
#line 2142 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39: /* field: colName type DEFAULT value  */
#line 277 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), false, (yyvsp[0].sv_val));
    }
#line 2150 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40: /* field: colName type NOT VALUE_NULL DEFAULT value  */
#line 281 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-5].sv_str), (yyvsp[-4].sv_type_len), true, (yyvsp[0].sv_val));
    }
#line 2158 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41: /* field: colName type PRIMARY KEY  */
#line 285 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        (yyval.sv_field) = col;
    }
#line 2168 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42: /* field: colName type AUTO_INCREMENT  */
#line 291 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2178 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43: /* field: colName type NOT VALUE_NULL AUTO_INCREMENT  */
#line 297 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2188 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44: /* field: colName type PRIMARY KEY AUTO_INCREMENT  */
#line 303 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2199 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45: /* type: INT  */
#line 313 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2207 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46: /* type: CHAR '(' VALUE_INT ')'  */
#line 317 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Multiply by 4 for UTF-8 multi-byte character support
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int) * 4);
    }
#line 2216 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47: /* type: CHAR  */
#line 322 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // CHAR without length defaults to 4 bytes (1 char)
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, 4);
    }
#line 2225 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48: /* type: DATE  */
#line 327 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, 256);
    }
#line 2233 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49: /* type: TEXT  */
#line 331 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, 256);
    }
#line 2241 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50: /* type: FLOAT  */
#line 335 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2249 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51: /* type: FLOAT '(' VALUE_INT ',' VALUE_INT ')'  */
#line 339 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // DECIMAL(p,s) / NUMERIC(p,s): ignore precision/scale, store as FLOAT
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2258 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52: /* valueList: value  */
#line 347 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2266 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 53: /* valueList: valueList ',' value  */
#line 351 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2274 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 54: /* valueTupleList: '(' valueList ')'  */
#line 358 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list) = std::vector<std::vector<std::shared_ptr<Value>>>{(yyvsp[-1].sv_vals)};
    }
#line 2282 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55: /* valueTupleList: valueTupleList ',' '(' valueList ')'  */
#line 362 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list).push_back((yyvsp[-1].sv_vals));
    }
#line 2290 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 56: /* value: VALUE_INT  */
#line 369 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2298 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57: /* value: VALUE_FLOAT  */
#line 373 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2306 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 58: /* value: VALUE_STRING  */
#line 377 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2314 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 59: /* value: VALUE_BOOL  */
#line 381 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2322 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60: /* value: VALUE_NULL  */
#line 385 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<NullLit>();
    }
#line 2330 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 63: /* cond_or: cond_or OR cond_and  */
#line 402 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_OR,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2339 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65: /* cond_and: cond_and AND cond_not  */
#line 411 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_AND,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2348 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67: /* cond_not: NOT cond_not  */
#line 420 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_NOT,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[0].sv_cond)});
    }
#line 2357 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68: /* cond_base: expr op expr  */
#line 428 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_expr), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2365 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69: /* cond_base: col IS VALUE_NULL  */
#line 432 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-2].sv_col), SV_OP_IS_NULL);
    }
#line 2373 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70: /* cond_base: col IS NOT VALUE_NULL  */
#line 436 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-3].sv_col), SV_OP_IS_NOT_NULL);
    }
#line 2381 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71: /* cond_base: col LIKE VALUE_STRING  */
#line 440 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-2].sv_col), false, (yyvsp[0].sv_str));
    }
#line 2389 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72: /* cond_base: col NOT LIKE VALUE_STRING  */
#line 444 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-3].sv_col), true, (yyvsp[0].sv_str));
    }
#line 2397 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73: /* cond_base: col BETWEEN value AND value  */
#line 448 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-4].sv_col), false, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2405 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 74: /* cond_base: col NOT BETWEEN value AND value  */
#line 452 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-5].sv_col), true, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2413 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 75: /* cond_base: col IN '(' valueList ')'  */
#line 456 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, (yyvsp[-1].sv_vals));
    }
#line 2421 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 76: /* cond_base: col NOT IN '(' valueList ')'  */
#line 460 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, (yyvsp[-1].sv_vals));
    }
#line 2429 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 77: /* cond_base: col IN '(' dml ')'  */
#line 464 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2437 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 78: /* cond_base: col NOT IN '(' dml ')'  */
#line 468 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2445 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 79: /* cond_base: '(' condition ')'  */
#line 472 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[-1].sv_cond);
    }
#line 2453 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 80: /* optWhereClause: %empty  */
#line 479 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2461 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 81: /* optWhereClause: WHERE condition  */
#line 483 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2469 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 82: /* optHaving: %empty  */
#line 490 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2477 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 83: /* optHaving: HAVING condition  */
#line 494 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2485 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 86: /* expr_add_sub: expr_add_sub '+' expr_mul_div  */
#line 510 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_ADD, (yyvsp[0].sv_expr));
    }
#line 2493 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 87: /* expr_add_sub: expr_add_sub '-' expr_mul_div  */
#line 514 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_SUB, (yyvsp[0].sv_expr));
    }
#line 2501 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 89: /* expr_mul_div: expr_mul_div '*' expr_unary  */
#line 522 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MUL, (yyvsp[0].sv_expr));
    }
#line 2509 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 90: /* expr_mul_div: expr_mul_div '/' expr_unary  */
#line 526 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_DIV, (yyvsp[0].sv_expr));
    }
#line 2517 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 91: /* expr_mul_div: expr_mul_div '%' expr_unary  */
#line 530 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MOD, (yyvsp[0].sv_expr));
    }
#line 2525 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 93: /* expr_unary: '-' expr_unary  */
#line 538 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>(nullptr, ARITH_NEG, (yyvsp[0].sv_expr));
    }
#line 2533 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 94: /* expr_base: value  */
#line 545 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2541 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 95: /* expr_base: col  */
#line 549 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2549 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 96: /* expr_base: aggExpr  */
#line 553 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_agg));
    }
#line 2557 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 97: /* expr_base: CONCAT '(' expr_list ')'  */
#line 557 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ConcatExpr>((yyvsp[-1].sv_exprs));
    }
#line 2565 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 98: /* expr_base: '(' dml ')'  */
#line 561 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<SubqueryExpr>((yyvsp[-1].sv_node));
    }
#line 2573 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 99: /* expr_base: '(' expr ')'  */
#line 565 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = (yyvsp[-1].sv_expr);
    }
#line 2581 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 100: /* aggType: COUNT  */
#line 575 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_COUNT; }
#line 2587 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 101: /* aggType: SUM  */
#line 576 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_SUM; }
#line 2593 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 102: /* aggType: AVG  */
#line 577 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_AVG; }
#line 2599 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 103: /* aggType: MAX  */
#line 578 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MAX; }
#line 2605 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 104: /* aggType: MIN  */
#line 579 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MIN; }
#line 2611 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 105: /* aggExpr: aggType '(' col ')'  */
#line 584 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_agg) = std::make_shared<AggExpr>((yyvsp[-3].sv_agg_type), (yyvsp[-1].sv_col)->col_name);
    }
#line 2619 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 106: /* aggExpr: aggType '(' '*' ')'  */
#line 588 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        if ((yyvsp[-3].sv_agg_type) == AGG_COUNT) {
            (yyval.sv_agg) = std::make_shared<AggExpr>(AGG_COUNT, "", true);
        } else {
            yyerror(&yylloc, "Only COUNT supports * argument");
            YYERROR;
        }
    }
#line 2632 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 107: /* optDistinct: %empty  */
#line 603 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = false; }
#line 2638 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 108: /* optDistinct: DISTINCT  */
#line 604 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = true; }
#line 2644 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 109: /* selectItems: '*'  */
#line 609 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{};
    }
#line 2652 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 111: /* selectItemList: expr opt_alias  */
#line 617 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[-1].sv_expr)};
    }
#line 2660 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 112: /* selectItemList: selectItemList ',' expr opt_alias  */
#line 621 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[-1].sv_expr));
    }
#line 2668 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 113: /* opt_alias: %empty  */
#line 627 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2674 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 114: /* opt_alias: IDENTIFIER  */
#line 628 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2680 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 115: /* opt_alias: AS IDENTIFIER  */
#line 629 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2686 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 116: /* opt_alias: AS COUNT  */
#line 630 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2692 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 117: /* opt_alias: AS AVG  */
#line 631 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2698 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 118: /* opt_alias: AS SUM  */
#line 632 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2704 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 119: /* opt_alias: AS MAX  */
#line 633 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2710 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 120: /* opt_alias: AS MIN  */
#line 634 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2716 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 121: /* optAliasStr: %empty  */
#line 638 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = ""; }
#line 2722 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 122: /* optAliasStr: IDENTIFIER  */
#line 639 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2728 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 123: /* optAliasStr: AS IDENTIFIER  */
#line 640 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2734 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 124: /* optAliasStr: AS COUNT  */
#line 641 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "count"; }
#line 2740 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 125: /* optAliasStr: AS AVG  */
#line 642 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "avg"; }
#line 2746 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 126: /* optAliasStr: AS SUM  */
#line 643 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "sum"; }
#line 2752 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 127: /* optAliasStr: AS MAX  */
#line 644 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "max"; }
#line 2758 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 128: /* optAliasStr: AS MIN  */
#line 645 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "min"; }
#line 2764 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 129: /* fromList: tbName optAliasStr  */
#line 650 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[-1].sv_str)};
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2773 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 130: /* fromList: fromList ',' tbName optAliasStr  */
#line 655 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[-1].sv_str));
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2782 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 131: /* optJoinList: %empty  */
#line 663 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{};
    }
#line 2790 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 132: /* optJoinList: joinList  */
#line 667 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = (yyvsp[0].sv_joins);
    }
#line 2798 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 133: /* joinList: joinClause  */
#line 674 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join)};
    }
#line 2806 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 134: /* joinList: joinList joinClause  */
#line 678 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins).push_back((yyvsp[0].sv_join));
    }
#line 2814 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 135: /* joinType: INNER  */
#line 684 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = INNER_JOIN; }
#line 2820 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 136: /* joinType: LEFT  */
#line 685 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = LEFT_JOIN; }
#line 2826 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 137: /* joinType: RIGHT  */
#line 686 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = RIGHT_JOIN; }
#line 2832 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 138: /* joinType: FULL  */
#line 687 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = FULL_JOIN; }
#line 2838 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 139: /* joinClause: joinType JOIN tbName optAliasStr ON condition  */
#line 692 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), static_cast<JoinType>((yyvsp[-5].sv_int)), (yyvsp[-2].sv_str));
    }
#line 2846 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 140: /* joinClause: JOIN tbName optAliasStr ON condition  */
#line 696 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), INNER_JOIN, (yyvsp[-2].sv_str));
    }
#line 2854 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 141: /* joinClause: joinType JOIN tbName optAliasStr  */
#line 700 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, static_cast<JoinType>((yyvsp[-3].sv_int)), (yyvsp[0].sv_str));
    }
#line 2862 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 142: /* joinClause: JOIN tbName optAliasStr  */
#line 704 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, INNER_JOIN, (yyvsp[0].sv_str));
    }
#line 2870 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 143: /* optGroupBy: %empty  */
#line 711 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = nullptr;
    }
#line 2878 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 144: /* optGroupBy: GROUP BY colList  */
#line 715 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = std::make_shared<GroupBy>((yyvsp[0].sv_cols));
    }
#line 2886 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 145: /* optLimit: %empty  */
#line 722 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = nullptr;
    }
#line 2894 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 146: /* optLimit: LIMIT VALUE_INT  */
#line 726 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[0].sv_int));
    }
#line 2902 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 147: /* optLimit: LIMIT VALUE_INT OFFSET VALUE_INT  */
#line 730 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[-2].sv_int), (yyvsp[0].sv_int));
    }
#line 2910 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 148: /* col: tbName '.' colName  */
#line 737 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2918 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 149: /* col: colName  */
#line 741 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2926 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 150: /* colList: col  */
#line 748 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2934 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 151: /* colList: colList ',' col  */
#line 752 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2942 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 152: /* op: '='  */
#line 759 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2950 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 153: /* op: '<'  */
#line 763 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2958 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 154: /* op: '>'  */
#line 767 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2966 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 155: /* op: NEQ  */
#line 771 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2974 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 156: /* op: LEQ  */
#line 775 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2982 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 157: /* op: GEQ  */
#line 779 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2990 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 158: /* setClauses: setClause  */
#line 786 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2998 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 159: /* setClauses: setClauses ',' setClause  */
#line 790 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 3006 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 160: /* setClause: colName '=' value  */
#line 797 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 3014 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 161: /* opt_order_clause: ORDER BY order_clause  */
#line 804 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby);
    }
#line 3022 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 162: /* opt_order_clause: %empty  */
#line 807 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                    { /* ignore*/ }
#line 3028 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 163: /* order_clause: col opt_asc_desc  */
#line 812 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 3036 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 164: /* order_clause: order_clause ',' col opt_asc_desc  */
#line 816 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Multi-column ORDER BY — only first column is used
    }
#line 3044 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 165: /* opt_asc_desc: ASC  */
#line 822 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 3050 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 166: /* opt_asc_desc: DESC  */
#line 823 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DESC; }
#line 3056 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 167: /* opt_asc_desc: %empty  */
#line 824 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 3062 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 168: /* set_knob_type: ENABLE_NESTLOOP  */
#line 828 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 3068 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 169: /* set_knob_type: ENABLE_SORTMERGE  */
#line 829 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 3074 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 170: /* expr_list: expr  */
#line 834 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[0].sv_expr)};
    }
#line 3082 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 171: /* expr_list: expr_list ',' expr  */
#line 838 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[0].sv_expr));
    }
#line 3090 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 3094 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 846 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"

