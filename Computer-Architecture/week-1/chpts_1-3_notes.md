# Chapter 1: Basic Concepts and Computer Evolution

## Learning objectives

- Explain the general functions and structure of a digital computer
- Present an overview of the evolution of computer technology from early digital
  computers to the latest microprocessors
- Present an overview of the evolution of the x86 architecture
- Define embedded systems and list some of the requirements and constraints that
  various embedded systems must meet

### Organization and Architecture

- **Computer architecture** refers to attributes visible to a programmer, i.e.
  those attributes that have a direct impact on the logical execution of a
  program
  - Often used interchangeably with **instruction set architecture (ISA)**

- **Computer organization** refers to the operational units and their
  interconnections that realize the architectural specifications

### Structure and Function

- Hierarchical system
  - Set of interrelated subsystems

- Hierarchical nature of complex systems is essential to both their design and
  their description

- Designer need only deal with a particular level of the system at a time
  - Concerned with structure and function at each level

- **Structure**
  - The way in which components relate to each other

- **Function**
  - The operation of individual components as part of the structure

### Function

- There are 4 basic functions that a computer can perform
  - **Data processing**
    - Data may take a wide variety of forms and the range of processing
      requirements is broad

  - **Data storage**
    - Short-term
    - Long-term

  - **Data movement**
    - Input-output (I/O) - when data are received from or delivered to a device
      (peripheral) that is directly connected to the computer

  - **Control**
    - A control unit manages the computer's resources and orchestrates the
      performance of its functional parts in response to instructions

### Structure

#### Figure 1.1 - A Top-Down View of a Computer

- There are 4 main structural components of the computer
  - **CPU** - controls the operation of the computer and performs its data
    processing functions

  - **Main memory** - stores data

  - **I/O** - moves data between the computer and its external environment

  - **System interconnection** - some mechanism that provides for communication
    among CPU, main memory, and I/O

- Major structural components of the CPU
  - **Control unit** - controls the operation of the CPU and hence the computer

  - **Arithmetic and Logic Unit (ALU)** - Performs the computer's data
    processing function

  - **Registers** - Provide storage internal to the CPU

  - **CPU Interconnection** - Some mechanism that provides for communication
    among the control unit, ALU, and registers

### Multicore Computer Structure

- Central processing unit (CPU)
  - Portion of the computer that fetches and executes instructions
  - Consists of an ALU, a control unit, and registers
  - Referred to as a processor in a system with a single processing unit

- Core
  - An individual processing unit on a processor chip
  - May be equivalent in functionality to a CPU on a single-CPU system
  - Specialized processing units are also referred to as cores

- Processor
  - A physical piece of silicon containing one or more cores
  - Is the computer component that interprets and executes instructions
  - Referred to as a *multicore processor* if it contains multiple cores

### Cache Memory

- Multiple layers of memory between the processor and main memory
- Is smaller and faster than main memory
- Used to speed up memory access by placing in the cache data from main memory
  that is likely to be used in the near future
- A greater performance improvement may be obtained by using multiple levels of
  cache, with level 1 (L1) closest to the core and additional levels (L2, L3,
  etc.) progressively farther away from the core

#### Figure 1.2 - Simplified View of Major Elements of a Multicore Processor

#### Figure 1.3 - Motherboard with Two Intel Quad-Core Xeon Processors

#### Figure 1.4 - zEnterprise EC12 Processor Unit (PU) Chip Diagram

#### Figure 1.5 - zEnterprise EC12 Core Layout

### History of Computers - First generation: Vacuum tubes

- Vacuum tubes were used for digital logic elements and memeory

- IAS computer
  - Fundamental design approach was the stored program concept
    - Attributed to the mathematician John von Neumann
    - First publication of the idea was in 1945 for the EDVAC
  - Design began at the Princeton Institute for Advanced Studies
  - Completed in 1952
  - Prototype of all subsequent general-purpose computers

#### Figure 1.6 - IAS Structure

### Registers

- **Memory buffer register (MBR)**
  - Contains a word to be stored in memory of sent to the I/O unit
  - Or is used to receive a word from memory of from the I/O unit

- **Memory address register (MAR)**
  - Specifies the address in memory of the word to be written from or read into
    the MBR

- **Instruction Register (IR)**
  - Contains the 8-bit opcode instruction being executed

- **Instruction buffer register (IBR)**
  - Employed to temporarily hold the right-hand instruction from a word in
    memory

- **Program counter (PC)**
  - Contains the address of the next instruction pair to be fetched from memory

- **Accumulator (AC) and multiplier quotient (MQ)**
  - Employed to temporarily hold operands and results of the ALU operations

#### Figure 1.8 - Partial Flowchart of IAS Operation

#### Table 1.1 (p. 17 of textbook) - The IAS Instruction Set

### History of Computers - Second Generation: Transistors

- Smaller
- Cheaper
- Dissipates less heat than a vacuum tube
- Is a *solid state* device made from silicon
- Was invented at Bell Labs in 1947
- It was not until the late 1950s that full transistorized computers were
  commercially available

#### Table 1.2 - Computer Generations

### Second Generation Computers

- Introduced
  - More complex arithmetic and logic units
  - The use of high-level programming languages
  - Provision of *system software* which provided the ability to
    - Load programs
    - Move data to peripherals
    - Use libraries to perform common computations

#### Figure 1.9 - An IBM 7094 Configuration

### History of Computers - Third Generation: Integrated Circuits

- 1958 - the invention of the integrated circuit
- *Discrete component*
  - Single, self-contained transistor
  - Manufactured separately, packaged in their own containers, and soldered
    or wired together onto masonite-like circuit boards
  - Manufacturing process was expensive and cumbersome
- The two most important members of the third generation were the IBM System/360
  and the DEC PDP-8

#### Figure 1.10 - Fundamental Computer Elements

### Integrated Circuits

- Data storage - provided by memory cells
- Data processing - provided by gates
- Data movement - the paths among components are used to move data from memory
  to memory and from memory through gates to memory
- Control - the paths among components can carry control signals
- A computer consists of gates, memory cells, and interconnections among these
  elements
- Exploits the fact that such components as transistors, resistors, and
  conductors can be fabricated from a semiconductor such as silicon
- Many transistors can be produced at the same time on a single wafer of silicon
- Transistors can be connected with a processor metallization to form circuits

#### Figure 1.11 - Relationship Among Wafer, Chip, and Gate

#### Figure 1.12 - Growth in Transistor Count on Integrated Circuits (DRAM memory)

### Moore's Law

- 1965; Gordon Moore - co-founder of Intel
- Observed number of transistors that could be put on a chip was doubling every
  year
- The pace slowed to a doubling every 18 months in the 1970s but has sustained
  that rate ever since

- Consequences of Moore's Law:
  - The cost of computer logic and memory circuitry has fallen at a dramatic rate
  - The electrical path length is shortened, increasing operation speed
  - Computer becomes smaller and is more convenient to use in a variety of
    environments
  - Reduction in power and cooling equipment
  - Fewer inter-chip connections
