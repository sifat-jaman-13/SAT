# SAT - Management Systems

Two interactive C-based management systems built as part of **CSE115L** coursework at **North South University**. These projects demonstrate file handling, data structures, and user interface design in C.

---

## 📋 Projects Overview

### 1. **Phonebook Management System** (`Phonebook_FIXED.c`)
A comprehensive contact management application that allows users to store, retrieve, update, and manage contact information.

### 2. **Movie Library Management System** (`Movie_Management_System_FIXED.c`)
A movie database system with advanced search and filtering capabilities, perfect for managing personal movie collections.

---

## ✨ Features

### Phonebook Management System
- ✅ **Add Contacts** - Create new contacts with detailed information
- ✅ **Search Contacts** - Find contacts by first name
- ✅ **Update Contacts** - Modify existing contact details
- ✅ **Delete Contacts** - Remove individual contacts
- ✅ **Display All** - View complete contact list
- ✅ **Contact Counter** - See total number of saved contacts
- ✅ **Bulk Delete** - Clear all records at once
- ✅ **Data Persistence** - Contacts saved in `phonebook.txt`

**Contact Fields:**
- First Name (Required)
- Last Name
- Mobile Number (7-20 digits validation)
- Gender
- Email
- Birthdate
- Address

### Movie Library Management System
- ✅ **Add Movies** - Add new movies to your library
- ✅ **Search Movies** - Find movies by:
  - Title
  - Director
  - Language
  - Release Year
- ✅ **Delete Movies** - Remove movies by:
  - Title (single movie)
  - Genre
  - Director
  - Language
  - Year
- ✅ **Edit Movies** - Modify movie details
- ✅ **Display Sorted** - View all movies sorted by release year (newest first)
- ✅ **Count Movies** - Get total number of movies in library
- ✅ **Clear Library** - Delete entire database
- ✅ **Data Persistence** - Movies saved in `movies.txt`
- ✅ **Login System** - Secure access with username/password

**Movie Fields:**
- Title
- Genre
- Release Year
- Director
- Language

---

## 🔧 Requirements

- **OS:** Windows (uses Windows-specific functions)
- **Compiler:** GCC, MSVC, or any C compiler supporting C99+
- **Dependencies:** Standard C library (stdio.h, stdlib.h, string.h, windows.h, conio.h)

### For Cross-Platform Use:
Remove the following from the source files:
- `#include <windows.h>` 
- `system("cls");` → Replace with `system("clear");` (Linux/Mac)
- `system("color E0");` → Remove (color not supported)
- `getch()` → Replace with alternative input method

---

## 🚀 Installation & Running

### **Option 1: Using GCC (Recommended for Windows)**

```bash
# Compile Phonebook
gcc Phonebook_FIXED.c -o phonebook.exe

# Compile Movie Management System
gcc Movie_Management_System_FIXED.c -o movies.exe

# Run
./phonebook.exe
./movies.exe
```

### **Option 2: Using Visual Studio**
1. Create a new C project
2. Add the `.c` file to your project
3. Build → Compile
4. Debug → Start Debugging

### **Option 3: Using Code::Blocks / Dev-C++**
1. Create new project
2. Add source file
3. Build & Run

---

## 📖 User Guide

### **Phonebook Management System**

#### Starting the Application
```
1. Run phonebook.exe
2. A colorful menu will appear
3. Choose an option (1-8)
```

#### Menu Options

| Option | Action |
|--------|--------|
| 1 | Add a new contact |
| 2 | Update existing contact details |
| 3 | Display all saved contacts |
| 4 | Delete a specific contact |
| 5 | Search for a contact by first name |
| 6 | Count total saved contacts |
| 7 | Exit the application |
| 8 | Delete all records (irreversible) |

#### Example Usage
```
Choose an option: 1
Do you want to add contact to your phonebook?
Press 1 to confirm 
Press 2 to Go back to Main Menu
→ 1

1. First Name (Required): John
2. Last Name: Doe
3. Mobile Number: 01912345678
4. Gender: Male
5. Email: john@example.com
6. Birthdate: 1995-05-15
7. Address: 123 Main Street, Dhaka

Your contact has been saved!
```

---

### **Movie Library Management System**

#### Starting the Application
```
1. Run movies.exe
2. Login Screen appears
   Username: admin
   Password: sifat
3. Main menu will be displayed
```

#### Login Credentials
- **Username:** `admin`
- **Password:** `sifat`
- **Max Attempts:** 5

#### Menu Options

| Option | Action |
|--------|--------|
| 1 | Add a new movie |
| 2 | Search for a movie (4 search methods) |
| 3 | Delete a single movie by title |
| 4 | Delete multiple movies by criteria |
| 5 | Display all movies sorted by year |
| 6 | Edit movie details |
| 7 | Count total movies in library |
| 8 | Delete entire movie library |
| 9 | Exit application |

#### Example Usage
```
=== Add a Movie ===

Title: Inception
Genre: Sci-Fi
Year: 2010
Director: Christopher Nolan
Language: English

Movie added successfully!
```

---

## 🔐 Data Storage

### Phonebook
- **File:** `phonebook.txt` (binary format)
- **Location:** Same directory as executable
- **Auto-created:** Yes (if doesn't exist)

### Movie Library
- **File:** `movies.txt` (binary format)
- **Location:** Same directory as executable
- **Auto-created:** Yes (if doesn't exist)
- **Temp File:** `temp.txt` (used during deletion operations)

---

## ⚠️ Known Limitations

1. **Phone Number Validation:** Only checks length (7-20 chars), not format
2. **Search Results:** Shows first match only (except bulk displays)
3. **Case Sensitive:** Searches are case-sensitive
4. **No Export:** Cannot export data to CSV or other formats
5. **Single User:** No multi-user support
6. **Fixed Arrays:** Maximum field lengths cannot exceed allocated size
7. **Weak Authentication:** Simple hardcoded credentials (Movie app only)
8. **Windows-Only:** Uses Windows system calls; requires modification for other OS

---

## 🐛 Fixed Issues (Version 2.0)

✅ Replaced unsafe `gets()` with `fgets()`  
✅ Fixed newline handling in string inputs  
✅ Corrected typos (`delelteone` → `deleteone`, "Brithdate" → "Birthdate")  
✅ Added proper buffer clearing with `getchar()`  
✅ Fixed missing `rewind()` calls in Movie app  
✅ Improved `printf()` formatting with newlines  
✅ Enhanced input validation  

---

## 💡 Future Enhancements

- [ ] Add sorting capabilities for phonebook
- [ ] Implement search by partial name match
- [ ] Add duplicate contact detection
- [ ] Create CSV import/export functionality
- [ ] Add password protection with encryption
- [ ] Implement rating system for movies
- [ ] Add genre-based statistics
- [ ] Create backup/restore functionality
- [ ] Build cross-platform GUI version
- [ ] Add cloud sync capability

---

## 📝 Code Structure

### File Organization
```
SAT/
├── Phonebook_FIXED.c                      (Fixed version)
├── Movie_Management_System_FIXED.c        (Fixed version)
├── Phonebook.c                            (Original)
├── Movie Management System.c              (Original)
├── CSE115L_GROUP_B1_Project_Report.pdf   (Documentation)
└── README.md                              (This file)
```

### Key Functions

**Phonebook.c:**
- `addperson()` - Add new contact
- `deleteone()` - Delete single contact
- `update()` - Update contact details
- `searchandprint()` - Search contact
- `displayall()` - Display all contacts
- `deleteall()` - Clear all records

**Movie_Management_System_FIXED.c:**
- `addMovie()` - Add movie
- `searchMovieByName/Director/Language/ReleaseDate()` - Search functions
- `deleteMovieByName/ByGenre/ByYear/ByDirector/ByLanguage()` - Delete functions
- `displayAllMoviesSortedByYear()` - Sorted display
- `editMovieDetails()` - Edit movie info

---

## 🎨 Features Highlights

### Phonebook
- **Colorful Console UI** - Color-coded text for better readability
- **Input Validation** - Phone number validation
- **Persistent Storage** - Data survives application restart
- **User-Friendly Menu** - Clear navigation options

### Movie Library
- **Secure Login** - Password-protected access
- **Multiple Search Options** - Find movies various ways
- **Bulk Operations** - Delete multiple movies at once
- **Sorting Algorithm** - Bubble sort implementation (newest first)
- **Dynamic Memory** - Allocates memory based on movie count

---

## 🤝 Contributing

These are educational projects from CSE115L coursework. For improvements:

1. Fork or clone the repository
2. Make your changes
3. Test thoroughly
4. Document your modifications
5. Submit a pull request

---

## 📚 Educational Value

These projects teach:
- **File I/O Operations** - Binary file reading/writing
- **Data Structures** - Structs for organizing data
- **Memory Management** - Dynamic allocation and deallocation
- **String Operations** - Buffer management and validation
- **User Interface Design** - Interactive menu systems
- **Search Algorithms** - Linear search implementation
- **Sorting Algorithms** - Bubble sort for data arrangement
- **Error Handling** - Input validation and file operations

---

## 📞 Support

For issues or questions:
1. Check the limitations section
2. Review the project report PDF
3. Verify input format and requirements
4. Ensure files have read/write permissions

---

## 📄 License

Educational project - Use freely for learning purposes.

---

## 👥 Authors

**North South University - CSE115L Course**
- Group B1 (3-person team)
- First Semester CSE Students
- Instructor: RIH Faculty

---

## 🎯 Project Goals Achieved

✅ Understand file handling in C  
✅ Implement data persistence  
✅ Create interactive user interfaces  
✅ Practice struct and data management  
✅ Learn search and sort algorithms  
✅ Develop debugging and testing skills  

---

**Version:** 2.0 (Fixed)  
**Last Updated:** 2026  
**Status:** ✅ Working
