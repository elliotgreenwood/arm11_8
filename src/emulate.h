#ifndef EMULATEDEFS
#define EMULATEDEFS

#include <stdlib.h>
#include <stdint.h>

typedef int bool;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef MEM16BIT
#define MEM16BIT 65536
#endif

//execute return values
const int EXE_HALT = 0;
const int EXE_CONTINUE = -1;
const int EXE_BRANCH = 1;

// Instruction types
const int BRANCH = 128;
const int DATA_TRANS = 64;
const int MULT = 32;
const int DATA_PROC = 16;

typedef struct {
  uint8_t cond;
  uint8_t instType;
  uint8_t opcode;
  uint8_t rn;
  uint8_t rd;
  uint8_t rm;
  uint8_t rs;
  int32_t operandOffset;
} DecodedInst;

struct regFile {
  uint32_t *reg; // registers 0-13 are general purpose.
  uint32_t *SP;
  uint32_t *LR;
  uint32_t *PC;
  uint32_t *CPSR;
};

// execute functions --
int execute(DecodedInst di);
void executeDataProcessing(uint8_t instType, uint8_t opcode, uint8_t Rn, uint8_t Rd, uint32_t operand);
uint32_t barrelShift(uint32_t valu, int shiftSeg, int s);
void setCPSRZN(int value, int trigger);
void executeMult(uint8_t instType, uint8_t rd, uint8_t rn, uint8_t rs, uint8_t rm);
void executeSingleDataTransfer(uint8_t instType, uint8_t rn, uint8_t rd, uint32_t offset);
void executeBranch(int offset);
void testing(void); //WILL REMOVE
// --
void dealloc(void);
void loadFileToMem(char const *file);
void clearRegfile (struct regFile rf);
// helper functions --
int ipow(int x, int y);
int rotr8(uint8_t x, int n);
int rotr32(uint32_t x, int n);
void enterC(void);  //WILL REMOVE
void alterC(bool set);
void alterZ(bool set);
void alterN(bool set);
int getBit(int x, int pos);
//--
int32_t fetch(uint8_t *mem);
DecodedInst decode(int32_t instruction);
uint8_t getInstType(int32_t instruction);

// dont keep getFlags()
//***********************

void decodeForDataProc(int32_t instruction, DecodedInst di);
void decodeForMult(int32_t instruction, DecodedInst di);
void decodeForDataTrans(int32_t instruction, DecodedInst di);
void decodeForBranch(int32_t instruction, DecodedInst di);

#endif /* end of include guard: EMULATEDEFS */
