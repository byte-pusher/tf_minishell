### TODOS

- valgrind laufen lassen

- norminette

## redir

- | alleine und | | (falsh gefreed)
- /bin/ls asdads
	-> exit code should be 1 und nicht 2

- teshno: syntax error near unexpected token `newline'
==2873== Invalid free() / delete / delete[] / realloc()
==2873==    at 0x4839A0C: free (vg_replace_malloc.c:540)
==2873==    by 0x40424C: ft_err_msg (in /tst/minishell)
==2873==    by 0x401D5F: ft_check_quotes (in /tst/minishell)
==2873==    by 0x40146C: ft_init_input (in /tst/minishell)
==2873==    by 0x4014BF: ft_init_teshno (in /tst/minishell)
==2873==    by 0x4012F3: main (in /tst/minishell)
==2873==  Address 0x40903e is in a r-- mapped file /tst/minishell segment

- woco='wc -l'
		-> cat Makefile | $woco

## ray
- STRG+\ wenn etwas schon eingegeben soll quiten
- nach cat STRG+C soll new prompt anezeigen
- export ohne arg
- export ray2=jo

## evtl:
- redir
	-> echo hey man >out | echo jojo > out (überschreibt die file falsch)
	  -> if the overwriting is shorter i get a mix of both files
	  -> only happens If I have a pipe in between bzw If in the same cmd_line
	  -> weird stuff:
	  	-> in bash this happens
		echo hallo >out | <out wc -l >out2 | echo jo >out => cat out => jo\nlo
			--> sometimes jo\nlo, but sometimes also only jo
