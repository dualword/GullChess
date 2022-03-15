#define W32_BUILD
#undef W32_BUILD

#ifdef W32_BUILD
#define NTDDI_VERSION 0x05010200
#define _WIN32_WINNT 0x0501
#endif

#include "fcntl.h"
#include <fstream>
#include "intrin.h"
#include "io.h"
#include <iostream>
#include "math.h"
#include "setjmp.h"
#include "stdio.h"
#include "windows.h"
using namespace std;

#define DEBUG // looking for bugs
#undef DEBUG

#define ASPIRATION
//#undef ASPIRATION

#define LONGEST_LINE // just for fun :)
#undef LONGEST_LINE

#define HASH_READER
#undef HASH_READER

#ifdef HASH_READER
#ifdef ASPIRATION
#undef ASPIRATION
#endif
#endif

#define EXTENSIONS
//#undef EXTENSIONS

#define CHECK_EXT_PV
//#undef CHECK_EXT_PV
#define CheckPVExt 2

#define CHECK_EXT_NPV
//#undef CHECK_EXT_NPV
#define CheckNPVExt(depth) ((depth) < 16 ? 2 : 1)

#define SINGLE_REPLY_EXT
//#undef SINGLE_REPLY_EXT

#define DOUBLE_SINGLE
#undef DOUBLE_SINGLE

#define NULL_MOVE
//#undef NULL_MOVE

#define NPV_IID
//#undef NPV_IID

#define REPETITION
//#undef REPETITION

#define PV_HASHING
//#undef PV_HASHING

#define PREFETCH
//#undef PREFETCH

#define MP_NPS
//#undef MP_NPS

#define CHILD_PROCESS_SPLIT
#undef CHILD_PROCESS_SPLIT

#define PV_SPLIT
//#undef PV_SPLIT

#define WAIT_FOR_CHILD_PROCESSES
#undef WAIT_FOR_CHILD_PROCESSES

#define CPU_TIMING
#undef CPU_TIMING

#define TIME_TO_DEPTH
//#undef TIME_TO_DEPTH

#define HASH_STORE
#undef HASH_STORE

#define LARGE_PAGES
//#undef LARGE_PAGES

#define CUT_ALL
#undef CUT_ALL

#define TUNER
#undef TUNER

#ifdef TUNER
#undef MP_NPS
#include "time.h"

#define LOCAL_TUNER
//#define MAT_STAT

//#define NO_DELTA
//#define NO_CAP_PRUNING
//#define NO_HISTORY_PRUNING
//#define NO_EVASION_HISTORY_PRUNING

//#define RECORD_GAMES
#define NODES
#else
#define LOAD_MAT_SHIFT
#endif

#define uint8 unsigned __int8
#define sint8 __int8
#define uint16 unsigned __int16
#define sint16 __int16
#define uint32 unsigned __int32
#define sint32 __int32
#define uint64 unsigned __int64
#define sint64 __int64

#define Convert(x,type) ((type)(x))

#define Abs(x) ((x) > 0 ? (x) : (-(x)))
#define Sgn(x) ((x) == 0 ? 0 : ((x) > 0 ? 1 : (-1)))
#define Min(x,y) ((x) < (y) ? (x) : (y))
#define Max(x,y) ((x) > (y) ? (x) : (y))
#define T(x) ((x) != 0)
#define F(x) ((x) == 0)
#define Even(x) F((x) & 1)
#define Odd(x) T((x) & 1)
#define Eq(x,y) ((x) == (y))
#define Combine(x,y) ((x) | ((y) << 16))
#define Compose(x,y) ((x) + ((y) << 16))
#define Opening(x) Convert((x) & 0xFFFF,sint16)
#define Endgame(x) (((x >> 15) & 1) + Convert((x) >> 16,sint16))

#define File(x) ((x) & 7)
#define Rank(x) ((x) >> 3)
#define CRank(me,x) ((me) ? (7 - Rank(x)) : Rank(x))
#define NDiag(x) (7 - File(x) + Rank(x))
#define SDiag(x) (File(x) + Rank(x))
#define Dist(x,y) Max(Abs(Rank(x)-Rank(y)),Abs(File(x)-File(y)))
#define CVar(var,me) ((me) ? (var##_b) : (var##_w))
#define CVarEI(var,me)((me) ? (EI.var##_b) : (EI.var##_w))
#define CVarPEI(var,me)((me) ? (PEI.var##_b) : (PEI.var##_w))

#define Bit(x) (Convert(1,uint64) << (x))
#define Cut(x) (x &= (x) - 1)
#define Multiple(x) T((x) & ((x) - 1))
#define Single(x) F((x) & ((x) - 1))
#define Add(x,b) (x |= Bit(b))

#define Move(from,to) (((from) << 6) | (to))
#define From(move) (((move) >> 6) & 0x3f)
#define To(move) ((move) & 0x3f)

#define Empty Convert(0,uint64)
#define Filled (~Empty)
#define Interior Convert(0x007E7E7E7E7E7E00,uint64)
#define Boundary (~Interior)
#define WhiteArea Convert(0x00000000FFFFFFFF,uint64)
#define BlackArea (~WhiteArea)
#define LightArea Convert(0x55AA55AA55AA55AA,uint64)
#define DarkArea (~LightArea)
#define FileA Convert(0x0101010101010101,uint64)
#define Line0 Convert(0x00000000000000FF,uint64)

#define High32(x) ((x) >> 32)
#define Low32(x) Convert(x,uint32)

#define White 0
#define Black 1
#define WhitePawn 2
#define BlackPawn 3
#define WhiteKnight 4
#define BlackKnight 5
#define WhiteLight 6
#define BlackLight 7
#define WhiteDark 8
#define BlackDark 9
#define WhiteRook 10
#define BlackRook 11
#define WhiteQueen 12
#define BlackQueen 13
#define WhiteKing 14
#define BlackKing 15

#define IsSlider(x) T(0x3FC0 & Bit(x))

#define CanCastle_OO 1
#define CanCastle_oo 2
#define CanCastle_OOO 4
#define CanCastle_ooo 8

#define FlagCastling 0x1000
#define FlagEP 0x2000
#define FlagPKnight 0x4000
#define FlagPLight 0x6000
#define FlagPDark 0x8000
#define FlagPRook 0xA000
#define FlagPQueen 0xC000

#define IsPromotion(move) T((move) & 0xC000)
#define IsCastling(move) T((move) & 0x1000)
#define IsEP(move) Eq((move) & 0xF000, 0x2000)
#define Promotion(move,side) ((side) + (((move) & 0xF000) >> 12))

const uint8 UpdateCastling[64] = {
	0xFF^CanCastle_OOO,0xFF,0xFF,0xFF,0xFF^(CanCastle_OO|CanCastle_OOO),0xFF,0xFF,0xFF^CanCastle_OO,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF^CanCastle_ooo,0xFF,0xFF,0xFF,0xFF^(CanCastle_oo|CanCastle_ooo),0xFF,0xFF,0xFF^CanCastle_oo
};

const uint64 BMagic[64] = {
    0x0048610528020080, 0x00c4100212410004, 0x0004180181002010, 0x0004040188108502, 
    0x0012021008003040, 0x0002900420228000, 0x0080808410c00100, 0x000600410c500622, 
    0x00c0056084140184, 0x0080608816830050, 0x00a010050200b0c0, 0x0000510400800181, 
    0x0000431040064009, 0x0000008820890a06, 0x0050028488184008, 0x00214a0104068200, 
    0x004090100c080081, 0x000a002014012604, 0x0020402409002200, 0x008400c240128100, 
    0x0001000820084200, 0x0024c02201101144, 0x002401008088a800, 0x0003001045009000, 
    0x0084200040981549, 0x0001188120080100, 0x0048050048044300, 0x0008080000820012, 
    0x0001001181004003, 0x0090038000445000, 0x0010820800a21000, 0x0044010108210110, 
    0x0090241008204e30, 0x000c04204004c305, 0x0080804303300400, 0x00a0020080080080, 
    0x0000408020220200, 0x0000c08200010100, 0x0010008102022104, 0x0008148118008140, 
    0x0008080414809028, 0x0005031010004318, 0x0000603048001008, 0x0008012018000100, 
    0x0000202028802901, 0x004011004b049180, 0x0022240b42081400, 0x00c4840c00400020, 
    0x0084009219204000, 0x000080c802104000, 0x0002602201100282, 0x0002040821880020, 
    0x0002014008320080, 0x0002082078208004, 0x0009094800840082, 0x0020080200b1a010, 
    0x0003440407051000, 0x000000220e100440, 0x00480220a4041204, 0x00c1800011084800, 
    0x000008021020a200, 0x0000414128092100, 0x0000042002024200, 0x0002081204004200
};

const uint64 RMagic[64] = {
    0x00800011400080a6, 0x004000100120004e, 0x0080100008600082, 0x0080080016500080, 
    0x0080040008000280, 0x0080020005040080, 0x0080108046000100, 0x0080010000204080, 
    0x0010800424400082, 0x00004002c8201000, 0x000c802000100080, 0x00810010002100b8, 
    0x00ca808014000800, 0x0002002884900200, 0x0042002148041200, 0x00010000c200a100, 
    0x00008580004002a0, 0x0020004001403008, 0x0000820020411600, 0x0002120021401a00, 
    0x0024808044010800, 0x0022008100040080, 0x00004400094a8810, 0x0000020002814c21, 
    0x0011400280082080, 0x004a050e002080c0, 0x00101103002002c0, 0x0025020900201000, 
    0x0001001100042800, 0x0002008080022400, 0x000830440021081a, 0x0080004200010084, 
    0x00008000c9002104, 0x0090400081002900, 0x0080220082004010, 0x0001100101000820, 
    0x0000080011001500, 0x0010020080800400, 0x0034010224009048, 0x0002208412000841, 
    0x000040008020800c, 0x001000c460094000, 0x0020006101330040, 0x0000a30010010028, 
    0x0004080004008080, 0x0024000201004040, 0x0000300802440041, 0x00120400c08a0011, 
    0x0080006085004100, 0x0028600040100040, 0x00a0082110018080, 0x0010184200221200, 
    0x0040080005001100, 0x0004200440104801, 0x0080800900220080, 0x000a01140081c200, 
    0x0080044180110021, 0x0008804001001225, 0x00a00c4020010011, 0x00001000a0050009, 
    0x0011001800021025, 0x00c9000400620811, 0x0032009001080224, 0x001400810044086a
};

const int BShift[64] = {
    58, 59, 59, 59, 59, 59, 59, 58, // magics with constant shift are much harder to generate (manual fitting is required => TODO) so we use this simple "fancy magic" scheme
	59, 59, 59, 59, 59, 59, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59, 
	59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59, 
	59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 59, 59, 59, 59, 59, 59, 
	58, 59, 59, 59, 59, 59, 59, 58
};

const int BOffset[64] = {
    0, 64, 96, 128, 160, 192, 224, 256, 
    320, 352, 384, 416, 448, 480, 512, 544, 
    576, 608, 640, 768, 896, 1024, 1152, 1184, 
    1216, 1248, 1280, 1408, 1920, 2432, 2560, 2592, 
    2624, 2656, 2688, 2816, 3328, 3840, 3968, 4000, 
    4032, 4064, 4096, 4224, 4352, 4480, 4608, 4640, 
    4672, 4704, 4736, 4768, 4800, 4832, 4864, 4896, 
    4928, 4992, 5024, 5056, 5088, 5120, 5152, 5184 
};

const int RShift[64] = {
    52, 53, 53, 53, 53, 53, 53, 52, 
	53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 
	52, 53, 53, 53, 53, 53, 53, 52
};

const int ROffset[64] = {
    5248, 9344, 11392, 13440, 15488, 17536, 19584, 21632, 
    25728, 27776, 28800, 29824, 30848, 31872, 32896, 33920, 
    35968, 38016, 39040, 40064, 41088, 42112, 43136, 44160, 
    46208, 48256, 49280, 50304, 51328, 52352, 53376, 54400, 
    56448, 58496, 59520, 60544, 61568, 62592, 63616, 64640, 
    66688, 68736, 69760, 70784, 71808, 72832, 73856, 74880, 
    76928, 78976, 80000, 81024, 82048, 83072, 84096, 85120, 
    87168, 91264, 93312, 95360, 97408, 99456, 101504, 103552
};

#define BishopAttacks(sq,occ) (MagicAttacks[BOffset[(sq)] + (((BMagicMask[(sq)] & (occ)) * BMagic[(sq)]) >> BShift[(sq)])])
#define RookAttacks(sq,occ) (MagicAttacks[ROffset[(sq)] + (((RMagicMask[(sq)] & (occ)) * RMagic[(sq)]) >> RShift[(sq)])])
#define QueenAttacks(sq,occ) (BishopAttacks(sq,occ) | RookAttacks(sq,occ))

#define MatWQ 1
#define MatBQ 3
#define MatWR (3 * 3)
#define MatBR (3 * 3 * 3)
#define MatWL (3 * 3 * 3 * 3)
#define MatBL (3 * 3 * 3 * 3 * 2)
#define MatWD (3 * 3 * 3 * 3 * 2 * 2)
#define MatBD (3 * 3 * 3 * 3 * 2 * 2 * 2)
#define MatWN (3 * 3 * 3 * 3 * 2 * 2 * 2 * 2)
#define MatBN (3 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 3)
#define MatWP (3 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 3 * 3)
#define MatBP (3 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 3 * 3 * 9)
#define TotalMat ((2*(MatWQ+MatBQ)+MatWL+MatBL+MatWD+MatBD+2*(MatWR+MatBR+MatWN+MatBN)+8*(MatWP+MatBP)) + 1)
#define FlagUnusualMaterial (1 << 30)

const int MatCode[16] = {0,0,MatWP,MatBP,MatWN,MatBN,MatWL,MatBL,MatWD,MatBD,MatWR,MatBR,MatWQ,MatBQ,0,0};
const uint64 File[8] = {FileA,FileA<<1,FileA<<2,FileA<<3,FileA<<4,FileA<<5,FileA<<6,FileA<<7};
const uint64 Line[8] = {Line0,(Line0<<8),(Line0<<16),(Line0<<24),(Line0<<32),(Line0<<40),(Line0<<48),(Line0<<56)};

#define IPawn(me) (WhitePawn | (me))
#define IKnight(me) (WhiteKnight | (me))
#define ILight(me) (WhiteLight | (me))
#define IDark(me) (WhiteDark | (me))
#define IRook(me) (WhiteRook | (me))
#define IQueen(me) (WhiteQueen | (me))
#define IKing(me) (WhiteKing | (me))

#define BB(i) Board->bb[i]
#define Pawn(me) (BB(WhitePawn | (me)))
#define Knight(me) (BB(WhiteKnight | (me)))
#define Bishop(me) (BB(WhiteLight | (me)) | BB(WhiteDark | (me)))
#define Rook(me) (BB(WhiteRook | (me)))
#define Queen(me) (BB(WhiteQueen | (me)))
#define King(me) (BB(WhiteKing | (me)))
#define Piece(me) (BB(me))
#define NonPawn(me) (Piece(me) ^ Pawn(me))
#define NonPawnKing(me) (NonPawn(me) ^ King(me))
#define BSlider(me) (Bishop(me) | Queen(me))
#define RSlider(me) (Rook(me) | Queen(me))
#define Heavy(me) RSlider(me)
#define Light(me) (Knight(me) | Bishop(me))
#define Slider(me) (BSlider(me) | RSlider(me))
#define PieceAll (Piece(White) | Piece(Black))
#define SliderAll (Slider(White) | Slider(Black))
#define PawnAll (Pawn(White) | Pawn(Black))

#define ShiftNW(target) (((target) & (~(File[0] | Line[7]))) << 7)
#define ShiftNE(target) (((target) & (~(File[7] | Line[7]))) << 9)
#define ShiftSE(target) (((target) & (~(File[7] | Line[0]))) >> 7)
#define ShiftSW(target) (((target) & (~(File[0] | Line[0]))) >> 9)
#define ShiftW(me,target) ((me) ? ShiftSW(target) : ShiftNW(target))
#define ShiftE(me,target) ((me) ? ShiftSE(target) : ShiftNE(target))
#define ShiftN(target) ((target) << 8)
#define ShiftS(target) ((target) >> 8)
#define Shift(me,target) ((me) ? ShiftS(target) : ShiftN(target))
#define PushW(me) ((me) ? (-9) : (7))
#define PushE(me) ((me) ? (-7) : (9))
#define Push(me) ((me) ? (-8) : (8))
#define IsGreater(me,x,y) ((me) ? ((x) < (y)) : ((x) > (y)))

#define Line(me,n) ((me) ? Line[7 - n] : Line[n])
#define Attacks(sq) Current->attacks[sq]
#define Square(sq) Board->square[sq]
#define AddMove(from,to,flags,score) { *list = ((from) << 6) | (to) | (flags) | (score); list++; }
#define AddCapture(from,to,flags) AddMove(from,to,flags,MVVLVA[Square(from)][Square(to)])
#define AddCaptureP(piece,from,to,flags) AddMove(from,to,flags,MVVLVA[piece][Square(to)])
#define AddHistoryP(piece,from,to,flags) AddMove(from,to,flags,HistoryP(piece,from,to))
#define AddHistory(from,to) AddMove(from,to,0,History(from,to))
#define AddDeltaP(piece,from,to,flags) AddMove(from,to,flags,Convert(DeltaP(piece,from,to)+0x4000,int) << 16)
#define AddDelta(from,to) AddMove(from,to,0,Convert(Delta(from,to)+0x4000,int) << 16)
#define AddCDeltaP(piece,from,to,flags) {if (DeltaP(piece,from,to) >= Current->margin) AddMove(from,to,flags,Convert(DeltaP(piece,from,to)+0x4000,int) << 16)}
#define AddCDelta(from,to) {if (Delta(from,to) >= Current->margin) AddMove(from,to,0,Convert(Delta(from,to)+0x4000,int) << 16)}

#define Check(me) T(Current->att[1 ^ me] & King(me))
#define IsIllegal(me,move) ((T(Current->xray[1 ^ me] & Bit(From(move))) && F(Bit(To(move)) & FullLine[lsb(King(me))][From(move)])) \
	|| (IsEP(move) && T(Line[Rank(From(move))] & King(me)) && T(Line[Rank(From(move))] & Heavy(1 ^ me)) && \
	T(RookAttacks(lsb(King(me)),PieceAll ^ Bit(From(move)) ^ Bit(Current->ep_square - Push(me))) & Heavy(1 ^ me))))
#ifdef REPETITION
#define IsRepetition(margin,move) (margin > 0 && Current->ply >= 2 && (Current-1)->move == ((To(move) << 6) | From(move)) && F(Square(To(move))) && F((move) & 0xF000))
#else
#define IsRepetition(margin,move) (0)
#endif

#define Inc(x) (me ? (score -= (x)) : (score += (x)))
#define Dec(x) Inc(-(x))
#define IncV(var,x) (me ? (var -= (x)) : (var += (x)))
#define DecV(var,x) IncV(var,-(x))

#define PawnValue Compose(80, 125)
#define KnightValue Compose(265, 355)
#define BishopValue Compose(280, 360)
#define RookValue Compose(405, 610)
#define QueenValue Compose(800, 1150)
#define KPKValue 300
#define EvalValue 30000
#define MateValue 32760

#define C4(x1,x2,x3,x4) (((uint64)(x1)) + (((uint64)(x2)) << 16) + (((uint64)(x3)) << 32) + (((uint64)(x4)) << 48))
#define PawnV4 C4(80, 90, 110, 125)
#define KnightV4 C4(265, 280, 320, 355)
#define BishopV4 C4(280, 295, 325, 360)
#define RookV4 C4(405, 450, 550, 610)
#define QueenV4 C4(800, 875, 1025, 1150)

#define BishopPairV4 C4(35, 40, 50, 55)
#define DoubleRooksV4 C4(16, 20, 28, 32)
#define DoubleHeavyV4 C4(8, 10, 14, 16)
#define MinorSupV4 C4(20, 15, 10, 5)
#define KnightPawnAdj C4(0, 2, 4, 5)
#define RookPawnAdj C4(5, 4, 2, 0)

const int SEEValue[16] = {0, 0, 90, 90, 325, 325, 325, 325, 325, 325, 510, 510, 975, 975, 30000, 30000};
const int BishopPair[9] = {70, 65, 60, 55, 50, 45, 40, 35, 30};
const int MVVLVAVictim[16] = {0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5}; 
const int MVVLVAAttacker[16] = {0, 0, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 2, 7, 7};
#define MVVLVAPromotion ((1 << 24) | (MVVLVAVictim[12] << 27))
#define MVVLVAPromotionCap(capture) (MVVLVAPromotion | MVVLVA[0][capture])
#define MVVLVAXray (1 << 30)
#define MVVLVAXrayCap(capture) (MVVLVAXray | MVVLVA[0][capture])
#define KillerOneScore (0xFF << 16)
#define KillerTwoScore (0xFE << 16)

#define halt_check if ((Current - Data) >= 126) {evaluate(); return Current->score;} \
    if (Current->ply >= 100) return 0; \
	for (i = 4; i <= Current->ply; i+= 2) if (Stack[sp-i] == Current->key) return 0
#define ExtFlag(ext) ((ext) << 16)
#define Ext(flags) (((flags) >> 16) & 0xF)
#define FlagHashCheck (1 << 20) // first 20 bits are reserved for the hash killer and extension
#define FlagHaltCheck (1 << 21)
#define FlagCallEvaluation (1 << 22)
#define FlagDisableNull (1 << 23)
#define FlagNeatSearch (FlagHashCheck | FlagHaltCheck | FlagCallEvaluation)
#define FlagNoKillerUpdate (1 << 24)
#define FlagReturnBestMove (1 << 25)

#define opp (1 ^ me)
#define all (1 ^ cut)
#ifdef CUT_ALL
#define ReturnHigh (cut ? T(1) : NonWeakHigh(Entry))
#define ReturnLow (cut ? NonWeakLow(Entry) : T(1))
#define HashHigh(value, depth) if (cut) hash_high_weak(value, depth); else hash_high(value, depth)
#define HashLow(move,value, depth) if (cut) hash_low(move, value, depth); else hash_low_weak(move, value, depth)
#define CUT (cut)
#define ALL (all)
#else 
#define ReturnHigh (T(1))
#define ReturnLow (T(1))
#define HashHigh(value, depth) hash_high(value, depth)
#define HashLow(move,value, depth) hash_low(move, value, depth)
#define CUT 0
#define ALL 1
#endif
#define LSBC(x) ((x) ? lsb(x) : 0)
#define MSBC(x) ((x) ? msb(x) : 63)
#define NBC(me, x) ((me) ? MSBC(x) : LSBC(x))
#define NB(me, x) ((me) ? msb(x) : lsb(x))

const int DistC[8] = {3, 2, 1, 0, 0, 1, 2, 3};
const int RankR[8] = {-3, -2, -1, 0, 1, 2, 3, 4};
#define KnightTrapped 100
const int KingROp[8] = {4, 1, -2, -5, -10, -15, -25, -35};
const int KingFOp[8] = {40, 45, 15, -5, -5, 15, 45, 40};
const int KingVEg[8] = {2, 0, -2, -5, -8, -12, -20, -30};
const int KingREg[8] = {-30, -5, 0, 5, 10, 5, 0, -10};
const int KingFEg[8] = {-15, 0, 10, 15, 15, 10, 0, -15};

const uint64 Outpost[2] = {Convert(0x00007e7e7e000000,uint64), Convert(0x0000007e7e7e0000,uint64)};

#define KingQAttack Combine(1, 40)
#define KingRAttack Combine(1, 25)
#define KingBAttack Combine(1, 15)
#define KingNAttack Combine(1, 15)
#define KingAttack Combine(1, 0)

const int KingAttackScale[16] = {0, 1, 4, 9, 16, 25, 36, 49, 50, 50, 50, 50, 50, 50, 50, 50};

const int Shelter[3][8] = {
	30, 0, 5, 15, 20, 25, 25, 25,
	55, 0, 15, 40, 50, 55, 55, 55,
	30, 0, 10, 20, 25, 30, 30, 30
};
const int Storm[3][8] = { 
	5, 0, 35, 15, 5, 0, 0, 0,
	10, 0, 50, 20, 10, 0, 0, 0,
	10, 0, 50, 20, 10, 0, 0, 0
};
const int ShelterDiag[4][8] = {
	10, 0, 2, 4, 6, 8, 10, 10,
    8, 0, 2, 4, 6, 7, 8, 8,
    6, 0, 2, 3, 4, 5, 6, 6,
    4, 0, 1, 2, 3, 4, 4, 4
};

#define KingPawnDistance(king_colour, rp, rk, fp, fk) Max ((((king_colour) ? (rk < rp) : (rk > rp)) ? 3 : 6) * Abs(rp - rk), 6 * Abs(fp - fk))
const uint8 BlockedPawn[64] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 2, 2, 2, 2, 1, 1,
  1, 2, 3, 3, 3, 3, 2, 1,
  1, 2, 3, 5, 5, 3, 2, 1,
  1, 2, 3, 5, 5, 3, 2, 1,
  1, 2, 3, 3, 3, 3, 2, 1,
  1, 1, 2, 2, 2, 2, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0
};

const int PassedPawnValue[8] = {0, 0, 0, Compose(10, 10), Compose(20, 25), Compose(40, 50), Compose(60, 75), 0};
const int OutsidePassedPawnValue[8] = {0, 0, 0, 0, Compose(2, 5), Compose(5, 10), Compose(10, 20), 0};
const int ProtectedPassedPawnValue[8] = {0, 0, 0, 0, Compose(5, 10), Compose(10, 15), Compose(15, 25), 0};
const int ConnectedPassedPawnValue[8] = {0, 0, 0, 0, Compose(5, 10), Compose(10, 15), Compose(20, 30), 0};
const int CandidatePawnValue[8] = {0, 0, 0, Compose(5, 5), Compose(10, 12), Compose(20, 25), 0, 0};
const int MyKingPawnDistance[8] = {0, 0, 0, 1, 2, 3, 5, 0};
const int OppKingPawnDistance[8] = {0, 0, 0, 2, 4, 6, 10, 0};

const int OpposingPawnsMult[9] = {5, 4, 3, 2, 1, 0, 0, 0, 0};
const int PawnCountMult[9] = {7, 6, 5, 4, 3, 2, 1, 0, 0};

const int PassedPawnMeClear[8] = {0, 0, 0, Compose(0, 0), Compose(0, 0), Compose(3, 5), Compose(5, 10), 0};
const int PassedPawnOppClear[8] = {0, 0, 0, Compose(0, 0), Compose(5, 10), Compose(15, 30), Compose(25, 50), 0};
const int PassedPawnCanMove[8] = {0, 0, 0, Compose(1, 2), Compose(2, 3), Compose(3, 5), Compose(5, 10), 0};
const int PassedPawnIsFree[8] = {0, 0, 0, Compose(0, 0), Compose(5, 10), Compose(10, 20), Compose(20, 40), 0};
const int RankQueenEnd[8] = {0, 0, 0, Compose(5, 5), Compose(10, 10), Compose(20, 20), Compose(40, 40), 0};

#define xrayB0 Compose(0, 0)
#define xrayBmP Compose(3, 5)
#define xrayBmN Compose(3, 5)
#define xrayBmK Compose(3, 5)
#define xrayBmB Compose(0, 0)
#define xrayBmR Compose(3, 5)
#define xrayBmQ Compose(0, 0)

#define xrayBoP Compose(2, 5)
#define xrayBoN Compose(2, 5)
#define xrayBoK Compose(0, 0)
#define xrayBoB Compose(0, 0)
#define xrayBoR Compose(15, 25)
#define xrayBoQ Compose(10, 20)

#define xrayR0 Compose(0, 0)
#define xrayRmP Compose(0, 0)
#define xrayRmN Compose(3, 5)
#define xrayRmK Compose(3, 5)
#define xrayRmB Compose(3, 5)
#define xrayRmR Compose(0, 0)
#define xrayRmQ Compose(0, 0)

#define xrayRoP Compose(2, 5)
#define xrayRoN Compose(2, 5)
#define xrayRoK Compose(0, 0)
#define xrayRoB Compose(2, 5)
#define xrayRoR Compose(0, 0)
#define xrayRoQ Compose(10, 20)

#define xQ0d Compose(0, 0)
#define xQmPd Compose(1, 2)
#define xQmNd Compose(2, 4)
#define xQmKd Compose(2, 4)
#define xQmBd Compose(0, 0)
#define xQmRd Compose(2, 4)
#define xQmQd Compose(0, 0)

#define xQoPd Compose(0, 0)
#define xQoNd Compose(2, 5)
#define xQoKd Compose(0, 0)
#define xQoBd Compose(0, 0)
#define xQoRd Compose(2, 5)
#define xQoQd Compose(0, 0)

#define xQ0hv Compose(0, 0)
#define xQmPhv Compose(0, 0)
#define xQmNhv Compose(2, 4)
#define xQmKhv Compose(2, 4)
#define xQmBhv Compose(2, 4)
#define xQmRhv Compose(0, 0)
#define xQmQhv Compose(0, 0)

#define xQoPhv Compose(0, 0)
#define xQoNhv Compose(2, 5)
#define xQoKhv Compose(0, 0)
#define xQoBhv Compose(2, 5)
#define xQoRhv Compose(0, 0)
#define xQoQhv Compose(0, 0)

const int Bxray[2][16] = {
	xrayB0, xrayB0, xrayBmP, xrayBoP, xrayBmN, xrayBoN, xrayBmB, xrayBoB, xrayBmB, xrayBoB, xrayBmR, xrayBoR, xrayBmQ, xrayBoQ, xrayBmK, xrayBoK,
    xrayB0, xrayB0, xrayBoP, xrayBmP, xrayBoN, xrayBmN, xrayBoB, xrayBmB, xrayBoB, xrayBmB, xrayBoR, xrayBmR, xrayBoQ, xrayBmQ, xrayBoK, xrayBmK
};
const int Rxray[2][16] = {
	xrayR0, xrayR0, xrayRmP, xrayRoP, xrayRmN, xrayRoN, xrayRmB, xrayRoB, xrayRmB, xrayRoB, xrayRmR, xrayRoR, xrayRmQ, xrayRoQ, xrayRmK, xrayRoK,
    xrayR0, xrayR0, xrayRoP, xrayRmP, xrayRoN, xrayRmN, xrayRoB, xrayRmB, xrayRoB, xrayRmB, xrayRoR, xrayRmR, xrayRoQ, xrayRmQ, xrayRoK, xrayRmK
};
const int QxrayD[2][16] = {
	xQ0d, xQ0d, xQmPd, xQoPd, xQmNd, xQoNd, xQmBd, xQoBd, xQmBd, xQoBd, xQmRd, xQoRd, xQmQd, xQoQd, xQmKd, xQoKd,
    xQ0d, xQ0d, xQoPd, xQmPd, xQoNd, xQmNd, xQoBd, xQmBd, xQoBd, xQmBd, xQoRd, xQmRd, xQoQd, xQmQd, xQoKd, xQmKd
};
const int QxrayO[2][16] = {
	xQ0hv, xQ0hv, xQmPhv, xQoPhv, xQmNhv, xQoNhv, xQmBhv, xQoBhv, xQmBhv, xQoBhv, xQmRhv, xQoRhv, xQmQhv, xQoQhv, xQmKhv, xQoKhv,
    xQ0hv, xQ0hv, xQoPhv, xQmPhv, xQoNhv, xQmNhv, xQoBhv, xQmBhv, xQoBhv, xQmBhv, xQoRhv, xQmRhv, xQoQhv, xQmQhv, xQoKhv, xQmKhv
};

typedef struct {
	uint64 bb[16];
	uint8 square[64];
} GBoard;
__declspec(align(64)) GBoard Board[1];
uint64 Stack[2048];
int sp;
uint64 nodes, check_node, check_node2;

typedef struct {
	uint64 attacks[64];
	uint64 key, pawn_key, eval_key, att[2], patt[2], passer, xray[2], pin[2], threat, mask;
	uint8 turn, capture, castle_flags, ply, ep_square, gen_flags, piece, stage, king_att[2];
	sint16 score;
	uint16 move, killer[3], ref[2];
	int best;
	int material, pst;
	int margin, *start, *current;
	int moves[228];
} GData;
__declspec(align(64)) GData Data[128];
GData *Current = Data;
#define FlagNoQuietSort (1 << 0)

enum {
	s_gen_cap, s_good_cap, s_killer_one, s_killer_two, s_ref_one, s_ref_two, s_gen_quiet, s_quiet, s_init_bc, s_bad_cap,
	e_gen_ev, e_ev,
	r_gen_cap, r_cap, r_gen_checks, r_checks
};

#ifndef TUNER
typedef struct {
    uint32 key;
	uint16 date;
	uint16 move;
	sint16 low;
	sint16 high;
	uint16 flags;
	uint8 low_depth;
	uint8 high_depth;
} GEntry;
#define FlagWeakLow (1 << 0)
#define FlagWeakHigh (1 << 1)
#ifdef CUT_ALL
#define WeakLow(Entry) T(Entry->flags & FlagWeakLow)
#define NonWeakLow(Entry) F(Entry->flags & FlagWeakLow)
#define WeakHigh(Entry) T(Entry->flags & FlagWeakHigh)
#define NonWeakHigh(Entry) F(Entry->flags & FlagWeakHigh)
#else
#define WeakLow(Entry) T(0)
#define NonWeakLow(Entry) F(0)
#define WeakHigh(Entry) T(0)
#define NonWeakHigh(Entry) F(0)
#endif
#define initial_hash_size (8 * 1024 * 1024)
sint64 hash_size = initial_hash_size;
uint64 hash_mask = (initial_hash_size - 4);
GEntry * Hash;
GEntry * HashBase = NULL;

typedef struct {
	uint64 key;
	int shelter[2];
	uint8 light[2], dark[2], passer[2], draw[2];
	int score, dummy;
} GPawnEntry;
#define pawn_hash_size (1024 * 1024)
#define pawn_hash_mask (pawn_hash_size - 1)
__declspec(align(64)) GPawnEntry PawnHash[pawn_hash_size];

typedef struct {
	uint32 key;
	uint16 date;
	uint16 move;
	sint16 value;
	sint16 exclusion;
	uint8 depth;
	uint8 ex_depth;
	int knodes;
	int ply;
} GPVEntry;
#define pv_hash_size (1024 * 1024)
#define pv_cluster_size 4
#define pv_hash_mask (pv_hash_size - pv_cluster_size)
GPVEntry * PVHash = NULL;
GPVEntry * PVEntry;
#else
typedef struct {
    uint32 key;
	uint16 date;
	uint16 move;
	sint16 low;
	sint16 high;
	uint16 flags;
	uint8 low_depth;
	uint8 high_depth;
} GEntry;
#define initial_hash_size (64 * 1024)
sint64 hash_size = initial_hash_size;
uint64 hash_mask = (initial_hash_size - 4);
__declspec(align(64)) GEntry HashBase1[initial_hash_size];
__declspec(align(64)) GEntry HashBase2[initial_hash_size];
GEntry * Hash;
GEntry * Entry;

typedef struct {
	uint64 key;
	int shelter[2];
	uint8 light[2], dark[2], passer[2], draw[2];
	int score, dummy;
} GPawnEntry;
#define pawn_hash_size (64 * 1024)
#define pawn_hash_mask (pawn_hash_size - 1)
__declspec(align(64)) GPawnEntry PawnHashBase1[pawn_hash_size];
__declspec(align(64)) GPawnEntry PawnHashBase2[pawn_hash_size];
GPawnEntry * PawnHash;
GPawnEntry * PawnEntry;

typedef struct {
	uint32 key;
	uint16 date;
	uint16 move;
	sint16 value;
	sint16 exclusion;
	uint8 depth;
	uint8 ex_depth;
	int knodes;
	int ply;
} GPVEntry;
#define pv_hash_size (64 * 1024)
#define pv_cluster_size 4
#define pv_hash_mask (pv_hash_size - pv_cluster_size)
__declspec(align(64)) GPVEntry PVHashBase1[pv_hash_size];
__declspec(align(64)) GPVEntry PVHashBase2[pv_hash_size];
GPVEntry * PVHash;
GPVEntry * PVEntry;
#endif

typedef struct {
	uint32 key;
	sint16 value;
	uint16 move;
	sint16 exclusion;
	sint16 weight;
	uint8 depth;
	uint8 ex_depth;
	int time;
} GStoreEntry;
#define store_hash_size (1024 * 1024)
#define store_hash_mask (store_hash_size - 4)
GStoreEntry * StoreHash = NULL;
GStoreEntry * StoreEntry;

typedef struct {
	int move;
	int score;
	int stage;
	int flags;
} GSort;

typedef struct {
	int number, pos;
	GSort sort[256];
} GSortList;
GSortList RootList[1];

#ifdef PREFETCH
#define prefetch(a,mode) _mm_prefetch(a,mode)
#else
#define prefetch(a,mode) 1
#endif

uint64 Forward[2][8];
uint64 West[8];
uint64 East[8];
uint64 AreaB[8];
uint64 AreaS[8];
uint64 AreaC[8];
uint64 PIsolated[8];
uint64 MDiag[64];
uint64 HLine[64];
uint64 VLine[64];
uint64 NDiag[64];
uint64 SDiag[64];
uint64 RMask[64];
uint64 BMask[64];
uint64 QMask[64];
uint64 BMagicMask[64];
uint64 RMagicMask[64];
uint64 QMagicMask[64];
uint64 NAtt[64];
uint64 SArea[64];
uint64 DArea[64];
uint64 NArea[64];
uint64 PAtt[2][64];
uint64 PMove[2][64];
uint64 PWay[2][64];
uint64 PSupport[2][64];
uint64 Between[64][64];
uint64 FullLine[64][64];

#define magic_size 107648
uint64 * MagicAttacks;
typedef struct {
	sint16 score;
	uint8 mul_w;
	uint8 mul_b;
	uint8 phase;
	uint8 pieces_w;
	uint8 pieces_b;
	uint8 flags;
} GMaterial;
GMaterial * Material;
#define FlagCallEvalEndgame_w (1 << 0)
#define FlagCallEvalEndgame_b (1 << 1)
#define FlagSingleBishop_w (1 << 2)
#define FlagSingleBishop_b (1 << 3)
#define FlagNoHeavy_w (1 << 4)
#define FlagNoHeavy_b (1 << 5)
#define FlagNoLight_w (1 << 6)
#define FlagNoLight_b (1 << 7)

#ifdef LOCAL_TUNER
typedef struct {
	volatile long long eval_sum;
	volatile double cov_sum;
	int w, d, l;
} GMaterialStat;
GMaterialStat * MatStat;
volatile LONG MatStatLock = 0;
typedef struct {
	int games;
	int score_x2;
} GEvalStat;
GEvalStat * EvalStat;
volatile LONG EvalStatLock = 0;
#ifndef MAT_STAT
int CollectMatStat = 0;
#else
int CollectMatStat = 1;
#endif
#define MatStatPosInRow 5
int MatList[1024];
int EvalList[1024];
#endif

int PST[16][64];
int MVVLVA[16][16]; // [piece][capture]
uint64 TurnKey;
uint64 PieceKey[16][64];
uint64 CastleKey[16];
uint64 EPKey[8];
uint16 date;

uint64 KPK[2][64][64]; 

#ifndef TUNER
sint16 History[16][64]; // may be replaced by History[16][4096]
#define HistoryP(piece,from,to) ((Convert(History[piece][to] & 0xFF00,int)/Convert(History[piece][to] & 0x00FF,int)) << 16)
#define History(from,to) HistoryP(Square(from),from,to)
#define HistoryM(move) History[Square(From(move))][To(move)]
#define HistoryScore(depth) Min(((depth) >> 1) * ((depth) >> 1), 64)
#define HistoryGood(move) if ((HistoryM(move) & 0x00FF) >= 256 - HistoryScore(depth)) \
	HistoryM(move) = ((HistoryM(move) & 0xFEFE) >> 1) + ((HistoryScore(depth) << 8) |HistoryScore(depth)); \
	else HistoryM(move) += ((HistoryScore(depth) << 8) | HistoryScore(depth))
#define HistoryBad(move) if ((HistoryM(move) & 0x00FF) >= 256 - HistoryScore(depth)) \
	HistoryM(move) = ((HistoryM(move) & 0xFEFE) >> 1) + HistoryScore(depth); else HistoryM(move) += HistoryScore(depth)

sint16 Delta[16][4096]; // may be replaced by Delta[16][64]
#define DeltaP(piece,from,to) Delta[piece][((from) << 6) | (to)]
#define Delta(from,to) Delta[Square(from)][((from) << 6) | (to)]
#define DeltaM(move) Delta(From(move),To(move))
#define UpdateDelta if (F(Current->capture) && T(Current->move) && F(Current->move & 0xE000) && Current > Data) { \
	if (DeltaP(Current->piece,From(Current->move),To(Current->move)) <= -Current->score - ((Current - 1)->score)) \
	DeltaP(Current->piece,From(Current->move),To(Current->move)) = -Current->score - ((Current - 1)->score); \
	else DeltaP(Current->piece,From(Current->move),To(Current->move))--; }
#define DeltaMarginP(piece,from,to) (DeltaP(piece,from,to) >= Current->margin)
#define DeltaMargin(from,to) (Delta(from,to) >= Current->margin)

typedef struct {
	uint16 ref[2];
} GRef;
GRef Ref[16][64]; // may be replaced by Ref[16][4096]
#define RefP(piece,from,to) Ref[piece][to]
#define RefM(move) RefP(Square(To(move)),From(move),To(move))
#define UpdateRef(ref_move) if (T(Current->move) && RefM(Current->move).ref[0] != (ref_move)) { \
	RefM(Current->move).ref[1] = RefM(Current->move).ref[0]; RefM(Current->move).ref[0] = (ref_move); }
#else
sint16 History1[16 * 64];
sint16 History2[16 * 64];
sint16 * History;
#define HistoryP(piece,from,to) ((Convert(History[((piece) << 6) | (to)] & 0xFF00,int)/Convert(History[((piece) << 6) | (to)] & 0x00FF,int)) << 16)
#define History(from,to) HistoryP(Square(from),from,to)
#define HistoryM(move) History[(Square(From(move)) << 6) | To(move)]
#define HistoryScore(depth) Min(((depth) >> 1) * ((depth) >> 1), 64)
#define HistoryGood(move) if ((HistoryM(move) & 0x00FF) >= 256 - HistoryScore(depth)) \
	HistoryM(move) = ((HistoryM(move) & 0xFEFE) >> 1) + ((HistoryScore(depth) << 8) |HistoryScore(depth)); \
	else HistoryM(move) += ((HistoryScore(depth) << 8) | HistoryScore(depth))
#define HistoryBad(move) if ((HistoryM(move) & 0x00FF) >= 256 - HistoryScore(depth)) \
	HistoryM(move) = ((HistoryM(move) & 0xFEFE) >> 1) + HistoryScore(depth); else HistoryM(move) += HistoryScore(depth)

sint16 Delta1[16 * 64 * 64];
sint16 Delta2[16 * 64 * 64];
sint16 * Delta;
#define DeltaP(piece,from,to) Delta[((piece) << 12) | ((from) << 6) | (to)]
#define Delta(from,to) Delta[(Square(from) << 12) | ((from) << 6) | (to)]
#define DeltaM(move) Delta(From(move),To(move))
#define UpdateDelta if (F(Current->capture) && T(Current->move) && F(Current->move & 0xE000) && Current > Data) { \
	if (DeltaP(Current->piece,From(Current->move),To(Current->move)) <= -Current->score - ((Current - 1)->score)) \
	DeltaP(Current->piece,From(Current->move),To(Current->move)) = -Current->score - ((Current - 1)->score); \
	else DeltaP(Current->piece,From(Current->move),To(Current->move))--; }
#define DeltaMarginP(piece,from,to) (DeltaP(piece,from,to) >= Current->margin)
#define DeltaMargin(from,to) (Delta(from,to) >= Current->margin)

typedef struct {
	uint16 ref[2];
} GRef;
GRef Ref1[16 * 64];
GRef Ref2[16 * 64];
GRef * Ref;
#define RefP(piece,from,to) Ref[((piece) << 6) | (to)]
#define RefM(move) RefP(Square(To(move)),From(move),To(move))
#define UpdateRef(ref_move) if (T(Current->move) && RefM(Current->move).ref[0] != (ref_move)) { \
	RefM(Current->move).ref[1] = RefM(Current->move).ref[0]; RefM(Current->move).ref[0] = (ref_move); }
#endif

uint64 seed = 1;
uint8 PieceFromChar[256];
uint16 PV[128];
char info_string[1024];
char pv_string[1024];
char score_string[16];
char input_string[65536];
int MultiPV[256];
int pvp;
int pv_length;
int best_move, best_score;
#ifdef CUT_ALL
int pv_height;
#endif
int TimeLimit1, TimeLimit2, Console, HardwarePopCnt, GlobalTime, GlobalInc;
int DepthLimit, LastDepth, LastTime, LastValue, LastExactValue, PrevMove, InstCnt;
sint64 LastSpeed;
int PVN, Stop, Print, Input = 1, CPUTime = 0, PVHashing = 1, Infinite, MoveTime, SearchMoves, SMPointer, Ponder, Searching, Previous;
typedef struct {
	int Bad, Change, Singular, Early, FailLow, FailHigh;
} GSearchInfo;
GSearchInfo CurrentSI[1], BaseSI[1];
int LargePages = 1, Aspiration = 1;
#define TimeSingTwoMargin 20
#define TimeSingOneMargin 30
#define TimeNoPVSCOMargin 60
#define TimeNoChangeMargin 70
#define TimeRatio 120
#define PonderRatio 120
#define MovesTg 30
#define InfoLag 5000
#define InfoDelay 1000
sint64 StartTime, InfoTime, CurrTime;
uint16 SMoves[256];
jmp_buf Jump, CheckJump, ResetJump;
HANDLE StreamHandle; 
#define CyclesPerMSec Convert(3400000, sint64)
#define CPUTimeBaseMul 10
#define CPUTimeIncMul 10
#ifdef LONGEST_LINE
int LLine[128];
int LLSave[128];
int LLLength = 0;
#endif
#ifdef HASH_READER
FILE * fhr;
#endif
#define ExclSingle(depth) ((depth)/2)
#define ExclDouble(depth) (depth)
#define ExclSinglePV(depth) Min(16,(depth)/2)
#define ExclDoublePV(depth) Min(32,depth)

const int PstPawnToQueen[18 * 5] = {
	/*0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*/
	-30,15,-71,-119,-40,80,-46,33,-11,-18,-22,-171,-65,52,152,209,146,-526,-169,-192,-185,-45,-197,-140,-109,-65,113,-32,-13,151,-221,-80,151,238,-94,60,-103,-86,-25,-73,-161,-43,-121,12,93,13,-13,-32,-125,-93,-89,200,272,731,-64,-7,-29,-14,-9,-98,9,-148,-61,14,34,-5,91,10,-31,127,-248,193,-110,-140,-35,18,-25,-77,-8,-316,-66,39,3,179,-15,-105,-37,451,1921,1960
};

#ifdef TUNER
typedef struct {
	int value;
	int active;
	double var;
} GEvalVar;
#define VarMargin 0.1 // parameters with var below VarMargin may be considered inactive

GEvalVar Variables[256];
int VarIndex[256];
int IndexVar[256];
int var_number = 0;
#define V(index) (Variables[index].value)
double FirstEval[256], SecondEval[256], DefaultEval[256], BestEval[256];
double VarMax[256], VarBase[256];
int command = 0;

typedef struct {
	double grad[256];
} GGradient;

char Fen[65536][128];
int op_pos_number = 0;
GBoard SaveBoard[1];
GData SaveData[1];
int sp_save;
int wins, draws, losses;
#ifndef MAT_STAT
int ResignThreshold = 350;
#else
int ResignThreshold = 600;
#endif
int MaxNodes = 0;

enum {
	IPstPawnToQueen, IPstKingOp = IPstPawnToQueen + (18 * 5), IPstKingEg,
	IPawnBlockedOp, IPawnBlockedEg, IPawnIslandOp, IPawnIslandEg, IPawnHoleOp, IPawnHoleEg,
	IKnightOutpostOp, IKnightOutpostEg, IKnightOutpostProtectedOp, IKnightOutpostProtectedEg, IBishopOutpostOp, IBishopOutpostEg,
    IKnightMobilityOp, IKnightMobilityEg, IBishopMobilityOp, IBishopMobilityEg, IRookMobilityOp, IRookMobilityEg, IQueenMobilityOp, IQueenMobilityEg,
	IQueenSeventhRankOp, IQueenSeventhRankEg, IQueenSeventhRankDoubledOp, IQueenSeventhRankDoubledEg,
	IRookHOFOp, IRookHOFEg, IRookHOFPawnAttOp, IRookHOFPawnAttEg, IRookHOFKingAttOp, IRookHOFKingAttEg, 
	IRookOFOp, IRookOFEg, IRookOFMinorAttOp, IRookOFMinorAttEg, IRookOFMinorFixedOp, IRookOFMinorFixedEg,
	IRookSeventhRankOp, IRookSeventhRankEg, IRookSeventhRankDoubledOp, IRookSeventhRankDoubledEg,
	IRookEighthRankOp, IRookEighthRankEg, IRookSixthRankOp, IRookSixthRankEg,
	IDoubledClosedOp, IDoubledClosedEg, IDoubledClosedIsolatedOp, IDoubledClosedIsolatedEg, IIsolatedClosedOp, IIsolatedClosedEg, IBackwardClosedOp, IBackwardClosedEg,
	IDoubledOpenOp, IDoubledOpenEg, IDoubledOpenIsolatedOp, IDoubledOpenIsolatedEg, IIsolatedOpenOp, IIsolatedOpenEg, IBackwardOpenOp, IBackwardOpenEg,
	IMaterialMe, IMaterialOpp = IMaterialMe + 14
};
#define C(x) Compose(V(I##x##Op),V(I##x##Eg))
#define S(x) V(I##x)
#define TrIndex(width,row,column) ((((row) * ((width) + (width) - (row) + 1)) >> 1) + (column))
#define Tr(x,width,row,column) V(I##x + TrIndex(width,row,column))
#define StAIndex(width,row,column) (((row) * (width)) + (column))
#define StA(x,width,row,column) V(I##x + StAIndex(width,row,column))
#else
#define C(x) (x)
#define S(x) (x)
#define TrIndex(width,row,column) ((((row) * ((width) + (width) - (row) + 1)) >> 1) + (column))
#define Tr(x,width,row,column) (*((x) + TrIndex(width,row,column)))
#define StAIndex(width,row,column) (((row) * (width)) + (column))
#define StA(x,width,row,column) (*((x) + StAIndex(width,row,column)))

#define PstKing Compose(70,98)
#define PawnBlocked Compose(5,12)
#define PawnIsland Compose(6,2)
#define PawnHole Compose(4,5)
#define KnightOutpost Compose(12,2)
#define KnightOutpostProtected Compose(9,7)
#define BishopOutpost Compose(4,9)
#define KnightMobility Compose(6,3)
#define BishopMobility Compose(5,3)
#define RookMobility Compose(2,3)
#define QueenMobility Compose(2,4)
#define QueenSeventhRank Compose(-5,19)
#define QueenSeventhRankDoubled Compose(2,13)
#define RookHOF Compose(4,0)
#define RookHOFPawnAtt Compose(9,10)
#define RookHOFKingAtt Compose(9,0)
#define RookOF Compose(19,15)
#define RookOFMinorAtt Compose(18,6)
#define RookOFMinorFixed Compose(7,-1)
#define RookSeventhRank Compose(8,16)
#define RookSeventhRankDoubled Compose(15,13)
#define RookEighthRank Compose(7,0)
#define RookSixthRank Compose(12,4)
#define DoubledClosed Compose(0,1)
#define DoubledClosedIsolated Compose(2,10)
#define IsolatedClosed Compose(2,6)
#define BackwardClosed Compose(0,2)
#define DoubledOpen Compose(6,4)
#define DoubledOpenIsolated Compose(0,3)
#define IsolatedOpen Compose(14,16)
#define BackwardOpen Compose(13,13)
const int MaterialMe[14] = {
	0, 0, 0, 0, 0, // Pawn: pawns, knights, bishops, rooks, queens
	0, 0, 0, 0, // Knight: knights, bishops, rooks, queens
	0, 0, 0, // Bishop: bishops, rooks, queens
	0, 0 // Rook: rooks, queens
};
const int MaterialOpp[15] = {
	0, 0, 0, 0, 0, // Pawn: 1, knights, bishops, rooks, queens
	0, 0, 0, 0, // Knight: 1, bishops, rooks, queens
	0, 0, 0, // Bishop: 1, rooks, queens
	0, 0, // Rook: 1, queens
	0 // Queen: 1
};
#endif
#define MatScoreShiftNumber 1614 // 131072 games at d7/8
const int MatScoreShift[MatScoreShiftNumber * 2] = {
    215136, 47, 226800, 42, 28512, -47, 133488, -42, 343440, 21, 250128, -21, 460080, 6, 366768, -6, 576720, 7, 483408, -7, 223560, 36, 25272, -40,
    130248, -30, 340200, 16, 246888, -8, 573480, 10, 678456, 22, 122472, 50, 134136, 23, 214164, 40, 225828, 30, 132516, -36, 342468, 8, 249156, -16,
    482436, -10, 494100, -22, 122148, -50, 227124, -23, 222588, 19, 129276, -19, 249804, 5, 340524, -5, 227772, 16, 134460, -16, 223074, 36, 24786, -40,
    129762, -30, 339714, 16, 246402, -8, 572994, 10, 677970, 22, 121986, 50, 133650, 23, 210438, 75, 222102, 24, 327078, 25, 23814, -75, 128790, -24,
    140454, -25, 572022, -9, 478710, 9, 109350, 120, 121014, 50, 132678, 15, 249318, 21, 13446, -120, 118422, -50, 223398, -15, 340038, -21, 227286, 29,
    133974, -29, 343926, 15, 448902, 56, 250614, -15, 460566, 16, 565542, 29, 262278, -56, 367254, -16, 577206, 14, 378918, -29, 483894, -14, 129438, 57,
    224046, 75, 340686, 51, 142398, -39, 457326, 27, 259038, -11, 573966, 22, 375678, -32, 690606, 5, 213921, 40, 225585, 30, 132273, -36, 342225, 8,
    248913, -16, 482193, -10, 493857, -22, 121905, -50, 226881, -23, 210681, 75, 222345, 24, 327321, 25, 24057, -75, 129033, -24, 140697, -25, 572265, -9,
    478953, 9, 109593, 120, 121257, 50, 132921, 15, 249561, 21, 13689, -120, 118665, -50, 223641, -15, 340281, -21, 227529, 29, 134217, -29, 344169, 15,
    449145, 56, 250857, -15, 460809, 16, 565785, 29, 262521, -56, 367497, -16, 577449, 14, 379161, -29, 484137, -14, 222669, -57, 331533, 39, 133245, -75,
    448173, 11, 249885, -51, 564813, 32, 366525, -27, 483165, -22, 599805, -5, 221859, 19, 128547, -19, 249075, 5, 339795, -5, 227043, 16, 133731, -16,
    129195, 57, 223803, 75, 340443, 51, 142155, -39, 457083, 27, 258795, -11, 573723, 22, 375435, -32, 690363, 5, 222183, -57, 331047, 39, 132759, -75,
    447687, 11, 249399, -51, 564327, 32, 366039, -27, 482679, -22, 599319, -5, 222831, 19, 129519, -19, 339471, 6, 246159, -6, 117963, 43, 129627, 31,
    246267, 13, 491211, -16, 116991, 88, 128655, 51, 233631, 53, 245295, 38, 350271, 23, 361935, 17, 490239, -14, 106623, 23, 211599, 48, 13311, -11,
    328239, 25, 444879, 26, 561519, 8, 235575, 18, 247239, 6, 12177, 120, 118449, 62, 130113, 15, 235089, 38, 246753, 21, 468369, 19, 585009, 5,
    116748, 88, 128412, 51, 233388, 53, 245052, 38, 350028, 23, 361692, 17, 489996, -14, 106380, 23, 211356, 48, 13068, -11, 327996, 25, 444636, 26,
    561276, 8, 12420, 120, 118692, 62, 130356, 15, 235332, 38, 246996, 21, 468612, 19, 585252, 5, 466992, 14, 571968, 18, 117720, 15, 234360, 40,
    246024, 7, 351000, 20, 234846, 18, 246510, 6, 117234, 15, 233874, 40, 245538, 7, 350514, 20, 120537, -43, 225513, -31, 342153, -13, 680409, 16,
    117297, -88, 222273, -51, 233937, -53, 338913, -38, 350577, -23, 455553, -17, 677169, 14, 109521, 11, 16209, -23, 27873, -48, 144513, -25, 261153, -26,
    377793, -8, 238149, -18, 343125, -6, 116811, -88, 221787, -51, 233451, -53, 338427, -38, 350091, -23, 455067, -17, 676683, 14, 109035, 11, 15723, -23,
    27387, -48, 144027, -25, 260667, -26, 377307, -8, 467379, -14, 479043, -18, 105471, -120, 121023, -62, 225999, -15, 237663, -38, 342639, -21, 470943, -19,
    587583, -5, 117783, -15, 234423, -40, 339399, -7, 351063, -20, 105714, -120, 121266, -62, 226242, -15, 237906, -38, 342882, -21, 471186, -19, 587826, -5,
    237420, -18, 342396, -6, 117540, -15, 234180, -40, 339156, -7, 350820, -20, 105012, -13, 209988, -9, 11700, 13, 326628, -24, 23364, 9, 443268, -28,
    140004, 24, 454932, -8, 256644, 28, 361620, 8, 571572, -15, 478260, 15, 688212, -13, 594900, 13, 804852, -8, 711540, 8, 120564, 54, 132228, 41,
    143892, 11, 248868, 22, 388836, -10, 117972, -54, 222948, -41, 327924, -11, 339588, -22, 666180, 10, 110196, 32, 215172, 59, 16884, -32, 226836, 33,
    331812, 38, 28548, -59, 133524, -33, 343476, 20, 448452, 45, 145188, -38, 250164, -20, 460116, 16, 565092, 28, 261828, -45, 366804, -16, 576756, 10,
    681732, 20, 378468, -28, 483444, -10, 495108, -20, 128988, 27, 268956, -14, 373932, -5, 385596, -5, 490572, -9, 106956, 35, 211932, 51, 13644, -20,
    223596, 25, 328572, 34, 25308, -56, 130284, -13, 340236, 20, 445212, 16, 141948, -24, 246924, -16, 456876, 11, 258588, -26, 363564, -12, 573516, 8,
    678492, 17, 375228, -10, 480204, -7, 495756, -14, 221976, -27, 548568, 14, 560232, 5, 665208, 5, 676872, 9, 109224, 20, 214200, 56, 15912, -35,
    225864, 13, 330840, 24, 27576, -51, 132552, -25, 342504, 16, 447480, 26, 144216, -34, 249192, -20, 459144, 12, 564120, 10, 260856, -16, 365832, -11,
    575784, 7, 482472, -8, 494136, -17, 682056, 14, 105984, 18, 210960, 17, 12672, -18, 222624, 16, 327600, 29, 24336, -17, 129312, -16, 339264, 13,
    444240, 14, 140976, -29, 245952, -13, 560880, 8, 257616, -14, 677520, 20, 374256, -8, 490896, -20, 332784, 20, 449424, 5, 146160, -20, 461088, 8,
    262800, -5, 367776, -8, 682704, 17, 496080, -17, 128502, 27, 268470, -14, 373446, -5, 385110, -5, 490086, -9, 106470, 35, 211446, 51, 13158, -20,
    223110, 25, 328086, 34, 24822, -56, 129798, -13, 339750, 20, 444726, 16, 141462, -24, 246438, -16, 456390, 11, 258102, -26, 363078, -12, 573030, 8,
    678006, 17, 374742, -10, 479718, -7, 495270, -14, 105498, 62, 210474, 61, 12186, -62, 222138, 27, 327114, 20, 23850, -61, 128826, -27, 338778, 18,
    443754, 22, 140490, -20, 245466, -18, 455418, 6, 560394, 18, 257130, -22, 362106, -6, 572058, 7, 677034, 8, 373770, -18, 478746, -7, 490410, -8,
    448938, 25, 565578, 13, 262314, -25, 577242, 13, 682218, 13, 378954, -13, 483930, -13, 693882, 6, 495594, -13, 600570, -6, 340722, 17, 445698, 66,
    457362, 6, 259074, -11, 574002, 19, 678978, 47, 375714, -23, 690642, 12, 492354, -22, 221733, -27, 548325, 14, 559989, 5, 664965, 5, 676629, 9,
    108981, 20, 213957, 56, 15669, -35, 225621, 13, 330597, 24, 27333, -51, 132309, -25, 342261, 16, 447237, 26, 143973, -34, 248949, -20, 458901, 12,
    563877, 10, 260613, -16, 365589, -11, 575541, 7, 482229, -8, 493893, -17, 681813, 14, 105741, 62, 210717, 61, 12429, -62, 222381, 27, 327357, 20,
    24093, -61, 129069, -27, 339021, 18, 443997, 22, 140733, -20, 245709, -18, 455661, 6, 560637, 18, 257373, -22, 362349, -6, 572301, 7, 677277, 8,
    374013, -18, 478989, -7, 490653, -8, 449181, 25, 565821, 13, 262557, -25, 577485, 13, 682461, 13, 379197, -13, 484173, -13, 694125, 6, 495837, -13,
    600813, -6, 448209, 11, 249921, -17, 564849, 23, 261585, -66, 366561, -6, 681489, 22, 483201, -19, 494865, -47, 599841, -12, 105255, 18, 210231, 17,
    11943, -18, 221895, 16, 326871, 29, 23607, -17, 128583, -16, 338535, 13, 443511, 14, 140247, -29, 245223, -13, 560151, 8, 256887, -14, 676791, 20,
    373527, -8, 490167, -20, 332055, 20, 448695, 5, 145431, -20, 460359, 8, 262071, -5, 367047, -8, 681975, 17, 495351, -17, 340479, 17, 445455, 66,
    457119, 6, 258831, -11, 573759, 19, 678735, 47, 375471, -23, 690399, 12, 492111, -22, 447723, 11, 249435, -17, 564363, 23, 261099, -66, 366075, -6,
    681003, 22, 482715, -19, 494379, -47, 599355, -12, 256671, 35, 117999, 12, 234639, 15, 117027, 25, 233667, 41, 245331, 9, 350307, 24, 361971, 6,
    268659, -25, 583587, 7, 700227, 19, 549891, 29, 561555, 8, 666531, 41, 701523, 20, 472131, 24, 378819, -5, 468405, 7, 701685, 7, 116784, 25,
    233424, 41, 245088, 9, 350064, 24, 361728, 6, 268416, -25, 583344, 7, 699984, 19, 549648, 29, 561312, 8, 666288, 41, 701280, 20, 471888, 24,
    378576, -5, 468648, 7, 701928, 7, 572004, 10, 351036, 11, 456012, 26, 584316, 8, 350550, 11, 455526, 26, 583830, 8, 443277, -35, 120573, -12,
    237213, -15, 117333, -25, 233973, -41, 338949, -9, 548901, 25, 350613, -24, 455589, -6, 583893, -7, 700533, -19, 272853, -29, 377829, -8, 389493, -41,
    704421, -20, 565749, 5, 472437, -24, 116847, -25, 233487, -41, 338463, -9, 548415, 25, 350127, -24, 455103, -6, 583407, -7, 700047, -19, 272367, -29,
    377343, -8, 389007, -41, 703935, -20, 565263, 5, 471951, -24, 479079, -10, 470979, -7, 704259, -7, 351099, -11, 362763, -26, 584379, -8, 471222, -7,
    704502, -7, 350856, -11, 362520, -26, 584136, -8, 105048, 10, 210024, 50, 315000, 75, 11736, -10, 221688, 10, 326664, 20, 23400, -50, 128376, -10,
    338328, 11, 443304, 29, 35064, -75, 140040, -20, 245016, -11, 454968, 13, 559944, 29, 256680, -29, 361656, -13, 571608, 5, 676584, 11, 373320, -29,
    478296, -5, 489960, -11, 248904, 44, 339624, -44, 448488, 15, 261864, -15, 681768, 27, 495144, -27, 478944, 6, 385632, -9, 490608, -15, 456912, 7,
    375264, -16, 480240, -7, 491904, -17, 596880, -5, 665244, 9, 571932, -6, 676908, 15, 564156, 16, 365868, -7, 575820, 7, 680796, 17, 692460, 5,
    444276, 12, 560916, 13, 257652, -12, 677556, 6, 374292, -13, 490932, -6, 682740, 25, 799380, 13, 496116, -25, 612756, -13, 478458, 6, 385146, -9,
    490122, -15, 456426, 7, 374778, -16, 479754, -7, 491418, -17, 596394, -5, 327150, 6, 140526, -6, 560430, 20, 572094, 14, 677070, 6, 373806, -20,
    478782, -14, 688734, 12, 490446, -6, 595422, -12, 679014, 41, 375750, -5, 690678, 14, 492390, -6, 579222, 5, 695862, 10, 812502, 17, 719190, -6,
    665001, 9, 571689, -6, 676665, 15, 563913, 16, 365625, -7, 575577, 7, 680553, 17, 692217, 5, 327393, 6, 140769, -6, 560673, 20, 572337, 14,
    677313, 6, 374049, -20, 479025, -14, 688977, 12, 490689, -6, 595665, -12, 564885, 5, 681525, 6, 494901, -41, 599877, -14, 488421, -5, 605061, -10,
    815013, 6, 721701, -17, 443547, 12, 560187, 13, 256923, -12, 676827, 6, 373563, -13, 490203, -6, 682011, 25, 798651, 13, 495387, -25, 612027, -13,
    678771, 41, 375507, -5, 690435, 14, 492147, -6, 578979, 5, 695619, 10, 812259, 17, 718947, -6, 564399, 5, 681039, 6, 494415, -41, 599391, -14,
    487935, -5, 604575, -10, 814527, 6, 721215, -17, 694647, 8, 601335, -8, 699831, 10, 606519, -10, 11676, 120, 23340, 58, 128316, 120, 139980, 28,
    117948, 21, 222924, 72, 234588, 41, 456204, 46, 116976, 57, 221952, 75, 233616, 51, 338592, 57, 350256, 13, 116733, 57, 221709, 75, 233373, 51,
    338349, 57, 350013, 13, 104997, 13, 209973, 70, 221637, 15, 326613, 67, 431589, 57, 128325, -10, 338277, 27, 443253, 54, 244965, -9, 454917, 6,
    559893, 33, 361605, -14, 587433, -12, 587190, -12, 466932, 34, 583572, 19, 466689, 34, 583329, 19, 105004, -120, 209980, -58, 221644, -120, 326620, -28,
    120556, -21, 132220, -72, 237196, -41, 365500, -46, 117316, -57, 128980, -75, 233956, -51, 245620, -57, 350596, -13, 116830, -57, 128494, -75, 233470, -51,
    245134, -57, 350110, -13, 11719, -13, 221671, 10, 23383, -70, 128359, -15, 338311, 9, 140023, -67, 244999, -27, 454951, 14, 151687, -57, 256663, -54,
    361639, -6, 373303, -33, 585199, 12, 584713, 12, 467272, -34, 583912, -19, 466786, -34, 583426, -19, 104980, 38, 209956, 58, 11668, -38, 221620, 31,
    326596, 54, 23332, -58, 128308, -31, 338260, 20, 443236, 23, 139972, -54, 244948, -20, 454900, 8, 256612, -23, 361588, -8, 120532, 57, 132196, 18,
    248836, 18, 117940, -57, 222916, -18, 339556, -18, 226804, 10, 133492, -10, 343444, 6, 448420, 27, 250132, -6, 460084, 16, 565060, 20, 261796, -27,
    366772, -16, 576724, 11, 378436, -20, 483412, -11, 693364, 10, 600052, -10, 117292, 84, 128956, 42, 245596, 29, 362236, 10, 478876, 5, 583852, 87,
    595516, 12, 223564, 27, 328540, 73, 130252, -5, 340204, 15, 445180, 19, 246892, -14, 456844, 23, 561820, 24, 258556, -31, 573484, 11, 678460, 15,
    375196, -42, 480172, -8, 690124, 14, 596812, -9, 116968, -84, 221944, -42, 338584, -29, 455224, -10, 571864, -5, 583528, -87, 688504, -12, 225832, 5,
    132520, -27, 342472, 14, 447448, 31, 144184, -73, 249160, -15, 564088, 42, 260824, -19, 365800, -23, 575752, 8, 377464, -24, 482440, -11, 692392, 9,
    494104, -15, 599080, -14, 339232, 8, 444208, 25, 245920, -8, 455872, 8, 257584, -25, 362560, -8, 572512, 8, 479200, -8, 689152, 13, 595840, -13,
    577696, 6, 484384, -6, 116806, 84, 128470, 42, 245110, 29, 361750, 10, 478390, 5, 583366, 87, 595030, 12, 223078, 27, 328054, 73, 129766, -5,
    339718, 15, 444694, 19, 246406, -14, 456358, 23, 561334, 24, 258070, -31, 572998, 11, 677974, 15, 374710, -42, 479686, -8, 689638, 14, 596326, -9,
    222106, 48, 327082, 78, 128794, -48, 338746, 34, 443722, 82, 140458, -78, 245434, -34, 455386, 27, 560362, 53, 257098, -82, 362074, -27, 572026, 25,
    677002, 48, 373738, -53, 478714, -25, 688666, 17, 490378, -48, 595354, -17, 457330, 10, 573970, 18, 116725, -84, 221701, -42, 338341, -29, 454981, -10,
    571621, -5, 583285, -87, 688261, -12, 225589, 5, 132277, -27, 342229, 14, 447205, 31, 143941, -73, 248917, -15, 563845, 42, 260581, -19, 365557, -23,
    575509, 8, 377221, -24, 482197, -11, 692149, 9, 493861, -15, 598837, -14, 222349, 48, 327325, 78, 129037, -48, 338989, 34, 443965, 82, 140701, -78,
    245677, -34, 455629, 27, 560605, 53, 257341, -82, 362317, -27, 572269, 25, 677245, 48, 373981, -53, 478957, -25, 688909, 17, 490621, -48, 595597, -17,
    366529, -10, 483169, -18, 338503, 8, 443479, 25, 245191, -8, 455143, 8, 256855, -25, 361831, -8, 571783, 8, 478471, -8, 688423, 13, 595111, -13,
    576967, 6, 483655, -6, 457087, 10, 573727, 18, 366043, -10, 482683, -18, 128335, 120, 256639, 114, 361615, 120, 373279, 75, 478255, 120, 234607, 17,
    351247, 20, 467887, 36, 233635, 23, 350275, 48, 466915, 43, 385267, -7, 700195, 19, 456547, 13, 678163, 9, 588739, 11, 468373, 16, 585013, 20,
    233392, 23, 350032, 48, 466672, 43, 385024, -7, 699952, 19, 456304, 13, 677920, 9, 588496, 11, 468616, 16, 585256, 20, 221629, -120, 443245, -114,
    454909, -120, 559885, -75, 571549, -120, 237181, -17, 353821, -20, 470461, -36, 233941, -23, 350581, -48, 665509, 7, 467221, -43, 700501, -19, 366133, -13,
    494437, -9, 589045, -11, 233455, -23, 350095, -48, 665023, 7, 466735, -43, 700015, -19, 365647, -13, 493951, -9, 588559, -11, 470947, -16, 587587, -20,
    471190, -16, 587830, -20, 221656, 13, 326632, 18, 128344, -13, 338296, 11, 443272, 27, 140008, -18, 244984, -11, 454936, 9, 559912, 29, 256648, -27,
    361624, -9, 571576, 9, 676552, 23, 373288, -29, 478264, -9, 489928, -23, 248872, 9, 365512, 16, 388840, -11, 598792, 9, 339592, -9, 456232, -16,
    666184, 11, 689512, -9, 448456, 23, 565096, 17, 261832, -23, 576760, 9, 681736, 25, 378472, -17, 483448, -9, 693400, 5, 495112, -25, 600088, -5,
    362272, 14, 478912, 20, 445216, 37, 456880, 6, 561856, 27, 258592, -7, 363568, -7, 678496, 29, 375232, -43, 480208, -14, 795136, 11, 491872, -25,
    600736, 6, 455260, -14, 571900, -20, 447484, 7, 459148, 7, 564124, 43, 260860, -37, 365836, -6, 575788, 14, 680764, 25, 377500, -27, 494140, -29,
    610780, -11, 693724, -6, 444244, 24, 560884, 21, 257620, -24, 677524, 27, 374260, -21, 490900, -27, 471460, 62, 483124, 35, 588100, 57, 389812, -7,
    599764, 13, 667156, 7, 468868, -62, 573844, -35, 585508, -57, 690484, -13, 566068, 9, 577732, 7, 682708, 14, 379444, -9, 484420, -7, 496084, -14,
    361786, 14, 478426, 20, 444730, 37, 456394, 6, 561370, 27, 258106, -7, 363082, -7, 678010, 29, 374746, -43, 479722, -14, 794650, 11, 491386, -25,
    600250, 6, 338782, 9, 443758, 27, 245470, -9, 560398, 41, 257134, -27, 572062, 9, 677038, 25, 373774, -41, 478750, -9, 688702, 16, 490414, -25,
    595390, -16, 482638, 20, 573358, -20, 565582, 20, 682222, 37, 378958, -20, 693886, 17, 495598, -37, 600574, -17, 457366, 14, 574006, 17, 678982, 11,
    690646, 15, 579190, 15, 455017, -14, 571657, -20, 447241, 7, 458905, 7, 563881, 43, 260617, -37, 365593, -6, 575545, 14, 680521, 25, 377257, -27,
    493897, -29, 610537, -11, 693481, -6, 339025, 9, 444001, 27, 245713, -9, 560641, 41, 257377, -27, 572305, 9, 677281, 25, 374017, -41, 478993, -9,
    688945, 16, 490657, -25, 595633, -16, 482881, 20, 573601, -20, 565825, 20, 682465, 37, 379201, -20, 694129, 17, 495841, -37, 600817, -17, 366565, -14,
    483205, -17, 494869, -11, 599845, -15, 488389, -15, 443515, 24, 560155, 21, 256891, -24, 676795, 27, 373531, -21, 490171, -27, 470731, 62, 482395, 35,
    587371, 57, 389083, -7, 599035, 13, 666427, 7, 468139, -62, 573115, -35, 584779, -57, 689755, -13, 565339, 9, 577003, 7, 681979, 14, 378715, -9,
    483691, -7, 495355, -14, 457123, 14, 573763, 17, 678739, 11, 690403, 15, 578947, 15, 366079, -14, 482719, -17, 494383, -11, 599359, -15, 487903, -15,
    677767, 27, 491143, -27, 351283, 6, 467923, 11, 584563, 29, 689539, 17, 701203, 7, 350311, 20, 466951, 14, 571927, 17, 688567, 13, 700231, 7,
    678199, 6, 588775, 12, 705415, 28, 573871, 9, 690511, 59, 585049, 10, 701689, 27, 350068, 20, 466708, 14, 571684, 17, 688324, 13, 699988, 7,
    677956, 6, 588532, 12, 705172, 28, 585292, 10, 701932, 27, 676984, 15, 793624, 9, 682168, 8, 572656, 34, 678928, 9, 577840, 26, 589504, 9,
    694480, 41, 706144, 6, 811120, 33, 822784, 11, 800752, 9, 573142, 9, 689782, 59, 572170, 34, 678442, 9, 577354, 26, 589018, 9, 693994, 41,
    705658, 6, 810634, 33, 822298, 11, 800266, 9, 707602, 21, 824242, 7, 353857, -6, 470497, -11, 587137, -29, 598801, -17, 703777, -7, 350617, -20,
    362281, -29, 467257, -14, 478921, -17, 595561, -13, 700537, -7, 494473, -6, 589081, -12, 705721, -28, 483133, -9, 599773, -59, 350131, -20, 361795, -29,
    466771, -14, 478435, -17, 595075, -13, 700051, -7, 493987, -6, 588595, -12, 705235, -28, 490747, -15, 607387, -9, 495931, -8, 587623, -10, 704263, -27,
    479407, -34, 494959, -9, 484591, -26, 589567, -9, 601231, -41, 706207, -6, 717871, -33, 822847, -11, 616783, -9, 587866, -10, 704506, -27, 482404, -9,
    599044, -59, 479164, -34, 494716, -9, 484348, -26, 589324, -9, 600988, -41, 705964, -6, 717628, -33, 822604, -11, 616540, -9, 710176, -21, 826816, -7,
    676588, 17, 793228, 10, 489964, -17, 606604, -10, 482188, 29, 572908, -29, 565132, 23, 681772, 8, 378508, -23, 495148, -8, 362308, 16, 467284, 53,
    478948, 14, 561892, 15, 375268, -20, 491908, -19, 806836, 6, 608548, -12, 484132, 18, 589108, 86, 600772, 17, 507460, -11, 455296, -16, 466960, -53,
    571936, -14, 564160, 20, 680800, 19, 377536, -15, 797440, 12, 715792, -6, 577120, -18, 787072, 11, 588784, -86, 693760, -17, 560920, 17, 677560, 18,
    374296, -17, 794200, 11, 490936, -18, 607576, -11, 483160, 28, 588136, 77, 389848, -8, 599800, 15, 667192, 8, 573880, -28, 585544, -77, 690520, -15,
    682744, 24, 799384, 21, 496120, -24, 612760, -21, 604984, 22, 721624, 5, 695704, -22, 812344, -5, 361822, 16, 466798, 53, 478462, 14, 561406, 15,
    374782, -20, 491422, -19, 806350, 6, 608062, -12, 483646, 18, 588622, 86, 600286, 17, 506974, -11, 560434, 17, 677074, 25, 373810, -17, 688738, 5,
    793714, 7, 490450, -25, 595426, -5, 607090, -7, 482674, 32, 573394, -32, 682258, 25, 495634, -25, 596074, 39, 679018, 28, 690682, 14, 795658, 34,
    492394, -18, 807322, 12, 484618, 55, 589594, 120, 391306, 6, 496282, 25, 601258, 64, 717898, 65, 684202, 30, 695866, 10, 800842, 22, 812506, 9,
    614218, -10, 929146, 28, 455053, -16, 466717, -53, 571693, -14, 563917, 20, 680557, 19, 377293, -15, 797197, 12, 715549, -6, 576877, -18, 786829, 11,
    588541, -86, 693517, -17, 560677, 17, 677317, 25, 374053, -17, 688981, 5, 793957, 7, 490693, -25, 595669, -5, 607333, -7, 482917, 32, 573637, -32,
    682501, 25, 495877, -25, 689305, -39, 681529, 18, 494905, -28, 599881, -14, 611545, -34, 716521, -12, 671161, -6, 577849, -55, 682825, -25, 589513, -120,
    694489, -64, 811129, -65, 803353, 10, 500089, -30, 605065, -10, 616729, -22, 721705, -9, 838345, -28, 560191, 17, 676831, 18, 373567, -17, 793471, 11,
    490207, -18, 606847, -11, 482431, 28, 587407, 77, 389119, -8, 599071, 15, 666463, 8, 573151, -28, 584815, -77, 689791, -15, 682015, 24, 798655, 21,
    495391, -24, 612031, -21, 604255, 22, 720895, 5, 694975, -22, 811615, -5, 595831, 39, 678775, 28, 690439, 14, 795415, 34, 492151, -18, 807079, 12,
    484375, 55, 589351, 120, 391063, 6, 496039, 25, 601015, 64, 717655, 65, 683959, 30, 695623, 10, 800599, 22, 812263, 9, 613975, -10, 928903, 28,
    688819, -39, 681043, 18, 494419, -28, 599395, -14, 611059, -34, 716035, -12, 670675, -6, 577363, -55, 682339, -25, 589027, -120, 694003, -64, 810643, -65,
    802867, 10, 499603, -30, 604579, -10, 616243, -22, 721219, -9, 837859, -28, 677803, 8, 491179, -8, 600043, 32, 506731, -8, 716683, 51, 784075, 8,
    690763, -32, 807403, -51, 682987, 20, 694651, 5, 799627, 24, 496363, -20, 601339, -5, 613003, -24, 605227, 21, 710203, 108, 616891, 9, 721867, 65,
    695947, -21, 800923, -9, 707611, -108, 812587, -65, 804811, 16, 618187, -16
};

// SMP section

#ifdef DEBUG
#define MaxPrN 1
#else 
#ifndef TUNER
#define MaxPrN 16
#else
#ifdef LOCAL_TUNER
#define MaxPrN 16
#else
#define MaxPrN 1
#endif
#endif
#endif

int PrN = 1, NewPrN = 0;
int CPUs = 1;
#define SplitDepth 10

HANDLE ChildPr[MaxPrN];

int WinProcId, WinParId, Id, parent, child;
#define NAME_HASH "GULL_HASH"
#define NAME_PV_HASH "GULL_PV_HASH"
#define NAME_STORE_HASH "GULL_STORE_HASH"
#define NAME_SHARED "GULL_SHARED"
#define NAME_EVENT "GULL_EVENT"
#define NAME_MAGIC "GULL_MAGIC"
#define NAME_MATERIAL "GULL_MATERIAL"
HANDLE HASH, PV_HASH, STORE_HASH, MAGIC, MATERIAL;
#ifdef LOCAL_TUNER
#define NAME_MATERIAL_STAT "GULL_MATERIAL_STAT"
#define NAME_EVAL_STAT "GULL_EVAL_STAT"
HANDLE MATERIAL_STAT, EVAL_STAT;
#endif
int hash_initialized = 0, reset_hash = 1, init_cnt = 0; 

#ifndef W32_BUILD
#define TEST_RESET_BIT(var,bit) (InterlockedBitTestAndReset(&(var),bit))
#define SET_BIT(var,bit) (InterlockedOr(&(var),1 << (bit)))
#define SET_BIT_64(var,bit) (InterlockedOr64(&(var),Bit(bit)));
#define ZERO_BIT_64(var,bit) (InterlockedAnd64(&(var),~Bit(bit)));
#else
#define TEST_RESET_BIT(var,bit) (InterlockedBitTestAndReset(&(var),bit))
#define SET_BIT(var,bit) (_InterlockedOr(&(var),1 << (bit)))
#define SET_BIT_64(var,bit) {if ((bit) < 32) _InterlockedOr((LONG*)&(var),1 << (bit)); else _InterlockedOr(((LONG*)(&(var))) + 1,1 << ((bit) - 32));}
#define ZERO_BIT_64(var,bit) {if ((bit) < 32) _InterlockedAnd((LONG*)&(var),~(1 << (bit))); else _InterlockedAnd(((LONG*)(&(var))) + 1,~(1 << ((bit) - 32)));}
#endif
#define SET(var,value) (InterlockedExchange(&(var),value))
#define TEST(var) (InterlockedCompareExchange(&(var),12345,12345))

#define LOCK(lock) {while (InterlockedCompareExchange(&(lock),1,0)) _mm_pause();}
#define UNLOCK(lock) {SET(lock,0);}

typedef struct {
	GData Current[1];
	GBoard Board[1];
	uint64 stack[128];
	uint16 killer[16][2];
	int sp;
	int date;
} GPosition;

#define FlagClaimed (1 << 1)
#define FlagFinished (1 << 2)

typedef struct {
	volatile int value;
	volatile uint16 move;
	volatile uint8 reduced_depth;
	volatile uint8 research_depth;
	volatile uint8 stage;
	volatile uint8 ext;
	volatile uint8 id;
	volatile uint8 flags;
} GMove;

typedef struct {
	volatile LONG lock;
	volatile int active; // split point is active
	volatile int pv; // pv node?
#ifdef CUT_ALL
	volatile int cut; // cut node?
#endif
	volatile int move_number; // number of legal moves
	volatile int current_master_position; // the master process is currently searching the move with this number
	GMove move[256]; // list of legal moves
	volatile int depth; // depth to search
	volatile int alpha; // used in pv nodes only
	volatile int beta; // beta
	volatile int singular; // whether hash killer is muche better than other moves
	volatile int split; // split occured?
	volatile int value; // result
	volatile int best_move; // move which caused the cutoff
	jmp_buf jump; // jump to be used by the master process
	GPosition position[1]; // game state copy
} GMoveList;
#define STOP_ORDER 1
#define FH_SIGNAL 2
#define QUIT_ORDER 3
#define SPLIT_SIGNAL 4
typedef struct {
	volatile LONG searching;
	volatile LONG flags; // for stop order & fail high signal
	volatile long long active_sp[2]; 
	GMoveList MoveList[128];
} GProcessInfo;
#define ActivateSP(id,height) {if ((height) < 64) SET_BIT_64(SMPI->Info[id].active_sp[0],height) else SET_BIT_64(SMPI->Info[id].active_sp[1],height - 64)}
#define CancelSP(id,height) {if ((height) < 64) ZERO_BIT_64(SMPI->Info[id].active_sp[0],height) else ZERO_BIT_64(SMPI->Info[id].active_sp[1],height - 64)}

typedef struct {
	volatile long long total_nodes;
	volatile int hash_size;
	volatile int PrN;
	GProcessInfo Info[MaxPrN];
} GSMPInfo;

GSMPInfo * SMPI;
GProcessInfo * GPI;
GMoveList * ML;

#ifdef LOCAL_TUNER
typedef struct {
	volatile int updated;
	int data_i[256];
	double data_d[256];
	double List[256];
} GTunerFeedback;

typedef struct {
	volatile LONG lock;
	volatile int type;
	volatile int command;
	int data_i[256];
	double data_d[256];
	double Var[256];
	double Base[256];
	double First[256];
	double Second[256];
	GTunerFeedback feedback[MaxPrN];
} GTunerBuffer;
#define GRADIENT_COMMAND 1
#define MATCH_COMMAND 2

GTunerBuffer * TB;
#endif

// end SMP section

__forceinline int lsb(uint64 x);
__forceinline int msb(uint64 x);
__forceinline int popcnt(uint64 x);
template <bool HPopCnt> __forceinline int popcount(uint64 x);
uint64 BMagicHash(int i, uint64 occ);
uint64 RMagicHash(int i, uint64 occ);
uint16 rand16();
uint64 random();
void gen_kpk();
void init();
void init_search(int clear_hash);
void setup_board();
void get_board(const char fen[]);
void init_hash();
void move_to_string(int move, char string[]);
int move_from_string(char string[]);
void pick_pv();
void send_pv(int depth, int alpha, int beta, int score);
template <bool me> void do_move(int move);
template <bool me> void undo_move(int move);
void do_null();
void undo_null();
template <bool me> int kpkx();
template <bool me> int krpkrx();
template <bool me> int kqkp();
template <bool me> int krkpx();
template <bool me> int krppkrpx();
template <bool me> int krpppkrppx();
template <bool me> int kbpkbx();
template <bool me> int kbpknx();
template <bool me> int kbppkbx();
template <bool me> int krppkrx();
__forceinline void evaluate();
template <bool me> int is_legal(int move);
template <bool me> int is_check(int move);
template <bool me> int is_tactical(int move);
template <bool me> int is_fork(int move);
template <bool me> int is_defence(int move, int threat_move);
void hash_high(int value, int depth);
void hash_low(int move, int value, int depth);
#ifdef CUT_ALL
void hash_high_weak(int value, int depth);
void hash_low_weak(int move, int value, int depth);
#endif
void hash_exact(int move, int value, int depth, int exclusion, int ex_depth, int knodes);
#ifdef HASH_STORE
void hash_store(int move, int value, int depth, int exclusion, int ex_depth, int time);
#endif
int check_hash(int beta, int depth, int * move, int * value);
int extension(int move, int depth, int pv);
__forceinline int pick_move();
template <bool me> int get_move();
template <bool me> int see(int move, int margin);
template <bool me> void gen_legal_moves();
template <bool me> int * gen_captures(int * list);
template <bool me> int * gen_evasions(int * list);
void mark_evasions(int * list);
template <bool me> int * gen_quiet_moves(int * list);
template <bool me> int * gen_checks(int * list);
template <bool me> int * gen_delta_moves(int * list);
template <bool me> int q_search(int alpha, int beta, int depth, int flags);
template <bool me> int q_evasion(int alpha, int beta, int depth, int flags);
template <bool me> int qpv_search(int alpha, int beta, int depth);
template <bool me, bool exclusion> int search(int beta, int depth, int flags);
template <bool me, bool exclusion> int search_evasion(int beta, int depth, int flags);
template <bool me, bool root> int pv_search(int alpha, int beta, int depth, int flags);
template <bool me> void root();
template <bool me> int multipv(int depth);
void send_pv(int depth, int alpha, int beta, int score);
void send_multipv(int depth, int curr_number);
void send_best_move();
void get_position(char string[]);
void get_time_limit(char string[]);
sint64 get_time();
int time_to_stop(GSearchInfo * SI, int time, int searching);
void check_time(int searching);
void check_time(int time, int searching);
void check_state(int searching);
void init_move_list(GMoveList * ML);
void send_position(GPosition * gp);
void retrieve_position(GPosition * gp, int height);
void halt_all(GMoveList * ML, int locked);
void halt_all(int from, int to);
int input();
void uci(int searching);
#ifdef HASH_READER
template <bool me> void print_pos_info();
void print_curr_line();
#endif

#ifdef DEBUG
int check_board() {
	int sq;
	for (sq = 0; sq < 64; sq++) {
		if (Square(sq)) {
			if (F(BB(Square(sq)) & Bit(sq))) return 0;
			if (F(Piece(Square(sq) & 1) & Bit(sq))) return 0;
		} else if (PieceAll & Bit(sq)) return 0;
	}
	if (F(King(White)) || F(King(Black))) return 0;
	if ((Pawn(White) | Pawn(Black)) & (Line[0] | Line[7])) return 0;
	if ((Light(White) | Heavy(White) | Pawn(White) | King(White)) != Piece(White)) return 0;
	if ((Light(Black) | Heavy(Black) | Pawn(Black) | King(Black)) != Piece(Black)) return 0;
	return 1;
}
void flip_board() {
	GBoard NewBoard[1];
	int sq, new_sq;

	memset(NewBoard,0,sizeof(GBoard));
	for (sq = 0; sq < 64; sq++) {
		new_sq = File(sq) + ((7 - Rank(sq)) << 3);
		if (Square(sq)) NewBoard->square[new_sq] = Square(sq) ^ 1;
        else NewBoard->square[new_sq] = 0;
	}
	uint8 flags = Current->castle_flags;
	Current->castle_flags = 0;
	if (flags & CanCastle_OO) Current->castle_flags |= CanCastle_oo;
	if (flags & CanCastle_oo) Current->castle_flags |= CanCastle_OO;
	if (flags & CanCastle_OOO) Current->castle_flags |= CanCastle_ooo;
	if (flags & CanCastle_ooo) Current->castle_flags |= CanCastle_OOO;
	if (Current->ep_square) Current->ep_square = File(Current->ep_square) + ((7 - Rank(Current->ep_square)) << 3);
	Current->turn ^= 1;
	memcpy(Board,NewBoard,sizeof(GBoard));
	setup_board();
}
int test_eval() {
	int value, flag = 0;
	evaluate();
	value = Current->score;
	flip_board();
	evaluate();
	if (Current->score != value) flag = 1;
	flip_board();
	if (flag) return 0;
	else return 1;
}
void epd(char string[]) {
	int i, sq, n = 0, positions = 4000, AD = 0, old_value, value, piece, write_piece, pair[2];
	sint64 SetMaxNodes = 1024 * 1024;
	uint64 u, Time, delta, all_nodes = 0;
    sint64 piece_delta[16];
	sint64 piece_count[16];
	double time, av_depth;
	char * ptr; 
	FILE * f = fopen(string, "r");
	if (f == NULL) {
		fprintf(stdout,"File not found\n");
		return;
	}
	Infinite = 1;
	Time = get_time();
	for (i = 0; i < 16; i++) {
		piece_delta[i] = 0;
		piece_count[i] = 0;
	}
	while (!feof(f) && n < positions) {
		(void)fgets(input_string, 65536, f);
		ptr = strchr(input_string, '\n');
        if (ptr != NULL) *ptr = 0;
		get_board(input_string);
		if (n == 36)
			nodes += 0;
		if (!test_eval()) {
			fprintf(stdout,"Eval assymetry detected: < %d >!\n",n);
			getchar();
		} else fprintf(stdout,"#%d checked\n",n);
		pair[0] = pair[1] = 0;
		evaluate();
		old_value = Current->score;
		if (T(Bishop(White)) && Multiple(Bishop(White))) pair[0] = 1;
		if (T(Bishop(Black)) && Multiple(Bishop(Black))) pair[1] = 1;
		for (u = NonPawnKing(White) | NonPawnKing(Black); T(u); Cut(u)) {
			sq = lsb(u);
			piece = Square(sq);
			Piece(piece & 1) ^= Bit(sq);
			Piece(piece) ^= Bit(sq);
			Square(sq) = 0;
			Current->material -= MatCode[piece];
			write_piece = piece;
			if (piece >= WhiteLight && piece < WhiteRook) {
				write_piece = WhiteLight | (piece & 1);
				if (pair[piece & 1]) write_piece += 2;
			}
			evaluate();
			if ((piece & 1) == Current->turn) piece_delta[write_piece] += old_value - Current->score;
			else piece_delta[write_piece] += Current->score - old_value;
			piece_count[write_piece]++;
			Piece(piece & 1) |= Bit(sq);
			Piece(piece) |= Bit(sq);
			Square(sq) = piece;
			Current->material += MatCode[piece];
		}
		n++;
	}
	if (n == 0) {
		fprintf(stdout,"Empty file\n");
		return;
	}
	fclose(f);
	for (i = 0; i < 16; i++) if (piece_count[i]) fprintf(stdout,"%d: %d\n",i,piece_delta[i]/piece_count[i]);
}
#endif

#ifndef W32_BUILD
__forceinline int lsb(uint64 x) {
	register unsigned long y;
#ifdef DEBUG
	if (F(x))
	    nodes /= 0;
#endif
	_BitScanForward64(&y,x);
	return y;
}

__forceinline int msb(uint64 x) {
	register unsigned long y;
#ifdef DEBUG
	if (F(x))
	    nodes /= 0;
#endif
	_BitScanReverse64(&y,x);
	return y;
}

__forceinline int popcnt(uint64 x) { 
    x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    return (x * 0x0101010101010101) >> 56;
}

template <bool HPopCnt> __forceinline int popcount(uint64 x) {
	return HPopCnt ? _mm_popcnt_u64(x) : popcnt(x);
}
#else
__forceinline int lsb(uint64 x) {
    _asm {
         mov eax, dword ptr x[0]
        test eax, eax
        jz l_high
        bsf eax, eax
        jmp l_ret
        l_high: bsf eax, dword ptr x[4]
        add eax, 20h
        l_ret:
    }
}

__forceinline int msb(uint64 x) {
	_asm {
        mov eax, dword ptr x[4]
        test eax, eax
        jz l_low
        bsr eax, eax
        add eax, 20h
        jmp l_ret
        l_low: bsr eax, dword ptr x[0]
        l_ret:
    }
}

__forceinline int popcnt(uint64 x) { 
    unsigned int x1, x2;
    x1 = (unsigned int) (x & 0xFFFFFFFF);
    x1 -= (x1 >> 1) & 0x55555555;
    x1 = (x1 & 0x33333333) + ((x1 >> 2) & 0x33333333);
    x1 = (x1 + (x1 >> 4)) & 0x0F0F0F0F;
    x2 = (unsigned int) (x >> 32);
    x2 -= (x2 >> 1) & 0x55555555;
    x2 = (x2 & 0x33333333) + ((x2 >> 2) & 0x33333333);
    x2 = (x2 + (x2 >> 4)) & 0x0F0F0F0F;
    return ((x1 * 0x01010101) >> 24) + ((x2 * 0x01010101) >> 24);
}

template <bool HPopCnt> __forceinline int popcount(uint64 x) {
	return HPopCnt ? (__popcnt((int)x) + __popcnt(x >> 32)) : popcnt(x);
}
#endif

uint64 BMagicHash(int i, uint64 occ) {
    uint64 free = 0;
    int j;
	if (File(i) < 7 && Rank(i) < 7) {
		occ |= File[7] | Line[7];
        for (j = i + 9; ((j & 7) < 7) && ((occ & ((uint64)1 << j)) == 0); j += 9) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (File(i) > 0 && Rank(i) < 7) {
		occ |= File[0] | Line[7];
	    for (j = i + 7; ((j & 7) > 0) && ((occ & ((uint64)1 << j)) == 0); j += 7) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (File(i) > 0 && Rank(i) > 0) {
		occ |= File[0] | Line[0];
	    for (j = i - 9; ((j & 7) > 0) && ((occ & ((uint64)1 << j)) == 0); j -= 9) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (File(i) < 7 && Rank(i) > 0) {
		occ |= File[7] | Line[0];
	    for (j = i - 7; ((j & 7) < 7) && ((occ & ((uint64)1 << j)) == 0); j -= 7) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	return free;
}

uint64 RMagicHash(int i, uint64 occ) {
    uint64 free = 0;
    int j;
	if (File(i) < 7) {
		occ |= File[7];
        for (j = i + 1; ((j & 7) < 7) && ((occ & ((uint64)1 << j)) == 0); j++) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (File(i) > 0) {
		occ |= File[0];
        for (j = i - 1; ((j & 7) > 0) && ((occ & ((uint64)1 << j)) == 0); j--) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (Rank(i) < 7) {
		occ |= Line[7];
	    for (j = i + 8; (j < 56) && ((occ & ((uint64)1 << j)) == 0); j += 8) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	if (Rank(i) > 0) {
		occ |= Line[0];
        for (j = i - 8; (j > 7) && ((occ & ((uint64)1 << j)) == 0); j -= 8) free |= (uint64)1 << j;
	    free |= (uint64)1 << j;
	}
	return free;
}

uint16 rand16() {
	seed = (seed * Convert(6364136223846793005,uint64)) + Convert(1442695040888963407,uint64);
	return Convert((seed >> 32) & 0xFFFF,uint16);
}

uint64 random() {
	uint64 key = Convert(rand16(),uint64); key <<= 16;
	key |= Convert(rand16(),uint64); key <<= 16;
	key |= Convert(rand16(),uint64); key <<= 16;
	return key | Convert(rand16(),uint64);
}

void gen_kpk() {
	int turn, wp, wk, bk, to, cnt, old_cnt, un;
	uint64 bwp, bwk, bbk, u;
	uint8 KPK_gen[2][64][64][64];

	memset(KPK_gen, 0, 2 * 64 * 64 * 64);
	
	cnt = 0;
	old_cnt = 1;
start:
	if (cnt == old_cnt) goto end;
	old_cnt = cnt;
	cnt = 0;
	for (turn = 0; turn < 2; turn++) {
		for (wp = 0; wp < 64; wp++) {
			for (wk = 0; wk < 64; wk++) {
				for (bk = 0; bk < 64; bk++) {
					if (KPK_gen[turn][wp][wk][bk]) continue;
					cnt++;
					if (wp < 8 || wp >= 56) goto set_draw;
					if (wp == wk || wk == bk || bk == wp) goto set_draw;
					bwp = Bit(wp);
					bwk = Bit(wk);
					bbk = Bit(bk);
					if (PAtt[White][wp] & bbk) {
						if (turn == White) goto set_draw;
						else if (F(SArea[wk] & bwp)) goto set_draw; 
					}
					un = 0;
					if (turn == Black) {
						u = SArea[bk] & (~(SArea[wk] | PAtt[White][wp]));
						if (F(u)) goto set_draw;
						for (; T(u); Cut(u)) {
						    to = lsb(u);
							if (KPK_gen[turn ^ 1][wp][wk][to] == 1) goto set_draw;
							else if (KPK_gen[turn ^ 1][wp][wk][to] == 0) un++;
						}
						if (F(un)) goto set_win;
					} else {
						for (u = SArea[wk] & (~(SArea[bk] | bwp)); T(u); Cut(u)) {
						    to = lsb(u);
							if (KPK_gen[turn ^ 1][wp][to][bk] == 2) goto set_win;
							else if (KPK_gen[turn ^ 1][wp][to][bk] == 0) un++;
						}
						to = wp + 8;
						if (to != wk && to != bk) {
							if (to >= 56) {
								if (F(SArea[to] & bbk)) goto set_win;
								if (SArea[to] & bwk) goto set_win;
							} else {
								if (KPK_gen[turn ^ 1][to][wk][bk] == 2) goto set_win;
								else if (KPK_gen[turn ^ 1][to][wk][bk] == 0) un++;
								if (to < 24) {
								    to += 8;
							        if (to != wk && to != bk) {
										if (KPK_gen[turn ^ 1][to][wk][bk] == 2) goto set_win;
										else if (KPK_gen[turn ^ 1][to][wk][bk] == 0) un++;
									}
							    }
							}
						}
						if (F(un)) goto set_draw;
					}
                	continue;
set_draw:
					KPK_gen[turn][wp][wk][bk] = 1;
					continue;
set_win:
					KPK_gen[turn][wp][wk][bk] = 2;
					continue;
				}
			}
		}
	}
	if (cnt) goto start;
end:
	for (turn = 0; turn < 2; turn++) {
		for (wp = 0; wp < 64; wp++) {
			for (wk = 0; wk < 64; wk++) {
				KPK[turn][wp][wk] = 0;
				for (bk = 0; bk < 64; bk++) {
					if (KPK_gen[turn][wp][wk][bk] == 2) KPK[turn][wp][wk] |= Bit(bk);
				}
			}
		}
	}
}

void init_pst() {
	int i, j, k, op, eg, r, f, d, e;
	memset(PST,0,16 * 64 * sizeof(int));
	for (i = 0; i < 64; i++) {
		r = Rank(i);
		f = File(i);
		d = Abs(f - r);
		e = Abs(f + r - 7);
		for (j = WhitePawn; j < WhiteKing; j += 2) {
			int index;
			if (j < WhiteKnight) index = 0;
			else if (j < WhiteLight) index = 1;
			else if (j < WhiteRook) index = 2;
			else if (j < WhiteQueen) index = 3;
			else index = 4;
			op = StA(PstPawnToQueen,18,index,16);
			eg = StA(PstPawnToQueen,18,index,17);
			int distq[4], distl[4];
			distq[0] = DistC[f] * DistC[f]; distl[0] = DistC[f];
			distq[1] = DistC[r] * DistC[r]; distl[1] = DistC[r];
			distq[2] = DistC[d] * DistC[d] + DistC[e] * DistC[e]; distl[2] = DistC[d] + DistC[e];
			distq[3] = RankR[r] * RankR[r]; distl[3] = RankR[r];
			for (k = 0; k < 4; k++) {
				op += StA(PstPawnToQueen,18,index,(k * 4)) * distq[k];
				op += StA(PstPawnToQueen,18,index,(k * 4) + 2) * distl[k];
				eg += StA(PstPawnToQueen,18,index,(k * 4) + 1) * distq[k];
				eg += StA(PstPawnToQueen,18,index,(k * 4) + 3) * distl[k];
			}
			PST[j][i] = Compose(op/100, eg/100);
		}
#ifdef TUNER
		PST[WhiteKing][i] = Compose(((KingROp[r] + KingFOp[f]) * V(IPstKingOp))/100, ((KingVEg[d] + KingVEg[e] + KingREg[r] + KingFEg[f]) * V(IPstKingEg))/100);
#else
		PST[WhiteKing][i] = Compose(((KingROp[r] + KingFOp[f]) * Opening(PstKing))/100, ((KingVEg[d] + KingVEg[e] + KingREg[r] + KingFEg[f]) * Endgame(PstKing))/100);
#endif
	}
	PST[WhiteKnight][56] -= Compose(KnightTrapped, 0);
	PST[WhiteKnight][63] -= Compose(KnightTrapped, 0);
	for (i = 0; i < 64; i++) {
		for (j = 3; j < 16; j+=2) {
			op = Opening(PST[j-1][63-i]);
			eg = Endgame(PST[j-1][63-i]);
			PST[j][i] = Compose(-op,-eg);
		}
	}
#ifdef TUNER
	Current->pst = 0;
	for (i = 0; i < 64; i++)
		if (Square(i)) Current->pst += PST[Square(i)][i];
#endif
}

#ifdef TUNER
double rand_u() {
	return Min(1.0, Max(0.0, ((double)((rand() << 15) | rand()))/(32768.0 * 32768.0)));
}
void set(int index, int value, double var, int active) {
	Variables[index].value = value; 
	Variables[index].var = var;
	Variables[index].active = active;
	if (active) {
		VarIndex[index] = var_number;
		IndexVar[var_number] = index;
		var_number++;
	}
}
void set(int index, int value, int var, int active) {
	Variables[index].value = value; 
	Variables[index].var = (double)var;
	Variables[index].active = active;
	if (active) {
		VarIndex[index] = var_number;
		IndexVar[var_number] = index;
		var_number++;
	}
}
void set_zero_tr_array(int index, int width, int height, int var, int active) {
	for (int i = 0; i < height; i++) 
		for (int j = 0; j < width - i; j++) set(index + TrIndex(width,i,j),0,var,active);
}
void set_zero_array(int index, int width, int height, int var, int active) {
	for (int i = 0; i < height; i++) 
		for (int j = 0; j < width; j++) set(index + StAIndex(width,i,j),0,var,active);
}
void load_list(double * List) {
	for (int i = 0; i < var_number; i++) Variables[IndexVar[i]].value = (int)List[i];
}
void save_list(double * List) {
	for (int i = 0; i < var_number; i++) List[i] = (double)Variables[IndexVar[i]].value;
}
void copy_list(double * Dst, double * Src) {
	for (int i = 0; i < var_number; i++) Dst[i] = Src[i];
}
void load_first_eval() {
	load_list(FirstEval);
	Hash = HashBase1;
	PawnHash = PawnHashBase1;
	PVHash = PVHashBase1;
	History = History1;
	Delta = Delta1;
	Ref = Ref1;
	init_pst();
}
void load_second_eval() {
	load_list(SecondEval);
	Hash = HashBase2;
	PawnHash = PawnHashBase2;
	PVHash = PVHashBase2;
	History = History2;
	Delta = Delta2;
	Ref = Ref2;
	init_pst();
}
void clear_data() {
	date = 0;
	memset(History1,1,16 * 64 * sizeof(sint16));
	memset(History2,1,16 * 64 * sizeof(sint16));
	memset(Delta1,0,16 * 4096 * sizeof(sint16));
	memset(Delta2,0,16 * 4096 * sizeof(sint16));
	memset(Ref1,0,16 * 64 * sizeof(GRef));
	memset(Ref2,0,16 * 64 * sizeof(GRef));
	memset(HashBase1,0,hash_size * sizeof(GEntry));
	memset(HashBase2,0,hash_size * sizeof(GEntry));
	memset(PawnHashBase1,0,pawn_hash_size * sizeof(GPawnEntry));
	memset(PawnHashBase2,0,pawn_hash_size * sizeof(GPawnEntry));
	memset(PVHashBase1,0,pv_hash_size * sizeof(GPVEntry));
	memset(PVHashBase2,0,pv_hash_size * sizeof(GPVEntry));
}
double ratio_from_elo(double elo) {
	return 1.0/(1.0 + exp(((-elo)/400.0)*log(10.0)));
}
double elo_from_ratio(double ratio) {
	return -(log((1.0/Min(0.99999,Max(ratio,0.00001))) - 1.0)/log(10.0)) * 400.0;
}
double ratio_from_eval(int eval) {
	double result, de = (double)eval;
	result = ratio_from_elo(1.6 * de);
	return result;
}
int play(int depth) {
	int d, value = 0;

	date++;
	nodes = check_node = 0;
	LastDepth = TimeLimit1 = TimeLimit2 = 0;
#ifndef NODES
	if (depth) DepthLimit = 2 * depth + 2;
	else DepthLimit = 128;
#else 
	DepthLimit = 128;
	MaxNodes = 32 << depth;
#endif
	Infinite = 1;
	best_score = best_move = 0;
	Print = 0;

	if (Current->turn == White) root<0>();
	else root<1>();
	return best_score;
}
template <bool me> int halt_game() {
	int i;
	int moves[256];
	int *list;
	if (Current->att[opp] & King(me)) {
		Current->mask = Filled;
		gen_evasions<me>(moves);
		for (i = 0; i < 256; i++) {
			if (F(moves[i])) return 2;
			if (IsIllegal(me,moves[i])) continue;
			goto check_draw;
		}
		return 2;
	} else {
		Current->mask = Piece(opp);
		list = gen_captures<me>(moves);
	    gen_quiet_moves<me>(list);
		for (i = 0; i < 256; i++) {
			if (F(moves[i])) return 1;
			if (IsIllegal(me,moves[i])) continue;
			goto check_draw;
		}
	}
check_draw:
	if (Current->ply >= 100) return 1;
	for (i = 4; i <= Current->ply; i+= 2) if (Stack[sp-i] == Current->key) return 1;

	return 0;
}
int insufficient_material() {
	int me = 0;
	if (F(Pawn(me) | Pawn(opp))) {
	    int my_score = 3 * popcnt(Light(me)) + 5 * popcnt(Rook(me)) + 10 * popcnt(Queen(me));
		int opp_score = 3 * popcnt(Light(opp)) + 5 * popcnt(Rook(opp)) + 10 * popcnt(Queen(opp));
		if (Abs(my_score - opp_score) <= 3) return 1; // hack
	}
	return 0;
}
int end_game() {
	if (Current->turn == White) return halt_game<0>();
	else return halt_game<1>();
}
int get_mat_index(int wq, int bq, int wr, int br, int wl, int bl, int wd, int bd, int wn, int bn, int wp, int bp) {
	if (wq > 2 || bq > 2 || wr > 2 || br > 2 || wl > 1 || bl > 1 || wd > 1 || bd > 1 || wn > 2 || bn > 2 || wp > 8 || bp > 8) return -1;
	return wp*MatWP+bp*MatBP+wn*MatWN+bn*MatBN+wl*MatWL+bl*MatBL+wd*MatWD+bd*MatBD+wr*MatWR+br*MatBR+wq*MatWQ+bq*MatBQ;
}
int conj_mat_index(int index, int * conj_symm, int * conj_ld, int * conj_ld_symm) {
	int wq = index % 3; index /= 3;
	int bq = index % 3; index /= 3;
	int wr = index % 3; index /= 3;
	int br = index % 3; index /= 3;
	int wl = index % 2; index /= 2;
	int bl = index % 2; index /= 2;
	int wd = index % 2; index /= 2;
	int bd = index % 2; index /= 2;
	int wn = index % 3; index /= 3;
	int bn = index % 3; index /= 3;
	int wp = index % 9; index /= 9;
	int bp = index;
	*conj_symm = -1;
	*conj_ld = -1;
	*conj_ld_symm = -1;
	if (wq != bq || wr != br || wl != bd || wd != bl || wn != bn || wp != bp) {
		*conj_symm = get_mat_index(bq,wq,br,wr,bd,wd,bl,wl,bn,wn,bp,wp);
		if (wl != wd || bl != bd) {
			*conj_ld = get_mat_index(wq,bq,wr,br,wd,bd,wl,bl,wn,bn,wp,bp);
			*conj_ld_symm = get_mat_index(bq,wq,br,wr,bl,wl,bd,wd,bn,wn,bp,wp);
		}
	}
	return *conj_symm;
}
int play_game(double * FL, double * SL, int depth, int inc_depth, char * fen) {
	int cnt, i, j, halt, value, old_value = 0, rdepth, im, ds;
	int mat_history[MatStatPosInRow];
	int eval_history[MatStatPosInRow];
	int stop_mat_history = 0;
	uint64 u, evalF = 0, evalS = 0;
	if (CollectMatStat) {
		memset(MatList,0,1024 * sizeof(int));
		memset(EvalList,0,1024 * sizeof(int));
		memset(mat_history,0,MatStatPosInRow * sizeof(int));
		memset(eval_history,0,MatStatPosInRow * sizeof(int));
	}

	get_board(fen);
#ifdef RECORD_GAMES
	char move_string[16];
	strcpy(pv_string,fen);
	*(pv_string + strlen(pv_string) - 1) = 0;
	sprintf(input_string,"[FEN \"%s\"] ",pv_string);
#endif
	copy_list(FirstEval,FL);
	copy_list(SecondEval,SL);
	clear_data();
	im = ds = 0;
	for (cnt = 0; cnt < 200; cnt++) {
		load_first_eval();
	    memcpy(Data,Current,sizeof(GData));
	    Current = Data;
		rdepth = depth;
		if (T(inc_depth) && T(depth)) if (Odd(rand16())) rdepth += inc_depth;
		value = play(rdepth);
		if (value <= -ResignThreshold && old_value >= ResignThreshold) {
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) {
					if (Current->turn) MatStat[MatList[i]].w++;
					else MatStat[MatList[i]].l++;
					MatStat[MatList[i]].cov_sum += ratio_from_eval(EvalList[i]) * (double)(Current->turn ? (1) : (-1));
				}
				UNLOCK(MatStatLock);
			}
			return 0;
		}
		if (value == 0 && old_value == 0) ds++;
		else ds = 0;
#ifndef MAT_STAT
		if (ds) {
#else
		if (ds >= 8) {
#endif
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
					EvalStat[height].score_x2 += 1;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
				UNLOCK(MatStatLock);
			}
			return 1;
		}
		old_value = value;
		if (value >= 0 && value < (64 << 3)) evalF |= Bit(value >> 3);
		if (Current->turn == White) do_move<0>(best_move);
		else do_move<1>(best_move);
#ifdef RECORD_GAMES
		move_to_string(best_move,move_string);
		if (Current->turn) sprintf(input_string+strlen(input_string),"%d. ",cnt+1);
		sprintf(input_string+strlen(input_string),"%s {%d} ",move_string,value);
#endif
		evaluate();
		if (halt = end_game()) {
		    if (halt == 1) {
				if (CollectMatStat) {
					LOCK(EvalStatLock);
					for (u = evalF; T(u); Cut(u)) {
						int height = lsb(u);
						EvalStat[height].games++;
						EvalStat[height].score_x2 += 1;
					}
					UNLOCK(EvalStatLock);
					LOCK(MatStatLock);
					for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
					UNLOCK(MatStatLock);
				}
				return 1;
			} else {
				if (CollectMatStat) {
					LOCK(EvalStatLock);
					for (u = evalF; T(u); Cut(u)) {
						int height = lsb(u);
						EvalStat[height].games++;
						EvalStat[height].score_x2 += 2;
					}
					UNLOCK(EvalStatLock);
					LOCK(MatStatLock);
					for (i = 0; T(MatList[i]); i++) {
						if (Current->turn) MatStat[MatList[i]].w++;
						else MatStat[MatList[i]].l++;
						MatStat[MatList[i]].cov_sum += ratio_from_eval(EvalList[i]) * (double)(Current->turn ? (1) : (-1));
					}
					UNLOCK(MatStatLock);
				}
				return 2;
			}
		}
		if (insufficient_material()) im++; 
		else im = 0;
		if (im >= 5) {
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
					EvalStat[height].score_x2 += 1;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
				UNLOCK(MatStatLock);
			}
			return 1;
		}

		if (F(CollectMatStat)) goto finish_mat_stat1;
		if (Current->material & FlagUnusualMaterial) stop_mat_history = 0;
		if (stop_mat_history) goto finish_mat_stat1;
		for (i = MatStatPosInRow - 1; i > 0; i--) {
			mat_history[i] = mat_history[i - 1];
			eval_history[i] = eval_history[i - 1];
		}
		mat_history[0] = Current->material;
		eval_history[0] = Current->score;
		for (i = 1; i < MatStatPosInRow; i++) if (mat_history[i] != Current->material) goto finish_mat_stat1;
		for (i = 0; T(MatList[i]); i++) if (MatList[i] == Current->material) goto finish_mat_stat1;
		MatList[i] = Current->material;
		EvalList[i] = (Current->turn ? -eval_history[MatStatPosInRow - 1] : eval_history[MatStatPosInRow - 1]);
		InterlockedAdd64(&MatStat[Current->material].eval_sum, (LONG64)EvalList[i]);
finish_mat_stat1:

		load_second_eval();
	    memcpy(Data,Current,sizeof(GData));
	    Current = Data;
		value = play(rdepth);
		if (value <= -ResignThreshold && old_value >= ResignThreshold) {
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
					EvalStat[height].score_x2 += 2;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) {
					if (Current->turn) MatStat[MatList[i]].w++;
					else MatStat[MatList[i]].l++;
					MatStat[MatList[i]].cov_sum += ratio_from_eval(EvalList[i]) * (double)(Current->turn ? (1) : (-1));
				}
				UNLOCK(MatStatLock);
			}
			return 2;
		}
		if (value == 0 && old_value == 0) ds++;
		else ds = 0;
#ifndef MAT_STAT
		if (ds) {
#else
		if (ds >= 8) {
#endif
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
					EvalStat[height].score_x2 += 1;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
				UNLOCK(MatStatLock);
			}
			return 1;
		}
		old_value = value;
		if (value >= 0 && value < (64 << 3)) evalS |= Bit(value >> 3);
		if (Current->turn == White) do_move<0>(best_move);
		else do_move<1>(best_move);
#ifdef RECORD_GAMES
		move_to_string(best_move,move_string);
		if (Current->turn) sprintf(input_string+strlen(input_string),"%d. ",cnt+1);
		sprintf(input_string+strlen(input_string),"%s {%d} ",move_string,value);
#endif
		evaluate();
		if (halt = end_game()) {
		    if (halt == 1) {
				if (CollectMatStat) {
					LOCK(EvalStatLock);
					for (u = evalF; T(u); Cut(u)) {
						int height = lsb(u);
						EvalStat[height].games++;
						EvalStat[height].score_x2 += 1;
					}
					UNLOCK(EvalStatLock);
					LOCK(MatStatLock);
					for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
					UNLOCK(MatStatLock);
				}
				return 1;
			} else {
				if (CollectMatStat) {
					LOCK(EvalStatLock);
					for (u = evalF; T(u); Cut(u)) {
						int height = lsb(u);
						EvalStat[height].games++;
					}
					UNLOCK(EvalStatLock);
					LOCK(MatStatLock);
					for (i = 0; T(MatList[i]); i++) {
						if (Current->turn) MatStat[MatList[i]].w++;
						else MatStat[MatList[i]].l++;
						MatStat[MatList[i]].cov_sum += ratio_from_eval(EvalList[i]) * (double)(Current->turn ? (1) : (-1));
					}
					UNLOCK(MatStatLock);
				}
				return 0;
			}
		}
		if (insufficient_material()) im++; 
		else im = 0;
		if (im >= 5) {
			if (CollectMatStat) {
				LOCK(EvalStatLock);
				for (u = evalF; T(u); Cut(u)) {
					int height = lsb(u);
					EvalStat[height].games++;
					EvalStat[height].score_x2 += 1;
				}
				UNLOCK(EvalStatLock);
				LOCK(MatStatLock);
				for (i = 0; T(MatList[i]); i++) MatStat[MatList[i]].d++;
				UNLOCK(MatStatLock);
			}
			return 1;
		}

		if (F(CollectMatStat)) goto finish_mat_stat2;
		if (Current->material & FlagUnusualMaterial) stop_mat_history = 0;
		if (stop_mat_history) goto finish_mat_stat2;
		for (i = MatStatPosInRow - 1; i > 0; i--) {
			mat_history[i] = mat_history[i - 1];
			eval_history[i] = eval_history[i - 1];
		}
		mat_history[0] = Current->material;
		eval_history[0] = Current->score;
		for (i = 1; i < MatStatPosInRow; i++) if (mat_history[i] != Current->material) goto finish_mat_stat2;
		for (i = 0; T(MatList[i]); i++) if (MatList[i] == Current->material) goto finish_mat_stat2;
		MatList[i] = Current->material;
		EvalList[i] = (Current->turn ? -eval_history[MatStatPosInRow - 1] : eval_history[MatStatPosInRow - 1]);
		InterlockedAdd64(&MatStat[Current->material].eval_sum, (LONG64)EvalList[i]);
finish_mat_stat2:
		nodes += 0;
	}
	return 1;
}
int play_position(double * FL, double * SL, int depth, int inc_depth, char * fen) {
	int score, result = 0;

	score = play_game(FL, SL, depth, inc_depth,fen);
	result += score;
	if (score == 2) wins++;
	else if (score == 1) draws++;
	else losses++;
#ifdef RECORD_GAMES
	if (score != 1) sprintf(input_string+strlen(input_string),"{score = %d}\n",score/2);
	FILE * fgames = fopen("games.txt","a");
	fprintf(fgames,"%s\n",input_string);
#endif
	score = play_game(SL, FL, depth, inc_depth,fen);
	result += 2 - score;
	if (score == 0) wins++;
	else if (score == 1) draws++;
	else losses++;
#ifdef RECORD_GAMES
	if (score != 1) sprintf(input_string+strlen(input_string),"{score = %d}\n",score/2);
	fprintf(fgames,"%s\n",input_string);
	fclose(fgames);
#endif
	return result;
}
double match(double * FL, double * SL, int games, int depth) {
	int score = 0, n;

	wins = draws = losses = 0;
	for (n = 0; n < games; n++) {
#ifdef LOCAL_TUNER
		if (child) {
			if (F(TB->type) || command != TB->command) {
				LOCK(TB->lock);
				if (F(TB->type) || command != TB->command) {
					UNLOCK(TB->lock);
				    return 0.0;
				}
				UNLOCK(TB->lock);
			}
		}
#endif
		score += play_position(FL,SL,depth,1,Fen[Max(0,Min(op_pos_number - 1, (int)(rand_u() * (double)op_pos_number)))]);
	}
	return ((double)score * 100.0)/((double)n * 4.0);
}
double match_smp(double * FL, double * SL, int games, int depth) {
	int i, chunks = 0, played = 0, chunk_size = 32;
	double r = 0.0;

	wins = draws = losses = 0;
	LOCK(TB->lock);
	TB->command++;
	TB->type = MATCH_COMMAND;
	TB->data_i[0] = depth;
	TB->data_i[1] = chunk_size;
	for (i = 0; i < var_number; i++) TB->Var[i] = Variables[IndexVar[i]].var;
	memcpy(TB->First,FL,var_number * sizeof(double));
	memcpy(TB->Second,SL,var_number * sizeof(double));
	UNLOCK(TB->lock);
	while (played < games) {
		for (i = 0; i < PrN; i++) if (TB->feedback[i].updated) goto set_lock; 
		Sleep(1);
set_lock:
		LOCK(TB->lock);
		for (i = 0; i < PrN; i++) {
			if (TB->feedback[i].updated) {
				TB->feedback[i].updated = 0;
				r += TB->feedback[i].data_d[0];
				wins += TB->feedback[i].data_i[0];
				draws += TB->feedback[i].data_i[1];
				losses += TB->feedback[i].data_i[2];
				UNLOCK(TB->lock);
				chunks++;
				played += chunk_size;
				continue;
			}
		}
		UNLOCK(TB->lock);
	}
	LOCK(TB->lock);
	TB->command++;
	TB->type = 0;
	UNLOCK(TB->lock);
	return r/(double)chunks;
}
double sample_var(double draw_ratio) {
	return Max(0.0, 0.25 * (1.0 - draw_ratio));
}
double SD(double draw_ratio, int games) {
	return sqrt(sample_var(draw_ratio)/(double)(games * 2)) * 100.0;
}
int match_los(double * FL, double * SL, int games, int max_games, int depth, double gain, double success, double fail, double stop, int * games_played, double * score) {
	int i, iter_played = 0, max_iter = max_games/games, w = 0, d = 0, l = 0;
	double r = 0.0, ratio, curr_score, success_target, sigma, tot_sigma, remaining_sigma;;

	*score = 0.0;
	*games_played = 0;
	tot_sigma = SD(0.35, max_iter * games);
	success_target = 50.0 + gain + success * tot_sigma;

	LOCK(TB->lock);
	TB->command++;
	TB->type = MATCH_COMMAND;
	TB->data_i[0] = depth;
	TB->data_i[1] = games;
	for (i = 0; i < var_number; i++) TB->Var[i] = Variables[IndexVar[i]].var;
	memcpy(TB->First,FL,var_number * sizeof(double));
	memcpy(TB->Second,SL,var_number * sizeof(double));
	UNLOCK(TB->lock);

	while (iter_played < max_iter) {
        for (i = 0; i < PrN; i++) if (TB->feedback[i].updated) goto set_lock; 
		Sleep(1);
set_lock:
		LOCK(TB->lock);
		for (i = 0; i < PrN; i++) {
			if (TB->feedback[i].updated) {
				TB->feedback[i].updated = 0;
				r += TB->feedback[i].data_d[0];
				w += TB->feedback[i].data_i[0];
				d += TB->feedback[i].data_i[1];
				l += TB->feedback[i].data_i[2];
				UNLOCK(TB->lock);
				iter_played++;
				*games_played = iter_played * games;
				*score = curr_score = r/(double)iter_played;
				goto check_score;
			}
		}
		UNLOCK(TB->lock);
		continue;
check_score:
		fprintf(stdout,"%.2lf ",curr_score);
		if (w + l == 0) continue;
		if (iter_played < PrN) continue;
		ratio = (((double)w) - ((double)l) - 0.02 * gain * (double)(w + l))/sqrt((double)(w + l));
		if (ratio > success) {
			fprintf(stdout,"Success (WDL: %d-%d-%d).\n",w,d,l);
			goto ret_1;
		}
		if (ratio < -fail) {
			fprintf(stdout,"Fail (WDL: %d-%d-%d).\n",w,d,l);
			goto ret_0;
		}
		remaining_sigma = SD(0.35, (max_iter - iter_played) * games);
		if (curr_score * (double)iter_played + (success_target + stop * remaining_sigma) * (double)(max_iter - iter_played) <= success_target * (double)max_iter) {
			fprintf(stdout,"Fail: improvement unlikely.\n");
			goto ret_0;
		}
	}
ret_0:
	LOCK(TB->lock);
	TB->command++;
	TB->type = 0;
	UNLOCK(TB->lock);
	return 0;
ret_1:
	LOCK(TB->lock);
	TB->command++;
	TB->type = 0;
	UNLOCK(TB->lock);
	return 1;
}
void log_list(FILE * f, double * list) {
	fprintf(f,"(");
	for (int j = 0; j < var_number; j++) {
		fprintf(f,"%.2lf",list[j]);
		if (j + 1 < var_number) fprintf(f,",");
		else fprintf(f,")\n");
	}
}
void log_list_int(FILE * f, double * list) {
	fprintf(f,"(");
	for (int j = 0; j < var_number; j++) {
		fprintf(f,"%d",(int)list[j]);
		if (j + 1 < var_number) fprintf(f,",");
		else fprintf(f,")\n");
	}
}
void get_list(double * list, char * str) {
	int i = 0;
	char * ptr;
	char * last_c;

	last_c = strrchr(str,',');
	ptr = strchr(str,'(') + 1;
	while (ptr < last_c) {
		list[i] = atof(ptr);
		i++;
		ptr = strchr(ptr,',') + 1;
	}
	list[i] = atof(ptr);
}
void get_list(double * list, FILE * f) {
	char list_str[65536];
	fgets(list_str,65536,f);
	get_list(list,list_str);
}
void load_var(double * var) {
	for (int i = 0; i < var_number; i++) Variables[IndexVar[i]].var = var[i];
}
void save_var(double * var) {
	for (int i = 0; i < var_number; i++) var[i] = Variables[IndexVar[i]].var;
}
void get_var(char * str) {
	double Var[256];
	get_list(Var,str);
	load_var(Var);
}
void calibrate(int games, double mul) {
    int i;
	double New[256];
	for (i = 0; i < var_number; i++) New[i] = DefaultEval[i] + mul * (Even(i) ? Variables[IndexVar[i]].var : (-Variables[IndexVar[i]].var))/sqrt((double)var_number);
	for (i = 2; i < 64; i++) {
		sint64 start_time = GetTickCount();
		double r = match_smp(New,DefaultEval,games,i);
		sint64 stop_time = GetTickCount();
		double draw_ratio = ((double)draws)/(double)Max(1, wins + draws + losses);
		double sigma = sqrt(sample_var(draw_ratio));
		int time = (stop_time-start_time)/(2 * games);
		fprintf(stdout,"depth %d-%d: %.2lf +- %.2lf; %d ms per game, \ndraw ratio = %.2lf, sigma = %.2lf, sigma^2 * time = %.2lf\n\n",
			i,i+1,r,(2.0 * 100.0 * sigma)/sqrt((double)(2 * games)),time,draw_ratio,sigma,sigma * sigma * (double)time);
	}
}
void compute_list(double * list, double * Base, double * Dir, double a) {
	for (int i = 0; i < var_number; i++) {
		double r = a * Dir[i];
		double range = (double)Variables[IndexVar[i]].var;
		list[i] = Base[i] + range * r;
	}
}
void grad(int depth, int iter, int games, double radius, double * Base, double * Grad) {
	double r, Dir[256], A[256], B[256];
	int i, j, active_var = 0;

	for (i = 0; i < var_number; i++) {
		Grad[i] = 0.0;
		if (Variables[IndexVar[i]].var >= VarMargin) active_var++;
	}
	if (active_var == 0) return;
	for (j = 0; j < iter; j++) {
#ifdef LOCAL_TUNER
		if (child) {
			if (F(TB->type) || command != TB->command) {
				LOCK(TB->lock);
				if (F(TB->type) || command != TB->command) {
					UNLOCK(TB->lock);
				    return;
				}
				UNLOCK(TB->lock);
			}
		}
#endif
		for (i = 0; i < var_number; i++) {
			Dir[i] = (rand_u() > 0.5 ? 1.0 : -1.0)/sqrt((double)active_var); 
			if (Variables[IndexVar[i]].var < VarMargin) Dir[i] = 0.0;
		}
		compute_list(A,Base,Dir,-radius);
		compute_list(B,Base,Dir,radius);
		r = 50.0 - match(A,B,games,depth);
		for (i = 0; i < var_number; i++) Grad[i] += r * Dir[i];
	}
	for (i = 0; i < var_number; i++) Grad[i] /= (double)iter;
}
void EstimateVar(int depth, int games, double mul, double target, double * Max, double * Base, double * Var) {
	int i, j;
	double New[256], r, value, var;

	for (i = 0; i < var_number; i++) {
		copy_list(New,DefaultEval);
		var = Base[i];
		fprintf(stdout,"Variable %d (%.2lf): ",i,var);
		for (j = 0; j < 10; j++) {
			New[i] = DefaultEval[i] + mul * var;
			r = match_smp(DefaultEval,New,games,depth);
			value = elo_from_ratio(r * 0.01);
			if (value < target) break;
			var = var * Min(sqrt(target/Max(value, 1.0)),1.5);
			fprintf(stdout,"(%.2lf,%.2lf) ",value,var);
			if (var > Max[i]) {
				var = Max[i];
				break;
			}
		}
		Var[i] = var;
		fprintf(stdout,"%.2lf\n",var);
	}
	FILE * fvar = fopen("var.txt","w");
	log_list(fvar,Var);
	fclose(fvar);
}
void normalize(int dim, double * dst, double * src, double r) {
	int i;
	double norm = 0.0;
	for (i = 0; i < dim; i++) norm += src[i] * src[i];
	norm = r/sqrt(Max(0.00000000000001,norm));
	for (i = 0; i < dim; i++) dst[i] = src[i] * norm;
}
void Gradient(int depth, int chunk_size, int max_grad_games, int angle_number, double angle_target, double radius, double * Base, double * Grad) {
	int i, j, k, chunks = 0, max_chunks = max_grad_games/chunk_size;
	double scalar, average, angle = 180.0, CurrGrad[256];
	GGradient *AG, *NG;
	
	FILE * flog = fopen("gradient.log","w");
	fclose(flog);
	for (i = 0; i < var_number; i++) CurrGrad[i] = Grad[i] = 0.0;
	AG = (GGradient*)malloc(angle_number * sizeof(GGradient));
	memset(AG,0,angle_number * sizeof(GGradient));
	NG = (GGradient*)malloc(angle_number * sizeof(GGradient));

	LOCK(TB->lock);
	TB->command++;
	TB->type = GRADIENT_COMMAND;
	TB->data_i[0] = depth;
	TB->data_i[1] = chunk_size;
	TB->data_d[0] = radius;
	for (i = 0; i < var_number; i++) TB->Var[i] = Variables[IndexVar[i]].var;
	memcpy(TB->Base,Base,var_number * sizeof(double));
	UNLOCK(TB->lock);
    while (chunks < max_chunks && angle > angle_target) {
        for (i = 0; i < PrN; i++) if (TB->feedback[i].updated) goto set_lock; 
		Sleep(1);
set_lock:
		LOCK(TB->lock);
		for (i = 0; i < PrN; i++) {
			if (TB->feedback[i].updated) {
				TB->feedback[i].updated = 0;
				for (j = 0; j < var_number; j++) {
					CurrGrad[j] += TB->feedback[i].List[j];
					AG[chunks % angle_number].grad[j] += TB->feedback[i].List[j];
				}
				UNLOCK(TB->lock);
				chunks++;
				goto check_gradient;
			}
		}
		UNLOCK(TB->lock);
		continue;
check_gradient:
		fprintf(stdout,"%d chunks: ",chunks);
		normalize(var_number,Grad,CurrGrad,1.0);
		log_list(stdout,Grad);
		FILE * flog = fopen("gradient.log","a");
		log_list(flog,Grad);
	    fclose(flog);
		if (angle_number <= 1) continue;
		if (F(chunks % angle_number)) {
			memset(NG,0,angle_number * sizeof(GGradient));
			for (i = 0; i < angle_number; i++) normalize(var_number,NG[i].grad,AG[i].grad,1.0);
			average = 0.0;
			for (i = 0; i < angle_number - 1; i++) {
				for (j = i + 1; j < angle_number; j++) {
					scalar = 0.0;
					for (k = 0; k < var_number; k++) scalar += NG[i].grad[k] * NG[j].grad[k];
					average += scalar;
				}
			}
			average /= (double)(angle_number * (angle_number - 1)) * 0.5;
			average = Min(0.99999,Max(-0.99999,average));
			angle = (acos(average) * 180.0)/3.1415926535;
			fprintf(stdout,"Angle = %.2lf\n",angle);
		}
	}
	LOCK(TB->lock);
	TB->command++;
	TB->type = 0;
	UNLOCK(TB->lock);
	return;
}
void GD(int depth, int max_grad_games, int angle_number, double angle_target, int max_line_games, double gain, double success, double fail, double stop, double min_radius, double radius) {
	int i, iter = 0, played;
	double Grad[256], New[256], OldBest[256], score, a;

	FILE * flog = fopen("tuner.log","w");
	log_list_int(flog,BestEval);
	fclose(flog);
	fprintf(stdout,"Gradient descent: %d dimensions\n",var_number);

loop:
	iter++;
	fprintf(stdout,"Iteration %d, radius = %.2lf\n",iter,radius);
	copy_list(OldBest,BestEval);

	//radius = 2.0;
	//get_list(Grad,"(-0.06,0.03,-0.01,-0.06,0.22,0.12,0.21,0.08,0.13,0.02,0.18,0.04,0.22,0.14,-0.15,-0.12,0.08,0.03,0.06,-0.01,0.01,-0.07,0.03,-0.03,-0.00,0.05,-0.09,0.01,-0.08,-0.10,0.09,-0.01,0.00,-0.05,0.05,-0.00,0.00,-0.04,-0.12,-0.04,-0.02,-0.00,0.14,0.02,-0.00,0.01,-0.05,-0.01,0.11,0.00,-0.09,-0.03,-0.04,0.02,-0.14,-0.03,-0.12,0.09,0.06,0.01,0.15,0.06,0.08,0.06,-0.01,0.05,0.14,0.08,0.01,0.12,-0.03,0.05,-0.10,0.03,-0.02,0.05,0.09,0.04,0.14,0.06,-0.07,0.02,-0.01,0.03,0.09,0.02,-0.12,0.09,-0.01,0.03,-0.05,0.13,-0.04,-0.01,-0.04,0.04,0.19,-0.03,0.05,-0.02,0.05,-0.08,0.01,0.01,0.07,0.03,0.02,0.03,0.12,0.20,-0.03,-0.02,-0.03,-0.09,0.03,0.11,0.15,-0.01,-0.07,0.02,0.08,-0.03,0.14,0.01,0.06,-0.07,0.03,-0.04,0.05,0.09,-0.02,-0.01,0.05,0.07,-0.04,-0.02,-0.01,-0.02,-0.03,-0.01,0.01,0.04,0.09,0.04,-0.07,0.02,0.08,0.04,-0.01,-0.00,-0.01,-0.09,-0.06,0.10,0.10,0.06,-0.03,0.11,0.08,0.01,0.10,-0.05,-0.05,-0.01,0.13,-0.02,0.01,-0.01,-0.03,-0.03,0.08,0.07,0.02,0.05,0.01,0.03,-0.05,0.07,-0.05,0.01,0.02)");
	Gradient(depth,128,max_grad_games,angle_number,angle_target,radius,BestEval,Grad);

	a = radius;
	if (radius <= min_radius) min_radius = radius * 0.45;
	while (a >= min_radius) {
		fprintf(stdout,"Verification %.2lf: ",a);
		compute_list(New,BestEval,Grad,a);
		/*FILE * flog = fopen("tuner.log","a");
		log_list_int(flog,New);
	    fclose(flog);*/
		if (match_los(New,BestEval,128,max_line_games,depth,gain,success,fail,stop,&played,&score)) {
			fprintf(stdout,"\nNew best: ");
		    log_list_int(stdout,New);
	        FILE * flog = fopen("tuner.log","a");
	        fprintf(flog,"New best: ");
		    log_list_int(flog,New);
	        fclose(flog);

			copy_list(BestEval,New);
			a *= 0.6;
			fprintf(stdout,"Verification %.2lf: ",a);
		    compute_list(New,OldBest,Grad,a);
			if (match_los(New,BestEval,128,max_line_games,depth,gain,Min(success,2.0),Min(fail,1.5),Min(stop,1.5),&played,&score)) {
				fprintf(stdout,"\nNew best: ");
		        log_list_int(stdout,New);
				FILE * flog = fopen("tuner.log","a");
	        	fprintf(flog,"New best: ");
		    	log_list_int(flog,New);
	        	fclose(flog);

				copy_list(BestEval,New);
			}
			goto loop;
		}
		a *= 0.7;
	}
	radius *= 0.7;
    goto loop;
}
void MaterialStat(int depth, int games) {
	int i, cnt = 0, wp, bp, wn, bn, wl, bl, wd, bd, wr, br, wq, bq, index, phase, wb, bb, w_min, b_min, w_maj, b_maj;
	double New[256];
	FILE * fstat = fopen("matstat.txt","w");
	fclose(fstat);

typedef enum {
	QPq, QPPqp, QPPPqpp, QPPPPqppp,
	RPr, RPPrp, RPPPrpp, RPPPPrppp,
	LPl, LPPlp, LPPPlpp, LPPPPlppp,
	LPd, LPPdp, LPPPdpp, LPPPPdppp,
	NPn, NPPnp, NPPPnpp, NPPPPnppp,
	BPn, BPPnp, BPPPnpp, BPPPPnppp,
	NPb, NPPbp, NPPPbpp, NPPPPbppp,
	mat_type_cnt
} GMType;
#define IncMatType(type) {W[type]+=MatStat[index].w;D[type]+=MatStat[index].d;L[type]+=MatStat[index].l;eval[type]+=MatStat[index].eval_sum;cov[type]+=MatStat[index].cov_sum;}
#define DecMatType(type) {W[type]+=MatStat[index].l;D[type]+=MatStat[index].d;L[type]+=MatStat[index].w;eval[type]-=MatStat[index].eval_sum;cov[type]+=MatStat[index].cov_sum;}

	int W[64], D[64], L[64];
	sint64 eval[64];
	double cov[64], eval_stat[64];
	for (i = 0; i < 64; i++) eval_stat[i] = 1000.0;

	int * mat_score_shift = (int*)malloc(TotalMat * sizeof(int) * 2);
	int shift_pos;
	
	copy_list(New,DefaultEval);

	fprintf(stdout,"Collecting material statistics...\n");
loop:
	cnt++;
	match_smp(DefaultEval,New,games,depth);
	fprintf(stdout,"Games played: %d\n",cnt * games);
	fstat = fopen("matstat.txt","a");
	fprintf(fstat,"Games played: %d\n",cnt * games);
	fclose(fstat);
	for (i = 0; i < 64; i++) {
		eval[i] = W[i] = D[i] = L[i] = 0;
		cov[i] = 0.0;
	}

	memset(mat_score_shift,0,TotalMat * sizeof(int) * 2);
	shift_pos = 0;

	for (wq = 0; wq < 3 && T(parent); wq++)
	for (bq = 0; bq < 3; bq++)
	for (wr = 0; wr < 3; wr++)
	for (br = 0; br < 3; br++)
	for (wl = 0; wl < 2; wl++)
	for (bl = 0; bl < 2; bl++)
	for (wd = 0; wd < 2; wd++)
	for (bd = 0; bd < 2; bd++)
	for (wn = 0; wn < 3; wn++)
	for (bn = 0; bn < 3; bn++)
	for (wp = 0; wp < 9; wp++)
	for (bp = 0; bp < 9; bp++) {
		index = wp*MatWP+bp*MatBP+wn*MatWN+bn*MatBN+wl*MatWL+bl*MatBL+wd*MatWD+bd*MatBD+wr*MatWR+br*MatBR+wq*MatWQ+bq*MatBQ;
		phase = Min(32, (wn + bn + wl + bl + wd + bd) + 3 * (wr + br) + 6 * (wq + bq));
		wb = wl + wd;
		bb = bl + bd;
		w_min = wb + wn;
	    b_min = bb + bn;
		w_maj = wq + wr;
	    b_maj = bq + br;

		if (w_maj + w_min >= 1 && b_maj + b_min >= 1 && (wp != bp || w_min != b_min || w_maj != b_maj)) {
			int mat_index[4], total = 0, w = 0, d = 0, l = 0;
			sint64 eval_sum = 0;
			mat_index[0] = index; mat_index[1] = mat_index[2] = mat_index[3] = -1;
			conj_mat_index(index,mat_index+1,mat_index+2,mat_index+3);
			for (i = 0; i < 4 && mat_index[i] >= 0; i++) {
				total += MatStat[mat_index[i]].w + MatStat[mat_index[i]].d + MatStat[mat_index[i]].l;
				w += Even(i) ? MatStat[mat_index[i]].w : MatStat[mat_index[i]].l;
				d += MatStat[mat_index[i]].d;
				l += Even(i) ? MatStat[mat_index[i]].l : MatStat[mat_index[i]].w;
				eval_sum += Even(i) ? MatStat[mat_index[i]].eval_sum : (-MatStat[mat_index[i]].eval_sum);
			}
			if (total < 64) goto no_shift;
			double ratio = (((double)w) + 0.5 * ((double)d))/(double)total;
			double elo_est = elo_from_ratio(ratio);
			if (Abs(elo_est) >= 400.0) goto no_shift;
			int eval_delta = 0;
			int score = Material[index].score;
			int mul;
			if (score > 0) mul = Material[index].mul_w;
			else if (score < 0) mul = Material[index].mul_b;
			else mul = 0;
			int av_eval = eval_sum/(sint64)total;
			for (int j = 63; j >= 0; j--) if (eval_stat[j] <= Abs(elo_est)) {
				eval_delta = Sgn(elo_est) * ((j << 3) + 8) - av_eval;
				break;
			}
			eval_delta = Sgn(eval_delta) * Max(Abs(eval_delta) - Convert(375.0/sqrt((double)total),int),0);
			if (mul) eval_delta = (eval_delta * 15)/mul;
			//if (Abs(score + eval_delta) < Abs(score)) eval_delta = Sgn(eval_delta) * Min((3 * Abs(score))/4,Abs(eval_delta));
			//if (Abs(eval_delta) > 120) eval_delta = Sgn(eval_delta) * 120; 
			if (Abs(eval_delta) < 5) goto no_shift;
			
			mat_score_shift[shift_pos] = index;
			mat_score_shift[shift_pos + 1] = eval_delta;
			shift_pos += 2;
		}
no_shift:
		if (w_maj == wq && b_maj == bq && w_min == 0 && b_min == 0) {
			if (wq == 1 && bq == 1) {
				if (wp == 1 && bp == 0) IncMatType(QPq);
				if (wp == 0 && bp == 1) DecMatType(QPq);

				if (wp == 2 && bp == 1) IncMatType(QPPqp);
				if (wp == 1 && bp == 2) DecMatType(QPPqp);

				if (wp == 3 && bp == 2) IncMatType(QPPPqpp);
				if (wp == 2 && bp == 3) DecMatType(QPPPqpp);

				if (wp == 4 && bp == 3) IncMatType(QPPPPqppp);
				if (wp == 3 && bp == 4) DecMatType(QPPPPqppp);
			}
		}
		if (w_maj == wr && b_maj == br && w_min == 0 && b_min == 0) {
			if (wr == 1 && br == 1) {
				if (wp == 1 && bp == 0) IncMatType(RPr);
				if (wp == 0 && bp == 1) DecMatType(RPr);

				if (wp == 2 && bp == 1) IncMatType(RPPrp);
				if (wp == 1 && bp == 2) DecMatType(RPPrp);

				if (wp == 3 && bp == 2) IncMatType(RPPPrpp);
				if (wp == 2 && bp == 3) DecMatType(RPPPrpp);

				if (wp == 4 && bp == 3) IncMatType(RPPPPrppp);
				if (wp == 3 && bp == 4) DecMatType(RPPPPrppp);
			}
		}
		if (w_maj == 0 && b_maj == 0 && w_min == 1 && b_min == 1) {
			if ((wl == 1 && bl == 1) || (wd == 1 && bd == 1)) {
				if (wp == 1 && bp == 0) IncMatType(LPl);
				if (wp == 0 && bp == 1) DecMatType(LPl);

				if (wp == 2 && bp == 1) IncMatType(LPPlp);
				if (wp == 1 && bp == 2) DecMatType(LPPlp);

				if (wp == 3 && bp == 2) IncMatType(LPPPlpp);
				if (wp == 2 && bp == 3) DecMatType(LPPPlpp);

				if (wp == 4 && bp == 3) IncMatType(LPPPPlppp);
				if (wp == 3 && bp == 4) DecMatType(LPPPPlppp);
			}
		}
		if (w_maj == 0 && b_maj == 0 && w_min == 1 && b_min == 1) {
			if ((wl == 1 && bd == 1) || (wd == 1 && bl == 1)) {
				if (wp == 1 && bp == 0) IncMatType(LPd);
				if (wp == 0 && bp == 1) DecMatType(LPd);

				if (wp == 2 && bp == 1) IncMatType(LPPdp);
				if (wp == 1 && bp == 2) DecMatType(LPPdp);

				if (wp == 3 && bp == 2) IncMatType(LPPPdpp);
				if (wp == 2 && bp == 3) DecMatType(LPPPdpp);

				if (wp == 4 && bp == 3) IncMatType(LPPPPdppp);
				if (wp == 3 && bp == 4) DecMatType(LPPPPdppp);
			}
		}
		if (w_maj == 0 && b_maj == 0 && w_min == 1 && b_min == 1) {
			if (wn == 1 && bn == 1) {
				if (wp == 1 && bp == 0) IncMatType(NPn);
				if (wp == 0 && bp == 1) DecMatType(NPn);

				if (wp == 2 && bp == 1) IncMatType(NPPnp);
				if (wp == 1 && bp == 2) DecMatType(NPPnp);

				if (wp == 3 && bp == 2) IncMatType(NPPPnpp);
				if (wp == 2 && bp == 3) DecMatType(NPPPnpp);

				if (wp == 4 && bp == 3) IncMatType(NPPPPnppp);
				if (wp == 3 && bp == 4) DecMatType(NPPPPnppp);
			}
		}
		if (w_maj == 0 && b_maj == 0 && w_min == 1 && b_min == 1) {
			if ((wb == 1 && bn == 1 && wp > bp) || (wn == 1 && bb == 1 && wp < bp)) {
				if (wp == 1 && bp == 0) IncMatType(BPn);
				if (wp == 0 && bp == 1) DecMatType(BPn);

				if (wp == 2 && bp == 1) IncMatType(BPPnp);
				if (wp == 1 && bp == 2) DecMatType(BPPnp);

				if (wp == 3 && bp == 2) IncMatType(BPPPnpp);
				if (wp == 2 && bp == 3) DecMatType(BPPPnpp);

				if (wp == 4 && bp == 3) IncMatType(BPPPPnppp);
				if (wp == 3 && bp == 4) DecMatType(BPPPPnppp);
			}
		}
		if (w_maj == 0 && b_maj == 0 && w_min == 1 && b_min == 1) {
			if ((wn == 1 && bb == 1 && wp > bp) || (wb == 1 && bn == 1 && wp < bp)) {
				if (wp == 1 && bp == 0) IncMatType(NPb);
				if (wp == 0 && bp == 1) DecMatType(NPb);

				if (wp == 2 && bp == 1) IncMatType(NPPbp);
				if (wp == 1 && bp == 2) DecMatType(NPPbp);

				if (wp == 3 && bp == 2) IncMatType(NPPPbpp);
				if (wp == 2 && bp == 3) DecMatType(NPPPbpp);

				if (wp == 4 && bp == 3) IncMatType(NPPPPbppp);
				if (wp == 3 && bp == 4) DecMatType(NPPPPbppp);
			}
		}
	}

	for (i = 0; i < MatScoreShiftNumber; i++) {
		index = MatScoreShift[i * 2];
		int shift = MatScoreShift[(i * 2) + 1];
		for (int j = 0; j < MatScoreShiftNumber; j++) {
			if (mat_score_shift[j * 2] == index) {
				mat_score_shift[(j * 2) + 1] += shift;
				goto match_found;
			}
		}
		mat_score_shift[shift_pos] = index;
		mat_score_shift[shift_pos + 1] = shift;
		shift_pos += 2;
match_found:
		nodes += 0;
	}

	FILE * fshift = fopen("matshift.txt","w");
	fprintf(fshift,"#define MatScoreShiftNumber %d\n",shift_pos/2);
	fprintf(fshift,"const int MatScoreShift[MatScoreShiftNumber * 2] = {\n");
	for (i = 0; i < shift_pos; i++) {
		if ((i % 24) == 0) fprintf(fshift,"    ");
		fprintf(fshift,"%d",mat_score_shift[i]);
		if (i + 1 == shift_pos) fprintf(fshift,"\n};");
		else if ((i % 24) == 23) fprintf(fshift,",\n");
		else fprintf(fshift,", ");
	}
	fclose(fshift);

	fprintf(stdout,"Eval:\n");
	fstat = fopen("matstat.txt","a");
	fprintf(fstat,"Eval:\n");
	fclose(fstat);
	for (i = 0; i < 64; i++) {
		double ratio = ((double)EvalStat[i].score_x2)/(2.0 * (double)EvalStat[i].games);
		eval_stat[i] = elo_from_ratio(ratio);
		if (i < 32) {
			fprintf(stdout,"%dcp-%dcp: games = %d, ratio = %.2lf [%.1lf elo]\n",i << 3,((i + 1) << 3) - 1,EvalStat[i].games,ratio,eval_stat[i]);
			fstat = fopen("matstat.txt","a");
			fprintf(fstat,"%dcp-%dcp: games = %d, ratio = %.2lf [%.1lf elo]\n",i << 3,((i + 1) << 3) - 1,EvalStat[i].games,ratio,eval_stat[i]);
			fclose(fstat);
		}
	}
	fprintf(stdout,"Material:\n");
	fstat = fopen("matstat.txt","a");
	fprintf(fstat,"Material:\n");
	fclose(fstat);
	for (i = 0; i < mat_type_cnt; i++) {
		int total = W[i] + D[i] + L[i];
		if (F(total)) {
			fprintf(stdout,"%d: no hits\n",i); 
			fstat = fopen("matstat.txt","a");
			fprintf(fstat,"%d: no hits\n",i); 
			fclose(fstat);
			continue;
		}
		double ratio = (((double)W[i]) + 0.5 * (double)D[i])/(double)total;
		double av_cov = cov[i]/(double)total;
		double av_eval = ((double)eval[i])/(double)total;
		double elo_est = elo_from_ratio(ratio);
		int index = Min(63,((int)av_eval) >> 3);
		double elo_delta = elo_est-eval_stat[index];
		double eval_delta = 0.0;
		for (int j = 63; j >= 0; j--) if (eval_stat[j] <= elo_est) {
			eval_delta = ((double)(j << 3)) + 8.0 - av_eval;
			break;
		}
		fprintf(stdout,"%d: [%.2lf, %.0lf], %d-%d-%d, %.2lf [%.0lf], %.0lf/%.0lf\n",i,
			av_cov,av_eval,W[i],D[i],L[i],ratio,elo_est,eval_delta,elo_delta);
		fstat = fopen("matstat.txt","a"); 
		fprintf(fstat,"%d: cov/eval = [%.2lf, %.0lf], WDL = %d-%d-%d, ratio = %.2lf [%.0lf], delta eval/delta elo = %.0lf/%.0lf\n",i,
			av_cov,av_eval,W[i],D[i],L[i],ratio,elo_est,eval_delta,elo_delta);
		fclose(fstat);
	}
	goto loop;
}
#endif

void init() {
	int i, j, k, l, n, r, f, d, e, index, bits, op, eg;
	int wp, bp, wn, bn, wl, bl, wd, bd, wr, br, wq, bq, score, phase, wb, bb;
    int w_maj, b_maj, w_maj_score, b_maj_score, w_min, b_min, w_tot_score, b_tot_score, wmul, bmul, wmat, bmat, m1, m2, m3, m4;
	int bit_list[16];
	char name_magic[256], name_material[256];
	uint64 u;
	sint64 mscore;
	double new_depth, value;

#ifdef TUNER
	set_zero_array(IPstPawnToQueen,18,5,1000,1);
	for (i = 0; i < 18 * 5; i++) Variables[i].value = PstPawnToQueen[i];
	set(IPstKingOp,70,20,1);
	set(IPstKingEg,98,20,1);
	set(IPawnBlockedOp,5,10,1);
	set(IPawnBlockedEg,12,10,1);
	set(IPawnIslandOp,6,10,1);
	set(IPawnIslandEg,2,10,1);
	set(IPawnHoleOp,4,10,1);
	set(IPawnHoleEg,5,10,1);
	set(IKnightOutpostOp,12,10,1);
	set(IKnightOutpostEg,2,10,1);
	set(IKnightOutpostProtectedOp,9,10,1);
	set(IKnightOutpostProtectedEg,7,10,1);
	set(IBishopOutpostOp,4,10,1);
	set(IBishopOutpostEg,9,10,1);
	set(IKnightMobilityOp,6,1,1);
	set(IKnightMobilityEg,3,1,1);
	set(IBishopMobilityOp,5,1,1);
	set(IBishopMobilityEg,3,1,1);
	set(IRookMobilityOp,2,1,1);
	set(IRookMobilityEg,3,1,1);
	set(IQueenMobilityOp,2,1,1);
	set(IQueenMobilityEg,4,1,1);
	set(IQueenSeventhRankOp,-5,20,1);
	set(IQueenSeventhRankEg,19,20,1);
	set(IQueenSeventhRankDoubledOp,2,20,1);
	set(IQueenSeventhRankDoubledEg,13,20,1);
	set(IRookHOFOp,4,10,1);
	set(IRookHOFEg,0,10,1);
	set(IRookHOFPawnAttOp,9,10,1);
	set(IRookHOFPawnAttEg,10,10,1);
	set(IRookHOFKingAttOp,9,10,1);
	set(IRookHOFKingAttEg,0,10,1);
	set(IRookOFOp,19,10,1);
	set(IRookOFEg,15,10,1);
	set(IRookOFMinorAttOp,18,10,1);
	set(IRookOFMinorAttEg,6,10,1);
	set(IRookOFMinorFixedOp,7,10,1);
	set(IRookOFMinorFixedEg,-1,10,1);
	set(IRookSeventhRankOp,8,10,1);
	set(IRookSeventhRankEg,16,10,1);
	set(IRookSeventhRankDoubledOp,15,10,1);
	set(IRookSeventhRankDoubledEg,13,10,1);
	set(IRookEighthRankOp,7,10,1);
	set(IRookEighthRankEg,0,10,1);
	set(IRookSixthRankOp,12,10,1);
	set(IRookSixthRankEg,4,10,1);
	set(IDoubledClosedOp,0,10,1);
	set(IDoubledClosedEg,1,10,1);
	set(IDoubledClosedIsolatedOp,2,10,1);
	set(IDoubledClosedIsolatedEg,10,10,1);
	set(IIsolatedClosedOp,2,10,1);
	set(IIsolatedClosedEg,6,10,1);
	set(IBackwardClosedOp,0,10,1);
	set(IBackwardClosedEg,2,10,1);
	set(IDoubledOpenOp,6,10,1);
	set(IDoubledOpenEg,4,10,1);
	set(IDoubledOpenIsolatedOp,0,10,1);
	set(IDoubledOpenIsolatedEg,3,10,1);
	set(IIsolatedOpenOp,14,10,1);
	set(IIsolatedOpenEg,16,10,1);
	set(IBackwardOpenOp,13,10,1);
	set(IBackwardOpenEg,13,10,1);
	set_zero_tr_array(IMaterialMe,5,4,500,1);
	set_zero_tr_array(IMaterialOpp,5,5,500,1);
#endif

#ifdef TUNER
	FILE * ffen = NULL;
	ffen = fopen("op.epd","r");
	if (ffen != NULL) {
		for (i = 0; i < 65536; i++) {
			fgets(Fen[i],128,ffen);
			if (feof(ffen)) {
				op_pos_number = Max(op_pos_number - 1, 0);
				break;
			} else op_pos_number++;
		}
	} else {
		fprintf(stdout,"File 'op.epd' not found\n");
		exit(0);
	}
	fclose(ffen);
	if (op_pos_number == 0) {
		sprintf(Fen[0],"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\n");
		op_pos_number = 1;
	}
#ifdef LOCAL_TUNER
	fprintf(stdout,"%d opening positions\n",op_pos_number);
#endif
#endif
	for (i = 0; i < 64; i++) {
		HLine[i] = VLine[i] = NDiag[i] = SDiag[i] = RMask[i] = BMask[i] = QMask[i] = MDiag[i] = 0;
		BMagicMask[i] = RMagicMask[i] = QMagicMask[i] = NAtt[i] = SArea[i] = DArea[i] = NArea[i] = 0;
		PAtt[0][i] = PAtt[1][i] = PMove[0][i] = PMove[1][i] = PWay[0][i] = PWay[1][i] = PSupport[0][i] = PSupport[1][i] = 0;
		for (j = 0; j < 64; j++) {
			Between[i][j] = 0;
			FullLine[i][j] = 0;
		}
	}
	sprintf(name_material,NAME_MATERIAL"_%d",WinParId);
#ifdef LOCAL_TUNER
	char name_material_stat[256], name_eval_stat[256];
	sprintf(name_material_stat,NAME_MATERIAL_STAT"_%d",WinParId);
	sprintf(name_eval_stat,NAME_EVAL_STAT"_%d",WinParId);
#endif
	if (parent) {
		MATERIAL = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TotalMat * sizeof(GMaterial), name_material);
		Material = (GMaterial*)MapViewOfFile(MATERIAL,FILE_MAP_ALL_ACCESS,0,0,TotalMat * sizeof(GMaterial));
		for (index = 0; index < TotalMat; index++) Material[index].phase = 0xFF;
#ifdef LOCAL_TUNER
		MATERIAL_STAT = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TotalMat * sizeof(GMaterialStat), name_material_stat);
		MatStat = (GMaterialStat*)MapViewOfFile(MATERIAL_STAT,FILE_MAP_ALL_ACCESS,0,0,TotalMat * sizeof(GMaterialStat));
		memset(MatStat,0,TotalMat * sizeof(GMaterialStat));
		EVAL_STAT = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 64 * sizeof(GEvalStat), name_eval_stat);
		EvalStat = (GEvalStat*)MapViewOfFile(EVAL_STAT,FILE_MAP_ALL_ACCESS,0,0,64 * sizeof(GEvalStat));
		memset(EvalStat,0,64 * sizeof(GEvalStat));
#endif
	} else {
		MATERIAL = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_material);
		Material = (GMaterial*)MapViewOfFile(MATERIAL,FILE_MAP_ALL_ACCESS,0,0,TotalMat * sizeof(GMaterial));
#ifdef LOCAL_TUNER
		MATERIAL_STAT = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_material_stat);
		MatStat = (GMaterialStat*)MapViewOfFile(MATERIAL_STAT,FILE_MAP_ALL_ACCESS,0,0,TotalMat * sizeof(GMaterialStat));
		EVAL_STAT = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_eval_stat);
		EvalStat = (GEvalStat*)MapViewOfFile(EVAL_STAT,FILE_MAP_ALL_ACCESS,0,0,64 * sizeof(GEvalStat));
#endif
	}
	for (i = 0; i < 64; i++) {
		for (j = 0; j < 64; j++) {
			if (i != j) {
				u = Bit(j);
				if (File(i) == File(j)) VLine[i] |= u;
				if (Rank(i) == Rank(j)) HLine[i] |= u;
				if (NDiag(i) == NDiag(j)) NDiag[i] |= u;
				if (SDiag(i) == SDiag(j)) SDiag[i] |= u;
				if (Dist(i,j) <= 2) {
					DArea[i] |= u;
					if (Dist(i,j) <= 1) SArea[i] |= u;
					if (Abs(Rank(i)-Rank(j)) + Abs(File(i)-File(j)) == 3) NAtt[i] |= u;
				}
				if (j == i + 8) PMove[0][i] |= u;
				if (j == i - 8) PMove[1][i] |= u;
				if (Abs(File(i) - File(j)) == 1) {
					if (Rank(j) >= Rank(i)) {
						PSupport[1][i] |= u;
				        if (Rank(j) - Rank(i) == 1) PAtt[0][i] |= u;
					} 
					if (Rank(j) <= Rank(i)) {
						PSupport[0][i] |= u;
						if (Rank(i) - Rank(j) == 1) PAtt[1][i] |= u;
					}
				} else if (File(i) == File(j)) {
					if (Rank(j) > Rank(i)) PWay[0][i] |= u;
					else PWay[1][i] |= u;
				}
			}
		}
	}
	for (i = 0; i < 64; i++) {
		RMask[i] = HLine[i] | VLine[i];
		BMask[i] = NDiag[i] | SDiag[i];
		QMask[i] = RMask[i] | BMask[i];
		BMagicMask[i] = BMask[i] & Interior;
		RMagicMask[i] = RMask[i];
		if (File(i) > 0) RMagicMask[i] &= ~File[0];
		if (Rank(i) > 0) RMagicMask[i] &= ~Line[0];
		if (File(i) < 7) RMagicMask[i] &= ~File[7];
		if (Rank(i) < 7) RMagicMask[i] &= ~Line[7];
		QMagicMask[i] = BMagicMask[i] | RMagicMask[i];
		for (j = 0; j < 64; j++) {
			if (NAtt[i] & NAtt[j]) Add(NArea[i],j);
		}
		if ((File(i) <= 3 && Rank(i) <= 3) || (File(i) > 3 && Rank(i) > 3)) MDiag[i] = NDiag[i];
		else MDiag[i] = SDiag[i];
	}
	for (i = 0; i < 64; i++) {
		for (u = QMask[i]; T(u); Cut(u)) {
			j = lsb(u);
			k = Sgn(Rank(j)-Rank(i));
			l = Sgn(File(j)-File(i));
			for (n = i + 8 * k + l; n != j; n += (8 * k + l)) Add(Between[i][j],n);
		}
		for (u = BMask[i]; T(u); Cut(u)) {
			j = lsb(u);
			FullLine[i][j] = BMask[i] & BMask[j];
		}
		for (u = RMask[i]; T(u); Cut(u)) {
			j = lsb(u);
			FullLine[i][j] = RMask[i] & RMask[j];
		}
	}
	sprintf(name_magic,NAME_MAGIC"_%d",WinParId);
	if (parent) {
		MAGIC = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, magic_size * sizeof(uint64), name_magic);
		MagicAttacks = (uint64*)MapViewOfFile(MAGIC,FILE_MAP_ALL_ACCESS,0,0,magic_size * sizeof(uint64));
		for (i = 0; i < 64; i++) {
			bits = 64 - BShift[i];
			for (u = BMagicMask[i], j = 0; T(u); Cut(u), j++) bit_list[j] = lsb(u);
			for (j = 0; j < Bit(bits); j++) {
				u = 0;
				for (k = 0; k < bits; k++)
					if (Odd(j >> k)) Add(u,bit_list[k]);
				index = Convert(BOffset[i] + ((BMagic[i] * u) >> BShift[i]),int);
           	    MagicAttacks[index] = BMagicHash(i,u);
			}
			bits = 64 - RShift[i];
			for (u = RMagicMask[i], j = 0; T(u); Cut(u), j++) bit_list[j] = lsb(u);
			for (j = 0; j < Bit(bits); j++) {
				u = 0;
				for (k = 0; k < bits; k++)
					if (Odd(j >> k)) Add(u,bit_list[k]);
				index = Convert(ROffset[i] + ((RMagic[i] * u) >> RShift[i]),int);
             	MagicAttacks[index] = RMagicHash(i,u);
			}	
		}
	} else {
		MAGIC = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_magic);
		MagicAttacks = (uint64*)MapViewOfFile(MAGIC,FILE_MAP_ALL_ACCESS,0,0,magic_size * sizeof(uint64));
	}
	init_pst();
	for (i = 0; i < 8; i++) {
		West[i] = 0;
		East[i] = 0;
		Forward[0][i] = Forward[1][i] = 0;
		AreaB[i] = AreaS[i] = AreaC[i] = 0;
		PIsolated[i] = 0;
		for (j = 0; j < 8; j++) {
			if (i < j) Forward[0][i] |= Line[j];
			else if (i > j) Forward[1][i] |= Line[j];
			if (i < j) East[i] |= File[j];
			else if (i > j) West[i] |= File[j];
		}
		if (i <= 3) {
			if (i > 0) {
				AreaB[i] = File[File(i) - 1];
				AreaS[i] = File[File(i)];
				AreaC[i] = File[File(i) + 1];
			} else {
				AreaB[i] = File[File(i)];
				AreaS[i] = File[File(i) + 1];
				AreaC[i] = File[File(i) + 2];
			}
		} else {
			if (i < 7) {
				AreaB[i] = File[File(i) + 1];
				AreaS[i] = File[File(i)];
				AreaC[i] = File[File(i) - 1];
			} else {
				AreaB[i] = File[File(i)];
				AreaS[i] = File[File(i) - 1];
				AreaC[i] = File[File(i) - 2];
			}
		}
		if (i > 0) PIsolated[i] |= File[i - 1];
		if (i < 7) PIsolated[i] |= File[i + 1];
	}
    for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++) MVVLVA[i][j] = (MVVLVAAttacker[i] << 24) | (MVVLVAVictim[j] << 27);
	for (i = 0; i < 256; i++) PieceFromChar[i] = 0;
    PieceFromChar[66] = 6;
    PieceFromChar[75] = 14;
    PieceFromChar[78] = 4;
    PieceFromChar[80] = 2;
    PieceFromChar[81] = 12;
    PieceFromChar[82] = 10;
    PieceFromChar[98] = 7;
    PieceFromChar[107] = 15;
    PieceFromChar[110] = 5;
    PieceFromChar[112] = 3;
    PieceFromChar[113] = 13;
    PieceFromChar[114] = 11;
	TurnKey = random();
	for (i = 0; i < 8; i++) EPKey[i] = random();
	for (i = 0; i < 16; i++) CastleKey[i] = random();
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 64; j++) PieceKey[i][j] = random();
	}
	for (wq = 0; wq < 3 && T(parent); wq++)
	for (bq = 0; bq < 3; bq++)
	for (wr = 0; wr < 3; wr++)
	for (br = 0; br < 3; br++)
	for (wl = 0; wl < 2; wl++)
	for (bl = 0; bl < 2; bl++)
	for (wd = 0; wd < 2; wd++)
	for (bd = 0; bd < 2; bd++)
	for (wn = 0; wn < 3; wn++)
	for (bn = 0; bn < 3; bn++)
	for (wp = 0; wp < 9; wp++)
	for (bp = 0; bp < 9; bp++) {
		index = wp*MatWP+bp*MatBP+wn*MatWN+bn*MatBN+wl*MatWL+bl*MatBL+wd*MatWD+bd*MatBD+wr*MatWR+br*MatBR+wq*MatWQ+bq*MatBQ;
		if (Material[index].phase == 0xFF) {
			phase = Min(32, (wn + bn + wl + bl + wd + bd) + 3 * (wr + br) + 6 * (wq + bq));
			wb = wl + wd;
			bb = bl + bd;
			w_min = wb + wn;
	        b_min = bb + bn;
		    w_maj = wq + wr;
	        b_maj = bq + br;
			w_maj_score = 5 * wr + 10 * wq;
            b_maj_score = 5 * br + 10 * bq;
		    w_tot_score = w_maj_score + 3 * w_min;
		    b_tot_score = b_maj_score + 3 * b_min;
			wmat = wmul = 15;
			bmat = bmul = 15;
			
			mscore = ((wp - bp) * PawnV4) + ((wn - bn) * KnightV4) + ((wb - bb) * BishopV4) + ((wr - br) * RookV4) + ((wq - bq) * QueenV4) + 
				 (((wb/2) - (bb/2)) * BishopPairV4) + (((br/2) - (wr/2)) * DoubleRooksV4) + (((br + bq >= 2) - (wr + wq >= 2)) * DoubleHeavyV4);
			mscore += (((wp - 5) * wn) - ((bp - 5) * bn)) * KnightPawnAdj;
			mscore -= (((wp - 5) * wr) - ((bp - 5) * br)) * RookPawnAdj;
			mscore -= (wp - 5) * (wb/2) * C4(0, 1, 2, 3);
			mscore += (bp - 5) * (bb/2) * C4(0, 1, 2, 3);
			if (wb == 2 && b_min == 0) mscore += C4(5, 5, 5, 5);
			if (bb == 2 && w_min == 0) mscore -= C4(5, 5, 5, 5);

			m4 = (int)(((sint16)(mscore >> 48)) + ((mscore >> 47) & 1));
			m3 = (int)((sint16)((mscore >> 32) & 0xFFFF) + ((mscore >> 31) & 1));
			m2 = (int)((sint16)((mscore >> 16) & 0xFFFF) + ((mscore >> 15) & 1));
			m1 = (int)(sint16)(mscore & 0xFFFF);

			if (phase < 8) score = ((m3  * phase) + (m4 * (8 - phase)))/8;
			else if (phase < 24) score = ((m2  * (phase - 8)) + (m3 * (24 - phase)))/16;
			else score = ((m1  * (phase - 24)) + (m2 * (32 - phase)))/8;

#ifndef TUNER
			int p_w[5], p_b[5], quad = 0, piece_mul;
			p_w[0] = wp; p_w[1] = wn; p_w[2] = wb; p_w[3] = wr; p_w[4] = wq;
			p_b[0] = bp; p_b[1] = bn; p_b[2] = bb; p_b[3] = br; p_b[4] = bq;
#define me White
			for (i = 0; i < 5; i++) {
				piece_mul = Tr(MaterialOpp,5,i,0);
				if (i <= 3) for (j = i; j < 5; j++) {
					piece_mul += Tr(MaterialMe,5,i,j - i) * (*(CVar(p,me)+j));
					if (j > i) piece_mul += Tr(MaterialOpp,5,i,j - i) * (*(CVar(p,opp)+j));
				}
				quad += piece_mul * (1 - (2 * me)) * (*(CVar(p,me)+i));
			}
#undef me
#define me Black
			for (i = 0; i < 5; i++) {
				piece_mul = Tr(MaterialOpp,5,i,0);
				if (i <= 3) for (j = i; j < 5; j++) {
					piece_mul += Tr(MaterialMe,5,i,j - i) * (*(CVar(p,me)+j));
					if (j > i) piece_mul += Tr(MaterialOpp,5,i,j - i) * (*(CVar(p,opp)+j));
				}
				quad += piece_mul * (1 - (2 * me)) * (*(CVar(p,me)+i));
			}
#undef me
			score += quad/100;
#endif

			if (wp <= 1) {
				wmul = Min(wmul, 13);
				if (wr == 1 && wq + w_min == 0 && br == 1) wmat = Min(wmat, 11);
				if (wp == 0) wmul = Min(wmul, 10);
				if (w_maj == 0 && w_min == 1 && b_maj + b_min >= 1) wmat = Min(wmat, 1);
			}
			if (bp <= 1) {
				bmul = Min(bmul, 13);
				if (br == 1 && bq + b_min == 0 && wr == 1) bmat = Min(bmat, 11);
				if (bp == 0) bmul = Min(bmul, 10);
				if (b_maj == 0 && b_min == 1 && w_maj + w_min >= 1) bmat = Min(bmat, 1);
			}
			if (wp == 0 && w_tot_score - b_tot_score <= 3) {
			    if (wb < 2 || b_min != bn || bn > 1 || b_maj != 0) {
					if (w_maj == 0 || w_maj + w_min <= 2 || w_tot_score - b_tot_score < 3) wmat = Min(wmat, 1);
					else wmat = Min(wmat, 7);
				}
		    }
		    if (bp == 0 && b_tot_score - w_tot_score <= 3) {
			    if (bb < 2 || w_min != wn || wn > 1 || w_maj != 0) {
					if (b_maj == 0 || b_maj + b_min <= 2 || b_tot_score - w_tot_score < 3) bmat = Min(bmat, 1);
					else bmat = Min(bmat, 7);
				}
		    }
			if (w_maj == 0) {
			    if (w_min == 0) {
                    if (bp > wp) score -= (bp - wp) * Endgame(PawnValue);
			    } else if (w_min == 1 && wb == 1) {
					if (b_min == 1 && bb == 1 && wl != bl) {
						wmul = Min(wmul, 7);
						if (wp - bp <= 1) wmul = Min(wmul, 5);
					}
				}
			    if (wp == 0) {
				    if (w_min <= 1) wmul = 0;
				    else if (w_min == 2) {
					    if (wn == 2) {
						    if (b_min + b_maj == 0 && bp != 0) wmat = Min(wmat, 3);
						    else wmul = 0;
					    }
				    }
			    }
		    }
		    if (b_maj == 0) {
			    if (b_min == 0) {
                    if (wp > bp) score += (wp - bp) * Endgame(PawnValue);
			    } else if (b_min == 1 && bb == 1) {
					if (w_min == 1 && wb == 1 && wl != bl) {
						bmul = Min(bmul, 7);
						if (bp - wp <= 1) bmul = Min(bmul, 5);
					}
				}
			    if (bp == 0) {
				    if (b_min <= 1) bmul = 0;
				    else if (b_min == 2) {
					    if (bn == 2) {
						    if (w_min + w_maj == 0 && wp != 0) bmat = Min(bmat, 3);
						    else bmul = 0;
					    }
				    }
			    }
		    }
			if (wr == 1 && br == 1 && wq + bq + w_min + b_min == 0) {
				wmul = Min(wmul, 11);
				bmul = Min(bmul, 11);
			}
			if (wq == 1 && bq == 1 && wr + br + w_min + b_min == 0) {
				wmul = Min(wmul, 11);
				bmul = Min(bmul, 11);
			}
			if (wq + bq == 0 && wr == 1 && br == 1 && w_min == 1 && b_min == 1 && ((wl == 1 && bd == 1) || (wd == 1 && bl == 1))) {
				wmul = Min(wmul, 12);
				bmul = Min(bmul, 12);
			}
			if (b_maj == 0 && b_min == 0 && bp == 0) {
				if (w_maj >= 1) wmul = 15;
				else if (wn >= 1 && wb >= 1) wmul = 15;
				else if (wl >= 1 && wd >= 1) wmul = 15;
			}
			if (w_maj == 0 && w_min == 0 && wp == 0) {
				if (b_maj >= 1) bmul = 15;
				else if (bn >= 1 && bb >= 1) bmul = 15;
				else if (bl >= 1 && bd >= 1) bmul = 15;
			}
			if (b_tot_score <= 5 && bp == 0 && wq == 1) wmul = 15;
			if (w_tot_score <= 5 && wp == 0 && bq == 1) bmul = 15;

			if (score > 0) score = (score * wmat)/15;
			else score = (score * bmat)/15;

		    Material[index].score = score;
			Material[index].mul_w = wmul;
			Material[index].mul_b = bmul;
			Material[index].phase = phase;
			Material[index].pieces_w = w_maj + w_min;
			Material[index].pieces_b = b_maj + b_min;
			Material[index].flags = 0;
			if (w_maj == 0 && w_min == wb && wb <= 1) Material[index].flags |= FlagSingleBishop_w;
			if (b_maj == 0 && b_min == bb && bb <= 1) Material[index].flags |= FlagSingleBishop_b;
			if (w_maj == 0) Material[index].flags |= FlagNoHeavy_w;
			if (b_maj == 0) Material[index].flags |= FlagNoHeavy_b;
			if (w_min == 0) Material[index].flags |= FlagNoLight_w;
			if (b_min == 0) Material[index].flags |= FlagNoLight_b;
			if (((w_maj == 0 || w_min == 0) && w_maj + w_min <= 1) || b_maj + b_min == 0) Material[index].flags |= FlagCallEvalEndgame_w;
			if (((b_maj == 0 || b_min == 0) && b_maj + b_min <= 1) || w_maj + w_min == 0) Material[index].flags |= FlagCallEvalEndgame_b;
		}
	}
	gen_kpk();

#ifdef LOAD_MAT_SHIFT
	if (parent) for (i = 0; i < MatScoreShiftNumber; i++) {
		index = MatScoreShift[i * 2];
		int shift = MatScoreShift[(i * 2) + 1];
		Material[index].score += shift;
	}
#endif
}

void init_search(int clear_hash) {
	int i, j;
#ifndef TUNER
	for (i = 0; i < 16; i++) for (j = 0; j < 64; j++) History[i][j] = 1;
	memset(Delta,0,16 * 4096 * sizeof(sint16));
	memset(Ref,0,16 * 64 * sizeof(GRef));
#else
	for (i = 0; i < 16; i++) for (j = 0; j < 64; j++) History1[(i << 6) | j] = History2[(i << 6) | j] = 1;
	memset(Delta1,0,16 * 4096 * sizeof(sint16));
	memset(Delta2,0,16 * 4096 * sizeof(sint16));
	memset(Ref1,0,16 * 64 * sizeof(GRef));
	memset(Ref2,0,16 * 64 * sizeof(GRef));
#endif
	memset(Data + 1, 0, 127 * sizeof(GData));
	if (clear_hash) {
		date = 0;
#ifndef TUNER
		if (parent) {
			date = 1;
		    memset(Hash,0,hash_size * sizeof(GEntry));
		    memset(PVHash,0,pv_hash_size * sizeof(GPVEntry));
		}
#else
	    memset(HashBase1,0,hash_size * sizeof(GEntry));
		memset(HashBase2,0,hash_size * sizeof(GEntry));
		memset(PawnHashBase1,0,pawn_hash_size * sizeof(GPawnEntry));
		memset(PawnHashBase2,0,pawn_hash_size * sizeof(GPawnEntry));
		memset(PVHashBase1,0,pv_hash_size * sizeof(GPVEntry));
		memset(PVHashBase2,0,pv_hash_size * sizeof(GPVEntry));
#endif
	}
#ifdef TUNER
	Hash = HashBase1;
	PawnHash = PawnHashBase1;
	PVHash = PVHashBase1;
	History = History1;
	Delta = Delta1;
#endif
	get_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	nodes = 0;
	best_move = best_score = 0;
	LastDepth = LastTime = LastValue = LastExactValue = InstCnt = 0;
	LastSpeed = 0;
	if (F(init_cnt)) PVN = 1;
	Infinite = 1;
	SearchMoves = 0;
	TimeLimit1 = TimeLimit2 = 0;
	Stop = Searching = 0;
	DepthLimit = 128;
	LastDepth = 128;
	Print = 1;
	memset(CurrentSI,0,sizeof(GSearchInfo));
	memset(BaseSI,0,sizeof(GSearchInfo));
	GlobalTime = GlobalInc = 0x1FFFFFFF;
#ifdef CUT_ALL
	pv_height = 0;
#endif
}

void setup_board() {
	int i;
	uint64 occ;
	GEntry * Entry;

	occ = 0;
	sp = 0;
	date++;
	if (date > 0x8000) { // musn't ever happen
		date = 2;
		// now GUI must wait for readyok... we have plenty of time :)
		for (Entry = Hash, i = 0; i < hash_size; i++, Entry++) Entry->date = 1;
		for (PVEntry = PVHash, i = 0; i < pv_hash_size; i++, PVEntry++) PVEntry->date = 1;
	}
	Current->material = 0;
	Current->pst = 0;
	Current->key = PieceKey[0][0];
	if (Current->turn) Current->key ^= TurnKey;
	Current->key ^= CastleKey[Current->castle_flags];
	if (Current->ep_square) Current->key ^= EPKey[File(Current->ep_square)];
	Current->pawn_key = 0;
	Current->pawn_key ^= CastleKey[Current->castle_flags];
	for (i = 0; i < 16; i++) BB(i) = 0;
	for (i = 0; i < 64; i++) {
		if (Square(i)) {
		    Add(BB(Square(i)),i);
		    Add(BB(Square(i) & 1),i);
		    Add(occ,i);
		    Current->key ^= PieceKey[Square(i)][i];
		    if (Square(i) < WhiteKnight) Current->pawn_key ^= PieceKey[Square(i)][i];
			if (Square(i) < WhiteKing) Current->material += MatCode[Square(i)];
			else Current->pawn_key ^= PieceKey[Square(i)][i];
			Current->pst += PST[Square(i)][i];
		}
	}
	for (i = 0; i < 64; i++) {
		if (IsSlider(Square(i))) {
			if (Square(i) < WhiteRook) Attacks(i) = BishopAttacks(i,occ);
			else if (Square(i) < WhiteQueen) Attacks(i) = RookAttacks(i,occ);
			else Attacks(i) = QueenAttacks(i,occ);
		}
	}
	if (popcnt(BB(WhiteKnight)) > 2 || popcnt(BB(WhiteLight)) > 1 || popcnt(BB(WhiteDark)) > 1 
		|| popcnt(BB(WhiteRook)) > 2 || popcnt(BB(WhiteQueen)) > 2) Current->material |= FlagUnusualMaterial; 
	if (popcnt(BB(BlackKnight)) > 2 || popcnt(BB(BlackLight)) > 1 || popcnt(BB(BlackDark)) > 1 
		|| popcnt(BB(BlackRook)) > 2 || popcnt(BB(BlackQueen)) > 2) Current->material |= FlagUnusualMaterial; 
	Current->capture = 0;
	Current->killer[1] = Current->killer[2] = 0;
	Current->ply = 0;
	Stack[sp] = Current->key;
}

void get_board(const char fen[]) {
	int pos, i, j;
	unsigned char c;

	Current = Data;
	memset(Board,0,sizeof(GBoard));
	memset(Current,0,sizeof(GData));
	pos = 0;
	c = fen[pos];
	while (c == ' ') c = fen[++pos];
	for (i = 56; i >= 0; i -= 8) {
		for (j = 0; j <= 7; ) {
            if (c <= '8') j += c - '0';
			else {
				Square(i+j) = PieceFromChar[c];
				if (Even(SDiag(i+j)) && Eq(Square(i+j)/2,3)) Square(i+j) += 2;
				j++;
			}
			c = fen[++pos];
		}
		c = fen[++pos];
	}
	if (c == 'b') Current->turn = 1;
	c = fen[++pos]; c = fen[++pos];
    if (c == '-') c = fen[++pos];
	if (c == 'K') { Current->castle_flags |= CanCastle_OO; c = fen[++pos]; }
	if (c == 'Q') { Current->castle_flags |= CanCastle_OOO; c = fen[++pos]; }
	if (c == 'k') { Current->castle_flags |= CanCastle_oo; c = fen[++pos]; }
	if (c == 'q') { Current->castle_flags |= CanCastle_ooo; c = fen[++pos]; }
	c = fen[++pos];
	if (c != '-') {
        i = c + fen[++pos] * 8 - 489;
		j = i ^ 8;
		if (Square(i) != 0) i = 0;
		else if (Square(j) != (3 - Current->turn)) i = 0;
		else if (Square(j-1) != (Current->turn+2) && Square(j+1) != (Current->turn+2)) i = 0;
		Current->ep_square = i;
	}
	setup_board();
}

void init_hash() {
#ifdef TUNER
	Hash = HashBase1;
	PawnHash = PawnHashBase1;
	PVHash = PVHashBase1;
#else
	sint64 size = (hash_size * sizeof(GEntry));
	sint64 pv_size = (pv_hash_size * sizeof(GPVEntry));
	char name_hash[256], name_pv_hash[256], name_store_hash[256];
	sprintf(name_hash,NAME_HASH"_%d",WinParId);
	sprintf(name_pv_hash,NAME_PV_HASH"_%d",WinParId);
	sprintf(name_store_hash,NAME_STORE_HASH"_%d",WinParId);

	if (T(parent) && T(hash_initialized)) {
		if (HashBase != NULL) UnmapViewOfFile(HashBase);
		CloseHandle(HASH);
	}

    if (parent) {
		if (F(LargePages)) goto no_lp;
#ifndef LARGE_PAGES
		goto no_lp;
#endif
	    typedef int (*GETLARGEPAGEMINIMUM)(void);
	    GETLARGEPAGEMINIMUM pGetLargePageMinimum;
        HINSTANCE hDll = LoadLibrary(TEXT("kernel32.dll"));  
        if (hDll == NULL) goto no_lp;
        pGetLargePageMinimum = (GETLARGEPAGEMINIMUM)GetProcAddress(hDll, "GetLargePageMinimum");
        if (pGetLargePageMinimum == NULL) goto no_lp;
        int min_page_size = (*pGetLargePageMinimum)();
		if (size < min_page_size) size = min_page_size;
	    if (F(hash_initialized)) {
	        TOKEN_PRIVILEGES tp;
	        HANDLE hToken;
	        OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	        LookupPrivilegeValue(NULL, "SeLockMemoryPrivilege", &tp.Privileges[0].Luid);
	        tp.PrivilegeCount = 1;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	        AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	    }
		HASH = NULL;
		HASH = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT | SEC_LARGE_PAGES, size >> 32, size & 0xFFFFFFFF, name_hash);
		if (HASH != NULL) {
			fprintf(stdout,"Large page hash\n");
			goto hash_allocated;
		}
no_lp:
		HASH = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, size >> 32, size & 0xFFFFFFFF, name_hash);
hash_allocated:
		if (F(hash_initialized)) {
			PV_HASH = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, pv_size, name_pv_hash);
#ifdef HASH_STORE
			STORE_HASH = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, store_hash_size * sizeof(GStoreEntry), name_store_hash);
			StoreHash = (GStoreEntry*)MapViewOfFile(STORE_HASH,FILE_MAP_ALL_ACCESS,0,0,store_hash_size * sizeof(GStoreEntry));
			memset(StoreHash, 0, store_hash_size * sizeof(GStoreEntry)); 
			ifstream fstore;
	    	fstore.open("GullHash.gsh", ifstream::binary);
	    	if (!fstore.fail()) {
	        	fstore.read((char*)StoreHash,store_hash_size * sizeof(GStoreEntry));
 	        	fstore.close();
	   	 	}
#endif
		}
	} else {
		HASH = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_hash);
		if (F(hash_initialized)) {
			PV_HASH = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_pv_hash);
#ifdef HASH_STORE
			STORE_HASH = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name_store_hash);
			StoreHash = (GStoreEntry*)MapViewOfFile(STORE_HASH,FILE_MAP_ALL_ACCESS,0,0,store_hash_size * sizeof(GStoreEntry));
#endif
		}
	}
	HashBase = (GEntry*)MapViewOfFile(HASH,FILE_MAP_ALL_ACCESS,0,0,size);
	Hash = HashBase;
	if (parent) memset(Hash,0,size);
	hash_mask = hash_size - 4;
	if (F(hash_initialized)) {
	    PVHash = (GPVEntry*)MapViewOfFile(PV_HASH,FILE_MAP_ALL_ACCESS,0,0,pv_size);
	    if (parent) memset(PVHash,0,pv_size);
	}
#endif
	hash_initialized = 1;
}

void move_to_string(int move, char string[]) { 
	int pos = 0;
    string[pos++] = ((move >> 6) & 7) + 'a';
    string[pos++] = ((move >> 9) & 7) + '1';
    string[pos++] = (move & 7) + 'a';
    string[pos++] = ((move >> 3) & 7) + '1';
    if (IsPromotion(move)) {
        if ((move & 0xF000) == FlagPQueen)  string[pos++] = 'q';
        else if ((move & 0xF000) == FlagPRook)   string[pos++] = 'r';
        else if ((move & 0xF000) == FlagPLight || (move & 0xF000) == FlagPDark) string[pos++] = 'b';
        else if ((move & 0xF000) == FlagPKnight) string[pos++] = 'n';
    }
    string[pos] = 0;
}

int move_from_string(char string[]) { 
	int from, to, move;
    from = ((string[1] - '1') * 8) + (string[0] - 'a');
    to  = ((string[3] - '1') * 8) + (string[2] - 'a');
    move = (from << 6) | to;
    if (Board->square[from] >= WhiteKing && Abs(to - from) == 2) move |= FlagCastling;
    if (T(Current->ep_square) && to == Current->ep_square) move |= FlagEP;
    if (string[4] != 0) {
        if (string[4] == 'q') move |= FlagPQueen;
        else if (string[4] == 'r') move |= FlagPRook;
        else if (string[4] == 'b') {
			if (Odd(to ^ Rank(to))) move |= FlagPLight;
			else move |= FlagPDark;
		} else if (string[4] == 'n') move |= FlagPKnight;
    }
    return move;
}

void pick_pv() {
	GEntry * Entry;
	GPawnEntry * PawnEntry;
	int i, depth, move;
	if (pvp >= Min(pv_length,64)) {
		PV[pvp] = 0;
		return;
	}
	move = 0;
	depth = -256;
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Entry->key == Low32(Current->key)) {
			if (T(Entry->move) && Entry->low_depth > depth) {
				depth = Entry->low_depth;
				move = Entry->move;
			}
		}
	}
	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key)) {
			if (T(PVEntry->move) && PVEntry->depth > depth) {
				depth = PVEntry->depth;
				move = PVEntry->move;
			}
		}
	}
#ifdef HASH_STORE
	for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4; i++, StoreEntry++) {
		if (StoreEntry->key == Low32(Current->key)) {
			if (T(StoreEntry->move) && StoreEntry->depth > depth) {
				depth = StoreEntry->depth;
				move = StoreEntry->move;
			}
		}
	}
#endif
	evaluate();
	if (move) {
		PV[pvp] = move;
		pvp++;
		if (Current->turn) do_move<1>(move);
		else do_move<0>(move);
		for (i = 4; i <= Current->ply; i+= 2) if (Stack[sp-i] == Current->key) {
			PV[pvp] = 0;
			goto finish;
		}
		pick_pv();
finish:
		if (Current->turn ^ 1) undo_move<1>(move);
		else undo_move<0>(move);
	} else PV[pvp] = 0;
}

template <bool me> void do_move(int move) {
	GEntry * Entry;
	GPawnEntry * PawnEntry;
	int from, to, piece, capture;
	GData * Next;
	uint64 u, updated, mask_from, mask_to, occ;
#ifdef LONGEST_LINE
	if (F((Current + 1)->att[White])) {
		int * p;
		for (Next = Data + 1, p = LLSave; Next <= Current; Next++, p++) {
			if (Next->move) *p = Next->move;
			else break;
		}
		*p = 0;
		if (p - LLSave > LLLength) {
			int * q;
			LLLength = p - LLSave;
			for (p = LLSave, q = LLine; T(*p); p++, q++) *q = *p;
			*q = 0;
		}
	}
#endif
#ifdef DEBUG
	if (nodes == 801535)
		nodes += 0;
	if (F(is_legal<me>(move)))
		nodes += 0;
	if (F(check_board()))
		nodes += 0;
#endif

	to = To(move);
	Next = Current + 1;
	Next->ep_square = 0;
	capture = Square(to);
    if (F(capture)) {
		Next->capture = 0;
		goto non_capture;
    }
	from = From(move);
	piece = Square(from);
	Next->turn = opp;
	Next->capture = capture;
	Square(from) = 0;
	Square(to) = piece;
	Next->piece = piece;
	mask_from = Bit(from);
	mask_to = Bit(to);
	BB(piece) ^= mask_from;
	Piece(me) ^= mask_from;
	BB(capture) ^= mask_to;
	Piece(opp) ^= mask_to;
	BB(piece) |= mask_to;
	Piece(me) |= mask_to;
	Next->castle_flags = Current->castle_flags & UpdateCastling[to] & UpdateCastling[from];
	Next->pst = Current->pst + PST[piece][to] - PST[piece][from] - PST[capture][to];
	Next->key = Current->key ^ PieceKey[piece][from] ^ PieceKey[piece][to] ^ PieceKey[capture][to] ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
	if (capture != IPawn(opp)) Next->pawn_key = Current->pawn_key ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags]; // of course we can put a lot of operations inside this "if {}" but the speedup won't be worth the effort
	else Next->pawn_key = Current->pawn_key ^ PieceKey[IPawn(opp)][to] ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
	Next->material = Current->material - MatCode[capture];
	if (T(Current->material & FlagUnusualMaterial) && capture >= WhiteKnight) {
		if (popcnt(BB(WhiteQueen)) <= 2 && popcnt(BB(BlackQueen)) <= 2) {
			if (popcnt(BB(WhiteLight)) <= 1 && popcnt(BB(BlackLight)) <= 1 && popcnt(BB(WhiteKnight)) <= 2
				&& popcnt(BB(BlackKnight)) <= 2 && popcnt(BB(WhiteRook)) <= 2 && popcnt(BB(BlackRook)) <= 2)
				Next->material ^= FlagUnusualMaterial;
		}
	}
	if (piece == IPawn(me)) {
		Next->pawn_key ^= PieceKey[IPawn(me)][from] ^ PieceKey[piece][to];
		if (IsPromotion(move)) {
			piece = Promotion(move,me);
			Square(to) = piece;
		    Next->material += MatCode[piece] - MatCode[IPawn(me)];
			if (piece < WhiteRook) {
				if (piece >= WhiteLight && T(BB(piece))) Next->material |= FlagUnusualMaterial;
				if (Multiple(BB(piece))) Next->material |= FlagUnusualMaterial;
			} else if (Multiple(BB(piece))) Next->material |= FlagUnusualMaterial;
			Pawn(me) ^= mask_to;
			BB(piece) |= mask_to;
			Next->pst += PST[piece][to] - PST[IPawn(me)][to];
			Next->key ^= PieceKey[piece][to] ^ PieceKey[IPawn(me)][to];
			Next->pawn_key ^= PieceKey[IPawn(me)][to];
		}
		PawnEntry = PawnHash + (Next->pawn_key & pawn_hash_mask);
	    prefetch((char *)PawnEntry,_MM_HINT_NTA);
	} else if (piece >= WhiteKing) {
		Next->pawn_key ^= PieceKey[piece][from] ^ PieceKey[piece][to];
		PawnEntry = PawnHash + (Next->pawn_key & pawn_hash_mask);
	    prefetch((char *)PawnEntry,_MM_HINT_NTA);
	} else if (capture < WhiteKnight) {
		PawnEntry = PawnHash + (Next->pawn_key & pawn_hash_mask);
	    prefetch((char *)PawnEntry,_MM_HINT_NTA);
	}
	if (F(Next->material & FlagUnusualMaterial)) prefetch((char *)(Material + Next->material), _MM_HINT_NTA); 
	if (Current->ep_square) Next->key ^= EPKey[File(Current->ep_square)];
	Next->turn = Current->turn ^ 1;
	Next->key ^= TurnKey;
	Entry = Hash + (High32(Next->key) & hash_mask);
	prefetch((char *)Entry,_MM_HINT_NTA);
	occ = BB(White) | BB(Black);
	if (piece >= WhiteLight) {
		if (piece < WhiteRook) Next->attacks[to] = BishopAttacks(to,occ);
		else if (piece < WhiteQueen) Next->attacks[to] = RookAttacks(to,occ);
		else if (piece < WhiteKing) Next->attacks[to] = QueenAttacks(to,occ);
	}
	mask_to = ~mask_to;
	for (u = (Bishop(0) | Bishop(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & mask_from)) Next->attacks[from] = Attacks(from);
		else Next->attacks[from] = BishopAttacks(from,occ);
	}
	for (u = (Rook(0) | Rook(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & mask_from)) Next->attacks[from] = Attacks(from);
		else Next->attacks[from] = RookAttacks(from,occ);
	}
	for (u = (Queen(0) | Queen(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & mask_from)) Next->attacks[from] = Attacks(from);
		else {
			if (RMask[from] & mask_from) Next->attacks[from] = RookAttacks(from,occ) | (Attacks(from) & BMask[from]);
			else Next->attacks[from] = BishopAttacks(from,occ) | (Attacks(from) & RMask[from]);
		}
	}
	Next->ply = 0;
	goto finish;
non_capture:
	from = From(move);
	Next->ply = Current->ply + 1;
	piece = Square(from);
	Square(from) = 0;
	Square(to) = piece;
	Next->piece = piece;
	mask_from = Bit(from);
	mask_to = Bit(to);
	BB(piece) ^= mask_from;
	Piece(me) ^= mask_from;
	BB(piece) |= mask_to;
	Piece(me) |= mask_to;
	updated = mask_from | mask_to;
	Next->castle_flags = Current->castle_flags & UpdateCastling[to] & UpdateCastling[from];
	Next->pst = Current->pst + PST[piece][to] - PST[piece][from];
	Next->key = Current->key ^ PieceKey[piece][to] ^ PieceKey[piece][from] ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
	Next->material = Current->material;
	if (piece == IPawn(me)) {
		Next->ply = 0;
		Next->pawn_key = Current->pawn_key ^ PieceKey[IPawn(me)][to] ^ PieceKey[IPawn(me)][from] ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
		if (IsEP(move)) {
			Square(to ^ 8) = 0;
			u = Bit(to ^ 8);
			updated |= u;
			Next->key ^= PieceKey[IPawn(opp)][to ^ 8];
			Next->pawn_key ^= PieceKey[IPawn(opp)][to ^ 8];
			Next->pst -= PST[IPawn(opp)][to ^ 8];
			Pawn(opp) &= ~u;
			Piece(opp) &= ~u;
			Next->material -= MatCode[IPawn(opp)];
		} else if (IsPromotion(move)) {
			piece = Promotion(move,me);
			Square(to) = piece;
		    Next->material += MatCode[piece] - MatCode[IPawn(me)];
			if (piece < WhiteRook) {
				if (piece >= WhiteLight && T(BB(piece))) Next->material |= FlagUnusualMaterial;
				if (Multiple(BB(piece))) Next->material |= FlagUnusualMaterial;
			} else if (Multiple(BB(piece))) Next->material |= FlagUnusualMaterial;
			Pawn(me) ^= mask_to;
			BB(piece) |= mask_to;
			Next->pst += PST[piece][to] - PST[IPawn(me)][to];
			Next->key ^= PieceKey[piece][to] ^ PieceKey[IPawn(me)][to];
			Next->pawn_key ^= PieceKey[IPawn(me)][to];
		} else if (Eq(to ^ from, 16)) {
			if (PAtt[me][(to + from) >> 1] & Pawn(opp)) {
				Next->ep_square = (to + from) >> 1;
				Next->key ^= EPKey[File(Next->ep_square)];
			}
		}
		PawnEntry = PawnHash + (Next->pawn_key & pawn_hash_mask);
	    prefetch((char *)PawnEntry,_MM_HINT_NTA);
	} else {
		if (piece < WhiteKing) Next->pawn_key = Current->pawn_key ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
		else {
			Next->pawn_key = Current->pawn_key ^ PieceKey[piece][to] ^ PieceKey[piece][from] ^ CastleKey[Current->castle_flags] ^ CastleKey[Next->castle_flags];
			PawnEntry = PawnHash + (Next->pawn_key & pawn_hash_mask);
	        prefetch((char *)PawnEntry,_MM_HINT_NTA);
		}
		if (IsCastling(move)) {
			int rold, rnew;
			Next->ply = 0;
			if (to == 6) {
			    rold = 7; 
			    rnew = 5;
		    } else if (to == 2) {
                rold = 0; 
			    rnew = 3;
		    } else if (to == 62) {
                rold = 63;
			    rnew = 61;
		    } else if (to == 58) {
                rold = 56; 
			    rnew = 59;
		    }
			Add(mask_to,rnew);
			updated |= Bit(rnew) | Bit(rold);
			Square(rold) = 0;
			Square(rnew) = IRook(me);
			BB(IRook(me)) ^= Bit(rold);
			Piece(me) ^= Bit(rold);
			BB(IRook(me)) |= Bit(rnew);
			Piece(me) |= Bit(rnew);
			Next->pst += PST[IRook(me)][rnew] - PST[IRook(me)][rold];
			Next->key ^= PieceKey[IRook(me)][rnew] ^ PieceKey[IRook(me)][rold];
			Next->attacks[rnew] = RookAttacks(rnew,BB(White) | BB(Black));
		}
	}

	if (Current->ep_square) Next->key ^= EPKey[File(Current->ep_square)];
	Next->turn = opp;
	Next->key ^= TurnKey;
	Entry = Hash + (High32(Next->key) & hash_mask);
	prefetch((char *)Entry,_MM_HINT_NTA);

	mask_to = ~mask_to;
	occ = BB(White) | BB(Black);
	if (piece >= WhiteLight) {
		if (piece < WhiteRook) Next->attacks[to] = BishopAttacks(to,occ);
		else if (piece < WhiteQueen) Next->attacks[to] = RookAttacks(to,occ);
		else if (piece < WhiteKing) Next->attacks[to] = QueenAttacks(to,occ);
	}
	for (u = (Bishop(0) | Bishop(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & updated)) Next->attacks[from] = Attacks(from);
		else Next->attacks[from] = BishopAttacks(from,occ);
	}
	for (u = (Rook(0) | Rook(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & updated)) Next->attacks[from] = Attacks(from);
		else Next->attacks[from] = RookAttacks(from,occ);
	}
	for (u = (Queen(0) | Queen(1)) & mask_to; T(u); Cut(u)) {
		from = lsb(u);
		if (F(Attacks(from) & updated)) Next->attacks[from] = Attacks(from);
		else {
			if (F(BMask[from] & updated)) Next->attacks[from] = RookAttacks(from,occ) | (Attacks(from) & BMask[from]);
			else if (F(RMask[from] & updated)) Next->attacks[from] = BishopAttacks(from,occ) | (Attacks(from) & RMask[from]);
			else Next->attacks[from] = QueenAttacks(from,occ);
		}
	}
finish:
	sp++;
	Stack[sp] = Next->key;
	Next->move = move;
	Next->gen_flags = 0;
	Current++;
#ifdef DEBUG
	if (nodes == 262812)
		nodes += 0;
	if (F(check_board()))
		nodes += 0;
#endif
	nodes++;
}

template <bool me> void undo_move(int move) {
	int to, from, piece;
#ifdef DEBUG
	if (F(check_board()))
		nodes += 0;
#endif
	from = From(move);
	to = To(move);
	if (IsPromotion(move)) {
		BB(Square(to)) ^= Bit(to);
		piece = IPawn(me);
	} else piece = Square(to);
	Square(from) = piece;
	BB(piece) |= Bit(from);
	Piece(me) |= Bit(from);
	BB(piece) &= ~Bit(to);
	Piece(me) ^= Bit(to);
	Square(to) = Current->capture;
	if (Current->capture) {
	    BB(Current->capture) |= Bit(to);
	    Piece(opp) |= Bit(to);
	} else {
		if (IsCastling(move)) {
			int rold, rnew;
			if (to == 6) {
			    rold = 7; 
			    rnew = 5;
		    } else if (to == 2) {
                rold = 0; 
			    rnew = 3;
		    } else if (to == 62) {
                rold = 63;
			    rnew = 61;
		    } else if (to == 58) {
                rold = 56; 
			    rnew = 59;
		    }
			Square(rnew) = 0;
			Square(rold) = IRook(me);
			Rook(me) ^= Bit(rnew);
			Piece(me) ^= Bit(rnew);
			Rook(me) |= Bit(rold);
			Piece(me) |= Bit(rold);
		} else if (IsEP(move)) {
			to = to ^ 8;
			piece = IPawn(opp);
			Square(to) = piece;
			Piece(opp) |= Bit(to);
			Pawn(opp) |= Bit(to);
		}
	}
	Current--;
	sp--;
#ifdef DEBUG
	if (F(check_board()))
		nodes += 0;
#endif
}

void do_null() {
	uint64 u;
	GData * Next;
	GEntry * Entry;
#ifdef DEBUG
	if (F(check_board()))
		nodes += 0;
#endif
	Next = Current + 1;
	Next->key = Current->key ^ TurnKey;
	Entry = Hash + (High32(Next->key) & hash_mask);
	prefetch((char *)Entry,_MM_HINT_NTA);
	Next->pawn_key = Current->pawn_key;
	Next->eval_key = 0;
	Next->turn = Current->turn ^ 1;
	Next->material = Current->material;
	Next->pst = Current->pst;
	Next->ply = 0;
	Next->castle_flags = Current->castle_flags;
	Next->ep_square = 0;
	Next->capture = 0;
	if (Current->ep_square) Next->key ^= EPKey[File(Current->ep_square)];
	for (u = Slider(0) | Slider(1); T(u); Cut(u)) Next->attacks[lsb(u)] = Attacks(lsb(u));
	sp++;	
	Next->att[White] = Current->att[White];
	Next->att[Black] = Current->att[Black];
	Next->patt[White] = Current->patt[White];
	Next->patt[Black] = Current->patt[Black];
	Next->xray[White] = Current->xray[White];
	Next->xray[Black] = Current->xray[Black];
	Next->pin[White] = Current->pin[White];
	Next->pin[Black] = Current->pin[Black];
	Next->king_att[White] = Current->king_att[White];
	Next->king_att[Black] = Current->king_att[Black];
	Stack[sp] = Next->key;
	Next->threat = Current->threat;
	Next->passer = Current->passer;
	Next->score = -Current->score;
	Next->move = 0;
	Next->gen_flags = 0;
	Current++;
	nodes++;
}

void undo_null() {
	Current--;
	sp--;
#ifdef DEBUG
	if (F(check_board()))
		nodes += 0;
#endif
}

template <bool me> int kpkx() {
	uint64 u;
    if (me == White) u = KPK[Current->turn][lsb(Pawn(White))][lsb(King(White))] & Bit(lsb(King(Black)));
	else u = KPK[Current->turn ^ 1][63 - lsb(Pawn(Black))][63 - lsb(King(Black))] & Bit(63 - lsb(King(White)));
	if (u) return 15;
	else if (Piece(opp) ^ King(opp)) return 1;
	else return 0;
}

template <bool me> int krpkrx() {
	int mul = 15;
	int sq = lsb(Pawn(me));
	int rrank = CRank(me,sq);
	int o_king = lsb(King(opp));
	int o_rook = lsb(Rook(opp));
	int m_king = lsb(King(me));
	int add_mat = T(Piece(opp) ^ King(opp) ^ Rook(opp));
	int clear = F(add_mat) || F((PWay[opp][sq] | PIsolated[File(sq)]) & Forward[opp][Rank(sq + Push(me))] & (Piece(opp) ^ King(opp) ^ Rook(opp)));
	
	if (F(clear)) return 15;

	if (PWay[me][sq] & King(opp)) {
		if (rrank <= 3) mul = Min(mul, add_mat << 2);
		if (rrank == 4 && CRank(me,m_king) <= 4 && CRank(me,o_rook) == 5 && T(King(opp) & (Line(me,6) | Line(me,7))) 
			&& (Current->turn != me || F(PAtt[me][sq] & Attacks(lsb(Rook(me))) & (~SArea[o_king])))) mul = Min(mul, add_mat << 2);
		if (rrank >= 5 && CRank(me,o_rook) <= 1 && (Current->turn != me || Check(me) || Dist(m_king, sq) >= 2)) mul = Min(mul, add_mat << 2);
		if (T(King(opp) & (File[1] | File[2] | File[6] | File[7])) && T(Rook(opp) & Line(me,7)) && T(Between[o_king][o_rook] & (File[3] | File[4])) && F(Rook(me) & Line(me,7))) mul = Min(mul, add_mat << 2);
		return mul;
	}

	if (SArea[o_king] & PWay[me][sq] & Line(me,7)) {
		if (rrank <= 4 && CRank(me,m_king) <= 4 && CRank(me,o_rook) == 5) mul = Min(mul, add_mat << 2);
		if (rrank == 5 && CRank(me,o_rook) <= 1 && Current->turn != me || (F(SArea[m_king] & PAtt[me][sq] & (~SArea[o_king])) && (Check(me) || Dist(m_king, sq) >= 2))) 
			mul = Min(mul, add_mat << 2);
	}

	if (T(PWay[me][sq] & Rook(me)) && T(PWay[opp][sq] & Rook(opp)) && T(King(opp) & (File[0] | File[1] | File[6] | File[7]) & Line(me,6)) 
		&& T(Pawn(me) & (File[0] | File[7])) && T(Between[o_king][sq] & (File[3] | File[4]))) mul = Min(mul, add_mat << 2);

	return mul;
}

template <bool me> int kqkp() {
	if (F(SArea[lsb(King(opp))] & Pawn(opp) & Line(me,1) & (File[0] | File[2] | File[5] | File[7]))) return 15;
	if (PWay[opp][lsb(Pawn(opp))] & (King(me) | Queen(me))) return 15;
	if (Pawn(opp) & (File[0] | File[7])) return 1;
	else return 2;
	return 15;
}

template <bool me> int krkpx() {
	if (T(SArea[lsb(King(opp))] & Pawn(opp) & Line(me,1)) & F(PWay[opp][NB(me,Pawn(opp))] & King(me))) return 0;
	return 15;
}

template <bool me> int krppkrpx() {
	if (Current->passer & Pawn(me)) return 15;
	if (F((~(PWay[opp][lsb(King(opp))] | PSupport[me][lsb(King(opp))])) & Pawn(me))) return 1;
	return 15;
}

template <bool me> int krpppkrppx() {
	if (T(Current->passer & Pawn(me)) || F((SArea[lsb(Pawn(opp))] | SArea[msb(Pawn(opp))]) & Pawn(opp))) return 15;
	if (F((~(PWay[opp][lsb(King(opp))] | PSupport[me][lsb(King(opp))])) & Pawn(me))) return 2;
	return 15;
}

template <bool me> int kbpkbx() {
	int sq = lsb(Pawn(me));
	uint64 u;
	if ((T(Board->bb[ILight(me)]) && T(Board->bb[IDark(opp)])) || (T(Board->bb[IDark(me)]) && T(Board->bb[ILight(opp)]))) {
		if (CRank(me, sq) <= 4) return 0;
		if (T(PWay[me][sq] & King(opp)) && CRank(me, sq) <= 5) return 0;
		for (u = Bishop(opp); T(u); Cut(u)) {
			if (CRank(me,lsb(u)) <= 4 && T(Attacks(lsb(u)) & PWay[me][sq])) return 0;
			if (Current->turn == opp && T(Attacks(lsb(u)) & Pawn(me))) return 0;
	    }
	} else if (T(PWay[me][sq] & King(opp)) && T(King(opp) & LightArea) != T(Bishop(me) & LightArea)) return 0;
	return 15;
}

template <bool me> int kbpknx() {
	uint64 u;
	if (T(PWay[me][lsb(Pawn(me))] & King(opp)) && T(King(opp) & LightArea) != T(Bishop(me) & LightArea)) return 0;
	if (Current->turn == opp)
	    for (u = Knight(opp); T(u); Cut(u))
		    if (NAtt[lsb(u)] & Pawn(me)) return 0;
	return 15;
}

template <bool me> int kbppkbx() {
	int sq1 = NB(me,Pawn(me));
	int sq2 = NB(opp,Pawn(me));
	int o_king = lsb(King(opp));
	int o_bishop = lsb(Bishop(opp));

	if ((F(Board->bb[ILight(me)]) || F(Board->bb[IDark(opp)])) && (F(Board->bb[IDark(me)]) || F(Board->bb[ILight(opp)]))) return 15;
	if (File(sq1) == File(sq2)) {
		if (CRank(me, sq2) <= 3) return 0;
		if (T(PWay[me][sq2] & King(opp)) && CRank(me, sq2) <= 5) return 0;
	} else if (PIsolated[File(sq1)] & Pawn(me)) {
		if (T(King(opp) & LightArea) != T(Bishop(me) & LightArea)) {
			if (T((SArea[o_king] | King(opp)) & Bit(sq2 + Push(me))) && T(Attacks(o_bishop) & Bit(sq2 + Push(me))))
				if (T((SArea[o_king] | King(opp)) & Bit((sq2 & 0xFFFFFFF8) | File(sq1))) && T(Attacks(o_bishop) & Bit((sq2 & 0xFFFFFFF8) | File(sq1)))) return 0;
		}
	}
	return 15;
}

template <bool me> int krppkrx() {
	int sq1 = NB(me,Pawn(me));
	int sq2 = NB(opp,Pawn(me));

	if ((Piece(opp) ^ King(opp) ^ Rook(opp)) & Forward[me][Rank(sq1 - Push(me))]) return 15;

	if (File(sq1) == File(sq2)) {
		if (T(PWay[me][sq2] & King(opp))) return 8;
		return 15;
	}
	if (T(PIsolated[File(sq2)] & Pawn(me)) && T((File[0] | File[7]) & Pawn(me)) && CRank(me,sq2) == 5 && CRank(me,sq1) == 4 
		&& T(King(opp) & Shift(me,Pawn(me))) && T(Rook(opp) & (Line(me,5) | Line(me,6)))) return 5;

	return 15;
}

typedef struct {
	int kdist_w, kdist_b, king_w, king_b, kf_w, kf_b, kr_w, kr_b, score;
	uint64 patt_w, patt_b;
} GPawnEvalInfo;

template <bool me, bool HPopCnt> __forceinline void eval_pawns(GPawnEntry * PawnEntry, GPawnEvalInfo &PEI) {
	uint64 own = Pawn(me) & (~Forward[opp][CVarPEI(kr,me)]);
	int rmb = CRank(me, NBC(me, own & AreaB[CVarPEI(kf,me)]));
	int rms = CRank(me, NBC(me, own & AreaS[CVarPEI(kf,me)]));
	int rmc = CRank(me, NBC(me, own & AreaC[CVarPEI(kf,me)]));
    int rob = CRank(me, NBC(me, Pawn(opp) & AreaB[CVarPEI(kf,me)])); // bug?: storm pawn h6 is better than two pawns on h6 and h7...  
	int ros = CRank(me, NBC(me, Pawn(opp) & AreaS[CVarPEI(kf,me)]));
	int roc = CRank(me, NBC(me, Pawn(opp) & AreaC[CVarPEI(kf,me)])); 

	PawnEntry->shelter[me] += Shelter[0][rmb] + Shelter[1][rms] + Shelter[2][rmc]; // PawnEntry->shelter[me]: shelter penalty
	if (rmb != rob - 1) PawnEntry->shelter[me] += Storm[0][rob];
	else PawnEntry->shelter[me] += Storm[0][rob] >> 1;
	if (rms != ros - 1) PawnEntry->shelter[me] += Storm[1][ros];
	else PawnEntry->shelter[me] += Storm[1][ros] >> 1;
	if (rmc != roc - 1) PawnEntry->shelter[me] += Storm[2][roc];
	else PawnEntry->shelter[me] += Storm[2][roc] >> 1;

	int rdiag = CRank(me, NBC(me, own & MDiag[CVarPEI(king,me)]));
	PawnEntry->shelter[me] += ShelterDiag[Min(CVarPEI(kf,me), 7 - CVarPEI(kf,me))][rdiag];

	int i = 0;
    for (int file = 0; file <= 7; file++) {
		if (F(File[file] & Pawn(me))) i = 0;
		else {
			if (F(i)) DecV(PEI.score,C(PawnIsland));
			i = 1;
		}
	}

	uint64 u = Pawn(me);
	uint64 connected = 0;
	while (u) {
		uint64 sq = lsb(u);
		uint64 b = Bit(sq);
		int file = File(sq);
		int rank = Rank(sq);
		int rrank = CRank(me, sq);
		u ^= b;

		int value = KingPawnDistance(me,rank,CVarPEI(kr,me),file,CVarPEI(kf,me));
		if (value < CVarPEI(kdist,me)) CVarPEI(kdist,me) = value;
		value = KingPawnDistance(me,rank,CVarPEI(kr,opp),file,CVarPEI(kf,opp));
		if (value < CVarPEI(kdist,opp)) CVarPEI(kdist,opp) = value;

		if (b & LightArea) PawnEntry->light[me] += BlockedPawn[sq];
		else PawnEntry->dark[me] += BlockedPawn[sq];

		if (file >= 2 && T(Pawn(me) & Bit(sq - 2)) && F(Pawn(me) & File[file - 1] & Forward[me][rank - (Push(me) >> 3)])) DecV(PEI.score,C(PawnHole));
		
		if (PawnAll & PWay[me][sq]) {
			if (Pawn(me) & (PWay[me][sq] | PWay[opp][sq])) {
				DecV(PEI.score,C(DoubledClosed));
				if (F(Pawn(me) & PIsolated[file])) DecV(PEI.score,C(DoubledClosedIsolated));
			}
			if (F(Pawn(me) & PIsolated[file])) {
				DecV(PEI.score,C(IsolatedClosed));
				continue;
			}
			if (F(Pawn(me) & PSupport[me][sq])) 
				if (IsGreater(me,NB(me,CVarPEI(patt,me) & PWay[me][sq]),NB(me,(PawnAll | CVarPEI(patt,opp)) & PWay[me][sq]))) DecV(PEI.score,C(BackwardClosed));
			continue;
		}
        if (Pawn(me) & PWay[opp][sq]) {
            DecV(PEI.score,C(DoubledOpen));
			if (F(Pawn(me) & PIsolated[file])) DecV(PEI.score,C(DoubledOpenIsolated));
		}
		if (F(Pawn(me) & PIsolated[file])) DecV(PEI.score,C(IsolatedOpen));
		else if (F(Pawn(me) & PSupport[me][sq])) 
			if (CVarPEI(patt,opp) & PWay[me][sq]) if (IsGreater(me,NB(me,CVarPEI(patt,me) & PWay[me][sq]),NB(me,CVarPEI(patt,opp) & PWay[me][sq]))) DecV(PEI.score,C(BackwardOpen));
        if (Pawn(opp) & PIsolated[file] & Forward[me][rank]) {
		    if (Pawn(opp) & PIsolated[file] & Forward[me][rank] & (~PAtt[me][sq])) {
			    IncV(PEI.score,CandidatePawnValue[rrank]);
			    continue;
		    }
		    if (popcount<HPopCnt>(PAtt[me][sq] & Pawn(opp)) > popcount<HPopCnt>(PAtt[opp][sq] & Pawn(me))) {
			    IncV(PEI.score,CandidatePawnValue[rrank]);
			    continue;
		    }
	    }
		IncV(PEI.score,PassedPawnValue[rrank]);
		if (Pawn(me) & PAtt[opp][sq]) IncV(PEI.score,ProtectedPassedPawnValue[rrank]);
		if (F(Pawn(opp) & West[file]) || F(Pawn(opp) & East[file])) IncV(PEI.score,OutsidePassedPawnValue[rrank]);
		uint64 next = connected & DArea[sq] & PIsolated[file];
		connected |= b;
		if (next) {
			IncV(PEI.score,ConnectedPassedPawnValue[rrank] + ConnectedPassedPawnValue[CRank(me, lsb(next))]);
			Cut(next);
			if (next) IncV(PEI.score,ConnectedPassedPawnValue[rrank] + ConnectedPassedPawnValue[CRank(me, lsb(next))]);
		}
		PawnEntry->passer[me] |= (uint8)(1 << file);
		if (rrank <= 2) continue;
		IncV(PEI.score,Compose(0, KingPawnDistance(me, rank + (Push(me) >> 3), CVarPEI(kr,opp), file, CVarPEI(kf,opp)) * OppKingPawnDistance[rrank]));
		DecV(PEI.score,Compose(0, KingPawnDistance(me, rank + (Push(me) >> 3), CVarPEI(kr,me), file, CVarPEI(kf,me)) * MyKingPawnDistance[rrank]));
	}
}

template <bool HPopCnt> void eval_pawn_structure(GPawnEntry * PawnEntry) {
	GPawnEvalInfo PEI;

	memset(PawnEntry,0,sizeof(GPawnEntry));
	PawnEntry->key = Current->pawn_key;

	PEI.patt_w = ShiftW(White,Pawn(White)) | ShiftE(White,Pawn(White));
	PEI.patt_b = ShiftW(Black,Pawn(Black)) | ShiftE(Black,Pawn(Black));
	PEI.king_w = lsb(King(White));
	PEI.king_b = lsb(King(Black));
	PEI.kf_w = File(PEI.king_w);
	PEI.kf_b = File(PEI.king_b);
	PEI.kr_w = Rank(PEI.king_w);
	PEI.kr_b = Rank(PEI.king_b);
	PEI.kdist_w = PEI.kdist_b = MateValue;
	PEI.score = 0;

	eval_pawns<White,HPopCnt>(PawnEntry,PEI);
	eval_pawns<Black,HPopCnt>(PawnEntry,PEI);

	if (PawnAll) PEI.score += Compose(0, PEI.kdist_b - PEI.kdist_w);
	uint64 wp = 0, bp = 0;
	for (int i = 1; i <= 6; i++) {
		wp |= ((Pawn(White) >> (i << 3)) & 0xff);
		bp |= ((Pawn(Black) >> (i << 3)) & 0xff);
	}
	PawnEntry->draw[White] = OpposingPawnsMult[popcount<HPopCnt>(wp & (~bp))] * PawnCountMult[popcount<HPopCnt>(wp)];
	PawnEntry->draw[Black] = OpposingPawnsMult[popcount<HPopCnt>(bp & (~wp))] * PawnCountMult[popcount<HPopCnt>(bp)];
	if (T(SArea[lsb(King(White))] & Pawn(Black) & (~PEI.patt_b))) PEI.score += Compose(0, 5);
	if (T(SArea[lsb(King(Black))] & Pawn(White) & (~PEI.patt_w))) PEI.score -= Compose(0, 5);
	if (Current->castle_flags & CanCastle_OO) PEI.score += Compose(5, 0);
	if (Current->castle_flags & CanCastle_oo) PEI.score -= Compose(5, 0);
	if (Current->castle_flags & CanCastle_OOO) PEI.score += Compose(5, 0);
	if (Current->castle_flags & CanCastle_ooo) PEI.score -= Compose(5, 0);
	PawnEntry->score = PEI.score;
}

typedef struct {
	int score, king_w, king_b, mul;
	uint32 king_att_w, king_att_b;
	uint64 occ, free_w, free_b, area_w, area_b;
	GPawnEntry * PawnEntry;
	GMaterial * material;
} GEvalInfo;

template <bool me, bool HPopCnt> __forceinline void eval_queens(GEvalInfo &EI) {
	uint64 u, b;
	for (u = Queen(me); T(u); u ^= b) {
		uint64 sq = lsb(u);
		b = Bit(sq);
		uint64 att = Attacks(sq);
		Current->att[me] |= att;
		if (uint64 v = Between[CVarEI(king,opp)][sq] & EI.occ)
			if (Single(v)) {
				Current->xray[me] |= v;
				if (v & BMask[sq]) IncV(EI.score,QxrayD[me][Square(lsb(v))]);
				else IncV(EI.score,QxrayO[me][Square(lsb(v))]);
			}
		if (att & CVarEI(area,opp)) {
			CVarEI(king_att,me) += KingQAttack;
			for (uint64 v = att & CVarEI(area,opp); T(v); Cut(v))
				if (FullLine[sq][lsb(v)] & Attacks(sq) & ((Rook(me) & RMask[sq]) | (Bishop(me) & BMask[sq]))) CVarEI(king_att,me)++;
		}
		if (att & CVarEI(area,me)) IncV(EI.score,Compose(5, 2));
		if (att & Piece(opp) & CVarEI(free,me)) IncV(EI.score,Compose(4, 4));
		IncV(EI.score,popcount<HPopCnt>(att & CVarEI(free,me)) * C(QueenMobility));
		if (b & Line(me,6))
			if (T((King(opp) | Pawn(opp)) & (Line(me,6) | Line(me,7)))) {
				IncV(EI.score,C(QueenSeventhRank));
				if (T(att & Rook(me) & Line(me,6)) && T(King(opp) & Line(me,7))) IncV(EI.score,C(QueenSeventhRankDoubled));
			}
	}
}
template <bool me, bool HPopCnt> __forceinline void eval_rooks(GEvalInfo &EI) {
	uint64 u, b;
	for (u = Rook(me); T(u); u ^= b) {
		uint64 sq = lsb(u);
		b = Bit(sq);
		uint64 att = Attacks(sq);
		Current->att[me] |= att;
		if (RMask[sq] & King(opp))
		    if (uint64 v = Between[CVarEI(king,opp)][sq] & EI.occ)
			    if (Single(v)) {
					Current->xray[me] |= v;
					IncV(EI.score,Rxray[me][Square(lsb(v))]);
				}
		IncV(EI.score,popcount<HPopCnt>(att & (~(Current->patt[opp] | Pawn(me)))) * C(RookMobility));
		if (att & CVarEI(area,opp)) {
			CVarEI(king_att,me) += KingRAttack;
			for (uint64 v = att & CVarEI(area,opp); T(v); Cut(v))
				if (FullLine[sq][lsb(v)] & Attacks(sq) & Heavy(me)) CVarEI(king_att,me)++;
		}
		if (att & CVarEI(area,me)) IncV(EI.score,Compose(3, 1));
		if (att & Pawn(opp) & CVarEI(free,me)) IncV(EI.score,Compose(2, 3));
		if (att & Light(opp) & CVarEI(free,me)) IncV(EI.score,Compose(4, 5));
		Current->threat |= att & Queen(opp);
		if (F(Pawn(me) & PWay[me][sq])) {
			IncV(EI.score,C(RookHOF));
			if (F(Pawn(opp) & PWay[me][sq])) {
				uint64 v = Current->patt[opp] & Light(opp) & PWay[me][sq];
				if (F(v)) IncV(EI.score,C(RookOF));
				else {
					int rank = NB(me, v);
					if (PIsolated[File(rank)] & Forward[opp][Rank(rank)] & Pawn(me)) IncV(EI.score,C(RookOFMinorAtt));
					else IncV(EI.score,C(RookOFMinorFixed));
				}
			} else {
				int rank = NB(me, Pawn(opp) & PWay[me][sq]);
				if (F(PIsolated[File(rank)] & Forward[me][Rank(rank)] & Pawn(opp))) IncV(EI.score,C(RookHOFPawnAtt));
			}
			if (King(opp) & PWay[me][sq]) IncV(EI.score,C(RookHOFKingAtt));
		}
		if (T(b & Outpost[me] & Current->patt[me]) && F(Pawn(opp) & Forward[me][Rank(sq)] & PIsolated[File(sq)])) {
			IncV(EI.score,Compose(1, 2));
			if (att & (SArea[CVarEI(king,opp)] | (CVarEI(free,me) & Piece(opp))) & Line[Rank(sq)]) IncV(EI.score,Compose(3, 4));
		}
		if (b & (Line(me, 5) | Line(me, 6) | Line(me, 7))) {
		    if (b & Line(me,6)) {
			    if (T((King(opp) | Pawn(opp)) & (Line(me,6) | Line(me,7)))) {
				    IncV(EI.score,C(RookSeventhRank));
				    if (T(att & Heavy(me) & Line(me,6)) && T(King(opp) & Line(me,7))) IncV(EI.score,C(RookSeventhRankDoubled));
			    }
			} else if (b & Line(me,7)) {
				if (King(opp) & Line(me, 7)) IncV(EI.score,C(RookEighthRank));
			} else if (T(b & Line(me,5)) && T((King(opp) | Pawn(opp)) & (Line(me,6) | Line(me,7) | Line(me,5)))) IncV(EI.score,C(RookSixthRank));
		}
	}
}
template <bool me, bool HPopCnt> __forceinline void eval_knights(GEvalInfo &EI) {
	uint64 u, b;
	for (u = Knight(me); T(u); u ^= b) {
		uint64 sq = lsb(u);
		b = Bit(sq);
		uint64 att = NAtt[sq];
		Current->att[me] |= att;
		if (att & CVarEI(area,opp)) CVarEI(king_att,me) += KingNAttack;
		IncV(EI.score,popcount<HPopCnt>(att & CVarEI(free,me) & Forward[me][Rank(sq)]) * C(KnightMobility));
		if (att & CVarEI(area,me)) IncV(EI.score,Compose(4, 2));
		if (att & Pawn(opp) & CVarEI(free,me)) IncV(EI.score,Compose(3, 4));
		if (att & Bishop(opp) & CVarEI(free,me)) IncV(EI.score,Compose(5, 5));
		Current->threat |= att & Heavy(opp);
		if (T(b & Outpost[me]) && F(Pawn(opp) & Forward[me][Rank(sq)] & PIsolated[File(sq)])) {
			IncV(EI.score,C(KnightOutpost));
			if (Current->patt[me] & b) {
				IncV(EI.score,C(KnightOutpostProtected));
				if (att & (CVarEI(area,opp) | (CVarEI(free,me) & Piece(opp)))) {
					IncV(EI.score,Compose(5, 5));
					if (b & Line(me,4)) IncV(EI.score,Compose(2, 2));
					if (b & (File[3] | File[4])) IncV(EI.score,Compose(3, 3));
				}
			}
		}
	}
}
template <bool me, bool HPopCnt> __forceinline void eval_bishops(GEvalInfo &EI) {
	uint64 u, b;
	for (u = Bishop(me); T(u); u ^= b) {
		uint64 sq = lsb(u);
		b = Bit(sq);
		uint64 att = Attacks(sq);
		Current->att[me] |= att;
		if (BMask[sq] & King(opp))
		    if (uint64 v = Between[CVarEI(king,opp)][sq] & EI.occ)
			    if (Single(v)) {
					Current->xray[me] |= v;
					IncV(EI.score,Bxray[me][Square(lsb(v))]);
				}
		if (att & CVarEI(area,opp)) CVarEI(king_att,me) += KingBAttack;
		IncV(EI.score,popcount<HPopCnt>(att & CVarEI(free,me) & Forward[me][Rank(sq)]) * C(BishopMobility));
		if (att & CVarEI(area,me)) IncV(EI.score,Compose(2, 1));
		if (att & Pawn(opp) & CVarEI(free,me)) IncV(EI.score,Compose(3, 4));
		if (att & Knight(opp) & CVarEI(free,me)) IncV(EI.score,Compose(5, 5));
		Current->threat |= att & Heavy(opp);
		if (b & LightArea) {
			DecV(EI.score,(EI.PawnEntry->light[me] + EI.PawnEntry->light[opp]/2) * Compose(1, 1));
			IncV(EI.score,popcount<HPopCnt>(Pawn(opp) & LightArea & CVarEI(free,me) & Forward[me][Rank(sq)]) * Compose(0, 2));
		} else {
			DecV(EI.score,(EI.PawnEntry->dark[me] + EI.PawnEntry->dark[opp]/2) * Compose(1, 1));
			IncV(EI.score,popcount<HPopCnt>(Pawn(opp) & DarkArea & CVarEI(free,me) & Forward[me][Rank(sq)]) * Compose(0, 2));
		}
		if (T(b & Outpost[me]) && F(Pawn(opp) & Forward[me][Rank(sq)] & PIsolated[File(sq)]) && T(Current->patt[me] & b)) {
			IncV(EI.score,C(BishopOutpost));
			if (att & (CVarEI(area,opp) | (CVarEI(free,me) & Piece(opp)))) IncV(EI.score,Compose(3, 4));
		}
	}
}
template <bool me, bool HPopCnt> __forceinline void eval_king(GEvalInfo &EI) {
	Current->king_att[me] = CVarEI(king_att,me) & 0xFFFF;
	int score = (CVarEI(king_att,me) >> 16);
	if (Current->king_att[me] >= 2 && T(Queen(me)) && T(Current->att[me] & CVarEI(area,opp) & (~Current->att[opp]))) 
		score += popcount<HPopCnt>(Current->att[me] & CVarEI(area,opp) & (~Current->att[opp])) << 5;
	int adjusted = ((score * KingAttackScale[CVarEI(king_att,me) & 0xFFFF]) >> 3) + EI.PawnEntry->shelter[opp];
	if (F(Queen(me))) adjusted = (adjusted * popcount<HPopCnt>(Rook(me) | Light(me)))/8;
	IncV(EI.score,adjusted);
}
template <bool me, bool HPopCnt> __forceinline void eval_passer(GEvalInfo &EI) {
	for (uint64 u = EI.PawnEntry->passer[me]; T(u); Cut(u)) {
		int file = lsb(u);
		uint64 sq = NB(opp, File[file] & Pawn(me));
		int rank = CRank(me,sq);
		Current->passer |= Bit(sq);
		if (rank <= 2) continue;
		uint64 way = PWay[me][sq];
		int connected = 0, supported = 0, hooked = 0, square;
		if (PWay[opp][sq] & Heavy(me)) {
			square = NB(opp,PWay[opp][sq] & Heavy(me));
			if (Attacks(square) & Bit(sq)) supported = 1;
		}
		if (PWay[opp][sq] & Heavy(opp)) {
			square = NB(opp,PWay[opp][sq] & Heavy(opp));
			if (Attacks(square) & Bit(sq)) hooked = 1;
		}
		for (uint64 v = SArea[sq] & (~File[file]) & Pawn(me); T(v); Cut(v)) {
			square = lsb(v);
			if (F(Pawn(opp) & (File[File(square)] | PIsolated[File(square)]) & Forward[me][Rank(square)])) connected++;
		}
		if (F(Light(me) | Queen(me))) {
			if (Rook(me) & way) {
				if (rank == 6) DecV(EI.score,Compose(100, 100));
				else if (rank == 7) DecV(EI.score,Compose(25, 25));
			}
			if (T(way & King(me)) && T(File[file] & Rook(opp))) DecV(EI.score,Compose(0, 1 << (rank - 1))); 
		}
		if (F(hooked) || T(connected)) {
		    if (F(Square(sq + Push(me)))) IncV(EI.score,PassedPawnCanMove[rank]);
		    if (F(Piece(me) & way)) IncV(EI.score,PassedPawnMeClear[rank]);
		    if (F(Piece(opp) & way)) {
			    IncV(EI.score,PassedPawnOppClear[rank]);
		        if (F(way & Current->att[opp] & (~Current->att[me])) || T(supported) || connected >= 2) IncV(EI.score,PassedPawnIsFree[rank]);
		    }
		}
		if (F(Light(me) | Rook(me))) {
			if (rank == 6 && T(Queen(me) & way)) DecV(EI.score,Compose(10, 10));
			if (T(Queen(me)) && F(Light(opp) | Rook(opp))) IncV(EI.score,RankQueenEnd[rank]);
		}
	}
}
template <bool me, bool HPopCnt> __forceinline void eval_pieces(GEvalInfo &EI) {
	Current->threat |= Current->att[opp] & (~Current->att[me]) & Piece(me);
	if (Current->threat & Piece(me)) {
		DecV(EI.score,Compose(5, 5));
		uint64 u = Current->threat & Piece(me);
        u &= u - 1;
		if (u) {
			DecV(EI.score,Compose(5, 5) + Compose(15, 25));
			for (u = u & (u - 1); T(u); Cut(u)) DecV(EI.score,Compose(5, 5));
		}
	}
	if (File[File(CVarEI(king,opp))] & Heavy(me)) {
		IncV(EI.score,Compose(0, 5));
		if (F(PawnAll & File[File(CVarEI(king,opp))])) IncV(EI.score,Compose(5, 0));
	}
}
template <bool me, bool HPopCnt> void eval_endgame(GEvalInfo &EI) {
	if (EI.material->flags & CVar(FlagSingleBishop,me)) {
		if (F(Pawn(me) & (~(File[0] | File[7]))) && F(Knight(me) | Heavy(me))) {
			// 1) wrong bishop
			if ((F(Pawn(me) & File[7]) && F(Board->bb[WhiteLight + (3 * me)]) && T(King(opp) & (File[0] | File[1]) & (Line(me,6) | Line(me,7))))
				|| (F(Pawn(me) & File[0]) && F(Board->bb[WhiteDark - me]) && T(King(opp) & (File[6] | File[7]) & (Line(me,6) | Line(me,7))))) {
				Current->score = ((Current->score * (1 - (2 * me))) >> 1) * (1 - (2 * me));
				EI.mul = Min(EI.mul, 1);
				if (F(Pawn(me))) EI.mul = 0;
				else {
					uint64 sq = NB(me,Pawn(me));
					if (F(Pawn(opp) & PSupport[opp][sq]) || (Single(Pawn(me)) && Single(Pawn(opp)))) EI.mul = 0;
				}
			}
			// 2) bishop & blocked pawn
			if (T(Pawn(me) & Line(me,5) & Shift(opp,Pawn(Black)))) {
			    if (F(Pawn(me) & File[7]) && T(King(opp) & (File[0] | File[1] | File[2]) & (Line(me,6) | Line(me,7)))) EI.mul = Min(EI.mul, 1);
			    if (F(Pawn(me) & File[0]) && T(King(opp) & (File[5] | File[6] | File[7]) & (Line(me,6) | Line(me,7)))) EI.mul = Min(EI.mul, 1);
			}
		}
		if (F(Bishop(me)) && T(Pawn(me)) && Single(Pawn(me))) {
			EI.mul = Min(EI.mul, kpkx<me>());
			if (Piece(opp) == King(opp) && EI.mul == 15) Current->score += (Endgame(PawnValue) << 2) * (1 - (2 * me));
		}
	}
	if (F(Heavy(me))) {
		if (T(Bishop(me)) && F(Knight(me)) && Single(Bishop(me)) && T(Pawn(me))) {
			int number = popcount<HPopCnt>(Pawn(me));
			if (number == 1) {
				if (Bishop(opp)) EI.mul = Min(EI.mul, kbpkbx<me>());
				else if (Knight(opp)) EI.mul = Min(EI.mul, kbpknx<me>());
			} else if (number == 2 && T(Bishop(opp))) EI.mul = Min(EI.mul, kbppkbx<me>()); 
		}
	} else if (F(Light(me))) {
		if (F(Pawn(me)) && F(Rook(me)) && T(Queen(me)) && F(NonPawnKing(opp)) && T(Pawn(opp)) && Single(Pawn(opp))) EI.mul = Min(EI.mul, kqkp<me>());
		else if (F(Queen(me)) && T(Rook(me)) && Single(Rook(me))) {
			int number = popcount<HPopCnt>(Pawn(me));
			if (number <= 3) {
				if (number == 0) {
					if (Pawn(opp)) EI.mul = Min(EI.mul, krkpx<me>());
				} else if (Rook(opp)) {
					if (number == 1) EI.mul = Min(EI.mul, krpkrx<me>());
					   else {
						if (number == 2) EI.mul = Min(EI.mul, krppkrx<me>());
						if (Pawn(opp)) {
						    if (number == 2) EI.mul = Min(EI.mul, krppkrpx<me>());
						    else if (Multiple(Pawn(opp))) EI.mul = Min(EI.mul, krpppkrppx<me>()); 
						}
					}
				}
			}
		}
	}
	if (F(NonPawnKing(opp)) && Current->turn == opp && F(Current->att[me] & King(opp)) && F(CVarEI(area,opp) & (~Current->att[me])) 
		&& F(Current->patt[opp] & Piece(me)) && F(Shift(opp,Pawn(opp)) & (~EI.occ))) EI.mul = 0; 
}
template <bool HPopCnt> void eval_unusual_material(GEvalInfo &EI) {
	int wp, bp, wlight, blight, wr, br, wq, bq;
	wp = popcount<HPopCnt>(Pawn(White));
	bp = popcount<HPopCnt>(Pawn(Black));
	wlight = popcount<HPopCnt>(Light(White));
	blight = popcount<HPopCnt>(Light(Black));
	wr = popcount<HPopCnt>(Rook(White));
	br = popcount<HPopCnt>(Rook(Black));
	wq = popcount<HPopCnt>(Queen(White));
	bq = popcount<HPopCnt>(Queen(Black));
	int phase = Min(24, (wlight + blight) + 2 * (wr + br) + 4 * (wq + bq));
	int mat_score = PawnValue * (wp - bp) + KnightValue * (wlight - blight) + RookValue * (wr - br) + QueenValue * (wq - bq);
	Current->score = (((Opening(mat_score + EI.score) * phase) + (Endgame(mat_score + EI.score) * (24 - phase)))/24);
	if (Current->turn) Current->score = -Current->score;
	UpdateDelta
}

template <bool HPopCnt> void evaluation() {
	GEvalInfo EI;
	
#ifndef DEBUG
	if (Current->eval_key == Current->key) return;
#endif
	Current->eval_key = Current->key;

	EI.king_w = lsb(King(White));
	EI.king_b = lsb(King(Black));
	EI.occ = PieceAll;
	Current->patt[White] = ShiftW(White,Pawn(White)) | ShiftE(White,Pawn(White));
	Current->patt[Black] = ShiftW(Black,Pawn(Black)) | ShiftE(Black,Pawn(Black));
	EI.area_w = SArea[EI.king_w];
	EI.area_b = SArea[EI.king_b];
	Current->att[White] = Current->patt[White];
	Current->att[Black] = Current->patt[Black];
	Current->passer = 0;
	Current->threat = (Current->patt[White] & NonPawn(Black)) | (Current->patt[Black] & NonPawn(White));
	EI.score = Current->pst;

#define me White
	Current->xray[me] = 0;
	DecV(EI.score,popcount<HPopCnt>(Shift(opp,EI.occ) & Pawn(me)) * C(PawnBlocked));
	if (Current->patt[me] & CVarEI(area,opp)) CVarEI(king_att,me) = KingAttack;
	else CVarEI(king_att,me) = 0;
	CVarEI(free,me) = ~(Piece(me) | Current->patt[opp]);
	if (CVarEI(area,me) & Pawn(opp) & CVarEI(free,me)) IncV(EI.score,Compose(0, 5));
	eval_queens<me,HPopCnt>(EI);
	eval_rooks<me,HPopCnt>(EI);
	CVarEI(free,me) |= NonPawn(opp);
	eval_knights<me,HPopCnt>(EI);
#undef me
#define me Black
	Current->xray[me] = 0;
	DecV(EI.score,popcount<HPopCnt>(Shift(opp,EI.occ) & Pawn(me)) * C(PawnBlocked));
	if (Current->patt[me] & CVarEI(area,opp)) CVarEI(king_att,me) = KingAttack;
	else CVarEI(king_att,me) = 0;
	CVarEI(free,me) = ~(Piece(me) | Current->patt[opp]);
	if (CVarEI(area,me) & Pawn(opp) & CVarEI(free,me)) IncV(EI.score,Compose(0, 5));
	eval_queens<me,HPopCnt>(EI);
	eval_rooks<me,HPopCnt>(EI);
	CVarEI(free,me) |= NonPawn(opp);
	eval_knights<me,HPopCnt>(EI);
#undef me

	EI.PawnEntry = PawnHash + (Current->pawn_key & pawn_hash_mask);
	if (Current->pawn_key != EI.PawnEntry->key) eval_pawn_structure<HPopCnt>(EI.PawnEntry);
	EI.score += EI.PawnEntry->score;

	eval_bishops<White,HPopCnt>(EI);
	eval_bishops<Black,HPopCnt>(EI);

    eval_king<White,HPopCnt>(EI);
	eval_king<Black,HPopCnt>(EI);
	Current->att[White] |= EI.area_w;
	Current->att[Black] |= EI.area_b;

	eval_passer<White,HPopCnt>(EI);
	eval_pieces<White,HPopCnt>(EI);
	eval_passer<Black,HPopCnt>(EI);
	eval_pieces<Black,HPopCnt>(EI);

	if (Current->material & FlagUnusualMaterial) {
		eval_unusual_material<HPopCnt>(EI);
		return;
	}
	EI.material = &Material[Current->material];
	Current->score = EI.material->score + (((Opening(EI.score) * EI.material->phase) + (Endgame(EI.score) * (32 - EI.material->phase)))/32);

#ifdef TUNER
	int p_w[5], p_b[5], quad = 0, piece_mul;
	p_w[0] = popcount<HPopCnt>(Pawn(White)); p_w[1] = popcount<HPopCnt>(Knight(White)); p_w[2] = popcount<HPopCnt>(Bishop(White)); 
	p_w[3] = popcount<HPopCnt>(Rook(White)); p_w[4] = popcount<HPopCnt>(Queen(White));
	p_b[0] = popcount<HPopCnt>(Pawn(Black)); p_b[1] = popcount<HPopCnt>(Knight(Black)); p_b[2] = popcount<HPopCnt>(Bishop(Black)); 
	p_b[3] = popcount<HPopCnt>(Rook(Black)); p_b[4] = popcount<HPopCnt>(Queen(Black));
#define me White
	for (int i = 0; i < 5; i++) {
		piece_mul = Tr(MaterialOpp,5,i,0);
		if (i <= 3) for (int j = i; j < 5; j++) {
			piece_mul += Tr(MaterialMe,5,i,j - i) * (*(CVar(p,me)+j));
			if (j > i) piece_mul += Tr(MaterialOpp,5,i,j - i) * (*(CVar(p,opp)+j));
		}
		quad += piece_mul * (1 - (2 * me)) * (*(CVar(p,me)+i));
	}
#undef me
#define me Black
	for (int i = 0; i < 5; i++) {
		piece_mul = Tr(MaterialOpp,5,i,0);
		if (i <= 3) for (int j = i; j < 5; j++) {
			piece_mul += Tr(MaterialMe,5,i,j - i) * (*(CVar(p,me)+j));
			if (j > i) piece_mul += Tr(MaterialOpp,5,i,j - i) * (*(CVar(p,opp)+j));
		}
		quad += piece_mul * (1 - (2 * me)) * (*(CVar(p,me)+i));
	}
#undef me
	Current->score += quad/100;
#endif

	if (Current->ply > 50) Current->score = (Current->score * (114 - Current->ply))/64;
	if (Current->score > 0) {
		Current->score -= (Min(Current->score, 100) * EI.PawnEntry->draw[White]) >> 6;
		EI.mul = EI.material->mul_w;
		if (EI.material->flags & FlagCallEvalEndgame_w) eval_endgame<White,HPopCnt>(EI);
	} else {
		Current->score += (Min(-Current->score, 100) * EI.PawnEntry->draw[Black]) >> 6;
		EI.mul = EI.material->mul_b;
		if (EI.material->flags & FlagCallEvalEndgame_b) eval_endgame<Black,HPopCnt>(EI);
	}
	Current->score = (Current->score * EI.mul) / 15;
	if (Current->turn) Current->score = -Current->score;
	UpdateDelta
}

__forceinline void evaluate() {
	HardwarePopCnt ? evaluation<1>() : evaluation<0>();
}

template <bool me> int is_legal(int move) {
	int from, to, piece, capture;
	uint64 u, occ;

    from = From(move);
	to = To(move);
	piece = Board->square[from];
	capture = Board->square[to];
	if (piece == 0) return 0;
	if ((piece & 1) != Current->turn) return 0;
	if (capture) {
		if ((capture & 1) == (piece & 1)) return 0;
		if (capture >= WhiteKing) return 0;
	}
	occ = PieceAll;
	u = Bit(to);
	if (piece >= WhiteLight && piece < WhiteKing) {
	    if ((QMask[from] & u) == 0) return 0;
		if (Between[from][to] & occ) return 0;
	}
	if (IsEP(move)) {
		if (piece >= WhiteKnight) return 0;
		if (Current->ep_square != to) return 0;
		return 1;
	}
	if (IsCastling(move) && Board->square[from] < WhiteKing) return 0;
	if (IsPromotion(move) && Board->square[from] >= WhiteKnight) return 0;
	if (piece == IPawn(me)) {
		if (u & PMove[me][from]) {
            if (capture) return 0;
			if (T(u & Line(me,7)) && !IsPromotion(move)) return 0;
			return 1;
		} else if (to == (from + 2 * Push(me))) {
            if (capture) return 0;
			if (Square(to - Push(me))) return 0;
			if (F(u & Line(me,3))) return 0;
			return 1;
		} else if (u & PAtt[me][from]) {
            if (capture == 0) return 0;
			if (T(u & Line(me,7)) && !IsPromotion(move)) return 0;
			return 1;
		} else return 0;
	} else if (piece == IKing(me)) {
		if (me == White) {
		    if (IsCastling(move)) {
			    if (u & 0x40) {
                    if (((Current->castle_flags) & CanCastle_OO) == 0) return 0;
					if (occ & 0x60) return 0;
					if (Current->att[Black] & 0x70) return 0;
				} else {
					if (((Current->castle_flags) & CanCastle_OOO) == 0) return 0;
					if (occ & 0xE) return 0;
					if (Current->att[Black] & 0x1C) return 0;
				}
				return 1;
			}
		} else {
            if (IsCastling(move)) {
				if (u & 0x4000000000000000) {
                    if (((Current->castle_flags) & CanCastle_oo) == 0) return 0;
					if (occ & 0x6000000000000000) return 0;
					if (Current->att[White] & 0x7000000000000000) return 0;
				} else {
					if (((Current->castle_flags) & CanCastle_ooo) == 0) return 0;
					if (occ & 0x0E00000000000000) return 0;
					if (Current->att[White] & 0x1C00000000000000) return 0;
				}
				return 1;
			}
		}
        if (F(SArea[from] & u)) return 0;
	    if (Current->att[opp] & u) return 0;
		return 1;
	}
	piece = (piece >> 1) - 2;
	if (piece == 0) {
        if (u & NAtt[from]) return 1;
		else return 0;
	} else {
		if (Attacks(from) & u) return 1;
		else return 0;
	}
	return 0;
}

template <bool me> int is_check(int move) { // doesn't detected castling and ep checks
	uint64 king;
	int from, to, piece, king_sq;

	from = From(move);
	to = To(move);
	king = King(opp);
	king_sq = lsb(king);
	piece = Square(from);
	if (T(Bit(from) & Current->xray[me]) && F(FullLine[king_sq][from] & Bit(to))) return 1;
	if (piece < WhiteKnight) {
		if (PAtt[me][to] & king) return 1;
		if (T(Bit(to) & Line(me, 7)) && T(king & Line(me, 7)) && F(Between[to][king_sq] & PieceAll)) return 1;
	} else if (piece < WhiteLight) {
		if (NAtt[to] & king) return 1;
	} else if (piece < WhiteRook) {
		if (BMask[to] & king) if (F(Between[king_sq][to] & PieceAll)) return 1;
	} else if (piece < WhiteQueen) {
		if (RMask[to] & king) if (F(Between[king_sq][to] & PieceAll)) return 1;
	} else if (piece < WhiteKing) {
		if (QMask[to] & king) if (F(Between[king_sq][to] & PieceAll)) return 1;
	}
	return 0;
}

template <bool me> int is_tactical(int move) {
	int from, to, piece;
	uint64 u;

	from = From(move);
	to = To(move);
	piece = Square(from);
	if ((Current->pin[me] | Current->xray[me]) & Bit(from)) return 1;
	if (piece < WhiteKnight) {
		if (PAtt[me][to] & (Piece(opp) ^ Pawn(opp))) return 1;
	} else if (piece < WhiteLight) {
		if (NAtt[to] & Heavy(opp)) return 1;
	} else if (piece < WhiteRook) {
		for (u = (BMask[to] & Heavy(opp)); T(u); Cut(u)) {
			if (F(Between[to][lsb(u)] & PieceAll)) return 1;
		}
	} else if (piece < WhiteQueen) {
		for (u = (RMask[to] & Queen(opp)); T(u); Cut(u)) {
			if (F(Between[to][lsb(u)] & PieceAll)) return 1;
		}
	}
	return 0;
}

template <bool me> int is_fork(int move) {
	int from, to, piece;
	uint64 u, v;

	from = From(move);
	to = To(move);
	piece = Square(from);
	if ((Current->pin[me] | Current->xray[me]) & Bit(from)) {
		if (piece < WhiteKnight) {
		    if (PAtt[me][to] & (Piece(opp) ^ Pawn(opp))) return 1;
	    } else if (piece < WhiteLight) {
		    if (NAtt[to] & Heavy(opp)) return 1;
	    } else if (piece < WhiteRook) {
		    for (u = (BMask[to] & Heavy(opp)); T(u); Cut(u)) {
			    if (F(Between[to][lsb(u)] & PieceAll)) return 1;
		    }
	    } else if (piece < WhiteQueen) {
		    for (u = (RMask[to] & Queen(opp)); T(u); Cut(u)) {
			    if (F(Between[to][lsb(u)] & PieceAll)) return 1;
		    }
	    }
	} else {
		if (piece < WhiteKnight) {
		    if (u = (PAtt[me][to] & (Piece(opp) ^ Pawn(opp)))) if (Multiple(u)) return 1;
	    } else if (piece < WhiteLight) {
		    if (u = (NAtt[to] & Heavy(opp))) if (Multiple(u)) return 1;
	    } else if (piece < WhiteRook) {
			v = 0;
		    for (u = (BMask[to] & Heavy(opp)); T(u); Cut(u)) {
			    if (F(Between[to][lsb(u)] & PieceAll)) v |= Bit(lsb(u));
		    }
			if (T(v) && Multiple(v)) return 1;
	    }
	}
	return 0;
}

template <bool me> int is_defence(int move, int threat_move) {
	int from, to, piece, sq, tfrom, tto;

	if (F(threat_move)) return 0;
	from = From(move);
	tto = To(threat_move);
	if (from == tto) return 1;
	to = To(move);
	piece = Square(from);
	tfrom = From(threat_move);

	if (SEEValue[Square(tfrom)] >= SEEValue[Square(tto)]) {
		if (piece < WhiteKnight) {
			if (PAtt[me][to] & Bit(tto)) return 1;
		} else if (piece < WhiteLight) {
			if (NAtt[to] & Bit(tto)) return 1;
		} else if (piece < WhiteRook) {
			if (T(FullLine[tto][to] & BMask[tto]) && F(Attacks(from) & Bit(tto))) if (F(Between[tto][to] & (PieceAll ^ Bit(tfrom)))) return 1;
		} else if (piece < WhiteQueen) {
			if (T(FullLine[tto][to] & RMask[tto]) && F(Attacks(from) & Bit(tto))) if (F(Between[tto][to] & (PieceAll ^ Bit(tfrom)))) return 1;
		} else if (piece < WhiteKing) {
			if (T(FullLine[tto][to]) && F(Attacks(from) & Bit(tto))) if (F(Between[tto][to] & (PieceAll ^ Bit(tfrom)))) return 1;
		} else if (SArea[tto] & Bit(to)) return 1;

		if (T(FullLine[tto][from]) && F(FullLine[tto][from] & Bit(to))) 
			for (uint64 u = FullLine[tto][from] & ((BMask[tto] & (Bishop(me) | Queen(me))) | (RMask[tto] & (Rook(me) | Queen(me)))); T(u); Cut(u)) 
				if (F(Between[tto][lsb(u)] & (PieceAll ^ Bit(from))) && T(F(Between[tto][lsb(u)] & Bit(from)))) return 1;
	}

	if (T(Between[tto][tfrom] & Bit(to)) && T(see<me>(move,0))) return 1;

	return 0;
}

void hash_high(int value, int depth) {
	int i, score, min_score;
	GEntry *best, *Entry;

	min_score = 0x70000000;
	for (i = 0, best = Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Entry->key == Low32(Current->key)) {
			Entry->date = date;
			if (depth > Entry->high_depth || (depth == Entry->high_depth && value < Entry->high)) {
				if (Entry->low <= value) { 
				    Entry->high_depth = depth;
				    Entry->high = value;
#ifdef CUT_ALL
					Entry->flags &= ~FlagWeakHigh;
#endif
				} else if (Entry->low_depth < depth) {
					Entry->high_depth = depth;
				    Entry->high = value;
					Entry->low = value;
#ifdef CUT_ALL
					Entry->flags &= ~FlagWeakHigh;
#endif
				}
			}
			return;
		} else score = (Convert(Entry->date,int) << 3) + Convert(Max(Entry->high_depth, Entry->low_depth),int);
		if (score < min_score) {
			min_score = score;
			best = Entry;
		}
	}
	best->date = date;
	best->key = Low32(Current->key);
	best->high = value;
	best->high_depth = depth;
	best->low = 0;
	best->low_depth = 0;
	best->move = 0;
	best->flags = 0;
	return;
}

void hash_low(int move, int value, int depth) {
	int i, score, min_score;
	GEntry *best, *Entry;

	min_score = 0x70000000;
	move &= 0xFFFF;
	for (i = 0, best = Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Entry->key == Low32(Current->key)) {
			Entry->date = date;
			if (depth > Entry->low_depth || (depth == Entry->low_depth && value > Entry->low)) {
				if (move) Entry->move = move;
				if (Entry->high >= value) {
				    Entry->low_depth = depth;
				    Entry->low = value;
#ifdef CUT_ALL
					Entry->flags &= ~FlagWeakLow;
#endif
				} else if (Entry->high_depth < depth) {
					Entry->low_depth = depth;
				    Entry->low = value;
					Entry->high = value;
#ifdef CUT_ALL
					Entry->flags &= ~FlagWeakLow;
#endif
				}
			} else if (F(Entry->move)) Entry->move = move;
			return;
		} else score = (Convert(Entry->date,int) << 3) + Convert(Max(Entry->high_depth, Entry->low_depth),int);
		if (score < min_score) {
			min_score = score;
			best = Entry;
		}
	}
	best->date = date;
	best->key = Low32(Current->key);
	best->high = 0;
	best->high_depth = 0;
	best->low = value;
	best->low_depth = depth;
	best->move = move;
	best->flags = 0;
	return;
}

#ifdef CUT_ALL
void hash_high_weak(int value, int depth) {
	int i, score, min_score;
	GEntry *best, *Entry;

	min_score = 0x70000000;
	for (i = 0, best = Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Entry->key == Low32(Current->key)) {
			Entry->date = date;
			if (depth > Entry->high_depth || (depth == Entry->high_depth && value < Entry->high && WeakHigh(Entry))) {
				if (Entry->low <= value) { 
				    Entry->high_depth = depth;
				    Entry->high = value;
					Entry->flags |= FlagWeakHigh;
				} else if (Entry->low_depth < depth) {
					Entry->high_depth = depth;
				    Entry->high = value;
					Entry->flags |= FlagWeakHigh;
					if (WeakLow(Entry)) Entry->low = value;
				}
			}
			return;
		} else score = (Convert(Entry->date,int) << 3) + Convert(Max(Entry->high_depth, Entry->low_depth),int);
		if (score < min_score) {
			min_score = score;
			best = Entry;
		}
	}
	best->date = date;
	best->key = Low32(Current->key);
	best->high = value;
	best->high_depth = depth;
	best->low = 0;
	best->low_depth = 0;
	best->move = 0;
	best->flags = FlagWeakHigh;
	return;
}

void hash_low_weak(int move, int value, int depth) {
	int i, score, min_score;
	GEntry *best, *Entry;

	min_score = 0x70000000;
	move &= 0xFFFF;
	for (i = 0, best = Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Entry->key == Low32(Current->key)) {
			Entry->date = date;
			if (depth > Entry->low_depth || (depth == Entry->low_depth && value > Entry->low && WeakLow(Entry))) {
				if (move) Entry->move = move;
				if (Entry->high >= value) {
				    Entry->low_depth = depth;
				    Entry->low = value;
					Entry->flags |= FlagWeakLow;
				} else if (Entry->high_depth < depth) {
					Entry->low_depth = depth;
				    Entry->low = value;
					Entry->flags |= FlagWeakLow;
					if (WeakHigh(Entry)) Entry->high = value;
				}
			} else if (F(Entry->move)) Entry->move = move;
			return;
		} else score = (Convert(Entry->date,int) << 3) + Convert(Max(Entry->high_depth, Entry->low_depth),int);
		if (score < min_score) {
			min_score = score;
			best = Entry;
		}
	}
	best->date = date;
	best->key = Low32(Current->key);
	best->high = 0;
	best->high_depth = 0;
	best->low = value;
	best->low_depth = depth;
	best->move = move;
	best->flags = FlagWeakLow;
	return;
}
#endif

void hash_exact(int move, int value, int depth, int exclusion, int ex_depth, int knodes) {
	int i, score, min_score;
	GPVEntry *best;

	min_score = 0x70000000;
	for (i = 0, best = PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key)) {
			PVEntry->date = date;
			PVEntry->knodes += knodes;
			if (PVEntry->depth <= depth) {
				PVEntry->value = value;
				PVEntry->depth = depth;
				PVEntry->move = move;
				PVEntry->ply = Current->ply;
				if (ex_depth) {
					PVEntry->exclusion = exclusion;
					PVEntry->ex_depth = ex_depth;
				}
			}
			return;
		}
		score = (Convert(PVEntry->date,int) << 3) + Convert(PVEntry->depth,int);
		if (score < min_score) {
			min_score = score;
			best = PVEntry;
		}
	}
	best->key = Low32(Current->key);
	best->date = date;
	best->value = value;
	best->depth = depth;
	best->move = move;
	best->exclusion = exclusion;
	best->ex_depth = ex_depth;
	best->knodes = knodes;
	best->ply = Current->ply;
}

#ifdef HASH_STORE
void hash_store(int move, int value, int depth, int exclusion, int ex_depth, int time) {
	int i, score, min_score;
	GStoreEntry *best;

	if (F(parent)) return;
	min_score = 0x70000000;
	for (i = 0, best = StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4; i++, StoreEntry++) {
		if (StoreEntry->key == Low32(Current->key)) {
			if (StoreEntry->depth < depth) {
				StoreEntry->time = Max(time, StoreEntry->time);
				StoreEntry->value = value;
				StoreEntry->depth = depth;
				StoreEntry->move = move;
				StoreEntry->weight = popcnt(NonPawnKing(White) | NonPawnKing(Black));
				if (ex_depth) {
					StoreEntry->exclusion = exclusion;
					StoreEntry->ex_depth = ex_depth;
				}
			}
			return;
		}
		score = Convert(StoreEntry->depth,int) + (Convert(StoreEntry->weight,int) << 8);
		if (score < min_score) {
			min_score = score;
			best = StoreEntry;
		}
	}
	best->key = Low32(Current->key);
	best->value = value;
	best->depth = depth;
	best->move = move;
	best->time = time;
	best->weight = popcnt(NonPawnKing(White) | NonPawnKing(Black));
	best->exclusion = exclusion;
	best->ex_depth = ex_depth;
}
#endif

int check_hash(int beta, int depth, int * move, int * value) {
	int i;
	GEntry * Entry;
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		if (Low32(Current->key) == Entry->key) {
			Entry->date = date;
			if (Entry->high < beta && Entry->high_depth >= depth) {
				*value = Entry->high;
				return 1;
			}
			if (Entry->low >= beta && Entry->low_depth >= depth) {
				*move = Entry->move;
				*value = Entry->low;
				return 1;
			}
			break;
		}
	}
	return 0;
}

int extension(int move, int depth, int pv) {
	register int ext = 0;
#ifdef EXTENSIONS
	if (pv) {
		if (T(Current->passer & Bit(From(move))) && CRank(Current->turn, From(move)) >= 5 && depth < 16) ext = 2;
	} else {
		if (T(Current->passer & Bit(From(move))) && CRank(Current->turn, From(move)) >= 5 && depth < 16) ext = 1; 
	}
#endif
	return ext;
}

__forceinline int pick_move() {
	register int move, *p, *best;
	move = *(Current->current);
	if (F(move)) return 0;
	best = Current->current;
	for (p = Current->current + 1; T(*p); p++) {
		if ((*p) > move) {
			best = p;
			move = *p;
		}
	}
	*best = *(Current->current);
	*(Current->current) = move;
	Current->current++;
	return move & 0xFFFF;
}

template <bool me> int get_move() {
	int move, next, *p, *q;
	switch(Current->stage) {
	case s_gen_cap:
		Current->mask = Piece(opp);
		Current->start = gen_captures<me>(Current->moves);
		for (q = Current->start - 1, p = Current->moves; q >= p;) {
		    move = (*q) & 0xFFFF;
		    if (F(see<me>(move,0))) {
			    next = *p;
			    *p = *q;
			    *q = next;
			    p++;
		    } else q--;
	    }
		Current->start = p;
		Current->current = p;
		Current->stage++;
	case s_good_cap:
		if (move = pick_move()) return move;
		else Current->stage++;
	case s_killer_one:
		move = Current->killer[1];
		if (T(move) && F(Square(To(move))) && F(move & 0xE000) && is_legal<me>(move)) { 
			Current->stage++; 
			return move;
		}
		Current->stage++;
	case s_killer_two:
		move = Current->killer[2];
		if (T(move) && F(Square(To(move))) && F(move & 0xE000) && is_legal<me>(move)) { 
			Current->stage++; 
			return move;
		}
		Current->stage++;
	case s_ref_one:
		move = Current->ref[0];
		if (T(move) && F(Square(To(move))) && F(move & 0xE000) && move != Current->killer[1] && move != Current->killer[2] && is_legal<me>(move)) { 
			Current->stage++; 
			return move;
		}
		Current->stage++;
	case s_ref_two:
		move = Current->ref[1];
		if (T(move) && F(Square(To(move))) && F(move & 0xE000) && move != Current->killer[1] && move != Current->killer[2] && is_legal<me>(move)) { 
			Current->stage++; 
			return move;
		}
		Current->stage++;
	case s_gen_quiet: 
		gen_quiet_moves<me>(Current->start);
		Current->current = Current->start;
		Current->stage++;
	case s_quiet:
ls_quiet:
		if (Current->gen_flags & FlagNoQuietSort) {
			move = (*(Current->current)) & 0xFFFF;
			Current->current++;
		} else move = pick_move();
		if (move) {
			if (move != Current->killer[1] && move != Current->killer[2] && move != Current->ref[0] && move != Current->ref[1]) return move;
			else goto ls_quiet;
		} else Current->stage++;
	case s_init_bc:
		*(Current->start) = 0;
		Current->current = Current->moves;
		Current->stage++;
	case s_bad_cap:
		if (move = pick_move()) return move;
		else return 0;
	case e_gen_ev:
		Current->mask = Filled;
		gen_evasions<me>(Current->moves); 
		mark_evasions(Current->moves);
		Current->current = Current->moves;
		Current->stage++;
	case e_ev:
		if (move = pick_move()) return move;
		else return 0;
	case r_gen_cap:
		gen_captures<me>(Current->moves);
		Current->current = Current->moves; 
		Current->stage++;
	case r_cap:
		if (move = pick_move()) return move;
		else Current->stage++;
	case r_gen_checks:
		gen_checks<me>(Current->moves);
		Current->current = Current->moves; 
		Current->stage++;
	case r_checks:
		if (move = pick_move()) return move;
		else return 0;
	}
	return 0;
}

template <bool me> int see(int move, int margin) {
	int from, to, piece, capture, delta, sq, pos;
	uint64 clear, def, att, occ, b_area, r_slider_att, b_slider_att, r_slider_def, b_slider_def, r_area, u, new_att, my_bishop, opp_bishop;

	from = From(move);
	to = To(move);
	piece = SEEValue[Square(from)];
	capture = SEEValue[Square(to)];
	delta = piece - capture;
	if (delta <= -margin) return 1;
	if (piece == SEEValue[WhiteKing]) return 1;
	if (Current->xray[me] & Bit(from)) return 1;
	if (T(Current->pin[me] & Bit(from)) && piece <= SEEValue[WhiteDark]) return 1;
	if (piece > (SEEValue[WhiteKing] >> 1)) return 1;
	if (IsEP(move)) return 1;
	if (F(Current->att[opp] & Bit(to))) return 1;
	att = PAtt[me][to] & Pawn(opp);
	if (T(att) && delta + margin > SEEValue[WhitePawn]) return 0;
	clear = ~Bit(from);
	def = PAtt[opp][to] & Pawn(me) & clear;
	if (T(def) && delta + SEEValue[WhitePawn] + margin <= 0) return 1;
	att |= NAtt[to] & Knight(opp);
	if (T(att) && delta > SEEValue[WhiteDark] - margin) return 0;
	occ = PieceAll & clear;
    b_area = BishopAttacks(to,occ);
	opp_bishop = Bishop(opp);
	if (delta > SEEValue[IDark(me)] - margin) if (b_area & opp_bishop) return 0;
	my_bishop = Bishop(me);
    b_slider_att = BMask[to] & (opp_bishop | Queen(opp));
	r_slider_att = RMask[to] & Heavy(opp);
	b_slider_def = BMask[to] & (my_bishop | Queen(me)) & clear;
	r_slider_def = RMask[to] & Heavy(me) & clear;
	att |= (b_slider_att & b_area);
	def |= NAtt[to] & Knight(me) & clear;
	r_area = RookAttacks(to,occ);
	att |= (r_slider_att & r_area);
	def |= (b_slider_def & b_area);
	def |= (r_slider_def & r_area);
	att |= SArea[to] & King(opp);
	def |= SArea[to] & King(me) & clear;
	while (1) {
		if (u = (att & Pawn(opp))) {
			capture -= piece;
			piece = SEEValue[WhitePawn];
			sq = lsb(u);
			occ ^= Bit(sq);
			att ^= Bit(sq);
			for (new_att = FullLine[to][sq] & b_slider_att & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(att,pos);
					break;
				}
			}
		} else if (u = (att & Knight(opp))) {
			capture -= piece;
			piece = SEEValue[WhiteKnight];
			att ^= (~(u-1)) & u;
		} else if (u = (att & opp_bishop)) {
            capture -= piece;
			piece = SEEValue[WhiteDark];
			sq = lsb(u);
			occ ^= Bit(sq);
			att ^= Bit(sq);
			for (new_att = FullLine[to][sq] & b_slider_att & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(att,pos);
					break;
				}
			}
		} else if (u = (att & Rook(opp))) {
            capture -= piece;
			piece = SEEValue[WhiteRook];
			sq = lsb(u);
			occ ^= Bit(sq);
			att ^= Bit(sq);
			for (new_att = FullLine[to][sq] & r_slider_att & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(att,pos);
					break;
				}
			}
		} else if (u = (att & Queen(opp))) {
            capture -= piece;
			piece = SEEValue[WhiteQueen];
			sq = lsb(u);
			occ ^= Bit(sq);
			att ^= Bit(sq);
			for (new_att = FullLine[to][sq] & (r_slider_att | b_slider_att) & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(att,pos);
					break;
				}
			}
		} else if (u = (att & King(opp))) {
            capture -= piece;
			piece = SEEValue[WhiteKing];
		} else return 1;
		if (capture < -(SEEValue[WhiteKing] >> 1)) return 0;
		if (piece + capture < margin) return 0;
		if (u = (def & Pawn(me))) {
            capture += piece;
			piece = SEEValue[WhitePawn];
            sq = lsb(u);
			occ ^= Bit(sq);
			def ^= Bit(sq);
			for (new_att = FullLine[to][sq] & b_slider_def & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(def,pos);
					break;
				}
			}
		} else if (u = (def & Knight(me))) {
            capture += piece;
			piece = SEEValue[WhiteKnight];
			def ^= (~(u-1)) & u;
		} else if (u = (def & my_bishop)) {
            capture += piece;
			piece = SEEValue[WhiteDark];
            sq = lsb(u);
			occ ^= Bit(sq);
			def ^= Bit(sq);
			for (new_att = FullLine[to][sq] & b_slider_def & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(def,pos);
					break;
				}
			}
		} else if (u = (def & Rook(me))) {
            capture += piece;
			piece = SEEValue[WhiteRook];
            sq = lsb(u);
			occ ^= Bit(sq);
			def ^= Bit(sq);
			for (new_att = FullLine[to][sq] & r_slider_def & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(def,pos);
					break;
				}
			}
		} else if (u = (def & Queen(me))) {
            capture += piece;
			piece = SEEValue[WhiteQueen];
			sq = lsb(u);
			occ ^= Bit(sq);
			def ^= Bit(sq);
			for (new_att = FullLine[to][sq] & (r_slider_def | b_slider_def) & occ & (~att); T(new_att); Cut(new_att)) {
                pos = lsb(new_att);
				if (F(Between[to][pos] & occ)) {
                    Add(def,pos);
					break;
				}
			}
		} else if (u = (def & King(me))) {
            capture += piece;
			piece = SEEValue[WhiteKing];
		} else return 0;
		if (capture > (SEEValue[WhiteKing] >> 1)) return 1;
		if (capture - piece >= margin) return 1;
	}
}

template <bool me> void gen_legal_moves() {
	int i, *p, *q, killer, depth = -256, move, value = -MateValue, list[256];
	GEntry * Entry;

	killer = 0;
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; i++, Entry++) {
		if (Low32(Current->key) == Entry->key) {
			if (T(Entry->move) && Entry->low_depth > depth) {
				depth = Entry->low_depth;
				killer = Entry->move;
				value = Entry->low;
			}
			break;
		}
	}
	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key)) {
			if (PVEntry->depth > depth && T(PVEntry->move)) {
				depth = PVEntry->depth;
				killer = PVEntry->move;
				value = PVEntry->value;
			}
			break;
		}
	}
#ifdef HASH_STORE
	for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4 && T(parent); i++, StoreEntry++) {
		if (StoreEntry->key == Low32(Current->key)) {
			if (StoreEntry->depth > depth && T(StoreEntry->move)) {
				depth = StoreEntry->depth;
				killer = StoreEntry->move;
				value = StoreEntry->value;
			}
			break;
		}
	}
#endif

	if (Check(me)) Current->stage = e_gen_ev;
	else {
		Current->stage = s_gen_cap;
		Current->ref[0] = RefM(Current->move).ref[0];
	    Current->ref[1] = RefM(Current->move).ref[1];
	}
	Current->gen_flags = 0;
	p = list;
	while (move = get_move<me>()) {
		if (IsIllegal(me,move)) continue;
		if (SearchMoves) {
			for (i = 0; i < SMPointer; i++)
				if (SMoves[i] == move) goto keep_move;
			continue;
	    }
keep_move:
		*p = move;
		p++;
	}
	*p = 0;
	for (q = list; q < p; q++) {
		if (((*q) & 0xFFFF) == killer) {
			for (p = q; p > list; p--) *p = *(p - 1);
			list[0] = killer;
			break;
		}
	}
	for (q = Current->moves, p = list; T(*p); q++, p++) *q = *p;
	*q = 0;
	memset(RootList, 0, sizeof(GSortList));
	for (p = Current->moves; T(move = (*p)); p++) RootList->sort[RootList->number++].move = move;
	RootList->sort[RootList->number].move = 0;
}

template <bool me> int * gen_captures(int * list) {
	uint64 u, v;

	if (Current->ep_square)
		for (v = PAtt[opp][Current->ep_square] & Pawn(me); T(v); Cut(v)) AddMove(lsb(v),Current->ep_square,FlagEP,MVVLVA[IPawn(me)][IPawn(opp)])
	for (u = Pawn(me) & Line(me,6); T(u); Cut(u))
    	if (F(Square(lsb(u) + Push(me)))) {
			AddMove(lsb(u),lsb(u) + Push(me),FlagPQueen,MVVLVAPromotion)
			if (NAtt[lsb(King(opp))] & Bit(lsb(u) + Push(me))) AddMove(lsb(u),lsb(u) + Push(me),FlagPKnight,0)
		}
	for (v = ShiftW(opp,Current->mask) & Pawn(me) & Line(me,6); T(v); Cut(v)) {
		AddMove(lsb(v),lsb(v)+PushE(me),FlagPQueen,MVVLVAPromotionCap(Square(lsb(v)+PushE(me))))
#ifndef TUNER
		if (NAtt[lsb(King(opp))] & Bit(lsb(v) + PushE(me))) AddMove(lsb(v),lsb(v)+PushE(me),FlagPKnight,MVVLVA[IPawn(me)][Square(lsb(v)+PushE(me))])
#endif
	}
	for (v = ShiftE(opp,Current->mask) & Pawn(me) & Line(me,6); T(v); Cut(v)) {
		AddMove(lsb(v),lsb(v)+PushW(me),FlagPQueen,MVVLVAPromotionCap(Square(lsb(v)+PushW(me))))
#ifndef TUNER
		if (NAtt[lsb(King(opp))] & Bit(lsb(v) + PushW(me))) AddMove(lsb(v),lsb(v)+PushW(me),FlagPKnight,MVVLVA[IPawn(me)][Square(lsb(v)+PushW(me))])
#endif
	}
	if (F(Current->att[me] & Current->mask)) goto finish;
	for (v = ShiftW(opp,Current->mask) & Pawn(me) & (~Line(me,6)); T(v); Cut(v)) AddCaptureP(IPawn(me),lsb(v),lsb(v)+PushE(me),0)
	for (v = ShiftE(opp,Current->mask) & Pawn(me) & (~Line(me,6)); T(v); Cut(v)) AddCaptureP(IPawn(me),lsb(v),lsb(v)+PushW(me),0)
	for (v = SArea[lsb(King(me))] & Current->mask & (~Current->att[opp]); T(v); Cut(v)) AddCaptureP(IKing(me),lsb(King(me)),lsb(v),0)
	for (u = Knight(me); T(u); Cut(u))
		for (v = NAtt[lsb(u)] & Current->mask; T(v); Cut(v)) AddCaptureP(IKnight(me),lsb(u),lsb(v),0)
	for (u = Slider(me); T(u); Cut(u))
		for (v = Attacks(lsb(u)) & Current->mask; T(v); Cut(v)) AddCapture(lsb(u),lsb(v),0)
finish:
	*list = 0;
	return list;
}

template <bool me> int * gen_evasions(int * list) {
	int king, att_sq, from;
	uint64 att, esc, b, u;

	king = lsb(King(me));
	att = (NAtt[king] & Knight(opp)) | (PAtt[me][king] & Pawn(opp));
	for (u = (BMask[king] & BSlider(opp)) | (RMask[king] & RSlider(opp)); T(u); u ^= b) {
		b = Bit(lsb(u));
		if (Attacks(lsb(u)) & King(me)) att |= b;
	}
	att_sq = lsb(att);
	esc = SArea[king] & (~(Piece(me) | Current->att[opp])) & Current->mask;
	if (Square(att_sq) >= WhiteLight) esc &= ~FullLine[king][att_sq];
	Cut(att);
	if (att) {
		att_sq = lsb(att);
		if (Square(att_sq) >= WhiteLight) esc &= ~FullLine[king][att_sq];
		for (; T(esc); Cut(esc)) AddCaptureP(IKing(me),king,lsb(esc),0)
		*list = 0;
		return list;
	}
	if (Bit(att_sq) & Current->mask) {
	    if (T(Current->ep_square) && Current->ep_square == att_sq + Push(me))
		    for (u = PAtt[opp][att_sq + Push(me)] & Pawn(me); T(u); Cut(u)) AddMove(lsb(u),att_sq + Push(me),FlagEP,MVVLVA[IPawn(me)][IPawn(opp)])
	}
	for (u = PAtt[opp][att_sq] & Pawn(me); T(u); Cut(u)) {
        from = lsb(u);
		if (Bit(att_sq) & Line(me,7)) AddMove(from,att_sq,FlagPQueen,MVVLVAPromotionCap(Square(att_sq)))
		else if (Bit(att_sq) & Current->mask) AddCaptureP(IPawn(me),from,att_sq,0)
	}
	for ( ; T(esc); Cut(esc)) AddCaptureP(IKing(me),king,lsb(esc),0)
	att = Between[king][att_sq];
	for (u = Shift(opp,att) & Pawn(me); T(u); Cut(u)) {
        from = lsb(u);
		if (Bit(from) & Line(me,6)) AddMove(from,from + Push(me),FlagPQueen,MVVLVAPromotion)
		else if (F(~Current->mask)) AddMove(from,from + Push(me),0,0)
	}
	if (F(~Current->mask)) {
	    for (u = Shift(opp,Shift(opp,att)) & Line(me, 1) & Pawn(me); T(u); Cut(u))
            if (F(Square(lsb(u)+Push(me)))) AddMove(lsb(u),lsb(u) + 2 * Push(me),0,0)
    }
	att |= Bit(att_sq);
	for (u = Knight(me); T(u); Cut(u))
        for (esc = NAtt[lsb(u)] & att; T(esc); esc ^= b) {
			b = Bit(lsb(esc));
			if (b & Current->mask) AddCaptureP(IKnight(me),lsb(u),lsb(esc),0)
		}
	for (u = Slider(me); T(u); Cut(u))
        for (esc = Attacks(lsb(u)) & att; T(esc); esc ^= b) {
			b = Bit(lsb(esc));
			if (b & Current->mask) AddCapture(lsb(u),lsb(esc),0)
		}
	*list = 0;
	return list;
}

void mark_evasions(int * list) {
	for (; T(*list); list++) {
		register int move = (*list) & 0xFFFF;
	    if (F(Square(To(move))) && F(move & 0xE000)) {
			if (move == Current->killer[1]) *list |= KillerOneScore;
			else if (move == Current->killer[2]) *list |= KillerTwoScore;
			else *list |= HistoryP(Square(From(move)),From(move),To(move));
		}
	}
}

template <bool me> int * gen_quiet_moves(int * list) {
	int to;
	uint64 u, v, free, occ;

    occ = PieceAll;
	free = ~occ;
	if (me == White) {
		if (T(Current->castle_flags & CanCastle_OO) && F(occ & 0x60) && F(Current->att[Black] & 0x70)) AddHistoryP(IKing(White),4,6,FlagCastling)
	    if (T(Current->castle_flags & CanCastle_OOO) && F(occ & 0xE) && F(Current->att[Black] & 0x1C)) AddHistoryP(IKing(White),4,2,FlagCastling)
	} else {
		if (T(Current->castle_flags & CanCastle_oo) && F(occ & 0x6000000000000000) && F(Current->att[White] & 0x7000000000000000)) AddHistoryP(IKing(Black),60,62,FlagCastling)
	    if (T(Current->castle_flags & CanCastle_ooo) && F(occ & 0x0E00000000000000) && F(Current->att[White] & 0x1C00000000000000)) AddHistoryP(IKing(Black),60,58,FlagCastling)
	}
	for (v = Shift(me,Pawn(me)) & free & (~Line(me,7)); T(v); Cut(v)) {
        to = lsb(v);
	    if (T(Bit(to) & Line(me,2)) && F(Square(to + Push(me)))) AddHistoryP(IPawn(me),to - Push(me),to + Push(me),0)
		AddHistoryP(IPawn(me),to - Push(me),to,0)
	}
	for (u = Knight(me); T(u); Cut(u))
		for (v = free & NAtt[lsb(u)]; T(v); Cut(v)) AddHistoryP(IKnight(me),lsb(u),lsb(v),0)
	for (u = Slider(me); T(u); Cut(u))
		for (v = free & Attacks(lsb(u)); T(v); Cut(v)) AddHistory(lsb(u),lsb(v))
	for (v = SArea[lsb(King(me))] & free & (~Current->att[opp]); T(v); Cut(v)) AddHistoryP(IKing(me),lsb(King(me)),lsb(v),0)
	*list = 0;
	return list;
}

template <bool me> int * gen_checks(int * list) {
	int king, from;
    uint64 u, v, target, b_target, r_target, clear, xray;

	clear = ~(Piece(me) | Current->mask);
    king = lsb(King(opp));
	for (u = Current->xray[me] & Piece(me); T(u); Cut(u)) {
		from = lsb(u);
		target = clear & (~FullLine[king][from]);
		if (Square(from) == IPawn(me)) {
			if (F(Bit(from + Push(me)) & Line(me,7))) {
			    if (T(Bit(from + Push(me)) & target) && F(Square(from + Push(me)))) AddMove(from,from + Push(me),0,MVVLVAXray)
				for (v = PAtt[me][from] & target & Piece(opp); T(v); Cut(v)) AddMove(from,lsb(v),0,MVVLVAXrayCap(Square(lsb(v))))
			}
		} else {
			if (Square(from) < WhiteLight) v = NAtt[from] & target;
			else if (Square(from) < WhiteKing) v = Attacks(from) & target;
			else v = SArea[from] & target & (~Current->att[opp]);
			for ( ; T(v); Cut(v)) AddMove(from,lsb(v),0,MVVLVAXrayCap(Square(lsb(v))))
		}
	}
	xray = ~(Current->xray[me] & Board->bb[me]);
	for (u = Knight(me) & NArea[king] & xray; T(u); Cut(u))
		for (v = NAtt[king] & NAtt[lsb(u)] & clear; T(v); Cut(v)) AddCaptureP(IKnight(me),lsb(u),lsb(v),0)
    for (u = DArea[king] & Pawn(me) & (~Line(me,6)) & xray; T(u); Cut(u)) {
		from = lsb(u);
		for (v = PAtt[me][from] & PAtt[opp][king] & clear & Piece(opp); T(v); Cut(v)) AddCaptureP(IPawn(me),from,lsb(v),0)
		if (F(Square(from + Push(me))) && T(Bit(from + Push(me)) & PAtt[opp][king])) AddMove(from,from + Push(me),0,0)
	}
	b_target = BishopAttacks(king,PieceAll) & clear;
	r_target = RookAttacks(king,PieceAll) & clear;
	for (u = (Queen(me) | (Odd(king ^ Rank(king)) ? Board->bb[WhiteLight | me] : Board->bb[WhiteDark | me])) & xray; T(u); Cut(u)) 
		for (v = Attacks(lsb(u)) & b_target; T(v); Cut(v)) AddCapture(lsb(u),lsb(v),0)
	for (u = (Queen(me) | Rook(me)) & xray; T(u); Cut(u)) 
		for (v = Attacks(lsb(u)) & r_target; T(v); Cut(v)) AddCapture(lsb(u),lsb(v),0)
	*list = 0;
	return list;
}

template <bool me> int * gen_delta_moves(int * list) {
	int to;
	uint64 u, v, free, occ;

    occ = PieceAll;
	free = ~occ;
	if (me == White) {
		if (T(Current->castle_flags & CanCastle_OO) && F(occ & 0x60) && F(Current->att[Black] & 0x70)) AddCDeltaP(IKing(White),4,6,FlagCastling)
	    if (T(Current->castle_flags & CanCastle_OOO) && F(occ & 0xE) && F(Current->att[Black] & 0x1C)) AddCDeltaP(IKing(White),4,2,FlagCastling)
	} else {
		if (T(Current->castle_flags & CanCastle_oo) && F(occ & 0x6000000000000000) && F(Current->att[White] & 0x7000000000000000)) AddCDeltaP(IKing(Black),60,62,FlagCastling)
	    if (T(Current->castle_flags & CanCastle_ooo) && F(occ & 0x0E00000000000000) && F(Current->att[White] & 0x1C00000000000000)) AddCDeltaP(IKing(Black),60,58,FlagCastling)
	}
	for (v = Shift(me,Pawn(me)) & free & (~Line(me,7)); T(v); Cut(v)) {
        to = lsb(v);
	    if (T(Bit(to) & Line(me,2)) && F(Square(to + Push(me)))) AddCDeltaP(IPawn(me),to - Push(me),to + Push(me),0)
		AddCDeltaP(IPawn(me),to - Push(me),to,0)
	}
	for (u = Knight(me); T(u); Cut(u))
		for (v = free & NAtt[lsb(u)]; T(v); Cut(v)) AddCDeltaP(IKnight(me),lsb(u),lsb(v),0)
	for (u = Slider(me); T(u); Cut(u))
		for (v = free & Attacks(lsb(u)); T(v); Cut(v)) AddCDelta(lsb(u),lsb(v))
	for (v = SArea[lsb(King(me))] & free & (~Current->att[opp]); T(v); Cut(v)) AddCDeltaP(IKing(me),lsb(King(me)),lsb(v),0)
	*list = 0;
	return list;
}

template <bool me> int q_search(int alpha, int beta, int depth, int flags) {
	int i, value, score, move, hash_move, hash_depth, cnt;
	GEntry * Entry;

	if (flags & FlagHaltCheck) halt_check;
	if (flags & FlagCallEvaluation) evaluate();
	if (Check(me)) return q_evasion<me>(alpha, beta, depth, FlagHashCheck);
	score = Current->score + 3;
	if (score > alpha) {
		alpha = score;
		if (score >= beta) return score;
	}

	hash_move = hash_depth = 0;
	if (flags & FlagHashCheck) {
	    for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		    if (Low32(Current->key) == Entry->key) {
			    if (T(Entry->low_depth)) {
				    if (Entry->low >= beta) return Entry->low;
				    if (Entry->low_depth > hash_depth && T(Entry->move)) {
					    hash_move = Entry->move;
					    hash_depth = Entry->low_depth;
				    }
			    }
			    if (T(Entry->high_depth) && Entry->high <= alpha) return Entry->high;
				break;
		    }
	    }
	}

	Current->mask = Piece(opp);
#ifndef NO_CAP_PRUNING
	if (Current->score + 200 <= alpha) {
		score = Current->score + 200;
		Current->mask ^= Pawn(opp);
		if (Current->score + 500 <= alpha) {
			score = Current->score + 500;
			Current->mask ^= Light(opp);
			if (Current->score + 700 <= alpha) {
				score = Current->score + 700;
				Current->mask ^= Rook(opp);
				if (Current->score + 1400 <= alpha) {
					score = Current->score + 1400;
					Current->mask ^= Queen(opp);
				}
			}
		}
	}
#endif

	cnt = 0;
	if (T(hash_move)) {
#ifndef NO_DELTA
		if (F(Bit(To(hash_move)) & Current->mask) && F(hash_move & 0xE000) && (Current->score + DeltaM(hash_move) <= alpha || depth < -4) && F(is_check<me>(hash_move))) goto skip_hash_move;
#endif
		if (is_legal<me>(move = hash_move)) {
			if (IsIllegal(me,move)) goto skip_hash_move;
			if (SEEValue[Square(To(move))] > SEEValue[Square(From(move))]) cnt++;
			do_move<me>(move);
		    value = -q_search<opp>(-beta, -alpha, depth - 1, FlagNeatSearch);
		    undo_move<me>(move);
			if (value > score) {
			    score = value;
			    if (value > alpha) {
				    alpha = value;
			        if (value >= beta) goto cut;
			    }
		    }
			if (F(Bit(To(hash_move)) & Current->mask) && F(hash_move & 0xE000) && (depth < -2 || depth <= -1 && Current->score + 50 < alpha) && alpha >= beta - 1) return alpha;
		}
	}
skip_hash_move:
	gen_captures<me>(Current->moves);
	Current->current = Current->moves;
	while (move = pick_move()) {
		if (move == hash_move) continue;
		if (IsIllegal(me,move)) continue;
		if (F(see<me>(move,-50))) continue;
		if (SEEValue[Square(To(move))] > SEEValue[Square(From(move))]) cnt++;
		do_move<me>(move);
		value = -q_search<opp>(-beta, -alpha, depth - 1, FlagNeatSearch);
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value > alpha) {
				alpha = value;
			    if (value >= beta) goto cut;
			}
		}
	}

	if (depth < -2) goto finish;
	if (depth <= -1 && Current->score + 50 < alpha) goto finish;
	gen_checks<me>(Current->moves);
	Current->current = Current->moves;
	while (move = pick_move()) {
		if (move == hash_move) continue;
		if (IsIllegal(me,move)) continue;
		if (IsRepetition(alpha + 1,move)) continue;
		if (F(see<me>(move,-50))) continue;
		do_move<me>(move);
		value = -q_evasion<opp>(-beta, -alpha, depth - 1, FlagNeatSearch);
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value > alpha) {
				alpha = value;
			    if (value >= beta) goto cut;
			}
		}
	}

#ifndef NO_DELTA
	if (T(cnt) || Current->score + 30 < alpha || T(Current->threat & Piece(me)) || T((Current->xray[opp] | Current->pin[opp]) & NonPawn(opp)) 
		|| T(Pawn(opp) & Line(me, 1) & Shift(me,~PieceAll))) goto finish;
	Current->margin = alpha - Current->score + 6;
	gen_delta_moves<me>(Current->moves);
	Current->current = Current->moves;
	while (move = pick_move()) {
		if (move == hash_move) continue;
		if (IsIllegal(me,move)) continue;
		if (IsRepetition(alpha + 1,move)) continue;
		if (F(see<me>(move,-50))) continue;
		cnt++;
		do_move<me>(move);
		value = -q_search<opp>(-beta, -alpha, depth - 1, FlagNeatSearch);
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value > alpha) {
				alpha = value;
			    if (value >= beta) {
					if (Current->killer[1] != move) {
						Current->killer[2] = Current->killer[1];
						Current->killer[1] = move;
					}
					goto cut;
				}
			}
		}
		if (cnt >= 3) break; 
	}
#endif

finish:
	if (depth >= -2 && (depth >= 0 || Current->score + 50 >= alpha)) hash_high(score, 1);
	return score;
cut:
	hash_low(move, score, 1);
	return score;
}

template <bool me> int q_evasion(int alpha, int beta, int depth, int flags) {
	int i, value, pext, score, move, cnt, hash_move, hash_depth;
	int *p;
	GEntry * Entry;

	score = Convert((Current - Data),int) - MateValue;
	if (flags & FlagHaltCheck) halt_check;

	hash_move = hash_depth = 0;
	if (flags & FlagHashCheck) {
	    for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		    if (Low32(Current->key) == Entry->key) {
			    if (T(Entry->low_depth)) {
				    if (Entry->low >= beta) return Entry->low;
				    if (Entry->low_depth > hash_depth && T(Entry->move)) {
					    hash_move = Entry->move;
					    hash_depth = Entry->low_depth;
				    }
			    }
			    if (T(Entry->high_depth) && Entry->high <= alpha) return Entry->high;
				break;
		    }
	    }
	}

	if (flags & FlagCallEvaluation) evaluate();
	Current->mask = Filled;
#ifndef NO_CAP_PRUNING
	if (Current->score - 10 <= alpha) {
		Current->mask = Piece(opp);
		score = Current->score - 10;
	    if (Current->score + 200 <= alpha) {
		    score = Current->score + 200;
		    Current->mask ^= Pawn(opp);
		    if (Current->score + 500 <= alpha) {
			    score = Current->score + 500;
			    Current->mask ^= Light(opp);
			    if (Current->score + 700 <= alpha) {
				    score = Current->score + 700;
				    Current->mask ^= Rook(opp);
				    if (Current->score + 1400 <= alpha) {
					    score = Current->score + 1400;
					    Current->mask ^= Queen(opp);
				    }
			    }
		    }
	    }
	}
#endif

	alpha = Max(score, alpha);
	pext = 0;
	gen_evasions<me>(Current->moves);
	Current->current = Current->moves;
	if (F(Current->moves[0])) return score;
	if (F(Current->moves[1])) pext = 1;
	else {
		mark_evasions(Current->moves);
	    if (T(hash_move) && (T(Bit(To(hash_move)) & Current->mask) || T(hash_move & 0xE000))) {
	        for (p = Current->moves; T(*p); p++) {
		        if (((*p) & 0xFFFF) == hash_move) {
				    *p |= 0x7FFF0000;
				    break;
			    }
	        }
	    }
	}
	cnt = 0;
	while (move = pick_move()) {
		if (IsIllegal(me,move)) continue;
		cnt++;
		if (IsRepetition(alpha + 1,move)) {
			score = Max(0, score);
			continue;
		}
		if (F(Square(To(move))) && F(move & 0xE000)) {
#ifndef NO_EVASION_HISTORY_PRUNING
			if (cnt > 3 && F(is_check<me>(move))) continue;
#endif
#ifndef NO_DELTA
			if ((value = Current->score + DeltaM(move) + 10) <= alpha) {
				score = Max(value, score);
				continue;
			}
#endif
		}
		do_move<me>(move);
		value = -q_search<opp>(-beta, -alpha, depth - 1 + pext, FlagNeatSearch);
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value > alpha) {
				alpha = value;
			    if (value >= beta) goto cut;
			}
		}
	}
	return score;
cut:
	return score;
}

template <bool me, bool exclusion> int search(int beta, int depth, int flags) {
	int i, value, cnt, flag, hash_value = -MateValue, fork, moves_to_play, check, score, move, ext, margin, hash_move, threat_move, 
		high_depth = 0, high_value = MateValue, new_depth, move_back, hash_depth, *p, singular = 0, do_split = 0, loop, new_move, new_value, split_search;
	int height = (int)(Current - Data);
	GEntry * Entry;
	GMoveList * CML;
	GMove * CM;

#ifndef TUNER
	if (nodes >= check_node2 + 0x10) {
#ifndef W32_BUILD
		InterlockedAdd64(&SMPI->total_nodes, (long long)(nodes) - (long long)(check_node2)); 
#else
		SMPI->total_nodes += nodes - check_node2;
#endif
		check_node2 = nodes;
		check_state(1);
	}

	if (nodes > check_node + 0x4000 && T(parent)) {
		check_node = nodes;
		check_time(1);
	}
#endif

	if (depth <= 1) return q_search<me>(beta - 1, beta, 1, flags);
	if (flags & FlagHaltCheck) {
	    if (height - MateValue >= beta) return beta;
	    if (MateValue - height < beta) return beta - 1;
	    halt_check;
	}

	hash_depth = -1;
	hash_move = flags & 0xFFFF;
#ifdef CUT_ALL
	int cut = Odd(height - pv_height);
#endif
	if (exclusion) {
		cnt = 0;
		threat_move = 0;
		flag = 1;
		score = beta - 1;
		split_search = 0;
		goto skip_hash_move;
	}

	if (flags & FlagCallEvaluation) evaluate();
	if (Check(me)) return search_evasion<me, 0>(beta, depth, flags & (~(FlagHaltCheck | FlagCallEvaluation)));

	if ((value = Current->score - 90 - (depth << 3) - (Max(depth - 5, 0) << 5)) >= beta && F(Pawn(opp) & Line(me, 1)) && F(flags & FlagReturnBestMove) && depth <= 13) return value;
	if ((value = Current->score + 50) < beta && depth <= 3) return Max(value, q_search<me>(beta - 1, beta, 1, FlagHashCheck | hash_move));

	Current->best = hash_move;
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		if (Low32(Current->key) == Entry->key) {
			Entry->date = date;
			if (Entry->high_depth > high_depth) {
				high_depth = Entry->high_depth;
				high_value = Entry->high;
			}
			if (Entry->high < beta && Entry->high_depth >= depth && ReturnHigh) return Entry->high;
			if (T(Entry->move) && Entry->low_depth > hash_depth) {
				Current->best = hash_move = Entry->move;
				hash_depth = Entry->low_depth;
				if (Entry->low_depth) hash_value = Entry->low;
			}
			if (Entry->low >= beta && Entry->low_depth >= depth) {
				if (Entry->move) {
					Current->best = Entry->move;
					if (ReturnLow) {
						if (F(Square(To(Entry->move))) && F(Entry->move & 0xE000)) {
							if (Current->killer[1] != Entry->move && F(flags & FlagNoKillerUpdate)) {
								Current->killer[2] = Current->killer[1];
								Current->killer[1] = Entry->move;
							}
							UpdateRef(Entry->move);
						}
						return Entry->low;
					}
				}
				if (ReturnLow) if (F(flags & FlagReturnBestMove)) return Entry->low;
			}
			break;
		}
	}

#ifdef PV_HASHING
	if (depth >= 20) {
    	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
			if (PVEntry->key == Low32(Current->key)) {
				PVEntry->date = date;
				hash_low(PVEntry->move,PVEntry->value,PVEntry->depth);
				hash_high(PVEntry->value,PVEntry->depth);
				if (PVEntry->depth >= depth) {
					if (PVEntry->move) Current->best = PVEntry->move;
					if (F(flags & FlagReturnBestMove)) return PVEntry->value;
				}
				if (T(PVEntry->move) && PVEntry->depth > hash_depth) {
					Current->best = hash_move = PVEntry->move;
					hash_depth = PVEntry->depth;
					hash_value = PVEntry->value;
				}
				break;
			}
		}
#ifdef HASH_STORE
		for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4; i++, StoreEntry++) {
			if (StoreEntry->key == Low32(Current->key)) {
				hash_low(StoreEntry->move,StoreEntry->value,StoreEntry->depth);
				hash_high(StoreEntry->value,StoreEntry->depth);
				if (StoreEntry->depth >= depth) {
					if (StoreEntry->move) Current->best = StoreEntry->move;
					if (F(flags & FlagReturnBestMove)) return StoreEntry->value;
				}
				if (T(StoreEntry->move) && StoreEntry->depth > hash_depth) {
					Current->best = hash_move = StoreEntry->move;
					hash_depth = StoreEntry->depth;
					hash_value = StoreEntry->value;
				}
				break;
			}
		}
#endif
	}
#endif
	threat_move = 0;
	if (depth < 10) score = height - MateValue;
	else score = beta - 1;
#ifdef NPV_IID
	if (depth >= 12 && (F(hash_move) || hash_value < beta || hash_depth < depth - 12) && (high_value >= beta || high_depth < depth - 12) && F(flags & FlagDisableNull)) {
		new_depth = depth - 8;
		value = search<me, 0>(beta, new_depth, FlagHashCheck | FlagNoKillerUpdate | FlagDisableNull | FlagReturnBestMove | hash_move);
		if (value >= beta) {
			if (Current->best) hash_move = Current->best;
			hash_depth = new_depth;
			hash_value = beta;
		}
	}
#endif
#ifdef NULL_MOVE
	if (depth >= 4 && Current->score + 3 >= beta && F(flags & FlagDisableNull) && (F(Pawn(opp) & Line(me, 1) & Shift(me,~PieceAll)) || depth >= 10) 
		&& (high_value >= beta || high_depth < depth - 10) && (depth < 12 || (hash_value >= beta && hash_depth >= depth - 12)) && beta > -EvalValue && T(NonPawnKing(me))) {
		new_depth = depth - 8;
		do_null();
	    value = -search<opp, 0>(1 - beta, new_depth, FlagHashCheck);
		undo_null();
		if (value >= beta) {
			if (depth < 12) HashLow(0, value, depth);
			return value;
		} else threat_move = (Current + 1)->best;
	}
#endif

	cnt = 0;
	flag = 0;
	split_search = 0;
	if (T(hash_move) && is_legal<me>(move = hash_move)) {
		if (IsIllegal(me,move)) goto skip_hash_move;
		cnt++;
		check = is_check<me>(move);
#ifdef CHECK_EXT_NPV
		if (check) ext = CheckNPVExt(depth);
		else
#endif
	    ext = extension(move, depth, 0);
		if (depth >= 16 && ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2)) {
			new_depth = depth - Min(12, depth/2);
			value = -MateValue;
			if (hash_value >= beta && hash_depth >= new_depth) {
				margin = beta - ExclSingle(depth);
				if (ext < 1 + (Ext(flags) < 1)) {
					value = search<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) {
						singular = 1;
						ext = 1 + (Ext(flags) < 1);
					}
				}
				if (value < margin && ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2)) {
					margin = beta - ExclDouble(depth);
			    	value = search<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) {
						singular = 2;
						ext = 2 + (Ext(flags) < 1) - (Ext(flags) >= 2);
					}
				}
			}
		} 
		if (depth < 16 && To(move) == To(Current->move) && T(Square(To(move)))) ext = Max(ext, 2);
		new_depth = depth - 2 + ext;
		do_move<me>(move);
		value = -search<opp, 0>(1 - beta, new_depth, FlagNeatSearch | ((hash_value >= beta && hash_depth >= depth - 12) ? FlagDisableNull : 0) | ExtFlag(ext));
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value >= beta) goto cut;
		}
	}
skip_hash_move:
	Current->stage = s_gen_cap;
	Current->gen_flags = 0;
	Current->ref[0] = RefM(Current->move).ref[0];
	Current->ref[1] = RefM(Current->move).ref[1];
	move_back = 0;
#ifdef REPETITION
	if (beta > 0 && Current->ply >= 2) {
		if (F((Current - 1)->move & 0xF000)) {
			move_back = (To((Current - 1)->move) << 6) | From((Current - 1)->move);
			if (Square(To(move_back))) move_back = 0;
		}
	}
#endif
	moves_to_play = 3 + (depth * depth)/6;
	margin = Current->score + 70 + (depth << 3) + (Max(depth - 7, 0) << 5);
	if ((value = margin) < beta && depth <= 19) {
		flag = 1;
		score = Max(value, score);
		Current->stage = r_gen_cap;
		Current->mask = Piece(opp);
#ifndef NO_CAP_PRUNING
		if ((value = Current->score + 200 + (depth << 5)) < beta) {
			score = Max(value, score);
			Current->mask ^= Pawn(opp);
		}
#endif
	}
#ifndef LOCAL_TUNER
	if (depth >= SplitDepth && F(exclusion) && PrN > 1) 
#ifndef CHILD_PROCESS_SPLIT
		if (Id == 0)
#endif
		do_split = 1;
#endif
	if (do_split) {
	    CML = &SMPI->Info[Id].MoveList[height];
		CML->active = 0;
	    init_move_list(CML);
		CML->pv = 0;
		CML->alpha = beta - 1;
		CML->beta = beta;
		CML->depth = depth;
        CML->singular = singular;
#ifdef CUT_ALL
		CML->cut = cut;
#endif
	}
	while (move = get_move<me>()) {
		if (move == hash_move) continue;
		if (IsIllegal(me,move)) continue;
		cnt++;
		if (move == move_back) {
			score = Max(0, score);
			continue;
		}
		if (Current->stage == r_checks) check = 1;
		else check = is_check<me>(move);
#ifdef CHECK_EXT_NPV
		if (T(check) && T(see<me>(move,0))) ext = CheckNPVExt(depth);
		else
#endif      
		ext = extension(move, depth, 0);
		new_depth = depth - 2 + ext;
		if (F(Square(To(move))) && F(move & 0xE000)) {
			if (Current->stage > s_ref_one && Current->stage <= s_quiet) {
				if (F(check)) {
#ifndef NO_HISTORY_PRUNING
			        if (cnt > moves_to_play && F(is_defence<me>(move, threat_move))) {
				        Current->gen_flags |= FlagNoQuietSort;
				        continue;
			        }
#endif
		        }
#ifndef CUT_ALL
				if (depth >= 6) {
					int reduction = msb(cnt);
					if (move == Current->ref[0] || move == Current->ref[1]) reduction = Max(0, reduction - 1);
					if (new_depth - reduction > 3)
						if (F(see<me>(move, -50))) reduction += 2;
					if (T(reduction) && reduction < 2 && new_depth - reduction > 3) {
						if (cnt > 3) reduction = 2;
						else reduction = 0;
					}
					new_depth = Max(3, new_depth - reduction);
				}
#else
			    if (depth >= 6 && cnt > (3 * all)) {
					new_depth = Max(3, new_depth - msb(cnt));
					if (cut) new_depth = Max(3, new_depth - 2);
				}
#endif
		    }
			if (F(check)) {
#ifndef NO_DELTA
			    if ((value = Current->score + DeltaM(move) + 10) < beta && depth <= 3) {
				    score = Max(value, score);
				    continue;
			    }
				if (cnt > 7 && (value = margin + DeltaM(move) - 25 * msb(cnt)) < beta && depth <= 19) {
					score = Max(value, score);
					continue;
				}
#endif
			}
			if (depth <= 9 && T(NonPawnKing(me)) && F(see<me>(move, -50))) continue;
		} else {
			if (Current->stage == r_cap && F(check) && depth <= 9 && F(see<me>(move, -50))) continue;
			else if (Current->stage == s_bad_cap && depth <= 5 && F(check)) continue;
		}
		if (T(do_split) && cnt > 1) {
			CM = &CML->move[CML->move_number++];
			CM->move = move;
			CM->reduced_depth = new_depth;
			CM->research_depth = depth - 2 + ext;
			CM->ext = ext;
			CM->stage = Current->stage;
			CM->flags = 0;
			continue;
		}
		do_move<me>(move);
		value = -search<opp, 0>(1 - beta, new_depth, FlagNeatSearch | ExtFlag(ext));
		if (value >= beta && new_depth < depth - 2 + ext) value = -search<opp, 0>(1 - beta, depth - 2 + ext, FlagNeatSearch | FlagDisableNull | ExtFlag(ext));
undo:
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value >= beta) goto cut;
		}
	}
	if (F(cnt) && F(flag)) {
		hash_high(0, 127);
		hash_low(0, 0, 127);
		return 0;
	}
	if (do_split) {
		split_search = 1;
		loop = 0;
		LOCK(CML->lock);
		CML->active = 1;
		ActivateSP(Id,height);
		CML->move[CML->move_number].move = 0;
		CM = &CML->move[0];
		send_position(CML->position);
		if (setjmp(CML->jump)) {
			score = beta;
			move = CML->best_move;
			retrieve_position(CML->position, height);
			halt_all(height, 127);
			goto cut;
		}
new_loop:
		for (i = 0; i < CML->move_number; i++) {
			CM = &CML->move[i];
			if (loop == 0) CML->current_master_position = i;
			move = CM->move;
			if (CM->flags & FlagFinished) {
				if (CM->value >= beta) goto cut_achieved;
				continue;
			}
			if (loop == 0) {
			    if (CM->flags & FlagClaimed) continue;
				CM->flags |= FlagClaimed;
			    CM->id = Id;
			}
			if (loop == 1) {
#ifdef WAIT_FOR_CHILD_PROCESSES
				UNLOCK(CML->lock);
				while (F(CM->flags & FlagFinished)) _mm_pause();
				LOCK(CML->lock);
				if (CM->value >= beta) goto cut_achieved;
				continue;
#endif
				SET_BIT(SMPI->Info[CM->id].flags, STOP_ORDER);
				CM->id = Id;
			}
			new_depth = CM->reduced_depth;
			ext = CM->ext;
			UNLOCK(CML->lock);
			for (int id = 0; id < PrN; id++) if (id != Id) SET_BIT(SMPI->Info[id].flags,SPLIT_SIGNAL); 

			if (check_hash(beta, depth, &new_move, &new_value)) {
				halt_all(CML, 0);
				return new_value;
			}

			do_move<me>(move);
			value = -search<opp, 0>(1 - beta, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value >= beta && new_depth < depth - 2 + ext) value = -search<opp, 0>(1 - beta, depth - 2 + ext, FlagNeatSearch | FlagDisableNull | ExtFlag(ext));
			undo_move<me>(move);

			LOCK(CML->lock);
			CM->value = value;
			CM->flags |= FlagFinished;
			if (value >= beta) {
cut_achieved:
				score = CM->value;
				halt_all(CML, 1);
				UNLOCK(CML->lock);
				goto cut;
			}
		}
		if (loop == 0) {
			loop = 1;
			goto new_loop;
		}
		halt_all(CML, 1);
		UNLOCK(CML->lock);
	}
fail_low:
	if (F(exclusion)) HashHigh(score, depth);
	return score;
cut:
	if (exclusion) return score;
	Current->best = move;
	if (depth >= 10) score = Min(beta, score);
	HashLow(move, score, depth);
	if (F(Square(To(move))) && F(move & 0xE000)) {
		if (Current->killer[1] != move && F(flags & FlagNoKillerUpdate)) {
			Current->killer[2] = Current->killer[1];
			Current->killer[1] = move;
		}
		HistoryGood(move);
		if (F(do_split)) {
			if (move != hash_move && Current->stage == s_quiet) for (p = Current->start; p < (Current->current - 1); p++) HistoryBad(*p);
		} else if (split_search) {
			for (i = 0; i < CML->move_number; i++) {
				CM = &CML->move[i];
				if (T(CM->flags & FlagFinished) && CM->stage == s_quiet && move != CM->move) HistoryBad(CM->move);
			}
		}
		UpdateRef(move);
	}
	return score;
}

template <bool me, bool exclusion> int search_evasion(int beta, int depth, int flags) {
	int i, value, score, pext, move, cnt, hash_value = -MateValue, hash_depth, hash_move, margin, new_depth, ext, check, moves_to_play;
	int height = (int)(Current - Data);
	GEntry * Entry;

	if (depth <= 1) return q_evasion<me>(beta - 1, beta, 1, flags);
	score = height - MateValue;
	if (flags & FlagHaltCheck) {
	    if (score >= beta) return beta;
	    if (MateValue - height < beta) return beta - 1;
	    halt_check;
	}

	hash_depth = -1;
	hash_move = flags & 0xFFFF;
#ifdef CUT_ALL
	int cut = Odd(height - pv_height);
#endif
	if (exclusion) {
		cnt = pext = 0;
		score = beta - 1;
		gen_evasions<me>(Current->moves);
	    if (F(Current->moves[0])) return score;
		goto skip_hash_move;
	}
	Current->best = hash_move;
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		if (Low32(Current->key) == Entry->key) {
			Entry->date = date;
			if (Entry->high < beta && Entry->high_depth >= depth && ReturnHigh) return Entry->high;
			if (T(Entry->move) && Entry->low_depth > hash_depth) {
				Current->best = hash_move = Entry->move;
				hash_depth = Entry->low_depth;
			}
			if (Entry->low >= beta && Entry->low_depth >= depth) {
				if (Entry->move) Current->best = Entry->move;
				if (ReturnLow) return Entry->low;
			}
			if (Entry->low_depth >= depth - 8 && Entry->low > hash_value) hash_value = Entry->low;
			break;
		}
	}

#ifdef PV_HASHING
	if (depth >= 20) {
    	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
			if (PVEntry->key == Low32(Current->key)) {
				PVEntry->date = date;
				hash_low(PVEntry->move,PVEntry->value,PVEntry->depth);
				hash_high(PVEntry->value,PVEntry->depth);
				if (PVEntry->depth >= depth) {
					if (PVEntry->move) Current->best = PVEntry->move;
					return PVEntry->value;
				}
				if (T(PVEntry->move) && PVEntry->depth > hash_depth) {
					Current->best = hash_move = PVEntry->move;
					hash_depth = PVEntry->depth;
					hash_value = PVEntry->value;
				}
				break;
			}
		}
#ifdef HASH_STORE
		for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4; i++, StoreEntry++) {
			if (StoreEntry->key == Low32(Current->key)) {
				hash_low(StoreEntry->move,StoreEntry->value,StoreEntry->depth);
				hash_high(StoreEntry->value,StoreEntry->depth);
				if (StoreEntry->depth >= depth) {
					if (StoreEntry->move) Current->best = StoreEntry->move;
					return StoreEntry->value;
				}
				if (T(StoreEntry->move) && StoreEntry->depth > hash_depth) {
					Current->best = hash_move = StoreEntry->move;
					hash_depth = StoreEntry->depth;
					hash_value = StoreEntry->value;
				}
				break;
			}
		}
#endif
	}
#endif

	if (hash_depth >= depth && hash_value > -EvalValue) score = Min(beta - 1, Max(score, hash_value));
	if (flags & FlagCallEvaluation) evaluate();

	Current->mask = Filled;
#ifndef NO_CAP_PRUNING
	if (Current->score - 10 < beta && depth <= 3) {
		Current->mask = Piece(opp);
		score = Current->score - 10;
	    if (Current->score + 200 < beta) {
		    score = Current->score + 200;
		    Current->mask ^= Pawn(opp);
		    if (Current->score + 500 < beta) {
			    score = Current->score + 500;
			    Current->mask ^= Light(opp);
			    if (Current->score + 700 < beta) {
				    score = Current->score + 700;
				    Current->mask ^= Rook(opp);
				    if (Current->score + 1400 < beta) {
					    score = Current->score + 1400;
					    Current->mask ^= Queen(opp);
				    }
			    }
		    }
	    }
	}
#endif
	cnt = 0;
	pext = 0;
    gen_evasions<me>(Current->moves);
	if (F(Current->moves[0])) return score;
#ifdef SINGLE_REPLY_EXT
	if (F(Current->moves[1])) pext = 2;
#ifdef DOUBLE_SINGLE
	else if (F(Current->moves[2])) pext = 1;
#endif
#endif

	if (T(hash_move) && is_legal<me>(move = hash_move)) {
		if (IsIllegal(me,move)) goto skip_hash_move;
		cnt++;
		check = is_check<me>(move);
#ifdef CHECK_EXT_NPV
		if (check) ext = CheckNPVExt(depth);
		else
#endif      
		ext = Max(pext, extension(move, depth, 0));
		if (depth >= 16 && ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2)) {
			new_depth = depth - Min(12, depth/2);
			value = -MateValue;
			if (hash_value >= beta && hash_depth >= new_depth) {
				margin = beta - ExclSingle(depth);
				if (ext < 1 + (Ext(flags) < 1)) {
					value = search_evasion<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) ext = 1 + (Ext(flags) < 1);
				}
				if (value < margin && ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2)) {
					margin = beta - ExclDouble(depth);
			    	value = search_evasion<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) ext = 2 + (Ext(flags) < 1) - (Ext(flags) >= 2);
				}
			}
		}
		new_depth = depth - 2 + ext;
		do_move<me>(move);
		evaluate();
		if (Current->att[opp] & King(me)) {
			undo_move<me>(move);
			cnt--;
			goto skip_hash_move;
		}
		value = -search<opp, 0>(1 - beta, new_depth, FlagHaltCheck | FlagHashCheck | ((hash_value >= beta && hash_depth >= depth - 12) ? FlagDisableNull : 0) | ExtFlag(ext));
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value >= beta) goto cut;
		}
	}
skip_hash_move:
	moves_to_play = 3 + ((depth * depth)/6);
	mark_evasions(Current->moves);
	Current->current = Current->moves;
	while (move = pick_move()) {
		if (move == hash_move) continue;
		if (IsIllegal(me,move)) continue;
		cnt++;
		if (IsRepetition(beta,move)) {
			score = Max(0, score);
			continue;
		}
		check = is_check<me>(move);
#ifdef CHECK_EXT_NPV
		if (check) ext = CheckNPVExt(depth);
		else
#endif      
		ext = Max(pext, extension(move, depth, 0));
		new_depth = depth - 2 + ext;
		if (F(Square(To(move))) && F(move & 0xE000)) {
#ifndef NO_EVASION_HISTORY_PRUNING
			if (F(check)) {
				if (cnt > moves_to_play) continue;
#endif
#ifndef NO_DELTA
				if ((value = Current->score + DeltaM(move) + 10) < beta && depth <= 3) {
					score = Max(value, score);
					continue;
				}
#endif
			}
#ifndef CUT_ALL
			if (depth >= 6 && cnt > 3) new_depth = Max(3, new_depth - msb(cnt));
#else
			if (depth >= 6 && cnt > (3 * all) && F(ext)) {
				new_depth = Max(3, new_depth - msb(cnt));
				if (cut) new_depth = Max(3, new_depth - 2);
			}
#endif
		}
		do_move<me>(move);
		value = -search<opp, 0>(1 - beta, new_depth, FlagNeatSearch | ExtFlag(ext));
		if (value >= beta && new_depth < depth - 2 + ext) value = -search<opp, 0>(1 - beta, depth - 2 + ext, FlagNeatSearch | FlagDisableNull | ExtFlag(ext));
		undo_move<me>(move);
		if (value > score) {
			score = value;
			if (value >= beta) goto cut;
		}
	}
	if (F(exclusion)) HashHigh(score, depth);
	return score;
cut:
	if (exclusion) return score;
	Current->best = move;
	HashLow(move, score, depth);
	return score;
}

template <bool me, bool root> int pv_search(int alpha, int beta, int depth, int flags) {
	int i, j, k, value, move, cnt, pext = 0, ext, check, hash_value = -MateValue, margin, 
		new_depth, hash_move, hash_depth, old_alpha = alpha, split_alpha, old_best, ex_depth = 0, ex_value, loop, do_split = 0, start_knodes = (nodes >> 10);
	GSortList SL[1];
	int height = (int)(Current - Data);
	GEntry * Entry;
	GMoveList * CML;
	GMove * CM;

	if (root) {
		depth = Max(depth, 2);
		flags |= ExtFlag(1);
		if (F(RootList->sort[0].move)) return 0;
	    if (Print) {
			fprintf(stdout,"info depth %d\n",(depth/2)); 
			fflush(stdout);
		}
		for (i = 0; i < RootList->number - 1; i++) {
			k = i;
			value = RootList->sort[i].score;
			for (j = i + 1; j < RootList->number; j++) {
				if (RootList->sort[j].score > value) {
					k = j;
					value = RootList->sort[j].score;
				}
			}
			if (k != i) {
				move = RootList->sort[k].move;
				for (j = k; j > i; j--) {
					RootList->sort[j].move = RootList->sort[j - 1].move;
					RootList->sort[j].score = RootList->sort[j - 1].score;
				}
				RootList->sort[i].move = move;
				RootList->sort[i].score = value;
			}
		}
		for (i = 0; i < RootList->number; i++) {
			RootList->sort[i].score = 0;
			RootList->sort[i].stage = 0;
			RootList->sort[i].flags = 0;
		}
		RootList->sort[0].score = 2;
		goto check_hash;
	}
	if (depth <= 1) return q_search<me>(alpha, beta, 1, FlagNeatSearch);
	if (Convert((Current - Data),int) - MateValue >= beta) return beta;
	if (MateValue - Convert((Current - Data),int) <= alpha) return alpha;
	halt_check;

check_hash:
	hash_depth = -1;
	Current->best = hash_move = 0;
#ifdef PV_HASHING
    for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size && F(root); i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key)) {
			PVEntry->date = date;
			hash_low(PVEntry->move,PVEntry->value,PVEntry->depth);
			hash_high(PVEntry->value,PVEntry->depth);
			if (PVEntry->depth >= depth && T(PVHashing)) {
				if (PVEntry->move) Current->best = PVEntry->move;
				if ((Current->ply <= 50 && PVEntry->ply <= 50) || Current->ply == PVEntry->ply) return PVEntry->value;
			}
			if (T(PVEntry->move) && PVEntry->depth > hash_depth) {
				Current->best = hash_move = PVEntry->move;
				hash_depth = PVEntry->depth;
				hash_value = PVEntry->value;
			}
			break;
		}
	}
#ifdef HASH_STORE
	for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4 && F(root); i++, StoreEntry++) {
		if (StoreEntry->key == Low32(Current->key)) {
			hash_low(StoreEntry->move,StoreEntry->value,StoreEntry->depth);
			hash_high(StoreEntry->value,StoreEntry->depth);
			if (StoreEntry->depth >= depth) {
				if (StoreEntry->move) Current->best = StoreEntry->move;
				return StoreEntry->value;
			}
			if (T(StoreEntry->move) && StoreEntry->depth > hash_depth) {
				Current->best = hash_move = StoreEntry->move;
				hash_depth = StoreEntry->depth;
				hash_value = StoreEntry->value;
			}
			break;
		}
	}
#endif
#endif
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4 && F(root); Entry++, i++) {
		if (Low32(Current->key) == Entry->key) {
			Entry->date = date;
			if (T(Entry->move) && Entry->low_depth > hash_depth) {
				Current->best = hash_move = Entry->move;
				hash_depth = Entry->low_depth;
				if (Entry->low_depth) hash_value = Entry->low;
			}
			break;
		}
	}

	evaluate();
	if (F(root) && depth >= 6 && (F(hash_move) || hash_value <= alpha || hash_depth < depth - 8)) {
		if (F(hash_move)) new_depth = depth - 2;
		else new_depth = depth - 4;
		value = pv_search<me, 0>(alpha, beta, new_depth, hash_move);
		if (value > alpha) {
hash_move_found:
			if (Current->best) hash_move = Current->best;
		    hash_depth = new_depth;
		    hash_value = value;
			goto skip_iid;
		} else {
			i = 0;		
			new_depth = depth - 8;
iid_loop:
			margin = alpha - (8 << i);
			if (T(hash_move) && hash_depth >= Min(new_depth, depth - 8) && hash_value >= margin) goto skip_iid;
#ifdef CUT_ALL
			pv_height = height;
#endif
			value = search<me, 0>(margin, new_depth, FlagHashCheck | FlagNoKillerUpdate | FlagDisableNull | FlagReturnBestMove | hash_move);
			if (value >= margin) goto hash_move_found;
			i++;
			if (i < 5) goto iid_loop;
		}
	}
skip_iid:
	if (F(root) && Check(me)) {
		alpha = Max(Convert((Current - Data),int) - MateValue, alpha);
		Current->mask = Filled;
		gen_evasions<me>(Current->moves);
		if (F(Current->moves[0])) return Convert((Current - Data),int) - MateValue; 
#ifdef SINGLE_REPLY_EXT
	    if (F(Current->moves[1])) pext = 2;
#ifdef DOUBLE_SINGLE
		else if (F(Current->moves[2])) pext = 1;
#endif
#endif
	}
	if (root) {
		hash_move = RootList->sort[0].move;
		hash_value = Previous;
		hash_depth = Max(0, depth - 2);
	}

	if (F(Check(me))) {
		Current->stage = s_gen_cap;
		Current->gen_flags = 0;
		Current->ref[0] = RefM(Current->move).ref[0];
	    Current->ref[1] = RefM(Current->move).ref[1];
	} else Current->stage = e_gen_ev;
	SL->number = 0;
	if (F(root)) {
	    while (move = get_move<me>()) {
		    SL->sort[SL->number].move = move;
		    SL->sort[SL->number].stage = Current->stage;
		    SL->number++;
	    }
		for (i = 0; i < SL->number; i++) {
			if (SL->sort[i].move == hash_move) {
				GSort CS[1];
			    memcpy(CS, &SL->sort[i], sizeof(GSort));
			    for (j = i; j > 0; j--) memcpy(&SL->sort[j], &SL->sort[j - 1], sizeof(GSort));
			    memcpy(&SL->sort[0], CS, sizeof(GSort));
			    break;
			}
		}
	} else memcpy(SL, RootList, sizeof(GSortList));
	SL->sort[SL->number].move = 0;
	SL->pos = 0;

	cnt = 0;
#ifdef PV_SPLIT
#ifndef LOCAL_TUNER
	if (F(root) && depth >= SplitDepth && PrN > 1)
#ifndef CHILD_PROCESS_SPLIT
		if (Id == 0)
#endif
		do_split = 1;
#endif
#endif
	if (do_split) {
	    CML = &SMPI->Info[Id].MoveList[height];
	    init_move_list(CML);
		CML->pv = 1;
		CML->alpha = alpha;
		CML->beta = beta;
		CML->depth = depth;
        CML->singular = 0;
	}
	while (SL->pos < SL->number) {
		move = SL->sort[SL->pos].move;
		if (IsIllegal(me,move)) goto next_move;
		cnt++;
#ifndef TUNER
		if (root) {
		    memset(Data + 1, 0, 127 * sizeof(GData));
		    move_to_string(move,score_string);
		    if (Print) sprintf(info_string,"info currmove %s currmovenumber %d\n",score_string,cnt);
		}
#endif
		if (IsRepetition(alpha + 1,move)) goto next_move;
		check = is_check<me>(move);
#ifdef CHECK_EXT_PV
		if (check) ext = CheckPVExt;
		else
#endif      
		ext = Max(pext, extension(move, depth, 1));
#ifdef CUT_ALL
		pv_height = height;
#endif
		if (move == hash_move && depth >= 12 && (ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2) || T(root))) {
			new_depth = depth - Min(12, depth/2);
			value = -MateValue;
			if (hash_value > alpha && hash_depth >= new_depth) {
				margin = hash_value - ExclSinglePV(depth);
				if (ext < 1 + (Ext(flags) < 1) || T(root)) {
					if (Check(me)) value = search_evasion<me, 1>(margin, new_depth, hash_move); 
			    	else value = search<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) {
						ext = Max(1 + (Ext(flags) < 1), ext);
						if (root) CurrentSI->Singular = 1;
						ex_depth = new_depth;
						ex_value = margin - 1;
					}
				}
				if (value < margin && (ext < 2 + (Ext(flags) < 1) - (Ext(flags) >= 2) || T(root))) {
					margin = hash_value - ExclDoublePV(depth);
			    	if (Check(me)) value = search_evasion<me, 1>(margin, new_depth, hash_move); 
			    	else value = search<me, 1>(margin, new_depth, hash_move); 
			    	if (value < margin) {
						ext = Max(2 + (Ext(flags) < 1) - (Ext(flags) >= 2), ext);
						if (root) CurrentSI->Singular = 2;
						ex_depth = new_depth;
						ex_value = margin - 1;
					}
				}
			}
		}
		new_depth = depth - 2 + ext;
		if (((T(root) && F(move & 0xE000) && F(Square(To(move)))) || (SL->sort[SL->pos].stage > s_ref_one && SL->sort[SL->pos].stage <= s_quiet)) 
			&& cnt > 3 && depth >= 6) {
			int reduction = msb(cnt) - 1;
			if (move == Current->ref[0] || move == Current->ref[1]) reduction = Max(0, reduction - 1);
			new_depth = Max(3, new_depth - reduction);
		}
		if (T(do_split) && move != hash_move && cnt > 1) {
			CM = &CML->move[CML->move_number++];
			CM->move = move;
			CM->reduced_depth = new_depth;
			CM->research_depth = depth - 2 + ext;
			CM->ext = ext;
			CM->stage = Current->stage;
			CM->flags = 0;
			goto next_move;
		}
		do_move<me>(move);
		if (new_depth <= 1 || move == hash_move) value = -pv_search<opp, 0>(-beta, -alpha, new_depth, ExtFlag(ext));
		else {
#ifdef CUT_ALL
			pv_height = height;
#endif
			value = -search<opp, 0>(-alpha, new_depth, FlagNeatSearch | ExtFlag(ext));
		}
		if (value > alpha && new_depth > 1 && move != hash_move) {
			if (root) {
			    RootList->sort[SL->pos + 1].score = 1;
			    CurrentSI->Early = 0;
			    old_best = best_move;
			    best_move = move;
			}
			new_depth = depth - 2 + ext;
			value = -pv_search<opp, 0>(-beta, -alpha, new_depth, ExtFlag(ext));
			if (T(root) && value <= alpha) best_move = old_best;
		}
		undo_move<me>(move);
		if (value > alpha) {
			if (root) {
			    if (move != hash_move) {
					RootList->sort[SL->pos].score = cnt + 3;
				    CurrentSI->Change = 1;
				}
				CurrentSI->FailLow = 0;
			    best_move = move;
			    best_score = value;
				hash_low(best_move,value,depth);
				if (depth >= 14 || T(Console)) send_pv(depth/2, old_alpha, beta, value);
			}
		    alpha = value;
			if (do_split) CML->alpha = value;
			Current->best = move;
			if (value >= beta) goto cut;
		} else if (T(root) && move == hash_move) {
			CurrentSI->FailLow = 1;
			CurrentSI->FailHigh = 0;
			CurrentSI->Singular = 0;
			if (depth >= 14 || T(Console)) send_pv(depth/2, old_alpha, beta, value);
		}
next_move:
		SL->pos++;
	}
	if (F(cnt) && F(Check(me))) {
		hash_high(0, 127);
		hash_low(0, 0, 127);
		hash_exact(0, 0, 127, 0, 0, 0);
	    return 0;
	}
	if (do_split) {
		split_alpha = alpha;
		loop = 0;
		LOCK(CML->lock);
		CML->active = 1;
		ActivateSP(Id,height);
		CML->move[CML->move_number].move = 0;
		CM = &CML->move[0];
		send_position(CML->position);
		if (setjmp(CML->jump)) {
			alpha = beta;
			move = CML->best_move;
			retrieve_position(CML->position, height);
			halt_all(height, 127);
			goto cut;
		}
new_loop:
		for (i = 0; i < CML->move_number; i++) {
			CM = &CML->move[i];
			if (loop == 0) CML->current_master_position = i;
			move = CM->move;
			if (CM->flags & FlagFinished) {
				if (CM->value >= beta) goto cut_achieved;
				continue;
			}
			if (loop == 0) {
			    if (CM->flags & FlagClaimed) continue;
				CM->flags |= FlagClaimed;
			    CM->id = Id;
			}
			if (loop == 1 && T(CM->flags & FlagClaimed)) {
#ifdef WAIT_FOR_CHILD_PROCESSES
				UNLOCK(CML->lock);
				while (F(CM->flags & FlagFinished)) _mm_pause();
				LOCK(CML->lock);
				if (CM->value >= beta) goto cut_achieved;
				continue;
#endif
				SET_BIT(SMPI->Info[CM->id].flags, STOP_ORDER);
				CM->id = Id;
			}
			new_depth = CM->reduced_depth;
			ext = CM->ext;
			alpha = CML->alpha;
			UNLOCK(CML->lock);
			for (int id = 0; id < PrN; id++) if (id != Id) SET_BIT(SMPI->Info[id].flags,SPLIT_SIGNAL);

			do_move<me>(move);
#ifdef CUT_ALL
			pv_height = height;
#endif
			value = -search<opp, 0>(-alpha, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value > alpha) value = -pv_search<opp, 0>(-beta, -alpha, depth - 2 + ext, ExtFlag(ext));
			undo_move<me>(move);

			LOCK(CML->lock);
			alpha = CML->alpha;
			CM->value = value;
			CM->flags |= FlagFinished;
			if (value > alpha) {
				alpha = value;
				Current->best = CML->best_move = move;
				CML->alpha = value;
				if (value >= beta) {
cut_achieved:
					alpha = CM->value;
					Current->best = move;
					halt_all(CML, 1);
					UNLOCK(CML->lock);
					goto cut;
				}
			}
		}
		if (loop == 0) {
			loop = 1;
			goto new_loop;
		}
		alpha = CML->alpha;
		if (alpha > split_alpha) Current->best = CML->best_move;
		halt_all(CML, 1);
		UNLOCK(CML->lock);
	}
	if (F(root) || F(SearchMoves)) hash_high(alpha, depth);
	if (alpha > old_alpha) {
		hash_low(Current->best,alpha,depth); 
		if (Current->best != hash_move) ex_depth = 0;
		if (F(root) || F(SearchMoves)) hash_exact(Current->best,alpha,depth,ex_value,ex_depth,T(parent) ? (Convert(nodes >> 10,int) - start_knodes) : 0); 
#ifdef HASH_STORE
		if (Current - Data <= 2 && (F(root) || F(SearchMoves))) {
			if (Current != Data) hash_store(Current->best,alpha,depth,ex_value,ex_depth,0);
			else hash_store(Current->best,alpha,depth,ex_value,ex_depth,get_time() - StartTime);
		}
#endif
	}
	return alpha;
cut:
	hash_low(move, alpha, depth);
	return alpha;
}

template <bool me> void root() {
	int i, d, move, depth, value, alpha, beta, delta, start_depth = 2, hash_depth = 0, hash_value, store_time = 0, time_est, ex_depth = 0, ex_value, prev_time = 0, knodes = 0;
	sint64 time;
	GEntry * Entry;

	date++;
	nodes = check_node = check_node2 = 0;
#ifndef TUNER
	if (parent) SMPI->total_nodes = 0;
#endif
	memcpy(Data,Current,sizeof(GData));
	Current = Data;
	evaluate();
#ifndef TUNER
	send_position(SMPI->Info[Id].MoveList[0].position);
#endif
	gen_legal_moves<me>();
	if (PVN > 1) {
		memset(MultiPV,0,128 * sizeof(int));
		for (i = 0; i < RootList->number; i++) MultiPV[i] = RootList->sort[i].move;
	}
	best_move = RootList->sort[0].move;
	if (F(best_move)) return;
	if (F(Infinite) && F(RootList->sort[1].move)) {
		value = pv_search<me, 1>(-MateValue, MateValue, 4, FlagNeatSearch);
		LastDepth = 128;
		send_pv(6, -MateValue, MateValue, value);
		send_best_move();
		Searching = 0;
		SET(SMPI->Info[Id].searching, 0);
		return;
	}

	memset(CurrentSI,0,sizeof(GSearchInfo));
	memset(BaseSI,0,sizeof(GSearchInfo));
	Previous = -MateValue;
	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key) && is_legal<me>(PVEntry->move) && PVEntry->move == best_move) {
			if (PVEntry->depth > hash_depth) {
				hash_depth = PVEntry->depth;
				hash_value = PVEntry->value;
				ex_depth = PVEntry->ex_depth;
				ex_value = PVEntry->exclusion;
				knodes = PVEntry->knodes;
			}
			break;
		}
	}
#ifdef HASH_STORE
	for (i = 0, StoreEntry = StoreHash + (High32(Current->key) & store_hash_mask); i < 4; i++, StoreEntry++) {
		if (StoreEntry->key == Low32(Current->key) && is_legal<me>(StoreEntry->move) && StoreEntry->move == best_move) {
			store_time = StoreEntry->time;
			if (StoreEntry->depth > hash_depth) {
				hash_depth = StoreEntry->depth;
				hash_value = StoreEntry->value;
			}
			if (StoreEntry->ex_depth > ex_depth) {
				ex_depth = StoreEntry->ex_depth;
				ex_value = StoreEntry->exclusion;
			}
			break;
		}
	}
#endif
	if (T(hash_depth) && PVN == 1) {
		Previous = best_score = hash_value;
		depth = hash_depth;
		if (PVHashing) {
	        send_pv(depth/2, -MateValue, MateValue, best_score);
		    start_depth = (depth + 2) & (~1);
		}
		if ((depth >= LastDepth - 8 || T(store_time)) && LastValue >= LastExactValue && hash_value >= LastExactValue && T(LastTime) && T(LastSpeed)) {
			time = TimeLimit1;
			if (ex_depth >= depth - Min(12, depth/2) && ex_value < hash_value - 10) {
				BaseSI->Early = 1;
				BaseSI->Singular = 1;
				if (ex_value < hash_value - 20) {
					time = (time * TimeSingTwoMargin)/100;
					BaseSI->Singular = 2;
				}
				else time = (time * TimeSingOneMargin)/100;
			}
			time_est = Min(LastTime,(knodes << 10)/LastSpeed);
			time_est = Max(time_est, store_time);
set_prev_time:
			LastTime = prev_time = time_est;
			if (prev_time >= time && F(Infinite)) {
				InstCnt++;
				if (time_est <= store_time) InstCnt = 0;
				if (InstCnt > 2) {
					if (T(store_time) && store_time < time_est) {
						time_est = store_time;
						goto set_prev_time;
					}
					LastSpeed = 0;
					LastTime = 0;
					prev_time = 0;
					goto set_jump;
				}
				if (hash_value > 0 && Current->ply >= 2 && F(Square(To(best_move))) && F(best_move & 0xF000) && PrevMove == ((To(best_move) << 6) | From(best_move))) goto set_jump;
				do_move<me>(best_move);
				if (Current->ply >= 100) {
					undo_move<me>(best_move);
					goto set_jump;
				}
				for (i = 4; i <= Current->ply; i+=2) if (Stack[sp-i] == Current->key) {
					undo_move<me>(best_move);
					goto set_jump;
				}
				undo_move<me>(best_move);
				LastDepth = depth;
				LastTime = prev_time;
				LastValue = LastExactValue = hash_value;
				send_best_move();
				Searching = 0;
				SET(SMPI->Info[Id].searching, 0);
				return;
			} else goto set_jump;
		}
	}
	LastTime = 0;
set_jump:
	if (setjmp(Jump)) {
		Current = Data;
#ifndef TUNER
		retrieve_position(SMPI->Info[Id].MoveList[0].position, 0);
		halt_all(0, 127);
		SET(SMPI->Info[Id].searching, 0);
#endif
		Searching = 0;
		send_best_move();
		return;
	}
	for (depth = start_depth; depth < DepthLimit; depth += 2) {
		memset(Data + 1, 0, 127 * sizeof(GData));
		CurrentSI->Early = 1;
		CurrentSI->Change = CurrentSI->FailHigh = CurrentSI->FailLow = CurrentSI->Singular = 0;
		if (PVN > 1) value = multipv<me>(depth);
#ifdef ASPIRATION
		else if ((depth/2) < 7 || F(Aspiration)) LastValue = LastExactValue = value = pv_search<me, 1>(-MateValue, MateValue, depth, FlagNeatSearch);
#else
		else if (1) LastValue = LastExactValue = value = pv_search<me, 1>(-MateValue, MateValue, depth, FlagNeatSearch);
#endif
		else {
			delta = 8;
			alpha = Previous - delta;
			beta = Previous + delta;
loop:
			if (delta >= 16 * 32) {
				LastValue = LastExactValue = value = pv_search<me, 1>(-MateValue, MateValue, depth, FlagNeatSearch);
				goto finish;
			}
			value = pv_search<me, 1>(alpha, beta, depth, FlagNeatSearch);
			if (value <= alpha) {
				CurrentSI->FailHigh = 0;
				CurrentSI->FailLow = 1;
				alpha -= delta;
				delta *= 2;
				LastValue = value;
				memcpy(BaseSI,CurrentSI,sizeof(GSearchInfo));
				goto loop;
			} else if (value >= beta) {
				CurrentSI->FailHigh = 1;
				CurrentSI->FailLow = 0;
				CurrentSI->Early = 1;
				CurrentSI->Change = 0;
				CurrentSI->Singular = Max(CurrentSI->Singular, 1);
				beta += delta;
				delta *= 2;
				LastDepth = depth;
				LastTime = Max(prev_time,get_time() - StartTime);
				LastSpeed = nodes/Max(LastTime, 1);
				if (depth + 2 < DepthLimit) depth += 2;
				InstCnt = 0;
				check_time(LastTime,0);
				memset(Data + 1, 0, 127 * sizeof(GData));
				LastValue = value;
				memcpy(BaseSI,CurrentSI,sizeof(GSearchInfo));
#ifdef NODES
				if (nodes > MaxNodes) break;
#endif
				goto loop;
			} else LastValue = LastExactValue = value;
		}
finish:
		if (value < Previous - 50) CurrentSI->Bad = 1;
		else CurrentSI->Bad = 0;
		memcpy(BaseSI,CurrentSI,sizeof(GSearchInfo));
		LastDepth = depth;
		LastTime = Max(prev_time,get_time() - StartTime);
		LastSpeed = nodes/Max(LastTime, 1);
		Previous = value;
		InstCnt = 0;
		check_time(LastTime,0);
#ifdef NODES
		if (nodes > MaxNodes) break;
#endif
	}
	Searching = 0;
#ifndef TUNER
	SET(SMPI->Info[Id].searching, 0);
#endif
	if (F(Infinite) || DepthLimit < 128) send_best_move();
}

template <bool me> int multipv(int depth) {
	int move, low = MateValue, value, i, cnt, ext, new_depth = depth;
	fprintf(stdout,"info depth %d\n",(depth/2)); fflush(stdout);
	for (cnt = 0; cnt < PVN && T(move = (MultiPV[cnt] & 0xFFFF)); cnt++) {
		MultiPV[cnt] = move;
		move_to_string(move,score_string);
		if (T(Print)) sprintf(info_string,"info currmove %s currmovenumber %d\n",score_string,cnt + 1);
		new_depth = depth - 2 + (ext = extension(move, depth, 1));
		do_move<me>(move);
		value = -pv_search<opp, 0>(-MateValue,MateValue,new_depth,ExtFlag(ext));
		MultiPV[cnt] |= value << 16;
		if (value < low) low = value;
		undo_move<me>(move);
		for (i = cnt - 1; i >= 0; i--) {
			if ((MultiPV[i] >> 16) < value) {
				MultiPV[i + 1] = MultiPV[i];
				MultiPV[i] = move | (value << 16);
			}
		}
		best_move = MultiPV[0] & 0xFFFF;
		Current->score = MultiPV[0] >> 16;
		send_multipv((depth/2), cnt);
	}
	for (;T(move = (MultiPV[cnt] & 0xFFFF)); cnt++) {
		MultiPV[cnt] = move;
		move_to_string(move,score_string);
		if (T(Print)) sprintf(info_string,"info currmove %s currmovenumber %d\n",score_string,cnt + 1);
		new_depth = depth - 2 + (ext = extension(move, depth, 1));
#ifdef CUT_ALL
		pv_height = (int)(Current - Data);
#endif
		do_move<me>(move);
		value = -search<opp, 0>(-low, new_depth, FlagNeatSearch | ExtFlag(ext));
		if (value > low) value = -pv_search<opp, 0>(-MateValue,-low,new_depth,ExtFlag(ext));
		MultiPV[cnt] |= value << 16;
		undo_move<me>(move);
		if (value > low) {
			for (i = cnt; i >= PVN; i--) MultiPV[i] = MultiPV[i - 1];
			MultiPV[PVN - 1] = move | (value << 16);
			for (i = PVN - 2; i >= 0; i--) {
				if ((MultiPV[i] >> 16) < value) {
					MultiPV[i + 1] = MultiPV[i];
					MultiPV[i] = move | (value << 16);
				}
			}
			best_move = MultiPV[0] & 0xFFFF;
		    Current->score = MultiPV[0] >> 16;
			low = MultiPV[PVN - 1] >> 16;
			send_multipv((depth/2), cnt);
		}
	}
	return Current->score;
}

void send_pv(int depth, int alpha, int beta, int score) {
	int i, pos, move, mate = 0, mate_score, sel_depth;
	sint64 nps, snodes;
	if (F(Print)) return;
	for (sel_depth = 1; sel_depth < 127 && T((Data + sel_depth)->att[0]); sel_depth++);
	sel_depth--;
	pv_length = 64;
	if (F(move = best_move)) move = RootList->sort[0].move;
	if (F(move)) return;
	PV[0] = move;
	if (Current->turn) do_move<1>(move);
	else do_move<0>(move);
	pvp = 1;
	pick_pv();
#ifdef LONGEST_LINE
	int *p;
	uint16 *q;
	for (p = LLine, q = PV; T(*p); p++, q++) *q = *p;  
#endif
	if (Current->turn ^ 1) undo_move<1>(move);
	else undo_move<0>(move);
	pos = 0;
	for (i = 0; i < 64 && T(PV[i]); i++) {
		if (pos > 0) { 
			pv_string[pos] = ' '; 
			pos++; 
		}
        move = PV[i];
        pv_string[pos++] = ((move >> 6) & 7) + 'a';
        pv_string[pos++] = ((move >> 9) & 7) + '1';
        pv_string[pos++] = (move & 7) + 'a';
        pv_string[pos++] = ((move >> 3) & 7) + '1';
        if (IsPromotion(move)) {
            if ((move & 0xF000) == FlagPQueen)  pv_string[pos++] = 'q';
            else if ((move & 0xF000) == FlagPRook)   pv_string[pos++] = 'r';
            else if ((move & 0xF000) == FlagPLight || (move & 0xF000) == FlagPDark) pv_string[pos++] = 'b';
            else if ((move & 0xF000) == FlagPKnight) pv_string[pos++] = 'n';
		}
        pv_string[pos] = 0;
	}
	score_string[0] = 'c';
	score_string[1] = 'p';
    if (score > EvalValue) {
		mate = 1;
		strcpy(score_string,"mate ");
		mate_score = (MateValue - score + 1)/2;
	    score_string[6] = 0;
	} else if (score < -EvalValue) {
		mate = 1;
        strcpy(score_string,"mate ");
		mate_score = -(score + MateValue + 1)/2;
		score_string[6] = 0;
	} else {
        score_string[0] = 'c';
	    score_string[1] = 'p';
		score_string[2] = ' ';
		score_string[3] = 0;
	}
	nps = get_time() - StartTime;
#ifdef MP_NPS
	snodes = SMPI->total_nodes;
#else
	snodes = nodes;
#endif
	if (nps) nps = (snodes * 1000)/nps; 
	if (score < beta) {
		if (score <= alpha) fprintf(stdout,"info depth %d seldepth %d score %s%d upperbound nodes %I64d nps %I64d pv %s\n",depth,sel_depth,score_string,(mate ? mate_score : score),snodes,nps,pv_string);
		else fprintf(stdout,"info depth %d seldepth %d score %s%d nodes %I64d nps %I64d pv %s\n",depth,sel_depth,score_string,(mate ? mate_score : score),snodes,nps,pv_string);
	} else fprintf(stdout,"info depth %d seldepth %d score %s%d lowerbound nodes %I64d nps %I64d pv %s\n",depth,sel_depth,score_string,(mate ? mate_score : score),snodes,nps,pv_string);
	fflush(stdout);
}

void send_multipv(int depth, int curr_number) {
	int i, j, pos, move, score;
	sint64 nps, snodes;
	if (F(Print)) return;
	for (j = 0; j < PVN && T(MultiPV[j]); j++) {
		pv_length = 63;
		pvp = 0;
		move = MultiPV[j] & 0xFFFF;
		score = MultiPV[j] >> 16;
		memset(PV,0,64 * sizeof(uint16));
		if (Current->turn) do_move<1>(move);
	    else do_move<0>(move);
		pick_pv();
		if (Current->turn ^ 1) undo_move<1>(move);
	    else undo_move<0>(move);
		for (i = 63; i > 0; i--) PV[i] = PV[i - 1];
		PV[0] = move;
		pos = 0;
		for (i = 0; i < 64 && T(PV[i]); i++) {
			if (pos > 0) { 
				pv_string[pos] = ' '; 
				pos++; 
			}
        	move = PV[i];
        	pv_string[pos++] = ((move >> 6) & 7) + 'a';
        	pv_string[pos++] = ((move >> 9) & 7) + '1';
        	pv_string[pos++] = (move & 7) + 'a';
        	pv_string[pos++] = ((move >> 3) & 7) + '1';
        	if (IsPromotion(move)) {
            	if ((move & 0xF000) == FlagPQueen)  pv_string[pos++] = 'q';
            	else if ((move & 0xF000) == FlagPRook)   pv_string[pos++] = 'r';
            	else if ((move & 0xF000) == FlagPLight || (move & 0xF000) == FlagPDark) pv_string[pos++] = 'b';
            	else if ((move & 0xF000) == FlagPKnight) pv_string[pos++] = 'n';
			}
        	pv_string[pos] = 0;
		}
		score_string[0] = 'c';
		score_string[1] = 'p';
		if (score > EvalValue) {
			strcpy(score_string,"mate ");
			score = (MateValue - score + 1)/2;
	    	score_string[6] = 0;
		} else if (score < -EvalValue) {
        	strcpy(score_string,"mate ");
			score = -(score + MateValue + 1)/2;
			score_string[6] = 0;
		} else {
        	score_string[0] = 'c';
	    	score_string[1] = 'p';
			score_string[2] = ' ';
			score_string[3] = 0;
		}
		nps = get_time() - StartTime;
#ifdef MP_NPS
	    snodes = SMPI->total_nodes;
#else
	    snodes = nodes;
#endif
	    if (nps) nps = (snodes * 1000)/nps; 
		fprintf(stdout,"info multipv %d depth %d score %s%d nodes %I64d nps %I64d pv %s\n",j + 1,(j <= curr_number ? depth : depth - 1),score_string,score,snodes,nps,pv_string);
		fflush(stdout);
	}
}

void send_best_move() {
	uint64 snodes;
	int ponder;
	GlobalTime -= Convert(get_time() - StartTime, int) - GlobalInc;
	if (GlobalTime < GlobalInc) GlobalTime = GlobalInc;
	if (F(Print)) return;
#ifdef MP_NPS
	snodes = SMPI->total_nodes;
#else
	snodes = nodes;
#endif
	fprintf(stdout,"info nodes %I64d score cp %d\n",snodes,best_score);
	if (!best_move) return;
	Current = Data;
	evaluate();
	if (Current->turn) do_move<1>(best_move);
	else do_move<0>(best_move);
	pv_length = 1;
	pvp = 0;
	pick_pv();
	ponder = PV[0];
	if (Current->turn ^ 1) undo_move<1>(best_move);
	else undo_move<0>(best_move);
	move_to_string(best_move,pv_string);
	if (ponder) {
		move_to_string(ponder,score_string);
		fprintf(stdout,"bestmove %s ponder %s\n",pv_string,score_string);
	} else fprintf(stdout,"bestmove %s\n",pv_string);
	fflush(stdout);
}

void get_position(char string[]) {
	const char * fen;
    char * moves;
    const char * ptr;
    int move, move1 = 0;

    fen = strstr(string,"fen ");
    moves = strstr(string,"moves ");
    if (fen != NULL) get_board(fen+4);
    else get_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	PrevMove = 0;
    if (moves != NULL) {
        ptr = moves+6;
        while (*ptr != 0) {
            pv_string[0] = *ptr++;
            pv_string[1] = *ptr++;
            pv_string[2] = *ptr++;
            pv_string[3] = *ptr++;
            if (*ptr == 0 || *ptr == ' ') pv_string[4] = 0;
            else { 
				pv_string[4] = *ptr++; 
				pv_string[5] = 0; 
			}
			evaluate();
            move = move_from_string(pv_string);
			PrevMove = move1;
			move1 = move;
            if (Current->turn) do_move<1>(move);
	        else do_move<0>(move);
			memcpy(Data,Current,sizeof(GData));
			Current = Data;
            while (*ptr == ' ') ptr++;
        }
    }
	memcpy(Stack, Stack + sp - Current->ply, (Current->ply + 1) * sizeof(uint64));
	sp = Current->ply;
}

void get_time_limit(char string[]) {
	const char * ptr;
	int i, time, inc, wtime, btime, winc, binc, moves, pondering, movetime = 0;
  
	Infinite = 1;
	MoveTime = 0;
	SearchMoves = 0;
	SMPointer = 0;
	pondering = 0;
	TimeLimit1 = 0;
	TimeLimit2 = 0;
	wtime = btime = 0;
	winc = binc = 0;
	moves = 0;
	Stop = 0;
	DepthLimit = 128;
    ptr = strtok(string," ");
    for (ptr = strtok(NULL," "); ptr != NULL; ptr = strtok(NULL," ")) {
		if (!strcmp(ptr,"binc")) {
			ptr = strtok(NULL," "); 
			binc = atoi(ptr);
			Infinite = 0;
		} else if (!strcmp(ptr,"btime")) { 
			ptr = strtok(NULL," "); 
			btime = atoi(ptr);
			Infinite = 0;
		} else if (!strcmp(ptr,"depth")) { 
			ptr = strtok(NULL," "); 
			DepthLimit = 2 * atoi(ptr) + 2; 
			Infinite = 1;
		} else if (!strcmp(ptr,"infinite")) { 
			Infinite = 1; 
		} else if (!strcmp(ptr,"movestogo")) { 
			ptr = strtok(NULL," "); 
			moves = atoi(ptr);
			Infinite = 0;
		} else if (!strcmp(ptr,"winc")) { 
			ptr = strtok(NULL," "); 
			winc = atoi(ptr);
			Infinite = 0;
		} else if (!strcmp(ptr,"wtime")) { 
			ptr = strtok(NULL," "); 
			wtime = atoi(ptr); 
			Infinite = 0;
		} else if (!strcmp(ptr,"movetime")) { 
			ptr = strtok(NULL," "); 
			movetime = atoi(ptr);
			MoveTime = 1;
			Infinite = 0;
		} else if (!strcmp(ptr,"searchmoves")) {
			if (F(SearchMoves)) {
				for (i = 0; i < 256; i++) SMoves[i] = 0;
			}
		    SearchMoves = 1;
		    ptr += 12;
			while (ptr != NULL && ptr[0] >= 'a' && ptr[0] <= 'h' && ptr[1] >= '1' && ptr[1] <= '8') {
				pv_string[0] = *ptr++;
                pv_string[1] = *ptr++;
                pv_string[2] = *ptr++;
                pv_string[3] = *ptr++;
                if (*ptr == 0 || *ptr == ' ') pv_string[4] = 0;
                else { 
				    pv_string[4] = *ptr++; 
				    pv_string[5] = 0; 
			    }
				SMoves[SMPointer] = move_from_string(pv_string);
				SMPointer++;
				ptr = strtok(NULL," ");
			}
		} else if (!strcmp(ptr,"ponder")) pondering = 1;
    }
	if (pondering) Infinite = 1;
	if (Current->turn == White) {
		time = wtime;
		inc = winc;
	} else {
		time = btime;
		inc = binc;
	}
	if (GlobalTime == 0x1FFFFFFF) {
		GlobalTime = time/CPUTimeBaseMul;
		GlobalInc = inc/CPUTimeIncMul;
	}
	if (CPUTime) {
	    time = GlobalTime;
	    inc = GlobalInc;
	}
	if (moves) moves = Max(moves - 1, 1);
	int time_max = Max(time - Min(1000, time/2), 0);
	int nmoves;
	if (moves) nmoves = moves;
	else nmoves = MovesTg - 1;
	TimeLimit1 = Min(time_max, (time_max + (Min(MovesTg - 1, nmoves) * inc))/Min(MovesTg - 1, nmoves));
	TimeLimit2 = Min(time_max, (time_max + (Min(MovesTg - 1, nmoves) * inc))/Min(3,Min(MovesTg - 1, nmoves)));
	TimeLimit1 = Min(time_max, (TimeLimit1 * TimeRatio)/100);
	if (Ponder) TimeLimit1 = (TimeLimit1 * PonderRatio)/100;
	if (MoveTime) {
		TimeLimit2 = movetime;
		TimeLimit1 = TimeLimit2 * 100;
	}
    InfoTime = StartTime = get_time();
	Searching = 1;
	SET(SMPI->Info[Id].searching, 1);
	if (F(Infinite)) PVN = 1;
	if (Current->turn) root<1>();
	else root<0>();
}

sint64 get_time() { // time in milliseconds
#ifdef CPU_TIMING
	if (F(CPUTime))
#endif
		return GetTickCount();
#ifdef CPU_TIMING
	else {
		uint64 ctime;
		QueryProcessCycleTime(GetCurrentProcess(), &ctime);
		return (ctime/CyclesPerMSec);
	}
#endif
}

int time_to_stop(GSearchInfo * SI, int time, int searching) {
	if (Infinite) return 0;
	if (time > TimeLimit2) return 1;
	if (searching) return 0;
	if (2 * time > TimeLimit2 && F(MoveTime)) return 1;
	if (SI->Bad) return 0;
	if (time > TimeLimit1) return 1;
	if (T(SI->Change) || T(SI->FailLow)) return 0;
	if (time * 100 > TimeLimit1 * TimeNoChangeMargin) return 1;
	if (F(SI->Early)) return 0;
	if (time * 100 > TimeLimit1 * TimeNoPVSCOMargin) return 1;
	if (SI->Singular < 1) return 0;
	if (time * 100 > TimeLimit1 * TimeSingOneMargin) return 1;
	if (SI->Singular < 2) return 0;
	if (time * 100 > TimeLimit1 * TimeSingTwoMargin) return 1;
	return 0;
}

void check_time(int searching) {
#ifdef TUNER
	return;
#endif
	while (!Stop && input()) uci(1);
	if (Stop) goto jump;
	CurrTime = get_time();
	int Time = Convert(CurrTime - StartTime,int);
	if (T(Print) && Time > InfoLag && CurrTime - InfoTime > InfoDelay) {
		InfoTime = CurrTime;
		if (info_string[0]) {
			fprintf(stdout,"%s",info_string);
			info_string[0] = 0;
			fflush(stdout);
		}
	}
	if (time_to_stop(CurrentSI, Time, searching)) goto jump;
	return;
jump:
	Stop = 1;
	longjmp(Jump,1);
}

void check_time(int time, int searching) {
#ifdef TUNER
	return;
#endif
	while (!Stop && input()) uci(1);
	if (Stop) goto jump;
	CurrTime = get_time();
	int Time = Convert(CurrTime - StartTime,int);
	if (T(Print) && Time > InfoLag && CurrTime - InfoTime > InfoDelay) {
		InfoTime = CurrTime;
		if (info_string[0]) {
			fprintf(stdout,"%s",info_string);
			info_string[0] = 0;
			fflush(stdout);
		}
	}
	if (time_to_stop(CurrentSI, time, searching)) goto jump;
	return;
jump:
	Stop = 1;
	longjmp(Jump,1);
}

void check_state(int searching) {
	int best_id, best_height, best_score, best_n;
	int id, hr, height, n, score, move, value, new_depth, r_depth, ext, alpha, beta, pv;
	uint64 u;
	GMoveList * CML;
	GMove * CM;

start:
	if (TEST_RESET_BIT(SMPI->Info[Id].flags, STOP_ORDER)) longjmp(CheckJump, 1);
    if (TEST_RESET_BIT(SMPI->Info[Id].flags, FH_SIGNAL)) {
		for (hr = 0; hr < 1; hr++) for (u = SMPI->Info[Id].active_sp[hr]; T(u); Cut(u)) {
			height = lsb(u) + (hr << 6);
			CML = &SMPI->Info[Id].MoveList[height];
			if (F(CML->active) || F(CML->best_move) || CML->alpha < CML->beta) continue;
			LOCK(CML->lock);
			if (T(CML->active) && T(CML->best_move) && CML->alpha >= CML->beta) {
				UNLOCK(CML->lock);
				longjmp(CML->jump, 1);
			}
			UNLOCK(CML->lock);
		}
	}
	if (SMPI->Info[Id].flags & (1 << QUIT_ORDER)) exit(0);
	if (parent) return;
	if (searching) return;
	if (F(SMPI->Info[0].searching)) {
		Sleep(1);
		goto start;
	}

	while (T(SMPI->Info[0].searching) && F(SMPI->Info[Id - 1].searching)) _mm_pause();
	for (id = 0; id < Id; id++) if (F(SMPI->Info[id].searching)) goto start;

	best_id = 0;
	best_height = 0;
	best_score = 0;
	best_n = 0;
#ifdef CHILD_PROCESS_SPLIT
	for (id = 0; id < PrN; id++) {
		if (id == Id) continue;
#else
	for (id = 0; id < 1; id++) {
#endif
		for (hr = 0; hr < 1; hr++) {
			for (u = SMPI->Info[id].active_sp[hr]; T(u); Cut(u)) {
				height = lsb(u) + (hr << 6);
				CML = &SMPI->Info[id].MoveList[height];
				if (F(CML->active) || T(CML->lock) || CML->alpha >= CML->beta) continue;
				for (n = CML->current_master_position + 1; n < CML->move_number; n++)
					if (F(CML->move[n].flags & FlagClaimed)) break;
				if (n < CML->move_number - 1) score = 1024 * 1024 + 256 * 1024 * (CML->depth >= 20) + 128 * 1024 * F(CML->split)
					+((CML->depth + 2 * CML->singular) * 1024) - (((16 * 1024) * (n - CML->current_master_position))/n);
				else continue;
				if (score > best_score) {
					best_id = id;
					best_height = height;
					best_score = score;
					best_n = n;
				}
			}
		}
	}
    if (F(best_height)) {
		while (T(SMPI->Info[0].searching) && F(TEST_RESET_BIT(SMPI->Info[Id].flags,SPLIT_SIGNAL))) _mm_pause();
		goto start;
	}

	CML = &SMPI->Info[best_id].MoveList[best_height];
	if (F(CML->active) || CML->alpha >= CML->beta || T(CML->move[best_n].flags & FlagClaimed) || best_n >= CML->move_number || F(SMPI->Info[best_id].searching)) goto start;
	if (CML->lock) goto start;

	LOCK(CML->lock);
	if (F(CML->active) || CML->alpha >= CML->beta || T(CML->move[best_n].flags & FlagClaimed) || best_n >= CML->move_number || F(SMPI->Info[best_id].searching)) {
		UNLOCK(CML->lock);
		goto start;
	}

	CM = &CML->move[best_n];
	CM->flags |= FlagClaimed;
	CM->id = Id;
	move = CM->move;
	alpha = CML->alpha;
	beta = CML->beta;
	pv = CML->pv;
	new_depth = CM->reduced_depth;
	r_depth = CM->research_depth;
	ext = CM->ext;
#ifdef CUT_ALL
	pv_height = (T(CML->cut) ? (-1) : 0);
#endif
	retrieve_position(CML->position, 0);

	CML->split |= (1 << Id);
	SET(SMPI->Info[Id].searching, 1);
	UNLOCK(CML->lock);

	if (setjmp(CheckJump)) {
		halt_all(0, 127);
		SET(SMPI->Info[Id].searching, 0);
		return;
	}
	if (Current->turn == White) {
		do_move<0>(move);
		if (pv) {
			value = -search<1, 0>(-alpha, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value > alpha) value = -pv_search<1, 0>(-beta, -alpha, r_depth, ExtFlag(ext));
		} else {
		    value = -search<1, 0>(1 - beta, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value >= beta && new_depth < r_depth) value = -search<1, 0>(1 - beta, r_depth, FlagNeatSearch | FlagDisableNull | ExtFlag(ext));
		}
		undo_move<0>(move);
	} else {
		do_move<1>(move);
		if (pv) {
			value = -search<0, 0>(-alpha, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value > alpha) value = -pv_search<0, 0>(-beta, -alpha, r_depth, ExtFlag(ext));
		} else {
		    value = -search<0, 0>(1 - beta, new_depth, FlagNeatSearch | ExtFlag(ext));
		    if (value >= beta && new_depth < r_depth) value = -search<0, 0>(1 - beta, r_depth, FlagNeatSearch | FlagDisableNull | ExtFlag(ext));
		}
		undo_move<1>(move);
	}

	LOCK(CML->lock);
	SET(SMPI->Info[Id].searching, 0);
	if (TEST_RESET_BIT(SMPI->Info[Id].flags, STOP_ORDER)) {
		UNLOCK(CML->lock);
		return;
	}
	if (F(CM->flags & FlagFinished)) {
	    CM->value = value;
		CM->flags |= FlagFinished;
		if (value > CML->alpha) {
			CML->alpha = value;
			CML->best_move = move;
			if (value >= beta) SET_BIT(SMPI->Info[best_id].flags, FH_SIGNAL);
		}
	}
	UNLOCK(CML->lock);
}

void init_move_list(GMoveList * ML) {
	ML->active = 0;
	ML->best_move = 0;
	ML->current_master_position = 0;
	ML->move_number = 0;
	ML->singular = 0;
	ML->split = 0;
}

void send_position(GPosition * gp) {
	gp->sp = Min(sp, 127);
	memcpy(gp->stack, Stack + sp - gp->sp, (gp->sp + 1) * sizeof(uint64));
	memcpy(gp->Current, Current, sizeof(GData));
	memcpy(gp->Board, Board, sizeof(GBoard));
	gp->date = date;
	for (int i = 0; i < 16 && Current + i < Data + 126; i++) {
		gp->killer[i][0] = (Current + i + 1)->killer[1];
		gp->killer[i][1] = (Current + i + 1)->killer[2];
	}
}

void retrieve_position(GPosition * gp, int height) {
	Current = Data + height;
	memcpy(Current, gp->Current, sizeof(GData));
	memcpy(Board, gp->Board, sizeof(GBoard));
	memcpy(Stack, gp->stack, (gp->sp + 1) * sizeof(uint64));
	sp = gp->sp;
	date = Max(date, gp->date);
	for (int i = 0; i < 16 && Current + i < Data + 126; i++) {
		(Current + i + 1)->killer[1] = gp->killer[i][0];
		(Current + i + 1)->killer[2] = gp->killer[i][1];
	}
}

void halt_all(GMoveList * ML, int locked) {
	GMove * CM;
	if (F(locked)) LOCK(ML->lock);
	if (ML->active) {
		for (int i = 0; i < ML->move_number; i++) {
			CM = &ML->move[i];
			if (T(CM->flags & FlagClaimed) && F(CM->flags & FlagFinished) && CM->id != Id) SET_BIT(SMPI->Info[CM->id].flags, STOP_ORDER);
		}
	}
	ML->active = 0;
	CancelSP(Id,(int)(ML - SMPI->Info[Id].MoveList));
	if (F(locked)) UNLOCK(ML->lock);
}

void halt_all(int from, int to) { // All the optex involved should be unlocked
	GMoveList * CML;
	for (int hr = 0; hr < 1; hr++) for (uint64 u = SMPI->Info[Id].active_sp[hr]; T(u); Cut(u)) {
		int height = lsb(u) + (hr << 6);
		if (height >= from && height <= to) {
			CML = &SMPI->Info[Id].MoveList[height];
			halt_all(CML, 0);
		}
	}
}

int input() {
    DWORD p;
#ifdef LOCAL_TUNER
	return 0;
#endif
	if (F(Input)) return 0;
	if (F(Console)) {
	    if (PeekNamedPipe(StreamHandle,NULL,0,NULL,&p,NULL)) return (p > 0);
        else return 1;
	} else {
		GetNumberOfConsoleInputEvents(StreamHandle,&p);
        return (p > 1);
	}
}

void epd_test(char string[], int time_limit) {
	int i, n = 0, positions = 4000, AD = 0;
	uint64 Time, delta, all_nodes = 0, new_time, total_time;
	double time, av_depth, prod = 0.0;
	char * ptr; 
	FILE * f = fopen(string, "r");
	if (f == NULL) {
		fprintf(stdout,"File not found\n");
		return;
	}
	Infinite = 1;
	Time = get_time();
	int total_depth = 0;
	Print = 0;
	Input = 0;
	GPI = &SMPI->Info[0];
	total_time = 1;
	while (!feof(f) && n < positions) {
new_position:
		(void)fgets(input_string, 65536, f);
		ptr = strchr(input_string, '\n');
        if (ptr != NULL) *ptr = 0;
		get_board(input_string);
#ifdef DEBUG
		if (!test_eval())
			fprintf(stdout,"Assymetric eval\n");
#endif
		evaluate();
		if (Current->turn == White) {
			gen_legal_moves<0>();
		} else {
			gen_legal_moves<1>();
		}
		Infinite = 0;
		MoveTime = TimeLimit1 = 100000000;
#ifndef TIME_TO_DEPTH
		TimeLimit2 = time_limit;
#else
		TimeLimit2 = TimeLimit1;
#endif
		DepthLimit = 127;
		n++;
		Stop = 0;
		SMPI->total_nodes = nodes = check_node = check_node2 = 0;
		StartTime = get_time();
		if (setjmp(Jump)) {
			halt_all(0, 127);
stop_searching:
			SET(GPI->searching, 0);
			Searching = 0;
			Current = Data;
			new_time = get_time() - StartTime;
			total_time += new_time;
#ifdef MP_NPS
			all_nodes += SMPI->total_nodes;
#else
			all_nodes += nodes;
#endif
			total_depth += LastDepth/2;
#ifndef TIME_TO_DEPTH
			fprintf(stdout,"Position %d: %d [%lf, %d]\n",n,LastDepth/2,((double)total_depth)/((double)n),(all_nodes * Convert(1000,uint64))/total_time);
#else
			prod += log((double)new_time);
			fprintf(stdout,"Position %d: %d [%.0lf, %d]\n",n,new_time,exp(prod/(double)n),(all_nodes * Convert(1000,uint64))/total_time);
#endif
			goto new_position;
		}
		for (int d = 4; d < 128; d += 2) {
			LastDepth = d;
			GPI->searching = Searching = 1;
			if (Current->turn == White) {
				pv_search<0, 1>(-MateValue,MateValue,d,FlagNeatSearch);
			} else {
				pv_search<1, 1>(-MateValue,MateValue,d,FlagNeatSearch);
			}	
#ifdef TIME_TO_DEPTH
			if (d >= (time_limit * 2)) goto stop_searching;
#endif
		}
	}
	if (n == 0) {
		fprintf(stdout,"Empty file\n");
		return;
	}
	fclose(f);
}

void uci(int searching) {
    char *ptr = NULL;
	int i;
	sint64 value;

#ifdef TUNER
	int version = 1, key = 0, depth = 0, iter = 0, games = 0;
	double radius = 0.0, r = 0.0, Base[256], Grad[256], First[256], Second[256];
	for (i = 0; i < 256; i++) Base[i] = Grad[i] = First[i] = Second[i] = 0.0;
#ifndef LOCAL_TUNER
	fgets(input_string,65536,stdin);

	if (strstr(input_string,"quit") != NULL) exit(0);

	ptr = strstr(input_string,"version");
	if (ptr == NULL) return;
	if (version != atoi(ptr + 8)) {
		fprintf(stdout,"Version mismatch\n");
		exit(0);
	}

	ptr = strstr(input_string,"command") + 8;
    command = atoi(ptr);
	key = version * 16384 + command;

	ptr = strstr(input_string,"depth") + 6;
	depth = atoi(ptr);

	ptr = strstr(input_string,"var");
	for (i = 0; i < var_number; i++) {
		ptr = strchr(ptr,' ') + 1;
		Variables[IndexVar[i]].var = Max(0.0, atof(ptr));
	}

    ptr = strstr(input_string,"gradient");
	if (ptr == NULL) goto run_match;
calc_gradient:
	ptr = strstr(input_string,"iter")+5;
	iter = atoi(ptr);
	ptr = strstr(input_string,"radius")+7;
	radius = atof(ptr);
    ptr = strstr(input_string,"base");
	for (i = 0; i < var_number; i++) {
		ptr = strchr(ptr,' ') + 1;
		Base[i] = atof(ptr);
	}
	grad(depth,iter,1,radius,Base,Grad);
	memset(input_string,0,65536);
	for (i = 0; i < var_number; i++) sprintf(input_string+strlen(input_string),"%.4lf ",Grad[i]);
	sprintf(input_string+strlen(input_string),"%d",key);
	fprintf(stdout,"%s\n",input_string);
	return;
run_match:
	ptr = strstr(input_string,"match");
	if (ptr == NULL) return;
	ptr = strstr(input_string,"games") + 6;
	games = atoi(ptr);
	ptr = strstr(input_string,"first");
	for (i = 0; i < var_number; i++) {
		ptr = strchr(ptr,' ') + 1;
		First[i] = atof(ptr);
	}
	ptr = strstr(input_string,"second");
	for (i = 0; i < var_number; i++) {
		ptr = strchr(ptr,' ') + 1;
		Second[i] = atof(ptr);
	}
	r = match(First,Second,games,depth);
	fprintf(stdout,"%lf %d\n",r,key);
	return;
#else
	LOCK(TB->lock);
	if (F(TB->type)) {
		UNLOCK(TB->lock);
		Sleep(1);
		return;
	}
	command = TB->command;
	depth = TB->data_i[0];
	for (i = 0; i < var_number; i++) Variables[IndexVar[i]].var = TB->Var[i];
	if (TB->type != GRADIENT_COMMAND) goto run_match;
calc_gradient:
	iter = TB->data_i[1];
	radius = TB->data_d[0];
    ptr = strstr(input_string,"base");
	memcpy(Base,TB->Base,var_number * sizeof(double));
	UNLOCK(TB->lock);
	grad(depth,iter,1,radius,Base,Grad);
	LOCK(TB->lock);
	if (command == TB->command) {
	    memcpy(TB->feedback[Id].List,Grad,var_number * sizeof(double));
	    TB->feedback[Id].updated = 1;
	}
	UNLOCK(TB->lock);
	return;
run_match:
	games = TB->data_i[1];
	memcpy(First,TB->First,var_number * sizeof(double));
	memcpy(Second,TB->Second,var_number * sizeof(double));
	UNLOCK(TB->lock);
	r = match(First,Second,games,depth);
	LOCK(TB->lock);
	if (command == TB->command) {
		TB->feedback[Id].data_d[0] = r;
		TB->feedback[Id].data_i[0] = wins;
		TB->feedback[Id].data_i[1] = draws;
		TB->feedback[Id].data_i[2] = losses;
		TB->feedback[Id].updated = 1;
	}
	UNLOCK(TB->lock);
	return;
#endif
#endif

	if (child) {
		check_state(searching);
		return;
	}

    (void)fgets(input_string, 65536, stdin);
    if (feof(stdin)) exit(0);
    ptr = strchr(input_string, '\n');
    if (ptr != NULL) *ptr = 0;
    if (!strcmp(input_string, "uci")) {
#ifndef W32_BUILD
		fprintf(stdout,"id name Gull 2.3 x64\n");
#else
		fprintf(stdout,"id name Gull 2.3\n");
#endif
        fprintf(stdout,"id author ThinkingALot\n");
#ifdef W32_BUILD
		fprintf(stdout,"option name Hash type spin min 1 max 1024 default 128\n");
#else
		fprintf(stdout,"option name Hash type spin min 1 max 65536 default 128\n");
#endif
		fprintf(stdout,"option name Ponder type check default false\n");
		fprintf(stdout,"option name MultiPV type spin min 1 max 64 default 1\n");
		fprintf(stdout,"option name Clear Hash type button\n");
#ifdef CPU_TIMING
		fprintf(stdout,"option name CPUTime type check default false\n");
#endif
		fprintf(stdout,"option name Threads type spin min 1 max %d default %d\n",Min(CPUs, MaxPrN),PrN);
		fprintf(stdout,"option name PV Hash type check default true\n");
		fprintf(stdout,"option name Aspiration window type check default true\n");
#ifdef LARGE_PAGES
		fprintf(stdout,"option name Large memory pages type check default true\n");
#endif
        fprintf(stdout,"uciok\n");
		if (F(Searching)) init_search(1);
    } else if (!strcmp(input_string,"ucinewgame")) {
        Stop = 0;
		init_search(1);
    } else if (!strcmp(input_string,"isready")) {
        fprintf(stdout,"readyok\n");
		fflush(stdout);
    }  else if (!memcmp(input_string,"position",8)) {
        if (F(Searching)) get_position(input_string);
    } else if (!memcmp(input_string,"go",2)) {
        if (F(Searching)) get_time_limit(input_string);
    } else if (!memcmp(input_string,"setoption",9)) {
		ptr = strtok(input_string," ");
		for (ptr = strtok(NULL," "); ptr != NULL; ptr = strtok(NULL," ")) {
			if (!memcmp(ptr,"Hash",4) && F(Searching)) {
				ptr += 11;
				value = atoi(ptr);
				if (value < 1) value = 1;
#ifdef W32_BUILD
				if (value > 1024) value = 1024;
#else
				if (value > 65536) value = 65536;
#endif
				value = (Bit(msb(value)) * Convert(1024 * 1024, sint64))/Convert(sizeof(GEntry),sint64);
				if (value != hash_size) {
					reset_hash = 1;
					hash_size = value;
				    hash_mask = hash_size - 4;
				    longjmp(ResetJump, 1);
				}
			} else if (!memcmp(ptr,"Threads",7)) {
			    ptr += 14;
				value = atoi(ptr);
				if (value != PrN) {
					NewPrN = Max(1, Min(MaxPrN, value));
				    reset_hash = 0;
				    longjmp(ResetJump, 1);
				}
		    } else if (!memcmp(ptr,"MultiPV",7)) {
				ptr += 14;
			    PVN = atoi(ptr);
				Stop = 1;
			} else if (!memcmp(ptr,"Ponder",6)) {
				ptr += 13;
				if (ptr[0] == 't') Ponder = 1;
				else Ponder = 0;
			} else if (!memcmp(ptr,"Clear",5)) {
				init_search(1);
				break;
			} else if (!memcmp(ptr,"CPUTime",7)) {
				ptr += 14;
				if (ptr[0] == 't') CPUTime = 1;
				else CPUTime = 0;
			} else if (!memcmp(ptr,"PV",2)) {
				ptr += 14;
				if (ptr[0] == 't') PVHashing = 1;
				else PVHashing = 0;
			} else if (!memcmp(ptr,"Large",5)) {
				ptr += 25;
				if (ptr[0] == 't') {
					if (LargePages) return;
					LargePages = 1;
				} else {
					if (F(LargePages)) return;
					LargePages = 0;
				}
				reset_hash = 1;
				longjmp(ResetJump, 1);
			} else if (!memcmp(ptr,"Aspiration",10)) {
				ptr += 24;
				if (ptr[0] == 't') Aspiration = 1;
				else Aspiration = 0;
			}
        }
	} else if (!strcmp(input_string,"stop")) {
		Stop = 1;
		if (F(Searching)) send_best_move();
	} else if (!strcmp(input_string,"ponderhit")) {
		Infinite = 0;
		if (F(RootList->sort[1].move)) Stop = 1;
		if (F(CurrentSI->Bad) && F(CurrentSI->FailLow) && time_to_stop(BaseSI, LastTime, 0)) Stop = 1;
		if (F(Searching)) send_best_move();
	}
#ifdef HASH_READER
	else if (!strcmp(input_string,"print")) {
		fprintf(fhr,"-->%s\n",input_string);
		if (Current->turn) print_pos_info<1>();
		else print_pos_info<0>();
	} else if (!memcmp(input_string,"do",2)) {
		fprintf(fhr,"-->%s\n",input_string);
		if (*(input_string+3) == 'n') do_null();
		else {
		    int move = move_from_string(input_string + 3);
			if (Current->turn) do_move<1>(move);
			else do_move<0>(move);
		}
		if (Current->turn) print_pos_info<1>();
		else print_pos_info<0>();
	} else if (!strcmp(input_string,"undo")) {
		fprintf(fhr,"-->%s\n",input_string);
		if (Current->move) {
			if (Current->turn) undo_move<0>(Current->move);
			else undo_move<1>(Current->move);
		} else undo_null();
		if (Current->turn) print_pos_info<1>();
		else print_pos_info<0>();
	}
#endif
    else if (!strcmp(input_string,"quit")) {
#ifdef HASH_READER
		fclose(fhr);
#endif
#ifdef HASH_STORE
	    ofstream fstore;
	    fstore.open("GullHash.gsh", ofstream::binary);
		if (!fstore.fail()) {
	        fstore.write((char*)StoreHash,store_hash_size * sizeof(GStoreEntry));
	        fstore.close();
		}
#endif
		for (i = 1; i < PrN; i++) {
			SET_BIT(SMPI->Info[i].flags, QUIT_ORDER);
			TerminateProcess(ChildPr[i], 0);
			CloseHandle(ChildPr[i]);
		}
		exit(0);
	} else if (!memcmp(input_string,"epd",3)) {
		ptr = input_string + 4;
		value = atoi(ptr);
		epd_test("op.epd",value);
	}
}

#ifdef HASH_READER
template <bool me> void print_pos_info() {
	int i, move;

	evaluate();
	fprintf(stdout,"Score = %d, Key = 0x%X%X\n",Current->score,Current->key >> 32, Current->key & 0xFFFFFFFF);
	fprintf(fhr,"Score = %d, Key = 0x%X%X\n",Current->score,Current->key >> 32, Current->key & 0xFFFFFFFF);
	for (i = 0, PVEntry = PVHash + (High32(Current->key) & pv_hash_mask); i < pv_cluster_size; i++, PVEntry++) {
		if (PVEntry->key == Low32(Current->key)) {
			if (PVEntry->move) {
				move_to_string(PVEntry->move,pv_string);
				fprintf(stdout,"PV Entry [date=%d]: move=%s, value=%d(%d)\n",PVEntry->date,pv_string,PVEntry->value,PVEntry->depth);
				fprintf(fhr,"PV Entry [date=%d]: move=%s, value=%d(%d)\n",PVEntry->date,pv_string,PVEntry->value,PVEntry->depth);
			} else {
				fprintf(stdout,"PV Entry [date=%d]: move=0, value=%d, depth=%d\n",PVEntry->date,PVEntry->value,PVEntry->depth);
				fprintf(fhr,"PV Entry [date=%d]: move=0, value=%d, depth=%d\n",PVEntry->date,PVEntry->value,PVEntry->depth);
			}
		}
	}
	for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		if (Low32(Current->key) == Entry->key) {
			if (Entry->move) {
				move_to_string(Entry->move,pv_string);
				fprintf(stdout,"Entry [date=%d]: move=%s, low=%d(%d), high=%d(%d)\n",Entry->date,pv_string,Entry->low,Entry->low_depth,Entry->high,Entry->high_depth);
				fprintf(fhr,"Entry [date=%d]: move=%s, low=%d(%d), high=%d(%d)\n",Entry->date,pv_string,Entry->low,Entry->low_depth,Entry->high,Entry->high_depth);
			} else {
				fprintf(stdout,"Entry [date=%d]: move=0, low=%d(%d), high=%d(%d)\n",Entry->date,Entry->low,Entry->low_depth,Entry->high,Entry->high_depth);
				fprintf(fhr,"Entry [date=%d]: move=0, low=%d(%d), high=%d(%d)\n",Entry->date,Entry->low,Entry->low_depth,Entry->high,Entry->high_depth);
			}
		}
	}
	if (Current->att[opp] & King(me)) Current->stage = e_gen_ev;
	else Current->stage = s_gen_cap;
	while (move = get_move<me>()) {
		if (IsIllegal(Current->turn, move)) continue;
		move_to_string(move,pv_string);
		fprintf(stdout,"%s [Delta=%d, History=%d]: ",pv_string,DeltaM(move),History(From(move),To(move)) >> 16);
		fprintf(fhr,"%s [Delta=%d, History=%d]: ",pv_string,DeltaM(move),History(From(move),To(move)) >> 16);
		do_move<me>(move);
		evaluate();
		fprintf(stdout,"[s,ds=%d,%d]\n",-Current->score,-Current->score - ((Current - 1)->score));
		fprintf(fhr,"[s,ds=%d,%d]: ",-Current->score,-Current->score - ((Current - 1)->score));
		for (i = 0, Entry = Hash + (High32(Current->key) & hash_mask); i < 4; Entry++, i++) {
		    if (Low32(Current->key) == Entry->key) {
				fprintf(stdout,"[");
				if (Entry->high_depth) fprintf(stdout,">=%d(%d) ",-Entry->high,Entry->high_depth);
				if (Entry->low_depth) fprintf(stdout,"<=%d(%d) ",-Entry->low,Entry->low_depth);
				fprintf(stdout,"]");

				fprintf(fhr,"[");
				if (Entry->high_depth) fprintf(fhr,">=%d(%d) ",-Entry->high,Entry->high_depth);
				if (Entry->low_depth) fprintf(fhr,"<=%d(%d) ",-Entry->low,Entry->low_depth);
				fprintf(fhr,"]");
		    }
	    }
		undo_move<me>(move);
		fprintf(stdout,"\n");
		fprintf(fhr,"\n");
	}
}

void print_curr_line() {
	GData * I;
	for (I = Data + 1; I <= Current; I++) {
		move_to_string(I->move, pv_string);
		fprintf(stdout, "%s ", pv_string);
	}
	fprintf(stdout,"\n");
}
#endif

HANDLE CreateChildProcess(int child_id) {
	char name[1024];
    TCHAR szCmdline[1024];
    PROCESS_INFORMATION piProcInfo; 
    STARTUPINFO siStartInfo;
    BOOL bSuccess = FALSE; 
	SECURITY_ATTRIBUTES saAttr; 

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	ZeroMemory(szCmdline, 1024 * sizeof(TCHAR));
	ZeroMemory(name, 1024);

    siStartInfo.cb = sizeof(STARTUPINFO); 
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	GetModuleFileName(NULL,name,1024);
	sprintf(szCmdline," child %d %d",WinProcId,child_id);
    
    bSuccess = CreateProcess(TEXT(name), TEXT(szCmdline), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo);
   
    if (bSuccess) {
        CloseHandle(piProcInfo.hThread);
	    return piProcInfo.hProcess;
    } else {
		fprintf(stdout,"Error %d\n",GetLastError());
		return NULL;
	}
}

void main(int argc, char *argv[]) {
	DWORD p;
	int i, j, HT = 0;
	HANDLE GSMPI_H;
	SYSTEM_INFO sysinfo;
	char name[256];

	int CPUInfo[4] = {-1};
    __cpuid(CPUInfo, 1);
    HardwarePopCnt = (CPUInfo[2] >> 23) & 1;

#ifdef TUNER
	parent = 1;
	child = 0;
	init();
	save_list(DefaultEval);
	save_list(BestEval);
	save_var(VarBase);
	save_var(VarMax);
	srand(time(NULL) + 123 * GetProcessId(GetCurrentProcess()));
	seed = (uint64)(time(NULL) - 123 * GetProcessId(GetCurrentProcess()));
#ifndef LOCAL_TUNER
	StreamHandle = GetStdHandle(STD_INPUT_HANDLE);
	Console = GetConsoleMode(StreamHandle,&p);
	if (Console) {
		SetConsoleMode(StreamHandle,p & (~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT)));
		FlushConsoleInputBuffer(StreamHandle);
	}
	SetPriorityClass(GetCurrentProcess(),IDLE_PRIORITY_CLASS);

	init_hash();
	init();
	init_search(1);

	setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    fflush(NULL);

#ifdef RECORD_GAMES
	FILE * fgames = fopen("games.txt","w");
	fclose(fgames);
#endif

	goto uci_loop;
#endif
#endif

	child = 0;
	if (argc >= 2) if (!memcmp(argv[1],"child",5)) {
		child = 1;
	    WinParId = atoi(argv[2]);
		Id = atoi(argv[3]);
		WinProcId = GetProcessId(GetCurrentProcess());
	}
	parent = child ^ 1;

	if (parent) {
		if (T((CPUInfo[3] >> 28) & 1) && GetProcAddress(GetModuleHandle(TEXT("kernel32")),"GetLogicalProcessorInformation") != NULL) {
		    SYSTEM_LOGICAL_PROCESSOR_INFORMATION syslogprocinfo[1];
		    p = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
#ifndef W32_BUILD
		    GetLogicalProcessorInformation(syslogprocinfo, &p);
		    if (syslogprocinfo->ProcessorCore.Flags == 1) HT = 1;
#endif
		}
		WinProcId = WinParId = GetProcessId(GetCurrentProcess());
		Id = 0;
	}

	if (parent) {
		HANDLE JOB = CreateJobObject(NULL, NULL);
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = {0};
		jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
		SetInformationJobObject(JOB, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));
		AssignProcessToJobObject(JOB, GetCurrentProcess());
	} 
#ifndef CPU_TIMING
	else 
#endif
		SetPriorityClass(GetCurrentProcess(),IDLE_PRIORITY_CLASS);

	if (MaxPrN > 1) {
	    GetSystemInfo(&sysinfo);
	    CPUs = sysinfo.dwNumberOfProcessors;
		PrN = Min(CPUs, MaxPrN);
		if (HT) PrN = Max(1, Min(PrN, CPUs/2));
		if (CPUs & 1) j = Id;
		else j = Id * 2;
		if (j >= CPUs) j = (j + 1) % CPUs;
	    if (PrN > 1) SetProcessAffinityMask(GetCurrentProcess(), (1 << Min(j, CPUs - 1)));
	}

	sprintf(name,NAME_SHARED"_%d",WinParId);
#ifndef LOCAL_TUNER
	if (parent) GSMPI_H = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(GSMPInfo), name);
	else GSMPI_H = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	SMPI = (GSMPInfo*)MapViewOfFile(GSMPI_H,FILE_MAP_ALL_ACCESS,0,0,sizeof(GSMPInfo));
	if (parent) {
		memset(SMPI, 0, sizeof(GSMPInfo));
	    SMPI->hash_size = hash_size;
		SMPI->PrN = PrN;
	}
#else
	HANDLE GTB_H;
	if (parent) GTB_H = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(GTunerBuffer), name);
	else GTB_H = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	TB = (GTunerBuffer*)MapViewOfFile(GTB_H,FILE_MAP_ALL_ACCESS,0,0,sizeof(GTunerBuffer));
	if (parent) memset(TB, 0, sizeof(GTunerBuffer));
#endif

#ifndef TUNER
	init();
#endif

#ifndef LOCAL_TUNER
set_reset:
	if (T(parent)) {
		if (setjmp(ResetJump)) {
		    halt_all(0, 127);
		    SET(SMPI->Info[Id].searching, 0);
wait_for_all_processes:
			for (i = 1; i < PrN; i++) if (SMPI->Info[i].searching) break;
			if (i < PrN) {
				Sleep(1);
				goto wait_for_all_processes;
			}
			for (i = 1; i < PrN; i++) {
				SET_BIT(SMPI->Info[i].flags, QUIT_ORDER);
				TerminateProcess(ChildPr[i], 0);
			}
		    for (i = 1; i < PrN; i++) {
				WaitForSingleObject(ChildPr[i], INFINITE);
				CloseHandle(ChildPr[i]);
			}
			for (i = 0; i < MaxPrN; i++) {
				SMPI->Info[i].searching = 0;
				SMPI->Info[i].flags = 0;
				for (j = 0; j < 128; j++) {
					SMPI->Info[i].MoveList[j].active = 0;
					SMPI->Info[i].MoveList[j].lock = 0;
				}
			}
	        SMPI->hash_size = hash_size;
			if (NewPrN) PrN = NewPrN;
			SMPI->PrN = PrN;
			if (PrN > 1) SetProcessAffinityMask(GetCurrentProcess(), 1);
			else SetProcessAffinityMask(GetCurrentProcess(), (1 << CPUs) - 1);
			goto set_reset;
		}
	}

	if (child) {
		hash_size = SMPI->hash_size;
		PrN = SMPI->PrN;
	}
#endif

	if (T(child) || T(reset_hash)) init_hash();
	init_search(reset_hash);

#ifndef LOCAL_TUNER
	if (parent) for (i = 1; i < PrN; i++) ChildPr[i] = CreateChildProcess(i);
#else
	if (parent) for (i = 0; i < PrN; i++) ChildPr[i] = CreateChildProcess(i);
#endif

#ifdef HASH_READER
	fhr = fopen("GHR.txt", "w");
#endif
	
	if (T(parent) && F(init_cnt)) {
	    StreamHandle = GetStdHandle(STD_INPUT_HANDLE);
	    Console = GetConsoleMode(StreamHandle,&p);
	    if (Console) {
		    SetConsoleMode(StreamHandle,p & (~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT)));
		    FlushConsoleInputBuffer(StreamHandle);
	    }

	    setbuf(stdout, NULL);
        setbuf(stdin, NULL);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stdin, NULL, _IONBF, 0);
        fflush(NULL);
#ifndef W32_BUILD
		fprintf(stdout,"Gull 2.3 x64\n");
#else
		fprintf(stdout,"Gull 2.3\n");
#endif
	}
	init_cnt++;

#ifdef LOCAL_TUNER
	if (child) goto uci_loop;
	fprintf(stdout,"Local tuner\n");

#ifdef MAT_STAT
	MaterialStat(7,512);
#endif

	//get_list(BestEval,"(-19,29,-54,37,2,112,49,91,-11,-24,-13,-186,-24,45,147,129,138,-431,-165,-177,-205,-87,-203,-155,-97,-58,99,-42,-63,161,-230,-85,291,170,-211,-86,-108,-77,-17,-89,-150,-39,-103,48,97,21,-6,-60,-127,-75,-143,206,182,589,-56,-21,-44,-41,12,-103,28,-97,-69,16,40,-17,110,8,-22,129,-56,105,-101,-106,-11,57,-26,-70,39,-243,-63,83,13,205,-16,-156,-76,431,2393,1559,69,95,5,11,7,0,3,4,8,0,8,0,5,0,6,4,5,2,2,3,2,4,-5,10,2,11,4,0,9,8,16,-16,20,17,21,7,9,0,5,11,18,10,8,-1,5,6,-1,2,1,5,3,5,1,6,5,5,0,2,14,18,13,15,4,-6,0,6)");
	//copy_list(DefaultEval,BestEval);

	/*double NewVar[256];
	EstimateVar(2,128,30.0,100.0,VarMax,VarBase,NewVar);
	load_var(NewVar);*/

	get_var("(56.09,84.47,141.12,229.13,85.35,112.90,179.70,180.83,27.50,40.52,56.12,83.91,76.36,92.98,115.68,158.75,363.74,538.58,41.82,79.50,125.01,248.96,36.86,86.87,139.80,235.13,36.55,51.67,108.30,148.53,42.98,74.40,188.68,226.41,719.90,927.40,43.27,63.13,145.10,165.67,37.31,59.50,113.83,189.40,40.66,45.45,127.12,158.15,32.88,38.57,113.08,149.82,1000.00,1000.00,39.20,43.78,138.36,153.70,68.42,59.46,243.39,192.68,21.05,25.11,68.90,98.91,68.41,53.28,75.02,103.66,1000.00,1000.00,38.29,123.10,137.89,454.69,40.73,105.85,128.23,409.58,39.64,104.44,114.32,303.80,37.49,104.67,142.04,411.95,1000.00,1000.00,20.00,11.38,1.91,2.67,3.06,4.11,5.79,5.69,10.00,10.00,10.00,10.00,10.00,10.00,1.00,1.00,0.85,1.00,0.64,0.80,0.66,1.00,19.67,20.00,20.00,20.00,4.46,6.94,3.43,4.54,10.00,10.00,6.06,7.99,10.00,10.00,10.00,10.00,10.00,10.00,10.00,10.00,10.00,10.00,9.67,6.60,3.20,5.13,4.73,7.11,2.77,4.36,7.27,7.54,7.11,7.60,9.07,10.00,5.30,4.47,10.00,10.00,22.02,107.66,100.87,118.05,210.38,261.18,500.00,243.71,500.00,293.82,500.00,500.00,470.77,500.00,202.84,53.80,50.16,65.94,148.17,500.00,166.44,168.23,500.00,500.00,232.10,500.00,500.00,500.00,500.00)");
	save_var(VarBase);

	//calibrate(1024,20.0);

	GD(6,256 * 1024,4,60.0,64 * 1024,0.0,2.0,2.0,1.0,2.0,7.0);

	double New[256], score;
	int played;
	get_list(New,"(-36,20,-73,-146,-2,107,29,61,-3,-16,-1,-164,-31,78,117,170,204,-493,-163,-193,-182,-79,-194,-145,-109,-41,106,-30,-30,121,-213,-81,151,215,-22,60,-103,-91,-59,-86,-162,-43,-89,19,93,13,-25,-35,-117,-93,-109,191,192,771,-74,-9,-62,13,0,-96,82,-124,-57,17,32,4,110,18,-29,151,-308,293,-117,-132,-40,63,-17,-68,27,-266,-71,43,0,197,-8,-100,-71,525,1901,2020,68,100,4,11,5,2,6,4,13,1,10,5,4,9,6,3,5,3,2,3,1,3,-6,15,3,17,5,0,8,10,10,0,20,15,19,4,7,-1,9,17,14,12,8,1,11,3,0,0,1,9,2,6,1,2,5,4,1,3,13,16,12,11,-2,21,20,14,-12,57,80,4,100,-29,-50,-10,122,-20,4,-1,-3,-3,23,70,6,16,10,30,-23,70,-50,10,20)");
	for (i = 3; i < 64; i++) {
		fprintf(stdout,"depth = %d/%d\n",i,i+1);
		//score = match_smp(New,BestEval,64 * 1024,i);
		match_los(New,BestEval,128,16 * 1024,i,0.0,2.5,2.5,1000.0,&played,&score);
		//score = match(New,BestEval,128,i);
		fprintf(stdout,"%lf\n",score);
	}

	getchar();
#endif

uci_loop:
	while (1) uci(0);
}