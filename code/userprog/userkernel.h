// userkernel.h
//	Global variables for the Nachos kernel, for the assignment
//	supporting running user programs.
//
//	The kernel supporting user programs is a version of the 
//	basic multithreaded kernel.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef USERKERNEL_H  
#define USERKERNEL_H

#include "kernel.h"
#include "filesys.h"
#include "machine.h"
#include "synchdisk.h"
#include "addrspace.h"

class FrameInfoEntry {
public:
    bool valid; //if being used
    bool lock;
    AddrSpace *addrSpace; //which process is using this page
    unsigned int vpn; //which virtual page of the process is stored in
                      //this page
};
enum SwapType {
	Random,
	FIFO
};
class VirtualMemoryManager {
public: 
	VirtualMemoryManager() {
//		cout << "VirtualMemoryManager initial\n";
	};
	void PageFaultHandler(SwapType swapType, unsigned int vpn);
	void SwapPage(int victim, unsigned int vpn);
	int victim;
};

//End-Modified

class SynchDisk;
class UserProgKernel : public ThreadedKernel {
  public:
    UserProgKernel(int argc, char **argv);
				// Interpret command line arguments
    ~UserProgKernel();		// deallocate the kernel

    void Initialize();		// initialize the kernel 

    void Run();			// do kernel stuff 

    void SelfTest();		// test whether kernel is working

// These are public for notational convenience.
    Machine *machine;
    FileSystem *fileSystem;

#ifdef FILESYS
    SynchDisk *synchDisk;
#endif // FILESYS

//[OS=Project3]Modified
    SynchDisk *swapDisk;
	VirtualMemoryManager *memManager;
	SwapType swapType;
	FrameInfoEntry *frameTable;
	FrameInfoEntry *swapTable;
//End-Modified


  private:
    bool debugUserProg;		// single step user program
	Thread* t[10];
	char*	execfile[10];
	int	execfileNum;
};

#endif //USERKERNEL_H
