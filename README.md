# Modern Compiler Implemented in Rust


## Tutorial

In this repo, I will build my own language targeting WebAssembly.

- [Lang. Manual](./writeup/00-manual.md): A language manual of which the compiler to develope.
- [Introduction](./writeup/01-intro.md): A introduction to the flow of a typical compiler.
- [Parser](./writeup/02-parser.md): Organize the language in a computer-understandable structure.
- [Intermediate Representation](./writeup/03-ir.md): LLVM: A bridge b/w parser and assembly code.
- [Optimization 1: SSA](./writeup/04-ssa.md): The optimization of optimization.
- [Optimization 2: CSE](./writeup/05-cse.md): A simple application of SSA.
- [Optimization 3: Const Propagation](./writeup/06-const-prop.md): 

## Reference Implementation

A reference Rust implementation is available at the [sub-repo](https://github.com/were/ecc-rust).
Test cases are available at the `tests` folder.
If you want to develop your own compiler,
you no longer need to design test cases from scratch.

