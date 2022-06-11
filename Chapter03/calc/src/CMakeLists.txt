add_calc_tool(calc
  Calc.cpp
  CodeGen.cpp
  Lexer.cpp
  Parser.cpp
  Sema.cpp
  lex.yy.c
  )
target_link_libraries(calc PRIVATE ${llvm_libs})
