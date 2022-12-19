# Operating Systems Tasks (Linux)

## Task 1

1. Output all script arguments in reverse order
Note: use the while loop

2. Creating a file if it does not exist and setting access rights to it  
syntax: `makefile <name> [<mode>]`  
The mode parameter is optional (you can omit it). If the mode parameter is specified, then pass it in the chmod style, for example mkfile my-script a+x  
Note: use if

3. Calculator for arithmetic operations +, -, *, /  
Instruction: use case and substitution of expr command

## Task 2

1. Write a txt script that displays the specified text a specified number of times after a specified time interval. Provide the following call syntax  
`ptxt -n <number of text outputs> -t <output timeout> -- <text to output>`  
use case and shift commands to get parameters

2. Write a txt script as in task 1  
use getopt

3. Write a script that sorts and outputs the arguments passed to it in alphabetical order  
to use arrays and array sorting by any method

## Task 4

Learn the theory from the attached file and write programs for Linux in C

1. The prntxt program, which accepts the number of repetitions, the timeout value and the text in the command line parameters, and then prints a line of text to the screen a specified number of times with a specified timeout. Support both short and long options. Call syntax  
`prntxt -n|--number <number of repetitions> [-t|--timeout [<timeout>]] -- <arbitrary text>`  
The value of the `<timeout>` parameter is optional, by default 1 second. When calling prntxt without the `-t|--timeout` parameter, output text without timeout. When calling prntxt without the `-n|--number` parameter, or if no text is specified for output, output an error message and a syntax hint (`usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>`)

2. The launch program, which takes in the first command-line parameter the file name of the program to run and in the second command-line parameter the file name.  
launch `<prog> <file>`  
The launch program should launch the `<prog>` program in the child process and redirect the standard output of the running program to the `<file>` file, wait for the child process to complete and display the PID and return code of the completed process.

## Task 5

Изучить теорию из присоединенного файла и выполнить следующие задания:

1. написать программу для Linux, которая выполняет следующие действия:
   - Создает дочерний процесс, который каждые 3 секунды посылает сигнал `SIGUSR1` родительскому процессу
   - Создает в текущем каталоге именованный канал с именем reqests и открывает его для чтения
   - Создает сигнальные дескрипторы для обработки сигналов `SIGINT` и `SIGUSR1`
   - Используя poll ожидает в цикле на дескрипторах сигналов и канала
   - При получении сигнала `SIGUSR1` выводит имя полученного сигнала на экран
   - При получении сигнала `SIGINT` завершает цикл ожидания
   - После завершения цикла ожидания посылает сигнал `SIGTERM` дочернему процессу
   - Ждет завершение дочернего процесса и выводит на экран его код завершения
   - Удаляет ранее созданный именованный канал reqests и завершается
2. Исправить (добавить семафор) в приведенную программу, чтобы исключить конфликт родительского и дочернего процессов при выводе текста на экран. Каждая строчка должна содержать или 10 символов 'P' или 10 символов 'C', символы не должны смешиваться в одной строке.

```
# include <stdio.h>
# include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (!pid) {
        while (1)
        {
            for (int i = 0; i < 10; i++)
            {
                putchar('C'); fflush(stdout);
                usleep(10000 /*us*/);
            }
            putchar('\n');
        }
    }

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putchar('P'); fflush(stdout);
            usleep(10000 /*us*/);
        }
        putchar('\n');
    }
    
    return 0;
}
```