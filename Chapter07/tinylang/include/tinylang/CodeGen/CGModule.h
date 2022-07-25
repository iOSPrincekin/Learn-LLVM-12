#ifndef TINYLANG_CODEGEN_CGMODULE_H
#define TINYLANG_CODEGEN_CGMODULE_H

#include "tinylang/AST/AST.h"
#include "tinylang/AST/ASTContext.h"
#include "tinylang/CodeGen/CGDebugInfo.h"
#include "tinylang/CodeGen/CGTBAA.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace tinylang {

class CGModule {
  ASTContext &ASTCtx;
  llvm::Module *M;

  ModuleDeclaration *Mod;

  llvm::DenseMap<TypeDeclaration *, llvm::Type *> TypeCache;

  // Repository of global objects.
  llvm::DenseMap<Decl *, llvm::GlobalObject *> Globals;

  CGTBAA TBAA;
  std::unique_ptr<CGDebugInfo> DebugInfo;

public:
  llvm::Type *VoidTy;
  llvm::Type *Int1Ty;
  llvm::Type *Int8Ty;
  llvm::Type *Int16Ty;
  llvm::Type *Int32Ty;
  llvm::Type *Int64Ty;
  llvm::Constant *Int1Zero;
  llvm::Constant *Int8Zero;
  llvm::Constant *Int16Zero;
  llvm::Constant *Int32Zero;
  llvm::Constant *Int64Zero;



public:
  CGModule(ASTContext &ASTCtx, llvm::Module *M);
  void initialize();

  ASTContext &getASTCtx() { return ASTCtx; }
  llvm::LLVMContext &getLLVMCtx() {
    return M->getContext();
  }
  llvm::Module *getModule() { return M; }
  ModuleDeclaration *getModuleDeclaration() { return Mod; }

  void decorateInst(llvm::Instruction *Inst,
                    TypeDeclaration *Type);

  llvm::Type *convertType(TypeDeclaration *Ty);
    
  llvm::Constant *getDefaultConstant(llvm::Type *T);
    
  std::string mangleName(Decl *D);

  llvm::GlobalObject *getGlobal(Decl *);

  CGDebugInfo *getDbgInfo() {
    return DebugInfo.get();
  }

  void applyLocation(llvm::Instruction *Inst, llvm::SMLoc Loc);

  void run(ModuleDeclaration *Mod);
};
} // namespace tinylang
#endif
