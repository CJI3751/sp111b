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

## 參考資料與來源
程式碼來源自陳鍾誠老師註解過後的的[c4.c](https://github.com/ccc-c/c4/blob/master/ccc/c4.c)，內容參考ChatGPT與老師的[C4原始碼解析](https://github.com/ccc111b/cpu2os/blob/master/%E6%9B%B8/%E7%B7%A8%E8%AD%AF%E5%99%A8/P1d-C4%E5%8E%9F%E5%A7%8B%E7%A2%BC%E8%A7%A3%E6%9E%90.md)的解釋。
* 其他參考:
  * [C in four function (c4) Compiler](https://hackmd.io/@srhuang/Bkk2eY5ES)
  * https://github.com/lotabout/write-a-C-interpreter
  * https://www.zhihu.com/question/28249756
