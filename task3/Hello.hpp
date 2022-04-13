#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;
namespace llvm::call{
class Hello : public FunctionPass {
    public:
        static char ID;
        Hello() : FunctionPass(ID) {}
        bool runOnFunction(Function &F) override;
        bool test();
}; // end of struct Hello
 // end of anonymous namespace

}