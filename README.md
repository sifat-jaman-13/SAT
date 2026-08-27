# 📇 SAT — Phonebook & Movie Library Management Systems

> Two console applications written in C for a first-year programming lab: a phonebook that stores contacts, and a movie library with rentals, ratings, and reporting.

[![C](https://img.shields.io/badge/C-ANSI%20C-A8B9CC?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![GCC](https://img.shields.io/badge/GCC-any%20version-4EAA25?logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Course](https://img.shields.io/badge/Course-CSE115L-yellow)](https://ece.northsouth.edu/)
[![NSU](https://img.shields.io/badge/NSU-North%20South%20University-1E90FF)](https://www.northsouth.edu/)
[![CI](https://github.com/sifat-jaman-13/SAT/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/sifat-jaman-13/SAT/actions/workflows/c-cpp.yml)

[![Platform](https://img.shields.io/badge/platform-windows%20%7C%20linux%20%7C%20macos-brightgreen)](#-quick-start)
[![License](https://img.shields.io/badge/license-educational%20use-blue)](#-license)
[![Repository](https://img.shields.io/badge/GitHub-SAT-333333?logo=github)](https://github.com/sifat-jaman-13/SAT)

---

## 📚 Project Information

| Field | Value |
|-------|-------|
| **Project** | SAT — Phonebook & Movie Library Management Systems |
| **Authors** | Sifat Jaman, Fahmid Shahriar Alvee, Tanvir Rahaman Miraz |
| **Course** | CSE115L — Programming Language I Lab |
| **Section / Group** | Section 12, Group B1 |
| **Institution** | North South University |
| **Semester** | Fall 2022 |
| **Type** | Group project (3 members) |
| **Language** | C (standard C, no external libraries) |
| **Size** | 2 programs, 1,823 lines of code, 35 functions |
| **Repository** | [sifat-jaman-13/SAT](https://github.com/sifat-jaman-13/SAT) |

---

## 🎯 Overview

This repository holds the two console programs submitted for CSE115L, the lab component of Programming Language I.

**Phonebook** (`Phonebook.c`, 457 lines) manages contact records: add, update, search, delete, and count, with input validation on names and phone numbers.

**Movie Management System** (`Movie_Management_System.c`, 1,366 lines) is the larger of the two — a library catalogue behind a login, supporting rentals and returns, star ratings, multi-criteria search, bulk deletion, sorted listing, genre statistics, CSV export, and backup.

Both keep their records in plain-text files in the working directory and use nothing beyond the C standard library. Together they cover the fundamentals the course targets: structs, file I/O, string handling, arrays, and menu-driven control flow.

> **On the name:** "SAT" comes from the first initials of the three group members — **S**ifat, **A**lvee, **T**anvir.

---

## ✨ Features

### Phonebook — 8 menu options

| # | Option |
|---|--------|
| 1 | Add new contact |
| 2 | Update contact details |
| 3 | Display all saved contacts |
| 4 | Delete a contact |
| 5 | Search for a contact |
| 6 | See total number of contacts saved |
| 7 | Exit Phonebook |
| 8 | Delete all records |

Each contact stores seven fields:

```c
typedef struct {
    char fname[MAX_NAME];      char lname[MAX_NAME];
    char number[MAX_PHONE];    char gender[MAX_GENDER];
    char email[MAX_EMAIL];     char birthdate[MAX_DATE];
    char address[MAX_ADDRESS];
} Contact;
```

First name is required; the mobile number is validated to 7–20 digits.

### Movie Management System — 15 menu options

| # | Option |
|---|--------|
| 1 | Add a Movie |
| 2 | Search for a Movie |
| 3 | Delete a Movie by Title |
| 4 | Delete Multiple Movies |
| 5 | Display All Movies (Sorted by Year) |
| 6 | Edit Movie Details |
| 7 | Count Movies in Library |
| 8 | Rate a Movie (1–5 stars) |
| 9 | Rent a Movie |
| 10 | Return a Movie |
| 11 | Genre Statistics |
| 12 | Export to CSV |
| 13 | Backup Database |
| 14 | Delete Entire Library |
| 15 | Exit |

Each film stores eight fields:

```c
typedef struct {
    char title[100];   char genre[50];      int  year;
    char director[100]; char language[50];  int  rating;
    char checkout_date[11];                 int  is_rented;
} Movie;
```

**Search** (option 2) offers four sub-modes: by Title, Director, Language, or Release Year.
**Delete Multiple** (option 4) offers four criteria: by Genre, Year, Director, or Language.

---

## 📋 Requirements

| Requirement | Minimum |
|-------------|---------|
| **Compiler** | Any C compiler — GCC, Clang, or MSVC |
| **OS** | Windows, Linux, or macOS |
| **RAM** | Negligible |
| **Disk** | Under 1 MB |

No external libraries or build system. Two source files, compiled directly.

### Verify your toolchain

```bash
gcc --version
```

---

## 🚀 Quick Start

```bash
git clone https://github.com/sifat-jaman-13/SAT.git
```

```bash
cd SAT
```

### Compile both programs

```bash
gcc -Wall -Wextra -O2 Phonebook.c -o phonebook
```

```bash
gcc -Wall -Wextra -O2 Movie_Management_System.c -o movie_management
```

On Windows, add `.exe` to the output names. These are the same flags the CI workflow uses, so a clean local build matches a clean CI build.

---

## 🖥️ Usage

### Phonebook

```bash
./phonebook
```

Opens straight to the main menu. Choose an option by number.

### Movie Management System

```bash
./movie_management
```

Prompts for a login first, then shows the main menu.

Both programs clear the screen between menus via a `CLEAR_SCREEN` macro that resolves to `cls` on Windows and `clear` elsewhere. Data files are created in the current working directory on first write, so run each program from the directory where you want its records kept.

---

## 🔐 Default Credentials

The Movie Management System requires a login. The Phonebook does not.

```
Username: admin
Password: sifat
```

Hardcoded in `Movie_Management_System.c`. Five failed attempts and the program exits, with the remaining count shown after each failure.

> ⚠️ **Security note:** the credentials are compared with `strcmp` against string literals in the source, and all records are stored as unencrypted plain text. This is a teaching exercise — do not store real personal data in it.

---

## 📁 Project Structure

```
SAT/
├── Phonebook.c                          # Contact manager (457 lines, 10 functions)
├── Movie_Management_System.c            # Movie library (1,366 lines, 25 functions)
├── CSE115L_GROUP_B1_Project_Report.pdf  # Submitted lab report
├── CSE115L_report_cover_S12_B1.docx     # Report cover sheet
├── LICENSE                              # Educational use license
├── .gitignore                           # Excludes binaries and runtime data files
└── .github/workflows/c-cpp.yml          # CI: builds both programs on every push
```

---

## 🏗️ Architecture

Both programs follow the same shape, which is the shape the course teaches:

1. **A `struct`** describing one record — `Contact` or `Movie`.
2. **A menu loop** in `main`, reading a numbered choice and dispatching to a handler.
3. **One function per operation**, each taking a `FILE *` and doing its own open, work, and close.
4. **Plain-text files** as the store, one record per line.

Deletions and updates use the standard C copy-and-rename technique: stream every record to a temporary file, skipping or replacing the target, then rename the temporary over the original. That is what `temporary.txt` and `temp.txt` are for.

### Portability

Neither program is Windows-only. Platform-specific code sits behind guards:

```c
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #define CLEAR_SCREEN system("cls")
#else
    #define CLEAR_SCREEN system("clear")
#endif
```

`<windows.h>` and `<conio.h>` are included only when `_WIN32` is defined, so both files compile unmodified with GCC or Clang on Linux and macOS.

### Continuous integration

[`.github/workflows/c-cpp.yml`](.github/workflows/c-cpp.yml) runs on every push and pull request to `main`. It sets up MSYS2 with `mingw-w64-x86_64-gcc` on `windows-latest` and compiles both programs with `-Wall -Wextra -O2`, so warnings surface as part of the build.

---

## 💾 Data Persistence

Records are stored as plain text — not binary — in the working directory. Every file is created on demand.

### Phonebook

| File | Purpose |
|------|---------|
| `phonebook.txt` | The contact records |
| `temporary.txt` | Scratch file for deletes and updates; removed afterwards |

### Movie Management System

| File | Purpose |
|------|---------|
| `movies.txt` | The film records |
| `temp.txt` | Scratch file for deletes and edits; removed afterwards |
| `movies_backup.txt` | Written by option 13, Backup Database |
| `movies_export.csv` | Written by option 12, Export to CSV |

All six are listed in [`.gitignore`](.gitignore) — they are the output of running the programs, not part of the source, so a fresh clone starts with an empty library.

> Plain text keeps the storage layer readable while learning file I/O. The trade-off is that a record containing the field delimiter can corrupt a line, and every operation rewrites the whole file.

---

## 🐛 Troubleshooting

**`gcc: command not found`**
Install a compiler: `sudo apt install build-essential` on Debian/Ubuntu, `xcode-select --install` on macOS, or MSYS2/MinGW on Windows.

**The screen does not clear**
`CLEAR_SCREEN` shells out to `cls` or `clear`. Some IDE-embedded consoles do not support either; run the program in a real terminal instead.

**Records are not saved, or the program cannot find them**
The data files are created in the current working directory, not next to the executable. Run the program from a writable directory, and always from the same one.

**Login fails on the Movie Management System**
The credentials are case-sensitive: `admin` and `sifat`. After five failures the program exits by design.

**Garbled characters in the menus**
The Movie Management System prints UTF-8 symbols such as `✗`. On an older Windows console, switch the code page first:

```bash
chcp 65001
```

---

## ⚠️ Known Limitations

1. **Credentials are hardcoded** in the source and compared as plain text.
2. **No encryption.** All records, including phone numbers, emails, addresses, and birthdates, are stored in readable text files.
3. **Whole-file rewrites.** Every delete and update streams the entire file through a temporary copy, which does not scale beyond a few thousand records.
4. **Fixed-size fields.** Field widths are set by `#define` constants; longer input is truncated.
5. **No concurrency safety.** Two instances running against the same data file will overwrite one another.
6. **The two programs are independent.** They share no data and no code, only a repository.
7. **No automated tests.** CI verifies that both programs compile without warnings; it does not test their behaviour.

---

## 🗺️ Roadmap

These are the natural next steps for anyone extending the project:

- [ ] Move credentials out of the source and store a password hash rather than a literal
- [ ] Factor the shared menu, input-validation, and file-rewrite helpers into a common module
- [ ] Replace fixed-size fields with dynamic allocation
- [ ] Add a proper delimiter with escaping, or move to CSV throughout
- [ ] Add pagination to the display-all listings
- [ ] Add a test script that drives each program through a scripted session and diffs the output
- [ ] Extend CI to build on Linux and macOS as well as Windows

---

## 🎓 Learning Outcomes

- **Structs** — modelling a record as a single composite type
- **File I/O** — `fopen`, `fgets`, `fprintf`, `rename`, `remove`, and the copy-and-rename update pattern
- **String handling** — `strcmp`, `strcpy`, `strtok`, and safe bounded input
- **Menu-driven design** — a control loop dispatching to one function per operation
- **Input validation** — length and digit checks on user-supplied fields
- **Sorting and searching** — ordering the catalogue by year, matching across four different fields
- **Conditional compilation** — `#ifdef` guards for cross-platform builds
- **Collaboration** — dividing two programs across three contributors under version control

---

## 👥 Contributors

A group project for CSE115L, Section 12, Group B1.

| Name | Student ID | GitHub |
|------|-----------|--------|
| **Sifat Jaman** | — | [@sifat-jaman-13](https://github.com/sifat-jaman-13) |
| **Fahmid Shahriar Alvee** | — | [@FahmidShahriarAlvee](https://github.com/FahmidShahriarAlvee) |
| **Tanvir Rahaman Miraz** | — | [@Tanvir-Miraz](https://github.com/Tanvir-Miraz) |

### Course staff

| Role | Name |
|------|------|
| Faculty | Rifat Ahmed Hassan (RIH) |
| Lab Instructor | A. S. M. Sabiqul Hassan |

North South University, Department of Electrical and Computer Engineering
Submitted 5 December 2022.

### Related projects

- [**GameStore-Python**](https://github.com/sifat-jaman-13/GameStore-Python) — a desktop game store in Python with CustomTkinter, for CSE101
- [**Movie-Project-Java**](https://github.com/sifat-jaman-13/Movie-Project-Java) — a movie store in Java with JavaFX, for CSE215

---

## 📜 License

**Educational use — see [LICENSE](LICENSE).**

Copyright © 2022 Sifat Jaman, Fahmid Shahriar Alvee, Tanvir Rahaman Miraz. Copyright is held jointly by all three authors.

- ✅ **Permitted:** reading, running, studying, teaching from, and building on this code for non-commercial learning, with attribution
- ❌ **Not permitted:** commercial use, or redistribution with the attribution removed
- 🚫 **Never:** submitting this work as your own coursework — that is plagiarism, and the license forbids it

See [LICENSE](LICENSE) for the full terms.
