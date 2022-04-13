#include "Hello.hpp"

using namespace llvm;
using namespace llvm::call;

bool Hello::runOnFunction(Function &F){
    errs() << "Callee\n";
    // errs().write_escaped(F.getName()) << '\n';
    return false;
}

bool Hello::test(){
    errs() << "Callee test\n";
    return false;
}       


char Hello::ID = 0;
static RegisterPass<Hello> X("callee", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

