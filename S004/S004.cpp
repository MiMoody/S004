
#include <iostream>

int main()
{
    char str[] = "Hello,World";
    char s[256] = "\0";
    int First = 6; // с какого индекса копируем
    int Len = 5; // длина копирования
    char f[] = "%s";
    __asm
    {
        lea esi, str
        lea ecx, f
        mov ecx, -1
        dec esi

        push edx
        mov edx, First

        lea ebx, str
        push ebx
        dec ebx

        LengthStr :
        inc ecx
            inc ebx
            mov al, [ebx]
            cmp al, 0
            jnz LengthStr
            push ecx

            StartCopy :
        cmp First, 0
            jl StrNoChange

            LengthCopy :
        cmp Len, 0
            jl StrNoChange

            FirstBiggerLength :
        cmp First, ecx
            jg StrNoChange

            add edx, Len

            CheckLengthCopy :
        add ecx, 1
            cmp edx, ecx
            jg StrNoChange

            add esp, 8
            mov ecx, -1
            dec esi

            lea esi, [str]
            lea edi, [s]
            push edi
            dec esi

            mov edx, First

            Write :
        inc esi
            inc ecx
            cmp ecx, edx
            jne Write

            add edx, Len

            ContinueWrite:
            inc ecx
            lodsb
            stosb
            cmp ecx,edx
            jne ContinueWrite

            jmp End

        StrNoChange:
        add esp, 8
            mov ecx, -1
            dec esi
            lea esi, [str]
            lea edi, [s]
            push edi

            ContinueNoChange :
        lodsb
            stosb
            cmp al, 0
            jnz ContinueNoChange

            End :
            pop edi
            pop esi
    }
    std::cout << s;
}

