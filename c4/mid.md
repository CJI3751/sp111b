簡介 -- C4 編譯器
=============================================================
C4 是 Robert Swierczek 寫的一個小型 C 語言編譯器，全部 527 行的原始碼都在 c4.c 裏 。

C4 編譯完成後，會產生一種《堆疊機機器碼》放在記憶體內，然後 虛擬機 會立刻執行該機器碼。

以下是 C4 編譯器的用法，C4 可以進行《自我編譯》:

    gcc -m32 -o c4 c4.c  (you may need the -m32 option on 64bit machines)
    ./c4 test/hello.c
    ./c4 -s test/hello.c

    ./c4 c4.c test/hello.c
    ./c4 c4.c c4.c test/hello.c
C4 在 Windows / Linux / MAC 中都可以執行，在 windows 必須在有支援 open, read 這些 POSIX 檔案函式庫環境下才能編譯！

## C4的特色
支援三種類型：INT（整數）、CHAR（字元）和PTR（指標，指向INT或CHAR）。\
支援if-else條件語句和while循環語句。\
支援列舉類型。\
變數宣告時不得賦值。\
區域變數宣告必須在函數內的最開頭位置。\
單遍編譯器（single-pass compiler）。\
最後生成虛擬機的代碼。
## 編譯器的編譯流程
### 一般編譯器的編譯流程可以分為以下幾個主要步驟：

*詞彙分析（Lexical Analysis）：該步驟將原始程式碼拆解成一系列的詞彙符號（tokens），例如關鍵字、運算子、識別字、常數等。同時，詞彙分析器也會去除不必要的空格、註解等，並將詞彙符號傳遞給下一個階段。

*語法分析（Syntax Analysis）：該步驟使用詞彙符號構建程式的語法結構，例如使用文法規則和語法分析器（parser）將詞彙符號組成語法樹（syntax tree）或抽象語法樹（abstract syntax tree，AST）。語法分析檢查程式的語法是否合法並生成中間表示形式。

*語意分析（Semantic Analysis）：該步驟對中間表示形式進行語意檢查和轉換。它包括類型檢查、符號表建立、作用域解析等。語意分析器會確保程式符合語言的規則和語意，並生成適當的中間表示形式。

*中間碼生成（Intermediate Code Generation）：該步驟將語法分析或語意分析產生的中間表示形式轉換為低階的中間碼表示形式。中間碼通常是一種較抽象且與特定硬體平台無關的表示形式，例如三地址碼、四地址碼、虛擬機器碼等。

*最佳化（Optimization）：該步驟對中間碼進行各種優化技術的應用，以改進程式的效能、執行速度或程式碼大小。最佳化技術包括常量摺疊、死碼消除、循環展開、指令調度等。

*目標碼生成（Code Generation）：該步驟將最佳化的中間碼轉換為目標平台的機器碼表示形式，這是特定硬體平台所能執行的指令。目標碼生成器會進行暫存器分配、指令選擇、指令排程等操作，以生成最終的機器碼。

*連結（Linking）：如果程式包含多個檔案，則連結器將這些檔案中的目標碼結合在一起，解析符號引用並生成可執行檔或動態連結庫。連結器還處理外部函式庫的鏈接，以確保程式能夠正確執行。
### C4編譯器的編譯流程
1.接收原始程式碼：編譯器接收使用者提供的原始程式碼作為輸入。

2.創建符號表：編譯器創建一個符號表，用於記錄變數、函數、類別等符號的定義和屬性。

3.詞法分析（Lexical Analysis）：編譯器從原始程式碼中逐個讀取字符，識別出不同的詞法單元（tokens），例如關鍵字、識別符、運算符等。同時，它也會檢查和捕獲基本的語法錯誤。

4.語法分析（Syntax Analysis）：編譯器根據詞法分析器生成的詞法單元序列，進行語法分析。它使用文法規則和語法規則來確定程式碼的結構是否合法，並構建一棵語法樹（parse tree）或抽象語法樹（abstract syntax tree，AST）。

5.語意分析（Semantic Analysis）：在語法分析的過程中，編譯器同時進行語意分析。它檢查變數和函數的聲明和使用是否合法，進行類型檢查，並執行其他語意相關的檢查。此階段也可能進行符號解析，以確定符號的實際內容。

6.目標碼生成（Code Generation）：編譯器根據語法分析和語意分析的結果，生成目標程式碼。這包括將高級語言的表示轉換為低級語言（如組合語言或機器語言），並生成相應的目標文件或可執行文件。
## C4 支援的語法

項目 | 語法
-----|-------------------
判斷 | if ... else
迴圈 | while (...)
區塊 | {...}
函數呼叫 | f()
函數定義 | int f(....)
傳回值 | return 
陣列存取 | a[i] 
數學運算 | +-*/%, ++, --, +=, -=, *=, /=, %=
位元運算 | &|^~
邏輯運算 |  ! && || 
列舉 | enum ...
運算式 | (a*3+5)/b 
指定 | x = (a*3+5)/b
取得大小 | sizeof
強制轉型 | (int*) ptr; (char) a;
基本型態 | int, char
指標 | *ptr 
遞迴 | int f(n) { ... return f(n-1) + f(n-2); }
陣列存取 | a[i]

## 沒有支援的語法

C4 編譯器並沒有支援下列語法:

項目 | 語法
-----|-------------------
結構 | struct
設定初值 | int a=3; int arr = {1,2,3}
巨集 | #define LEN 100
宣告陣列 | int a[10];

## 忽略的語法

而對於引入標頭檔， C4 會忽略這些指令，但是預設已經引入了像 printf 之類的函式庫。

項目 | 語法
-----|-------------------------------
引入標頭檔 | `#include <stdio.h>`
## C4 編譯器的使用方式

用 gcc 編譯 C4

```
$ gcc -m32 c4.c -o c4
```

# C4的虛擬機

C4 編譯完成後，會立刻執行編譯出來的機器碼 (中介虛擬機)，該機器碼包含以下高階指令 (透過呼叫 C 語言函數完成) :

```
指令   意義                              實作

OPEN: open                              a = open((char *)sp[1], *sp);
READ: read                              a = read(sp[2], (char *)sp[1], *sp);
CLOS: close                             a = close(*sp);
PRTF: printf                            t = sp + pc[1]; a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);
MALC: malloc                            a = (int)malloc(*sp);
FREE: free                              free((void *)*sp);
MSET: memset                            a = (int)memset((char *)sp[2], sp[1], *sp);
MCMP: memcmp                            a = memcmp((char *)sp[2], (char *)sp[1], *sp);
```

透過這些高階指令， c4 就不需要自行處理《記憶體、輸出入、檔案》等事項，而是將這些工作轉交 C 語言函式庫來處理。

C4 的虛擬機是一種堆疊機，包含累積器 a, 堆疊暫存器 sp, 框架暫存器 bp 。其中所有 +-*/ 等運算幾乎都是對 a 進行的，而 bp 則可被用來存取區域變數。

該堆疊機除了上述的高階指令外，還包含以下機器指令：

```
指令   意義                                                    實作

LEA : load local address 載入區域變數                          a = (int)(bp + *pc++); 
IMM : load global address or immediate 載入全域變數或立即值     a = *pc++;
JMP : jump               躍躍指令                              pc = (int *)*pc;
JSR : jump to subroutine 跳到副程式                            *--sp = (int)(pc + 1); pc = (int *)*pc;
BZ  : branch if zero     if (a==0) goto m[pc]                 pc = a ? pc + 1 : (int *)*pc;
BNZ : branch if not zero if (a!=0) goto m[pc]                 pc = a ? (int *)*pc : pc + 1;
ENT : enter subroutine   進入副程式                            *--sp = (int)bp; bp = sp; sp = sp - *pc++;
ADJ : stack adjust       調整堆疊                              sp = sp + *pc++;
LEV : leave subroutine   離開副程式                            sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;
LI  : load int           載入整數                              a = *(int *)a;
LC  : load char          載入字元                              a = *(char *)a;
SI  : store int          儲存整數                              *(int *)*sp++ = a;
SC  : store char         儲存字元                              a = *(char *)*sp++ = a;
PSH : push               推入堆疊                              *--sp = a;
OR  : a = a OR pop       pop 代表從堆疊中取出一個元素           a = *sp++ |  a;
XOR : a = a XOR pop                                           a = *sp++ ^  a;
AND : a = a AND pop                                           a = *sp++ &  a;
EQ : a = a EQ pop                                             a = *sp++ == a;
NE : a = a NE pop                                             a = *sp++ != a;
LT : a = a LT pop                                             a = *sp++ <  a;
GT : a = a GT pop                                             a = *sp++ >  a;
LE : a = a LE pop                                             a = *sp++ <= a;
GE : a = a GE pop                                             a = *sp++ >= a;
SHL : a = a SHL pop                                           a = *sp++ << a;
SHR : a = a SHR pop                                           a = *sp++ >> a;
ADD : a = a ADD pop                                           a = *sp++ +  a;
SUB : a = a SUB pop                                           a = *sp++ -  a;
MUL : a = a MUL pop                                           a = *sp++ *  a;
DIV : a = a DIV pop                                           a = *sp++ /  a;
MOD : a = a MOD pop                                           a = *sp++ %  a;
EXIT : 終止離開                                                return *sp;
```
## op的簡單描述
| Opcode	 | Fully Name |Description|
| --- | --- |---|
|LEA|	                   Load Effective Address	                                            |利用 bp 將相對位址存入暫存器 a|
|IMM|	                   Immediate Value	將 immediate value or global address                |存入暫存器 a|
|JMP|	                   Jump	                                                                |跳轉至目標指令的絕對位址|
|JSR|	                   Jump to SubRoutine	                                                |將返回地址推入堆疊(sp)並跳轉(JMP)|
|BZ|	                   Branch if Zero	                                                    |後面接的是目標指令的絕對位址|
|BNZ|	                   Branch if NOT Zero	                                                |後面接的是目標指令的絕對位址|
|ENT|	                   Enter SubRoutine	                                                    |將 bp 推入堆疊並且 bp 指向 sp，sp 會預留局部變數的位置|
|ADJ|	                   Stack Adjust	                                                        |根據目前 sp 的相對位置|
|LEV|	                   Leave SubRoutine	                                                    |sp=bp, bp points to old bp, 讀取 return address to pc, sp++釋放空間|
|LI|	                   Load INT	                                                            |將暫存器 a 所指的位址取值，存入暫存器 a|
|LC|	                   Load CHAR                                                            |將暫存器 a 所指的位址取值，存入暫存器 a|
|SI|                       Store INT	                                                        |將暫存器 a 取值，存入 stack frame sp 所指的位址，然後 sp++|
|SC|                       Store CHAR	                                                        |將暫存器 a 取值，存入 stack frame sp 所指的位址，然後 sp++，最後再存入暫存器 a|
|PSH|                      Push into Stack Frame	                                            |將暫存器 a 的值 push into Stack Frame|
|OR-MODE|                  Arithmetic operation	                                                |從堆疊框架中彈出值，與暫存器的值進行計算，然後將結果還原到暫存器中。|
|OPEN-MEMCMP|	           System Call	                                                        |使用 Stack Frame sp 當作參數傳遞，並且 pop Stack|
|EXIT|	                   exit program	                                                        |利用 Stack Frame sp 當作回傳值|

*sp：stack frame。
*a：register 暫存器。
*bp：概念跟 rbp(32 bits)/ebp(64 bits) 相同。
*pc：program counter，指向當前指令。

## 程式碼解析
### Tokens
```
// tokens and classes (operators last and in precedence order)
 enum {
   Num = 128, Fun, Sys, Glo, Loc, Id,
   Char, Else, Enum, If, Int, Return, Sizeof, While,
   Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt,  Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
 };
```
定義了一個列舉(enum)結構，用於表示不同的 tokens (符號) 和 classes (類別)。列舉是一種用來定義一組有名稱的整數常數的方式。
在這個列舉中，tokens 和 classes 被賦予了特定的數值，這些數值用於區分不同的符號或類別，方便進行相關操作和判斷。

### Opcode
```
 // opcodes
 enum { LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
        OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
        OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT };
```
### Types
```
// types
enum { CHAR, INT, PTR };
```
只支援三種型態

### Symbol Table
```
// identifier offsets (since we can't create an ident struct)
enum { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };
```
由於 c4 不支援 struct，因此使用 enum 來定義 symbol table

### Initialization
```
poolsz = 256*1024; // arbitrary size
if (!(sym = malloc(poolsz))) { printf("could not malloc(%d) symbol area\n", poolsz); return -1; } // 符號段
if (!(le = e = malloc(poolsz))) { printf("could not malloc(%d) text area\n", poolsz); return -1; } // 程式段
if (!(data = malloc(poolsz))) { printf("could not malloc(%d) data area\n", poolsz); return -1; } // 資料段
if (!(sp = malloc(poolsz))) { printf("could not malloc(%d) stack area\n", poolsz); return -1; }  // 堆疊段

memset(sym,  0, poolsz);
memset(e,    0, poolsz);
memset(data, 0, poolsz);
```
Symbol Table and Stack Frame 的大小都是 256KB。
###Keywords
```
p = "char else enum if int return sizeof while "
 "open read close printf malloc free memset memcmp exit void main";
i = Char; while (i <= While) { next(); id[Tk] = i++; } // add keywords to symbol table
```
根據 enum 從 Char 到 While 一一加入 symbol table 中。在 next() function 中 id 將會指到 sym.
```
id = sym;
```
另外，next() function 是根據 p 所指的 String 做 parsing token 的動作。
```
while (tk = *p)
```
### next() : Lexical Analyzer
```
    else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_') {
       pp = p - 1;
       while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
         tk = tk * 147 + *p++;
       tk = (tk << 6) + (p - pp);
       id = sym;
       while (id[Tk]) {
         if (tk == id[Hash] && !memcmp((char *)id[Name], pp, p - pp)) { tk = id[Tk]; return; }
         id = id + Idsz;
       }
       id[Name] = (int)pp;
       id[Hash] = tk;
       tk = id[Tk] = Id;
       return;
    }
```
這段是主要處理 Keywords。第一步先算出該 token 的 hash value，然後利用 hash value and name 找尋 symbol table，如果有找到就回傳該 token enum value；如果找不到就新增 id(symbol)，並且設定 token enum value 為 Id(133)。這邊最容易混淆的是 tk 這個 variable：在進入此 code block 之前，tk=*p；然後在算 hash value 的時候，tk 代表的是 hash value；最後要 return 前，tk 紀錄的是 token enum value。

```
  p = "char else enum if int return sizeof while "
      "open read close printf malloc free memset memcmp exit void main";
  i = Char; while (i <= While) { next(); id[Tk] = i++; } // add keywords to symbol table
```
從 next() 新增 id(symbol) 之後，會再重新設定 token enum value。

```
  i = OPEN; while (i <= EXIT) { next(); id[Class] = Sys; id[Type] = INT; id[Val] = i++; } // add library to symbol table
```
處理 system call library，從 next() 新增 id(symbol) 之後，再設定 token class, type, and value。

```
  next(); id[Tk] = Char; // handle void type
  next(); idmain = id; // keep track of main
```
處理 void and main keyword，另外使用 idmain 紀錄 main `在 symbol table 的位置。

```
  if (!(lp = p = malloc(poolsz))) { printf("could not malloc(%d) source area\n", poolsz); return -1; }
  if ((i = read(fd, p, poolsz-1)) <= 0) { printf("read() returned %d\n", i); return -1; }
  p[i] = 0; // 設定程式 p 字串結束符號 \0
  close(fd);
```
讀取 source code 到 p(lp=p) 所指的位址，並且關閉 FD。

```
     else if (tk >= '0' && tk <= '9') {
       if (ival = tk - '0') { while (*p >= '0' && *p <= '9') ival = ival * 10 + *p++ - '0'; }
       else if (*p == 'x' || *p == 'X') {
         while ((tk = *++p) && ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
           ival = ival * 16 + (tk & 15) + (tk >= 'A' ? 9 : 0);
       }
       else { while (*p >= '0' && *p <= '7') ival = ival * 8 + *p++ - '0'; }
       tk = Num;
       return;
     }
```
這三個條件分別處理的是十進位、十六進位、八進位。回傳計算後的 ival and tk=Num

```
     else if (tk == '/') {
       if (*p == '/') {
         ++p;
         while (*p != 0 && *p != '\n') ++p;
       }
      else {
        tk = Div;
        return;
      }
    }
```
這段是處理 Div(/) or comment(//)，回傳tk=Div。

```
    else if (tk == '\'' || tk == '"') {
      pp = data;
      while (*p != 0 && *p != tk) {
        if ((ival = *p++) == '\\') {
          if ((ival = *p++) == 'n') ival = '\n';
        }
        if (tk == '"') *data++ = ival;
      }
      ++p;
      if (tk == '"') ival = (int)pp; else tk = Num;
      return;
    }
```
主要是處理 String，並且將字串存入 data section 中。回傳 data 起始位置 ival = (int)pp;，如果 tk=" 將 token 設為 Num，tk=Num。

```
    else if (tk == '=') { if (*p == '=') { ++p; tk = Eq; } else tk = Assign; return; }
    else if (tk == '+') { if (*p == '+') { ++p; tk = Inc; } else tk = Add; return; }
    else if (tk == '-') { if (*p == '-') { ++p; tk = Dec; } else tk = Sub; return; }
    else if (tk == '!') { if (*p == '=') { ++p; tk = Ne; } return; }
    else if (tk == '<') { if (*p == '=') { ++p; tk = Le; } else if (*p == '<') { ++p; tk = Shl; } else tk = Lt; return; }
    else if (tk == '>') { if (*p == '=') { ++p; tk = Ge; } else if (*p == '>') { ++p; tk = Shr; } else tk = Gt; return; }
    else if (tk == '|') { if (*p == '|') { ++p; tk = Lor; } else tk = Or; return; }
    else if (tk == '&') { if (*p == '&') { ++p; tk = Lan; } else tk = And; return; }
    else if (tk == '^') { tk = Xor; return; }
    else if (tk == '%') { tk = Mod; return; }
    else if (tk == '*') { tk = Mul; return; }
    else if (tk == '[') { tk = Brak; return; }
    else if (tk == '?') { tk = Cond; return; }
    else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' || tk == '(' || tk == ')' || tk == ']' || tk == ',' || tk == ':') return;
```
Operator 的部分會轉成 token enum value，其他符號的部分就直接依照 ASCII Code 回傳。

## expr(), stmt() : Syntax Analyzer + Semantic Analyzer + CodeGen
### expr()
分成兩個部分：第一部分利用 recursive descent (parsing)，檢查 symbol table (semantic Analyzer)，直接產生 IR (Code Generator)；如果有需要就會進行第二部分，Operator precedence (parsing)，主要處理四則運算。

第一部分
```
    if (!tk) { printf("%d: unexpected eof in expression\n", line); exit(-1); }
```
第二部分
```
  while (tk >= lev)
```
Num 數字處理
```
    else if (tk == Num) { *++e = IMM; *++e = ival; next(); ty = INT; }
```
String 字串處理
```
     else if (tk == '"') {
       *++e = IMM; *++e = ival; next();
       while (tk == '"') next();
       data = (char *)((int)data + sizeof(int) & -sizeof(int)); ty = PTR;
     }
```
Sizeof Operator
```
     else if (tk == Sizeof) {
       next(); if (tk == '(') next(); else { printf("%d: open paren expected in sizeof\n", line); exit(-1); }
       ty = INT; if (tk == Int) next(); else if (tk == Char) { next(); ty = CHAR; }
       while (tk == Mul) { next(); ty = ty + PTR; }
       if (tk == ')') next(); else { printf("%d: close paren expected in sizeof\n", line); exit(-1); }
       *++e = IMM; *++e = (ty == CHAR) ? sizeof(char) : sizeof(int);
       ty = INT;
     }
```
變數處理
```
else if (tk == Id) {
    d = id; next();
    if (tk == '(') {
      next();
      t = 0;
      while (tk != ')') { expr(Assign); *++e = PSH; ++t; if (tk == ',') next(); }
      next();
      if (d[Class] == Sys) *++e = d[Val];
      else if (d[Class] == Fun) { *++e = JSR; *++e = d[Val]; }
      else { printf("%d: bad function call\n", line); exit(-1); }
      if (t) { *++e = ADJ; *++e = t; }
      ty = d[Type];
    }
    else if (d[Class] == Num) { *++e = IMM; *++e = d[Val]; ty = INT; }
    else {
      if (d[Class] == Loc) { *++e = LEA; *++e = loc - d[Val]; }
      else if (d[Class] == Glo) { *++e = IMM; *++e = d[Val]; }
      else { printf("%d: undefined variable\n", line); exit(-1); }
      *++e = ((ty = d[Type]) == CHAR) ? LC : LI;
    }
  }
```
第一個 if 處理 function call，第二個 else if 處理 enum，第三個 else 處理變數，其中d = id; next();使用了lookahead 的技巧。
第一個 while (155-165)處理參數(argument)的部分，並且產生 push into stack 的 IR；接下來的兩個 if 分別處理system call and function call：system call 不做 binding 的動作，只保留 Symbol name；function call 則使用 JSR 指令來跳躍到該函式的真實位址。最後根據參數的數量調整 stack frame pointer。
Local Variable 的部分(167-172)利用 LEA 將 local variable load 到 register 中，位址是相對位址。Global Variable 放在 data section，value 紀錄的是 data 的位址。最後根據 type 來決定 LC or LI。

括號處理
```
else if (tk == '(') {
    next();
    if (tk == Int || tk == Char) {
      t = (tk == Int) ? INT : CHAR; next();
      while (tk == Mul) { next(); t = t + PTR; }
      if (tk == ')') next(); else { printf("%d: bad cast\n", line); exit(-1); }
      expr(Inc);
      ty = t;
    }
    else {
      expr(Assign);
      if (tk == ')') next(); else { printf("%d: close paren expected\n", line); exit(-1); }
    }
}
```
第一個 if 處理 type casting，else 則是處理括號的優先權。

dereference（解引用）/address-of（取址）
```
else if (tk == Mul) {
    next(); expr(Inc);
    if (ty > INT) ty = ty - PTR; else { printf("%d: bad dereference\n", line); exit(-1); }
    *++e = (ty == CHAR) ? LC : LI;
}
else if (tk == And) {
    next(); expr(Inc);
    if (*e == LC || *e == LI) --e; else { printf("%d: bad address-of\n", line); exit(-1); }
    ty = ty + PTR;
}

```
recursive-descent call expr()，然後 check type 是否為一階 pointer type (semantic analyzer)，dereference semantic analyze 的過程為 ty=ty-PTR。

address-of 的部分直接把 LI/LC command 砍掉，register 所存的就會是位址；相較於 derefernece 而言，register 存的是真正的值。

Unary Operation
```
     else if (tk == '!') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = 0; *++e = EQ; ty = INT; }
     else if (tk == '~') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = -1; *++e = XOR; ty = INT; }
```
expr() 回傳的值會存在 register，因此這邊要產生的 IR 要先把結果 Push 回 stack，然後再設定 register value，最後做運算，結果會 restore into register。

```
else if (tk == Add) { next(); expr(Inc); ty = INT; }
else if (tk == Sub) {
    next(); *++e = IMM;
    if (tk == Num) { *++e = -ival; next(); } else { *++e = -1; *++e = PSH; expr(Inc); *++e = MUL; }
    ty = INT;
}
```
處理 expr 開頭是 +/- 的 case。

```
else if (tk == Inc || tk == Dec) {
    t = tk; next(); expr(Inc);
    if (*e == LC) { *e = PSH; *++e = LC; }
    else if (*e == LI) { *e = PSH; *++e = LI; }
    else { printf("%d: bad lvalue in pre-increment\n", line); exit(-1); }
    *++e = PSH;
    *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
    *++e = (t == Inc) ? ADD : SUB;
    *++e = (ty == CHAR) ? SC : SI;
}
```
pre-increment/pre-decrement：透過插入 Push command 將 register 的值存入 stack 中。

expr() 第一部分處理的都是 expression 開頭的部分，接著第二部分將會展示如何使用 operator-precedence 處理 operator 優先權。

Assign
```
if (tk == Assign) {
    next();
    if (*e == LC || *e == LI) *e = PSH; else { printf("%d: bad lvalue in assignment\n", line); exit(-1); }
    expr(Assign); *++e = ((ty = t) == CHAR) ? SC : SI;
}
```
將暫存器的位址 push 到 stack 中，做完後面的運算後，結果通常都會在暫存器中，因此透過 SC/SI 將暫存器的值存到 stack 中的位址。

```
else if (tk == Cond) {
  next();
  *++e = BZ; d = ++e;
  expr(Assign);
  if (tk == ':') next(); else { printf("%d: conditional missing colon\n", line); exit(-1); }
  *d = (int)(e + 3); *++e = JMP; d = ++e;
  expr(Cond);
  *d = (int)(e + 1);
}
```
處理類似 x=y?a:b 判斷式，保留 BZ 指令後面要填位址的空間，然後進行 recursive descent parser for expression，然後塞入 JMP 指令，且一樣保留後面要填位址的空間，展開最後的 expression 後，再填入要 JMP 的位址。

```
       else if (tk == Lor) { next(); *++e = BNZ; d = ++e; expr(Lan); *d = (int)(e + 1); ty = INT; }
       else if (tk == Lan) { next(); *++e = BZ;  d = ++e; expr(Or);  *d = (int)(e + 1); ty = INT; }
```
通常牽扯到 Branch/Jump 指令的都會使用類似這種方法：先保留目標位址，等待後面的指令都確定後，才會知道目標位址。

```
else if (tk == Or)  { next(); *++e = PSH; expr(Xor); *++e = OR;  ty = INT; }
else if (tk == Xor) { next(); *++e = PSH; expr(And); *++e = XOR; ty = INT; }
else if (tk == And) { next(); *++e = PSH; expr(Eq);  *++e = AND; ty = INT; }
else if (tk == Eq)  { next(); *++e = PSH; expr(Lt);  *++e = EQ;  ty = INT; }
else if (tk == Ne)  { next(); *++e = PSH; expr(Lt);  *++e = NE;  ty = INT; }
else if (tk == Lt)  { next(); *++e = PSH; expr(Shl); *++e = LT;  ty = INT; }
else if (tk == Gt)  { next(); *++e = PSH; expr(Shl); *++e = GT;  ty = INT; }
else if (tk == Le)  { next(); *++e = PSH; expr(Shl); *++e = LE;  ty = INT; }
else if (tk == Ge)  { next(); *++e = PSH; expr(Shl); *++e = GE;  ty = INT; }
else if (tk == Shl) { next(); *++e = PSH; expr(Add); *++e = SHL; ty = INT; }
else if (tk == Shr) { next(); *++e = PSH; expr(Add); *++e = SHR; ty = INT; }
```
這邊運算子的概念就是先將數值 push into stack frame，然後利用 operator-precedence 展開後面的 expression，展開的結果通常會存在 register，運算相關的 command 通常是拿 register 和 stack 做運算，然後將結果存回 register。

```
else if (tk == Add) {
  next(); *++e = PSH; expr(Mul);
  if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL;  }
  *++e = ADD;
}
```
這邊同時處理 pointer 的加法：因為一次 add 一個「單位」。

```
else if (tk == Sub) {
  next(); *++e = PSH; expr(Mul);
  if (t > PTR && t == ty) { *++e = SUB; *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = DIV; ty = INT; }
  else if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL; *++e = SUB; }
  else *++e = SUB;
}
```
if 判斷式，處理指標相減計算中間的個數。

```
else if (tk == Inc || tk == Dec) {
  if (*e == LC) { *e = PSH; *++e = LC; }
  else if (*e == LI) { *e = PSH; *++e = LI; }
  else { printf("%d: bad lvalue in post-increment\n", line); exit(-1); }
  *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
  *++e = (tk == Inc) ? ADD : SUB;
  *++e = (ty == CHAR) ? SC : SI;
  *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
  *++e = (tk == Inc) ? SUB : ADD;
  next();
} 
```
post-increment 的做法就是先改變 variable 在 stack 中的值，然後再回復成原來的值，並且存在 register 中，最後再進行運算。

```
else if (tk == Brak) {
  next(); *++e = PSH; expr(Assign);
  if (tk == ']') next(); else { printf("%d: close bracket expected\n", line); exit(-1); }
  if (t > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL;  }
  else if (t < PTR) { printf("%d: pointer type expected\n", line); exit(-1); }
  *++e = ADD;
  *++e = ((ty = t - PTR) == CHAR) ? LC : LI;
}
```
這部分是處理 array index 的取值到 register 中，中間必須處理一個 array 單位乘以 index，以計算最終位址。

## stmt() : 語意分析
利用 recursive-descent 處理 “if-else”, “while”, “return”, “{}”, “;”
```
 void stmt()
    {    
    ...
     }
```

##main() : declaration
```
bt = INT; // basetype
if (tk == Int) next();
else if (tk == Char) { next(); bt = CHAR; }
else if (tk == Enum) {
  next();
  if (tk != '{') next();
  if (tk == '{') {
    next();
    i = 0;
    while (tk != '}') {
      if (tk != Id) { printf("%d: bad enum identifier %d\n", line, tk); return -1; }
      next();
      if (tk == Assign) {
        next();
        if (tk != Num) { printf("%d: bad enum initializer\n", line); return -1; }
        i = ival;
        next();
      }
      id[Class] = Num; id[Type] = INT; id[Val] = i++;
      if (tk == ',') next();
    }
    next();
  }
}
```
前面兩個 if 分別處理 INT and CHAR，最後一個 if 處理 enum：使用 local variable i 來處理 value of enum id。
```
 while (tk != ';' && tk != '}') {
```
處理 Global variables and Functions。

```
 if (tk != Id) { printf("%d: bad global declaration\n", line); return -1; }
 if (id[Class]) { printf("%d: duplicate global definition\n", line); return -1; }
```
check 是否有重複宣告，是屬於 semantic analyzer 的一部份。

```
if (tk == '(') { // function
```
這邊開始處理 Function declaration。

```
id[Class] = Fun;
id[Val] = (int)(e + 1);
```
Symbol table 的 class 設定為 Fun 類型，然後將 value 設定為 IR command 的 下個指令(Function 第一個指令)的位址。

```
while (tk != ')') {
  ty = INT;
  if (tk == Int) next();
  else if (tk == Char) { next(); ty = CHAR; }
  while (tk == Mul) { next(); ty = ty + PTR; }
  if (tk != Id) { printf("%d: bad parameter declaration\n", line); return -1; }
  if (id[Class] == Loc) { printf("%d: duplicate parameter definition\n", line); return -1; }
  id[HClass] = id[Class]; id[Class] = Loc;
  id[HType]  = id[Type];  id[Type] = ty;
  id[HVal]   = id[Val];   id[Val] = i++;
  next();
  if (tk == ',') next();
}
```
檢查是否重複宣告 parameter。然後將 Symbol table 的資訊 (Class, type, Val) 備份到 HClass, HType, HVal，這邊是實作在 function 內部更改 local variable’s value 將不會影響到 Function 以外的 scope，parameter 也算是 Function local variables。

```
loc = ++i;
```
紀錄 local variable 開始的 order，前面的 order 是 parameter 個數。

```
while (tk == Int || tk == Char) {
  bt = (tk == Int) ? INT : CHAR;
  next();
  while (tk != ';') {
    ty = bt;
    while (tk == Mul) { next(); ty = ty + PTR; }
    if (tk != Id) { printf("%d: bad local declaration\n", line); return -1; }
    if (id[Class] == Loc) { printf("%d: duplicate local definition\n", line); return -1; }
    id[HClass] = id[Class]; id[Class] = Loc;
    id[HType]  = id[Type];  id[Type] = ty;
    id[HVal]   = id[Val];   id[Val] = ++i;
    next();
    if (tk == ',') next();
  }
  next();
}
```
處理 Function Local Variables declaration，一樣會備份 Symbol table 資訊。

```
*++e = ENT; *++e = i - loc;
while (tk != '}') stmt();
*++e = LEV;
```
處理 Function 內部的 statement，直到遇到屬於 function 的 }。i-loc 代表 local variables 的個數。

```
id = sym; // unwind symbol table locals
while (id[Tk]) {
  if (id[Class] == Loc) {
    id[Class] = id[HClass];
    id[Type] = id[HType];
    id[Val] = id[HVal];
  }
  id = id + Idsz;
}
```
回復所有 local variable 的 symbol table 資訊。

```
else {
    id[Class] = Glo;
    id[Val] = (int)data;
    data = data + sizeof(int);
}
```
處理 global declaration，symbol table 的 value 存的是 data section 的位址。

```
if (!(pc = (int *)idmain[Val])) { printf("main() not defined\n"); return -1; }
if (src) return 0;
```
最後檢查 main() function 是否有 define，以及是否要 run IR command on VM。




## 參考資料與來源
程式碼來源自陳鍾誠老師註解過後的的[c4.c](https://github.com/ccc-c/c4/blob/master/ccc/c4.c)，內容參考ChatGPT與老師的[C4原始碼解析](https://github.com/ccc111b/cpu2os/blob/master/%E6%9B%B8/%E7%B7%A8%E8%AD%AF%E5%99%A8/P1d-C4%E5%8E%9F%E5%A7%8B%E7%A2%BC%E8%A7%A3%E6%9E%90.md)的解釋。
* 其他參考:
  * [C in four function (c4) Compiler](https://hackmd.io/@srhuang/Bkk2eY5ES)
  * https://github.com/lotabout/write-a-C-interpreter
  * https://www.zhihu.com/question/28249756
