#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
 
using namespace std;
//Dictionary of all characters frequently used in writing a message. 
char a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
          'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
          '0','1','2','3','4','5','6','7','8','9','.',',','!','?','(',')'};
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i, enc[100];
char msg[100];

int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

 int prime(long int pr)
{
    long int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    cout << "\nENTER TWO PRIME NUMBERS	";
    cin >> p >> q;
    if( !prime(p) || !prime(q) )
	{    
	    cout<<"\nTHE NUMBERS YOU HAVE ENTERED ARE NOT PRIME!";
		exit(1);
	}	
    cout << "\nENTER MESSAGE\n";
    fflush(stdin);
    cin >> msg;
//Create a hash table to point each character in the message to its corresponding position in the dictionary. 
    for (i = 0; msg[i] != '\0'; i++)
    {
		if(msg[i]>96 && msg[i]<123)
			m[i] = msg[i]-97;
		if(msg[i]>64 && msg[i]<91)
			m[i] = msg[i]-39;
		if(msg[i]>47 && msg[i]<58)
			m[i] = msg[i]+4;
		if(msg[i]=='.')
			m[i]=62;
		if(msg[i]==',')
			m[i]=63;
		if(msg[i]=='!')
			m[i]=64;
		if(msg[i]=='?')
			m[i]=65;
		if(msg[i]=='(')
			m[i]=66;
		if(msg[i]==')')
			m[i]=67;	
		if(msg[i]==13)
			m[i]=68;
			
	}
//display the original message, using the hash table created above.	
	for(i=0; msg[i]!='\0'; i++)
		cout<<a[m[i]];
    n = p * q;
    t = (p - 1) * (q - 1);
	
//generate all possible public-private key pairs(ce: cypher text encryption)	
    ce();
    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
    for (i = 0; i < j - 1; i++)
        cout << e[i] << "\t" << d[i] << "\n";
//encrypt the message. Display the encrypted message.	
    encrypt();
//decrypt the message.	Display the original message.
    decrypt();
    return 0;
}
void ce()
{
    long int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
//Generate a private key corresponding to the current public key. 		
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
 long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
void encrypt()
{
    long int pt, ct, key = e[0], len;
    long int k;
    len = strlen(msg);
	cout<<"\nTHE ENCRYPTED MESSAGE IS\n";	
		
	for(i=0; i<len; i++)
	{
			pt = m[i];
			k  = pow(pt,key);
			ct = k % n;
			en[i] = ct;
			cout<<a[ct];
				
	}
//Terminating marker to identify the end of a messsage.	
	en[i]=-1;
	cout<<"\n\n";
}
void decrypt()
{
     long int pt, ct, key = d[0];
	 long int k;
    cout << "\nTHE DECRYPTED MESSAGE IS\n";
    for(i=0; en[i]!=-1; i++)
    {
			ct = en[i];
			k  = pow(ct,key);
			pt = k % n;
			cout<<a[pt];
		
    }
    m[i] = -1;
	cout<<"\n\n";	   
}
