### TODOS

- valgrind laufen lassen

- norminette

## redir

- woco='wc -l'
		-> cat Makefile | $woco

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
