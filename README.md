# XML PARSER
Tool to parse XML

# Grammar
## NON-TERMINAL SYMBOLS
N = {<, >, !, {, }, \s,\t, \n, \r, “, ’, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
S, T, U, V, W, X, Y, Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w,x,y,
z, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, [, ], (, ), @, #, $, %, ^, &, *, _, -, +, =, ~, `, ?, ,, ., :, ;, \, /, |, }

## TERMINAL SYMBOLS 
T = {STMT, TAG, DOCUMENT_TAG, PAIREDTAG, UNPAIREDTAG, OPENTAG, CLOSINGTAG,
OPENTAG, VALUE, STRING, OBJECT, CHARACTERSWITHOUTQUOTES, CHARACTERSWITHOUTSINGLEQUOTES, 
CHARACTER, WHITESPACE, NUMBER, LETTER, LOWERCASE, UPPERCASE, SYMBOL, QUOTES, SINGLEQUOTES,
ESCAPEDQUOTES, ESCAPEDSINGLEQUOTES, NAME, CHARACTERSWITHOUTWHITESPACE, ARRAYOPENBRACKET, 
 ARRAYCLOSEBRACKET, PRIMITIVE, ARRAYELEMENT, ARRAY, PAIRVALUE, OBJECTPAIR, OBJECTELEMENT, 
 OBJECTOPENBRACKET, OBJECTCLOSEBRACKET, OBJECT, COMMENTTAG, OPENBRACKET, CLOSEBRACKET, 
 BODY, SELFCLOSINGTAG, STARTTAG, CLOSETAG, XMLTAG, PROP, BOOLEANPROP, STRINGPROP, OBJECTPROP
 }

 ## START SYMBOL
 S = {STMT}

 ## Production Rules
 ```
 P={
    // A document tag with one or more tags
    //Or just a tag
	STMT = DOCUMENT_TAG + TAG | TAG,

    //A tag can be either paired, or unpaired or one or more tags
    TAG = PAIREDTAG | UNPAIREDTAG | TAG + TAG

    // TAGS can be in pairs with or without a value
    PAIREDTAG = OPENTAG + CLOSINGTAG | OPENTAG + VALUE + CLOSINGTAG,

    // Some tags can be unpaired
    UNPAIREDTAG = SELFCLOSINGTAG | XMLTAG | COMMENTTAG,

    //VALUES BETWEEN TAGS can be strings, objects, or other tags
    VALUE = STRING | OBJECT | TAG

    //A string consists of quotes surrounding one or more characters
    STRING = " + CHARACTERSWIHOUTQUOTES + " | ' + CHARACTERSWIHOUTSINGLEQUOTES + ' 
    
    CHARACTERSWITHOUTQUOTES = CHARACTER | SINGLEQUOTES | ESCAPEDQUOTES | ESCAPEDSINGLEQUOTES | CHARACTERSWITHOUTQUOTES + CHARACTERSWITHOUTQUOTES
    
    CHARACTERSWITHOUTSINGLEQUOTES = CHARACTER | QUOTES | ESCAPEDQUOTES | ESCAPEDSINGLEQUOTES | CHARACTERSWITHOUTSINGLEQUOTES + CHARACTERSWITHOUTSINGLEQUOTES

    CHARACTERSWITHOUTWHITESPACE = NUMBER | LETTER | SYMBOL | CHARACTERSWITHOUTWHITESPACE + CHARACTERSWITHOUTWHITESPACE

    //Characters can be any non-terminal symbol
    CHARACTER = WHITESPACE | NUMBER | LETTER | SYMBOL | CHARACTER + CHARACTER
    
    WHITESPACE = \s | \t | \n | \r | WHITESPACE + WHITESPACE

    NUMBER = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | NUMBER + NUMBER

    LETTER = LOWERCASE | UPPERCASE | LETTER + LETTER

    LOWERCASE = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p
    | q | r | s | t | u | v | w | x | y | z 

    UPPERCASE = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P
    | Q | R | S | T | U | V | W | X | Y | Z

    SYMBOL = ! | @ | # | $ | % | ^ | & | * | ( | ) | / | \ | + | - | ` | ~ |
    ? | > | < | , | . | : | ; | { | } | [ | ] | | | 

    QUOTES = ",
    SINGLEQUOTES = ',
    ESCAPEDQUOTES = \" ,
    ESCAPEDSINGLEQUOTES = \',

    // variable1, a, var, not 1variable
    NAME = LETTER | LETTER + CHARACTERSWITHOUTWHITESPACE
    ARRAYOPENBRACKET = [|[ +  WHITESPACE
    ARRAYCLOSEBRACKET = ] | WHITESPACE + ]
    PRIMITIVE = OBJECT | STRING | NUMBER | NAME | ARRAY
    ARRAYELEMENT = PRIMITIVE | PRIMITIVE + WHITESPACE | PRIMITIVE + , + WHITESPACE +  PRIMITIVE
    ARRAY = ARRAYOPENBRACKET + ARRAYELEMENT + ARRAYCLOSEBRACKET
    
    PAIRVALUE = OBJECT | STRING | NUMBER | NAME | ARRAY
    OBJECTPAIR = NAME + WHITESPACE + : + WHITESPACE + PAIRVALUE | 
    NAME  + : + WHITESPACE + PAIRVALUE | NAME + WHITESPACE + :  + PAIRVALUE|
    NAME  + :  + PAIRVALUE
    
    OBJECTELEMENT = OBJECTPAIR | NAME | STRING | OBJECTELEMENT + , + WHITESPACE + OBJECTELEMENT | OBJECTELEMENT + WHITESPACE + , + WHITESPACE + OBJECTELEMENT
    OBJECTOPENBRACKET = { | { + WHITESPACE
    OBJECTCLOSEBRACKET = WHITESPACE + } | }
    OBJECT = OBJECTOPENBRACKET +  OBJECTELEMENT + OBJECTCLOSEBRACKET


    COMMENTTAG =  < + ! + - + - + CHARACTER + - + - + >
    OPENBRACKET = < | < + WHITESPACE
    CLOSEBRACKET = > | WHITESPACE > 
    BODY = NAME | NAME + WHITESPACE + PROP
    SELFCLOSINGTAG = OPENBRACKET + BODY + / + CLOSEBRACKET | OPENBRACKET + BODY + WHITESPACE / + CLOSEBRACKET 
    STARTTAG = OPENBRACKET + BODY + CLOSEBRACKET
    CLOSETAG = OPENBRACKET + BODY + / + CLOSEBRACKET | OPENBRACKET + BODY + WHITESPACE / + CLOSEBRACKET 
    DOCUMENT_TAG = OPENBRACKET + ! + BODY + CLOSEBRACKET
    XMLTAG = OPENBRACKET + ? + BODY + CLOSEBRACKET

    PROP = BOOLEANPROP | STRINGPROP | OBJECTPROP | PROP + PROP
    BOOLEANPROP = NAME | NAME + WHITESPACE
    STRINGPROP = NAME + = + STRING | NAME + WHITESPACE + = + STRING |
     NAME  + = + WHITESPACE + STRING |
      NAME  + WHITESPACE + = + WHITESPACE + STRING | STRINGPROP + WHITESPACE
    OBJECTPROP = OBJECT | OBJECT + WHITESPACE
}
```

## Logic
Character (Token) -> Component (one or more tokens) -> Primitive, Element