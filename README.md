# Get next line

Welcome to Get Next Line, a project developed as part of the curriculum at **[42](https://www.42.fr/)**! Get Next Line is a function that reads a file line by line, allowing you to retrieve each line individually. This can be particularly useful when dealing with large files or when you need to process data line by line.

## **Table of Contents**

- **[About](#about)**
- **[Installation](#installation)**
- **[Usage](#usage)**
- **[Function Prototype](#function-prototype)**
- **[Return Value](#return-value)**
- **[Example](#example)**
- **[Bonus Part](#bonus-part)**
- **[Contributing](#contributing)**
- **[License](#license)**

## **About**

The Get Next Line project is aimed at improving your understanding of file descriptors, static variables, and reading from a file or a descriptor. The project challenges you to implement a function that reads a line from a file descriptor and returns it without the newline character.

## **Installation**

To use Get Next Line, follow these steps:

1. Clone the repository:
    
    ```bash
    git clone https://github.com/anassajaanan/Get-Next-Line.git
    ```
    
2. Navigate to the project directory:
    
    ```bash
    cd Get-Next-Line
    ```
    
3. Compile the source files using your preferred method.

## **Usage**

To use the Get Next Line function in your project, follow these steps:

1. Include the **`get_next_line.h`** header file in your source file:
    
    ```c
    #include "get_next_line.h"
    ```
    
2. Call the function **`get_next_line`** in your code:
    
    ```c
    char *get_next_line(int fd);
    ```
    
3. The function reads the file descriptor **`fd`** line by line and returns the line that was read. If there is nothing else to read or if an error occurred, it returns **`NULL`**.
4. Remember to handle memory allocation and deallocation properly, as the function allocates memory for the line read. It is the caller's responsibility to free the allocated memory.

## **Function Prototype**

The function **`get_next_line`** has the following prototype:

```c
char *get_next_line(int fd);
```

- **`fd`**: The file descriptor to read from.

## **Return Value**

The **`get_next_line`** function returns the following values:

- Read line: If a line has been successfully read.
- **`NULL`**: If there is nothing else to read or if an error occurred.

## **Example**

Here's an example of how you can use the Get Next Line function:

```c
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        // Handle error
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        // Process the line
        // ...

        free(line);
    }

    close(fd);

    return 0;
}

```

## **Efficient Implementation using Queue Data Structure**

In this implementation of Get Next Line, I have chosen to utilize a queue data structure to enhance the efficiency of the function.

By using a queue, the function can handle multiple file descriptors and read lines from each descriptor seamlessly. This approach allows for efficient memory management and eliminates the need for resizing arrays or maintaining static variables for each file descriptor.

Here's how the queue-based implementation works:

1. The **`get_next_line`** function maintains a queue for each file descriptor. Each queue holds the lines read from the corresponding file descriptor.
2. When **`get_next_line`** is called with a file descriptor **`fd`**, it checks if the queue for **`fd`** is empty. If it is, the function reads more lines from the file descriptor and enqueues them in the corresponding queue.
3. If the queue for **`fd`** is not empty, the function dequeues the next line from the queue and returns it. This ensures that lines are processed in the order they were read.
4. When there are no more lines left in the queue for a specific file descriptor, the function reads more lines from the file descriptor and enqueues them, if available.

By utilizing a queue data structure, your implementation achieves efficient handling of multiple file descriptors without compromising the integrity of the reading thread for each descriptor. This approach allows for a seamless reading experience, ensuring that lines are returned in the order they are encountered in the file.

Here's an example of how the efficient implementation with a queue can be used:

```c
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd1, fd2;
    char *line1, *line2;

    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 == -1)
    {
        // Handle error
    }

    fd2 = open("file2.txt", O_RDONLY);
    if (fd2 == -1)
    {
        // Handle error
    }

    while ((line1 = get_next_line(fd1)) != NULL || (line2 = get_next_line(fd2)) != NULL)
    {
        // Process lines from file1.txt and file2.txt separately
        // ...

        if (line1 != NULL)
        {
            free(line1);
        }

        if (line2 != NULL)
        {
            free(line2);
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}

```

By implementing Get Next Line using a queue data structure, your implementation achieves enhanced efficiency and ensures that lines are processed in the order they are read, providing an optimal solution for handling multiple file descriptors.

## **Bonus Part**

In addition to the mandatory part, the project also includes a bonus part. The bonus part allows the **`get_next_line`** function to handle multiple file descriptors at the same time.

To use the bonus part, include the following files:

- **`get_next_line_bonus.c`**
- **`get_next_line_bonus.h`**
- **`get_next_line_utils_bonus.c`**

### **Multiple File Descriptors**

With the bonus implementation, the **`get_next_line`** function can manage multiple file descriptors concurrently. This means that you can read from different file descriptors without losing the reading thread of each descriptor or returning a line from another descriptor.

To utilize this feature, follow these steps:

1. Call **`get_next_line`** with the desired file descriptor:
    
    ```c
    char *get_next_line(int fd);
    ```
    
2. The function reads the file descriptor **`fd`** line by line and returns the line that was read. If there is nothing else to read or if an error occurred, it returns **`NULL`**.
3. You can call **`get_next_line`** with different file descriptors in any order, and the function will maintain separate reading states for each descriptor.

Here's an example of how you can use the bonus feature with multiple file descriptors:

```c
#include <fcntl.h>#include "get_next_line_bonus.h"int main(void)
{
    int fd1, fd2;
    char *line1, *line2;

    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 == -1)
    {
        // Handle error
    }

    fd2 = open("file2.txt", O_RDONLY);
    if (fd2 == -1)
    {
        // Handle error
    }

    while ((line1 = get_next_line(fd1)) != NULL || (line2 = get_next_line(fd2)) != NULL)
    {
        // Process lines from file1.txt and file2.txt separately
        // ...

        if (line1 != NULL)
        {
            free(line1);
        }

        if (line2 != NULL)
        {
            free(line2);
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}

```

By using the bonus implementation, you can read lines from multiple file descriptors simultaneously, allowing for more efficient processing of data.

## **Contributing**

Contributions are welcome! If you'd like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create your feature branch: **`git checkout -b feature/my-feature`**.
3. Commit your changes: **`git commit -am 'Add some feature'`**.
4. Push to the branch: **`git push origin feature/my-feature`**.
5. Open a pull request.

## **License**

This project is licensed under the **[MIT License](https://github.com/anassajaanan/Get-Next-Line)**.

Feel free to modify and distribute this project as needed.
