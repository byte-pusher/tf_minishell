### TODOS

- valgrind laufen lassen

- norminette

- export 
	- export=42
	- export ''=''
	- export ""=""
	- export ''=''
	- export ""=""
	- export =============123
	- unset ""
	- unset =
	- unset "="
	- unset ""=
	- unset =""

## redir

-   > 'o'ut

- correction
	- echo """"''""''""
	- echo ""$PWD""
	- echo ''$PWD''
	- echo $USE"R"$HOME

- woco='wc -l'
		-> cat Makefile | $woco

- cd -
	-> invalid read/write size etc

- changed bis jetzt
	- to is_cmd_or quotes included FILE_NAME

## ray
~~- add path protections for all getcwd functions~~
- add dir creaion in makefile
~~- add2nd signal handler for in between readline, to silence~~

## evtl:
- redir
	-> echo hey man >out | echo jojo > out (überschreibt die file falsch)
	  -> if the overwriting is shorter i get a mix of both files
	  -> only happens If I have a pipe in between bzw If in the same cmd_line
	  -> weird stuff:
	  	-> in bash this happens
		echo hallo >out | <out wc -l >out2 | echo jo >out => cat out => jo\nlo
			--> sometimes jo\nlo, but sometimes also only jo



## Signal behaviour:
### bash:
empty promt:
- Ctrl+C  -> new bash promt
- Ctrl+D  -> exit shell

text in promt:
- Ctrl+C  -> new bash promt
- Ctrl+D  -> nothing

heredoc: 
- Ctrl+C  -> new bash promt
- Ctrl+D  -> new bash promt on last >heredoc line

shell in shell:
- Ctrl+C  -> new bash promt in subshell
- Ctrl+D  -> exit subshell


### teshno diff
heredoc: 
- Ctrl+C  -> new line with ^C
- Ctrl+D  -> new bash promt in new line

shell in shell:
- Ctrl+C  -> new bash promt in subshell
- Ctrl+D  -> exit subshell
