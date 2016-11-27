/*实现各字符串处理的函数
**2016-11-24
*/
#include<iostream>
#include<assert.h>
using namespace std;

size_t My_strlen1(const char *str);//求字符串长度
size_t My_strlen2(const char *str);
char *My_strcat(char *des, const char *src);//字符串的追加
char *My_strcpy(char *des, const char *src);//字符串拷贝
int My_strcmp(const char *str1, const char *str2);//字符串的比较
void *My_memset(void *s, int ch, size_t size);//将s指向的内存区域前n个字节以参数c传入，
                                           //然后返回s的指针。用于将数组初始化较方便
                                            //说明:参数c虽声明为int,但必须是unsigned char,所以范围在0到255之间
void *My_memcpy(void *dest, const void *src, size_t count);//拷贝src所指向的内存内容前n个字节到dest所指地址上。
                                                        //和strcpy不同的是，memcpy()会完整的复制n个字节，
                                                        //不会因为遇到字符串结束'\0'而结束

int My_memcmp(const void *s1, const void *s2, size_t n);//比较s1和s2前n个字符,返回差值
void *My_memmove( void *dest, const void *src, size_t count);

size_t My_strlen1(const char *str)
{
	assert(str != NULL);
	/*内核源码:
	**sc先是指向源字符串首元素，随后sc++，知道遇到'\0',则指向了
	**数组的末尾的'\0',则用此时的地址减去数组首元素的地址即是整个字符串的大小*/
	const char *sc;
	for(sc=str; *sc!=0; ++sc)//sc此时存储的地址和str一样，都指向str字符串
		/*nothing to do*/;
	return (sc-str);
}

size_t My_strlen2(const char *str)
{
	/*采取递归的方式*/
	assert(str != NULL);
	if(*str == '\0')
		return 0;
	else{
		return 1+My_strlen2(++str);//str++,先使用原字符，等于说将同一个地址压栈两次，程序中断
	}
}

char *My_strcat(char *des, const char *src)
{
	assert((des != NULL) && (src != NULL));
	char *tmp = des;
    while(*tmp != '\0')
        tmp++;
	while(*src != '\0')
        *tmp++ = *src++;
    *tmp = '\0';		//字符串追加结束，给末尾加\0
    return des;
}

char *My_strcpy(char *des, const char *src)
{
    assert((des != NULL) && (src != NULL));
	char *tmp = des;
	while(*src != '\0')
		*des++ = *src++;
	*des = '\0';
	return tmp;
}

int My_strcmp(const char *str1, const char *str2)
{
    unsigned char c1,c2;
    assert((str1 != NULL) && (str2 != NULL));
    while(1)
    {
        c1 = *str1++;
        c2 = *str2++;
        if(c1 != c2)
            return c1 > c2 ? 1 : -1;
        if(c1 == '\0')
            break;
    }
    return 0;
    /*一个错误的展示，当str1长度和str2长度不一致时出错
    while((*str1 != '\0') && (*str2 != '\0'))
    {
        if(*str1 > *str2)
            return 1;
        else if(*str1 == *str2)
        {
            str1++;
            str2++;
        }
        else
            return -1;
        
    }
    return 0;*/
}

void *My_memset(void *s, int ch, size_t size)
{
    assert(((char *)s != NULL) && (size>=0));
    char *tmp = (char *)s;
    while(size--)
    {
        *tmp++ = ch;
    }
    //*tmp = '\0';
    return s;
}

void *My_memcpy(void *dest, const void *src, size_t count)
{
    assert(((char *)dest!=NULL) && ((char *)src!=NULL) && (count>=0));
    char *tmp = (char *)dest;
    const char *s = (const char *)src;
    while(count--)
        *tmp++ = *s++;
    return dest;
}

int My_memcmp(const void *s1, const void *s2, size_t n)
{
    char *str1 = (char *)s1;
    char *str2 = (char *)s2;
    assert((str1!=NULL) && (str2!=NULL) && (n >= 0));
    while((*str1-*str2)==0)
    {
        str1++;
        str2++;
    }
        return (*str1-*str2);
}
    /*为验证memcpy和memmove的区别
    **void *memmove( void *dest, const void *src, size_t count );
    **当 src 和 dest 所指内存区有重叠时，memmove 相对 memcpy 能提供保证
    **下面给出具体的例子证明
    **当出现(1)(dest尾部和src头部重合)对应的情况时，就需要先从src的头部开始复制;
    **也就是memmove源码中的if分支，这部分源码和memcpy的实现是一致的;
    **当出现(2)(dest头部和src尾部重合)对应的情况时，就需要先从src的尾部开始复制，
    **防止出现了覆盖现象。这就是memmove比memcpy多的一个考虑点，
    **所以说，在实际使用时，使用memmove是比memcpy更安全的。
    */
void *My_memmove( void *dest, const void *src, size_t count)
{
    assert((dest != NULL) && (src != NULL));
    char *s1 = (char *)dest;
    char *s2 = (char *)src;
    if(s1 < s2)
    {/*dest尾部和src头部重合时,就先从src的头部开始复制;*/
        while(count--)
            *s1++ = *s2++;   
    }
    else if(s1 > s2)
    {/*dest头部和src尾部重合时,就先从src的尾部开始复制*/
        char *s3 = s1+count;
        char *s4 = s2+count;
        while(count--)
            *s3-- = *s4--; 
    }
    return dest;
}
int main(int argc, char const *argv)
{
	int select = 0;
	
	char s1[] = "liubaobao";	//数组，在栈区
	char *s2 = "helloz!rereewewew!";		//字符串常量，在文字常量区
    char *s6 = "helloz!";
	char s3[] = "liubaobao";
	char s4[] = "testtesttest";
	char s5[] = "testtesttest";
    char s9[] = "testtesttest";
    char s7[20];
    char s8[20];
    int a[10] = {0};
	while(1)
	{
		cout<<"*************************************"<<endl;
		cout<<"* 1.strlen   2.strcat    3.strcpy   *"<<endl;
		cout<<"* 4.strcmp   5.memset    6.memcpy   *"<<endl;
		cout<<"* 7.memcmp   8.memmove   0.quit_os  *"<<endl;
		cout<<"*************************************"<<endl;
		cout<<"+-----------------------------------+"<<endl;
		cout<<"你的选择是：";
		scanf("%d", &select);
		switch(select)
		{
			case 1:
				cout<<strlen(s1)<<endl;
				cout<<"+-------+"<<endl;
				cout<<My_strlen1(s1)<<endl;//内核的实现形式
				cout<<My_strlen2(s1)<<endl;//不申请第三方变量的实现形式：递归
				break;
			case 2:
				cout<<strcat(s1, s2)<<endl;
				cout<<"+-------+"<<endl;
				cout<<My_strcat(s3, s2)<<endl;
				break;
			case 3:
				cout<<strcpy(s4, s2)<<endl;
				cout<<"+-------+"<<endl;
				cout<<My_strcpy(s5, s2)<<endl;
				break;
			case 4:
                cout<<strcmp(s6, s2)<<endl;
                cout<<"+-------+"<<endl;
                cout<<My_strcmp(s6, s2)<<endl;
				break;
			case 5:
                memset(a, 0, sizeof(int)*10);
                for(int i=0; i<10;++i)
                    cout<<a[i]<<"\t";
                cout<<"+-------+"<<endl;
                My_memset(a, 0, sizeof(int)*10);
                for(int j=0; j<10;++j)
                    cout<<a[j]<<"\t";
				break;
			case 6:
                memcpy(s4, s3, strlen(s3));
                cout<<s4<<endl;
                cout<<"+-------+"<<endl;
                My_memcpy(s5, s1, My_strlen1(s1));
                cout<<s5<<endl;
				break;
			case 7:
                cout<<memcmp(s2, s6, sizeof(s6))<<endl;
                cout<<"+-------+"<<endl;
                cout<<My_memcmp(s2, s6, sizeof(s6))<<endl;
				break;
			case 8:
                memcpy(&s4[4], s4, sizeof(s4)/sizeof(char));
                cout<<"memcpy的结果\t"<<s4<<endl;
                memmove(&s5[4], s5, sizeof(s5)/sizeof(char));
                cout<<"memmove的结果\t"<<s5<<endl;
                cout<<"+-------+"<<endl;
                My_memmove(&s9[4], s9, sizeof(s9)/sizeof(char));  
                cout<<s9<<endl;
				break;
			case 0:
				return 0;
			default:
				cout<<"参数有误!"<<endl;
				break;		
		}
	}
	return 0;
}/*str_fun.cpp*/
