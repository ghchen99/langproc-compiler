#ifndef H_AST
#define H_AST

#include "ast/ast_arithOps.hpp"
#include "ast/ast_assignOps.hpp"
#include "ast/ast_base.hpp"
#include "ast/ast_bitOps.hpp"
#include "ast/ast_conditions.hpp"
#include "ast/ast_condOps.hpp"
#include "ast/ast_funcs.hpp"
#include "ast/ast_logicOps.hpp"
#include "ast/ast_loops.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_stmt.hpp"
#include "ast/ast_unary.hpp"


extern const Base *parseAST();

#endif
