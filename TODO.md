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

- export
	-> create export list
	-> handle VAR with no value or only with '=' (should be saved only in the export list)
		-> otherwise in both lists

- quotes
	-> "l"s -> ich würde das nicht behandeln
		-> wenn dann schauen ob is_space danach. wenn ja, quasi ein flag erstellen
		-> wenn flag == true dann strjoin

- expander
	bash-3.2$ << "end" cat
> "$USER"
> end
"$USER"
	bash-3.2$ << end cat
> $USER
> end
gjupy
