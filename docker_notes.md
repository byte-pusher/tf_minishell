

docker build -t memory-test .

docker run -ti -v $(PWD):/tf_minishell memory-test bash -c "cd /tf_minishell/; make re; valgrind --leak-check=full ./minishell; make fclean"

docker run -ti -v $(PWD):/tf_minishell memory-test bash -c "cd /tf_minishell/; make re; valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp ./minishell; make fclean"