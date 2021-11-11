/*
    Name 1: Masaad Khan
    UTEID 1: mak4668
*/

/***************************************************************/
/*                                                             */
/*   LC-3b Simulator                                           */
/*                                                             */
/*   EE 460N                                                   */
/*   The University of Texas at Austin                         */
/*                                                             */
/***************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lc3bsim3-good.h"
#include <stdbool.h>

/***************************************************************/
/*                                                             */
/* Files:  ucode        Microprogram file                      */
/*         isaprogram   LC-3b machine language program file    */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* These are the functions you'll have to write.               */
/***************************************************************/

void eval_micro_sequencer();
void cycle_memory();
void eval_bus_drivers();
void drive_bus();
void latch_datapath_values();

/***************************************************************/
/* A couple of useful definitions.                             */
/***************************************************************/
#define FALSE 0
#define TRUE  1

/***************************************************************/
/* Use this to avoid overflowing 16 bits on the bus.           */
/***************************************************************/
#define Low16bits(x) ((x) & 0xFFFF)

/***************************************************************/
/* Definition of the control store layout.                     */
/***************************************************************/
#define CONTROL_STORE_ROWS 64
#define INITIAL_STATE_NUMBER 18

/***************************************************************/
/* Definition of bit order in control store word.              */
/***************************************************************/
enum CS_BITS {                                                  
    IRD,
    COND1, COND0,
    J5, J4, J3, J2, J1, J0,
    LD_MAR,
    LD_MDR,
    LD_IR,
    LD_BEN,
    LD_REG,
    LD_CC,
    LD_PC,
    GATE_PC,
    GATE_MDR,
    GATE_ALU,
    GATE_MARMUX,
    GATE_SHF,
    PCMUX1, PCMUX0,
    DRMUX,
    SR1MUX,
    ADDR1MUX,
    ADDR2MUX1, ADDR2MUX0,
    MARMUX,
    ALUK1, ALUK0,
    MIO_EN,
    R_W,
    DATA_SIZE,
    LSHF1,
    CONTROL_STORE_BITS
} CS_BITS;

/***************************************************************/
/* Functions to get at the control bits.                       */
/***************************************************************/
int GetIRD(int *x)           { return(x[IRD]); }
int GetCOND(int *x)          { return((x[COND1] << 1) + x[COND0]); }
int GetJ(int *x)             { return((x[J5] << 5) + (x[J4] << 4) +
				      (x[J3] << 3) + (x[J2] << 2) +
				      (x[J1] << 1) + x[J0]); }
int GetLD_MAR(int *x)        { return(x[LD_MAR]); }
int GetLD_MDR(int *x)        { return(x[LD_MDR]); }
int GetLD_IR(int *x)         { return(x[LD_IR]); }
int GetLD_BEN(int *x)        { return(x[LD_BEN]); }
int GetLD_REG(int *x)        { return(x[LD_REG]); }
int GetLD_CC(int *x)         { return(x[LD_CC]); }
int GetLD_PC(int *x)         { return(x[LD_PC]); }
int GetGATE_PC(int *x)       { return(x[GATE_PC]); }
int GetGATE_MDR(int *x)      { return(x[GATE_MDR]); }
int GetGATE_ALU(int *x)      { return(x[GATE_ALU]); }
int GetGATE_MARMUX(int *x)   { return(x[GATE_MARMUX]); }
int GetGATE_SHF(int *x)      { return(x[GATE_SHF]); }
int GetPCMUX(int *x)         { return((x[PCMUX1] << 1) + x[PCMUX0]); }
int GetDRMUX(int *x)         { return(x[DRMUX]); }
int GetSR1MUX(int *x)        { return(x[SR1MUX]); }
int GetADDR1MUX(int *x)      { return(x[ADDR1MUX]); }
int GetADDR2MUX(int *x)      { return((x[ADDR2MUX1] << 1) + x[ADDR2MUX0]); }
int GetMARMUX(int *x)        { return(x[MARMUX]); }
int GetALUK(int *x)          { return((x[ALUK1] << 1) + x[ALUK0]); }
int GetMIO_EN(int *x)        { return(x[MIO_EN]); }
int GetR_W(int *x)           { return(x[R_W]); }
int GetDATA_SIZE(int *x)     { return(x[DATA_SIZE]); } 
int GetLSHF1(int *x)         { return(x[LSHF1]); }

/***************************************************************/
/* The control store rom.                                      */
/***************************************************************/
int CONTROL_STORE[CONTROL_STORE_ROWS][CONTROL_STORE_BITS];

/***************************************************************/
/* Main memory.                                                */
/***************************************************************/
/* MEMORY[A][0] stores the least significant byte of word at word address A
   MEMORY[A][1] stores the most significant byte of word at word address A 
   There are two write enable signals, one for each byte. WE0 is used for 
   the least significant byte of a word. WE1 is used for the most significant 
   byte of a word. */

#define WORDS_IN_MEM    0x08000 
#define MEM_CYCLES      5
int MEMORY[WORDS_IN_MEM][2];

/***************************************************************/

/***************************************************************/

/***************************************************************/
/* LC-3b State info.                                           */
/***************************************************************/
#define LC_3b_REGS 8

int RUN_BIT;	/* run bit */
int BUS;	/* value of the bus */

typedef struct System_Latches_Struct{

int PC,		/* program counter */
    MDR,	/* memory data register */
    MAR,	/* memory address register */
    IR,		/* instruction register */
    N,		/* n condition bit */
    Z,		/* z condition bit */
    P,		/* p condition bit */
    BEN;        /* ben register */

int READY;	/* ready bit */
  /* The ready bit is also latched as you dont want the memory system to assert it 
     at a bad point in the cycle*/

int REGS[LC_3b_REGS]; /* register file. */

int MICROINSTRUCTION[CONTROL_STORE_BITS]; /* The microintruction */

int STATE_NUMBER; /* Current State Number - Provided for debugging */ 
} System_Latches;

/* Data Structure for Latch */

System_Latches CURRENT_LATCHES, NEXT_LATCHES;

/***************************************************************/
/* A cycle counter.                                            */
/***************************************************************/
int CYCLE_COUNT;

/***************************************************************/
/*                                                             */
/* Procedure : help                                            */
/*                                                             */
/* Purpose   : Print out a list of commands.                   */
/*                                                             */
/***************************************************************/
void help() {                                                    
    printf("----------------LC-3bSIM Help-------------------------\n");
    printf("go               -  run program to completion       \n");
    printf("run n            -  execute program for n cycles    \n");
    printf("mdump low high   -  dump memory from low to high    \n");
    printf("rdump            -  dump the register & bus values  \n");
    printf("?                -  display this help menu          \n");
    printf("quit             -  exit the program                \n\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : cycle                                           */
/*                                                             */
/* Purpose   : Execute a cycle                                 */
/*                                                             */
/***************************************************************/
void cycle() {                                                

  eval_micro_sequencer();   
  cycle_memory();
  eval_bus_drivers();
  drive_bus();
  latch_datapath_values();

  CURRENT_LATCHES = NEXT_LATCHES;

  CYCLE_COUNT++;
}

/***************************************************************/
/*                                                             */
/* Procedure : run n                                           */
/*                                                             */
/* Purpose   : Simulate the LC-3b for n cycles.                 */
/*                                                             */
/***************************************************************/
void run(int num_cycles) {                                      
    int i;

    if (RUN_BIT == FALSE) {
	printf("Can't simulate, Simulator is halted\n\n");
	return;
    }

    printf("Simulating for %d cycles...\n\n", num_cycles);
    for (i = 0; i < num_cycles; i++) {
	if (CURRENT_LATCHES.PC == 0x0000) {
	    RUN_BIT = FALSE;
	    printf("Simulator halted\n\n");
	    break;
	}
	cycle();
    }
}

/***************************************************************/
/*                                                             */
/* Procedure : go                                              */
/*                                                             */
/* Purpose   : Simulate the LC-3b until HALTed.                 */
/*                                                             */
/***************************************************************/
void go() {                                                     
    if (RUN_BIT == FALSE) {
	printf("Can't simulate, Simulator is halted\n\n");
	return;
    }

    printf("Simulating...\n\n");
    while (CURRENT_LATCHES.PC != 0x0000)
	cycle();
    RUN_BIT = FALSE;
    printf("Simulator halted\n\n");
}

/***************************************************************/ 
/*                                                             */
/* Procedure : mdump                                           */
/*                                                             */
/* Purpose   : Dump a word-aligned region of memory to the     */
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void mdump(FILE * dumpsim_file, int start, int stop) {          
    int address; /* this is a byte address */

    printf("\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
    printf("-------------------------------------\n");
    for (address = (start >> 1); address <= (stop >> 1); address++)
	printf("  0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
    printf("\n");

    /* dump the memory contents into the dumpsim file */
    fprintf(dumpsim_file, "\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
    fprintf(dumpsim_file, "-------------------------------------\n");
    for (address = (start >> 1); address <= (stop >> 1); address++)
	fprintf(dumpsim_file, " 0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
    fprintf(dumpsim_file, "\n");
    fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : rdump                                           */
/*                                                             */
/* Purpose   : Dump current register and bus values to the     */   
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void rdump(FILE * dumpsim_file) {                               
    int k; 

    printf("\nCurrent register/bus values :\n");
    printf("-------------------------------------\n");
    printf("Cycle Count  : %d\n", CYCLE_COUNT);
    printf("PC           : 0x%.4x\n", CURRENT_LATCHES.PC);
    printf("IR           : 0x%.4x\n", CURRENT_LATCHES.IR);
    printf("STATE_NUMBER : 0x%.4x\n\n", CURRENT_LATCHES.STATE_NUMBER);
    printf("BUS          : 0x%.4x\n", BUS);
    printf("MDR          : 0x%.4x\n", CURRENT_LATCHES.MDR);
    printf("MAR          : 0x%.4x\n", CURRENT_LATCHES.MAR);
    printf("CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
    printf("Registers:\n");
    for (k = 0; k < LC_3b_REGS; k++)
	printf("%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
    printf("\n");

    /* dump the state information into the dumpsim file */
    fprintf(dumpsim_file, "\nCurrent register/bus values :\n");
    fprintf(dumpsim_file, "-------------------------------------\n");
    fprintf(dumpsim_file, "Cycle Count  : %d\n", CYCLE_COUNT);
    fprintf(dumpsim_file, "PC           : 0x%.4x\n", CURRENT_LATCHES.PC);
    fprintf(dumpsim_file, "IR           : 0x%.4x\n", CURRENT_LATCHES.IR);
    fprintf(dumpsim_file, "STATE_NUMBER : 0x%.4x\n\n", CURRENT_LATCHES.STATE_NUMBER);
    fprintf(dumpsim_file, "BUS          : 0x%.4x\n", BUS);
    fprintf(dumpsim_file, "MDR          : 0x%.4x\n", CURRENT_LATCHES.MDR);
    fprintf(dumpsim_file, "MAR          : 0x%.4x\n", CURRENT_LATCHES.MAR);
    fprintf(dumpsim_file, "CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
    fprintf(dumpsim_file, "Registers:\n");
    for (k = 0; k < LC_3b_REGS; k++)
	fprintf(dumpsim_file, "%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
    fprintf(dumpsim_file, "\n");
    fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : get_command                                     */
/*                                                             */
/* Purpose   : Read a command from standard input.             */  
/*                                                             */
/***************************************************************/
void get_command(FILE * dumpsim_file) {                         
    char buffer[20];
    int start, stop, cycles;

    printf("LC-3b-SIM> ");

    scanf("%s", buffer);
    printf("\n");

    switch(buffer[0]) {
    case 'G':
    case 'g':
	go();
	break;

    case 'M':
    case 'm':
	scanf("%i %i", &start, &stop);
	mdump(dumpsim_file, start, stop);
	break;

    case '?':
	help();
	break;
    case 'Q':
    case 'q':
	printf("Bye.\n");
	exit(0);

    case 'R':
    case 'r':
	if (buffer[1] == 'd' || buffer[1] == 'D')
	    rdump(dumpsim_file);
	else {
	    scanf("%d", &cycles);
	    run(cycles);
	}
	break;

    default:
	printf("Invalid Command\n");
	break;
    }
}

/***************************************************************/
/*                                                             */
/* Procedure : init_control_store                              */
/*                                                             */
/* Purpose   : Load microprogram into control store ROM        */ 
/*                                                             */
/***************************************************************/
void init_control_store(char *ucode_filename) {                 
    FILE *ucode;
    int i, j, index;
    char line[200];

    printf("Loading Control Store from file: %s\n", ucode_filename);

    /* Open the micro-code file. */
    if ((ucode = fopen(ucode_filename, "r")) == NULL) {
	printf("Error: Can't open micro-code file %s\n", ucode_filename);
	exit(-1);
    }

    /* Read a line for each row in the control store. */
    for(i = 0; i < CONTROL_STORE_ROWS; i++) {
	if (fscanf(ucode, "%[^\n]\n", line) == EOF) {
	    printf("Error: Too few lines (%d) in micro-code file: %s\n",
		   i, ucode_filename);
	    exit(-1);
	}

	/* Put in bits one at a time. */
	index = 0;

	for (j = 0; j < CONTROL_STORE_BITS; j++) {
	    /* Needs to find enough bits in line. */
	    if (line[index] == '\0') {
		printf("Error: Too few control bits in micro-code file: %s\nLine: %d\n",
		       ucode_filename, i);
		exit(-1);
	    }
	    if (line[index] != '0' && line[index] != '1') {
		printf("Error: Unknown value in micro-code file: %s\nLine: %d, Bit: %d\n",
		       ucode_filename, i, j);
		exit(-1);
	    }

	    /* Set the bit in the Control Store. */
	    CONTROL_STORE[i][j] = (line[index] == '0') ? 0:1;
	    index++;
	}

	/* Warn about extra bits in line. */
	if (line[index] != '\0')
	    printf("Warning: Extra bit(s) in control store file %s. Line: %d\n",
		   ucode_filename, i);
    }
    printf("\n");
}

/************************************************************/
/*                                                          */
/* Procedure : init_memory                                  */
/*                                                          */
/* Purpose   : Zero out the memory array                    */
/*                                                          */
/************************************************************/
void init_memory() {                                           
    int i;

    for (i=0; i < WORDS_IN_MEM; i++) {
	MEMORY[i][0] = 0;
	MEMORY[i][1] = 0;
    }
}

/**************************************************************/
/*                                                            */
/* Procedure : load_program                                   */
/*                                                            */
/* Purpose   : Load program and service routines into mem.    */
/*                                                            */
/**************************************************************/
void load_program(char *program_filename) {                   
    FILE * prog;
    int ii, word, program_base;

    /* Open program file. */
    prog = fopen(program_filename, "r");
    if (prog == NULL) {
	printf("Error: Can't open program file %s\n", program_filename);
	exit(-1);
    }

    /* Read in the program. */
    if (fscanf(prog, "%x\n", &word) != EOF)
	program_base = word >> 1;
    else {
	printf("Error: Program file is empty\n");
	exit(-1);
    }

    ii = 0;
    while (fscanf(prog, "%x\n", &word) != EOF) {
	/* Make sure it fits. */
	if (program_base + ii >= WORDS_IN_MEM) {
	    printf("Error: Program file %s is too long to fit in memory. %x\n",
		   program_filename, ii);
	    exit(-1);
	}

	/* Write the word to memory array. */
	MEMORY[program_base + ii][0] = word & 0x00FF;
	MEMORY[program_base + ii][1] = (word >> 8) & 0x00FF;
	ii++;
    }

    if (CURRENT_LATCHES.PC == 0) CURRENT_LATCHES.PC = (program_base << 1);

    printf("Read %d words from program into memory.\n\n", ii);
}

/***************************************************************/
/*                                                             */
/* Procedure : initialize                                      */
/*                                                             */
/* Purpose   : Load microprogram and machine language program  */ 
/*             and set up initial state of the machine.        */
/*                                                             */
/***************************************************************/
void initialize(char *ucode_filename, char *program_filename, int num_prog_files) { 
    int i;
    init_control_store(ucode_filename);

    init_memory();
    for ( i = 0; i < num_prog_files; i++ ) {
	load_program(program_filename);
	while(*program_filename++ != '\0');
    }
    CURRENT_LATCHES.Z = 1;
    CURRENT_LATCHES.STATE_NUMBER = INITIAL_STATE_NUMBER;
    memcpy(CURRENT_LATCHES.MICROINSTRUCTION, CONTROL_STORE[INITIAL_STATE_NUMBER], sizeof(int)*CONTROL_STORE_BITS);

    NEXT_LATCHES = CURRENT_LATCHES;

    RUN_BIT = TRUE;
}

/***************************************************************/
/*                                                             */
/* Procedure : main                                            */
/*                                                             */
/***************************************************************/
int main(int argc, char *argv[]) {                              
    FILE * dumpsim_file;

    /* Error Checking */
    if (argc < 3) {
	printf("Error: usage: %s <micro_code_file> <program_file_1> <program_file_2> ...\n",
	       argv[0]);
	exit(1);
    }

    printf("LC-3b Simulator\n\n");

    initialize(argv[1], argv[2], argc - 2);

    if ( (dumpsim_file = fopen( "dumpsim", "w" )) == NULL ) {
	printf("Error: Can't open dumpsim file\n");
	exit(-1);
    }

    while (1)
	get_command(dumpsim_file);

}

/***************************************************************/
/* Do not modify the above code.
   You are allowed to use the following global variables in your
   code. These are defined above.

   CONTROL_STORE
   MEMORY
   BUS

   CURRENT_LATCHES
   NEXT_LATCHES

   You may define your own local/global variables and functions.
   You may use the functions to get at the control bits defined
   above.

   Begin your code here 	  			       */
/***************************************************************/

int
power(int value, int exponent) {
  int sum = value;
  for (int i = exponent; i >= 2; i--) { // todo: maybe make this uint
    sum = sum*value;
  }
  return sum;
}

uint16_t unlatched_MDR = 0;
uint16_t unlatched_PC = 0;

uint16_t ALU = 0;
uint16_t SHF = 0;

uint16_t unlatched_SR1 = 0;
int8_t DR_reg = -1;

uint16_t MARMUX_value = 0;
uint16_t LShifted = 0;
uint16_t ADDR1 = 0;

void
eval_micro_sequencer(void) {
  /* 
   * Evaluate the address of the next state according to the 
   * micro sequencer logic. Latch the next microinstruction.
   */
  
  int* uinstr = CURRENT_LATCHES.MICROINSTRUCTION;

  uint8_t state = GetJ(uinstr);
  uint8_t conditions = GetCOND(uinstr);

  if (GetIRD(uinstr) == 0) {
    if (conditions == 1) {
      if (CURRENT_LATCHES.READY) {
        /* Memory is ready to continue! */
        state += power(2, 1);
        // todo: determine if I need to set READY to 0 here
        NEXT_LATCHES.READY = 0;
      }

    } else if (conditions == 2) {
      /* Determines whether we are branching */
      if (CURRENT_LATCHES.BEN) {
        state += power(2,2);
      }

    } else if (conditions == 3) {
      /* Determines whether we have a JSR or JSRR instruction */
      if (GET_IR_11(CURRENT_LATCHES.IR)) {
        state += 1;
      }
    }
  } else {
    /* Use the Opcode bits to determine next state */
    state = Low16bits(CURRENT_LATCHES.IR) >> 12;
  }

  NEXT_LATCHES.STATE_NUMBER = state;

#if (LOG_LEVEL > 2)
  printf("This is the current %d and the next state: %d\n", CURRENT_LATCHES.STATE_NUMBER, NEXT_LATCHES.STATE_NUMBER);
#endif

  memcpy(NEXT_LATCHES.MICROINSTRUCTION, CONTROL_STORE[NEXT_LATCHES.STATE_NUMBER], sizeof(int)*CONTROL_STORE_BITS);
}


void
cycle_memory(void) {
  /* 
   * This function emulates memory and the WE logic. 
   * Keep track of which cycle of MEMEN we are dealing with.  
   * If fourth, we need to latch Ready bit at the end of 
   * cycle to prepare microsequencer for the fifth cycle.  
   */

  static uint8_t mem_cycle = 0;
  int* uinstr = CURRENT_LATCHES.MICROINSTRUCTION;
  bool MIO_EN = GetMIO_EN(uinstr);

  if (MIO_EN) {
    mem_cycle++;

    if (mem_cycle == 4) {
      NEXT_LATCHES.READY = true;
#if (LOG_LEVEL > 2)
      printf("Asserted mem_ready for next cycle!\n");
#endif

    } else if (mem_cycle == 5) {
      /* Allow memory to continue execution */
      mem_cycle = 0;

      /* If true, it is a write, put the value from the MDR into memory */
      bool R_or_W = GetR_W(uinstr);
      if (R_or_W) {
        bool WE0 = false;
        bool WE1 = false;
        bool bit_0 = GET_MAR_0(CURRENT_LATCHES.MAR);
        bool data_size = GetDATA_SIZE(uinstr);

        /* 8 bit access to the even memory address */
        if (!data_size && !bit_0) {
          WE0 = true;
          WE1 = false;

        /* 8 bit access to the odd memory address */
        } else if (!data_size && bit_0) {
          WE0 = false;
          WE1 = true;

        /* 16 bit access to the even memory address */
        } else if (data_size && !bit_0) {
          WE0 = true;
          WE1 = true;

        /* 16 bit access to the odd memory address */
        } else if (data_size && bit_0) {
          /* unaligned access not being tested */
        }

        if (WE0) {
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE] = SET_MEM(CURRENT_LATCHES.MDR);
#if (LOG_LEVEL > 1)
          printf("First!\n");
          printf("Putting %04x into %04x\n", SET_MEM(CURRENT_LATCHES.MDR), CURRENT_LATCHES.MAR);
#endif
        }
        if (WE1) {
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE] = SET_MEM(CURRENT_LATCHES.MDR);
#if (LOG_LEVEL > 1)
          printf("Putting %04x into %04x\n", SET_MEM(CURRENT_LATCHES.MDR), CURRENT_LATCHES.MAR);
#endif
        }

        if (WE0 & WE1) {
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE] = SET_LOW_BYTE_MEM(CURRENT_LATCHES.MDR);
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE] = SET_HI_BYTE_MEM(CURRENT_LATCHES.MDR);
        } else if (WE0 & !WE1) {
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE] = SET_MEM(CURRENT_LATCHES.MDR);
        } else if (!WE0 & WE1) {
          MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE] = SET_MEM(CURRENT_LATCHES.MDR);
        }

#if (LOG_LEVEL > 1)
        if (WE0 && WE1) {
          printf("Completed a 16-bit write of %04x to memory address %04x!\n", MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE] |
                                                                               MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE],
                                                                               ADDR(CURRENT_LATCHES.MAR) << 1);
        } else if (WE0 && !WE1) {
          printf("Completed an 8-bit write of %04x to memory address %04x!\n", MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE],
                                                                               ADDR(CURRENT_LATCHES.MAR) << 1);
        } else if (!WE0 && WE1) {
          printf("Completed an 8-bit write of %04x to memory address %04x!\n", MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE],
                                                                               (ADDR(CURRENT_LATCHES.MAR) << 1) + 1);
        } else if (!WE0 && !WE1) {
          printf("Is this type of access even allowed here?!\n");
        }

#endif

      } else {
        /* Read, put the value from the memory into MDR */
        unlatched_MDR = Low16bits(GET_LOW_BYTE_MEM(MEMORY[ADDR(CURRENT_LATCHES.MAR)][LOW_BYTE]) |
                                  GET_HI_BYTE_MEM(MEMORY[ADDR(CURRENT_LATCHES.MAR)][HIGH_BYTE]));
#if (LOG_LEVEL > 2)
        printf("Read the value of %04x into the MDR!\n", unlatched_MDR);
#endif
      }
    } else {
#if (LOG_LEVEL > 2)
      printf("Cycling through Memory!\n");
#endif
    }
  }
}

void
eval_bus_drivers(void) {
  /* 
   * Datapath routine emulating operations before driving the bus.
   * Evaluate the input of tristate drivers 
   *             Gate_MARMUX,
   *		 Gate_PC,
   *		 Gate_ALU,
   *		 Gate_SHF,
   *		 Gate_MDR.
   */

  int* uinstr = CURRENT_LATCHES.MICROINSTRUCTION;

  bool DR_MUX = GetDRMUX(uinstr);
  bool SR1_MUX = GetSR1MUX(uinstr);
  bool ADDR1_MUX = GetADDR1MUX(uinstr);
  uint8_t ADDR2_MUX = GetADDR2MUX(uinstr);
  uint8_t ALUK = GetALUK(uinstr);
  bool IS_LSHF = GetLSHF1(uinstr);
  bool MAR_MUX = GetMARMUX(uinstr);

  uint8_t SHF_TYPE = GET_SHF_TYPE(CURRENT_LATCHES.IR);
  bool IS_IMM5 = GET_IR_5(CURRENT_LATCHES.IR);
  uint8_t amount4 = GET_AMOUNT4(CURRENT_LATCHES.IR);

  uint16_t unlatched_DR = 0;

  int8_t SR1_reg = -1;

  int8_t SR2_reg = -1;
  uint16_t unlatched_SR2 = 0;

  int16_t ADDR2 = -1;

  if (DR_MUX) {
    DR_reg = 7;
    unlatched_DR = MASK_16_BITS(CURRENT_LATCHES.REGS[DR_reg]);
  } else {
    DR_reg = GET_IR_11_9(CURRENT_LATCHES.IR);
    unlatched_DR = MASK_16_BITS(CURRENT_LATCHES.REGS[DR_reg]);
  }

#if (LOG_LEVEL > 2)
  printf("\nDR_reg: %d\n", DR_reg);
#endif

  if (SR1_MUX) {
    SR1_reg = GET_IR_8_6(CURRENT_LATCHES.IR);
    unlatched_SR1 = MASK_16_BITS(CURRENT_LATCHES.REGS[SR1_reg]);
  } else {
    SR1_reg = GET_IR_11_9(CURRENT_LATCHES.IR);
    unlatched_SR1 = MASK_16_BITS(CURRENT_LATCHES.REGS[SR1_reg]);
  }

#if (LOG_LEVEL > 2)
  printf("SR1_reg: %d\n", SR1_reg);
#endif

  if (IS_IMM5) {
    //imm5
    SR2_reg = -1;
    unlatched_SR2 = MASK_16_BITS(SEXT(GET_IMM5(CURRENT_LATCHES.IR), SEXT_5BITS));
  } else {
    SR2_reg = GET_IR_2_0(CURRENT_LATCHES.IR);
    unlatched_SR2 = MASK_16_BITS(CURRENT_LATCHES.REGS[SR2_reg]);
  }

#if (LOG_LEVEL > 2)
  printf("SR2_reg: %d\n", SR2_reg);
#endif

  if (ADDR1_MUX) {
    ADDR1 = unlatched_SR1;
  } else {
    ADDR1 = MASK_16_BITS(CURRENT_LATCHES.PC);
  }

#if (LOG_LEVEL > 2)
  printf("ADDR1: 0x%04x\n", ADDR1);
#endif

  if (ADDR2_MUX == 0) {
    ADDR2 = 0;
  } else if (ADDR2_MUX == 1) {
    ADDR2 = MASK_16_BITS(SEXT(GET_OFFSET6(CURRENT_LATCHES.IR), SEXT_6BITS));
  } else if (ADDR2_MUX == 2) {
    ADDR2 = MASK_16_BITS(SEXT(GET_PCOFFSET9(CURRENT_LATCHES.IR), SEXT_9BITS));
  } else if (ADDR2_MUX == 3) {
    ADDR2 = MASK_16_BITS(SEXT(GET_PCOFFSET11(CURRENT_LATCHES.IR), SEXT_11BITS));
  }

#if (LOG_LEVEL > 2)
  printf("ADDR2: 0x%04x\n", ADDR2);
#endif

  // todo: Do I have to SEXT here?
  if (ALUK == 0) {
    ALU = MASK_16_BITS(unlatched_SR1 + unlatched_SR2);
  } else if (ALUK == 1) {
    ALU = MASK_16_BITS(unlatched_SR1 & unlatched_SR2);
  } else if (ALUK == 2) {
    ALU = MASK_16_BITS(unlatched_SR1 ^ unlatched_SR2);
  } else if (ALUK == 3) {
    ALU = MASK_16_BITS(unlatched_SR1);
  }

#if (LOG_LEVEL > 2)
  printf("ALU: 0x%04x\n", ALU);
#endif

  if (SHF_TYPE == SHF_LSHFL) {
    SHF = MASK_16_BITS(LSHFT(unlatched_SR1, amount4));

  } else if (SHF_TYPE == SHF_RSHFL) {
    SHF = MASK_16_BITS(RSHFTL(unlatched_SR1, amount4));

  } else if (SHF_TYPE == SHF_RSHFA) {
    SHF = MASK_16_BITS(RSHFTA(unlatched_SR1, amount4));
  }

#if (LOG_LEVEL > 2)
  printf("SHF: 0x%04x\n\n", SHF);
#endif

  if (IS_LSHF) {
    LShifted = MASK_16_BITS(LSHFT(ADDR2, 1));
  } else {
    LShifted = MASK_16_BITS(ADDR2);
  }

  if (MAR_MUX) {
    MARMUX_value = MASK_16_BITS(LShifted + ADDR1);
  } else {
    MARMUX_value = LSHFT(ZEXT(GET_IR_7_0(CURRENT_LATCHES.IR)), 1);
  }

  unlatched_PC = MASK_16_BITS(CURRENT_LATCHES.PC);
}


void
drive_bus(void) {
  /* 
   * Datapath routine for driving the bus from one of the 5 possible 
   * tristate drivers. 
   */       
  int* uinstr = CURRENT_LATCHES.MICROINSTRUCTION;

  bool GATE_ALU = GetGATE_ALU(uinstr);
  bool GATE_SHF = GetGATE_SHF(uinstr);
  bool GATE_MAR_MUX = GetGATE_MARMUX(uinstr);
  bool GATE_MDR = GetGATE_MDR(uinstr);
  bool GATE_DATA_SIZE = GetDATA_SIZE(uinstr);
  bool GATE_PC = GetGATE_PC(uinstr);

  if (GATE_ALU) {
    BUS = MASK_16_BITS(ALU);
  } else if (GATE_SHF) {
    BUS = MASK_16_BITS(SHF);
  } else if (GATE_MAR_MUX) {
    BUS = MASK_16_BITS(MARMUX_value);
  } else if (GATE_MDR) {
    if (GATE_DATA_SIZE) {
      BUS = MASK_16_BITS(CURRENT_LATCHES.MDR);
    } else {
      if (GET_MAR_0(CURRENT_LATCHES.MAR)) {
        // todo: should I be SEXT here?
        // todo: something seems wrong about how I determine the high byte or low byte to put onto the BUS
        BUS = MASK_16_BITS(SEXT((CURRENT_LATCHES.MDR&0xFF00)>>8, SEXT_8BITS));
      } else {
        BUS = MASK_16_BITS(SEXT((CURRENT_LATCHES.MDR&0xFF), SEXT_8BITS));
      }
    }
  } else if (GATE_PC) {
    BUS = MASK_16_BITS(unlatched_PC);
  } else {
    BUS = 0;
  }
}


void
latch_datapath_values(void) {
  /* 
   * Datapath routine for computing all functions that need to latch
   * values in the data path at the end of this cycle.  Some values
   * require sourcing the bus; therefore, this routine has to come 
   * after drive_bus.
   */       

  int* uinstr = CURRENT_LATCHES.MICROINSTRUCTION;

  bool LD_MAR = GetLD_MAR(uinstr);
  bool LD_MDR = GetLD_MDR(uinstr);
  bool MIO_EN = GetMIO_EN(uinstr);
  bool DATA_SIZE = GetDATA_SIZE(uinstr);
  bool LD_IR = GetLD_IR(uinstr);
  bool LD_BEN = GetLD_BEN(uinstr);
  bool LD_REG = GetLD_REG(uinstr);
  bool LD_CC = GetLD_CC(uinstr);
  bool LD_PC = GetLD_PC(uinstr);
  uint8_t PC_MUX = GetPCMUX(uinstr);

  if (LD_MAR) {
    NEXT_LATCHES.MAR = MASK_16_BITS(BUS);
  }

  if (LD_MDR) {
    if (MIO_EN) {
      NEXT_LATCHES.MDR = MASK_16_BITS(unlatched_MDR); // todo: double check if this is valid
#if (LOG_LEVEL > 2)
        printf("MDR taking unlatched value 0x%04x\n", NEXT_LATCHES.MDR);
#endif
    } else {
      if (DATA_SIZE) {
        NEXT_LATCHES.MDR = MASK_16_BITS(BUS);
#if (LOG_LEVEL > 2)
        printf("MDR taking value 0x%04x from the bus\n", NEXT_LATCHES.MDR);
#endif
      } else {
        if (GET_MAR_0(CURRENT_LATCHES.MAR)) {
          NEXT_LATCHES.MDR = (BUS&0x00FF); // todo: check if this is right!
#if (LOG_LEVEL > 2)
        printf("MDR taking value 0x%04x from the bus\n", (BUS&0xFF00)>>8);
#endif
        } else {
          NEXT_LATCHES.MDR = BUS&0x00FF;
#if (LOG_LEVEL > 2)
        printf("MDR taking value 0x%04x from the bus\n", BUS&0x00FF);
#endif
        }
      }
    }
  }

  if (LD_IR) {
    NEXT_LATCHES.IR = MASK_16_BITS(BUS);
  }

  if (LD_BEN) {
    NEXT_LATCHES.BEN = (GET_N(CURRENT_LATCHES.IR) && CURRENT_LATCHES.N) ||
                       (GET_Z(CURRENT_LATCHES.IR) && CURRENT_LATCHES.Z) ||
                       (GET_P(CURRENT_LATCHES.IR) && CURRENT_LATCHES.P);
  }

  /* Sets the next state according to JSR/JSRR instructions */
  if ((CURRENT_LATCHES.STATE_NUMBER == 20) || (CURRENT_LATCHES.STATE_NUMBER == 21)) {
    uint16_t temp = CURRENT_LATCHES.PC + 2;

    if (!GET_IR_11(CURRENT_LATCHES.IR)) {
      unlatched_PC = unlatched_SR1; // todo: double check that I can make this unlatched_PC
    } else {
      unlatched_PC = temp + LSHFT(SEXT(GET_PCOFFSET11(CURRENT_LATCHES.IR), SEXT_11BITS), 1);
    }

    NEXT_LATCHES.REGS[RETURN_REGISTER] = temp;
    NEXT_LATCHES.PC = unlatched_PC;
  }

  if (LD_REG) {
    NEXT_LATCHES.REGS[DR_reg] = MASK_16_BITS(BUS);
  }

  if (LD_CC) {
    if (IS_ZERO(BUS)) {
      NEXT_LATCHES.N = 0;
      NEXT_LATCHES.Z = 1;
      NEXT_LATCHES.P = 0;

    } else if (IS_NEG(BUS)) { // todo: double check that IS_NEG Is working
      NEXT_LATCHES.N = 1;
      NEXT_LATCHES.Z = 0;
      NEXT_LATCHES.P = 0;

    } else {
      NEXT_LATCHES.N = 0;
      NEXT_LATCHES.Z = 0;
      NEXT_LATCHES.P = 1;
    }
  }

  if (LD_PC) {
    if (PC_MUX == 0) {
      unlatched_PC = MASK_16_BITS(2 + CURRENT_LATCHES.PC);
    } else if (PC_MUX == 1) {
      unlatched_PC = MASK_16_BITS(BUS);
    } else if (PC_MUX == 2) {
      unlatched_PC = MASK_16_BITS(LShifted + ADDR1);
    }
    NEXT_LATCHES.PC = MASK_16_BITS(unlatched_PC);
  }
}