#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopPass.h"

namespace {
    using ULLONG = unsigned long long;

    struct LoopCntr : public llvm::LoopPass {
        static char ID;
        static ULLONG countOfObjects; 

        LoopCntr() : LoopPass(this->ID) {}
        ~LoopCntr() {
            llvm::errs() << "You have "
                << this->countOfObjects << " loop(s) in your project!\n";
        }
        virtual bool runOnLoop(llvm::Loop* L, llvm::LPPassManager& LPM) override {
            ++this->countOfObjects;
            return false;
        }
    }; // end od LoopCntr struct
    
    ULLONG LoopCntr::countOfObjects = 0;
    char LoopCntr::ID = 0;
    llvm::RegisterPass< LoopCntr > X("CountLoops", "Counts all loops", false, false);
} // end of anonymous namespace

