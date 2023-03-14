#include <cstring>
#include <cassert>
#include <memory>

#include "ecc/ast.h"

namespace ecc {

StringLiteral::StringLiteral(int l, int c, const char * raw)
  : ExprNode(l, c, std::make_shared<BuiltinTypeNode>(l, c, BuiltinTypeNode::String)) {
  int n = strlen(raw);
  assert(raw[0] == '"');
  assert(raw[1] == '"');
  for (int i = 1; i < n - 1; ++i) {
    if (raw[i] != '\\') {
      data.push_back(raw[i]);
    } else {
      switch (raw[i + 1]) {
        case 'n': data.push_back('\n'); break;
        case '\"': data.push_back('\"'); break;
        case '\'': data.push_back('\''); break;
        case '\\': data.push_back('\\'); break;
      default:
        assert(0);
      }
      ++i;
    }
  }
}

}
