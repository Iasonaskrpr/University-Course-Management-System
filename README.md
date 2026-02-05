# 📚 University Course Management System

> [!IMPORTANT]
> ### 🛠️ Personal & Educational Project
> This repository is a **personal learning project** currently undergoing a transformation to implement modern C++ practices. 
>
> **Notice regarding usage:**
> * **Non-Commercial:** This project is for educational purposes and portfolio demonstration only.
> * **No Warranty:** It is not intended for production use or any serious applications.
> * **Licensing:** Development is conducted under "Personal Use" parameters. Users are responsible for adhering to third-party library licenses if adapting this code for other purposes.
>
> *This README is currently being updated to reflect the new library architecture and UI features.*

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
mkdir build && cd build
cmake ..
cmake --build .

# Run the program (names will change)
./build/Main/Example 

```


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
