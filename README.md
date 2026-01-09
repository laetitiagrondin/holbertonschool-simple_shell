# [**Simple Shell**](https://github.com/laetitiagrondin/holbertonschool-simple_shell)

## 🧠 Description

**Simple Shell** is a minimalist command-line interpreter written in C, inspired by the UNIX `sh` shell.
It can execute both built-in and external commands using a classic read–parse–execute loop.

---

## ⚙️ Features

| Feature | Status |
|---------|--------|
| Built-in `exit` & `env` | ✅ Implemented |
| PATH resolution | ✅ Implemented |
| Fork/execve execution | ✅ Implemented |
| Memory leak prevention | ✅ Implemented |
| Non-interactive mode | ✅ Implemented |
| Error handling | ✅ Basic |

---

## 🧩 Directory Structure

| File | Description |
|------|-------------|
| `builtin_env.c` | Handle exit & env built ins |
| `exec.c` | Execute commands with fork/execve/wait |
| `find_path.c` | used to find the absolute path of a command |
| `shell.c` | Read the command write by the user and execute it |
| `shell.h` | Header file with includes and prototypes |
| `man_1_simple_shell` | Manual page |
| `README.md` | Project documentation |

---

## 🔧 Compilation

Compile the project with:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
---

## ▶️ Usage

Interactive mode
```bash
./hsh
$ ls -l
$ echo Hello World
$ env
$ exit
```
Non-interactive mode
```bash
echo "ls" | ./hsh
```
---

## 🔍 Internal Workflow

Prompt: Display $ and wait for user input.

Read: Capture the input line using getline().

Parse: Split input into tokens using strtok().

Built-in check:

If exit: free memory and quit.

If env: print environment variables and continue.

PATH resolution: Search for executables in directories listed in PATH.

Execute:

Create a new process with fork().

The child executes using execve().

The parent waits for termination with wait().

Loop: Repeat until the user exits or EOF is reached.

---

## 💡 Built-in Commands

Command	Description
`exit`	Exit the shell
`env`	Display environment variables

---

## 🧹 Memory Management

Frees dynamically allocated memory after every command.

Proper cleanup on exit or end-of-file.

Prevents memory leaks caused by token duplication or getline buffer reuse.

---

## 🧭 Flowchart

┌──────────────┐
│   START      │
└──────┬───────┘
       │
       ▼
┌──────────────────────┐
│ Check isatty(STDIN)  │
└──────┬───────────────┘
       │
       ▼
┌──────────────────────┐
│ Display prompt ($) ? │◄─────┐
└──────┬───────────────┘      │
       │                      │
       ▼                      │
┌──────────────────────┐      │
│ Read line (getline)  │      │
└──────┬───────────────┘      │
       │
       ├── EOF ? ── YES ──► EXIT
       │
       ▼
┌──────────────────────┐
│ Empty line ?         │
└──────┬───────────────┘
       │
       ├── YES ───────────────┘
       │
       ▼
┌──────────────────────┐
│ split_line()         │
│ tokenize input       │
└──────┬───────────────┘
       │
       ▼
┌──────────────────────┐
│ args[0] == NULL ?    │
└──────┬───────────────┘
       │
       ├── YES ───────────────┘
       │
       ▼
┌──────────────────────┐
│ Builtin command ?    │
│ (exit / env)         │
└──────┬───────────────┘
       │
       ├── exit ───────► EXIT
       │
       ├── env ────────► Print environ
       │
       ▼
┌──────────────────────┐
│ find_path(command)  │
└──────┬───────────────┘
       │
       ├── NOT FOUND ──► Error message
       │
       ▼
┌──────────────────────┐
│ fork()               │
└──────┬───────────────┘
       │
       ├── pid == 0 (child)
       │        │
       │        ▼
       │   execve(path, args)
       │        │
       │        ├─ FAIL → error + exit(127)
       │
       └── pid > 0 (parent)
                │
                ▼
           wait()
                │
                ▼
          Free memory
                │
                └──────────────► LOOP

---

## 👨‍💻 Authors

[**Laetitia**](https://github.com/laetitiagrondin) & [**Benjamin**](https://github.com/B-ama-k)