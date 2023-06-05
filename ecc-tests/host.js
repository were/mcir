fs = require('fs');

wasm_binary = process.argv[2]

fd = fs.readFileSync(wasm_binary, undefined)

input_buffer = []

process.stdin.on('data', function (data) {
  input_buffer.push(data)
})

function print_int(x) {
  process.stdout.write(x.toString())
}

memory = null
i8view = null

function print_str(offset, len) {
  for (i = 0; i < len; ++i) {
    process.stdout.write(String.fromCharCode(i8view[offset + i]))
  }
}

__linear_memory = new WebAssembly.Memory({initial: 65536})
__stack_pointer = new WebAssembly.Global({value: "i32", mutable: true}, 0)

imports = {
  env: {
    print_int: print_int,
    print_str: print_str,
    __linear_memory: __linear_memory,
    __stack_pointer: __stack_pointer,
  }
}

WebAssembly.instantiate(fd, imports).then(function (result) {

  // memory = result.instance.exports.memory
  i8view = new Int8Array(__linear_memory.buffer)

  result.instance.exports.main(0, 0)
})

