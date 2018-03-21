%option c++
%option header-file="glsllexer.h"
%option outfile="glsllexer.cpp"
%option yylineno

%{
	#include "QsciLexerGlsl.h"
%}


SPACE       [ \t]+

RETURN      [\n\r]+

PREPROCESSOR #.*

ZERO        0
NONZERO     [1-9]
DIGIT       [0-9]
OCTDIGIT    [0-7]
HEXDIGIT    [0-9a-fA-F]
INTSUFFIX   [uU]

DECCONST    {NONZERO}{DIGIT}*{INTSUFFIX}?
OCTCONST    {ZERO}{OCTDIGIT}*{INTSUFFIX}?
HEXCONST    {ZERO}[xX]{HEXDIGIT}*{INTSUFFIX}?

INTEGER     {DECCONST}|{OCTCONST}|{HEXCONST}

DIGITSEQ    {DIGIT}+
FRACCONST   ({DIGITSEQ}\.{DIGITSEQ}+)|({DIGITSEQ}+[\.])|([\.]{DIGITSEQ}+)
SIGN        [+-]
EXPPART     [eE]{SIGN}?{DIGIT}+
FLOATSUFFIX [lL]?[fF]

FLOAT       {FRACCONST}{EXPPART}?{FLOATSUFFIX}?|{DIGITSEQ}{EXPPART}{FLOATSUFFIX}?

BOOL        true|false

NONDIGIT    [_a-zA-Z]

IDENTIFIER  {NONDIGIT}({NONDIGIT}|{DIGIT})*

NUMOPER     [\+\-\*\/\%]|\+\+|\-\-WW
BITOPER     [\^\|\&]|<<|>>
LOGIOPER    [\>\<\!]|\>\=|\<\=|&&|\|\||\=\=|\!\=
COMPAREOPER [?:]
STRUCTOPER  \.|->
OTHROPER    [\(\)\[\]\{\},;]
ASSIGNOPER  ({NUMOPER}|{BITOPER})?\=

OPERATOR    {NUMOPER}|{BITOPER}|{LOGIOPER}|{COMPAREOPER}|{STRUCTOPER}|{OTHROPER}|{ASSIGNOPER}


%%

volatile |
restrict |
readonly |
writeonly |
atomic_uint |
layout |
centroid |
flat |
smooth |
noperspective |
break |
continue |
do |
for |
while |
switch |
case |
default |
if |
else |
subroutine |
invariant |
precise |
discard |
return |
struct |
lowp |
mediump |
highp |
precision
attribute |
const |
uniform |
varying |
buffer |
shared |
coherent |
in |
out |
inout |
patch |
sample                                      { return QsciLexerGLSL::StyleType::KEYWORD; }

float |
double |
[u]?int |
void |
bool |
[d]?mat[234] |
[d]?mat[234]x[234] |
[biuvd]?vec[234] |
[iu]?sampler([123]D|2DMS|Cube)Array |
[iu]?sampler([123]D|2DMS|2DRect|Cube|Buffer) |
sampler(1D|2D|Cube)ArrayShadow |
sampler(1D|2D|2DRect|Cube)Shadow |
[iu]?image([12]D|2DMS|Cube)Array |
[iu]?image([123]D|2DRect|2DMS|Cube|Buffer)  { return QsciLexerGLSL::StyleType::DATATYPE; }

radians |
degrees |
sin |
cos |
asin |
acos |
pow |
exp |
log |
exp2 |
log2 |
sqrt |
inversesqrt |
abs |
sign |
floor |
trunc |
round |
ceil |
mod |
min |
max |
clamp |
length |
dot |
normalize                                   { return QsciLexerGLSL::StyleType::FUNCTION; }

{INTEGER} |
{FLOAT} |
{BOOL}                                      { return QsciLexerGLSL::StyleType::NUMBER; }
{IDENTIFIER}                                { return QsciLexerGLSL::StyleType::DEFAULT; }
{OPERATOR}                                  { return QsciLexerGLSL::StyleType::OPERATOR; }
{PREPROCESSOR}                              { return QsciLexerGLSL::StyleType::PREPROCESSOR; }
{SPACE} |
{RETURN}                                    { return QsciLexerGLSL::StyleType::WHITESPACE; }
.                                           { return QsciLexerGLSL::StyleType::ILLEGAL; }


%%

int yyFlexLexer::yywrap()   { return 1;}
