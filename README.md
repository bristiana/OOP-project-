# 🎪 Festival Management System

A comprehensive C++ object-oriented programming project demonstrating advanced OOP concepts through a festival and event management system.

## 📋 Project Overview

This system manages different types of events including general events, concerts, festivals, and conferences. It showcases fundamental and advanced C++ programming concepts including inheritance, polymorphism, operator overloading, and design patterns.

## 🏗️ Architecture & Design Patterns

### Class Hierarchy
```
Eveniment (Base Class)
├── Concert (Derived)
│   └── Festival (Grandchild)
└── Conferinta (Derived)
```

### Key Design Patterns
- **Singleton Pattern**: `Meniu` class ensures single instance for application control
- **Template Classes**: Generic `Container<T>` for type-safe data storage
- **Polymorphism**: Virtual functions and dynamic casting
- **Exception Handling**: Custom exception classes for robust error management

## 🔧 Technical Features

### Object-Oriented Programming Concepts
- **Inheritance**: Three-level hierarchy (Eveniment → Concert → Festival)
- **Polymorphism**: Virtual functions with method overriding
- **Encapsulation**: Private data members with public interfaces
- **Abstraction**: Clean separation of interface and implementation

### Advanced C++ Features
- **Operator Overloading**: Stream operators (`<<`, `>>`) for all classes
- **Copy Constructors & Assignment**: Proper object copying semantics
- **Smart Pointers**: `shared_ptr` for automatic memory management
- **STL Containers**: `vector`, `map`, `list`, `set` for data organization
- **Template Programming**: Generic container class with lambda support

### Memory Management
- **RAII**: Resource Acquisition Is Initialization principles
- **Smart Pointers**: Automatic memory cleanup
- **Exception Safety**: Proper resource management during exceptions

## 📊 Class Structure

### Base Class: `Eveniment`
```cpp
class Eveniment {
protected:
    string nume, organizator, data;
    double pretBilet;
public:
    virtual void afisare() const;
    virtual string getTip() const;
    // ... constructors, operators, getters
};
```

### Derived Classes
- **`Concert`**: Adds artist, genre, and duration
- **`Festival`**: Extends Concert with days and location
- **`Conferinta`**: Adds subject and participant count

### Template Container
```cpp
template <typename T>
class Container {
    // Generic storage with filtering and iteration
    template <typename Func>
    void forEach(Func operation);
    
    template <typename Predicate>
    vector<T> filter(Predicate condition);
};
```

### Exception Handling
- `FileException`: File I/O errors
- `InvalidDataException`: Invalid user input
- `NotFoundException`: Search failures

## 🚀 Features

### Core Functionality
- **Event Management**: Add, display, and manage different event types
- **Search & Filter**: Find events by organizer or custom criteria
- **File I/O**: Save/load data with persistent storage
- **Data Validation**: Input validation with exception handling

### Advanced Operations
- **Polymorphic Operations**: Runtime type identification
- **Up/Down Casting**: Demonstration of type conversions
- **Template Operations**: Generic filtering and iteration
- **Lambda Functions**: Modern C++ functional programming

## 💻 Usage Example

```cpp
// Create and manage events
Meniu* meniu = Meniu::getInstance();

// Add different event types
Festival rockFest("Rock Festival", "MusicCorp", "15/07/2024", 150.0,
                  "Various Artists", "Rock", 180, 3, "Central Park");

// Use template container
Container<shared_ptr<Eveniment>> evenimente;
evenimente.add(make_shared<Festival>(rockFest));

// Filter with lambda
auto expensive = evenimente.filter([](const auto& ev) {
    return ev->getPretBilet() > 100.0;
});
```

## 🔍 Key Programming Concepts Demonstrated

### 1. **Inheritance & Polymorphism**
```cpp
// Base class pointer, derived class object
shared_ptr<Eveniment> ev = make_shared<Festival>(...);
ev->afisare(); // Calls Festival::afisare() via virtual dispatch
```

### 2. **Template Programming**
```cpp
// Generic operations with type safety
container.forEach([](const auto& item) {
    cout << item->getTip() << endl;
});
```

### 3. **RAII & Smart Pointers**
```cpp
// Automatic memory management
shared_ptr<Eveniment> event = make_shared<Concert>(...);
// No manual delete needed
```

### 4. **Exception Safety**
```cpp
try {
    if (pret < 0) 
        throw InvalidDataException("Negative price!");
} catch (const exception& e) {
    cout << "Error: " << e.what() << endl;
}
```


## 🎯 Learning Outcomes

This project demonstrates mastery of:

- **Advanced OOP Design**: Multi-level inheritance with proper encapsulation
- **Modern C++ Features**: Smart pointers, templates, lambdas
- **Design Patterns**: Singleton, Template Method, Strategy (via lambdas)
- **Memory Management**: RAII principles and exception safety
- **STL Proficiency**: Containers, algorithms, and iterators
- **Error Handling**: Custom exceptions and robust error recovery

## 🛠️ Compilation & Running

```bash
# Compile with C++11 or later
g++ -std=c++11 -Wall -Wextra -o festival main.cpp

# Run the application
./festival

# Or with additional debugging
g++ -std=c++11 -g -DDEBUG -o festival main.cpp
```

## 📋 Requirements

- **C++11** or later compiler
- **Standard Library**: STL containers and algorithms
- **Memory**: Minimal requirements due to efficient memory management

## 🎓 Academic Context

**Course**: Object-Oriented Programming  
**Institution**: University of Bucharest, Faculty of Mathematics and Computer Science  
**Focus Areas**: 
- Advanced OOP concepts
- Design patterns implementation
- Modern C++ programming techniques
- Software architecture principles

---

**Note**: This project showcases comprehensive understanding of C++ OOP principles and serves as a foundation for more complex software systems development.
