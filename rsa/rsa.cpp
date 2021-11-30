#include <bits/stdc++.h>
using namespace std;
typedef long long lli;

lli Encrypt_Key;
lli Decrypt_Key;
lli n;

lli modulo_power(lli a, lli b, lli mod)
{
    lli expo = 1;
    a = a % mod;
    while (b > 0)
    {
        if (b & 1)
            expo = (expo * a) % mod;
        b = b >> 1;
        a = (a * a) % mod;
    }
    return expo;
}

lli encrypt(lli m)
{
    lli p1 = 42101;
    lli p2 = 42089;
    n = p1 * p2;
    lli e = (p1 - 1) * (p2 - 1);

    for (lli i = 2; i < e + 1; i++)
    {
        if (__gcd(i, e) == 1)
        {
            Encrypt_Key = i;
            break;
        }
    }
    for (lli i = 2; i < e + 1; i++)
    {
        lli k = 1 + e * i;
        if (k % Encrypt_Key == 0)
        {
            Decrypt_Key = k / Encrypt_Key;
            break;
        }
    }

    lli cipher = modulo_power(m, Encrypt_Key, n);

    printf("Public Key : \" e = %lld , n = %lld \"\n", Encrypt_Key, n);
    printf("private key is \" d =  %lld , n = %lld \"\n", Decrypt_Key, n);

    return cipher;
}

lli decrypt(lli e, lli b, lli c)
{
    lli mes = modulo_power(e, b, c);
    return mes;
}

int main(int argc, char **argv)
{

    lli message;

    switch (argc)
    {
    case 1:
        cout << "Invalid Arguments" << endl;
        cout << "Usage : ./a.out [ encrypt or decrypt ]" << endl;
        return 1;
        break;
    case 2:
        if (!strcmp(argv[1], "encrypt"))
        {
            cout << "Enter The (integer) Message to be encrypted" << endl;
            cin >> message;
            lli cipher_text = encrypt(message);

            printf("Encrypted message  : %lld\n", cipher_text);
        }
        else if (!strcmp(argv[1], "decrypt"))
        {
            printf("Enter the message : ");
            scanf("%lld", &message);
            if (argc != 4)
            {
                cout << "No Key provided" << endl;
                return 0;
            }
            lli p1 = atoll(argv[2]);
            lli p2 = atoll(argv[3]);
            lli plain_text = decrypt(message, p1, p2);
            printf("Decrypted message : %lld\n", plain_text);
        }
        else
        {
            cout << "Invalid Arguments" << endl;
            cout << "Usage : ./a.out [ encrypt or decrypt ]" << endl;
            return 1;
        }
        break;
    default:
        cout << "Invalid Arguments" << endl;
        return 1;
        break;
    }
    return 0;
}