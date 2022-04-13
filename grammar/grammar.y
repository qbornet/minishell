/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */


%token  WORD
%token  ASSIGNMENT_WORD
%token  NEWLINE


/* The following are the operators mentioned above. */


%token  AND_IF    OR_IF
/*      '&&'      '||' */


%token  DLESS  DGREAT
/*      '<<'   '>>' */

/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */


%start  complete_command
%%
complete_command : and_or
				 ;
and_or           :               pipeline
                 | and_or AND_IF pipeline
                 | and_or OR_IF  pipeline
                 ;
pipeline         :              command
                 | pipeline '|' command
                 ;
command          : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
				 | subshell redirect_list
                 ;
subshell         : '(' compound_list ')'
                 ;
compound_list    :               and_or
                 | compound_list and_or
                 ;
cmd_name         : WORD                   /* Apply rule 7a */
                 ;
cmd_word         : WORD                   /* Apply rule 7b */
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
io_redirect      : io_file
                 | io_here
                 ;
io_file          : '<'       filename
                 | '>'       filename
                 | DGREAT    filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 ;
here_end         : WORD                      /* Apply rule 3 */
                 ;
