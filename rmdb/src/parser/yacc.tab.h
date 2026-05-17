/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_OBUSER_RUBASE_DB2025_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED
# define YY_YY_HOME_OBUSER_RUBASE_DB2025_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED
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
    SHOW = 258,                    /* SHOW  */
    TABLES = 259,                  /* TABLES  */
    CREATE = 260,                  /* CREATE  */
    TABLE = 261,                   /* TABLE  */
    DROP = 262,                    /* DROP  */
    DESC = 263,                    /* DESC  */
    INSERT = 264,                  /* INSERT  */
    INTO = 265,                    /* INTO  */
    VALUES = 266,                  /* VALUES  */
    DELETE = 267,                  /* DELETE  */
    FROM = 268,                    /* FROM  */
    ASC = 269,                     /* ASC  */
    ORDER = 270,                   /* ORDER  */
    BY = 271,                      /* BY  */
    WHERE = 272,                   /* WHERE  */
    UPDATE = 273,                  /* UPDATE  */
    SET = 274,                     /* SET  */
    SELECT = 275,                  /* SELECT  */
    INT = 276,                     /* INT  */
    CHAR = 277,                    /* CHAR  */
    FLOAT = 278,                   /* FLOAT  */
    INDEX = 279,                   /* INDEX  */
    AND = 280,                     /* AND  */
    JOIN = 281,                    /* JOIN  */
    EXIT = 282,                    /* EXIT  */
    HELP = 283,                    /* HELP  */
    DEFAULT = 284,                 /* DEFAULT  */
    PRIMARY = 285,                 /* PRIMARY  */
    KEY = 286,                     /* KEY  */
    AUTO_INCREMENT = 287,          /* AUTO_INCREMENT  */
    AS = 288,                      /* AS  */
    CONCAT = 289,                  /* CONCAT  */
    TXN_BEGIN = 290,               /* TXN_BEGIN  */
    TXN_COMMIT = 291,              /* TXN_COMMIT  */
    TXN_ABORT = 292,               /* TXN_ABORT  */
    TXN_ROLLBACK = 293,            /* TXN_ROLLBACK  */
    ENABLE_NESTLOOP = 294,         /* ENABLE_NESTLOOP  */
    ENABLE_SORTMERGE = 295,        /* ENABLE_SORTMERGE  */
    AVG = 296,                     /* AVG  */
    BETWEEN = 297,                 /* BETWEEN  */
    COUNT = 298,                   /* COUNT  */
    DISTINCT = 299,                /* DISTINCT  */
    FULL = 300,                    /* FULL  */
    GROUP = 301,                   /* GROUP  */
    HAVING = 302,                  /* HAVING  */
    IN = 303,                      /* IN  */
    INNER = 304,                   /* INNER  */
    IS = 305,                      /* IS  */
    LEFT = 306,                    /* LEFT  */
    LIKE = 307,                    /* LIKE  */
    LIMIT = 308,                   /* LIMIT  */
    MAX = 309,                     /* MAX  */
    MIN = 310,                     /* MIN  */
    NOT = 311,                     /* NOT  */
    OFFSET = 312,                  /* OFFSET  */
    ON = 313,                      /* ON  */
    OR = 314,                      /* OR  */
    RIGHT = 315,                   /* RIGHT  */
    SUM = 316,                     /* SUM  */
    LEQ = 317,                     /* LEQ  */
    NEQ = 318,                     /* NEQ  */
    GEQ = 319,                     /* GEQ  */
    T_EOF = 320,                   /* T_EOF  */
    IDENTIFIER = 321,              /* IDENTIFIER  */
    VALUE_STRING = 322,            /* VALUE_STRING  */
    VALUE_INT = 323,               /* VALUE_INT  */
    VALUE_FLOAT = 324,             /* VALUE_FLOAT  */
    VALUE_BOOL = 325,              /* VALUE_BOOL  */
    VALUE_NULL = 326               /* VALUE_NULL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void);


#endif /* !YY_YY_HOME_OBUSER_RUBASE_DB2025_RMDB_SRC_PARSER_YACC_TAB_H_INCLUDED  */
