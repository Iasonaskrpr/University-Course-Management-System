# 📚 University Course Management System
[!NOTE] 
This project is undergoing a transformation. The goal is to use more modern c++ practices (this was a 3rd semester project so our c++ skills were not good) and to become a library that can be used independently, along with adding a simple UI showcasing its features. This README is outdated and will undergo a change eventually.

> 💻 **Object-Oriented Programming Project**  
> 👥 Developed by 2 students for the **Department of Informatics and Telecommunications (DIT), University of Athens (UOA)**

---

## 🚀 Features

- **Student Management**
  - Add, update, or delete students  
  - Track student progress (grades, semesters, ECTS)  
  - Enroll students in courses  

- **Professor Management**
  - Add, update, or remove professors  
  - Assign courses to professors  
  - View teaching statistics (success rate, average grades)

- **Course Management**
  - Create, update, or delete courses  
  - Set course details (ECTS, semester, mandatory/optional)  
  - Track student performance per course

- **Semester Lifecycle**
  - Start and end semesters  
  - Input grades and progress students through semesters  
  - Identify students eligible for graduation

- **File Persistence**
  - Automatically loads and saves data from/to:
    - `Courses.txt`
    - `Students.txt`
    - `Professors.txt`

---

## 📁 Project Structure

- `main.cpp` – Console interface and main program loop
- `file1.cpp` – All class implementations (`Person`, `Student`, `Professor`, `Course`, `Secretary`)
- `file1.h` – Class declarations (assumed present)
- `Courses.txt`, `Students.txt`, `Professors.txt` – Data files
- `Makefile` – Build automation

---

## 🧑‍💻 How to Build and Run

Make sure you have `g++` and `make` installed. Then run:

```bash
# Build the program
make

# Run the program
make run

# Run with Valgrind (for memory leak check)
make valgrind

# Clean all compiled files
make clean

# Build optimized version (no debug symbols)
make release
```

This will produce an executable named `main`.

---

## 🎓 Degree Eligibility Rules

A student is eligible to graduate if:

- They have **90 or more ECTS**
- Have completed **at least 8 semesters**
- Passed **all mandatory courses**

---

## 🛠 Technologies

- **Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Compiler:** `g++`
- **Tools:** Makefile, Valgrind (optional)

---

## 🏁 Notes

- The system uses interactive menus and handles common errors (e.g. missing students or courses).
- Grades, semester progression, and enrollments are managed per course and per student.
- Data is saved persistently after exiting the system.

---
