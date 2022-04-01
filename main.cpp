void Swap1(int &x, int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

// 指针实现
void Swap2(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp; 
}

int main(){
// 调用
int x = 5;
int y = 6;
Swap1(x, y);

// 调用
Swap2(&x, &y);
return 0;
}