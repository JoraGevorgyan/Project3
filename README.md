# **A simple LLVM Pass**
#
#
## General info
```txt
    This is a simple LLVM Pass which will count all loops in given bit code (file.bc)
```

### *I used this* **[llvm-project](https://github.com/JoraGevorgyan/llvm-project.git)**

## **Setup**
```txt
    To do this, you need to follow these steps
```
### step 1
```txt
    * clone this repo to your local machine
    * Copy the LoopCntr file into PathToLLVMProject/llvm/lib/Transforms/
```
### step 2
```txt 
    add following line into PathToLLVMProject/llvm/lib/Transforms/CMakeLists.txt 
        add_subdirectory(LoopCntr)
```
### step 3
```txt
    rebuild your llvm-project
```
### step 4
```txt
    run the pass with following command
        $ PathToLLVMProject/build/bin/opt -load \
            PathToLLVMProject/build/lib/LLVMLoopCntr.so \
            -CountLoops < file.bc > /dev/null
```

