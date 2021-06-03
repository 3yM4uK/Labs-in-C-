#include "main.h"

#undef main

int main ()
{
    assert(letter('a') == true);
    assert(letter('B') == true);
    assert(letter('2') == false);
    assert(letter('>') == false);

    assert(sentenceCompletion('!') == true);
    assert(sentenceCompletion('a') == false);
    
    assert(punctuation('a') == false);
    assert(punctuation(',') == true);

    char str[5] = "asBsD";
    int i;
    for (int i = 0; i < 5; i++)
    {
        assert(str[i] == fixCapitalLetters(i));
    }
    
    



    
    printf("All tests successful\n");
    system("pause");
}