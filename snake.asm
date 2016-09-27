;Karol Szustakowski 2016
;Feel free to copy just append previous authors
format PE console
entry start
include 'include/win32a.inc'
 
section '.text' code executable
    restart:
          mov ecx, 1999
          reslab:
        mov [indexactive+ecx],0
        mov [posx+ecx], 0
        mov [posy+ecx], 0
        dec ecx
        cmp ecx, 0
        jne reslab
    start:
          mov [indexactive], 1
          mov [posx], 40
          mov [posy], 10
          mov [indexactive+1], 1
          mov [indexactive+2], 1
          mov [indexactive+3], 1
          mov [indexactive+4], 1
          mov [indexactive+5], 1
          mov [indexactive+6], 1
          push -10
          call [GetStdHandle]
          mov [inhandle], eax
          push -11
          call [GetStdHandle]
          mov [outhandle], eax
          PUSH 09H
          push [outhandle]
          call [SetConsoleTextAttribute]
          push windowsize ;<- this is required if the app has to run on windows 10
          call [system]
    stlp:
          call FILLAREA
          xor ecx, ecx
          mov cl, 0
          printelements:
            xor eax, eax
            mov al, [indexactive + ecx]
            cmp eax, 0
            je notactive
            xor eax, eax
            mov al, [posy+ecx]
            mov ah, 80
            mul ah
            xor edx, edx
            add dl, [posx+ecx]
            add eax, edx
            mov [areatodraw+eax], 0xB2
            notactive:
            inc ecx
            cmp ecx, 2000
            jne printelements
 
          cmp [pointactive], 1
          je nopointpresent
          push 77
          push 2
          call GETRANDOMNUMBER
          mov [pointposx], EAX
          push 23
          push 3
          call GETRANDOMNUMBER
          mov [pointposy], EAX
          nopointpresent:
          mov eax, [pointposy]
          mov edx, 80
          mul edx
          add eax, [pointposx]
          mov [areatodraw+EAX], 254
          mov [pointactive], 1
          push eax
          xor eax, eax
          mov al, [posy]
          mov edx, 80
          mul edx
          xor ecx, ecx
          mov cl, [posx]
          add eax, ecx
          mov ecx,eax
          pop eax
          cmp eax, ecx
          jne  noscored
          inc [length]
          mov [pointactive], 0
          xor eax, eax
          mov al, [length]
          dec al
          mov [indexactive+eax], 1
          inc [score]
          noscored:
          push areatodraw
          push strbuff
          call [printf]
          push dword [scorecoord]
          push [outhandle]
          call [SetConsoleCursorPosition]
          push [score]
          push intbuff
          call [printf]
          add esp, 0x08
          push dword [coord]
          push [outhandle]
          call [SetConsoleCursorPosition]
          add esp, 0x08
          push 110
          call [Sleep]
          xor ecx, ecx
          mov cl, [length]
          dec cl
          ifdead:
        mov al, [posx+ecx]
        cmp [posx], al
        jne fcmp
        mov al, [posy+ecx]
        cmp [posy], al
        jne fcmp
        jmp gameover
        fcmp:
        dec cl
        cmp cl, 0
        jne ifdead
          mov ECX, 0
          copytablecnt:
        cmp [indexactive+ECX], 0
        je cndout
        mov al, [posx+ECX]
        mov bl, [posy+ECX]
        mov [posxb+ECX], al
        mov [posyb+ECX], bl
        inc ECX
        cmp ECX, 2000
        jne copytablecnt
          cndout:
          call CHECKFORCHAR
          cmp EAX, 80
          je plusy
          cmp EAX, 72
          je minusy
          cmp EAX, 75
          je minusx
          cmp EAX, 77
          je plusx
          jmp nokeypressed
          comparefinish:
        push [inhandle]
        call [FlushConsoleInputBuffer]
 
          mov ECX, 1
          jhl:
        cmp [indexactive+ECX], 0
        je conditionout
        mov al, [posxb+ECX-1]
        mov bl, [posyb+ECX-1]
        mov [posx+ECX], al
        mov [posy+ecx], bl
        inc ecx
        cmp ecx, 2000
        jne jhl
          conditionout:
 
          jmp stlp
 
          gameover:
        call FILLAREA
        push areatodraw
        push strbuff
        call [printf]
        add esp, 0x08
        push dword [overcoord]
        push [outhandle]
        call [SetConsoleCursorPosition]
        push overmsg
        push strbuff
        call [printf]
        add esp, 0x08
        push [score]
        push intbuff
        call [printf]
        add esp, 0x08
        push overmsg2
        push strbuff
        call [printf]
        add esp, 0x08
        call [_getch]
        jmp restart
 
 
          push 0
          call [ExitProcess]
          plusy:
        cmp [direction], 0
        je my
        py:
        mov [direction], 2
        inc [posy]
        cmp [posy], 23
        jg fliptostarty
        jmp comparefinish
          minusy:
        cmp [direction], 2
        je py
        my:
        mov [direction], 0
        dec [posy]
        cmp [posy], 2
        jl fliptofinishy
        jmp comparefinish
          minusx:
        cmp [direction], 1
        je px
        mx:
        mov [direction], 3
        dec [posx]
        cmp [posx], 1
        jl fliptofinishx
        jmp comparefinish
          plusx:
        cmp [direction], 3
        je mx
        px:
        mov [direction], 1
        inc [posx]
        cmp [posx], 78
        jg fliptostartx
        jmp comparefinish
 
 
          fliptofinishy:
        mov [posy], 23
        jmp comparefinish
          fliptofinishx:
        mov [posx], 78
        jmp comparefinish
          fliptostarty:
        mov [posy], 2
        jmp comparefinish
          fliptostartx:
        mov [posx], 1
        jmp comparefinish
 
        nokeypressed:
        cmp [direction], 0
        je my
        cmp [direction], 1
        je px
        cmp [direction], 2
        je py
        cmp [direction], 3
        je mx
        jmp comparefinish
 
 
    CHECKFORCHAR:
        push ebp
        call [_kbhit]
        cmp EAX, 0
        je nopress
        call [_getch]
        cmp EAX, 0xE0
        jne nopress
        call [_getch]
        nopress:
        pop ebp
        ret
    FILLAREA:
        push ebp
        mov ecx, 1999
        jh:
               mov [areatodraw+ecx], ' '
        loop jh
        mov ecx, 1
        l1:
            mov al, cl
            mov ah, 80
            mul ah
            mov [areatodraw + eax], 0xDB
            mov [areatodraw + eax + 79], 0xDB
            inc ecx
            cmp ecx, 25
            jne l1
        mov ecx, 0
        l2:
            mov [areatodraw + ecx + 80], 0xDB
            mov [areatodraw + ecx], 0xDB
            inc ecx
            cmp ecx, 80
            jne l2
        mov ecx, 0
        l3:
            mov [areatodraw + ecx + 1920], 0xDB
            inc ecx
            cmp ecx, 80
            jne l3
        mov [areatodraw + 5], 'S'
        mov [areatodraw + 6], 'c'
        mov [areatodraw + 7], 'o'
        mov [areatodraw + 8], 'r'
        mov [areatodraw + 9], 'e'
        mov [areatodraw + 10], ':'
        pop ebp
        ret
 
     GETRANDOMNUMBER:
        push EBP
        mov ebp, esp
        call [time]
        mov ebx, eax
        rdtsc
        mov ecx, eax
        mov eax, ebx
        mul cx
        push eax
        mov eax, [ebp+8] ;lowerbound
        mov ecx, eax
        mov ebx, [ebp+12] ;uperbound
        inc ebx ;inc by one to contain the upper bound
        ;need ebx to contain difference between upper and lower bound
        sub ebx, eax
        xor edx, edx ;zero edx
        pop eax
        div ebx ;div EDX:EAX by EBX rest of which is in EDX
        add edx, ecx ;add lowerbound to edx
        mov eax, edx ;save result to eax
        mov esp, ebp
        pop EBP
        ret 8
section '.data' data readable writeable
    intbuff db '%d', 0
    charbuff db '%c', 0
    strbuff db '%s', 0
    overmsg db 'Game over! Your score was: ', 0
    overmsg2 db ' Press any key to start again.' ,0
    areatodraw db 25*80 dup (' '), 0
    inhandle dd 0
    outhandle dd 0
    coord dw 0, 0
    scorecoord dw 12, 0
    overcoord dw 10, 10
    indexactive db 2000 dup (0)
    posx db 2000 dup (0)
    posy db 2000 dup (0)
    posxb db 2000 dup (0)
    posyb db 2000 dup (0)
    pointactive db 0
    pointposx dd 0
    pointposy dd 0
    direction db 0
    length db 7
    score dd 0
    windowsize db 'MODE CON COLS=80 LINES=26', 0
section '.idata' data readable import
    library kernel32, 'kernel32.dll', msvcrt, 'msvcrt.dll'
    import kernel32, ExitProcess, 'ExitProcess', Sleep, 'Sleep', GetStdHandle, 'GetStdHandle', FlushConsoleInputBuffer, 'FlushConsoleInputBuffer', \
           SetConsoleCursorPosition, 'SetConsoleCursorPosition', SetConsoleTextAttribute, 'SetConsoleTextAttribute'
    import msvcrt, scanf, 'scanf', printf, 'printf', _kbhit, '_kbhit', _getch, '_getch', time, 'time', system, 'system'
