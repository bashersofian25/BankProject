#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
string  DecryptText(string Text, short EncryptionKey)
{

    for (int i = 0; i <= Text.length(); i++)
    {

        Text[i] = char((int)Text[i] - EncryptionKey);

    }
    return Text;

}

int main()

{
    // to avoid circular referece problems
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen()) {
            break;
        }
    }


    system("pause>0");
    return 0;
}