template<typename T, typename Y>
auto add (T v1, Y v2) -> decltype(v1 + v2)
{
    return v1 + v2;
}