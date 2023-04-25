# Introduction

In the last section, the language manual is specified.
Still, it is a big engineering work to accomplish.
Therefore, let's break it down to pieces.

How a program is lowered into executable binaries? A programming language
is a "language" because it has all the aspects of a language:

- Words: The program is separated into a sequence of `words`. In compiler
  engineering, these `words` are called `tokens`. For such a program below,
  it will be separated into `func`, `main`, `(`, `)`, `->`, `void`, `{`,
  `return`, `0`, and `}`.

````
func main() -> void {
  return 0;
}
````

- Grammar: Then these words are structured in some grammar structure.

## Overview to Compiler

## Breadth First!

