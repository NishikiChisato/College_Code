# 1.尽量以 const, enum, inline 替换 #define



当我写出

```cpp
#define SIZE = 1.638;
```

记号 SIZE会在预编译阶段就被预处理器给替换掉，**这使得SIZE这个名称不会被编译器看到，进而导致SIZE不会进入记号表(symbol table)**。当我用此常量而获得一个错误的编译信息时，这个错误信息会提到 1.638 而不会提到 SIZE 。如果我将 SIZE 写在一个头文件内，这便会导致追踪该变量会浪费时间

因此，我们可以使用以下代码来进行替换

```cpp
const double Size = 1.638;
```

作为一个常量，它一定会被编译器看见进而进入记号表内



在用常量替换 #define 时，我们需要注意两种情况。

* 第一个是定义常量指针。

当我们定义常量指针并将其放入头文件内时，我们需要将该指针声明为 const 。一般来说，这种常量指针会指向一个字符常量，即

```cpp
const char* const authorName = "Mellina";
```

这里我们需要使用两个 const ，当然我们也可以用 string 来代替，即

```cpp
const string authorName = "Mellina";
```

* 第二个是 class 内部的常量

当我需要将常量的作用域限定于 class 内时，我需要对成员变量使用 const ，与此同时，既然是常量，那么它就**只能有一个实体**，因此我还需要用 static 来进行修饰。

对于非 const 修饰的 static 成员变量而言，**必须在 class 内部声明， 在 class 外部赋值**，即声明式需要写在 class 内，定义式需要写在 class 外。

但是，当该成员变量被 const 修饰时，我们可以**直接在 class 内部对其赋值**，即

```cpp
class Test
{
public:
	const static int size = 10;
	int arr[size];
};
```

对于 class 专属常量又被 static 修饰且为整数类型（int, char, bool），只要不取出它们的地址，那么我便可以声明便使用它而无需提供定义式。但如果我取出它的地址或者编译器要求看到其定义式，那么我们需要另外提供其定义式：

```cpp
const int Test::size;
```

将该式子放入一个**实现文件**当中即可（这里不需要赋值，因为在声明的时候已经有初值了）

当然，如果编译器不支持上述语法（这种语法也只对整型常量进行），我们按照 static 修饰成员变量的方式赋值即可

对于 #define 言，它并不支持任何封装，即它不能用于定义 class 专属常量



如果编译器不允许上述做法，我们还可以通过 enum 来进行实现，即

```cpp
class Test
{
public:
	enum
    {
        size = 5    
    }
	int arr[size];
};
```

使用 enum ，将 size 变成一个表示 5 的记号。值得注意的是，我们**取一个 enum 类型的变量的地址是不合法的，同样地，取一个 #define 地地址也是不合法的**



#define 的另一种用法是定义宏，其优点是可以避免进行函数调用进而实现更快速的运算。当然，宏会出现一些意料之外的问题（哪怕我加了括号也一样），这个时候我们可以**使用 inline 来对宏进行替换**，它们的本质都是对代码块的替换

```cpp
#define FUN(X, Y) f((X) > (Y) ? (X) : (Y));//f为一个函数
```

该代码有如下问题

```cpp
int a = 5, b = 0;
FUN(++a, b);     //a 会自增两次
FUN(++a, b + 10);//a 只会自增一次
```

自然，我们可以用 inline 加上 template 来进行替换

```cpp
templete <typename T>
inline void FUN(const T& x, const T& y)
{
    f(x > y ? x : y);
}
```



# 2.尽可以使用 const



如果 const 出现在星号的左边， 表示该指针所指向的物是常量，即**不能通过该指针对这个值进行修改，但指针的指向可以被修改**；如果出现在星号右边，说明该指针是常量，即**该指针的指向不允许被修改，但该指针指向的值可以被指针修改**



在STL中，iterator本质上是个 T* 的指针，当我用 const 对其进行修饰时，说明该指针是一个常量，不能随便修改，即对应于 T * const。如果我希望STL给我模拟一个指向常量的指针，即对应于 T const *，那么我应该使用 const_iterator

```cpp
vector<int>vec;
const vector<int>::iterator it = vec.begin();
*it = 10;//Allow
//it++;//Error

vector<int>::const_iterator cIt = vec.begin();
//cIt = 10;//Error
cIt++;//Allow
```



令函数返回一个常量值（返回值被 const 修饰），这样做可以避免相关错误而造成的意外。

我们考虑一个自定义的数据类型 Real ，当我们对 * 进行重载运算符时，我们可以写成

```cpp
const Real operator* (const Real& e1, const Real& e2);
```

参数部分的 const 我们不做讨论，我们将重点放在返回值上。在返回值那里加上 const 是为了避免因手误写成

```cpp
(a * b) = c;
```

而导致程序出错（说不定真的会有天才这么写吧）。对于函数的形参，**除非是该函数会修改这个值，否则都应该用 const 修饰**



## const 成员函数

对于 class 的成员函数，我们可以通过其常量性对其进行重载，即同一个重载函数对应于 const 对象版本和 non-const 对象版本

当然，我们需要知道：

* 常对象（被 const 修饰的对象）只能调用常函数（class 中被 const 修饰的函数）
* 常函数不能修改 class 当中任何 non-const 的成员，当然 const 成员可以被其修改

基于这两点，我们看下面的代码

```cpp
class Test
{
public:
	char& operator[](std::size_t pos)
	{
		return str[pos];
	}
	const char& operator[](std::size_t pos) const
	{
		return str[pos];//我们不允许常对象修改 class 内部的成员变量，因此在返回值那里要加上 const
	}
	Test(const std::string& str)
	{
		this->str = str;
	}
private:
	std::string str;
};
```



对于 non-const 对象而言，我们调用 [] 时用的是 non-const 成员函数，这也是通常情况；对于 const 对象而言，我们调用 [] 时用的是 const 成员函数，这里便可以于上面结合起来了。

在我们写函数的时候，如果形参不会对输入值进行改变，那么我们要加上 const 。而形参可以是 Test 类型的数据，如果在形参部分加上了 const ，那么就说明该形参是一个常对象，它不能调用 non-const 成员函数。

因此，**当成员函数不会改变 class 中的任何一个成员（包括 const 和 non-const）时，我们写重载函数时需要写两个**



我们刚刚所讨论的全部都是基于 const 对象与 const 成员函数不能修改 class 内部的成员变量这一点的，如果我 class 的内部当中的部分数据被 const 对象与 const 成员函数所修改是允许的，即我希望 const 成员函数能够修改部分 class 当中的成员变量。

为了应对这一需求，**我们可以在变量前面加上 mutable 来允许该变量可以被 const 所修饰的成员函数来修改**

我们看如下代码

```cpp
class CTest
{
public:
	char& operator[](std::size_t pos)
	{
		return str[pos];
	}
	const char& operator[](std::size_t pos) const
	{
		return str[pos];
	}
	std::size_t length() const
	{
		if (!lengthIsValid)
		{
			Length = std::strlen(str);
			lengthIsValid = true;
		}
		return Length;
	}
private:
	char* str;
	mutable std::size_t Length;//最近一次计算的长度
	mutable bool lengthIsValid;//目前长度是否有效
};
```



对于 length 函数，它并不会改变 str 的值，仅仅只是想获取其长度。但于此同时我们需要对该长度是否有效进行检验，这就必定会导致需要修改其成员变量，而 mutable 则很好地解决了这个问题。

事实上，这个地方我们还有一个很严重的问题，就是我们的重载函数写了两个版本，而这两个版本的函数体是完全一样的！！！作为一个优雅的程序员，你怎么可能允许这种事情发生，当然关于这个问题，我们也有其解决办法。嘛，今天就先到这里，明天我们再看。



首先，我们回顾一下C风格地转型动作

(T) expression     //将 expression 转型为 T

函数类型是这样的：

T(expression)     //将 expression 转型为T

C++提供四种新式类型转换

* const_cast<T>( expression )
* dynamic_cast<T>( expression )
* reinterpret_cast<T>( expression )
* static_cast<T>( expression )

它们的作用为

1. const_cast 通常用于将对象的常量性移除，即将 const 类型的对象转换为对应 non-const 类型的对象
2. dynamic_cast 主要用于执行“安全向下转型“(safe downcasting) ，也就是用来决定某对象是否归属继承体系中的某个类型
3. reinterpret_cast 意图执行低级转型，实际动作（及结果）可能取决于编译器，因此它是不可移植的。例如将一个 pointer to int 转型为 int。
4. static_cast 用来强迫隐式转换，例如将 nont-const 对象转换为 const 对象，或将 int 转为 double 等待



知道了这些之后，我们再来看那个代码复用的问题。我们有两个一样的函数，如果我能在一个函数中调用另一个函数，那么我就可以完美解决代码复用这个问题，那么现在问题的关键就变成我该在哪个函数中调用另一个函数。

如果我们考虑在调用 const 成员函数时，让传入的参数发生类型转换进而得以调用另一个函数，那么这就会导致违背 const 成员函数自身的承诺——不会改变对象的逻辑状态。

说人话就是 const 成员函数不允许传入的对象有任何的更改，但我想通过 const 函数调用 non-const 函数就必定需要发生转换，这里就产生了矛盾，因此我们采用这种——当我调用 non-const 函数时，对其发生类型转换进而调用 const 函数。实际代码为：

```cpp
char& operator[](std::size_t pos)
{
    return const_cast<char&>(static_cast<const CTest&>(*this)[pos]);
}
const char& operator[](std::size_t pos) const
{
    return str[pos];
}
```

这里类型转换发生了两次。**第一次是将该对象从 non-const 转换为 const** ，这一步实施完成后才能调用 const 成员函数。然后 const 成员函数返回的是 const char& ，我们需要将该类型转换成 char& ，**这里便是第二次转换**

有一点需要值得注意的是第一次转换的类型是 const CTest&。这里我的理解是：this 指针本身指向调用该成员函数的对象， *this 则是该对象的值，这个值的类型是 CTest& （它的类型应该是 CTest，但这里在C语言里面，C++引入了左值引用和右值引用的概率后，这里应当为 CTest&），我们需要在它的基础是加上 const ，于是便有了 const CTest&。如果不加这个引用那么它将不会更改 this 所指向的对象的值



# 3.确认对象被使用前已先被初始化



对于无任何成员的内置数据类型，  **我们需要在其使用前就手动将其初始化**。对于自定义数据类型，其初始化则需要靠构造函数，即**确保每一个构造函数都能将对象的每一个成员初始化**

考虑下面这个例子：

```cpp
class Test
{
public:
	Test(const string& e1, const vector<int>& e2, const int& e3)
	{
		str = e1;
		vec = e2;
		num = e3;
	}
private:
	string str;
	vector<int> vec;
	int num;
};
```

C++规定，**对象的成员变量的初始化动作发生在进入构造函数之前**。也就是说在 Test 构造函数内，str 、 vec 、 num 都不是被初始化而是被赋值，它们的初始化**发生在调用构造函数之前**，即这些成员变量的 *default* 构造函数发生时机**早于**该对象的构造函数发生时机。但这一点对于内置数据类型（这里的 int）并不有效，即**对于内置数据类型就是在对象的构造函数内初始化的**

我们考察上面这一过程，发现调用该对象的构造函数时发生了：调用该成员变量的 *default* 构造函数和对该成员变量进行赋值。那么 *default* 构造函数所做的工作就被浪费了，想要避免这种情况发生，我们可以使用初始化列表

将上述构造函数改为

```cpp
Test(const string& e1, const vector<int>& e2, const int& e3) :
	str(e1),
	vec(e2),
	num(e3)
{ }
```

采用初始化列表之后，成员变量便会调用 *copy* 构造函数来进行初始化。

当然，在该对象的 *default* 构造函数内，我们需要 *default* 构造一个成员变量，我们可以这么写：

```cpp
Test() :
	str(),
	vec(),
	num(0)
{ }
```

总结一下就是**最后使用初始化列表，并且要列出所有的成员变量**

当然，如果变量很多，或者存在多重继承的情况下，可以把那些”初始化和赋值看起来是一样“的变量封装起来（通常是private权限），供构造函数调用。这种做法适用于该成员变量需要**从文件或者数据库中读入的情况**



## 初始化次序

对于一个 class 当中的成员变量而言，它们的初始化是有顺序的，它们必定是按照**从上到下**的顺序来进行初始化，尽管在初始化列表那里可能写的不一样（但这并没有关系）

这样的好处在于，如果存在一个数组，其大小需要用到该 class 中其他的成员变量，我们只需要将该成员变量**先于**该数组初始化即可，并且这里的**先于**是可控的（毕竟只需要放在数组定义的前面就行）

在此，我们来考虑一个更深层次的问题——如果我写了多个源文件，这些源文件当中的变量需要相互初始化，我该如何确定它们的初始化次序？说的专业一点就是：不同编译单元内定义的 non-local static 对象的初始化次序

我们先看 static 对象。所谓 static 对象，其生命周期是从被构造那一刻起一直到程序结束为止。很显然，这包括 global 对象、定义在 namespace 作用域下的对象、在 class 内、在函数内、以及在 file 作用域内被 static 修饰的对象。程序结束时 static 对象会被自动销毁，在 main 函数的结尾会自动调用它们的析构代码

这里有一个分类是：**如果是在函数内定义的 static 对象，称为 local static 对象**（相对于函数而言是 local 的），**其余的都是 non-local static 对象**

所谓编译单元是指产出单一目标文件（ obj 文件，一个源文件会对应一个 obj 文件）的那些源码。

明白了这些概念之后上面那个问题可以更加清晰地表述为：如果某个编译单元内的 non-local static 对象使用了另外一个编译单元内的 non-local static 对象，但它所使用的这个对象可能并没有在它前面完成初始化。这是因为C++对”定义于不同编译单元内的 non-local static 对象“的初始化次序并无规定。（C++居然对这个没有规定，我直接 虎躯一震.jpg 加 黑人问号.jpg ）

我们用具体实现来分析这个问题

目前我们有一个 class ，并且用 extern 声明了一个变量供其他源文件使用

```cpp
class Fun
{
public:
	size_t Cal() const;//其中一个成员函数
};

extern Fun tfs;
```

其他源文件使用了外部变量 tfs 。你也可以用这个 class 来创建对象

```cpp
class Dir
{
public:
	Dir()
	{
		size_t tem = tfs.Cal();//使用 tfs 来创建对象
	}
};

Dir temp;
```

这个时候就会出现上面所说的问题。那么问题是我们要怎么解决呢？

我们将每个 non-local static 对象都半岛自己的专属函数里面去，在此函数内将该变量声明为 static ，并且该函数返回该变量的 reference。也就是说，我们用一个函数来对 non-local static 对象进行封装，将其变为 local static 对象

具体实现为：

```cpp
class Fun
{
public:
	size_t Cal() const;//其中一个成员函数
};
//核心在这里
inline Fun& tfs()
{
	static Fun tmp;
	return tmp;
}

class Dir
{
public:
	Dir()
	{
		size_t tem = tfs().Cal();//这里发生了变化
	}
};

inline Dir& temp()//直接使用 temp 函数来创建对象，当然这是在其他源文件需要使用 temp 对象的情况下才需要这么做
{
	static Dir tmp;
	return tmp;
}
```

**这种封装在频繁调用的情况下可以写成 inline 的形式**



# 4.了解C++默默编写并调用了哪些函数



当我写下一个 class 时，编译器会自动帮我创建 *default* 构造函数、*copy* 构造函数、 *copy assignment* 操作符和一个析构函数，这些函数都是 public 和 inline 的。当然，这些函数**只有在被调用时才会创建**

```cpp
class Empty
{
    Empty() {}
    Empty(const Empty& e1) {}
    ~Empty() {}
    Empty& operator=(const Empty& e1) {}
}
```

在这里我们需要注意的是赋值操作符，这个函数有的时候编译器并不会帮你创建

编译器自动创建的 *copy assignment* 操作符是逐字节赋值（这当然会引发深拷贝的问题，但我们暂且不提这一点），也就是说它会将新对象的成员变量全部**赋值**为原对象的成员变量（这里是赋值，不是初始化）。

那么这里的问题就是如果成员变量当中存在 referencd 或者 const 类型，该对象已经完成初始化了（也就是前面的二者已经有值了），这个时候如果调用编译器创建的 *copy assignment* 操作符，就会导致新的对象的 reference 或者 const 成员的值发生改变，这当然是不允许的，因此编译器会禁止这种行为。这就需要我们手动写 *copy assignment* 操作符了。
