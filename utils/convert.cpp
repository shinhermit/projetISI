using namespace my;

template<typename T, typename U>
Convert<T,U>::Convert()
{}

template<typename T, typename U>
U Convert<T,U>::operator()(T t)
{
    std::istringstream iss;
    std::ostringstream oss;
    U u;

    oss << t;
    iss.str(oss.str());
    iss >> u;

    return u;
}
