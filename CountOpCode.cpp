#include <map>
#include <string>
#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;
using namespace std;

#define DEBUG_TYPE "counter"
STATISTIC(NumOp , "The # of times I fetch mem");

namespace{
    class CountOpCode : public FunctionPass{
    public:
        static char ID;
        CountOpCode():FunctionPass(ID){};
        virtual  bool runOnFunction(Function &F) override{
            for (auto bb = F.begin(), e = F.end();bb!=e;++bb){
                for ( auto inst = bb->begin(),ie = bb->end();inst!=ie;++inst){
                    // errs()<<inst->getOpcodeName()<<"\n";
                    string instName=inst->getOpcodeName();
                    map<string,int>::iterator si_it=countermap.find(instName);
                    if (si_it==countermap.end()){
                        countermap.insert(map<string,int>::value_type(instName,1));
                    }else{
                        countermap[instName]++;
                    }
                }
            }
            // outs()<<NumMem<<"\n";
            for (auto it=countermap.begin();it!=countermap.end();it++){
                errs()<<it->first<<" "<<it->second<<"\n";
            }
            return false;
        }
        // virtual bool doFinalization(Function &F){
        //     for (auto it=countermap.begin();it!=countermap.end();it++){
        //         errs()<<it->first<<" "<<it->second<<"\n";
        //     }
        //     return false;
        // }
    private:
        map<string,int> countermap;
    };
};
char CountOpCode::ID=0;
static RegisterPass<CountOpCode> X("CountOpCode", "Print instruction Name", false, false);

// static void registerSkeletonPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) 
// {
//   PM.add(new InstruFuncPass());
// }

// static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerSkeletonPass);
