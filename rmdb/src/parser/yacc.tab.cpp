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
  YYSYMBOL_TXN_BEGIN = 36,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 37,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 38,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 39,              /* TXN_ROLLBACK  */
  YYSYMBOL_ENABLE_NESTLOOP = 40,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 41,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_AVG = 42,                       /* AVG  */
  YYSYMBOL_BETWEEN = 43,                   /* BETWEEN  */
  YYSYMBOL_COUNT = 44,                     /* COUNT  */
  YYSYMBOL_DISTINCT = 45,                  /* DISTINCT  */
  YYSYMBOL_FULL = 46,                      /* FULL  */
  YYSYMBOL_GROUP = 47,                     /* GROUP  */
  YYSYMBOL_HAVING = 48,                    /* HAVING  */
  YYSYMBOL_IN = 49,                        /* IN  */
  YYSYMBOL_INNER = 50,                     /* INNER  */
  YYSYMBOL_IS = 51,                        /* IS  */
  YYSYMBOL_LEFT = 52,                      /* LEFT  */
  YYSYMBOL_LIKE = 53,                      /* LIKE  */
  YYSYMBOL_LIMIT = 54,                     /* LIMIT  */
  YYSYMBOL_MAX = 55,                       /* MAX  */
  YYSYMBOL_MIN = 56,                       /* MIN  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_OFFSET = 58,                    /* OFFSET  */
  YYSYMBOL_ON = 59,                        /* ON  */
  YYSYMBOL_OR = 60,                        /* OR  */
  YYSYMBOL_RIGHT = 61,                     /* RIGHT  */
  YYSYMBOL_SUM = 62,                       /* SUM  */
  YYSYMBOL_LEQ = 63,                       /* LEQ  */
  YYSYMBOL_NEQ = 64,                       /* NEQ  */
  YYSYMBOL_GEQ = 65,                       /* GEQ  */
  YYSYMBOL_T_EOF = 66,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 67,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 68,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 69,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 70,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 71,                /* VALUE_BOOL  */
  YYSYMBOL_VALUE_NULL = 72,                /* VALUE_NULL  */
  YYSYMBOL_73_ = 73,                       /* ';'  */
  YYSYMBOL_74_ = 74,                       /* '='  */
  YYSYMBOL_75_ = 75,                       /* '('  */
  YYSYMBOL_76_ = 76,                       /* ')'  */
  YYSYMBOL_77_ = 77,                       /* ','  */
  YYSYMBOL_78_ = 78,                       /* '+'  */
  YYSYMBOL_79_ = 79,                       /* '-'  */
  YYSYMBOL_80_ = 80,                       /* '*'  */
  YYSYMBOL_81_ = 81,                       /* '/'  */
  YYSYMBOL_82_ = 82,                       /* '%'  */
  YYSYMBOL_83_ = 83,                       /* '.'  */
  YYSYMBOL_84_ = 84,                       /* '<'  */
  YYSYMBOL_85_ = 85,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_start = 87,                     /* start  */
  YYSYMBOL_stmt = 88,                      /* stmt  */
  YYSYMBOL_txnStmt = 89,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 90,                    /* dbStmt  */
  YYSYMBOL_setStmt = 91,                   /* setStmt  */
  YYSYMBOL_ddl = 92,                       /* ddl  */
  YYSYMBOL_dml = 93,                       /* dml  */
  YYSYMBOL_fieldList = 94,                 /* fieldList  */
  YYSYMBOL_colNameList = 95,               /* colNameList  */
  YYSYMBOL_optColList = 96,                /* optColList  */
  YYSYMBOL_field = 97,                     /* field  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_valueList = 99,                 /* valueList  */
  YYSYMBOL_valueTupleList = 100,           /* valueTupleList  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_condition = 102,                /* condition  */
  YYSYMBOL_cond_or = 103,                  /* cond_or  */
  YYSYMBOL_cond_and = 104,                 /* cond_and  */
  YYSYMBOL_cond_not = 105,                 /* cond_not  */
  YYSYMBOL_cond_base = 106,                /* cond_base  */
  YYSYMBOL_optWhereClause = 107,           /* optWhereClause  */
  YYSYMBOL_optHaving = 108,                /* optHaving  */
  YYSYMBOL_expr = 109,                     /* expr  */
  YYSYMBOL_expr_add_sub = 110,             /* expr_add_sub  */
  YYSYMBOL_expr_mul_div = 111,             /* expr_mul_div  */
  YYSYMBOL_expr_unary = 112,               /* expr_unary  */
  YYSYMBOL_expr_base = 113,                /* expr_base  */
  YYSYMBOL_aggType = 114,                  /* aggType  */
  YYSYMBOL_aggExpr = 115,                  /* aggExpr  */
  YYSYMBOL_optDistinct = 116,              /* optDistinct  */
  YYSYMBOL_selectItems = 117,              /* selectItems  */
  YYSYMBOL_selectItemList = 118,           /* selectItemList  */
  YYSYMBOL_opt_alias = 119,                /* opt_alias  */
  YYSYMBOL_optAliasStr = 120,              /* optAliasStr  */
  YYSYMBOL_fromList = 121,                 /* fromList  */
  YYSYMBOL_optJoinList = 122,              /* optJoinList  */
  YYSYMBOL_joinList = 123,                 /* joinList  */
  YYSYMBOL_joinType = 124,                 /* joinType  */
  YYSYMBOL_joinClause = 125,               /* joinClause  */
  YYSYMBOL_optGroupBy = 126,               /* optGroupBy  */
  YYSYMBOL_optLimit = 127,                 /* optLimit  */
  YYSYMBOL_col = 128,                      /* col  */
  YYSYMBOL_colList = 129,                  /* colList  */
  YYSYMBOL_op = 130,                       /* op  */
  YYSYMBOL_setClauses = 131,               /* setClauses  */
  YYSYMBOL_setClause = 132,                /* setClause  */
  YYSYMBOL_opt_order_clause = 133,         /* opt_order_clause  */
  YYSYMBOL_order_clause = 134,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 135,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 136,            /* set_knob_type  */
  YYSYMBOL_expr_list = 137,                /* expr_list  */
  YYSYMBOL_tbName = 138,                   /* tbName  */
  YYSYMBOL_colName = 139                   /* colName  */
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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
       2,     2,     2,     2,     2,     2,     2,    82,     2,     2,
      75,    76,    80,    78,    77,    79,    83,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    73,
      84,    74,    85,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    84,    89,    94,   102,   103,   104,   105,
     106,   110,   114,   118,   122,   129,   136,   143,   147,   151,
     155,   159,   164,   168,   172,   179,   183,   187,   191,   227,
     231,   238,   242,   250,   253,   260,   264,   268,   272,   276,
     280,   286,   292,   298,   308,   312,   317,   322,   326,   334,
     338,   345,   349,   356,   360,   364,   368,   372,   384,   388,
     389,   397,   398,   406,   407,   415,   419,   423,   427,   431,
     435,   439,   443,   447,   451,   455,   459,   467,   470,   478,
     481,   492,   496,   497,   501,   508,   509,   513,   517,   524,
     525,   532,   536,   540,   544,   548,   552,   563,   564,   565,
     566,   567,   571,   575,   591,   592,   596,   600,   604,   608,
     615,   616,   617,   618,   619,   620,   621,   622,   626,   627,
     628,   629,   630,   631,   632,   633,   637,   642,   651,   654,
     661,   665,   672,   673,   674,   675,   679,   683,   687,   691,
     699,   702,   710,   713,   717,   724,   728,   735,   739,   746,
     750,   754,   758,   762,   766,   773,   777,   784,   791,   795,
     799,   806,   807,   808,   812,   813,   817,   821,   827,   829
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
  "PRIMARY", "KEY", "AUTO_INCREMENT", "AS", "CONCAT", "VIEW", "TXN_BEGIN",
  "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK", "ENABLE_NESTLOOP",
  "ENABLE_SORTMERGE", "AVG", "BETWEEN", "COUNT", "DISTINCT", "FULL",
  "GROUP", "HAVING", "IN", "INNER", "IS", "LEFT", "LIKE", "LIMIT", "MAX",
  "MIN", "NOT", "OFFSET", "ON", "OR", "RIGHT", "SUM", "LEQ", "NEQ", "GEQ",
  "T_EOF", "IDENTIFIER", "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT",
  "VALUE_BOOL", "VALUE_NULL", "';'", "'='", "'('", "')'", "','", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'.'", "'<'", "'>'", "$accept", "start",
  "stmt", "txnStmt", "dbStmt", "setStmt", "ddl", "dml", "fieldList",
  "colNameList", "optColList", "field", "type", "valueList",
  "valueTupleList", "value", "condition", "cond_or", "cond_and",
  "cond_not", "cond_base", "optWhereClause", "optHaving", "expr",
  "expr_add_sub", "expr_mul_div", "expr_unary", "expr_base", "aggType",
  "aggExpr", "optDistinct", "selectItems", "selectItemList", "opt_alias",
  "optAliasStr", "fromList", "optJoinList", "joinList", "joinType",
  "joinClause", "optGroupBy", "optLimit", "col", "colList", "op",
  "setClauses", "setClause", "opt_order_clause", "order_clause",
  "opt_asc_desc", "set_knob_type", "expr_list", "tbName", "colName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-209)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-169)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     281,    12,    53,    88,   -29,    42,    60,   -29,    97,    37,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,    90,    13,  -209,
    -209,  -209,  -209,  -209,  -209,   -29,   -29,   -29,   -29,   -29,
     -29,  -209,  -209,   -29,   -29,    77,  -209,  -209,    34,  -209,
     260,  -209,  -209,    36,   -40,    89,  -209,    49,  -209,    56,
     111,    72,    71,    78,  -209,  -209,  -209,  -209,  -209,    61,
    -209,  -209,  -209,  -209,  -209,   208,   331,  -209,  -209,   -21,
     103,    69,  -209,  -209,    81,  -209,   145,    84,  -209,    82,
    -209,    72,   -29,    72,    86,    72,    72,   163,   299,  -209,
    -209,   -11,  -209,    93,  -209,   331,   100,   102,  -209,    85,
    -209,  -209,   331,   331,   331,   331,   331,    -6,   -29,   331,
      72,   124,  -209,   112,   119,   132,  -209,  -209,   156,   169,
     136,   299,   168,  -209,   154,   196,  -209,  -209,   105,   142,
      72,  -209,   135,  -209,   172,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,    69,    69,  -209,  -209,  -209,   151,   153,
     -13,   -18,   -21,  -209,  -209,    72,  -209,   159,   166,   -12,
      72,  -209,    72,  -209,  -209,   135,   167,  -209,   175,    99,
     299,   299,  -209,  -209,  -209,  -209,  -209,  -209,   331,   135,
     187,    15,   199,    -9,  -209,  -209,  -209,   331,  -209,  -209,
     -29,  -209,  -209,  -209,  -209,   -29,   111,    57,   242,  -209,
     104,  -209,  -209,  -209,  -209,   200,   202,   135,   241,  -209,
     201,  -209,   177,  -209,   180,  -209,   206,  -209,   196,  -209,
    -209,   249,    45,   210,  -209,  -209,   135,   216,   217,  -209,
     -18,   -18,   245,  -209,   -29,  -209,  -209,  -209,  -209,  -209,
    -209,   219,   220,  -209,   264,    70,  -209,  -209,   135,   135,
     135,   222,   182,  -209,   278,    45,  -209,   246,  -209,   290,
     259,   -18,  -209,   243,  -209,   135,  -209,  -209,   184,  -209,
    -209,  -209,   135,   234,   189,   299,   244,   299,   298,   255,
     247,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   248,  -209,
     305,   270,   299,  -209,   244,   244,   257,  -209,  -209,  -209,
      67,  -209,   276,  -209,  -209,  -209,   267,  -209
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       4,     3,    11,    12,    13,    14,     5,     0,     0,     9,
       6,    10,     7,     8,    15,     0,     0,     0,     0,     0,
       0,   168,    19,     0,     0,     0,   164,   165,     0,   105,
       0,     1,     2,     0,     0,     0,    18,     0,    24,    33,
      77,     0,     0,     0,    99,    97,   100,   101,    98,   169,
      55,    53,    54,    56,    57,     0,     0,   106,    91,   110,
      81,    82,    85,    89,     0,    93,     0,   107,    92,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,    26,
     169,    77,   155,     0,    16,     0,     0,     0,    90,     0,
     111,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,     0,    31,    23,     0,     0,
       0,     0,     0,    78,    58,    59,    61,    63,     0,    92,
       0,    27,     0,   166,     0,    95,    96,   114,   113,   116,
     117,   115,   112,    83,    84,    86,    87,    88,     0,     0,
     128,   118,   110,   145,    17,     0,    44,    46,    47,    35,
       0,    20,     0,    22,    34,     0,    25,    64,     0,     0,
       0,     0,   153,   152,   154,   149,   150,   151,     0,     0,
       0,     0,     0,     0,   156,   157,    94,     0,   103,   102,
       0,   135,   132,   133,   134,     0,    77,   129,     0,   130,
       0,   119,   126,   109,    30,     0,     0,     0,     0,    41,
       0,    36,     0,    32,     0,    49,     0,    76,    60,    62,
      65,     0,     0,     0,    66,    68,     0,     0,     0,   167,
     118,   118,   140,   131,     0,   122,   121,   124,   125,   123,
     120,     0,     0,    38,    40,    37,    21,    51,     0,     0,
       0,     0,     0,    67,     0,     0,    69,   139,   127,     0,
      79,   118,    45,     0,    43,     0,    42,    50,     0,    70,
      74,    72,     0,     0,     0,     0,     0,     0,   159,   138,
       0,    39,    52,    71,    75,    73,   137,   147,   141,    80,
       0,   142,     0,    48,     0,     0,     0,    28,   136,   148,
     163,   158,   143,   162,   161,   160,     0,   144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -209,  -209,  -209,  -209,  -209,  -209,  -209,     0,  -209,   -75,
    -209,   183,  -209,  -208,  -209,  -129,  -120,  -209,   174,  -113,
    -209,   -86,  -209,   -33,  -209,   116,   -37,  -209,  -209,  -209,
    -209,  -209,  -209,   185,  -160,  -209,  -209,  -209,  -209,   148,
    -209,  -209,   -79,  -209,  -209,  -209,   212,  -209,  -209,  -209,
    -209,  -209,    -3,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    17,    18,    19,    20,    21,    22,    96,   111,   115,
      87,   112,   159,   214,   166,    68,   123,   124,   125,   126,
     127,    89,   278,   128,    70,    71,    72,    73,    74,    75,
      40,    76,    77,   101,   202,   150,   196,   197,   198,   199,
     260,   297,    78,   288,   178,    91,    92,   291,   301,   305,
      38,   134,    79,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    32,   168,   185,    35,   131,    88,    69,   167,   129,
     118,   119,    99,   190,   252,   200,    24,   207,   208,    82,
     209,    93,    43,    44,    45,    46,    47,    48,   149,    98,
      49,    50,    97,   191,   226,    83,   215,   192,    31,   193,
     227,   268,   129,   129,   228,   210,   100,   274,   194,   201,
     221,   113,    33,   116,     5,   116,   116,     6,   219,    25,
     211,    59,   133,     7,   195,     9,   130,   145,   146,   147,
     257,   258,   223,    34,   148,   303,   152,    26,   243,   114,
     153,   304,    39,   190,   117,   212,    42,   224,    27,   169,
      41,   129,   129,   215,    28,     5,    51,   254,     6,   265,
      93,   279,   266,   191,     7,   151,     9,   192,    52,   193,
     232,    81,    29,    60,    61,    62,    63,    64,   194,   267,
     215,   269,    84,    30,    85,   113,   215,   137,    88,   138,
     116,    86,   213,   156,   157,   158,   281,    36,    37,    90,
     139,   140,    94,   283,  -168,   220,   235,   141,   236,   104,
     105,   106,   142,    95,   229,   286,   107,   289,   108,   237,
     238,   109,   172,   173,   174,   110,   239,   132,   172,   173,
     174,   240,   298,   175,   120,   136,   135,     5,   136,   175,
       6,   102,   103,   176,   177,   179,     7,   230,     9,   176,
     177,   180,   231,   181,   160,   182,   129,   287,   129,   183,
     154,   155,    53,    60,    61,    62,    63,    64,   161,   162,
      54,   165,    55,   129,   170,   299,   300,     5,   143,   144,
       6,   171,   251,    56,    57,   121,     7,   188,     9,   189,
      58,   261,   163,   162,   205,    59,    60,    61,    62,    63,
      64,   206,    53,   122,   216,   164,   162,    66,   186,   187,
      54,   217,    55,   246,   162,   273,   247,   248,   271,   248,
     282,   248,   222,    56,    57,   285,   248,   225,   234,   241,
      58,   242,   244,   245,   250,    59,    60,    61,    62,    63,
      64,   249,   253,    65,     1,   256,     2,    66,     3,     4,
       5,   255,   259,     6,    53,   262,   264,   263,   270,     7,
       8,     9,    54,   272,    55,   275,   276,   277,    10,    11,
     284,    59,   280,   290,   292,    56,    57,    12,    13,    14,
      15,   295,    58,   293,   296,   294,   302,    59,    60,    61,
      62,    63,    64,    53,   306,    65,   307,   203,   204,    66,
      67,    54,   184,    55,   218,   233,     0,    16,     0,     0,
       0,     0,     0,     0,    56,    57,   121,     0,     0,     0,
       0,    58,     0,     0,     0,    53,    59,    60,    61,    62,
      63,    64,     0,    54,   122,    55,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,    56,    57,     0,     0,
       0,     0,     0,    58,     0,     0,     0,     0,    59,    60,
      61,    62,    63,    64,     0,     0,    65,     0,     0,     0,
      66
};

static const yytype_int16 yycheck[] =
{
       0,     4,   122,   132,     7,    91,    17,    40,   121,    88,
      85,    86,    33,    26,   222,    33,     4,    29,    30,    59,
      32,    51,    25,    26,    27,    28,    29,    30,   107,    66,
      33,    34,    65,    46,    43,    75,   165,    50,    67,    52,
      49,   249,   121,   122,    53,    57,    67,   255,    61,    67,
     179,    81,    10,    83,     9,    85,    86,    12,   171,     6,
      72,    67,    95,    18,    77,    20,    77,   104,   105,   106,
     230,   231,    57,    13,    80,     8,   109,    24,   207,    82,
     110,    14,    45,    26,    84,   160,    73,    72,    35,   122,
       0,   170,   171,   222,     6,     9,    19,   226,    12,    29,
     130,   261,    32,    46,    18,   108,    20,    50,    74,    52,
     196,    75,    24,    68,    69,    70,    71,    72,    61,   248,
     249,   250,    33,    35,    75,   155,   255,    42,    17,    44,
     160,    75,   162,    21,    22,    23,   265,    40,    41,    67,
      55,    56,    71,   272,    83,   178,    42,    62,    44,    80,
      81,    82,    67,    75,   187,   275,    75,   277,    13,    55,
      56,    77,    63,    64,    65,    83,    62,    74,    63,    64,
      65,    67,   292,    74,    11,    76,    76,     9,    76,    74,
      12,    78,    79,    84,    85,    43,    18,   190,    20,    84,
      85,    49,   195,    51,    75,    53,   275,   276,   277,    57,
      76,    77,    34,    68,    69,    70,    71,    72,    76,    77,
      42,    75,    44,   292,    60,   294,   295,     9,   102,   103,
      12,    25,   222,    55,    56,    57,    18,    76,    20,    76,
      62,   234,    76,    77,    75,    67,    68,    69,    70,    71,
      72,    75,    34,    75,    77,    76,    77,    79,    76,    77,
      42,    76,    44,    76,    77,   255,    76,    77,    76,    77,
      76,    77,    75,    55,    56,    76,    77,    68,    26,    69,
      62,    69,    31,    72,    25,    67,    68,    69,    70,    71,
      72,    75,    72,    75,     3,    68,     5,    79,     7,     8,
       9,    75,    47,    12,    34,    76,    32,    77,    76,    18,
      19,    20,    42,    25,    44,    59,    16,    48,    27,    28,
      76,    67,    69,    15,    59,    55,    56,    36,    37,    38,
      39,    16,    62,    76,    54,    77,    69,    67,    68,    69,
      70,    71,    72,    34,    58,    75,    69,   152,   155,    79,
      80,    42,   130,    44,   170,   197,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    34,    67,    68,    69,    70,
      71,    72,    -1,    42,    75,    44,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,
      79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    36,    37,    38,    39,    66,    87,    88,    89,
      90,    91,    92,    93,     4,     6,    24,    35,     6,    24,
      35,    67,   138,    10,    13,   138,    40,    41,   136,    45,
     116,     0,    73,   138,   138,   138,   138,   138,   138,   138,
     138,    19,    74,    34,    42,    44,    55,    56,    62,    67,
      68,    69,    70,    71,    72,    75,    79,    80,   101,   109,
     110,   111,   112,   113,   114,   115,   117,   118,   128,   138,
     139,    75,    59,    75,    33,    75,    75,    96,    17,   107,
      67,   131,   132,   139,    71,    75,    93,   109,   112,    33,
      67,   119,    78,    79,    80,    81,    82,    75,    13,    77,
      83,    94,    97,   139,   138,    95,   139,    93,    95,    95,
      11,    57,    75,   102,   103,   104,   105,   106,   109,   128,
      77,   107,    74,   109,   137,    76,    76,    42,    44,    55,
      56,    62,    67,   111,   111,   112,   112,   112,    80,   128,
     121,   138,   109,   139,    76,    77,    21,    22,    23,    98,
      75,    76,    77,    76,    76,    75,   100,   105,   102,   109,
      60,    25,    63,    64,    65,    74,    84,    85,   130,    43,
      49,    51,    53,    57,   132,   101,    76,    77,    76,    76,
      26,    46,    50,    52,    61,    77,   122,   123,   124,   125,
      33,    67,   120,   119,    97,    75,    75,    29,    30,    32,
      57,    72,    95,   139,    99,   101,    77,    76,   104,   105,
     109,   101,    75,    57,    72,    68,    43,    49,    53,   109,
     138,   138,   107,   125,    26,    42,    44,    55,    56,    62,
      67,    69,    69,   101,    31,    72,    76,    76,    77,    75,
      25,    93,    99,    72,   101,    75,    68,   120,   120,    47,
     126,   138,    76,    77,    32,    29,    32,   101,    99,   101,
      76,    76,    25,    93,    99,    59,    16,    48,   108,   120,
      69,   101,    76,   101,    76,    76,   102,   128,   129,   102,
      15,   133,    59,    76,    77,    16,    54,   127,   102,   128,
     128,   134,    69,     8,    14,   135,    58,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    90,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   101,   101,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   107,   108,
     108,   109,   110,   110,   110,   111,   111,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   113,   114,   114,   114,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   124,   124,   125,   125,   125,   125,
     126,   126,   127,   127,   127,   128,   128,   129,   129,   130,
     130,   130,   130,   130,   130,   131,   131,   132,   133,   133,
     134,   135,   135,   135,   136,   136,   137,   137,   138,   139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     6,     3,     2,
       6,     8,     6,     5,     3,     6,     4,     5,    11,     1,
       3,     1,     3,     0,     3,     2,     3,     4,     4,     6,
       4,     3,     5,     5,     1,     4,     1,     1,     6,     1,
       3,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     2,     3,     3,     4,     3,     4,
       5,     6,     5,     6,     5,     6,     3,     0,     2,     0,
       2,     1,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     1,     1,     1,     4,     3,     3,     1,     1,     1,
       1,     1,     4,     4,     0,     1,     1,     1,     2,     4,
       0,     1,     2,     2,     2,     2,     2,     2,     0,     1,
       2,     2,     2,     2,     2,     2,     2,     4,     0,     1,
       1,     2,     1,     1,     1,     1,     6,     5,     4,     3,
       0,     3,     0,     2,     4,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       2,     1,     1,     0,     1,     1,     1,     3,     1,     1
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
#line 1853 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 85 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1862 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 90 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1871 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 95 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1880 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 111 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1888 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 115 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1896 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 119 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1904 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 123 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1912 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 130 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1920 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 137 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1928 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 144 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1936 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18: /* ddl: DROP TABLE tbName  */
#line 148 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1944 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19: /* ddl: DESC tbName  */
#line 152 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1952 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 156 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1960 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21: /* ddl: CREATE INDEX tbName ON tbName '(' colNameList ')'  */
#line 160 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Alternative: CREATE INDEX name ON table (cols)
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1969 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 165 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1977 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23: /* ddl: CREATE VIEW tbName AS dml  */
#line 169 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateView>((yyvsp[-2].sv_str), (yyvsp[0].sv_node));
    }
#line 1985 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24: /* ddl: DROP VIEW tbName  */
#line 173 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropView>((yyvsp[0].sv_str));
    }
#line 1993 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25: /* dml: INSERT INTO tbName optColList VALUES valueTupleList  */
#line 180 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-3].sv_str), (yyvsp[-2].sv_strs), (yyvsp[0].sv_vals_list));
    }
#line 2001 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26: /* dml: DELETE FROM tbName optWhereClause  */
#line 184 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_cond));
    }
#line 2009 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 188 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_cond));
    }
#line 2017 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28: /* dml: SELECT optDistinct selectItems FROM fromList optJoinList optWhereClause optGroupBy optHaving opt_order_clause optLimit  */
#line 193 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
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
#line 2053 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29: /* fieldList: field  */
#line 228 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2061 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30: /* fieldList: fieldList ',' field  */
#line 232 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2069 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31: /* colNameList: colName  */
#line 239 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2077 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32: /* colNameList: colNameList ',' colName  */
#line 243 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2085 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33: /* optColList: %empty  */
#line 250 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{};
    }
#line 2093 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34: /* optColList: '(' colNameList ')'  */
#line 254 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = (yyvsp[-1].sv_strs);
    }
#line 2101 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35: /* field: colName type  */
#line 261 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len), false, nullptr);
    }
#line 2109 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36: /* field: colName type VALUE_NULL  */
#line 265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
    }
#line 2117 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37: /* field: colName type NOT VALUE_NULL  */
#line 269 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
    }
#line 2125 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38: /* field: colName type DEFAULT value  */
#line 273 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), false, (yyvsp[0].sv_val));
    }
#line 2133 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39: /* field: colName type NOT VALUE_NULL DEFAULT value  */
#line 277 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-5].sv_str), (yyvsp[-4].sv_type_len), true, (yyvsp[0].sv_val));
    }
#line 2141 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40: /* field: colName type PRIMARY KEY  */
#line 281 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        (yyval.sv_field) = col;
    }
#line 2151 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41: /* field: colName type AUTO_INCREMENT  */
#line 287 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2161 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42: /* field: colName type NOT VALUE_NULL AUTO_INCREMENT  */
#line 293 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2171 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43: /* field: colName type PRIMARY KEY AUTO_INCREMENT  */
#line 299 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2182 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44: /* type: INT  */
#line 309 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2190 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45: /* type: CHAR '(' VALUE_INT ')'  */
#line 313 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Multiply by 4 for UTF-8 multi-byte character support
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int) * 4);
    }
#line 2199 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46: /* type: CHAR  */
#line 318 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // CHAR without length defaults to 256 bytes
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, 256);
    }
#line 2208 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47: /* type: FLOAT  */
#line 323 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2216 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48: /* type: FLOAT '(' VALUE_INT ',' VALUE_INT ')'  */
#line 327 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // DECIMAL(p,s) / NUMERIC(p,s): ignore precision/scale, store as FLOAT
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2225 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49: /* valueList: value  */
#line 335 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2233 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50: /* valueList: valueList ',' value  */
#line 339 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2241 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51: /* valueTupleList: '(' valueList ')'  */
#line 346 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list) = std::vector<std::vector<std::shared_ptr<Value>>>{(yyvsp[-1].sv_vals)};
    }
#line 2249 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52: /* valueTupleList: valueTupleList ',' '(' valueList ')'  */
#line 350 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list).push_back((yyvsp[-1].sv_vals));
    }
#line 2257 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 53: /* value: VALUE_INT  */
#line 357 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 54: /* value: VALUE_FLOAT  */
#line 361 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2273 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55: /* value: VALUE_STRING  */
#line 365 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2281 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 56: /* value: VALUE_BOOL  */
#line 369 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2289 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57: /* value: VALUE_NULL  */
#line 373 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<NullLit>();
    }
#line 2297 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60: /* cond_or: cond_or OR cond_and  */
#line 390 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_OR,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2306 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 62: /* cond_and: cond_and AND cond_not  */
#line 399 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_AND,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2315 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 64: /* cond_not: NOT cond_not  */
#line 408 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_NOT,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[0].sv_cond)});
    }
#line 2324 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65: /* cond_base: expr op expr  */
#line 416 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_expr), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2332 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 66: /* cond_base: col IS VALUE_NULL  */
#line 420 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-2].sv_col), SV_OP_IS_NULL);
    }
#line 2340 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67: /* cond_base: col IS NOT VALUE_NULL  */
#line 424 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-3].sv_col), SV_OP_IS_NOT_NULL);
    }
#line 2348 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68: /* cond_base: col LIKE VALUE_STRING  */
#line 428 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-2].sv_col), false, (yyvsp[0].sv_str));
    }
#line 2356 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69: /* cond_base: col NOT LIKE VALUE_STRING  */
#line 432 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-3].sv_col), true, (yyvsp[0].sv_str));
    }
#line 2364 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70: /* cond_base: col BETWEEN value AND value  */
#line 436 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-4].sv_col), false, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2372 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71: /* cond_base: col NOT BETWEEN value AND value  */
#line 440 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-5].sv_col), true, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2380 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72: /* cond_base: col IN '(' valueList ')'  */
#line 444 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, (yyvsp[-1].sv_vals));
    }
#line 2388 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73: /* cond_base: col NOT IN '(' valueList ')'  */
#line 448 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, (yyvsp[-1].sv_vals));
    }
#line 2396 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 74: /* cond_base: col IN '(' dml ')'  */
#line 452 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2404 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 75: /* cond_base: col NOT IN '(' dml ')'  */
#line 456 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2412 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 76: /* cond_base: '(' condition ')'  */
#line 460 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[-1].sv_cond);
    }
#line 2420 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 77: /* optWhereClause: %empty  */
#line 467 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2428 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 78: /* optWhereClause: WHERE condition  */
#line 471 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2436 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 79: /* optHaving: %empty  */
#line 478 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2444 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 80: /* optHaving: HAVING condition  */
#line 482 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2452 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 83: /* expr_add_sub: expr_add_sub '+' expr_mul_div  */
#line 498 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_ADD, (yyvsp[0].sv_expr));
    }
#line 2460 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 84: /* expr_add_sub: expr_add_sub '-' expr_mul_div  */
#line 502 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_SUB, (yyvsp[0].sv_expr));
    }
#line 2468 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 86: /* expr_mul_div: expr_mul_div '*' expr_unary  */
#line 510 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MUL, (yyvsp[0].sv_expr));
    }
#line 2476 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 87: /* expr_mul_div: expr_mul_div '/' expr_unary  */
#line 514 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_DIV, (yyvsp[0].sv_expr));
    }
#line 2484 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 88: /* expr_mul_div: expr_mul_div '%' expr_unary  */
#line 518 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MOD, (yyvsp[0].sv_expr));
    }
#line 2492 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 90: /* expr_unary: '-' expr_unary  */
#line 526 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>(nullptr, ARITH_NEG, (yyvsp[0].sv_expr));
    }
#line 2500 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 91: /* expr_base: value  */
#line 533 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2508 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 92: /* expr_base: col  */
#line 537 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2516 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 93: /* expr_base: aggExpr  */
#line 541 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_agg));
    }
#line 2524 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 94: /* expr_base: CONCAT '(' expr_list ')'  */
#line 545 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ConcatExpr>((yyvsp[-1].sv_exprs));
    }
#line 2532 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 95: /* expr_base: '(' dml ')'  */
#line 549 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<SubqueryExpr>((yyvsp[-1].sv_node));
    }
#line 2540 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 96: /* expr_base: '(' expr ')'  */
#line 553 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = (yyvsp[-1].sv_expr);
    }
#line 2548 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 97: /* aggType: COUNT  */
#line 563 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_COUNT; }
#line 2554 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 98: /* aggType: SUM  */
#line 564 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_SUM; }
#line 2560 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 99: /* aggType: AVG  */
#line 565 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_AVG; }
#line 2566 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 100: /* aggType: MAX  */
#line 566 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MAX; }
#line 2572 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 101: /* aggType: MIN  */
#line 567 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MIN; }
#line 2578 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 102: /* aggExpr: aggType '(' col ')'  */
#line 572 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_agg) = std::make_shared<AggExpr>((yyvsp[-3].sv_agg_type), (yyvsp[-1].sv_col)->col_name);
    }
#line 2586 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 103: /* aggExpr: aggType '(' '*' ')'  */
#line 576 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        if ((yyvsp[-3].sv_agg_type) == AGG_COUNT) {
            (yyval.sv_agg) = std::make_shared<AggExpr>(AGG_COUNT, "", true);
        } else {
            yyerror(&yylloc, "Only COUNT supports * argument");
            YYERROR;
        }
    }
#line 2599 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 104: /* optDistinct: %empty  */
#line 591 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = false; }
#line 2605 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 105: /* optDistinct: DISTINCT  */
#line 592 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = true; }
#line 2611 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 106: /* selectItems: '*'  */
#line 597 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{};
    }
#line 2619 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 108: /* selectItemList: expr opt_alias  */
#line 605 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[-1].sv_expr)};
    }
#line 2627 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 109: /* selectItemList: selectItemList ',' expr opt_alias  */
#line 609 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[-1].sv_expr));
    }
#line 2635 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 110: /* opt_alias: %empty  */
#line 615 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2641 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 111: /* opt_alias: IDENTIFIER  */
#line 616 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2647 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 112: /* opt_alias: AS IDENTIFIER  */
#line 617 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2653 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 113: /* opt_alias: AS COUNT  */
#line 618 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2659 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 114: /* opt_alias: AS AVG  */
#line 619 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2665 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 115: /* opt_alias: AS SUM  */
#line 620 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2671 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 116: /* opt_alias: AS MAX  */
#line 621 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2677 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 117: /* opt_alias: AS MIN  */
#line 622 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2683 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 118: /* optAliasStr: %empty  */
#line 626 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = ""; }
#line 2689 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 119: /* optAliasStr: IDENTIFIER  */
#line 627 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2695 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 120: /* optAliasStr: AS IDENTIFIER  */
#line 628 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2701 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 121: /* optAliasStr: AS COUNT  */
#line 629 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "count"; }
#line 2707 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 122: /* optAliasStr: AS AVG  */
#line 630 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "avg"; }
#line 2713 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 123: /* optAliasStr: AS SUM  */
#line 631 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "sum"; }
#line 2719 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 124: /* optAliasStr: AS MAX  */
#line 632 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "max"; }
#line 2725 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 125: /* optAliasStr: AS MIN  */
#line 633 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "min"; }
#line 2731 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 126: /* fromList: tbName optAliasStr  */
#line 638 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[-1].sv_str)};
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2740 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 127: /* fromList: fromList ',' tbName optAliasStr  */
#line 643 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[-1].sv_str));
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2749 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 128: /* optJoinList: %empty  */
#line 651 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{};
    }
#line 2757 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 129: /* optJoinList: joinList  */
#line 655 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = (yyvsp[0].sv_joins);
    }
#line 2765 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 130: /* joinList: joinClause  */
#line 662 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join)};
    }
#line 2773 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 131: /* joinList: joinList joinClause  */
#line 666 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins).push_back((yyvsp[0].sv_join));
    }
#line 2781 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 132: /* joinType: INNER  */
#line 672 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = INNER_JOIN; }
#line 2787 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 133: /* joinType: LEFT  */
#line 673 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = LEFT_JOIN; }
#line 2793 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 134: /* joinType: RIGHT  */
#line 674 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = RIGHT_JOIN; }
#line 2799 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 135: /* joinType: FULL  */
#line 675 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = FULL_JOIN; }
#line 2805 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 136: /* joinClause: joinType JOIN tbName optAliasStr ON condition  */
#line 680 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), static_cast<JoinType>((yyvsp[-5].sv_int)), (yyvsp[-2].sv_str));
    }
#line 2813 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 137: /* joinClause: JOIN tbName optAliasStr ON condition  */
#line 684 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), INNER_JOIN, (yyvsp[-2].sv_str));
    }
#line 2821 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 138: /* joinClause: joinType JOIN tbName optAliasStr  */
#line 688 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, static_cast<JoinType>((yyvsp[-3].sv_int)), (yyvsp[0].sv_str));
    }
#line 2829 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 139: /* joinClause: JOIN tbName optAliasStr  */
#line 692 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, INNER_JOIN, (yyvsp[0].sv_str));
    }
#line 2837 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 140: /* optGroupBy: %empty  */
#line 699 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = nullptr;
    }
#line 2845 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 141: /* optGroupBy: GROUP BY colList  */
#line 703 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = std::make_shared<GroupBy>((yyvsp[0].sv_cols));
    }
#line 2853 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 142: /* optLimit: %empty  */
#line 710 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = nullptr;
    }
#line 2861 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 143: /* optLimit: LIMIT VALUE_INT  */
#line 714 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[0].sv_int));
    }
#line 2869 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 144: /* optLimit: LIMIT VALUE_INT OFFSET VALUE_INT  */
#line 718 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[-2].sv_int), (yyvsp[0].sv_int));
    }
#line 2877 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 145: /* col: tbName '.' colName  */
#line 725 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2885 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 146: /* col: colName  */
#line 729 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2893 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 147: /* colList: col  */
#line 736 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2901 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 148: /* colList: colList ',' col  */
#line 740 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2909 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 149: /* op: '='  */
#line 747 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2917 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 150: /* op: '<'  */
#line 751 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2925 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 151: /* op: '>'  */
#line 755 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2933 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 152: /* op: NEQ  */
#line 759 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2941 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 153: /* op: LEQ  */
#line 763 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2949 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 154: /* op: GEQ  */
#line 767 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2957 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 155: /* setClauses: setClause  */
#line 774 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2965 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 156: /* setClauses: setClauses ',' setClause  */
#line 778 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2973 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 157: /* setClause: colName '=' value  */
#line 785 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2981 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 158: /* opt_order_clause: ORDER BY order_clause  */
#line 792 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby);
    }
#line 2989 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 159: /* opt_order_clause: %empty  */
#line 795 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                    { /* ignore*/ }
#line 2995 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 160: /* order_clause: col opt_asc_desc  */
#line 800 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 3003 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 161: /* opt_asc_desc: ASC  */
#line 806 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 3009 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 162: /* opt_asc_desc: DESC  */
#line 807 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DESC; }
#line 3015 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 163: /* opt_asc_desc: %empty  */
#line 808 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 3021 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 164: /* set_knob_type: ENABLE_NESTLOOP  */
#line 812 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 3027 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 165: /* set_knob_type: ENABLE_SORTMERGE  */
#line 813 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 3033 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 166: /* expr_list: expr  */
#line 818 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[0].sv_expr)};
    }
#line 3041 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 167: /* expr_list: expr_list ',' expr  */
#line 822 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[0].sv_expr));
    }
#line 3049 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 3053 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"

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

#line 830 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"

