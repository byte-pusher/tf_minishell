### Including readline:
via brew

- brew install readline

Get current path:
- brew --prefix readline

Get current version:
- brew info readline

Add compilationflags to Makefile:
- LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
- CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

add prototypes to header:
- void 	rl_replace_line(const char *text, int clear_undo);
- extern void rl_clear_history (void);


------------------------------------------------------------
Info:
Known problems for readline on MacOS Catalina.
GNU readline different to readline lib on Mac.
Specific path has to named to ensure correct interpretation if different readline versions are present.


Docs:

Function: void rl_replace_line (const char *text, int clear_undo)

    Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. 


Function: int rl_on_new_line (void)

    Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 

Function: void rl_redisplay (void)

    Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. 