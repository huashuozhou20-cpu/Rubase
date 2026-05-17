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
  YYSYMBOL_TXN_BEGIN = 35,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 36,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 37,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 38,              /* TXN_ROLLBACK  */
  YYSYMBOL_ENABLE_NESTLOOP = 39,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 40,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_AVG = 41,                       /* AVG  */
  YYSYMBOL_BETWEEN = 42,                   /* BETWEEN  */
  YYSYMBOL_COUNT = 43,                     /* COUNT  */
  YYSYMBOL_DISTINCT = 44,                  /* DISTINCT  */
  YYSYMBOL_FULL = 45,                      /* FULL  */
  YYSYMBOL_GROUP = 46,                     /* GROUP  */
  YYSYMBOL_HAVING = 47,                    /* HAVING  */
  YYSYMBOL_IN = 48,                        /* IN  */
  YYSYMBOL_INNER = 49,                     /* INNER  */
  YYSYMBOL_IS = 50,                        /* IS  */
  YYSYMBOL_LEFT = 51,                      /* LEFT  */
  YYSYMBOL_LIKE = 52,                      /* LIKE  */
  YYSYMBOL_LIMIT = 53,                     /* LIMIT  */
  YYSYMBOL_MAX = 54,                       /* MAX  */
  YYSYMBOL_MIN = 55,                       /* MIN  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_OFFSET = 57,                    /* OFFSET  */
  YYSYMBOL_ON = 58,                        /* ON  */
  YYSYMBOL_OR = 59,                        /* OR  */
  YYSYMBOL_RIGHT = 60,                     /* RIGHT  */
  YYSYMBOL_SUM = 61,                       /* SUM  */
  YYSYMBOL_LEQ = 62,                       /* LEQ  */
  YYSYMBOL_NEQ = 63,                       /* NEQ  */
  YYSYMBOL_GEQ = 64,                       /* GEQ  */
  YYSYMBOL_T_EOF = 65,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 66,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 67,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 68,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 69,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 70,                /* VALUE_BOOL  */
  YYSYMBOL_VALUE_NULL = 71,                /* VALUE_NULL  */
  YYSYMBOL_72_ = 72,                       /* ';'  */
  YYSYMBOL_73_ = 73,                       /* '='  */
  YYSYMBOL_74_ = 74,                       /* '('  */
  YYSYMBOL_75_ = 75,                       /* ')'  */
  YYSYMBOL_76_ = 76,                       /* ','  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '/'  */
  YYSYMBOL_81_ = 81,                       /* '%'  */
  YYSYMBOL_82_ = 82,                       /* '.'  */
  YYSYMBOL_83_ = 83,                       /* '<'  */
  YYSYMBOL_84_ = 84,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_start = 86,                     /* start  */
  YYSYMBOL_stmt = 87,                      /* stmt  */
  YYSYMBOL_txnStmt = 88,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 89,                    /* dbStmt  */
  YYSYMBOL_setStmt = 90,                   /* setStmt  */
  YYSYMBOL_ddl = 91,                       /* ddl  */
  YYSYMBOL_dml = 92,                       /* dml  */
  YYSYMBOL_fieldList = 93,                 /* fieldList  */
  YYSYMBOL_colNameList = 94,               /* colNameList  */
  YYSYMBOL_optColList = 95,                /* optColList  */
  YYSYMBOL_field = 96,                     /* field  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_valueList = 98,                 /* valueList  */
  YYSYMBOL_valueTupleList = 99,            /* valueTupleList  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_condition = 101,                /* condition  */
  YYSYMBOL_cond_or = 102,                  /* cond_or  */
  YYSYMBOL_cond_and = 103,                 /* cond_and  */
  YYSYMBOL_cond_not = 104,                 /* cond_not  */
  YYSYMBOL_cond_base = 105,                /* cond_base  */
  YYSYMBOL_optWhereClause = 106,           /* optWhereClause  */
  YYSYMBOL_optHaving = 107,                /* optHaving  */
  YYSYMBOL_expr = 108,                     /* expr  */
  YYSYMBOL_expr_add_sub = 109,             /* expr_add_sub  */
  YYSYMBOL_expr_mul_div = 110,             /* expr_mul_div  */
  YYSYMBOL_expr_unary = 111,               /* expr_unary  */
  YYSYMBOL_expr_base = 112,                /* expr_base  */
  YYSYMBOL_aggType = 113,                  /* aggType  */
  YYSYMBOL_aggExpr = 114,                  /* aggExpr  */
  YYSYMBOL_optDistinct = 115,              /* optDistinct  */
  YYSYMBOL_selectItems = 116,              /* selectItems  */
  YYSYMBOL_selectItemList = 117,           /* selectItemList  */
  YYSYMBOL_opt_alias = 118,                /* opt_alias  */
  YYSYMBOL_optAliasStr = 119,              /* optAliasStr  */
  YYSYMBOL_fromList = 120,                 /* fromList  */
  YYSYMBOL_optJoinList = 121,              /* optJoinList  */
  YYSYMBOL_joinList = 122,                 /* joinList  */
  YYSYMBOL_joinType = 123,                 /* joinType  */
  YYSYMBOL_joinClause = 124,               /* joinClause  */
  YYSYMBOL_optGroupBy = 125,               /* optGroupBy  */
  YYSYMBOL_optLimit = 126,                 /* optLimit  */
  YYSYMBOL_col = 127,                      /* col  */
  YYSYMBOL_colList = 128,                  /* colList  */
  YYSYMBOL_op = 129,                       /* op  */
  YYSYMBOL_setClauses = 130,               /* setClauses  */
  YYSYMBOL_setClause = 131,                /* setClause  */
  YYSYMBOL_opt_order_clause = 132,         /* opt_order_clause  */
  YYSYMBOL_order_clause = 133,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 134,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 135,            /* set_knob_type  */
  YYSYMBOL_expr_list = 136,                /* expr_list  */
  YYSYMBOL_tbName = 137,                   /* tbName  */
  YYSYMBOL_colName = 138                   /* colName  */
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
#define YYLAST   398

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  296

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,     2,     2,     2,     2,     2,    81,     2,     2,
      74,    75,    79,    77,    76,    78,    82,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    72,
      83,    73,    84,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    84,    89,    94,   102,   103,   104,   105,
     106,   110,   114,   118,   122,   129,   136,   143,   147,   151,
     155,   159,   166,   170,   174,   178,   214,   218,   225,   229,
     237,   240,   247,   251,   255,   259,   263,   269,   275,   281,
     291,   295,   300,   304,   312,   316,   323,   327,   334,   338,
     342,   346,   350,   362,   366,   367,   375,   376,   384,   385,
     393,   397,   401,   405,   409,   413,   417,   421,   425,   429,
     433,   437,   445,   448,   456,   459,   470,   474,   475,   479,
     486,   487,   491,   495,   502,   503,   510,   514,   518,   522,
     526,   530,   541,   542,   543,   544,   545,   549,   553,   569,
     570,   574,   578,   582,   586,   593,   594,   595,   596,   597,
     598,   599,   600,   604,   605,   606,   607,   608,   609,   610,
     611,   615,   620,   629,   632,   639,   643,   650,   651,   652,
     653,   657,   661,   665,   669,   677,   680,   688,   691,   695,
     702,   706,   713,   717,   724,   728,   732,   736,   740,   744,
     751,   755,   762,   769,   773,   777,   784,   785,   786,   790,
     791,   795,   799,   805,   807
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
  "PRIMARY", "KEY", "AUTO_INCREMENT", "AS", "CONCAT", "TXN_BEGIN",
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

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-164)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     255,     8,    26,    42,   -23,    44,    80,   -23,    71,    18,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,    85,    50,  -192,
    -192,  -192,  -192,  -192,  -192,   -23,   -23,   -23,   -23,  -192,
    -192,   -23,   -23,    79,  -192,  -192,    52,  -192,   243,  -192,
    -192,    56,    64,  -192,    66,    73,   128,    86,    97,    81,
    -192,  -192,  -192,  -192,  -192,   127,  -192,  -192,  -192,  -192,
    -192,   183,   320,  -192,  -192,   -22,    36,   -63,  -192,  -192,
     117,  -192,   169,   142,  -192,   137,  -192,    86,    86,    86,
      86,   210,   282,  -192,  -192,    -2,  -192,   149,  -192,   320,
     157,   161,  -192,    34,  -192,  -192,   320,   320,   320,   320,
     320,   -39,   -23,   320,    86,    57,  -192,   140,    60,  -192,
      90,   100,   165,   282,   103,  -192,   176,   215,  -192,  -192,
      43,   154,    86,  -192,   160,  -192,   104,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,   -63,   -63,  -192,  -192,  -192,
     166,   167,     4,   -19,   -22,  -192,  -192,    86,  -192,   171,
     172,    72,  -192,    86,  -192,  -192,   160,   179,  -192,   173,
     150,   282,   282,  -192,  -192,  -192,  -192,  -192,  -192,   320,
     160,   182,   -15,   180,   108,  -192,  -192,  -192,   320,  -192,
    -192,   -23,  -192,  -192,  -192,  -192,   -23,   128,    16,   233,
    -192,    88,  -192,  -192,  -192,  -192,   197,   198,   160,   237,
    -192,   199,  -192,   109,  -192,   195,  -192,   215,  -192,  -192,
     246,     1,   201,  -192,  -192,   160,   202,   211,  -192,   -19,
     -19,   234,  -192,   -23,  -192,  -192,  -192,  -192,  -192,  -192,
     204,   205,  -192,   253,    65,  -192,   160,   160,   160,   212,
     111,  -192,   263,     1,  -192,   231,  -192,   278,   248,   -19,
    -192,   228,  -192,   160,  -192,  -192,   118,  -192,  -192,  -192,
     160,   224,   122,   282,   235,   282,   285,   244,   230,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,   227,  -192,   290,   254,
     282,  -192,   235,   235,   240,  -192,  -192,  -192,    49,  -192,
     258,  -192,  -192,  -192,   250,  -192
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       4,     3,    11,    12,    13,    14,     5,     0,     0,     9,
       6,    10,     7,     8,    15,     0,     0,     0,     0,   163,
      19,     0,     0,     0,   159,   160,     0,   100,     0,     1,
       2,     0,     0,    18,     0,    30,    72,     0,     0,     0,
      94,    92,    95,    96,    93,   164,    50,    48,    49,    51,
      52,     0,     0,   101,    86,   105,    76,    77,    80,    84,
       0,    88,     0,   102,    87,     0,   141,     0,     0,     0,
       0,     0,     0,    23,   164,    72,   150,     0,    16,     0,
       0,     0,    85,     0,   106,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,    28,
       0,     0,     0,     0,     0,    73,    53,    54,    56,    58,
       0,    87,     0,    24,     0,   161,     0,    90,    91,   109,
     108,   111,   112,   110,   107,    78,    79,    81,    82,    83,
       0,     0,   123,   113,   105,   140,    17,     0,    40,     0,
      42,    32,    20,     0,    21,    31,     0,    22,    59,     0,
       0,     0,     0,   148,   147,   149,   144,   145,   146,     0,
       0,     0,     0,     0,     0,   151,   152,    89,     0,    98,
      97,     0,   130,   127,   128,   129,     0,    72,   124,     0,
     125,     0,   114,   121,   104,    27,     0,     0,     0,     0,
      37,     0,    29,     0,    44,     0,    71,    55,    57,    60,
       0,     0,     0,    61,    63,     0,     0,     0,   162,   113,
     113,   135,   126,     0,   117,   116,   119,   120,   118,   115,
       0,     0,    34,    36,    33,    46,     0,     0,     0,     0,
       0,    62,     0,     0,    64,   134,   122,     0,    74,   113,
      41,     0,    39,     0,    38,    45,     0,    65,    69,    67,
       0,     0,     0,     0,     0,     0,   154,   133,     0,    35,
      47,    66,    70,    68,   132,   142,   136,    75,     0,   137,
       0,    43,     0,     0,     0,    25,   131,   143,   158,   153,
     138,   157,   156,   155,     0,   139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,  -192,  -192,  -192,     0,  -192,   120,
    -192,   177,  -192,  -191,  -192,  -119,  -112,  -192,   158,  -104,
    -192,   -79,  -192,   -30,  -192,   119,   -17,  -192,  -192,  -192,
    -192,  -192,  -192,   184,  -129,  -192,  -192,  -192,  -192,   138,
    -192,  -192,   -75,  -192,  -192,  -192,   207,  -192,  -192,  -192,
    -192,  -192,    -3,   -44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    17,    18,    19,    20,    21,    22,    90,   105,   108,
      81,   106,   151,   203,   157,    64,   115,   116,   117,   118,
     119,    83,   266,   120,    66,    67,    68,    69,    70,    71,
      38,    72,    73,    95,   193,   142,   187,   188,   189,   190,
     248,   285,    74,   276,   169,    85,    86,   279,   289,   293,
      36,   126,    75,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    30,   159,    87,    33,   176,   123,   121,    65,   158,
       5,    93,    24,     6,   191,    82,    98,    99,   100,     7,
     240,     9,    41,    42,    43,    44,   141,    55,    45,    46,
     181,    91,    25,   107,   109,   109,   109,   204,   121,   121,
     140,   212,   181,    29,    94,    92,   256,   192,    27,   182,
      26,   210,   262,   183,    31,   184,   213,   291,   208,   125,
     145,   182,    37,   292,   185,   183,    28,   184,    56,    57,
      58,    59,    60,   144,   122,   129,   185,   130,    87,   232,
     186,   137,   138,   139,   160,    39,   121,   121,   131,   132,
     245,   246,   204,    32,   253,   133,   242,   254,    47,   143,
     134,   198,   199,   107,   200,   163,   164,   165,   221,   202,
      34,    35,     5,    96,    97,     6,   166,   255,   204,   257,
     267,     7,    40,     9,   204,    48,   167,   168,   201,   224,
      77,   225,   146,   147,   269,   152,   153,    49,    78,   209,
      79,   271,   226,   227,    50,    82,    51,    80,   218,   228,
     215,   274,    84,   277,   229,    89,   216,    52,    53,   113,
     217,   148,   149,   150,    54,   154,   153,    88,   286,    55,
      56,    57,    58,    59,    60,   155,   153,   114,   219,   177,
     178,    62,   102,   220,   235,   236,   259,   236,   121,   275,
     121,   101,     5,   270,   236,     6,   170,   273,   236,   110,
     111,     7,   171,     9,   172,   121,   173,   287,   288,  -163,
     174,   239,   163,   164,   165,   135,   136,    49,   103,   104,
     249,   112,   124,   166,    50,   128,    51,    56,    57,    58,
      59,    60,   127,   167,   168,   161,   128,    52,    53,   156,
     162,   179,   180,   261,    54,   196,   197,   214,   206,    55,
      56,    57,    58,    59,    60,   205,   211,    61,     1,   223,
       2,    62,     3,     4,     5,   230,   231,     6,   233,   237,
     234,   238,   241,     7,     8,     9,   243,    49,   244,   250,
     247,   251,    10,    11,    50,   252,    51,   258,   260,   263,
      12,    13,    14,    15,   264,   265,   268,    52,    53,   272,
     278,    55,   280,   282,    54,   281,   283,   284,   290,    55,
      56,    57,    58,    59,    60,   294,    49,    61,   295,   207,
      16,    62,    63,    50,   195,    51,   222,     0,   194,   175,
       0,     0,     0,     0,     0,     0,    52,    53,   113,     0,
       0,     0,     0,    54,     0,     0,     0,     0,    55,    56,
      57,    58,    59,    60,    49,     0,   114,     0,     0,     0,
      62,    50,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    53,     0,     0,     0,     0,
       0,    54,     0,     0,     0,     0,    55,    56,    57,    58,
      59,    60,     0,     0,    61,     0,     0,     0,    62
};

static const yytype_int16 yycheck[] =
{
       0,     4,   114,    47,     7,   124,    85,    82,    38,   113,
       9,    33,     4,    12,    33,    17,    79,    80,    81,    18,
     211,    20,    25,    26,    27,    28,   101,    66,    31,    32,
      26,    61,     6,    77,    78,    79,    80,   156,   113,   114,
      79,    56,    26,    66,    66,    62,   237,    66,     6,    45,
      24,   170,   243,    49,    10,    51,    71,     8,   162,    89,
     104,    45,    44,    14,    60,    49,    24,    51,    67,    68,
      69,    70,    71,   103,    76,    41,    60,    43,   122,   198,
      76,    98,    99,   100,   114,     0,   161,   162,    54,    55,
     219,   220,   211,    13,    29,    61,   215,    32,    19,   102,
      66,    29,    30,   147,    32,    62,    63,    64,   187,   153,
      39,    40,     9,    77,    78,    12,    73,   236,   237,   238,
     249,    18,    72,    20,   243,    73,    83,    84,    56,    41,
      74,    43,    75,    76,   253,    75,    76,    34,    74,   169,
      74,   260,    54,    55,    41,    17,    43,    74,   178,    61,
      42,   263,    66,   265,    66,    74,    48,    54,    55,    56,
      52,    21,    22,    23,    61,    75,    76,    70,   280,    66,
      67,    68,    69,    70,    71,    75,    76,    74,   181,    75,
      76,    78,    13,   186,    75,    76,    75,    76,   263,   264,
     265,    74,     9,    75,    76,    12,    42,    75,    76,    79,
      80,    18,    48,    20,    50,   280,    52,   282,   283,    82,
      56,   211,    62,    63,    64,    96,    97,    34,    76,    82,
     223,    11,    73,    73,    41,    75,    43,    67,    68,    69,
      70,    71,    75,    83,    84,    59,    75,    54,    55,    74,
      25,    75,    75,   243,    61,    74,    74,    67,    75,    66,
      67,    68,    69,    70,    71,    76,    74,    74,     3,    26,
       5,    78,     7,     8,     9,    68,    68,    12,    31,    74,
      71,    25,    71,    18,    19,    20,    74,    34,    67,    75,
      46,    76,    27,    28,    41,    32,    43,    75,    25,    58,
      35,    36,    37,    38,    16,    47,    68,    54,    55,    75,
      15,    66,    58,    76,    61,    75,    16,    53,    68,    66,
      67,    68,    69,    70,    71,    57,    34,    74,    68,   161,
      65,    78,    79,    41,   147,    43,   188,    -1,   144,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    34,    -1,    74,    -1,    -1,    -1,
      78,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    71,    -1,    -1,    74,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    35,    36,    37,    38,    65,    86,    87,    88,
      89,    90,    91,    92,     4,     6,    24,     6,    24,    66,
     137,    10,    13,   137,    39,    40,   135,    44,   115,     0,
      72,   137,   137,   137,   137,   137,   137,    19,    73,    34,
      41,    43,    54,    55,    61,    66,    67,    68,    69,    70,
      71,    74,    78,    79,   100,   108,   109,   110,   111,   112,
     113,   114,   116,   117,   127,   137,   138,    74,    74,    74,
      74,    95,    17,   106,    66,   130,   131,   138,    70,    74,
      92,   108,   111,    33,    66,   118,    77,    78,    79,    80,
      81,    74,    13,    76,    82,    93,    96,   138,    94,   138,
      94,    94,    11,    56,    74,   101,   102,   103,   104,   105,
     108,   127,    76,   106,    73,   108,   136,    75,    75,    41,
      43,    54,    55,    61,    66,   110,   110,   111,   111,   111,
      79,   127,   120,   137,   108,   138,    75,    76,    21,    22,
      23,    97,    75,    76,    75,    75,    74,    99,   104,   101,
     108,    59,    25,    62,    63,    64,    73,    83,    84,   129,
      42,    48,    50,    52,    56,   131,   100,    75,    76,    75,
      75,    26,    45,    49,    51,    60,    76,   121,   122,   123,
     124,    33,    66,   119,   118,    96,    74,    74,    29,    30,
      32,    56,   138,    98,   100,    76,    75,   103,   104,   108,
     100,    74,    56,    71,    67,    42,    48,    52,   108,   137,
     137,   106,   124,    26,    41,    43,    54,    55,    61,    66,
      68,    68,   100,    31,    71,    75,    76,    74,    25,    92,
      98,    71,   100,    74,    67,   119,   119,    46,   125,   137,
      75,    76,    32,    29,    32,   100,    98,   100,    75,    75,
      25,    92,    98,    58,    16,    47,   107,   119,    68,   100,
      75,   100,    75,    75,   101,   127,   128,   101,    15,   132,
      58,    75,    76,    16,    53,   126,   101,   127,   127,   133,
      68,     8,    14,   134,    57,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    89,    90,    91,    91,    91,
      91,    91,    92,    92,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      97,    97,    97,    97,    98,    98,    99,    99,   100,   100,
     100,   100,   100,   101,   102,   102,   103,   103,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   106,   106,   107,   107,   108,   109,   109,   109,
     110,   110,   110,   110,   111,   111,   112,   112,   112,   112,
     112,   112,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   121,   121,   122,   122,   123,   123,   123,
     123,   124,   124,   124,   124,   125,   125,   126,   126,   126,
     127,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     130,   130,   131,   132,   132,   133,   134,   134,   134,   135,
     135,   136,   136,   137,   138
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
       3,     3,     4,     3,     4,     5,     6,     5,     6,     5,
       6,     3,     0,     2,     0,     2,     1,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     1,     1,     1,     4,
       3,     3,     1,     1,     1,     1,     1,     4,     4,     0,
       1,     1,     1,     2,     4,     0,     1,     2,     2,     2,
       2,     2,     2,     0,     1,     2,     2,     2,     2,     2,
       2,     2,     4,     0,     1,     1,     2,     1,     1,     1,
       1,     6,     5,     4,     3,     0,     3,     0,     2,     4,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     2,     1,     1,     0,     1,
       1,     1,     3,     1,     1
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
#line 1845 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 85 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1854 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 90 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1863 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 95 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1872 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 111 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1880 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 115 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1888 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 119 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1896 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 123 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1904 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 130 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1912 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 16: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 137 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1920 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 17: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 144 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1928 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 18: /* ddl: DROP TABLE tbName  */
#line 148 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1936 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 19: /* ddl: DESC tbName  */
#line 152 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1944 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 20: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 156 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1952 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 21: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 160 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1960 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 22: /* dml: INSERT INTO tbName optColList VALUES valueTupleList  */
#line 167 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-3].sv_str), (yyvsp[-2].sv_strs), (yyvsp[0].sv_vals_list));
    }
#line 1968 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 23: /* dml: DELETE FROM tbName optWhereClause  */
#line 171 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_cond));
    }
#line 1976 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 24: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 175 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_cond));
    }
#line 1984 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 25: /* dml: SELECT optDistinct selectItems FROM fromList optJoinList optWhereClause optGroupBy optHaving opt_order_clause optLimit  */
#line 180 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
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
#line 2020 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 26: /* fieldList: field  */
#line 215 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2028 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 27: /* fieldList: fieldList ',' field  */
#line 219 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2036 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 28: /* colNameList: colName  */
#line 226 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2044 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 29: /* colNameList: colNameList ',' colName  */
#line 230 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2052 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 30: /* optColList: %empty  */
#line 237 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{};
    }
#line 2060 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 31: /* optColList: '(' colNameList ')'  */
#line 241 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = (yyvsp[-1].sv_strs);
    }
#line 2068 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 32: /* field: colName type  */
#line 248 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len), false, nullptr);
    }
#line 2076 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 33: /* field: colName type NOT VALUE_NULL  */
#line 252 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
    }
#line 2084 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 34: /* field: colName type DEFAULT value  */
#line 256 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), false, (yyvsp[0].sv_val));
    }
#line 2092 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 35: /* field: colName type NOT VALUE_NULL DEFAULT value  */
#line 260 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-5].sv_str), (yyvsp[-4].sv_type_len), true, (yyvsp[0].sv_val));
    }
#line 2100 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 36: /* field: colName type PRIMARY KEY  */
#line 264 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-3].sv_str), (yyvsp[-2].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        (yyval.sv_field) = col;
    }
#line 2110 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 37: /* field: colName type AUTO_INCREMENT  */
#line 270 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-2].sv_str), (yyvsp[-1].sv_type_len), false, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2120 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 38: /* field: colName type NOT VALUE_NULL AUTO_INCREMENT  */
#line 276 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2130 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 39: /* field: colName type PRIMARY KEY AUTO_INCREMENT  */
#line 282 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        auto col = std::make_shared<ColDef>((yyvsp[-4].sv_str), (yyvsp[-3].sv_type_len), true, nullptr);
        col->primary_key_ = true;
        col->auto_increment_ = true;
        (yyval.sv_field) = col;
    }
#line 2141 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 40: /* type: INT  */
#line 292 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2149 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 41: /* type: CHAR '(' VALUE_INT ')'  */
#line 296 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // Multiply by 4 for UTF-8 multi-byte character support
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int) * 4);
    }
#line 2158 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 42: /* type: FLOAT  */
#line 301 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2166 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 43: /* type: FLOAT '(' VALUE_INT ',' VALUE_INT ')'  */
#line 305 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        // DECIMAL(p,s) / NUMERIC(p,s): ignore precision/scale, store as FLOAT
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2175 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 44: /* valueList: value  */
#line 313 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2183 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 45: /* valueList: valueList ',' value  */
#line 317 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2191 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 46: /* valueTupleList: '(' valueList ')'  */
#line 324 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list) = std::vector<std::vector<std::shared_ptr<Value>>>{(yyvsp[-1].sv_vals)};
    }
#line 2199 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 47: /* valueTupleList: valueTupleList ',' '(' valueList ')'  */
#line 328 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_vals_list).push_back((yyvsp[-1].sv_vals));
    }
#line 2207 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 48: /* value: VALUE_INT  */
#line 335 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2215 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 49: /* value: VALUE_FLOAT  */
#line 339 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2223 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_STRING  */
#line 343 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2231 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 51: /* value: VALUE_BOOL  */
#line 347 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2239 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_NULL  */
#line 351 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<NullLit>();
    }
#line 2247 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 55: /* cond_or: cond_or OR cond_and  */
#line 368 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_OR,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2256 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 57: /* cond_and: cond_and AND cond_not  */
#line 377 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_AND,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[-2].sv_cond), (yyvsp[0].sv_cond)});
    }
#line 2265 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 59: /* cond_not: NOT cond_not  */
#line 386 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LogicExpr>(LOGIC_NOT,
              std::vector<std::shared_ptr<CondExpr>>{(yyvsp[0].sv_cond)});
    }
#line 2274 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 60: /* cond_base: expr op expr  */
#line 394 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_expr), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2282 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 61: /* cond_base: col IS VALUE_NULL  */
#line 398 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-2].sv_col), SV_OP_IS_NULL);
    }
#line 2290 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 62: /* cond_base: col IS NOT VALUE_NULL  */
#line 402 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<UnaryCondExpr>((yyvsp[-3].sv_col), SV_OP_IS_NOT_NULL);
    }
#line 2298 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 63: /* cond_base: col LIKE VALUE_STRING  */
#line 406 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-2].sv_col), false, (yyvsp[0].sv_str));
    }
#line 2306 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 64: /* cond_base: col NOT LIKE VALUE_STRING  */
#line 410 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<LikeExpr>((yyvsp[-3].sv_col), true, (yyvsp[0].sv_str));
    }
#line 2314 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 65: /* cond_base: col BETWEEN value AND value  */
#line 414 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-4].sv_col), false, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2322 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 66: /* cond_base: col NOT BETWEEN value AND value  */
#line 418 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BetweenExpr>((yyvsp[-5].sv_col), true, (yyvsp[-2].sv_val), (yyvsp[0].sv_val));
    }
#line 2330 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 67: /* cond_base: col IN '(' valueList ')'  */
#line 422 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, (yyvsp[-1].sv_vals));
    }
#line 2338 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 68: /* cond_base: col NOT IN '(' valueList ')'  */
#line 426 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, (yyvsp[-1].sv_vals));
    }
#line 2346 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 69: /* cond_base: col IN '(' dml ')'  */
#line 430 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-4].sv_col), false, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2354 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 70: /* cond_base: col NOT IN '(' dml ')'  */
#line 434 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<InExpr>((yyvsp[-5].sv_col), true, std::vector<std::shared_ptr<Value>>{}, (yyvsp[-1].sv_node));
    }
#line 2362 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 71: /* cond_base: '(' condition ')'  */
#line 438 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[-1].sv_cond);
    }
#line 2370 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 72: /* optWhereClause: %empty  */
#line 445 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2378 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 73: /* optWhereClause: WHERE condition  */
#line 449 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2386 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 74: /* optHaving: %empty  */
#line 456 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = nullptr;
    }
#line 2394 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 75: /* optHaving: HAVING condition  */
#line 460 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cond) = (yyvsp[0].sv_cond);
    }
#line 2402 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 78: /* expr_add_sub: expr_add_sub '+' expr_mul_div  */
#line 476 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_ADD, (yyvsp[0].sv_expr));
    }
#line 2410 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 79: /* expr_add_sub: expr_add_sub '-' expr_mul_div  */
#line 480 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_SUB, (yyvsp[0].sv_expr));
    }
#line 2418 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 81: /* expr_mul_div: expr_mul_div '*' expr_unary  */
#line 488 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MUL, (yyvsp[0].sv_expr));
    }
#line 2426 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 82: /* expr_mul_div: expr_mul_div '/' expr_unary  */
#line 492 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_DIV, (yyvsp[0].sv_expr));
    }
#line 2434 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 83: /* expr_mul_div: expr_mul_div '%' expr_unary  */
#line 496 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>((yyvsp[-2].sv_expr), ARITH_MOD, (yyvsp[0].sv_expr));
    }
#line 2442 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 85: /* expr_unary: '-' expr_unary  */
#line 504 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ArithExpr>(nullptr, ARITH_NEG, (yyvsp[0].sv_expr));
    }
#line 2450 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 86: /* expr_base: value  */
#line 511 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2458 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 87: /* expr_base: col  */
#line 515 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2466 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 88: /* expr_base: aggExpr  */
#line 519 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_agg));
    }
#line 2474 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 89: /* expr_base: CONCAT '(' expr_list ')'  */
#line 523 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<ConcatExpr>((yyvsp[-1].sv_exprs));
    }
#line 2482 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 90: /* expr_base: '(' dml ')'  */
#line 527 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::make_shared<SubqueryExpr>((yyvsp[-1].sv_node));
    }
#line 2490 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 91: /* expr_base: '(' expr ')'  */
#line 531 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_expr) = (yyvsp[-1].sv_expr);
    }
#line 2498 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 92: /* aggType: COUNT  */
#line 541 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_COUNT; }
#line 2504 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 93: /* aggType: SUM  */
#line 542 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_SUM; }
#line 2510 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 94: /* aggType: AVG  */
#line 543 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_AVG; }
#line 2516 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 95: /* aggType: MAX  */
#line 544 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MAX; }
#line 2522 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 96: /* aggType: MIN  */
#line 545 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_agg_type) = AGG_MIN; }
#line 2528 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 97: /* aggExpr: aggType '(' col ')'  */
#line 550 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_agg) = std::make_shared<AggExpr>((yyvsp[-3].sv_agg_type), (yyvsp[-1].sv_col)->col_name);
    }
#line 2536 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 98: /* aggExpr: aggType '(' '*' ')'  */
#line 554 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        if ((yyvsp[-3].sv_agg_type) == AGG_COUNT) {
            (yyval.sv_agg) = std::make_shared<AggExpr>(AGG_COUNT, "", true);
        } else {
            yyerror(&yylloc, "Only COUNT supports * argument");
            YYERROR;
        }
    }
#line 2549 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 99: /* optDistinct: %empty  */
#line 569 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = false; }
#line 2555 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 100: /* optDistinct: DISTINCT  */
#line 570 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_bool) = true; }
#line 2561 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 101: /* selectItems: '*'  */
#line 575 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{};
    }
#line 2569 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 103: /* selectItemList: expr opt_alias  */
#line 583 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[-1].sv_expr)};
    }
#line 2577 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 104: /* selectItemList: selectItemList ',' expr opt_alias  */
#line 587 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[-1].sv_expr));
    }
#line 2585 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 105: /* opt_alias: %empty  */
#line 593 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2591 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 106: /* opt_alias: IDENTIFIER  */
#line 594 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2597 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 107: /* opt_alias: AS IDENTIFIER  */
#line 595 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2603 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 108: /* opt_alias: AS COUNT  */
#line 596 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2609 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 109: /* opt_alias: AS AVG  */
#line 597 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2615 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 110: /* opt_alias: AS SUM  */
#line 598 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2621 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 111: /* opt_alias: AS MAX  */
#line 599 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2627 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 112: /* opt_alias: AS MIN  */
#line 600 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { }
#line 2633 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 113: /* optAliasStr: %empty  */
#line 604 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = ""; }
#line 2639 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 114: /* optAliasStr: IDENTIFIER  */
#line 605 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2645 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 115: /* optAliasStr: AS IDENTIFIER  */
#line 606 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = (yyvsp[0].sv_str); }
#line 2651 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 116: /* optAliasStr: AS COUNT  */
#line 607 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "count"; }
#line 2657 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 117: /* optAliasStr: AS AVG  */
#line 608 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "avg"; }
#line 2663 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 118: /* optAliasStr: AS SUM  */
#line 609 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "sum"; }
#line 2669 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 119: /* optAliasStr: AS MAX  */
#line 610 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "max"; }
#line 2675 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 120: /* optAliasStr: AS MIN  */
#line 611 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                        { (yyval.sv_str) = "min"; }
#line 2681 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 121: /* fromList: tbName optAliasStr  */
#line 616 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[-1].sv_str)};
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2690 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 122: /* fromList: fromList ',' tbName optAliasStr  */
#line 621 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[-1].sv_str));
        if (!(yyvsp[0].sv_str).empty()) (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2699 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 123: /* optJoinList: %empty  */
#line 629 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{};
    }
#line 2707 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 124: /* optJoinList: joinList  */
#line 633 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = (yyvsp[0].sv_joins);
    }
#line 2715 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 125: /* joinList: joinClause  */
#line 640 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join)};
    }
#line 2723 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 126: /* joinList: joinList joinClause  */
#line 644 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_joins).push_back((yyvsp[0].sv_join));
    }
#line 2731 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 127: /* joinType: INNER  */
#line 650 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = INNER_JOIN; }
#line 2737 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 128: /* joinType: LEFT  */
#line 651 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = LEFT_JOIN; }
#line 2743 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 129: /* joinType: RIGHT  */
#line 652 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = RIGHT_JOIN; }
#line 2749 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 130: /* joinType: FULL  */
#line 653 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_int) = FULL_JOIN; }
#line 2755 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 131: /* joinClause: joinType JOIN tbName optAliasStr ON condition  */
#line 658 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), static_cast<JoinType>((yyvsp[-5].sv_int)), (yyvsp[-2].sv_str));
    }
#line 2763 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 132: /* joinClause: JOIN tbName optAliasStr ON condition  */
#line 662 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_cond), INNER_JOIN, (yyvsp[-2].sv_str));
    }
#line 2771 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 133: /* joinClause: joinType JOIN tbName optAliasStr  */
#line 666 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, static_cast<JoinType>((yyvsp[-3].sv_int)), (yyvsp[0].sv_str));
    }
#line 2779 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 134: /* joinClause: JOIN tbName optAliasStr  */
#line 670 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_join) = std::make_shared<JoinExpr>((yyvsp[-1].sv_str), nullptr, INNER_JOIN, (yyvsp[0].sv_str));
    }
#line 2787 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 135: /* optGroupBy: %empty  */
#line 677 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = nullptr;
    }
#line 2795 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 136: /* optGroupBy: GROUP BY colList  */
#line 681 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = std::make_shared<GroupBy>((yyvsp[0].sv_cols));
    }
#line 2803 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 137: /* optLimit: %empty  */
#line 688 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = nullptr;
    }
#line 2811 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 138: /* optLimit: LIMIT VALUE_INT  */
#line 692 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[0].sv_int));
    }
#line 2819 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 139: /* optLimit: LIMIT VALUE_INT OFFSET VALUE_INT  */
#line 696 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_limit) = std::make_shared<LimitClause>((yyvsp[-2].sv_int), (yyvsp[0].sv_int));
    }
#line 2827 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 140: /* col: tbName '.' colName  */
#line 703 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2835 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 141: /* col: colName  */
#line 707 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2843 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 142: /* colList: col  */
#line 714 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2851 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 143: /* colList: colList ',' col  */
#line 718 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2859 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 144: /* op: '='  */
#line 725 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2867 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 145: /* op: '<'  */
#line 729 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2875 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 146: /* op: '>'  */
#line 733 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2883 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 147: /* op: NEQ  */
#line 737 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2891 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 148: /* op: LEQ  */
#line 741 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2899 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 149: /* op: GEQ  */
#line 745 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2907 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 150: /* setClauses: setClause  */
#line 752 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2915 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 151: /* setClauses: setClauses ',' setClause  */
#line 756 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2923 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 152: /* setClause: colName '=' value  */
#line 763 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2931 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 153: /* opt_order_clause: ORDER BY order_clause  */
#line 770 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby);
    }
#line 2939 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 154: /* opt_order_clause: %empty  */
#line 773 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                    { /* ignore*/ }
#line 2945 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 155: /* order_clause: col opt_asc_desc  */
#line 778 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2953 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 156: /* opt_asc_desc: ASC  */
#line 784 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2959 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 157: /* opt_asc_desc: DESC  */
#line 785 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DESC; }
#line 2965 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 158: /* opt_asc_desc: %empty  */
#line 786 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 2971 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 159: /* set_knob_type: ENABLE_NESTLOOP  */
#line 790 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2977 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 160: /* set_knob_type: ENABLE_SORTMERGE  */
#line 791 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2983 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 161: /* expr_list: expr  */
#line 796 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs) = std::vector<std::shared_ptr<Expr>>{(yyvsp[0].sv_expr)};
    }
#line 2991 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;

  case 162: /* expr_list: expr_list ',' expr  */
#line 800 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"
    {
        (yyval.sv_exprs).push_back((yyvsp[0].sv_expr));
    }
#line 2999 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"
    break;


#line 3003 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.tab.cpp"

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

#line 808 "/home/obuser/Rubase/db2025/rmdb/src/parser/yacc.y"

