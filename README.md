# Minishell

Minishell is a shell implementation project developed as part of the curriculum at the **42** programming school. It aims to create a simple yet functional shell with various features and built-in commands.

## Features

The Minishell project includes the following features:

1. **Prompt**: Minishell displays a prompt to the user when waiting for a new command.
2. **Command History**: Minishell maintains a working history of previously executed commands.
3. **Executable Search**: The shell searches for and launches the appropriate executable based on the PATH variable or using a relative or absolute path.
4. **Quoting**: Minishell does not interpret unclosed quotes or special characters that are not required by the subject, such as backslash (\) or semicolon (;). It handles single quotes ('), preventing the shell from interpreting metacharacters in the quoted sequence.
5. **Double Quotes**: Minishell handles double quotes (") by preventing the shell from interpreting metacharacters in the quoted sequence except for the dollar sign ($).
6. **Redirections**: Minishell implements redirections:
   - `<` redirects input.
   - `>` redirects output.
   - `<<` reads input until a line containing the specified delimiter is seen (does not update the history).
   - `>>` redirects output in append mode.
7. **Pipes**: Minishell implements pipes (|) to connect the output of each command in the pipeline to the input of the next command via a pipe.
8. **Environment Variables**: Minishell handles environment variables ($ followed by a sequence of characters) and expands them to their corresponding values.
9. **$?**: Minishell handles `$?`, which expands to the exit status of the most recently executed foreground pipeline.
10. **Signal Handling**: Minishell handles the following signals, behaving similar to bash:
    - `ctrl-C`: Displays a new prompt on a new line.
    - `ctrl-D`: Exits the shell.
    - `ctrl-\`: Does nothing.
11. **Built-in Commands**: Minishell implements the following built-in commands:
    - `echo` with the option `-n`.
    - `cd` with only a relative or absolute path.
    - `pwd` with no options.
    - `export` with no options.
    - `unset` with no options.
    - `env` with no options or arguments.
    - `exit` with no options.
