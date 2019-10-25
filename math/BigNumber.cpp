#include <iostream>
#include <stdio.h>
#include <cstring>
# define FOR(i, a, b) for(int i = a; i <= b; i++)
# define _FOR(i, a, b) for(int i = a; i >= b; i--)

struct BigInt
{
    static const int M = 1000;
    int num[M + 10], len;

    BigInt(int x) {
        clean();
        itoBig(x);
    }
    BigInt() {
        clean();
    }

    void clean(){
        memset(num, 0, sizeof(num));
        len = 1;
    }

    void read(){
        char str[M + 10];
        scanf("%s", str);
        len = strlen(str);
        FOR(i, 1, len)
            num[i] = str[len - i] - '0';
    }

    void write(){
        _FOR(i, len, 1)
            printf("%d", num[i]);
        //puts("");
    }

    void itoBig(int x){
        clean();
        while(x != 0){
            num[len++] = x % 10;
            x /= 10;
        }
        if(len != 1) len--;
    }

    bool operator < (const BigInt &cmp) const {
        if(len != cmp.len) return len < cmp.len;
        _FOR(i, len, 1)
            if(num[i] != cmp.num[i]) return num[i] < cmp.num[i];
        return false;
    }

    bool operator > (const BigInt &cmp) const { return cmp < *this; }
    bool operator <= (const BigInt &cmp) const { return !(cmp < *this); }
    bool operator != (const BigInt &cmp) const { return cmp < *this || *this < cmp; }
    bool operator == (const BigInt &cmp) const { return !(cmp < *this || *this < cmp); }

    BigInt operator + (const BigInt &A) const {
        BigInt S;
        S.len = max(len, A.len);
        FOR(i, 1, S.len){
            S.num[i] += num[i] + A.num[i];
            if(S.num[i] >= 10){
                S.num[i] -= 10;
                S.num[i + 1]++;
            }
        }
        while(S.num[S.len + 1]) S.len++;
        return S;
    }

    BigInt operator - (const BigInt &A) const {
        BigInt S;
        S.len = max(len, A.len);
        FOR(i, 1, S.len){
            S.num[i] += num[i] - A.num[i];
            if(S.num[i] < 0){
                S.num[i] += 10;
                S.num[i + 1]--;
            }
        }
        while(!S.num[S.len] && S.len > 1) S.len--;
        return S;
    }

    BigInt operator * (const BigInt &A) const {
        BigInt S;
        if((A.len == 1 && A.num[1] == 0) || (len == 1 && num[1] == 0)) return S;
        S.len = A.len + len - 1;
        FOR(i, 1, len)
            FOR(j, 1, A.len){
                S.num[i + j - 1] += num[i] * A.num[j];
                S.num[i + j] += S.num[i + j - 1] / 10;
                S.num[i + j - 1] %= 10;
            }
        while(S.num[S.len + 1]) S.len++;
        return S;
    }

    BigInt operator / (const BigInt &A) const {
        BigInt S;
        if((A.len == 1 && A.num[1] == 0) || (len == 1 && num[1] == 0)) return S;
        BigInt R, N;
        S.len = 0;
        _FOR(i, len, 1){
            N.itoBig(10);
            R = R * N;
            N.itoBig(num[i]);
            R = R + N;
            int flag = -1;
            FOR(j, 1, 10){
                N.itoBig(j);
                if(N * A > R){
                    flag = j - 1;
                    break;
                }
            }
            S.num[++S.len] = flag;
            N.itoBig(flag);
            R = R - N * A;
        }
        FOR(i, 1, S.len / 2) swap(S.num[i], S.num[len - i + 1]);
        while(!S.num[S.len] && S.len > 1) S.len--;
        return S;
    }

    BigInt operator % (const BigInt &A) const {
        BigInt S;
        BigInt P = *this / A;
        S = *this - P * A;
        return S;
    }
};
