# Introduction

In the last section, the language manual is specified.
Still, it is a big engineering work to accomplish.
Therefore, let's break it down to pieces.

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
binaries.

## Breadth First!

