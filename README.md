# Minishell

Eine eigene, vereinfachte Shell-Implementation nach POSIX-Prinzipien.  
Ziel des Projekts ist es, das Verhalten eines UNIX-Shell-Interpreters möglichst realitätsnah nachzubilden — inkl. Tokenizing, Parsing, Pipes, Redirections, Builtins, Environment-Handling und Signal-Management.

Minishell wurde im Rahmen des 42-Programms entwickelt und bildet die Grundlage für tiefes Verständnis von Prozesssteuerung, Dateideskriptoren, Signals & Shell-Parsing.

---

## Features

- **Bash-kompatible Eingabe** (mit grundlegender Syntax)
- **Pipes**: `cmd1 | cmd2 | cmd3`
- **Redirections**:  
  - Output: `>` und `>>`  
  - Input: `<`  
  - Heredoc: `<<`
- **Umgebungsvariablen**: `$VAR` Expansion
- **Builtins (ohne Fork)**  
  - `cd`  
  - `echo`  
  - `pwd`  
  - `export` / `unset`  
  - `env`  
  - `exit`
- **Signals**  
  - `Ctrl-C`: Unterbricht aktuelle Eingabe wie in Bash  
  - `Ctrl-\`: Ignoriert (wie Bash im interaktiven Modus)
- **Error-Handling**  
  - Syntaxfehler  
  - Command-not-found  
  - Zugriff/Permission-Fehler
- **Command execution pipeline** mit `fork`, `execve`, `dup2`, `pipe`

---

## Quickstart

> **WICHTIG:** Dieses Projekt verwendet `libft` als **Git submodule**.  
> Daher MUSST du beim Clone `--recurse-submodules` verwenden.

### 1. Repository klonen
```bash
git clone --recurse-submodules https://github.com/<dein-username>/minishell.git
cd minishell
```
Falls du das Repo bereits ohne Submodule geclont hast, hole es nach:
```bash
git submodule update --init --recursive
```

### 2. Kompilieren
Das erzeugt das Binary:
```bash
make
```

### 3. Starten
```bash
./minishell
```
Jetzt kannst du Kommandos wie in einer realen Shell ausführen:
```bash
echo Hallo Welt
ls -l | grep minishell
export TEST=42
echo $TEST
cat < input.txt | grep foo > out.txt
```

---

## Architektur (Kurzüberblick)
```bash
minishell/
 ├── src/
 │    ├── lexer/        # Tokenizing input → Tokens
 │    ├── parser/       # AST bauen, Syntax prüfen
 │    ├── exec/         # Pipelines, Redirections, FD-Management
 │    ├── builtins/     # cd, echo, export, ...
 │    ├── env/          # Environment-Verwaltung
 │    └── signals/      # Signal-Handler wie Bash
 ├── libft/             # Submodule – Utility-Funktionen
 ├── includes/          # Header (Datenstrukturen, APIs)
 ├── Makefile
 └── minishell.c
```
### Zentrale Konzepte
- **Tokenizer**
  Zerlegt Eingabezeichenketten in bedeutungsvolle Tokens (Wörter, Pipes, Redirections, Quotes).
- **Parser / AST**
  Baut eine interne Struktur der Kommandokette, überprüft Syntax und bereitet die Exec-Phase vor.
- **Executor** Baut die Pipeline, erstellt Child-Prozesse, dupliziert Deskriptoren (dup2), öffnet Redirections, ruft execve() auf.
- **Builtins ohne Fork**
Bestimmte Kommandos müssen im Elternprozess laufen, damit sie das Environment ändern können.
- **Signals**
Angepasstes Verhalten für interaktiven Modus (ähnlich Bash).

---

## Tests & Debugging
### Minishell starten mit Debug-Ausgaben
```bash
make debug
./minishell
```

### Leaks prüfen (macOS)
```bash
leaks --atExit -- ./minishell
```

### Leaks prüfen (Linux, z. B. WSL)
```bash
valgrind --leak-check=full ./minishell
```
### Vergleich mit Bash → Verhalten testen
```bash
echo "> minishell vs bash"
```

---

## Anforderungen aus dem originalen 42-Project (Kurzfassung)
- Keine Nutzung von system()
- korrekte Signals (SIGINT, SIGQUIT)
- korrekte Exit-Status
- Quotes-Handling ' ' / " "
- Pipe-Handling
- Redirection-Handling
- Builtins
- $? Expansion
- Leaks-frei

---

## License
Dieses Projekt folgt der Lizenz des 42-Curriculums.

Optionale offene Lizenz kann ergänzt werden (z. B. MIT).

---

## Autor

Felix Steinmann
GitHub: https://github.com/bddkalle
