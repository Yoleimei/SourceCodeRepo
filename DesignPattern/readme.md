# 设计模式的类型
## 创建型模式
这些设计模式提供了一种在创建对象的同时隐藏创建逻辑的方式，而不是是使用new运算符直接实例化对象。这使得程序在判断针对某个给定实例需要创建哪些对象时更加灵活。
- 工厂模式 (Factory Pattern)
- 抽象工厂模式 (Abstract Factory Pattern)
- 单例模式 (Singleton Pattern)
- 建造者模式 (Builder Pattern)
- 原型模式 (Prototype Pattern)
## 结构型模式
这些设计模式关注类和对象的组合。继承的概念被用来组合接口和定义组合对象获得新功能的方式。
- 适配器模式 (Adapter Pattern)
- 桥接模式 (Bridge Pattern)
- 过滤器模式 (Filter Pattern)
- 组合模式 (Composite Pattern)
- 装饰器模式 (Decorator Pattern)
- 外观模式 (Facade Pattern)
- 享元模式 (Flyweight Pattern)
- 代理模式 (Proxy Pattern)
## 行为型模式
这些设计模式特别关注对象之间的通信。
- 责任链模式 (Chain of Responsibility Pattern)
- 命令模式 (Command Pattern)
- 解释器模式 (Interpreter Pattern)
- 中介者模式 (Mediator Pattern)
- 备忘录模式 (Memento Pattern)
- 观察者模式 (Observer Pattern)
- 状态模式 (State Pattern)
- 空对象模式 (Null Object Pattern)
- 策略模式 (Strategy Pattern)
- 模板模式 (Template Pattern)
- 访问者模式 (Visitor Pattern)

# 设计模式的六大原则
## 开闭原则 (Open Close Principle)
对扩展开发，对修改关闭。想要达到这样的效果，需要使用接口和抽象类。
## 里氏替代原则 (Liskov Substitution Principle)
任何基类可以出现的地方，子类一定可以出现。
## 依赖倒转原则 (Dependency Inversion Principle)
针对接口编程，依赖于抽象而不依赖于具体。
## 接口隔离原则 (Interface Segregation Principle)
使用多个隔离的接口，比使用单个接口要好。
## 迪米特法则 (Demeter Principle)
一个实体应当尽量少地与其他实体之间发生相互作用，使得系统功能模块相互独立。
## 合成复用原则 (Composite Reuse Principle)
尽量使用合成/聚合的方式，而不是使用继承。

# 工厂模式
``` cpp
class Shape;
class Circle : public Shape;
class Square : public Shape;
class ShapeFactory
{
public:
	Shape* getShape(std::string shape); // "Circle", "Square", ...
};
```

# 抽象工厂模式
``` cpp
class Shape;
class Circle : public Shape;
class Square : public Shape;
class ShapeFactory : public AbstractFactory
{
public:
	Shape* getShape(std::string shape); // "Circle", "Square", ...
};
class Color;
class Red : public Color;
class Green : public Color;
class ColorFactory : public AbstractFactory
{
public:
	Color* getColor(std::string color); // "Red", "Green", ...
};
class AbstractFactory
{
public:
	Shape* getShape(std::string shape); // "Circle", "Square", ...
	Color* getColor(std::string color); // "Red", "Green", ...
};
class FactoryProducer
{
public:
	AbstractFactory* getFactory(std::string factory); // "Shape", "Color", ...
};
```

# 单例模式
略

# 建造者模式
``` cpp
class Packing
{
public:
	std::string pack();
};
class Wrapper : public Packing
{
public:
	std::string pack();
};
class Bottle : public Packing
{
public:
	std::string pack();
};
class Item
{
public:
	std::string name();
	Packing* packing();
	float price();
};
class Burger : public Item
{
public:
	std::string name();
	Packing* packing() { return new Wrapper(); }
	float price();
};
class ColdDrink : public Item
{
public:
	std::string name();
	Packing* packing() { return new Bottle(); }
	float price();
};
class VegBurger : public Burger
{
public:
	std::string name() { return "Veg Burger"; }
	float price() { return 10.0f; }
};
class Coke : public ColdDrink
{
public:
	std::string name() { return "Coke"; }
	float price() { return 4.0f; }
};
class Meal
{
public:
	void addItem(Item item);
	void showItems();
	float getCost();
private:
	std::list<Item> items;
};
class MealBuilder
{
public:
	Meal* prepareTaocan1();
	Meal* prepareTaocan2();
};
```

# 原型模式
拷贝构造

# 适配器模式
意图: 将一个类的接口转换成客户希望的另一个接口。适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作  
主要解决：主要解决在软件系统中，常常要将一些现存的对象放到新的环境中，而新环境要求的接口是现对象不能满足的。

# 桥接模式
???

# 过滤器模式
???

# 组合模式
树状结构?

# 装饰器模式
意图：动态的给一个对象添加一些额外的职责。就增加功能来说，装饰器模式相比生成子类更为灵活。
主要解决：一般的，我们为了扩展一个类经常使用继承方式实现，由于继承为类引入静态特征，并且随着扩展功能的增多，子类会很膨胀。

#  外观模式
``` cpp
class Shape
{
public:
	void draw();
};
class Circle : public Shape
{
public:
	void draw() {}
};
class Square : public Shape
{
public:
	void draw() {}
};
class ShapeMaker
{
public:
	void drawCircle();
	void drawSquare();
private:
	Shape* circle;
	Shape* square;
};
```

# 享元模式
意图：运用共享技术有效地支持大量细粒度的对象
主要解决：在有大量对象时，有可能会造成内存溢出，我们把其中共同的部分抽象出来，如果有相同的业务请求，直接返回在内存中已有的对象，避免重新创建。

# 代理模式
跨进程等

# 责任链模式
``` cpp
class AbstractLogger
{
public:
	void setNextLogger();
	void logMessage();
private:
	int level;
	AbstractLogger* nextLogger;
};
```

# 命令模式
``` cpp
class Request
{
public:
	void buy();
	void sell();
};
class Command
{
public:
	void execute();
};
class Buy : public Command
{
public:
	void execute();
private:
	Request* request;
};
class Sell : public Command
{
public:
	void execute();
private:
	Request* request;
};
class xxx
{
public:
	void placeCommands() { for(command ...) { command.execute(); } }
private:
	std::list<Command> commands;
};
```

# 解释器模式
解释特定的上下文，SQL解析、符号处理引擎等。

# 迭代器模式
C++ STL

# 中介者模式
意图：用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显示地相互作用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
主要解决：对象与对象之间存在大量的关联关系，这样势必会导致系统的结构变得很复杂，同时若一个对象发生改变，我们也需要跟踪与之相关联的对象，同时做出相应的处理。
``` cpp
class ChatRoom
{
public:
	static void showMessage();
};
class User
{
public:
	void setName();
	void sendMessage() { ChatRoom.showMessage(); }
private:
	std::string name;
};
```

# 备忘录模式
只用于有撤销动作

# 观察者模式
``` cpp
class Subject
{
public:
	void setNumber;
	void notifyAllObservers();
private;
	int number;
	std::list<Observer> observers;
};
class Observer
{
public:
	void update();
private:
	Subject* subject;
};
class BinaryObserver : public Observer
{
public:
	void update() {}
};
class HexObserver : public Observer
{
public:
	void update() {}
};
```

# 状态模式
``` cpp
class State
{
public:
	void doAction(Context context);
};
class StartState : public State
{
public:
	void doAction(Context context);
}；
class StopState : public State
{
public:
	void doAction(Context context);
};
class Context
{
public:
	void setState(State state);
private:
	State* state();
};
```

# 策略模式
``` cpp
class Operation
{
public:
	int doOperation(int, int);
};
class OperationAdd : public Operation
{
public:
	int doOperation(int, int);
};
class OperationSubstract : public Operation
{
public:
	int doOperation(int, int);
};
class Context
{
public:
	void executeOperation(int, int);
private:
	Operation* operation;
};
```

# 模板模式
将通用算法抽象出来作为基类，在子类中实现
``` cpp
class Handler
{
public:
	void initialize();
	void start();
	void run();
	void stop();
};
```

# 访问者模式
???