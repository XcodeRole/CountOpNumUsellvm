#include "CallHello.hpp"
#include "Hello.hpp"

using namespace llvm;
using namespace llvm::call;

void CallHello::getAnalysisUsage (AnalysisUsage &AU) const{
    AU.addRequired<Hello>();
    AU.setPreservesAll();
}

bool CallHello::runOnFunction(Function &F){
    Hello &Hel = getAnalysis<Hello>();

    Hel.test();
    // Hello::test();静态方法
    errs() << "Caller\n";

    errs().write_escaped(F.getName())<<"\n";
    return false;
}
 // end of struct Hello
  // end of anonymous namespace

char CallHello::ID = 0;
static RegisterPass<CallHello> Y("caller", "lkmk",
                             false,
                             false);

