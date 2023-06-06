# An Introduction to ECC Lang

## Prerequisites \& Post-gain

Before learning compiler, you should have basic ideas on at least
one main stream programming language (C++, Java, or Python).
All other knowledge required by building a compiler will
be covered along with each phase of compilation, including
regular expressions, context-free grammar, assembly codes,
as well as other programming tools\footnote{This tutorial
will stick on C++ implementation, so C-based parser generator,
and compilation toolchains will also be covered}.

This tutorial is aimed at learning compilers
both theoretically and practially. You will have:
1. Basic concepts of compilation including parsing, intermediate representation,
   optimization, and code generation.
2. Knowing the usage of the most compiler infrastructure LLVM.
3. Significantly improved coding power after writing a compiler!

## Overview

Engineering Compiler Construction Language (ECC Lang)
is writtten to define a language better serve the purpose of compiler education.
The syntaxes and design concepts are inspired by hybridizing C and Java.
Excessive and redundant syntax sugars are removed to keep
the language simple. Meanwhile, modern language features
are introduced to better understand the design concept.

````
func main() -> int {
  // This function can be invoked before declaration.
  printHello();
}
func printHello() -> void {
  println("Hello world!");
}
````

Listing above shows an example of this language.
This keeps the language implementation simple, so that we can focus on
learning the compiler principles.
We assume:

1. All the programs written in this language should **NOT exceed 1MB**.
   Otherwise, the compiler is not guaranteed/required to output a correct result!
2. Only single program compilation is supported for now.

## Language Manual

### Overview

An ECC program should be composed by the following aspects:

1. Function definition.

   - `main` function: The program starts with. This function have no arguments, and return an integeter.
   - For the better purpose of education, we do NOT support interface declration.
     (Interface declration is actually an legacy from the early stage of computer system design. Because of the
     limited disk/memory size, it is highly desirable to compile the whole program by scanning it only once.)

3. Class definition.
4. Global veriable declaration.

### Comments

We only support `//` to comment a line. No `/**/` supported.

### Data Types (\& their Constants)

Declaring a varialbe is just as simple as `let {type} {id} [= {initializer}];`,
and the initializer is optional. The `id` of a variable should not start with a
number, and it can be composed by a combination of numbers, letters, and underscore.
To keep the syntax simple, we do not support declaring multiple variables separated by
commas (`,`). The `let` keyword is also to keep the "parser look ahead" (will be explained later)
simple.

### Builtin Types
These following types are builtin types:
1. `void`: Cannot be an variable, can only be the return type of a function.
2. `int`: A 32-bit signed integer. Constant integers can range from $[-2^{31},2^{31}-1]$.
3. `char`: A 8-bit char. To keep it simple, all the char surrounded by a pair of
    \texttt{'}s should be printable.
    Only 4 backslash escape characters are supported, `\'`, `\"`,
    `\\`, and `\n`.
4. `bool`: A boolean value, whose constants can be either `true`,or `false`.
    Unlike C, there is no implicit conversion to bool for all the expressions (`int`, `char`, or `classes`).
5. `string`: Literals surrounded by \texttt{"} are constants of strings. Just like
    `char` each char of a string should either be printable or supported escape characters.
    Strings are immutable.
    The string data type with three builtin members:
      - `int length()` return the length of this string.
      - `int parseInt()` convert the string into an integer.
      - `char at(int pos)` starting with 0, return the character at the given position.

Note `int`, `char`, and `bool` are plain old data (POD), so they have instances.
`string` is non-modifiable, so its behavior of being a POD or a class,
does not matter that much.


### Classes

We also allow users to define their classes and classes can have their member functions/methods.
Listing below shows an example of defining a class.
The class name has the same requirement as the variable id.
Unlike conventional C, a class can only be a pointer to an instance.
This design concept is widely adopted in modern languages, like Java and Python.
Pointers can be `null` when empty. As mentioned before, there is no implicit conversion
from `0` to `null`.

````
class A {
  print() -> void {
    // This is OK, even though `value` defined later than `print()`
    println(toString(this.value));
  }
  int value;
};

int main() {
  A a = new A;
  a.value = 5;
  a.print(); // prints 5
  A b = a;
  b.a = 1;
  a.print(); // prints 1
  return 0;
}
````

In addition, within the scope of class,
the variable difinition is slightly different
from it is in the global scope. In the example shown above,
it is OK to use `value` before it is defined within
the scope of a class. However, it makes no sense to use a global
variable before its definition.

````
void foo() {
  // Too early to use `a`!
  println(a);
}
string a;
````

TODO(@were): support destructor, inherence, virtual function, and interfacing.

### Arrays

Array allocation is very similar in what we have in Java.
Arrays have one builtin method `size()` for the size of the array.

````
int[] a = new int[128];
````

We support two types of jagged array allocation.

````
int[][] a = new int[128][128];
int[][] b = new int[128][];
for i in 0..128 {
  b[i] = new int[i + 1];
}
````

We also support compound arrays.
````
class A {
  // ...
};
// Allocate 128 empty pointers of A.
A[] a = new A[128];
````

### Expressions

1. Arithmetic Opertions: `+, -, *, /`, both side should have the same type, and no implicit cast supported.
2. Bitwise Opertions: `|,&,^,~`
3. Logic Operations: `&&, ||, !`, both operands should be boolean.
4. Access Attributes: `.`
5. Pranthesis: `()`
6. Brackets: `[]`
7. Negative: `-`
8. Comparison: `==, >, <`, returns a boolean expression.
9. Cast: `{expr} as {type}` e.g. `a as int`. TODO(@were): Assign a priority to this.
10. Assignment: `=`
    - For simplicity, unlike C, assignment has no return value.
      Therefore, no `a=b=0` allowed.
    - For simplicity, no in-place update (e.g. `+=`) supported.

The priority of these operations are the same as C.

### Statements

Every statement can be a declaration, an assignment,
a conditional statement, for-loop, while-loop, or a compound statement.

````
if (bool-expr) {
  // do a
} else {
  // do b
}
````

````
for i in 0..n {
  // do something
}
````

````
while (bool-expr) {
  // do something
}
````


Unlike C, though compound statement does open a new scope,
we cannot define variables with same id to hide instances in outer scopes,
as it is shown in Listing below.

````
int a;
{
  int a; // This is not allowed!
  int b; // b is dedicated to this scope.
}
// We cannot use b here.
````

### Function

#### Builtins

Several builtin functions are supported for I/O.
1. `void print(string str):` Write the given string to stdout.
2. `void println(string str):` Write the given string to stdout and append a newline.
3. `int getInt():` Get an integer from stdin.
4. `string getLine():` Get a line of string from stdin.
5. `string toString(i):` Convert the given int to string.

#### Function Definition

Function declaration is the same C, but we allow to define new sub-functions
within a function that captures all the values in that scope. If the return
type is not void, the compiler should not pass the semantic check.

````
func {func-id}({arg-list}) -> {return-type} {
  // do something.
  // you can still define new functions here.
}
````

Similarly, the `func` keyword is also to keep the syntax simple.

### Keywords

To sum up, these key words are reserved `bool int string null void true false if for while break continue return new class this func let`.

## Exercise

According to the language manual, write a compiler for this language. Here are some hints:

1. Be incremental! Start with a something simple and incrementally extend and test it!
2. Be bold! Do not hesitate to make design decisions! Get hands dirty first!
3. Be patient! If certain bad deisng decision makes it hard to extend, do not hesitate to refactor!

