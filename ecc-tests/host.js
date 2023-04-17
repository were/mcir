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

function print_string(offset, len) {
  for (i = 0; i < len; ++i) {
    process.stdout.write(String.fromCharCode(i8view[offset + i]))
  }
}

imports = {
  host: {
    print_int: print_int,
    print_string: print_string
  }
}

WebAssembly.instantiate(fd, imports).then(function (result) {

  memory = result.instance.exports.memory
  i8view = new Int8Array(memory.buffer)

  result.instance.exports.run()
})

