![1552899411819](C:\Users\ASUS\AppData\Local\Temp\1552899411819.png) 



#### 通过这张图我们大概知道代码中各个变量是在哪存储的；

【说明】

1. **栈**又叫堆栈，非静态局部变量/函数参数/返回值等等，栈是向下增长的。
2. **内存映射段**是高效的I/O映射方式，用于装载一个共享的动态内存库。用户可使用系统接口创建共享共 享内存，做进程间通信。（Linux课程如果没学到这块，现在只需要了解一下） 
3. **堆**用于程序运行时动态内存分配，堆是可以上增长的。
4. **数据段**--存储全局数据和静态数据。
5. **代码段**--可执行的代码/只读常量。 



### 1.c语言中通过 malloc  relloc   calloc  free 管理内存

它们的区别:

```c
void test
{
int* p1=(int*)malloc(sizeof(int));        //申请一个整形大小的空间，把空间的首地址返回给p1;
free(p1);  //释放空间p1;
int* p2=(int*)calloc(5,sizeof(int));      //申请一个整形大小的空间，并且初始化为5；

int* p3=(int*)relloc(p2,sizeof(int)*100)  //改变已经申请好的空间的大小，第一个参数为需要修改的空间的首地址，第二个参数为修改后空间的大小；
free(p3);
}
```

 
--------------------- 

**区别:    (1)函数malloc不能初始化所分配的内存空间,而函数calloc能.如果由malloc()函数分配的内存空间原来没有被使用过，则其中的每一位可能都是0;反之, 如果这部分内存曾经被分配过,则其中可能遗留有各种各样的数据.也就是说，使用malloc()函数的程序开始时(内存空间还没有被重新分配)能正常进行,但经过一段时间(内存空间还已经被重新分配)可能会出现问题.**

  **(2)函数calloc() 会将所分配的内存空间中的每一位都初始化为零,也就是说,如果你是为字符类型或整数类型的元素分配内存,那么这些元素将保证会被初始化为0;如果你是为指针类型的元素分配内存,那么这些元素通常会被初始化为空指针;如果你为实型数据分配内存,则这些元素会被初始化为浮点型的零.**  

  **(3)函数malloc向系统申请分配指定size个字节的内存空间.返回类型是 void*类型.void*表示未确定类型的指针.C,C++规定，void* 类型可以强制转换为任何其它类型的指针.**  

  **(4)realloc可以对给定的指针所指的空间进行扩大或者缩小，无论是扩张或是缩小，原有内存的中内容将保持不变.当然，对于缩小，则被缩小的那一部分的内容会丢失.realloc并不保证调整后的内存空间和原来的内存空间保持同一内存地址.相反，realloc返回的指针很可能指向一个新的地址.**  

  **(5)realloc是从堆上分配内存的.当扩大一块内存空间时，realloc()试图直接从堆上现存的数据后面的那些字节中获得附加的字节，如果能够满足，自然天下太平；如果数据后面的字节不够，问题就出来了，那么就使用堆上第一个有足够大小的自由块，现存的数据然后就被拷贝至新的位置，而老块则放回到堆上.这句话传递的一个重要的信息就是数据可能被移动；**



### c++内存管理方式：

c++提出用 **new和delete**进行动态内存管理

```c++
void test()
{
    int* p1=new int;       //动态申请一个int类型的空间；
    int* p2=new int(10);   //动态申请一个int类型的空间，并初始化为10
    int* p3=new int[10];   //动态申请10个int 类型的空间；
    
    delete p1;
    delete p2;
    delete[] p3;
}
```

![1552901946307](C:\Users\ASUS\AppData\Local\Temp\1552901946307.png)

**注意：申请和释放单个元素的空间，使用new和delete操作符，申请和释放连续的空间，使用new[]和 delete[]**





### operator new  和opertor  delete 函数

**new和delete**是用户进行动态内存申请和释放的操作符，**operator new 和operator delete是系统提供的 全局函**数，new在底层调用operator new全局函数来申请空间，delete在底层通过operator delete全局 函数来释放空间

**operator new 实际也是通过malloc来申请空间，**如果malloc申请空间 成功就直接返回，否则执行用户提供的空间不足应对措施，如果用户提供该措施就继续申请，否则就**抛异 常**。**operator delete 最终是通过free来释放空间的**。





**自定义类型：new  malloc  delete  free**：

new: opreator new ---->malloc +构造              //先调 operator new    再调malloc

malloc:  malloc

new[N]:  operator new[N]------>operator new ---->malloc _构造

delete:  析构 +operator delete --->free

free:  free

delete[] :  N(析构 +operator delete ----->free)	



​	

```c++
//  operator new函数实现：

void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc) 
{    // try to allocate size bytes   
    void *p;   
    while ((p = malloc(size)) == 0)       
        if (_callnewh(size) == 0)       
        {            // report no memory        
            // 如果申请内存失败了，这里会抛出bad_alloc 类型异常        
            static const std::bad_alloc nomem;            
            _RAISE(nomem);     
        }
 
    return (p);
}
 
```



**new的原理** 

1.调用operator new函数申请空间 

2.在申请的空间上执行构造函数，完成对象的构造

 **delete的原理**

1.在空间上执行析构函数，完成对象中资源的清理工作

2.调用operator delete函数释放对象的空间

 **new T[N]的原理** 

1.调用operator new[]函数，在operator new[]中实际调用operator new函数完成N个对象空间的申 请 

2.在申请的空间上执行N次构造函数

 **delete[]的原理** 

1.在释放的对象空间上执行N次析构函数，完成N个对象中资源的清理 

2.调用operator delete[]释放空间，实际在operator delete[]中调用operator delete来释放空间	



 ### 定位new表达式：

定位new表达式是在已分配的原始内存空间中调用构造函数初始化一个对象。



**使用格式：**

new (place_address) type或者new (place_address) type(initializer-list)

place_address必须是一个**指针**，initializer-list是类型的初始化列表





**malloc / free    和     new/ delete的区别**：

**共同点**：都是从堆上申请空间，都需要用户手动释放；

**不同点**：

1.malloc和free是函数，new和delete是操作符；

2.malloc申请的空间不会初始化，new申请的空间可以初始化；

3.malloc申请空间需要手动计算大小并传递，new只需要在其后面跟上类型即可；

4.malloc返回的是void*类型，在使用时必须强转，new不需要，因为new 后边跟的就是所申请空间的类型；

5.malloc申请空间失败后返回的是NULL,因此使用时必须判断 是否为空，new不需要，

6.申请自定义类型对象时，malloc/free只会开辟空间，不会调用构造函数与析构函数，而new在申请空间 后会调用构造函数完成对象的初始化，delete在释放空间前会调用析构函数完成空间中资源的清理 

7.new/delete比malloc和free的效率稍微低点，因为new/delete的底层封装了malloc/free