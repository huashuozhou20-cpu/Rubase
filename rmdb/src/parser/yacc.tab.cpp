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
  YYSYMBOL_TXN_BEGIN = 33,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 34,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 35,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 36,              /* TXN_ROLLBACK  */
  YYSYMBOL_ENABLE_NESTLOOP = 37,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 38,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_AVG = 39,                       /* AVG  */
  YYSYMBOL_BETWEEN = 40,                   /* BETWEEN  */
  YYSYMBOL_COUNT = 41,                     /* COUNT  */
  YYSYMBOL_DISTINCT = 42,                  /* DISTINCT  */
  YYSYMBOL_FULL = 43,                      /* FULL  */
  YYSYMBOL_GROUP = 44,                     /* GROUP  */
  YYSYMBOL_HAVING = 45,                    /* HAVING  */
  YYSYMBOL_IN = 46,                        /* IN  */
  YYSYMBOL_INNER = 47,                     /* INNER  */
  YYSYMBOL_IS = 48,                        /* IS  */
  YYSYMBOL_LEFT = 49,                      /* LEFT  */
  YYSYMBOL_LIKE = 50,                      /* LIKE  */
  YYSYMBOL_LIMIT = 51,                     /* LIMIT  */
  YYSYMBOL_MAX = 52,                       /* MAX  */
  YYSYMBOL_MIN = 53,                       /* MIN  */
  YYSYMBOL_NOT = 54,                       /* NOT  */
  YYSYMBOL_OFFSET = 55,                    /* OFFSET  */
  YYSYMBOL_ON = 56,                        /* ON  */
  YYSYMBOL_OR = 57,                        /* OR  */
  YYSYMBOL_RIGHT = 58,                     /* RIGHT  */
  YYSYMBOL_SUM = 59,                       /* SUM  */
  YYSYMBOL_LEQ = 60,                       /* LEQ  */
  YYSYMBOL_NEQ = 61,                       /* NEQ  */
  YYSYMBOL_GEQ = 62,                       /* GEQ  */
  YYSYMBOL_T_EOF = 63,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 64,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 65,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 66,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 67,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 68,                /* VALUE_BOOL  */
  YYSYMBOL_VALUE_NULL = 69,                /* VALUE_NULL  */
  YYSYMBOL_70_ = 70,                       /* ';'  */
  YYSYMBOL_71_ = 71,                       /* '='  */
  YYSYMBOL_72_ = 72,                       /* '('  */
  YYSYMBOL_73_ = 73,                       /* ')'  */
  YYSYMBOL_74_ = 74,                       /* ','  */
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '-'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_79_ = 79,                       /* '%'  */
  YYSYMBOL_80_ = 80,                       /* '.'  */
  YYSYMBOL_81_ = 81,                       /* '<'  */
  YYSYMBOL_82_ = 82,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_start = 84,                     /* start  */
  YYSYMBOL_stmt = 85,                      /* stmt  */
  YYSYMBOL_txnStmt = 86,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 87,                    /* dbStmt  */
  YYSYMBOL_setStmt = 88,                   /* setStmt  */
  YYSYMBOL_ddl = 89,                       /* ddl  */
  YYSYMBOL_dml = 90,                       /* dml  */
  YYSYMBOL_fieldList = 91,                 /* fieldList  */
  YYSYMBOL_colNameList = 92,               /* colNameList  */
  YYSYMBOL_optColList = 93,                /* optColList  */
  YYSYMBOL_field = 94,                     /* field  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_valueList = 96,                 /* valueList  */
  YYSYMBOL_valueTupleList = 97,            /* valueTupleList  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_condition = 99,                 /* condition  */
  YYSYMBOL_cond_or = 100,                  /* cond_or  */
  YYSYMBOL_cond_and = 101,                 /* cond_and  */
  YYSYMBOL_cond_not = 102,                 /* cond_not  */
  YYSYMBOL_cond_base = 103,                /* cond_base  */
  YYSYMBOL_optWhereClause = 104,           /* optWhereClause  */
  YYSYMBOL_optHaving = 105,                /* optHaving  */
  YYSYMBOL_expr = 106,                     /* expr  */
  YYSYMBOL_expr_add_sub = 107,             /* expr_add_sub  */
  YYSYMBOL_expr_mul_div = 108,             /* expr_mul_div  */
  YYSYMBOL_expr_unary = 109,               /* expr_unary  */
  YYSYMBOL_expr_base = 110,                /* expr_base  */
  YYSYMBOL_aggType = 111,                  /* aggType  */
  YYSYMBOL_aggExpr = 112,                  /* aggExpr  */
  YYSYMBOL_optDistinct = 113,              /* optDistinct  */
  YYSYMBOL_selectItems = 114,              /* selectItems  */
  YYSYMBOL_selectItemList = 115,           /* selectItemList  */
  YYSYMBOL_fromList = 116,                 /* fromList  */
  YYSYMBOL_optJoinList = 117,              /* optJoinList  */
  YYSYMBOL_joinList = 118,                 /* joinList  */
  YYSYMBOL_joinType = 119,                 /* joinType  */
  YYSYMBOL_joinClause = 120,               /* joinClause  */
  YYSYMBOL_optGroupBy = 121,               /* optGroupBy  */
  YYSYMBOL_optLimit = 122,                 /* optLimit  */
  YYSYMBOL_col = 123,                      /* col  */
  YYSYMBOL_colList = 124,                  /* colList  */
  YYSYMBOL_op = 125,                       /* op  */
  YYSYMBOL_setClauses = 126,               /* setClauses  */
  YYSYMBOL_setClause = 127,                /* setClause  */
  YYSYMBOL_opt_order_clause = 128,         /* opt_order_clause  */
  YYSYMBOL_order_clause = 129,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 130,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 131,            /* set_knob_type  */
  YYSYMBOL_tbName = 132,                   /* tbName  */
  YYSYMBOL_colName = 133                   /* colName  */
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
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   254

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  259

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
       2,     2,     2,     2,     2,     2,     2,    79,     2,     2,
      72,    73,    77,    75,    74,    76,    80,    78,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    70,
      81,    71,    82,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    83,    88,    93,   101,   102,   103,   104,
     105,   109,   113,   117,   121,   128,   135,   142,   146,   150,
     154,   158,   165,   169,   173,   177,   209,   213,   220,   224,
     232,   235,   242,   246,   250,   254,   258,   264,   270,   276,
     286,   290,   294,   298,   306,   310,   317,   321,   328,   332,
     336,   340,   344,   356,   360,   361,   369,   370,   378,   379,
     387,   391,   395,   399,   403,   407,   411,   415,   419,   423,
     431,   434,   442,   445,   456,   460,   461,   465,   472,   473,
     477,   481,   488,   489,   496,   500,   504,   508,   519,   520,
     521,   522,   523,   527,   531,   547,   548,   552,   556,   560,
     564,   571,   575,   583,   586,   593,   597,   604,   605,   606,
     607,   611,   615,   619,   623,   631,   634,   642,   645,   649,
     656,   660,   667,   671,   678,   682,   686,   690,   694,   698,
     705,   709,   716,   723,   727,   731,   738,   739,   740,   744,
     745,   748,   750
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
  "PRIMARY", "KEY", "AUTO_INCREMENT", "TXN_BEGIN", "TXN_COMMIT",
  "TXN_ABORT", "TXN_ROLLBACK", "ENABLE_NESTLOOP", "ENABLE_SORTMERGE",
  "AVG", "BETWEEN", "COUNT", "DISTINCT", "FULL", "GROUP", "HAVING", "IN",
  "INNER", "IS", "LEFT", "LIKE", "LIMIT", "MAX", "MIN", "NOT", "OFFSET",
  "ON", "OR", "RIGHT", "SUM", "LEQ", "NEQ", "GEQ", "T_EOF", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "VALUE_NULL",
  "';'", "'='", "'('", "')'", "','", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'.'", "'<'", "'>'", "$accept", "start", "stmt", "txnStmt", "dbStmt",
  "setStmt", "ddl", "dml", "fieldList", "colNameList", "optColList",
  "field", "type", "valueList", "valueTupleList", "value", "condition",
  "cond_or", "cond_and", "cond_not", "cond_base", "optWhereClause",
  "optHaving", "expr", "expr_add_sub", "expr_mul_div", "expr_unary",
  "expr_base", "aggType", "aggExpr", "optDistinct", "selectItems",
  "selectItemList", "fromList", "optJoinList", "joinList", "joinType",
  "joinClause", "optGroupBy", "optLimit", "col", "colList", "op",
  "setClauses", "setClause", "opt_order_clause", "order_clause",
  "opt_asc_desc", "set_knob_type", "tbName", "colName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-171)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-142)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      51,    45,     1,    49,    10,    43,    64,    10,   -25,    41,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,   108,    24,  -171,
    -171,  -171,  -171,  -171,  -171,    10,    10,    10,    10,  -171,
    -171,    10,    10,    81,  -171,  -171,    35,  -171,   125,  -171,
    -171,    66,    83,  -171,    85,    87,    96,    57,    55,  -171,
    -171,  -171,  -171,  -171,    37,  -171,  -171,  -171,  -171,  -171,
     146,   146,  -171,  -171,  -171,   -35,    53,  -171,  -171,    90,
    -171,   115,   109,  -171,   116,  -171,    57,    57,    57,    57,
     154,   -38,  -171,  -171,    -8,  -171,   117,  -171,   113,  -171,
     146,   146,   146,   146,   146,   -44,    10,   146,    57,   -12,
    -171,   126,    29,  -171,    78,    94,   128,   -38,   -38,  -171,
     147,   178,  -171,  -171,    79,    57,  -171,    77,  -171,    53,
      53,  -171,  -171,  -171,   133,   134,    62,  -171,  -171,  -171,
    -171,    57,  -171,   136,   137,    61,  -171,    57,  -171,  -171,
      77,   142,  -171,   144,   -38,   -38,    77,   148,     3,   156,
      72,  -171,  -171,  -171,  -171,  -171,  -171,   146,  -171,  -171,
    -171,  -171,    10,  -171,  -171,  -171,  -171,    10,    96,   -11,
     193,  -171,  -171,   157,   158,    77,   194,  -171,   159,  -171,
      98,  -171,   155,  -171,   178,  -171,   201,    77,   160,  -171,
    -171,    77,   161,   165,  -171,   175,  -171,   188,  -171,    10,
     162,   163,  -171,   202,   -21,  -171,    77,    77,    77,   100,
    -171,   211,    77,  -171,   -38,   222,   195,   183,  -171,   176,
    -171,    77,  -171,  -171,   102,  -171,  -171,    77,   106,  -171,
     177,   -38,   228,   -38,   171,  -171,  -171,  -171,  -171,  -171,
     172,  -171,   229,   196,  -171,  -171,   177,   177,   182,  -171,
    -171,    67,  -171,   197,  -171,  -171,  -171,   184,  -171
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       4,     3,    11,    12,    13,    14,     5,     0,     0,     9,
       6,    10,     7,     8,    15,     0,     0,     0,     0,   141,
      19,     0,     0,     0,   139,   140,     0,    96,     0,     1,
       2,     0,     0,    18,     0,    30,    70,     0,     0,    90,
      88,    91,    92,    89,   142,    50,    48,    49,    51,    52,
       0,     0,    97,    84,    99,    74,    75,    78,    82,     0,
      86,     0,    98,    85,     0,   121,     0,     0,     0,     0,
       0,     0,    23,   142,    70,   130,     0,    16,     0,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,    28,     0,     0,     0,     0,     0,    71,
      53,    54,    56,    58,     0,     0,    24,     0,    87,    76,
      77,    79,    80,    81,     0,     0,   103,   101,   100,   120,
      17,     0,    40,     0,    42,    32,    20,     0,    21,    31,
       0,    22,    59,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   127,   129,   124,   125,   126,     0,   131,   132,
      94,    93,     0,   110,   107,   108,   109,     0,    70,   104,
       0,   105,    27,     0,     0,     0,     0,    37,     0,    29,
       0,    44,     0,    69,    55,    57,     0,     0,     0,    61,
      63,     0,     0,     0,    60,   114,   102,   115,   106,     0,
       0,     0,    34,    36,    33,    46,     0,     0,     0,     0,
      62,     0,     0,    64,     0,     0,    72,   113,    41,     0,
      39,     0,    38,    45,     0,    65,    67,     0,     0,   112,
       0,     0,   134,     0,     0,    35,    47,    66,    68,   122,
     116,    73,     0,   117,   111,    43,     0,     0,     0,    25,
     123,   138,   133,   118,   137,   136,   135,     0,   119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,    56,
    -171,   118,  -171,  -170,  -171,  -111,  -107,  -171,   107,   -97,
    -171,   -79,  -171,   -58,  -171,    91,   -42,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,    84,  -171,  -171,
     -77,  -171,  -171,  -171,   139,  -171,  -171,  -171,  -171,    -4,
     -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    17,    18,    19,    20,    21,    22,    23,    99,   102,
      80,   100,   135,   180,   141,    63,   109,   110,   111,   112,
     113,    82,   232,    64,    65,    66,    67,    68,    69,    70,
      38,    71,    72,   126,   168,   169,   170,   171,   216,   249,
      73,   240,   157,    84,    85,   243,   252,   256,    36,    74,
      75
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,   143,    88,    33,   114,   116,   159,    25,   221,    81,
     142,   222,    34,    35,    86,   162,   107,   209,   125,    89,
      54,    41,    42,    43,    44,    26,    54,    45,    46,   181,
     114,   114,   163,   124,   108,   186,   164,   224,   165,   128,
      90,    91,   228,   101,   103,   103,   103,   166,   185,    24,
     121,   122,   123,    31,     1,    27,     2,   188,     3,     4,
       5,   130,   131,     6,   202,   129,   115,   114,   114,     7,
       8,     9,   189,    28,    29,   254,   181,    32,    10,    11,
     211,   255,    86,    37,    12,    13,    14,    15,   162,   197,
     175,   176,   127,   177,    40,   223,   181,   225,   101,   194,
      47,   181,   136,   137,   179,   163,    48,   229,    39,   164,
     235,   165,   191,    81,    16,   178,   237,  -141,   192,   146,
     166,    83,   193,    87,   241,   147,   244,   148,    96,   149,
      92,    93,    94,   150,   104,   105,   167,   114,    76,   151,
     152,   153,    55,    56,    57,    58,    59,   132,   133,   134,
     154,   138,   137,   239,   114,    77,   114,    78,   195,    79,
     155,   156,    95,   196,    49,   106,    50,   139,   137,   250,
     251,   205,   206,   226,   206,   236,   206,    51,    52,   238,
     206,   119,   120,    97,    53,    49,   118,    50,   117,    54,
      55,    56,    57,    58,    59,   217,    98,    60,    51,    52,
     140,    61,    62,   145,   144,    53,   160,   161,   173,   174,
      54,    55,    56,    57,    58,    59,   182,   183,    60,   199,
     187,   190,    61,   200,   201,   203,   208,   207,   204,   210,
     213,   214,   215,   212,   220,   218,   227,   219,   230,   233,
     231,    54,   234,   242,   245,   247,   246,   248,   253,   172,
     258,   184,   257,   198,   158
};

static const yytype_uint8 yycheck[] =
{
       4,   108,    60,     7,    81,    84,   117,     6,    29,    17,
     107,    32,    37,    38,    47,    26,    54,   187,    95,    61,
      64,    25,    26,    27,    28,    24,    64,    31,    32,   140,
     107,   108,    43,    77,    72,   146,    47,   207,    49,    97,
      75,    76,   212,    76,    77,    78,    79,    58,   145,     4,
      92,    93,    94,    10,     3,     6,     5,    54,     7,     8,
       9,    73,    74,    12,   175,    98,    74,   144,   145,    18,
      19,    20,    69,    24,    64,     8,   187,    13,    27,    28,
     191,    14,   115,    42,    33,    34,    35,    36,    26,   168,
      29,    30,    96,    32,    70,   206,   207,   208,   131,   157,
      19,   212,    73,    74,   137,    43,    71,   214,     0,    47,
     221,    49,    40,    17,    63,    54,   227,    80,    46,    40,
      58,    64,    50,    68,   231,    46,   233,    48,    13,    50,
      77,    78,    79,    54,    78,    79,    74,   214,    72,    60,
      61,    62,    65,    66,    67,    68,    69,    21,    22,    23,
      71,    73,    74,   230,   231,    72,   233,    72,   162,    72,
      81,    82,    72,   167,    39,    11,    41,    73,    74,   246,
     247,    73,    74,    73,    74,    73,    74,    52,    53,    73,
      74,    90,    91,    74,    59,    39,    73,    41,    71,    64,
      65,    66,    67,    68,    69,   199,    80,    72,    52,    53,
      72,    76,    77,    25,    57,    59,    73,    73,    72,    72,
      64,    65,    66,    67,    68,    69,    74,    73,    72,    26,
      72,    65,    76,    66,    66,    31,    25,    72,    69,    69,
      65,    56,    44,    72,    32,    73,    25,    74,    16,    56,
      45,    64,    66,    15,    73,    16,    74,    51,    66,   131,
      66,   144,    55,   169,   115
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    33,    34,    35,    36,    63,    84,    85,    86,
      87,    88,    89,    90,     4,     6,    24,     6,    24,    64,
     132,    10,    13,   132,    37,    38,   131,    42,   113,     0,
      70,   132,   132,   132,   132,   132,   132,    19,    71,    39,
      41,    52,    53,    59,    64,    65,    66,    67,    68,    69,
      72,    76,    77,    98,   106,   107,   108,   109,   110,   111,
     112,   114,   115,   123,   132,   133,    72,    72,    72,    72,
      93,    17,   104,    64,   126,   127,   133,    68,   106,   109,
      75,    76,    77,    78,    79,    72,    13,    74,    80,    91,
      94,   133,    92,   133,    92,    92,    11,    54,    72,    99,
     100,   101,   102,   103,   123,    74,   104,    71,    73,   108,
     108,   109,   109,   109,    77,   123,   116,   132,   106,   133,
      73,    74,    21,    22,    23,    95,    73,    74,    73,    73,
      72,    97,   102,    99,    57,    25,    40,    46,    48,    50,
      54,    60,    61,    62,    71,    81,    82,   125,   127,    98,
      73,    73,    26,    43,    47,    49,    58,    74,   117,   118,
     119,   120,    94,    72,    72,    29,    30,    32,    54,   133,
      96,    98,    74,    73,   101,   102,    98,    72,    54,    69,
      65,    40,    46,    50,   106,   132,   132,   104,   120,    26,
      66,    66,    98,    31,    69,    73,    74,    72,    25,    96,
      69,    98,    72,    65,    56,    44,   121,   132,    73,    74,
      32,    29,    32,    98,    96,    98,    73,    25,    96,    99,
      16,    45,   105,    56,    66,    98,    73,    98,    73,   123,
     124,    99,    15,   128,    99,    73,    74,    16,    51,   122,
     123,   123,   129,    66,     8,    14,   130,    55,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    84,    84,    84,    85,    85,    85,    85,
      85,    86,    86,    86,    86,    87,    88,    89,    89,    89,
      89,    89,    90,    90,    90,    90,    91,    91,    92,    92,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   107,   107,   107,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   110,   111,   111,
     111,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     123,   123,   124,   124,   125,   125,   125,   125,   125,   125,
     126,   126,   127,   128,   128,   129,   130,   130,   130,   131,
     131,   132,   133
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     6,     3,     2,
       6,     6,     6,     4,     5,    11,     1,     3,     1,     3,
       0,     3,     2,     4,     4,     6,     4,     3,     5,     5,
       1,     4,     1,     6,     1,     3,     3,     5,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     2,
       3,     3,     4,     3,     4,     5,     6,     5,     6,     3,
       0,     2,     0,     2,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     4,     4,     0,     1,     1,     1,     1,
       3,     1,     3,     0,     1,     1,     2,     1,     1,     1,
       1,     5,     4,     3,     2,     0,     3,     0,     2,     4,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     2,     1,     1,     0,     1,
       1,     1,     1
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
#line 79 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1793 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 84 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1802 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 89 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1811 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 94 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1820 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 110 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1828 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 114 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1836 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 118 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1844 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 122 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1852 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 129 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1860 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 136 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1868 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 143 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1876 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18: /* ddl: DROP TABLE tbName  */
#line 147 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1884 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19: /* ddl: DESC tbName  */
#line 151 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1892 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 155 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1900 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 159 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1908 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22: /* dml: INSERT INTO tbName optColList VALUES valueTupleList  */
#line 166 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-3].sv_str), (yyvsp[-2].sv_strs), (yyvsp[0].sv_vals_list));
    }
#line 1916 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23: /* dml: DELETE FROM tbName optWhereClause  */
#line 170 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_cond));
    }
#line 1924 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 174 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_cond));
    }
#line 1932 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25: /* dml: SELECT optDistinct selectItems FROM fromList optJoinList optWhereClause optGroupBy optHaving opt_order_clause optLimit  */
#line 179 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
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
        // also add join table names to tabs for backward compatibility
        for (auto &j : stmt->joins) {
            stmt->tabs.push_back(j->tab_name);
        }
        stmt->cond = (yyvsp[-4].sv_cond);
        stmt->group_by = (yyvsp[-3].sv_groupby);
        stmt->having = (yyvsp[-2].sv_cond);
        stmt->order = (yyvsp[-1].sv_orderby);
        stmt->limit = (yyvsp[0].sv_limit);
        (yyval.sv_node) = stmt;
    }
#line 1964 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26: /* fieldList: field  */
#line 210 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1972 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27: /* fieldList: fieldList ',' field  */
#line 214 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1980 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28: /* colNameList: colName  */
#line 221 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1988 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29: /* colNameList: colNameList ',' colName  */
#line 225 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1996 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30: /* optColList: %empty  */
#line 232 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{};
    }
#line 2004 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31: /* optColList: '(' colNameList ')'  */
#line 236 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = (yyvsp[-1].sv_strs);
    }
#line 2012 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32: /* field: colName type  */
#line 243 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len), false, nullptr);
    }
#line 2020 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33: /* field: colName type NOT VALUE_NULL  */
#line 247 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
    }
#line 2028 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34: /* field: colName type DEFAULT value  */
#line 251 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), false, (yyvsp[0].sv_val));
    }
#line 2036 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35: /* field: colName type NOT VALUE_NULL DEFAULT value  */
#line 255 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-5].sv_str), (yyvsp[-4].sv_type_len), true, (yyvsp[0].sv_val));
    }
#line 2044 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36: /* field: colName type PRIMARY KEY  */
#line 259 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        (yyval.sv_field) = col;
    }
#line 2054 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37: /* field: colName type AUTO_INCREMENT  */
#line 265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2064 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38: /* field: colName type NOT VALUE_NULL AUTO_INCREMENT  */
#line 271 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2074 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39: /* field: colName type PRIMARY KEY AUTO_INCREMENT  */
#line 277 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2085 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40: /* type: INT  */
#line 287 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2093 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41: /* type: CHAR '(' VALUE_INT ')'  */
#line 291 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 2101 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42: /* type: FLOAT  */
#line 295 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2109 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43: /* type: FLOAT '(' VALUE_INT ',' VALUE_INT ')'  */
#line 299 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // DECIMAL(p,s) / NUMERIC(p,s): ignore precision/scale, store as FLOAT
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2118 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44: /* valueList: value  */
#line 307 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2126 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45: /* valueList: valueList ',' value  */
#line 311 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2134 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46: /* valueTupleList: '(' valueList ')'  */
#line 318 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list) = std::vector<std::vector<std::shared_ptr<Value>>>{(yyvsp[-1].sv_vals)};
    }
#line 2142 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47: /* valueTupleList: valueTupleList ',' '(' valueList ')'  */
#line 322 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list).push_back((yyvsp[-1].sv_vals));
    }
#line 2150 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48: /* value: VALUE_INT  */
#line 329 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2158 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49: /* value: VALUE_FLOAT  */
#line 333 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2166 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_STRING  */
#line 337 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2174 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51: /* value: VALUE_BOOL  */
#line 341 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2182 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_NULL  */
#line 345 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<NullLit>();
    }
#line 2190 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55: /* cond_or: cond_or OR cond_and  */
#line 362 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_OR,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2199 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57: /* cond_and: cond_and AND cond_not  */
#line 371 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_AND,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2208 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 59: /* cond_not: NOT cond_not  */
#line 380 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_NOT,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[0].sv_cond)});
    }
#line 2217 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60: /* cond_base: col op expr  */
#line 388 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2225 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 61: /* cond_base: col IS VALUE_NULL  */
#line 392 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-2].sv_col), SV_OP_IS_NULL);
    }
#line 2233 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 62: /* cond_base: col IS NOT VALUE_NULL  */
#line 396 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-3].sv_col), SV_OP_IS_NOT_NULL);
    }
#line 2241 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 63: /* cond_base: col LIKE VALUE_STRING  */
#line 400 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-2].sv_col), false, (yyvsp[0].sv_str));
    }
#line 2249 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 64: /* cond_base: col NOT LIKE VALUE_STRING  */
#line 404 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-3].sv_col), true, (yyvsp[0].sv_str));
    }
#line 2257 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65: /* cond_base: col BETWEEN value AND value  */
#line 408 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-4].sv_col), false, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 66: /* cond_base: col NOT BETWEEN value AND value  */
#line 412 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-5].sv_col), true, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2273 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67: /* cond_base: col IN '(' valueList ')'  */
#line 416 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, (yyvsp[-1].sv_vals));
    }
#line 2281 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68: /* cond_base: col NOT IN '(' valueList ')'  */
#line 420 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, (yyvsp[-1].sv_vals));
    }
#line 2289 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69: /* cond_base: '(' condition ')'  */
#line 424 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[-1].sv_cond);
    }
#line 2297 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70: /* optWhereClause: %empty  */
#line 431 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2305 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71: /* optWhereClause: WHERE condition  */
#line 435 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2313 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72: /* optHaving: %empty  */
#line 442 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2321 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73: /* optHaving: HAVING condition  */
#line 446 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2329 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 76: /* expr_add_sub: expr_add_sub '+' expr_mul_div  */
#line 462 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_ADD, (yyvsp[0].sv_expr));
    }
#line 2337 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 77: /* expr_add_sub: expr_add_sub '-' expr_mul_div  */
#line 466 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_SUB, (yyvsp[0].sv_expr));
    }
#line 2345 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 79: /* expr_mul_div: expr_mul_div '*' expr_unary  */
#line 474 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MUL, (yyvsp[0].sv_expr));
    }
#line 2353 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 80: /* expr_mul_div: expr_mul_div '/' expr_unary  */
#line 478 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_DIV, (yyvsp[0].sv_expr));
    }
#line 2361 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 81: /* expr_mul_div: expr_mul_div '%' expr_unary  */
#line 482 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MOD, (yyvsp[0].sv_expr));
    }
#line 2369 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 83: /* expr_unary: '-' expr_unary  */
#line 490 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>(nullptr, ARITH_NEG, (yyvsp[0].sv_expr));
    }
#line 2377 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 84: /* expr_base: value  */
#line 497 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2385 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 85: /* expr_base: col  */
#line 501 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2393 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 86: /* expr_base: aggExpr  */
#line 505 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_agg));
    }
#line 2401 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 87: /* expr_base: '(' expr ')'  */
#line 509 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = (yyvsp[-1].sv_expr);
    }
#line 2409 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 88: /* aggType: COUNT  */
#line 519 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_COUNT; }
#line 2415 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 89: /* aggType: SUM  */
#line 520 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_SUM; }
#line 2421 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 90: /* aggType: AVG  */
#line 521 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_AVG; }
#line 2427 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 91: /* aggType: MAX  */
#line 522 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MAX; }
#line 2433 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 92: /* aggType: MIN  */
#line 523 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MIN; }
#line 2439 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 93: /* aggExpr: aggType '(' col ')'  */
#line 528 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_agg) = std::make_shared<AggExpr>((yyvsp[-3].sv_agg_type), (yyvsp[-1].sv_col)->col_name);
    }
#line 2447 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 94: /* aggExpr: aggType '(' '*' ')'  */
#line 532 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        if ((yyvsp[-3].sv_agg_type) == AGG_COUNT) {
            (yyval.sv_agg) = std::make_shared<AggExpr>(AGG_COUNT, "", true);
        } else {
            yyerror(&yylloc, "Only COUNT supports * argument");
            YYERROR;
        }
    }
#line 2460 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 95: /* optDistinct: %empty  */
#line 547 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = false; }
#line 2466 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 96: /* optDistinct: DISTINCT  */
#line 548 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = true; }
#line 2472 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 97: /* selectItems: '*'  */
#line 553 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{};
    }
#line 2480 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 99: /* selectItemList: expr  */
#line 561 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[0].sv_expr)};
    }
#line 2488 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 100: /* selectItemList: selectItemList ',' expr  */
#line 565 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[0].sv_expr));
    }
#line 2496 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 101: /* fromList: tbName  */
#line 572 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2504 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 102: /* fromList: fromList ',' tbName  */
#line 576 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2512 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 103: /* optJoinList: %empty  */
#line 583 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{};
    }
#line 2520 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 104: /* optJoinList: joinList  */
#line 587 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = (yyvsp[0].sv_joins);
    }
#line 2528 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 105: /* joinList: joinClause  */
#line 594 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join)};
    }
#line 2536 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 106: /* joinList: joinList joinClause  */
#line 598 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins).push_back((yyvsp[0].sv_join));
    }
#line 2544 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 107: /* joinType: INNER  */
#line 604 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = INNER_JOIN; }
#line 2550 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 108: /* joinType: LEFT  */
#line 605 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = LEFT_JOIN; }
#line 2556 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 109: /* joinType: RIGHT  */
#line 606 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = RIGHT_JOIN; }
#line 2562 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 110: /* joinType: FULL  */
#line 607 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = FULL_JOIN; }
#line 2568 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 111: /* joinClause: joinType JOIN tbName ON condition  */
#line 612 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-2].sv_str), (yyvsp[0].sv_cond), static_cast<JoinType>((yyvsp[-4].sv_int)));
    }
#line 2576 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 112: /* joinClause: JOIN tbName ON condition  */
#line 616 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-2].sv_str), (yyvsp[0].sv_cond), INNER_JOIN);
    }
#line 2584 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 113: /* joinClause: joinType JOIN tbName  */
#line 620 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[0].sv_str), nullptr, static_cast<JoinType>((yyvsp[-2].sv_int)));
    }
#line 2592 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 114: /* joinClause: JOIN tbName  */
#line 624 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[0].sv_str), nullptr, INNER_JOIN);
    }
#line 2600 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 115: /* optGroupBy: %empty  */
#line 631 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = nullptr;
    }
#line 2608 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 116: /* optGroupBy: GROUP BY colList  */
#line 635 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = std::make_shared<GroupBy>((yyvsp[0].sv_cols));
    }
#line 2616 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 117: /* optLimit: %empty  */
#line 642 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = nullptr;
    }
#line 2624 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 118: /* optLimit: LIMIT VALUE_INT  */
#line 646 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[0].sv_int));
    }
#line 2632 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 119: /* optLimit: LIMIT VALUE_INT OFFSET VALUE_INT  */
#line 650 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[-2].sv_int), (yyvsp[0].sv_int));
    }
#line 2640 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 120: /* col: tbName '.' colName  */
#line 657 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2648 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 121: /* col: colName  */
#line 661 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2656 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 122: /* colList: col  */
#line 668 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2664 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 123: /* colList: colList ',' col  */
#line 672 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2672 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 124: /* op: '='  */
#line 679 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2680 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 125: /* op: '<'  */
#line 683 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2688 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 126: /* op: '>'  */
#line 687 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2696 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 127: /* op: NEQ  */
#line 691 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2704 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 128: /* op: LEQ  */
#line 695 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2712 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 129: /* op: GEQ  */
#line 699 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2720 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 130: /* setClauses: setClause  */
#line 706 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2728 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 131: /* setClauses: setClauses ',' setClause  */
#line 710 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2736 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 132: /* setClause: colName '=' value  */
#line 717 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2744 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 133: /* opt_order_clause: ORDER BY order_clause  */
#line 724 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby);
    }
#line 2752 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 134: /* opt_order_clause: %empty  */
#line 727 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                    { /* ignore*/ }
#line 2758 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 135: /* order_clause: col opt_asc_desc  */
#line 732 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2766 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 136: /* opt_asc_desc: ASC  */
#line 738 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2772 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 137: /* opt_asc_desc: DESC  */
#line 739 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DESC; }
#line 2778 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 138: /* opt_asc_desc: %empty  */
#line 740 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 2784 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 139: /* set_knob_type: ENABLE_NESTLOOP  */
#line 744 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2790 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 140: /* set_knob_type: ENABLE_SORTMERGE  */
#line 745 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2796 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 2800 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"

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

#line 751 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"

