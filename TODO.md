### TODOS

- valgrind laufen lassen

- error handling
	-> what happens with unclosed quotes?

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
	-> "       ls" -> soll nicht funktionieren
	-> echo "     jo" -> spaces müssen geprintet werden
	-> oder cat "        out" -> soll auch funktionieren
	-> "l"s -> ich würde das nicht behandeln

