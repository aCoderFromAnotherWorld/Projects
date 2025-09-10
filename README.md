# Projects
These are some projects that I made simply for learning basics of OOP with CPP...
These are mainly based on cosole input output... But these can be implemented by file also...


# 🏥 Hospital Manager (OOP with C++)

This project is a **Hospital Management System** built using **Object-Oriented Programming (OOP) principles in C++**.  
It was originally developed as a course assignment during my **1st year, 2nd semester**, and earned full marks.  

The system allows management of doctors and patients in a hospital, including appointment scheduling, patient admission, record management, and doctor specialization mapping.

---

## 🚀 Features

- 🔑 **Login system** with password protection
- 👨‍⚕️ **Doctor management**
  - Add a new doctor with specialization and visiting hours  
  - View all registered doctors  
  - Resign a doctor  
  - Search doctors by specialization
- 🧑‍🦽 **Patient management**
  - Admit a new patient with personal details and disease type  
  - Automatically recommend doctors based on disease  
  - View all admitted patients  
  - Search patients by name  
  - Release patients after treatment
- ⏱ **Time handling**
  - Visiting hours are automatically calculated for doctors
- 🔐 **Change password option** for login

---

## 📂 Project Structure

The project uses several classes to implement OOP principles:

- `Login` → Handles authentication and password management  
- `Time` → Manages doctor visiting hours  
- `Doctor` → Stores doctor details (ID, name, speciality, visiting hours)  
- `Patient` → Stores patient details (ID, name, age, blood group, gender, disease, contact)  
- `HospitalManager` → Main manager class for handling doctors and patients  

Additional helper functions are used for searching, recommending doctors, and managing records.

---

## 🛠 Technologies Used

- **Language:** C++  
- **Concepts Applied:**  
  - Classes & Objects  
  - Friend functions  
  - Operator overloading  
  - Encapsulation  
  - Inheritance-like access via friends  
  - Standard Template Library (STL): `vector`, `map`, `algorithm`  

---

## 📖 How to Run

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/Hospital-Manager.git
   cd Hospital-Manager
   ```
2. Compile the code:
    ```bash
    g++ hospital_manager.cpp -o hospital_manager
    ```
3. Run the program:
    ```bash
    ./hospital_manager
    ```
4. Default login password is:\
   ```bash
   12345
   ```
---

## 📸 Example Workflow
- Add doctors with their visiting hours and specializations
- Admit patients with details → system recommends relevant doctors
- View or search existing patients/doctors
- Release patients or resign doctors when needed

---
## 📌 Future Improvements
- Store data in files (persistence) instead of only in memory
- Add graphical user interface (GUI)
- Enhance search with fuzzy matching
- Add billing and pharmacy management

---
## 👨‍💻 Author
**MD. Abu Hasanat Soykot** 
Undergraduate CSE Student, KUET
---
