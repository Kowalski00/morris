# morris

This project is to have a little fun with the Morris Sequence and to learn a bit of C.

The Morris Sequence is also know as 'look-and-say' Sequence where each row explains the previous row by counting the number of digits in groups.

```
1
1 1                   =>  one 1
2 1                   =>  two 1
1 2 1 1               =>  one 2 and one 1
1 1 1 2 2 1           =>  one 1 and one 2 and two one's
3 1 2 2 1 1           =>  three 1 and two 2 and one 1
1 3 1 1 2 2 2 1       =>  one 3 and one 1 and two 2 and two 1
1 1 1 3 2 1 3 2 1 1   =>  one 1 and one 3 and two 1 and three 2 and one 1
.
.
.
```

The goals for this project are:

- [X] Create a program that will print the sequence up to 10 lines;
- [X] Ask for a input N to print the sequence up to the N line;
- [X] Describe the sequence along the lines;
- [X] Ask for a single digit number to begin the sequence with that number;
- [X] Ask for any number to begin the sequence;
- [ ] Match by color when describing;
- [ ] Print description in a more elegant way.
