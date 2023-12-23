# Introduction

In the last section, the language manual is specified.
Still, there is intensive engineering work to translate
the language into executable binaries, which can hardly
be done immediately.
To gently achieve this goal, let's break it down to pieces.

## What is a programming language?

How a program is lowered into executable binaries? A programming language
is a "language" because it has all the aspects of a language:

- Words: The program is separated into a sequence of `words`. In compiler
  engineering, these `words` are called `tokens`. For such a program below,
  it will be separated into:
  - Keyword: `func`
  - Identifier: `main`
  - {L/R}Pranthesis: `(`, `)`
  - Mapping Indicator: `->`
  - Builtin Type: `void`
  - Brace: `{`,
  - Keyword: `return`,
  - Integer Const: `0`
  - Semicolon: `;`
  - Brace: `}`.

````
func main() -> void {
  return 0;
}
````

- Grammar: Then these words are structured in some grammar structure. In compiler
  engineering, this grammar is called `syntax`. Just like a statement in English
  is composed by `subject verb object`. A programming should also have some grammars.
  Continue on the example above, declaring a func follows such a context-free grammar:

````
func-decl: Keyword("func") Identifier LPranthesis RPranthesis compound-statement
compound-statement: statement compound-statement
statement: return-statement ';'
return-statement: Keyword("return") expr
                | Keyword("return")
````

- Semantics: Even though a program is correct in term of syntax,
  it can still be non-sense. For example,
  I can say `A bottle of apples crawls on the sky.`.
  This is totally grammarly correct, but makes no sense.
  Therefore, a correct program should have some semantics
  enforcement. Also consider two counter-examples below:

````
func main() -> {
  break; // We cannot put a break outside a loop.
}
````

````
func foo(int a, int b) { ... }
func main() {
  foo("a", "b"); // Argument type mismatched.
}
````

## Overview to Compiler

So far, we know the key aspects of defining a programming language,
and now we discuss how a compiler acts on it to generate executable
binaries. The given program will undergo several components of the
compiler:

- Preprocessor: This is not included in this tutorial, and only covered here.
  All the macros will be resolved and fed to the real steps of compilation.
  Macros are those statements starts with `#` in C that allows you to manipulate
  the program in a macro way.
- Frontend: The programs are separated into a sequence of words discussed above
  by a lexer. Then this sequence of words are fed to the parser,
  and the parser will structure them into data structures in the memory.
  The snippet below shows the data structure of representing the
  return-0 example above. This data structure is called abstract syntax tree.
  Then the frontend traverses this tree to check if the semantics make sens.

````
func main() -> void {
  return 0;
}

FuncDecl
|->Name="main"
|->Args=[]
`->Body
   `->RetStmt
      `->Value=ConstInt: 0
````

- IR Generator: If the semantics make sense, the compiler then
  traverses the data structure recursively, and
  generate an intermediate representation (IR) of the program. IR
  is nearer to hardware code, and it is easier to apply some machine-independent
  optimizations. A good way to learn how a intermediate representation
  works, is to learn by examples. You can write a equivalent C code, and use the
  command in the comment to see the LLVM IR:

````
// $ clang main.c -c -S -emit-llvm
// $ ${EDITOR} main.ll

int main() {
  return 0;
}
````

- Optimizer: The optimizer applies several (mostly) machine-independent optimizations on the IR.

- Code Generator: The code generator will translate the IR into target machine
  assembly code. The key steps in this component are instruction select and
  register allocation. TODO(@were): Actually this is also my first time to
  write a compiler for a stack machine, and WebAssembly actually assumes
  infinite registers. I am not sure how to demonstrate the effects of
  register allocation.

## Depth First!

During my undergrad, I implemented the compiler in a breadth first style ---
finishing all the features of each component and go to next stage.
For example, after formalizing the whole grammar,
I wrote a universal parser to support all the frontend features.
The advantage of doing this is that each stage is highly decoupled, so
you can just focus on what you do each.

The tradeoff is that inside each module, each functionality is highly
coupled with each other, and the whole module is too large.
It is hard to write hundreds lines of code and test them at once,
Moreover,  actually when you work on a real project (not a toy like this),
you need to incrementally modify the project and embrace the ugly legacy.
Therefore, I decide to make this project depth first. We first write a set of
very simple functions, and incrementally work towards the universal set of the features.

1. Return 0
    1. Parse a function without arguments.
    2. Parse "return statement".
    3. Emit intermediate representation.
2. Hello world!
    1. Figure out how print to screen syscall is supported.
    2. Extend 1.1 to parsing arguments and parameters.
    3. Handle string literal and convert them in classes.

