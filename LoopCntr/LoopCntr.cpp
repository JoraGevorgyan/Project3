#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"

namespace {
    class LoopCntr : public llvm::FunctionPass {
        public:
            static char ID;
            LoopCntr() : FunctionPass(ID) {}

            void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
                AU.setPreservesCFG();
                AU.addRequired<llvm::LoopInfoWrapperPass>();
            }

            virtual bool runOnFunction(llvm::Function& F) override {
                llvm::LoopInfoBase< llvm::BasicBlock, llvm::Loop > *curLoopBase
                    = &getAnalysis< llvm::LoopInfoWrapperPass >().getLoopInfo();

                const std::vector< llvm::Loop*, std::allocator< llvm::Loop* >>* topLoops 
                    = &curLoopBase->getTopLevelLoops();

                llvm::errs() << "Function '" << F.getName()
                    << "' has " << topLoops->size() << " top level loop(s).\n";
                size_t loopNum = 1;
                for(auto it = topLoops->begin(); it != topLoops->end(); ++it, ++loopNum) {
                    llvm::errs() << loopNum << ": ";
                    this->countIntagratedLoops(*it);
                }

                llvm::errs() << "\n";

                return false;
            }

        private:
            void countIntagratedLoops(llvm::Loop* L, size_t loopLevel = 1) {
                const std::vector< llvm::Loop*, std::allocator< llvm::Loop* >>* loops
                    = &L->getSubLoops();

                llvm::errs() << loops->size() << " intagrated loop(s).\n";
                
                size_t curLoopNum = 1;
                std::string designStr(loopLevel * 4, '=');

                for(auto it = loops->begin(), endIt = loops->end(); it != endIt; ++it) {
                    llvm::errs() << designStr << " " << curLoopNum++ << ": ";
                    countIntagratedLoops(*it, loopLevel + 1);
                }
            }

    }; // end of LoopCntr struct

    char LoopCntr::ID = 0;
    llvm::RegisterPass< LoopCntr > X("CountLoops", "Counts all loops of each function",
            false, false);
} // end of anonymous namespace

