# Project 1 - Linear Equations Solver

A console program that reads up to **100 linear equations** and can arrange them, do operations on them and solve them using **Cramer's rule**.

## Build and run

```
g++ main.cpp -o main
./main
```

Everything is in `eqs.h` (the struct and all the functions) and `main.cpp` (reading the equations and the commands).

## Input

First the number of equations, then the equations one by one.

- variables can be any name that starts with a letter (`x1`, `x2`, `y`, `z` ...)
- variables and numbers can be on both sides and in any order
- spaces and `*` are ignored, decimals are allowed (`2.5x1`)

Every equation is arranged so all the variables are on the left (sorted) and the number is on the right:

```
3x1+x2=13-2x3   ->   3x1+x2+2x3=13
```

## Commands

| Command | What it does |
|---|---|
| `num_vars` | number of variables in all the equations |
| `num_vars i` | number of variables in equation i |
| `equation i` | prints equation i |
| `column x2` | coefficients of x2 in every equation |
| `add i j` | equation i + equation j |
| `subtract i j` | equation i - equation j |
| `substitute x2 i j` | replaces x2 in equation i using equation j |
| `D` | the coefficients matrix |
| `D x1` | the matrix with the x1 column replaced by the constants |
| `D_value` | determinant of D |
| `solve` | solves the system, or prints `No Solution` |
| `help` | shows the commands |
| `exit` | exit |

Equations are numbered from 1.

## Example

```
Enter the number of equations: 3
Enter Equation 1: 2x1+3x2+4x3=16
Enter Equation 2: x1 + 2x2 + x3 = 8
Enter Equation 3: 3x1+x2=13-2x3

The equations after arranging:
1) 2x1+3x2+4x3=16
2) x1+2x2+x3=8
3) 3x1+x2+2x3=13

column x2
3
2
1
add 1 3
5x1+4x2+6x3=29
subtract 1 3
-x1+2x2+2x3=3
substitute x2 1 3
-7x1-2x3=-23
D
2    3    4
1    2    1
3    1    2
D x1
16    3    4
8    2    1
13    1    2
D_value
-11
solve
x1=3
x2=2
x3=1
```

## How it works

1. `move_right_to_left` moves everything to the left side (`2x1+3x2=5` -> `2x1+3x2-5=0`)
2. `parse` cuts the equation into terms and separates the coefficient from the variable
3. `merge_variables` adds the same variables together (`x1+2x1` -> `3x1`)
4. `sort_attributes` sorts the variables (`x2` comes before `x10`)
5. `Form_equation` builds the equation string again

For the determinant I used Gaussian elimination instead of the cofactor way, because the cofactor way would take forever with 100 equations. Then `solve` uses Cramer's rule: `x = D_x / D`.

I tested it with random systems of 100 equations and it gives the right answers in less than a second.

To see what every function does step by step, uncomment `#define PRINT` at the top of `eqs.h`.
