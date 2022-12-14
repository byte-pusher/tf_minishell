### TODOS

- valgrind laufen lassen

- norminette

- woco='wc -l'
		-> cat Makefile | $woco

## ray
- STRG+\ wenn etwas schon eingegeben soll quiten
- nach cat STRG+C soll new prompt anezeigen

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
