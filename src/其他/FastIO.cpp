namespace Input
{
    const int BUF = 65536;
    char buf[BUF + 1];
    char *head = buf, *tail = buf;
}
inline char inputchar()
{
    using namespace Input;
    if(head == tail)
        *(tail = (head = buf) + fread(buf, 1, BUF, stdin)) = 0;
    return *head++;
}
inline void inputnum(int &ret)
{
    char ch = inputchar();
    while(ch < '0' || ch > '9')
        ch = inputchar();
    ret = ch - '0';
    ch = inputchar();
    while(ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + ch - '0';
        ch = inputchar();
    }
}
// 使用了快速读入之后不能再使用cin或者scanf