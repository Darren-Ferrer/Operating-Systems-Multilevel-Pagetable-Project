# Operating-Systems-Multilevel-Pagetable-Project

This program creates a N-level page tree.
It reads a file consisting of memory accesses for a single process, constructs the tree, and assigns frame indices to each page.

Flags:
  -n N 
    processes only N memory references, if not present then processes all addresses
  -o mode
    modes:
      bitmasks: prints out the bitmasks for each level
      logical2physical: prints the logical address and the physical address it was mapped to
      page2frame:page numbers of each level are printed and follwed by the frame number
      offset:
  
 Running the code:
  ./pagetable *flags* trace.sample.tr *bits for each page table*
  
  example:
    ./pagetable -n 20 -o offset trace.sample.tr 4 5 8
    prints out the first 20 memory references and shows the offsets of them. And creates pagetable with 3 levels with 4 bits, 5 bits, and 8 bits respectively
    
   Once the prgram has run, it will create a new file in the working directory.
  
