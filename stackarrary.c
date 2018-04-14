#include <stdio.h>

#define SharedStackMaxSize 1000

typedef char SharedStackType;

typedef struct SharedStack{
    SharedStackType data[SharedStackMaxSize];
    size_t top1;//栈1：[0,top1)
    size_t top2;//栈2：[top2,max_size)
} SharedStack;

//初始化
void SharedStackInit(SharedStack* stack){
    if(stack==NULL){
        return;
    }
    stack->top1=0;
    stack->top2=SharedStackMaxSize;
}

//入栈，插入 top1
void SharedStackPush1(SharedStack* stack,SharedStackType value){
    if(stack==NULL){
        //非法输入
        return;
    }
    if(stack->top1>=stack->top2){
        //栈满了
        return;
    }
    stack->data[stack->top1++]=value;
    return;
}

//插入 top2
void SharedStackPush2(SharedStack* stack,SharedStackType value){
    if(stack==NULL){
        //非法输入
        return;
    }
    if(stack->top1>=stack->top2){
        //栈满了
        return;
    }
    stack->data[--stack->top2]=value;//此处先--
    return;
}

//取栈顶元素（top1)
int SharedStackTop1(SharedStack* stack,SharedStackType* value){
    if(stack==NULL||stack==NULL){
        //非法输入
        return 0;
    }
    if(stack->top1==0){
        //空栈
        return 0;
    }
    *value=stack->data[stack->top1-1];//[ 0,top1  )
    return 1;
}

//取栈顶元素（top2)
int SharedStackTop2(SharedStack* stack,SharedStackType* value){
    if(stack==NULL||stack==NULL){
        return 0;
    }
    if(stack->top2==SharedStackMaxSize){
        return 0;
    }
    *value=stack->data[stack->top2];
    return 1;
}

//出栈（top1）
void SharedStackPop1(SharedStack* stack){
    if(stack==NULL){
        return;
    }
    if(stack->top1==0){
        return;
    }
    --stack->top1;
    return;
}


//出栈（top2）
void SharedStackPop2(SharedStack* stack){
    if(stack==NULL){
        return;
    }
    if(stack->top2==SharedStackMaxSize){
        return;
    }
    ++stack->top2;
    return;
}

/////////////////////////////////////////
//以下为测试函数
///////////////////////////////////////////
void SharedPrintChar(SharedStack* stack,const char* msg,size_t top1,size_t top2)
{
    printf("==== 以下为top1中元素 =====\n");
    printf("%s\n",msg);
    size_t i=0;
    for(;i<top1;++i){
        printf("[ %c ]",stack->data[top1-i]);
    }
    printf("==== 以下为top2中元素 =====\n");
    size_t j=SharedStackMaxSize;
    for(;j<=top2;--j)
    {
        printf("[ %c ]",stack->data[top2]);
    }
}
void Test()
{
    SharedStack stack;
    SharedStackInit(&stack);

    printf("入栈 4个元素\n");
    SharedStackPush1(&stack,'a');
    SharedStackPush1(&stack,'b');
    SharedStackPush1(&stack,'c');
    SharedStackPush1(&stack,'d');
    SharedStackPush2(&stack,'a');
    SharedStackPush2(&stack,'b');
    SharedStackPush2(&stack,'c');
    SharedStackPush2(&stack,'d');
    SharedPrintChar(&stack,"[打印入栈的四个元素]",3,996);

    printf("测试出栈1 个元素\n");
    SharedStackPop1(&stack);
    SharedStackPop2(&stack);
    SharedPrintChar(&stack,"[ 出栈1个 ]",2,997);

    printf("测试取栈顶元素 \n");
    SharedStackType top1;
    SharedStackType top2;
    int ret1=SharedStackTop1(&stack,&top1);
    int ret2=SharedStackTop2(&stack,&top2);
    printf("返回值是：[ top1: %d ],[ top2:%d ]\n 栈顶元素：[ top1:%c ],[ top2:%c ]\n",ret1,ret2,top1,top2);

}




int main()
{
    Test();
    return 0;
}
