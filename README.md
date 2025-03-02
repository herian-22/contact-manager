A simple **Contact Manager** application built using **GTK+ 3, GLib, and GObject** in C. This application allows users to **add, delete, and save contacts** with a GUI interface.

Features
- ✅ **Graphical User Interface (GUI)** with GTK+ 3.
- ✅ **Add new contacts** with a name and phone number.
- ✅ **View all saved contacts** in a list.
- ✅ **Delete selected contacts** from the list.
- ✅ **Save contacts** to a CSV file for persistence.
- ✅ **Load contacts** from a CSV file when the application starts.


---

## 📥 **Installation & Compilation**
### 1️⃣ **Install Required Dependencies**
Before compiling, make sure you have **GTK+ 3, GLib, and GObject** installed on your system.

#### **For Debian/Ubuntu:**
```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev libglib2.0-dev

Clone the Repository
git clone https://github.com/herian-22/contact-manager.git
cd contact-manager

Build the Project
make clean
make

Run the Application
./contact_manager

Graphical User Interface (GUI)

The application provides an interactive GUI built with GTK+ 3, featuring:

📌 Text entries for inputting contact name and phone number.
📌 A list box displaying all saved contacts.
📌 Buttons for adding, deleting, and saving contacts.
