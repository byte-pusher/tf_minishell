### TODOS

- valgrind laufen lassen

- check for open files

- error handling
	-> unclosed quotes (rays fct über slack)

- norminette
	-> comments löschen
	-> #define Ding klären

- redir
	-> echo hey man >out | echo jojo > out (überschreibt die file falsch)
	  -> if the overwriting is shorter i get a mix of both files
	  -> only happens If I have a pipe in between bzw If in the same cmd_line
	  -> weird stuff:
	  	-> in bash this happens
		echo hallo >out | <out wc -l >out2 | echo jo >out => cat out => jo\nlo
			--> sometimes jo\nlo, but sometimes also only jo
			--> so maybe I dont need to handle this


## ray
~~- -> $ alone should not expand~~
- SEGFAULT expansion: deletion of several non existing vars> e.g. echo $ghj $hj $ghj $ghj $ghj $Ghj
- further error messages for builtins?
- rewrite expansion functions
- protection for missing environment in builtins