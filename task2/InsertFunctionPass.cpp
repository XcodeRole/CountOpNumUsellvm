#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfo.h"
#include <string>

using namespace llvm;

namespace {
    class MyFunctionPass : public FunctionPass {
    public:
        static char ID;
        MyFunctionPass() : FunctionPass(ID) {}
        bool runOnFunction(Function &F) override {
            if (F.getName().startswith("my_mark_executed_func")){ // 如果已经插入则不用再次插入
                  return false;
            }
            LLVMContext &context = F.getParent()->getContext();
            BasicBlock &bb = F.getEntryBlock();
            IRBuilder<> bbBuilder(&bb);
            IRBuilder<> contextBuilder(context);
            Instruction *beginInst = dyn_cast<Instruction>(bb.begin()); // 所有函数的起始位置
            FunctionType *type = FunctionType::get(Type::getVoidTy(context), {Type::getInt8PtrTy(context),}, false); // 函数的返回类型和参数类型
            FunctionCallee beginFun = F.getParent()->getOrInsertFunction("my_mark_executed_func", type); // 获取函数
            CallInst *inst = contextBuilder.CreateCall(beginFun,{bbBuilder.CreateGlobalStringPtr(F.getName())}); // 构造函数
            inst->insertBefore(beginInst); // 插入标记函数
            
            auto SP = F.getSubprogram();
            // DebugLoc DL = DebugLoc::get(SP->getScopeLine(), 0, SP);
            // inst->setDebugLoc(DL); //设置DebugLoc，给debugger使用
            return false;
        }
    };
}

char MyFunctionPass::ID = 0;
static RegisterPass<MyFunctionPass> X("insert", "A pass that can check function coverage.", false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new MyFunctionPass()); });