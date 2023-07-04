/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/04 15:54:49 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fuck the dquotes that allow multiple variables inside of them

int	valid_varname(char c)
{
	// str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_' || str[i + j] == '\''
	return (c && (ft_isalnum(c) || c == '_' || c == '\''));
}

int check_dollar(char *str)
{
	if (!str)
		return (-1);
	if (!*str)
		return (0);
	if (*str == '$')
		return (1);
	return (check_dollar(str + 1));
}

char	*expand_var(char *str)
{
	char *expanded;
	char *temp;
	int	var_len;
	int	str_len;
	int	i;
	int	j;

//make cpy of the variable
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	j = 1;
	while (valid_varname(str[i + j]))
		j++;
	temp = ft_strndup(&str[i], j);
	if (!temp)
		return (NULL);//handle error
	str_len = ft_strlen(str) - j;
	i = 0;
	while (g_data.envir[i])
	{
		j = 0;
		while (g_data.envir[i][j] != '=' && g_data.envir[i][j])
			j++;
		if (!ft_strncmp(g_data.envir[i], temp + 1, j))
			break ;
		i++;
	}
	if (!g_data.envir[i])
		return (NULL);//we failed to find var
	j = 0;
	while (g_data.envir[i][j] && g_data.envir[i][j] != '=')
		j++;
	if (g_data.envir[i][j])
		j++;
	else
		return (NULL);
	var_len = ft_strlen(&g_data.envir[i][j]);
	if (*str == '$' && ft_strlen(str) == var_len)
		return (ft_strdup(&g_data.envir[i][j]));
	if (g_data.envir[i][j] == '\'')
		var_len -= 2;
	expanded = ft_calloc(1, str_len + var_len + 1);
	if (!expanded)
		return (NULL);//handle error
	free (temp);
	temp = &g_data.envir[i][j];
	i = 0;
	j = 0;
	while (str[i] != '$' && str[i])
	{
		expanded[i] = str[i];
		i++;
	}
	str += i;
	if (*str)
		str++;
	while (valid_varname(*str))
		str++;
	while (temp[j])
	{
		expanded[i] = temp[j];
		i++;
		j++;
	}
	j = i;
	while (*str)
	{
		expanded[j] = *str;
		j++;
		str++;
	}
	return (expanded);
}

char *check_var_logic(char **str)
{
	char *temp;

	if (!check_dollar(*str))
		return (*str);
	temp = expand_var(*str);
	free (*str);
	*str = temp;
	return (check_var_logic(str));
}

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_command *command;
	char *input;

	char *test = ft_strdup("$madon $madon $madon");
	copy_env(envp);
	printf("%s\n", test);
	test = check_var_logic(&test);
	printf("%s\n", test);
	while (1)
	{
		command = NULL;
		// token = NULL;
		input = readline(">");
		if (!count_quotes(input))
			token = tokenizer(input);
		if (!check_tokens(token))
		{
			// print_tokens(token);
			command = convert_tokens(token);
			check_list(command);
			// build_pipes(command);
			//handle_commands(command);
			print_commands(command);
			// free_tokens(token);
			// printf("freed tokens\n");
			token = NULL;
		}
		// free_commands(command);
		// printf("freed commands\n");
        // execve(get_path(*command->cmd),command->cmd, g_data.envir);
		if (input)
			free(input);
		for (int i = 0; g_data.envir[i]; i++)
		{
			printf("%s\n", g_data.envir[i]);
		}
	}
	return (0);
}

// void	build_pipes(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	// handle_pipes(command);
// 	build_pipes(command->next);
// }

// void	build_redirections(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	if (!*(command->redir))
// 		return ;
// 	handle_redirections(command);
// 	// if (command->next)
// 	// 	build_redirecitons(command->next);
// }

// // command->next
// // *command->redir;
// // execve(get_path(*command->cmd), (command->cmd + 1), g_data.envir);

// void	handle_commands(t_command *command)
// {
// 	pid_t pid;

// 	if (!command)
// 		return ;
// 	pid = fork();
// 	if (pid < 0)
// 		return ;
// 	if (pid == 0)
// 	{
// 		build_redirections(command);
// 		// run_command(command);
// 	}
// 	else
// 		handle_commands(command->next);
// }
