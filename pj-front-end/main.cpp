#include <bits/stdc++.h>

#define Project Y86_Simulator

#define rep(i, l, r) for (register int i = l; i <= r; i++)
#define per(i, r, l) for (register int i = r; i >= l; i--)
#define srep(i, l, r) for (register int i = l; i < r; i++)
#define sper(i, r, l) for (register int i = r; i > l; i--)
#define gc getchar
using namespace std;

namespace Define{
	#define MAX_MEMORY 0x100000
	#define MAX_REGISTER 0x10
	#define PC_START 0x000
	
	#define AOK 1
	#define HLT 2
	#define BUB 3
	#define ADR 4
	#define INS 5
	
	#define halt 	0x00
	#define nop 	0x10
	#define rrmovq 	0x20
	#define cmovle	0x21
	#define cmovl	0x22
	#define cmove	0x23
	#define cmovne	0x24
	#define cmovge	0x25
	#define cmovg	0x26
	#define irmovq 	0x30
	#define rmmovq 	0x40
	#define mrmovq 	0x50
	#define addq	0x60
	#define subq	0x61
	#define andq	0x62
	#define xorq	0x63
	#define jmp		0x70
	#define jle 	0x71
	#define jl		0x72
	#define je		0x73
	#define jne		0x74
	#define jge		0x75
	#define jg		0x76
	#define call 	0x80
	#define ret		0x90
	#define pushq	0xa0
	#define popq	0xb0
	
	#define ihalt	0x0
	#define inop	0x1
	#define irrmovq 0x2
	#define iirmovq 0x3
	#define irmmovq 0x4
	#define imrmovq 0x5
	#define iOPq	0x6
	#define iJXX	0x7
	#define icmovXX 0x2
	#define icall 	0x8
	#define iret 	0x9
	#define ipushq	0xa
	#define ipopq	0xb
	#define iall    0xb
	
	#define FNONE	0x0
	#define fhalt 	0x0
	#define fnop 	0x0
	#define frrmovq 0x0
	#define firmovq 0x0
	#define frmmovq 0x0
	#define fmrmovq 0x0
	#define faddq	0x0
	#define fsubq	0x1
	#define fandq	0x2
	#define fxorq	0x3
	#define fOPq	0x3
	#define fjmp	0x0
	#define fjle 	0x1
	#define fjl		0x2
	#define fje		0x3
	#define fjne	0x4
	#define fjge	0x5
	#define fjg		0x6
	#define fJXX	0x6
	#define fcmovle	0x1
	#define fcmovl	0x2
	#define fcmove	0x3
	#define fcmovne	0x4
	#define fcmovge	0x5
	#define fcmovg	0x6
	#define fcmovXX 0x6
	#define fcall 	0x0
	#define fret	0x0
	#define fpushq	0x0
	#define fpopq	0x0
	
	#define rax 	0x0
	#define rcx 	0x1
	#define rdx		0x2
	#define rbx		0x3
	#define	rsp		0x4
	#define rbp		0x5
	#define rsi		0x6
	#define rdi		0x7
	#define r8		0x8
	#define r9		0x9
	#define r10		0xa
	#define r11		0xb
	#define r12		0xc
	#define r13		0xd
	#define r14		0xe
	#define RNONE	0xf
	
	typedef unsigned char mem_t;
	typedef unsigned long long reg_t;
	typedef unsigned long long cpu_t;
	typedef signed long long ptr_t;
	typedef unsigned long long wire_t;
	typedef unsigned short int stat_t;
	typedef bool cc_t;
	typedef unsigned long long imm_t;
	typedef unsigned long long addr_t;
	typedef unsigned char hex_t;
	typedef char char_t;
	typedef bool bit_t;
}using namespace Define;

namespace Toolkit{	
	const char s_stat[][7] = {"\0", "AOK", "HLT", "BUB", "ADR", "INS"};
	const char* getStat(reg_t stat){
		if (1 <= stat && stat <= 5) 
			return s_stat[stat];
		else {
			return "ERROR";
		}
	}
	const char s_reg[][7]  = {"%rax", "%rcx", "%rdx", "%rbx", "%rsp", "%rbp", "%rsi", "%rdi", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "----"};
	const char* getReg(reg_t reg){
		if (reg <= 15) {
			return s_reg[reg];
		}
		else {
			return "ERROR";
		}
	}
	const char s_instr[][10][10] = {{"halt"}, {"nop"}, {"rrmovq", "cmovle", "cmovl", "cmove", "cmovne", "cmovge", "cmovg"}, {"irmovq"}, {"rmmovq"}, {"mrmovq"}, {"addq", "subq", "andq", "xorq"}, {"jmp", "jle", "jl", "je", "jne", "jge", "jg"}, {"call"}, {"ret"}, {"pushq"}, {"popq"}};
	const char* getIns(reg_t icode, reg_t ifun){	
		if (icode <= iall) {
			if (icode == iOPq){
				if (ifun <= fOPq) return s_instr[icode][ifun];
				else return "ERROR";
			}
			else if (icode == iJXX){
				if (ifun <= fJXX) return s_instr[icode][ifun];
				else return "ERROR";
			}
			else if (icode == icmovXX){
				if (ifun <= fcmovXX) return s_instr[icode][ifun];
				else return "ERROR";
			}
			else {
				if (!ifun) return s_instr[icode][ifun];
				else return "ERROR";
			}
		}
		else return "ERROR";
	}
}using namespace Toolkit;

namespace Modules{

	namespace F{
		void F_set(reg_t& F_bubble){
			F_bubble = true;
		}
		void SelectPC(reg_t predPC, reg_t W_valM, reg_t W_icode, reg_t M_valA, reg_t M_Cnd, reg_t M_icode, wire_t& f_pc){
			if (M_icode == iJXX && !M_Cnd) f_pc = M_valA;
			else if (W_icode == iret) f_pc = W_valM;
			else f_pc = predPC;
		}
		void InsMem(wire_t f_pc, wire_t& imem_err, wire_t& im_to_split, mem_t* im_to_align, mem_t* mem){
			if (f_pc >= MAX_MEMORY || f_pc + 0x9 >= MAX_MEMORY) {
				im_to_split = 0x0;
				im_to_align = 0x0;
				imem_err = true;
			}
			else {
				im_to_split = mem[f_pc];
				rep(i, 1, 9) im_to_align[i - 1] = mem[f_pc + i]; 
				imem_err = false;
			}
		}
		void Split(wire_t im_to_split, wire_t& sp_to_icode, wire_t& sp_to_ifun){
			sp_to_icode = im_to_split >> 0x4;
			sp_to_ifun  = im_to_split &  0xf;
		}
		void icode(wire_t sp_to_icode, wire_t imem_err, wire_t& f_icode){
			if (imem_err) f_icode = inop;
			else f_icode = sp_to_icode;
		}
		void ifun(wire_t sp_to_ifun, wire_t imem_err, wire_t& f_ifun){
			if (imem_err) f_ifun  = FNONE;
			else f_ifun = sp_to_ifun;
		}
		void Instr_valid(wire_t f_icode, wire_t f_ifun, wire_t& ins_err){
			if (f_icode <= iall) {
				if (f_icode == iOPq){
					if (f_ifun <= fOPq) ins_err = false;
					else ins_err = true;
				}
				else if (f_icode == iJXX){
					if (f_ifun <= fJXX) ins_err = false;
					else ins_err = true;
				}
				else if (f_icode == icmovXX){
					if (f_ifun <= fcmovXX) ins_err = false;
					else ins_err = true;
				}
				else {
					if (!f_ifun) ins_err = false;
					else ins_err = true;
				}
			}
			else ins_err = true;
		}
		void F_Stat(wire_t ins_err, wire_t imem_err, wire_t f_icode, wire_t& f_stat){
			if (imem_err) f_stat = ADR;
			else if (ins_err) f_stat = INS;
			else if (f_icode == ihalt) f_stat = HLT;
			else f_stat = AOK;
		}
		void need_valC(wire_t f_icode, wire_t& nv_to_PCincr){
			if (f_icode == iirmovq || f_icode == irmmovq || f_icode == imrmovq || f_icode == iJXX || f_icode == icall) {
				nv_to_PCincr = true;
			}
			else nv_to_PCincr = false;
		}
		void need_regids(wire_t f_icode, wire_t& nr_to_PCincr){
			if (f_icode == irrmovq || f_icode == iOPq || f_icode == ipushq || f_icode == ipopq || f_icode == iirmovq || f_icode == irmmovq || f_icode == imrmovq) {
				nr_to_PCincr = true;
			}
			else nr_to_PCincr = false;
		}
		void Align(mem_t* im_to_align, wire_t nr_to_PCincr, wire_t nv_to_PCincr, wire_t& f_rA, wire_t& f_rB, wire_t& f_valC){
			ptr_t ptr = 0x0;
			f_rA = RNONE;
			f_rB = RNONE;
			f_valC = 0x0;
			if (nr_to_PCincr) {
				f_rA = im_to_align[ptr] >> 0x4;
				f_rB = im_to_align[ptr] &  0xf;
				ptr++;
			}
			if (nv_to_PCincr) {
				per (i, ptr + 7, ptr){
					f_valC = (f_valC << 0x8) + im_to_align[i];
				}
			}
		}
		void PC_incr(wire_t nv_to_PCincr, wire_t nr_to_PCincr, wire_t f_pc, wire_t& f_valP){
			f_valP = f_pc + 0x1;
			if (nv_to_PCincr) f_valP += 0x8;
			if (nr_to_PCincr) f_valP += 0x1;
		}
		void Predict_PC(wire_t f_icode, wire_t f_valC, wire_t f_valP, wire_t& f_predPC){
			if (f_icode == iJXX || f_icode == icall) f_predPC = f_valC;
			else f_predPC = f_valP;
		}
		void F_load(reg_t& F_stall, reg_t& F_bubble, reg_t& D_stall, reg_t& D_bubble, wire_t f_stat, reg_t& D_stat, wire_t f_icode, reg_t& D_icode, wire_t f_ifun, reg_t& D_ifun, wire_t f_rA, reg_t& D_rA, wire_t f_rB, reg_t& D_rB, wire_t f_valC, reg_t& D_valC, wire_t f_valP, reg_t& D_valP, wire_t f_predPC, reg_t& predPC){
			if (F_stall) {
				F_stall = false;
				F_bubble = false;
			}
			else if (F_bubble){
				F_stall = false;
				F_bubble = false;
				predPC = PC_START;
			}
			else predPC = f_predPC;
			
			if (D_stall){
				D_stall = false;
				D_bubble = false;
			}
			else if (D_bubble){
				D_stall = false;
				D_bubble = false;
				D_stat = BUB;
				D_icode = inop;
				D_ifun = 0x0;
				D_rA = RNONE;
				D_rB = RNONE;
				D_valC = 0x0;
				D_valP = 0x0;
			}
			else {
				D_stall = false;
				D_bubble = false;
				D_stat = f_stat;
				D_icode = f_icode;
				D_ifun = f_ifun;
				D_rA = f_rA;
				D_rB = f_rB;
				D_valC = f_valC;
				D_valP = f_valP;
			} 
		}
	}using namespace F;

	namespace D{
		void D_set(reg_t& D_bubble){
			D_bubble = true;
		}
		void D_Pass(reg_t D_stat, wire_t& d_stat, reg_t D_icode, wire_t& d_icode, reg_t D_ifun, wire_t& d_ifun, reg_t D_valC, wire_t& d_valC){
			d_stat = D_stat;
			d_icode = D_icode;
			d_ifun = D_ifun;
			d_valC = D_valC;
		} 
		void RegisterFile(wire_t d_srcA, wire_t d_srcB, reg_t W_valE, reg_t W_dstE, reg_t W_valM, reg_t W_dstM, wire_t& d_rvalA, wire_t& d_rvalB, reg_t* reg){
			if (W_dstM != RNONE) reg[W_dstM] = W_valM;
			if (W_dstE != RNONE) reg[W_dstE] = W_valE;
			d_rvalA = (d_srcA == RNONE) ? 0x0 : reg[d_srcA];
			d_rvalB = (d_srcB == RNONE) ? 0x0 : reg[d_srcB];
		}
		void dstE(reg_t D_icode, reg_t D_rB, wire_t& d_dstE){
			if (D_icode == irrmovq || D_icode == iirmovq || D_icode == iOPq) d_dstE = D_rB;
			else if (D_icode == ipushq || D_icode == ipopq || D_icode == icall || D_icode == iret) d_dstE = rsp;
			else d_dstE= RNONE;
		}
		void dstM(reg_t D_icode, reg_t D_rA, wire_t& d_dstM){
			if (D_icode == imrmovq || D_icode == ipopq) d_dstM = D_rA;
			else d_dstM = RNONE;
		}
		void srcA(reg_t D_icode, reg_t D_rA, wire_t& d_srcA){
			if (D_icode == irrmovq || D_icode == irmmovq || D_icode == iOPq || D_icode == ipushq) d_srcA = D_rA;
			else if (D_icode == ipopq || D_icode == iret) d_srcA = rsp;
			else d_srcA = RNONE;
		}
		void srcB(reg_t D_icode, reg_t D_rB, wire_t& d_srcB){	
			if (D_icode == iOPq || D_icode == irmmovq || D_icode == imrmovq) d_srcB = D_rB;
			else if (D_icode == ipushq || D_icode == ipopq || D_icode == icall || D_icode == iret) d_srcB = rsp;
			else d_srcB = RNONE;
		}
		void Sel_FwdA(wire_t d_icode, reg_t D_valP, wire_t d_rvalA, wire_t d_srcA, reg_t W_valE, reg_t W_dstE, reg_t W_valM, reg_t W_dstM, wire_t m_valM, reg_t M_dstM, reg_t M_valE, reg_t M_dstE, wire_t e_valE, wire_t e_dstE, wire_t& d_valA){
			if (d_icode == icall || d_icode == iJXX) d_valA = D_valP;
			else if (d_srcA == e_dstE) d_valA = e_valE;
			else if (d_srcA == M_dstM) d_valA = m_valM;
			else if (d_srcA == M_dstE) d_valA = M_valE;
			else if (d_srcA == W_dstM) d_valA = W_valM;
			else if (d_srcA == W_dstE) d_valA = W_valE;
			else d_valA = d_rvalA;
		}
		void FwdB(wire_t d_rvalB, wire_t d_srcB, reg_t W_valE, reg_t W_dstE, reg_t W_valM, reg_t W_dstM, wire_t m_valM, reg_t M_dstM, reg_t M_valE, reg_t M_dstE, wire_t e_valE, wire_t e_dstE, wire_t& d_valB){
			if (d_srcB == e_dstE) d_valB = e_valE;
			else if (d_srcB == M_dstM) d_valB = m_valM;
			else if (d_srcB == M_dstE) d_valB = M_valE;
			else if (d_srcB == W_dstM) d_valB = W_valM;
			else if (d_srcB == W_dstE) d_valB = W_valE;
			else d_valB = d_rvalB;
		}
		void D_load(reg_t& E_stall, reg_t& E_bubble, wire_t d_stat, reg_t& E_stat, wire_t d_icode, reg_t& E_icode, wire_t d_ifun, reg_t& E_ifun, wire_t d_valC, reg_t& E_valC, wire_t d_valA, reg_t& E_valA, wire_t d_valB, reg_t& E_valB, wire_t d_dstE, reg_t& E_dstE, wire_t d_dstM, reg_t& E_dstM, wire_t d_srcA, reg_t& E_srcA, wire_t d_srcB, reg_t& E_srcB){
			if (E_stall){
				E_stall = false;
				E_bubble = false;
				return;
			}
			else if (E_bubble){	
				E_stall = false;
				E_bubble = false;
				E_stat = BUB;
				E_icode = inop;
				E_ifun = 0x0;
				E_valC = 0x0;
				E_valA = 0x0;
				E_valB = 0x0;
				E_dstE = RNONE;
				E_dstM = RNONE;
				E_srcA = RNONE;
				E_srcB = RNONE;
			}
			else {
				E_stall = false;
				E_bubble = false;
				E_stat = d_stat;
				E_icode = d_icode;
				E_ifun = d_ifun;
				E_valC = d_valC;
				E_valA = d_valA;
				E_valB = d_valB;
				E_dstE = d_dstE;
				E_dstM = d_dstM;
				E_srcA = d_srcA;
				E_srcB = d_srcB;
			} 
		}
	}using namespace D;

	namespace E{
		void E_set(reg_t& E_bubble){
			E_bubble = true;
		}
		void E_pass(reg_t E_stat, wire_t& e_stat, reg_t E_icode, wire_t& e_icode, reg_t E_ifun, wire_t& e_ifun, reg_t E_valA, wire_t& e_valA, reg_t E_dstM, wire_t& e_dstM){
			e_stat = E_stat;
			e_icode = E_icode;
			e_ifun = E_ifun;
			e_valA = E_valA;
			e_dstM = E_dstM;
		}
		void ALUA(reg_t E_icode, reg_t E_valC, reg_t E_valA, wire_t& A_to_ALU){
			if (E_icode == irrmovq || E_icode == iOPq) A_to_ALU = E_valA;
			else if (E_icode == iirmovq || E_icode == irmmovq || E_icode == imrmovq) A_to_ALU = E_valC;
			else if (E_icode == icall || E_icode == ipushq) A_to_ALU = -8;
			else if (E_icode == iret || E_icode == ipopq) A_to_ALU = 8;
			else A_to_ALU = 0;
		}
		void ALUB(reg_t E_icode, reg_t E_valB, wire_t& B_to_ALU){
			if (E_icode == irmmovq || E_icode == imrmovq || E_icode == iOPq || E_icode == icall || E_icode == ipushq || E_icode == iret || E_icode == ipopq) B_to_ALU = E_valB;
			else if (E_icode == irrmovq || E_icode == iirmovq) B_to_ALU = 0;
			else B_to_ALU = 0;
		}
		void SetCC(reg_t W_stat, wire_t m_stat, reg_t E_icode, wire_t& SetCC_to_CC){		
			if (m_stat != ADR && m_stat != INS && m_stat != HLT &&
				W_stat != ADR && W_stat != INS && W_stat != HLT && E_icode == iOPq) SetCC_to_CC = true;
				else SetCC_to_CC = false;
		}
		void CC(wire_t set_cc, wire_t SetCC_to_CC, wire_t ALU_to_CC, wire_t& CC_to_cond, cc_t& ZF, cc_t& SF, cc_t& OF){
			if (set_cc && SetCC_to_CC) {
				ZF = (ALU_to_CC >> 2) & 1;
				SF = (ALU_to_CC >> 1) & 1;
				OF = (ALU_to_CC >> 0) & 1;
				CC_to_cond = (ZF << 2) + (SF << 1) + (OF << 0);
			}
			else {
				CC_to_cond = (ZF << 2) + (SF << 1) + (OF << 0);
			}
		}
		void ALUfun(reg_t E_icode, reg_t E_ifun, wire_t& fun_to_ALU){
			if (E_icode == iOPq) fun_to_ALU = E_ifun;
			else fun_to_ALU = faddq;
		}
		void ALU(wire_t A_to_ALU, wire_t B_to_ALU, wire_t fun_to_ALU, wire_t& e_valE, wire_t& ALU_to_CC){
			ALU_to_CC = 0;
			cc_t A_sign = (A_to_ALU >> 63) & 1,
				 B_sign = (B_to_ALU >> 63) & 1,
				 E_sign = 0;
			switch(fun_to_ALU){
				case faddq: 
					e_valE = A_to_ALU + B_to_ALU; 
					E_sign = (e_valE >> 63) & 1;
					if ((!A_sign && !B_sign && E_sign) ||
						(A_sign && B_sign && !E_sign)) 
							ALU_to_CC |= 1;
					break;
				case fsubq: 
					e_valE = B_to_ALU - A_to_ALU;
					E_sign = (e_valE >> 63) & 1;
					if ((!B_sign && A_sign && E_sign) ||
						(B_sign && !A_sign && !E_sign)) 
							ALU_to_CC |= 1;
					break;
				case fandq:
					e_valE = A_to_ALU & B_to_ALU; 
					E_sign = (e_valE >> 63) & 1;
					break;
				case fxorq: 
					e_valE = A_to_ALU ^ B_to_ALU; 
					E_sign = (e_valE >> 63) & 1;
					break;
				default:
					cerr << "ERROR: ALU function not exists" << endl;
					exit(-1);
					break;
			}
			if (!e_valE) ALU_to_CC |= 4;
			if (E_sign) ALU_to_CC |= 2;
		}
		void cond(reg_t E_ifun, wire_t CC_to_cond, wire_t& e_Cnd){
			cc_t ZF = (CC_to_cond >> 2) & 1, 
				 SF = (CC_to_cond >> 1) & 1, 
				 OF = (CC_to_cond >> 0) & 1;
			switch(E_ifun){
				case fjmp: e_Cnd = true; 						break;
				case fjle: e_Cnd = (SF ^ OF) | ZF; 				break;
				case fjl:  e_Cnd = SF ^ OF; 					break;
				case fje:  e_Cnd = ZF; 							break;
				case fjne: e_Cnd = ZF ^ 1; 						break;
				case fjge: e_Cnd = 1 ^ (SF ^ OF); 				break;
				case fjg:  e_Cnd = (1 ^ (SF ^ OF)) & (1 ^ ZF); 	break;
				default:
					cerr << "Warning: condition not exists: " << E_ifun << endl;
					e_Cnd = false;
					break;
			}
			if (e_Cnd != 0 && e_Cnd != 1) {	
				cerr << "ERROR: condition value errors: " << e_Cnd << endl;
				cerr << "e_Cnd = " << e_Cnd << endl;
				cerr << "ZF = " << ZF << endl;
				cerr << "SF = " << SF << endl;
				cerr << "OF = " << OF << endl;
				exit(-1);
			}
		}
		void dstE(reg_t E_icode, reg_t E_dstE, wire_t e_Cnd, wire_t& e_dstE){
			if (E_icode == irrmovq && !e_Cnd) e_dstE = RNONE;
			else e_dstE = E_dstE;
		}
		void E_load(reg_t& M_stall, reg_t& M_bubble, wire_t e_stat, reg_t& M_stat, wire_t e_icode, reg_t& M_icode, wire_t e_ifun, reg_t& M_ifun, wire_t e_Cnd, reg_t& M_Cnd, wire_t e_valE, reg_t& M_valE, wire_t e_valA, reg_t& M_valA, wire_t e_dstE, reg_t& M_dstE, wire_t e_dstM, reg_t& M_dstM){	
			if (M_stall){
				M_stall = false;
				M_bubble = false;
				return;
			}
			else if (M_bubble){	
				M_stall = false;
				M_bubble = false;
				M_stat = BUB;
				M_icode = inop;
				M_ifun = FNONE;
				M_Cnd = false;
				M_valE = 0x0;
				M_valA = 0x0;
				M_dstE = RNONE;
				M_dstM = RNONE;
			}
			else {
				M_stall = false;
				M_bubble = false;
				M_stat = e_stat;
				M_icode = e_icode;
				M_ifun = e_ifun;
				M_Cnd = e_Cnd;
				M_valE = e_valE;
				M_valA = e_valA;
				M_dstE = e_dstE;
				M_dstM = e_dstM;
			}
		}
	}using namespace E;

	namespace M{	
		void M_set(reg_t& M_bubble){
			M_bubble = true;
		}
		void M_pass(reg_t M_icode, wire_t& m_icode, reg_t M_ifun, wire_t& m_ifun, reg_t M_valE, wire_t& m_valE, reg_t M_dstE, wire_t& m_dstE, reg_t M_dstM, wire_t& m_dstM){
			m_icode = M_icode;
			m_ifun =  M_ifun;
			m_valE =  M_valE;
			m_dstE =  M_dstE;
			m_dstM =  M_dstM;
		}
		void M_Stat(reg_t M_stat, wire_t dmem_err, wire_t& m_stat){
			if (dmem_err) m_stat = ADR;
			else m_stat = M_stat;
		}
		void Addr(reg_t M_valE, reg_t M_valA, reg_t M_icode, wire_t& Addr_to_DR){
			if (M_icode == irmmovq || M_icode == ipushq || M_icode == icall || M_icode == imrmovq) Addr_to_DR = M_valE;
			else if (M_icode == ipopq || M_icode == iret) Addr_to_DR = M_valA;
			else Addr_to_DR = 0x0;
		}
		void MemRead(reg_t M_icode, wire_t& MR_to_DR){
			if (M_icode == imrmovq || M_icode == ipopq || M_icode == iret) MR_to_DR = true;
			else MR_to_DR = false;
		}
		void MemWrite(reg_t M_icode, wire_t& MW_to_DR){
			if (M_icode == irmmovq || M_icode == ipushq || M_icode == icall) MW_to_DR = true;
			else MW_to_DR = false;
		}
		void DataRegister(wire_t Addr_to_DR, reg_t M_valA, wire_t MR_to_DR, wire_t MW_to_DR, wire_t& m_valM, wire_t& dmem_err, mem_t* mem){
			if (MR_to_DR && MW_to_DR) {
				cerr << "ERROR: memory reads and writes simultaneously" << endl;
				exit(-1);
			}
			ptr_t ptr = Addr_to_DR;
			m_valM = 0;
			dmem_err = false;
			if (MW_to_DR){	
				if (ptr >= MAX_MEMORY || ptr + 0x7 >= MAX_MEMORY || ptr < 0 || ptr + 0x7 < 0) {
					dmem_err = true;
				}
				else {
					rep(i, ptr, ptr + 7){
						mem[i] = M_valA & 0xff;
						M_valA >>= 8;
					}
				}
			}
			if (MR_to_DR){
				if (ptr >= MAX_MEMORY || ptr + 0x7 >= MAX_MEMORY || ptr < 0 || ptr + 0x7 < 0) {
					dmem_err = true;
				}
				else {
					per(i, ptr + 7, ptr){
						m_valM = (m_valM << 8) + mem[i];
					}
				}
			}
		}
		void M_load(reg_t& W_stall, reg_t& W_bubble, wire_t m_stat, reg_t& W_stat, wire_t m_icode, reg_t& W_icode, wire_t m_ifun, reg_t& W_ifun, wire_t m_valE, reg_t& W_valE, wire_t m_valM, reg_t& W_valM, wire_t m_dstE, reg_t& W_dstE, wire_t m_dstM, reg_t& W_dstM){
			if (W_stall){
				W_stall = false;
				W_bubble = false;
				return;
			}
			else if (W_bubble){
				W_stall = false;
				W_bubble = false;	
				W_stat = BUB;
				W_icode = inop;
				W_ifun = FNONE;
				W_valE = 0x0;
				W_valM = 0x0;
				W_dstE = RNONE;
				W_dstM = RNONE;
			}
			else{
				W_stall = false;
				W_bubble = false;
				W_stat = m_stat;
				W_icode = m_icode;
				W_ifun = m_ifun;
				W_valE = m_valE;
				W_valM = m_valM;
				W_dstE = m_dstE;
				W_dstM = m_dstM;
			} 
		}
	}using namespace M;

	namespace W{ 
		void W_set(reg_t& W_bubble){
			W_bubble = true;
		}
		void W_Stat(reg_t W_stat, wire_t& _Stat){
			if (W_stat == BUB) _Stat = AOK;
			else _Stat = W_stat;
		}
		void W_load(wire_t _Stat, reg_t& Stat){	
			Stat = _Stat;
		}
	}using namespace W;
	
	namespace L{
		void Logic(reg_t W_stat, wire_t& w_stall, wire_t m_stat, reg_t M_icode, wire_t& m_bubble, wire_t e_Cnd, wire_t& _set_cc, reg_t E_dstM, reg_t E_icode, wire_t& e_bubble, wire_t d_srcB, wire_t d_srcA, reg_t D_icode, wire_t& d_bubble, wire_t& d_stall, wire_t& f_stall){
			_set_cc = true;
			
			if(((E_icode == imrmovq || E_icode == ipopq) && 
				(E_dstM == d_srcA || E_dstM == d_srcB)) || 
				(D_icode == iret || E_icode == iret || M_icode == iret)) f_stall = true;
			else f_stall = false;
			
			if ((E_icode == imrmovq || E_icode == ipopq) && 
				(E_dstM == d_srcA || E_dstM == d_srcB)) d_stall = true;
			else d_stall = false;
			
			if ((E_icode == iJXX && !e_Cnd) || !((E_icode == imrmovq || E_icode == ipopq) && (E_dstM == d_srcA || E_dstM == d_srcB)) && (D_icode == iret || E_icode == iret || M_icode == iret)) d_bubble = true;
			else d_bubble = false;
			
			if ((E_icode == iJXX && !e_Cnd) || ((E_icode == imrmovq || E_icode == ipopq) && (E_dstM == d_srcA || E_dstM == d_srcB))) e_bubble = true;
			else e_bubble = false;
			
			if ((m_stat == ADR || m_stat == INS || m_stat == HLT) ||
				(W_stat == ADR || W_stat == INS || W_stat == HLT)) m_bubble = true;
			else m_bubble = false;
			
			if (W_stat == ADR || W_stat == INS || W_stat == HLT) w_stall = true;
			else w_stall = false;
		}
		void L_load(wire_t w_stall, reg_t& W_stall, wire_t m_bubble, reg_t& M_bubble, wire_t _set_cc, wire_t& set_cc, wire_t e_bubble, reg_t& E_bubble, wire_t d_bubble, reg_t& D_bubble, wire_t d_stall, reg_t& D_stall, wire_t f_stall, reg_t& F_stall){
			W_stall = w_stall;
			M_bubble = m_bubble;
			set_cc = _set_cc;
			E_bubble = e_bubble;
			D_bubble = d_bubble;
			D_stall = d_stall;
			F_stall = f_stall;
		}
	}using namespace L;
	
}using namespace Modules;

namespace Hardwares{
	mem_t 	mem[MAX_MEMORY];
	addr_t 	mxaddr;
	cc_t	ZF = 1, 
			SF = 0, 
			OF = 0;
	reg_t	predPC = PC_START,
			reg[MAX_REGISTER];
	reg_t	Stat = AOK;
	
	reg_t	F_bubble, F_stall,
			D_stat, D_icode, D_ifun, D_rA, D_rB, D_valC, D_valP, D_bubble, D_stall,
			E_stat, E_icode, E_ifun, E_valC, E_valA, E_valB, E_dstE, E_dstM, E_srcA, E_srcB, E_bubble, E_stall, 
			M_stat, M_icode, M_ifun, M_Cnd, M_valE, M_valA, M_dstE, M_dstM, M_bubble, M_stall,
			W_stat, W_icode, W_ifun, W_valE, W_valM, W_dstE, W_dstM, W_bubble, W_stall;

	mem_t	im_to_align[0xa];

	wire_t	f_pc, imem_err, f_split, f_align, f_icode, f_ifun, f_rA, f_rB, f_valC, f_stat, f_valP, f_predPC, im_to_split, sp_to_icode, sp_to_ifun, nr_to_PCincr, ins_err, nv_to_PCincr, 
			d_srcA, d_srcB, d_rvalA, d_rvalB, d_stat, d_icode, d_ifun, d_valC, d_dstE, d_dstM, d_valA, d_valB, 
			e_Cnd, e_valE, e_dstE, e_stat, e_icode, e_ifun, e_valA, e_dstM, A_to_ALU, B_to_ALU, SetCC_to_CC, set_cc, _set_cc, CC_to_cond, fun_to_ALU, ALU_to_CC,
			dmem_err, m_stat, m_valM, m_icode, m_ifun, m_valE, m_dstE, m_dstM, Addr_to_DR, MR_to_DR, MW_to_DR, 
			w_dstM, _Stat,
			w_stall, m_bubble, e_bubble, d_bubble, d_stall, f_stall;
		
	cpu_t	Cycle;
}using namespace Hardwares;

namespace Control{

	namespace F_Stage{
		void F_init(){
			F_set(F_bubble);
		}
		void F_run(){
			SelectPC(predPC, W_valM, W_icode, M_valA, M_Cnd, M_icode, f_pc);
			InsMem(f_pc, imem_err, im_to_split, im_to_align, mem);
			Split(im_to_split, sp_to_icode, sp_to_ifun);
			icode(sp_to_icode, imem_err, f_icode);
			ifun(sp_to_ifun, imem_err, f_ifun);
			Instr_valid(f_icode, f_ifun, ins_err);
			F_Stat(ins_err, imem_err, f_icode, f_stat);
			need_valC(f_icode, nv_to_PCincr);
			need_regids(f_icode, nr_to_PCincr);
			Align(im_to_align, nr_to_PCincr, nv_to_PCincr, f_rA, f_rB, f_valC);
			PC_incr(nv_to_PCincr, nr_to_PCincr, f_pc, f_valP);
			Predict_PC(f_icode, f_valC, f_valP, f_predPC);
		}
		void F_flush(){
			F_load(F_stall, F_bubble, D_stall, D_bubble, f_stat, D_stat, f_icode, D_icode, f_ifun, D_ifun, f_rA, D_rA, f_rB, D_rB, f_valC, D_valC, f_valP, D_valP, f_predPC, predPC);
		}
	}using namespace F_Stage;
	
	namespace D_Stage{
		void D_init(){
			D_set(D_bubble);
		}
		void D_run(){
			D_Pass(D_stat, d_stat, D_icode, d_icode, D_ifun, d_ifun, D_valC, d_valC);
			dstE(D_icode, D_rB, d_dstE);
			dstM(D_icode, D_rA, d_dstM);
			srcA(D_icode, D_rA, d_srcA);
			srcB(D_icode, D_rB, d_srcB);
			RegisterFile(d_srcA, d_srcB, W_valE, W_dstE, W_valM, W_dstM, d_rvalA, d_rvalB, reg);
			Sel_FwdA(d_icode, D_valP, d_rvalA, d_srcA, W_valE, W_dstE, W_valM, W_dstM, m_valM, M_dstM, M_valE, M_dstE, e_valE, e_dstE, d_valA);
			FwdB(d_rvalB, d_srcB, W_valE, W_dstE, W_valM, W_dstM, m_valM, M_dstM, M_valE, M_dstE, e_valE, e_dstE, d_valB);
		}
		void D_flush(){
			D_load(E_stall, E_bubble, d_stat, E_stat, d_icode, E_icode, d_ifun, E_ifun, d_valC, E_valC, d_valA, E_valA, d_valB, E_valB, d_dstE, E_dstE, d_dstM, E_dstM, d_srcA, E_srcA, d_srcB, E_srcB);
		}
	}using namespace D_Stage;
	
	namespace E_Stage{
		void E_init(){
			E_set(E_bubble);
		}
		void E_run(){
			E_pass(E_stat, e_stat, E_icode, e_icode, E_ifun, e_ifun, E_valA, e_valA, E_dstM, e_dstM);
			ALUA(E_icode, E_valC, E_valA, A_to_ALU);
			ALUB(E_icode, E_valB, B_to_ALU);
			SetCC(W_stat, m_stat, E_icode, SetCC_to_CC);
			ALUfun(E_icode, E_ifun, fun_to_ALU);
			ALU(A_to_ALU, B_to_ALU, fun_to_ALU, e_valE, ALU_to_CC);
			CC(set_cc, SetCC_to_CC, ALU_to_CC, CC_to_cond, ZF, SF, OF);
			cond(E_ifun, CC_to_cond, e_Cnd);
			dstE(E_icode, E_dstE, e_Cnd, e_dstE);
		}
		void E_flush(){
			E_load(M_stall, M_bubble, e_stat, M_stat, e_icode, M_icode, e_ifun, M_ifun, e_Cnd, M_Cnd, e_valE, M_valE, e_valA, M_valA, e_dstE, M_dstE, e_dstM, M_dstM);
		}
	}using namespace E_Stage;
	
	namespace M_Stage{
		void M_init(){
			M_set(M_bubble);
		}
		void M_run(){
			M_pass(M_icode, m_icode, M_ifun, m_ifun, M_valE, m_valE, M_dstE, m_dstE, M_dstM, m_dstM);
			Addr(M_valE, M_valA, M_icode, Addr_to_DR);
			MemRead(M_icode, MR_to_DR);
			MemWrite(M_icode, MW_to_DR);
			DataRegister(Addr_to_DR, M_valA, MR_to_DR, MW_to_DR, m_valM, dmem_err, mem);
			M_Stat(M_stat, dmem_err, m_stat); 
		}
		void M_flush(){
			M_load(W_stall, W_bubble, m_stat, W_stat, m_icode, W_icode, m_ifun, W_ifun, m_valE, W_valE, m_valM, W_valM, m_dstE, W_dstE, m_dstM, W_dstM);
		}
	}using namespace M_Stage;
	
	namespace W_Stage{
		void W_init(){
			W_set(W_bubble);
		}
		void W_run(){
			W_Stat(W_stat, _Stat);
		}
		void W_flush(){
			W_load(_Stat, Stat);
		}
	}using namespace W_Stage;
	
	namespace L_Stage{
		void L_init(){
			return;
		}
		void L_run(){
			Logic(W_stat, w_stall, m_stat, M_icode, m_bubble, e_Cnd, _set_cc, E_dstM, E_icode, e_bubble, d_srcB, d_srcA, D_icode, d_bubble, d_stall, f_stall);
		}
		void L_flush(){
			L_load(w_stall, W_stall, m_bubble, M_bubble, _set_cc, set_cc, e_bubble, E_bubble, d_bubble, D_bubble, d_stall, D_stall, f_stall, F_stall);
		}
	}using namespace L_Stage;
	
	namespace Debug{
		void _F(){	
			printf("F: predPC = 0x%llx\n", predPC);
		}
		void _D(){
			printf("D: instr = %s, rA = %s, rB = %s, valC = 0x%llx, valP = 0x%llx, Stat = %s\n", getIns(D_icode, D_ifun), getReg(D_rA), getReg(D_rB), D_valC, D_valP, getStat(D_stat));
		}
		void _E(){	
			printf("E: instr = %s, valC = 0x%llx, valA = 0x%llx, valB = 0x%llx\n   srcA = %s, srcB = %s, dstE = %s, dstM = %s, Stat = %s\n", getIns(E_icode, E_ifun), E_valC, E_valA, E_valB, getReg(E_srcA), getReg(E_srcB), getReg(E_dstE), getReg(E_dstM), getStat(E_stat));
		}
		void _M(){
			printf("M: instr = %s, Cnd = %lld, valE = 0x%llx, valA = 0x%llx\n   dstE = %s, dstM = %s, Stat = %s\n", getIns(M_icode, M_ifun), M_Cnd, M_valE, M_valA, getReg(M_dstE), getReg(M_dstM), getStat(M_stat));
		}
		void _W(){
			printf("W: instr = %s, valE = 0x%llx, valM = 0x%llx, dstE = %s, dstM = %s, Stat = %s\n", getIns(W_icode, W_ifun), W_valE, W_valM, getReg(W_dstE), getReg(W_dstM), getStat(W_stat));
		}
		void _L(){
			printf("L: W_stall = 0x%llx, M_bubble = 0x%llx, set_cc = 0x%llx, E_bubble = 0x%llx, D_bubble = 0x%llx, D_stall = 0x%llx, F_stall = 0x%llx\n", W_stall, M_bubble, set_cc, E_bubble, D_bubble, D_stall, F_stall);
		}
		void _Sys(){
			printf("Cycle %lld. CC=Z=%d S=%d O=%d, Stat=%s\n", Cycle, ZF, SF, OF, getStat(Stat));
		}
		void _SysSum(){
			printf("Condition Code:\n");
			printf("ZF: %d, SF: %d, OF: %d\n", ZF, SF, OF);
			printf("\nRegister File:\n");
			rep(i, 0, 14) printf("%s:\t0x%016llx\n", s_reg[i], reg[i]); 
			printf("\nMemory:\n");
			for (addr_t i = 0; i < mxaddr; i += 8){
				printf("0x%03llx:\t0x", i);
				for (addr_t j = i; j < min(mxaddr, i + 8); j++){
					printf("%x%x", mem[j] >> 4, mem[j] & 0xf);
				}
				printf("\n");
			}
		}
		void _End(){
			printf("	Fetch: f_pc = 0x%llx, imem_instr = %s, f_instr = %s\n\n", f_pc, getIns(f_icode, f_ifun), getIns(f_icode, f_ifun));
		}
		void _Header(){
			printf("Y86-64 Processor\n\n");
		}
	}using namespace Debug;
	
}using namespace Control;

namespace CPU{
	void cpu_init(){
		F_init();
		D_init();
		E_init();
		M_init();
		W_init();
		L_init();
		_Header();
	}
	void cpu_init_flush(){
		F_flush(); 
		D_flush();
		E_flush();
		M_flush();
		W_flush();
		L_flush();
	}
	void cpu_run(){
		W_run();
		M_run();
		E_run();
		D_run();
		F_run(); 
		L_run();
	}
	void cpu_flush(){
		L_flush();
		F_flush(); 
		D_flush();
		E_flush();
		M_flush();
		W_flush();
	}
	void cpu_print(){
		_Sys();
		_F();
		_D();
		_E();
		_M();
		_W();
		_End();
	}
	void cpu_final_print(){
		_SysSum();
	}
	bool cpu_check(){
		return Stat == AOK && Cycle < 1000;
	}
	void cpu_start(){
		Cycle = 0;
		cpu_init(); 
		cpu_init_flush();
		Stat = AOK;
		while (cpu_check()) {
			cpu_run();
			cpu_print();
			cpu_flush(); 
			Cycle++;
		}
		cpu_run();
		cpu_print();
		cpu_final_print();
		if (Cycle == 1000) {
			cerr << "Error: dead loop" << endl;
			exit(-1);
		}
	}
}using namespace CPU;

namespace Init{
	inline hex_t hex2int(char_t ch){ 
		return isdigit(ch) ? ch - '0' : ch - 'a' + 10;
	}
	void fetch_bytes(){
		char_t ch = '\0';
		while (ch != EOF){
			ch = gc(); 
			while (ch != 'x' && ch != '|' && ch != EOF) ch = gc();
			if (ch == 'x') {
				ch = gc(); 
				while (!isxdigit(ch)) ch = gc();  
				addr_t addr = 0; 
				while (isxdigit(ch)) {
					addr = (addr << 4) + hex2int(ch);
					ch = gc();
				}
				mxaddr = max(mxaddr, addr); 
				while (!isxdigit(ch) && ch != '|') ch = gc();
				if (ch == '|') goto fail;
				mem_t byte = 0; bit_t time_to_write_mem = 0;
				while (isxdigit(ch)) {
					byte = (byte << 4) + hex2int(ch);
					ch = gc();
					if (time_to_write_mem) mem[addr++] = byte;
					time_to_write_mem ^= 1;
				}
				mxaddr = max(mxaddr, addr); 
			}
			fail: while (ch != '\n' && ch != EOF) ch = gc(); 
			if (ch == EOF) return; 
		}
		cerr << "ERROR: fetch bytes fails" << endl; 
		exit(-1);
	}
}using namespace Init;

namespace Test{
	void _memory(){
		srep(i, 0, mxaddr) printf("%x%x", mem[i] >> 4, mem[i] & 15);
	}
	void _fetch_bytes(){
		fetch_bytes();
		_memory();
	}
}

namespace Y86_Call{
	void Y86_init(){
		fetch_bytes();
	}
	void Y86_run(){
		cpu_start();
	}
	void Y86_end(){
		return;
	}
	void Y86_play(){
		Y86_init();
		Y86_run();
		Y86_end();
	}
}using namespace Y86_Call;

#define Y86 main	// do you want to show your simulator? :)
//#define test main	// do you want to give a test? :)

int Y86(){ 
	freopen("input.yo", "r", stdin);
	freopen("output.txt", "w", stdout);
	Y86_play();
	return 0;
}

int test(){
	//Test :: _fetch_bytes();
}
