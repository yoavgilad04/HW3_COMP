%{

/* Declarations section */
#include <stdio.h>
#include "source.hpp"
#include "parser.tab.hpp"
%}

%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
escape          ([\\])
quote           ([\x22])
newline         ([\x0a])
whitespace		([\r\n\t ])
instring       ([\x00-\x09\x0b-\x0c\x0e-\x21\x23-\x5b\x5d-\x7f])
incomment      ([^\x0a\x0d])

%x STR

%%
{quote}                                 BEGIN(STR);
<STR>{quote}                            BEGIN(INITIAL); return STRING;
<STR>({instring}|\\[nrt"\\])+           ;
<STR>.                                  output::errorLex(yylineno); exit(0);
{whitespace}				            ;
void                                    return VOID;
int                                     return INT;
byte                                    return BYTE;
bool                                    return BOOL;
b                                       return B;
and                                     return AND;
or                                      return OR;
not                                     return NOT;
true                                    return TRUE;
false                                   return FALSE;
return                                  return RETURN;
else                                    return ELSE;
while                                   return WHILE;
if                                      return IF;
break                                   return BREAK;
continue                                return CONTINUE;
;                                       return SC;
,                                       return COMMA;
\(                                      return  LPAREN;
\)                                      return  RPAREN;
\{                                      return  LBRACE;
\}                                      return  RBRACE;
\=                                      return ASSIGN;
\<|\>|\<\=|\>\=                         return RELOP;
\=\=|\!\=                               return EQLOP;
\+|\-                                   return ADD;
\*|\/                                   return MUL;
override                                return OVERRIDE;
0|[1-9]{digit}*                         yylval=new Node(yytext); return NUM;
{letter}({letter}|{digit})*             return ID;
\/\/{incomment}*[\r|\n|\r\n]?           ;
.                                       output::errorLex(yylineno); exit(0);

%%