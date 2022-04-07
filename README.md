# DSBA Introduction to Programming // Workshop 24
Spring semester 2021/22


Exceptions. Reading incorrect data.

## Task 1. Warnings.

You have a function that reads data and fills empty "ID", "Age", "SibSp" and "Parch" cells with 0. However, there are no checks implemented for some other columns, and if empty data appears in them, the program will not work.

- Try loading data from the file "titanic_empty_fare.csv".

- Fix the program so that it warns the user that the file was corrupted, similar to the existing check.


## Task 2. Corrupted data.

The original version of the program assumes that if a line was read correctly, it contains a correct number of columns. However, this may not be the case.

- Try loading data from the file "titanic_no_columns.csv".

- Add a check to the cell reading function `extractData` to see if all the cells were read correctly. Give a warning and skip the row, if there was a mistake in that row.

To skip the row, move the line that adds a passenger to the vector to a `try` block like this:

```cpp
        std::stringstream lineStream(buffer);
        try
        {
            Passenger newPass = extractData(lineStream);
            passengers.push_back(newPass);
        }
        catch(std::runtime_error const& ex)
        {
            // warn the user that a row was skipped
        }
```

## Task 3. Asking the user.

Implement the following logic in your application.

When the program encounters incorrect data, it should ask the user for input. The user has 4 options.

1. Skip the row as corrupt.
2. Fill the row with default data, trying to "repair" it and add it to the vector of passengers.
3. Choose and remember option 1, so the user isn't asked anymore.
4. Choose and remember option 2, so the user isn't asked anymore.


### Additional subtask

Add option 5: "Exit the program" by throwing another exception and catching it in `main()`.


