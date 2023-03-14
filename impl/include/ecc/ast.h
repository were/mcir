#pragma once

#include <memory>
#include <vector>

namespace ecc {

// TODO(@were): It is highly recommended to make a enum for each sub-class
//              for better performance.
enum NodeTy {
};

struct ASTNode {
  /*
   * \brief The line number of this AST node derived from.
   */
  int lineno;
  /*
   * \brief The column number of this AST node derived from.
   */
  int colno;

  ASTNode(int l, int c) : lineno(l), colno(c) {}
};

struct CompoundStmtNode;
struct TypeNode;
struct VariableNode;

/*!
 * \brief A function implementation.
 */
struct FunctionNode : ASTNode {
  using ArgListTy = std::vector<std::shared_ptr<VariableNode>>;
  /*!
   * \brief The type and name of this function.
   */
  std::shared_ptr<VariableNode> func;
  /*!
   * \brief The argument list declared.
   */
  ArgListTy arg_list;
  /*!
   * \brief The function body.
   */
  std::unique_ptr<CompoundStmtNode> body;

  FunctionNode(int l, int c,
               VariableNode *func_, const ArgListTy &arg_list_,
               CompoundStmtNode *body_)
    : ASTNode(l, c), func(func_), arg_list(arg_list_), body(body_) {}
};

struct StatementNode;

/*!
 * \brief A compound statement node.
 */
struct CompoundStmtNode : ASTNode {
  /*!
   * \brief The statements in this compound statement scope.
   */
  std::vector<std::unique_ptr<ASTNode>> statements;

  CompoundStmtNode(const std::vector<ASTNode*> &stmt);
};

/*!
 * \brief The super class of a type.
 */
struct TypeNode : ASTNode {
  TypeNode(int l, int c) : ASTNode(l, c) {}
};

/*
 * \brief The builtin type.
 */
struct BuiltinTypeNode : TypeNode {
  enum TypeCode {
    Void,
    Bool,
    Char,
    Int,
    String,
  };
  /*!
   * \brief The type indicator.
   */
  TypeCode code;

  BuiltinTypeNode(int l, int c, TypeCode tc) : TypeNode(l, c), code(tc) {}
};

struct ExprNode;
struct VariableNode;

/*!
 * Declaring a variable.
 */
struct VarDeclNode : ASTNode {
  /*!
   * \brief The type and name of the variable declared.
   */
  std::shared_ptr<VariableNode> variable;
  /*!
   * \brief The initial value of this variable.
   */
  std::unique_ptr<ExprNode> initializer;

  VarDeclNode(int l, int c, VariableNode *var, ExprNode *init)
    : ASTNode(l, c), variable(var), initializer(init) {}
};

/*!
 * \brief Expression node.
 */
struct ExprNode : ASTNode {
  /*!
   * \brief The type of this expression.
   */
  std::shared_ptr<TypeNode> ty;

  ExprNode(int l, int c, std::shared_ptr<TypeNode> ty_) :
    ASTNode(l, c), ty(ty_) {}
};

/*!
 * \brief A variable instance.
 */
struct VariableNode : ExprNode {
  /*!
   * \brief The name of the variable.
   */
  std::string id;

  VariableNode(int l, int c, std::shared_ptr<TypeNode> ty_,
               const std::string &id_)
    : ExprNode(l, c, ty_), id(id_) {}
};

struct StringLiteral : ExprNode {
  /*!
   * \brief The raw buffer of the string.
   */
  std::string data;
  /*!
   * \brief Parse the string wrapped by a pair of ".
   */
  StringLiteral(int l, int c, const char *raw);
};

/*!
 * \brief Call a function.
 */
struct FuncCallNode : ExprNode {
  /*!
   * \brief The function to be called.
   */
  std::shared_ptr<FunctionNode> callee;
  /*!
   * \brief Arguments fill into the argument list.
   */
  std::vector<std::unique_ptr<ExprNode>> args;

};

/*!
 * \brief Binary operations.
 */
struct BinaryExprNode : ExprNode {
  enum OpCode {
    Add,
    Sub,
    Mul,
    Div,
    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    LogicAnd,
    LogicOr,
    CmpEq,
    CmpNeq,
  };
  /*!
   * \brief The LHS of the op.
   */
  std::unique_ptr<ExprNode> a;
  /*!
   * \brief The RHS of the op.
   */
  std::unique_ptr<ExprNode> b;
};

}
