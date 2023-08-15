# Parser

**parse** v.: Analyze the text grammarly.

The purpose of the parser is to represent the program text
in data structures that can be understood by computers.
This is a recursive data structure called abstract syntax tree (AST).

Consider a more complicated example. Say we have such a piece of program below:

````
let i32 n = 128;
for i in 0..n {
  a[i] = i * i;
}
````

It should be represented as something like this:

````
Declare
|->Name="n"
|->Type=i32
`->Init=ConstInt
        `->Value=128
ForLoop
|->Declare
|  |->Name="i"
|  |->Type=i32
|  `->Init=ConstInt
|          `->Value=0
|->End=ConstInt
|      `->Value=128
`->Body=CompoundStmt
        |->Assignment
	|->LHS=ArrayAccess
	|      |->Array=Variable
	|      |        `->Name="a"
	|      `->Index=Variable
	|               `->Name="i"
        `->RHS=BinaryOp
	       |->Op="*"
	       |->LHS=Variable
	       |       `->Name="i"
	       `->RHS=Variable
		      `->Name="i"
````

To get such data structure representation, we need to first
define the syntax/grammar of the program, and then write a
program accepts this syntax rules.

