#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"


using namespace llvm;

namespace llvm::call{
class CallHello : public FunctionPass {
public:
    static char ID;
    CallHello() : FunctionPass(ID) {}

    void getAnalysisUsage (AnalysisUsage &AU) const override;

    bool runOnFunction(Function &F) override;
}; // end of struct Hello
  // end of anonymous namespace
}
