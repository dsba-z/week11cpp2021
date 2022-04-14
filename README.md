# DSBA Introduction to Programming // Workshop 26
Spring semester 2021/22


Custom Exceptions. Enums. Inheritance.

Online IDE version (click "Fork" to run it yourself): https://replit.com/@l8doku/Workshop23FunctionObjects

Full instructions are included in the file [Workshop 26](/Workshop26-custom-exceptions.pdf).

## Tasks

1. Develop a custom exception class AppExcept , choose an appropriate base class (e.g., std::runtime_error or std::exception classes).
2. Define in it a user-defined data type enum class ErrorCode describing a list of possible incorrect situations that the program expects.
3. Create a constructor for AppExcept that allows you to raise an exception object with an error code and (optionally) an informative message for the developer (specify the ancestor class).
4. In the main() function, add a “top-level” exception dispatcher that handles application exceptions ( AppExcept ), all standardized exceptions (std::exception ), and all others ( ... ).
5. Handle AppExcept exceptions 
    1. by the switch block, 
    2. by the associated map “error code” → “message test”.
