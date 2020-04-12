# CompileTimeUI
Compile time UI for command line tools, using c++ 20

Creating a command line UI that does not use runtime polymorphism and thus generating minimum lines of assembly.
Each command should satisfy a simple concept:

  * Must be a callable object that accepts __char **__ and __int__ as arguments (so the command line arguments that get passed to __int main()__)
  * Must have a __GetTrigger()__ method that returns __const char *__ - the trigger by which the command can be found
  
Creating and using a UI object is a peace of cake:
```c++
  UI<Command1, Command2> ui;
  char c[100];
  cin >> c;
  
  ui.CallByTrigger(c, nullptr, 0);
```
The commands in the UI must be unique:
```c++
 UI<Command1, Command2> ui_1; // OK
 
 UI<Command1, Command1> ui_2; // Will not compile
```
see main.cpp
