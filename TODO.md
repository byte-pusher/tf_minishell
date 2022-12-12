### TODOS

- valgrind laufen lassen

- norminette
	-> comments löschen
	-> #define Ding klären

- exit after syntax error and cmd not found is returning 0. Should return the error nbr

- fix error msgs for imputs:
	- alles was nicht /bin (. , /)
	- bei ./ printen "is a directory"
		-> (beim executor checken falls execve == -1 und strcp nicht /bin)

## ray
~~- -> $ alone should not expand~~
- SEGFAULT expansion: deletion of several non existing vars> e.g. echo $ghj $hj $ghj $ghj $ghj $Ghj
- further error messages for builtins?
- rewrite expansion functions
- protection for missing environment in builtins






## evtl:
- redir
	-> echo hey man >out | echo jojo > out (überschreibt die file falsch)
	  -> if the overwriting is shorter i get a mix of both files
	  -> only happens If I have a pipe in between bzw If in the same cmd_line
	  -> weird stuff:
	  	-> in bash this happens
		echo hallo >out | <out wc -l >out2 | echo jo >out => cat out => jo\nlo
			--> sometimes jo\nlo, but sometimes also only jo
uiltin_protection
