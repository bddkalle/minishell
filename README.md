*This project has been created as part of the 42 curriculum by bddkalle.*

# Minishell — simplified POSIX-style shell implementation

## Description

Minishell is a small, simplified shell implementation aiming to reproduce the behavior of a UNIX shell interpreter as realistically as possible. The project covers tokenizing, parsing, pipelines (pipes), redirections (including heredoc), builtin commands, environment handling and basic signal management. Minishell was developed as part of the 42 curriculum and is intended to provide deep, hands-on understanding of process control, file descriptors, signals and shell parsing.

## Features

- Basic Bash-compatible input parsing and syntax.
- Pipes: `cmd1 | cmd2 | cmd3`.
- Redirections:
  - Output: `>` and `>>`
  - Input: `<`
  - Heredoc: `<<`
- Environment variable expansion using `$VAR`.
- Builtins (executed without forking): `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`.
- Signal handling comparable to interactive Bash (`SIGINT`/Ctrl-C behavior, ignoring `SIGQUIT` in interactive mode, etc.).
- Error handling for syntax errors, command-not-found, access/permission errors.
- Command execution pipeline implemented with `fork`, `execve`, `dup2`, and `pipe`.

## Instructions

> **IMPORTANT:** This project depends on `libft` as a Git submodule. Clone with submodules to ensure `libft` is present.

1. Clone the repository (with submodules):

```bash
git clone --recurse-submodules https://github.com/bddkalle/minishell.git
cd minishell
```

If you already cloned without submodules, fetch them afterwards:

```bash
git submodule update --init --recursive
```

2. Compile the project:

```bash
make
```

This produces the `minishell` binary in the repository root.

3. Run the shell:

```bash
./minishell
```

Example commands to try inside the shell:

```bash
echo "Hello World"
ls -l | grep minishell
export TEST=42
echo $TEST
cat < input.txt | grep foo > out.txt
```

## Architecture (short overview)

```
minishell/
├── src/
│   ├── lexer/       # Tokenizing input → tokens
│   ├── parser/      # Build AST, check syntax
│   ├── exec/        # Pipelines, redirections, FD management
│   ├── builtins/    # cd, echo, export, ...
│   ├── env/         # Environment management
│   └── signals/     # Signal handlers (interactive behavior)
├── libft/           # Submodule – utility functions
├── includes/        # Headers (data structures, APIs)
├── Makefile
└── minishell.c
```

### Core concepts

- **Tokenizer:** Splits the input string into meaningful tokens (words, pipes, redirections, quotes).
- **Parser / AST:** Builds an internal representation of the command chain, validates syntax and prepares execution structures.
- **Executor:** Constructs the pipeline, creates child processes, duplicates file descriptors (`dup2`), opens redirections and invokes `execve()`.
- **Builtins without fork:** Certain builtins must run in the parent process so they can change the environment (e.g. `cd`, `export`).
- **Signals:** Adjusted behavior for interactive mode to match common shell expectations.

## Tests & debugging

- Build a debug binary with additional logging:

```bash
make debug
./minishell
```

- Memory leak checks on macOS:

```bash
leaks --atExit -- ./minishell
```

- Memory leak checks on Linux (e.g. WSL):

```bash
valgrind --leak-check=full ./minishell
```

- For behavioral comparison, test against Bash for various use cases.

## Requirements from the original 42 project (summary)

- Do not use `system()`.
- Correct handling of signals (`SIGINT`, `SIGQUIT`).
- Correct exit statuses.
- Proper handling of single and double quotes.
- Correct pipe handling.
- Correct redirection handling (>, >>, <, <<).
- Implement builtins and `$?` expansion.
- Leak-free implementation.

## Resources

Classic references and documentation useful for this project:

- POSIX and Shell specifications (man pages: `sh`, `bash`, `execve(2)`, `dup2(2)`, `pipe(2)`).
- The GNU Bash Reference Manual — for expected interactive behavior and conventions.
- `Advanced Programming in the UNIX Environment` (Stevens) — chapters on processes and I/O.
- Valgrind documentation — for memory leak detection.
- Tutorials and articles on shell parsing, tokenization and implementing toy shells.

### AI usage disclosure

- This README was translated and edited using an AI assistant to produce a clear English version and to ensure the README meets the 42 README requirements. The AI was used only for the README text (translation, restructuring, and wording). **No project source code was generated or modified by AI** — the implementation and logic remain the author's work.

## License

This project follows the licensing terms of the 42 curriculum. Optionally, an open-source license (e.g. MIT) may be added by the author.

## Author

Felix Steinmann — GitHub: https://github.com/bddkalle

