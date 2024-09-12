# Optimizing-Arithmetic-Expressions

## Part 1 : Parsing and Converting to Binary Operations
- Parsing through the Arithmetic Operations
- Dividing each expression to Binary Operation
- For example, $x + y * z = 5$ can be converted to
  - $t_1 = y * z$
  - $t_2 = x + t_1$
  - $5 = t_2$

## Part 2 : Optimizing by removing unnecesary definitions and Constant Propagation
- Parse through the Binary Operations
- Remove all Operations which give a number as a result
- For example, converting $x + 3 * 4 = y$ to binary operations gives :
  - $t_1 = 3 * 4$
  - $t_2 = x + t_1$
  - $y = t_2$
- Optimized output :
  - $p_1 = x + 12$
  - $y = p_1$
