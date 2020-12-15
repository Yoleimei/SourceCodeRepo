// shared_ptr constructor example
#include <iostream>
#include <memory>

struct C {int* data;};

int main () {
    std::shared_ptr<int> p1;
    std::shared_ptr<int> p2 (nullptr);
    std::shared_ptr<int> p3 (new int);
    std::shared_ptr<int> p4 (new int, std::default_delete<int>());
    std::shared_ptr<int> p5 (new int, [](int* p){delete p;}, std::allocator<int>());
    std::shared_ptr<int> p6 (p5);
    std::shared_ptr<int> p7 (std::move(p6));
    std::shared_ptr<int> p8 (std::unique_ptr<int>(new int));
    std::shared_ptr<C> obj (new C);
    std::shared_ptr<int> p9 (obj, obj->data);

    std::cout << "use_count:\n";
    std::cout << "p1: " << p1.get() << ", use_count: " << p1.use_count() << '\n';
    std::cout << "p2: " << p2.get() << ", use_count: " << p2.use_count() << '\n';
    std::cout << "p3: " << p3.get() << ", use_count: " << p3.use_count() << '\n';
    std::cout << "p4: " << p4.get() << ", use_count: " << p4.use_count() << '\n';
    std::cout << "p5: " << p5.get() << ", use_count: " << p5.use_count() << '\n';
    std::cout << "p6: " << p6.get() << ", use_count: " << p6.use_count() << '\n';
    std::cout << "p7: " << p7.get() << ", use_count: " << p7.use_count() << '\n';
    std::cout << "p8: " << p8.get() << ", use_count: " << p8.use_count() << '\n';
    std::cout << "p9: " << p9.get() << ", use_count: " << p9.use_count() << '\n';
    return 0;
}