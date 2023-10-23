#include <iostream>
#include <fstream>
using namespace std;

const int BYTE = 256, M = 101, L = 14, KEY[L] = {1, 18, 20, 1, 11, 0, 19, 1, 14, 1, 13, 25, 1, 14};
int s[BYTE], k[BYTE], keG[BYTE], irc4 = 0, jrc4 = 0, s4[4][BYTE];

void init()
{
    int j;
    for (int i = 0; i < BYTE; i++)
    {
        k[i] = KEY[i % L];
        s[i] = i;
    }
    
    irc4 = 0; jrc4 = 0; j = 0;

    for (int i = 0; i < BYTE; i++)
    {
        j = (j + s[i] + k[i]) % BYTE;
        swap(s[i], s[j]);
    }
}

int rc4()
{
    int t;
    irc4 = (irc4 + 1) % BYTE;
    jrc4 = (jrc4 + s[irc4]) % BYTE;
    swap(s[irc4], s[jrc4]);
    t = (s[irc4] + s[jrc4]) % BYTE;
    return s[t];
}

int rc4r(int m)
{
    int b, y = BYTE - (BYTE % m);
    for (b = y; b >= y; b = rc4());
    return b % m;
}   

int rc4m(int i)
{
    int k = 0, c;
    for (int j = i; j < 128; j <<= 1, k++);
    for (c = i; c >= i; c = (rc4() << k) >> k);
    return c;
}

void rc4_shuffle(int m, int p[BYTE])
{
    int s[BYTE];
    for (int i = 0; i < BYTE; i++)
        s[i] = 0;

    for (int i = 0; i < m; i++)
        s[i] = i;

    for (int i = m - 1; i > 0; i--)
    {
        int k = rc4m(i);
        p[i] = s[k];
        for (int j = k; j <= i; j++)
            if (j < m) 
                s[j] = s[j + 1];
        
        if (i == m - 1) 
            s[m - 1] = 0;
    }

    p[0] = s[0];
    //result in p
}

void rc4_shuffle1(int t, int ans[BYTE])
{
    bool used[BYTE];
    int size = 0, s[BYTE];  
    for (int i = 0; i < BYTE; i++)
    {
        s[i] = i;
        used[i] = false;
    }

    while (size < BYTE) //BYTTE or t
    {
        for (int i = 0; i < BYTE; i++)
        {
            int k = rc4(), m = rc4();
            size += (!used[k]) + (!used[m]);
            used[k] = true;
            used[m] = true;
            swap(s[k], s[m]);
        }
    }

    int m = 0;
    for (int i = 0; i < BYTE; i++)
        if (s[i] < t)
            ans[m++] = s[i];

    //result in ans
}

void my_rc4_shuffle(int t, int s[BYTE])
{
    for (int i = 0; i < t; i++)
        s[i] = i;

    for (int i = 1; i < t; i++) 
        for (int j = 0; j < i; j++)
        {
            int k = rc4() % t;
            int m = rc4() % t;
            swap(s[k], s[m]);
        }

    //result in s
}

int pow_mod(int a, int n, int m)
{
    int ans = 1;
    for (int i = 1; i < n; i++)
        ans = (ans * a) % m;

    return ans;
}

void discreteLogPermModM(int p[BYTE])
{
    int pow = 1;
    for (int i = 0; i < BYTE; i++)
        p[i] = 0;

    for (int i = 0; i < M - 1; i++)
    {
        int y = pow % (M - 1);
        p[y] = i;
        pow = (pow * 2) % M;
    }

    //result in p
}

int gcd(int a, int b)
{
    while (a > 0 && b > 0)
        if (a > b)
            a%=b;
        else 
            b%=a;

    return a + b;
}

void formularPermModM(int x[BYTE], int y[BYTE])
{
    for (int i = 0; i < M; i++) // <=
        y[i] = 0;

    int k1, k2;
    for (k1 = M - 1; gcd(M - 1, k1) != 1; k1 = rc4m(M - 1));
    k2 = rc4m(M - 1);
    for (int i = 0; i < M - 1; i++)
        y[i] = (k1 * x[i] + k2) % (M - 1);

    //result in y
}

void matrixMult(int a[BYTE][BYTE], int b[BYTE][BYTE], int ans[BYTE][BYTE], int l, int m, int n) //sizes
{
    const int X = 10;
    for (int i = 0; i < l; i++)
        for (int j = 0; j < m; j++)
            ans[i][j] = 0;

    for (int i = 0; i < l; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
                ans[i][j] = (ans[i][j] + (a[i][k] * b[k][j]) % X) % X;

    //result in ans 
}

int e[BYTE][BYTE], a2[BYTE][BYTE];
bool isInvolutive(int a[BYTE][BYTE], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            e[i][j] = (i == j);

    matrixMult(a, a, a2, n, n, n);
    bool flag = true;
    for (int i = 0; i < n && flag; i++)
        for (int j = 0; j < n && flag; j++)
            flag = (flag && (a2[i][j] != e[i][j]));

    return flag;
}

int count2DInvolutiveMatrices(bool isShow)
{
    int m[BYTE][BYTE];
    for (int i = 0; i < BYTE; i++)
        for (int j = 0; j < BYTE; j++)
            m[i][j] = 0;

    int cnt = 0;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 10; b++)
            for (int c = 0; c < 10; c++)
                for (int d = 0; d < 10; d++)
                {
                    m[0][0] = a;
                    m[0][1] = b;
                    m[1][0] = c;
                    m[1][1] = d;

                    if (isInvolutive(m, 2))
                    {
                        cnt++;
                        if (isShow)
                        {
                            for (int i = 0; i < 2; i++, cout << endl)
                                for (int j = 0; j < 2; j++)
                                    cout << m[i][j] << ' ';

                            cout << endl;
                        }
                    }
                }

    return cnt;
}

int divR(int a, int b, int m)
{
    int c = 0, i = 0;
    for (; i != a && i < m; i++)
        c = (c + b) % m;
    
    return i % m;
}

void genInverse(int a[BYTE][BYTE], int ainv[BYTE][BYTE], int n) //for triangle matrix
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            ainv[i][j] = 0;

        ainv[i][i] = 1;
    }

    bool isLower = false;
    if (a[0][1] == 0)
    {
        isLower = true;
        for (int i = 0; i < n / 2; i++)
            for (int j = 0; j < n; j++)
            {
                swap(a[i][j], a[n - i - 1][j]);
                swap(ainv[i][j], ainv[n - i - 1][j]);
            }

        for (int j = 0; j < n / 2; j++)
            for (int i = 0; i < n; i++)
            {
                swap(a[i][j], a[i][n - j - 1]);
                swap(ainv[i][j], ainv[i][n - j - 1]);
            }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int tmp = a[i][i];
        for (int j = 0; j < n - 1; j++)
        {
            ainv[i][j] = divR(ainv[i][j], tmp, M - 1);
            a[i][j] = divR(a[i][j], tmp, M - 1);
        }

        if (i > 0)
        {
            for (int k = i - 1; k >= 0; k--)
            {
                tmp = a[k][i];
                for (int j = 0; j < n; j++)
                {
                    ainv[k][j] = (ainv[k][j] + (M - 1) - (ainv[i][j] * tmp) % (M - 1)) % (M - 1);
                    a[k][j] = (a[k][j] + (M - 1) - (a[i][j] * tmp) % (M - 1)) % (M - 1);
                }
            }
        }

        if (!isLower)
        {
            for (int i = 0; i < n / 2; i++)
                for (int j = 0; j < n; j++)
                {
                    swap(a[i][j], a[n - i - 1][j]);
                    swap(ainv[i][j], ainv[n - i - 1][j]);
                }
        }
    }

    //result in ainv
}

int mn[BYTE][BYTE], v[BYTE][BYTE], w[BYTE][BYTE], vinv[BYTE][BYTE], winv[BYTE][BYTE], tmp[BYTE][BYTE];
void genInvolutiveMatrix(int ans[BYTE][BYTE], int n)
{
    for (int a = 0; a < n; a++)
        for (int b = 0; b < n; b++)
        {
            mn[a][b] = 0;
            v[a][b] = 0;
            w[a][b] = 0;
            if (a < b)
                v[a][b] = rc4m(M - 1);
            else if (a > b)
                w[a][b] = rc4m(M - 1);
            else 
            {
                for (v[a][b] = M - 1; gcd(M - 1, v[a][b]) != 1; v[a][b] = rc4m(M - 1));
                for (w[a][b] = M - 1; gcd(M - 1, w[a][b]) != 1; w[a][b] = rc4m(M - 1));
            }
        }
    
    int a = rc4m(M - 1), b, binv = 1;
    for (b = M - 1; gcd(M - 1, b) != 1; b = rc4m(M - 1));
    for (int i = 1; i < 20; i++) //Karmichael
        binv = (binv * b) % (M - 1);

    
	int m00 = a, m01 = b;
    int m10 = (binv * (M - a * a % (M - 1)) % (M - 1)) % (M - 1); 
    int m11 = (M - 1 - a) % (M - 1);

    for (int i = 0; i < n / 2; i++)
    {
        mn[2 * i][2 * i] = m00;
        mn[2 * i][2 * i + 1] = m01;
        mn[2 * i + 1][2 * i] = m10;
        mn[2 * i + 1][2 * i + 1] = m11;
    }

	genInverse(v, vinv, n);
    genInverse(w, winv, n);

    matrixMult(v, w, tmp, n, n, n);
    matrixMult(tmp, mn, ans, n, n, n);
    matrixMult(ans, vinv, tmp, n, n, n);
    matrixMult(tmp, winv, ans, n, n, n);

    //result in ans
}

void G(int k1, int k2, int k3, int k4, int &a, int &b)
{
    a = (a + s4[0][(b + k1) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + s4[1][(b + k2) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + s4[2][(b + k3) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + s4[3][(b + k4) % (M - 1)]) % (M - 1); 
}

void Ginv(int k1, int k2, int k3, int k4, int &a, int &b)
{
    a = (a + (M - 1) - s4[0][(b + k4) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + (M - 1) - s4[1][(b + k3) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + (M - 1) - s4[2][(b + k2) % (M - 1)]) % (M - 1); swap(a, b);
    a = (a + (M - 1) - s4[3][(b + k1) % (M - 1)]) % (M - 1); 
}

void gen_ke(int ke[BYTE])
{
    for (int i = 0; i < 16; i++)
        ke[i] = rc4m(M - 1);
}

void genPINcode(int c[BYTE], bool isInverse)
{
    int a[BYTE][BYTE], q[BYTE][BYTE], q1[BYTE][BYTE], k[BYTE], ke[BYTE], b[BYTE];
    for (int i = 0; i < 8; i++)
        k[i] = rc4m(M - 1);

    if (!isInverse)
        for (int i = 0; i < 16; i++)
            ke[i] = keG[i];
    else if (isInverse)
        for (int i = 0; i < 16; i++)
            ke[i] = keG[15 - i];

    for (int i = 0; i < 8; i++)
    {
        b[i] = c[2 * i] + c[2 * i + 1] * 10;
        b[i] = (b[i] + k[i]) % (M - 1);
    }

    for (int i = 0; i < 3; i++)
    {
        G(b[7], ke[2 * i], b[2], ke[2 * i + 1], b[0], b[1]);
        int tmp1 = b[6], tmp2 = b[7];

        for (int j = 2; j < 8; j++)
            b[j] = b[j - 2];

        b[0] = tmp1;
        b[1] = tmp2;       
    }

    G(b[7], ke[6], b[2], ke[7], b[0], b[1]);
    genInvolutiveMatrix(a, 8);
	cerr << isInvolutive(a, 8);
	cerr << endl;

	for (int i = 0; i < BYTE; i++)
        q[0][i] = b[i];

    matrixMult(q, a, q1, 1, 8, 8);
    for (int i = 0; i < BYTE; i++)
    {
        for (int j = 0; j < BYTE; j++)
            q[i][j] = q1[i][j];
        b[i] = q[0][i];
    }

    for (int i = 4; i < 7; i++)
    {
        Ginv(b[7], ke[2 * i], b[2], ke[2 * i + 1], b[0], b[1]);
        int tmp1 = b[0], tmp2 = b[1];
        for (int j = 0; j < 6; j++)
            b[j] = b[j + 2];

        b[6] = tmp1;
        b[7] = tmp2;
    }

    Ginv(b[7], ke[14], b[2], ke[15], b[0], b[1]);

    for (int i = 0; i < 8; i++)
    {
        b[i] = b[i] + (M - 1 - k[i]) % (M - 1);
        c[2 * i] = b[i] % 10;
        c[2 * i + 1] = b[i] / 10;
    }
}

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    init();

    for (int i = 0; i < BYTE; i++)
        rc4();
    
    gen_ke(keG);

    rc4_shuffle(M - 1, s4[0]);
    rc4_shuffle(M - 1, s4[2]);

    discreteLogPermModM(s4[1]);
    formularPermModM(s4[1], s4[3]);
    //discreteLogPerm2Mid101(); does not works

    int c[BYTE]; bool inverse = true;
    for (int i = 0; i < 16; i++)
        cin >> c[i];

    genPINcode(c, !inverse);

    for (int i = 0; i < 16; i++)
        cout << c[i] << " ";

    cout << endl << "inverse" << endl;

    genPINcode(c, inverse);
    
    for (int i = 0; i < 16; i++)
        cout << c[i] << " ";

    return 0;
}