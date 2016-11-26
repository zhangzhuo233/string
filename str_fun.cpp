/*ʵ�ָ��ַ�������ĺ���
**2016-11-24
*/
#include<iostream>
#include<assert.h>
using namespace std;

size_t My_strlen1(const char *str);//���ַ�������
size_t My_strlen2(const char *str);
char *My_strcat(char *des, const char *src);//�ַ�����׷��
char *My_strcpy(char *des, const char *src);//�ַ�������
int My_strcmp(const char *str1, const char *str2);//�ַ����ıȽ�
void *My_memset(void *s, int ch, size_t size);//��sָ����ڴ�����ǰn���ֽ��Բ���c���룬
                                           //Ȼ�󷵻�s��ָ�롣���ڽ������ʼ���Ϸ���
                                            //˵��:����c������Ϊint,��������unsigned char,���Է�Χ��0��255֮��
void *My_memcpy(void *dest, const void *src, size_t count);//����src��ָ����ڴ�����ǰn���ֽڵ�dest��ָ��ַ�ϡ�
                                                        //��strcpy��ͬ���ǣ�memcpy()�������ĸ���n���ֽڣ�
                                                        //������Ϊ�����ַ�������'\0'������

int My_memcmp(const void *s1, const void *s2, size_t n);//�Ƚ�s1��s2ǰn���ַ�,���ز�ֵ
void *My_memmove( void *dest, const void *src, size_t count);

size_t My_strlen1(const char *str)
{
	assert(str != NULL);
	/*�ں�Դ��:
	**sc����ָ��Դ�ַ�����Ԫ�أ����sc++��֪������'\0',��ָ����
	**�����ĩβ��'\0',���ô�ʱ�ĵ�ַ��ȥ������Ԫ�صĵ�ַ���������ַ����Ĵ�С*/
	const char *sc;
	for(sc=str; *sc!=0; ++sc)//sc��ʱ�洢�ĵ�ַ��strһ������ָ��str�ַ���
		/*nothing to do*/;
	return (sc-str);
}

size_t My_strlen2(const char *str)
{
	/*��ȡ�ݹ�ķ�ʽ*/
	assert(str != NULL);
	if(*str == '\0')
		return 0;
	else{
		return 1+My_strlen2(++str);//str++,��ʹ��ԭ�ַ�������˵��ͬһ����ַѹջ���Σ������ж�
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
    *tmp = '\0';		//�ַ���׷�ӽ�������ĩβ��\0
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
    /*һ�������չʾ����str1���Ⱥ�str2���Ȳ�һ��ʱ����
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
    assert((str1!='\0') && (str2!='\0') && (n >= 0));
    while((*str1-*str2)==0)
    {
        str1++;
        str2++;
    }
        return (*str1-*str2);
}
    /*Ϊ��֤memcpy��memmove������
    **void *memmove( void *dest, const void *src, size_t count );
    **�� src �� dest ��ָ�ڴ������ص�ʱ��memmove ��� memcpy ���ṩ��֤
    **����������������֤��
    **������(1)(destβ����srcͷ���غ�)��Ӧ�����ʱ������Ҫ�ȴ�src��ͷ����ʼ����;
    **Ҳ����memmoveԴ���е�if��֧���ⲿ��Դ���memcpy��ʵ����һ�µ�;
    **������(2)(destͷ����srcβ���غ�)��Ӧ�����ʱ������Ҫ�ȴ�src��β����ʼ���ƣ�
    **��ֹ�����˸������������memmove��memcpy���һ�����ǵ㣬
    **����˵����ʵ��ʹ��ʱ��ʹ��memmove�Ǳ�memcpy����ȫ�ġ�
    */
void *My_memmove( void *dest, const void *src, size_t count)
{
    assert((dest != NULL) && (src != NULL));
    char *s1 = (char *)dest;
    char *s2 = (char *)src;
    if(s1 > s2)
    {/*destβ����srcͷ���غ�ʱ,���ȴ�src��ͷ����ʼ����;*/
        while(count--)
            *s1++ = *s2++;   
    }
    else if(s1 < s2)
    {/*destͷ����srcβ���غ�ʱ,���ȴ�src��β����ʼ����*/
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
	
	char s1[] = "liubaobao";	//���飬��ջ��
	char *s2 = "helloz!rereewewew!";		//�ַ��������������ֳ�����
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
		cout<<"���ѡ���ǣ�";
		scanf("%d", &select);
		switch(select)
		{
			case 1:
				cout<<strlen(s1)<<endl;
				cout<<"+-------+"<<endl;
				cout<<My_strlen1(s1)<<endl;//�ں˵�ʵ����ʽ
				cout<<My_strlen2(s1)<<endl;//�����������������ʵ����ʽ���ݹ�
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
                cout<<"memcpy�Ľ��\t"<<s4<<endl;
                memmove(&s5[4], s5, sizeof(s5)/sizeof(char));
                cout<<"memmove�Ľ��\t"<<s5<<endl;
                cout<<"+-------+"<<endl;
                My_memmove(&s9[4], s9, sizeof(s9)/sizeof(char));  
                cout<<s9<<endl;
				break;
			case 0:
				return 0;
			default:
				cout<<"��������!"<<endl;
				break;		
		}
	}
	return 0;
}/*str_fun.cpp*/