
#include <iostream>
#include <type_traits>
#include <memory>

template <typename T>
struct is_smart_pointer_helper : public std::false_type {};

template <typename T>
struct is_smart_pointer_helper<std::shared_ptr<T> > : public std::true_type {};

template <typename T>
struct is_smart_pointer_helper<std::unique_ptr<T> > : public std::true_type {};

template <typename T>
struct is_smart_pointer_helper<std::weak_ptr<T> > : public std::true_type {};

template <typename T>
struct is_smart_pointer : public is_smart_pointer_helper<typename std::remove_cv<T>::type> {};

template <typename T>
typename std::enable_if<is_smart_pointer<T>::value, void>::type 
check_smart_pointer(const T& t)
{
	std::cout << "is smart pointer" << std::endl;
}

template <typename T>
typename std::enable_if<!is_smart_pointer<T>::value, void>::type 
check_smart_pointer(const T& t)
{
	std::cout << "not smart pointer" << std::endl;
}

int main()
{
	int* p(new int(2));
	std::shared_ptr<int> pp(new int(2));
	std::unique_ptr<int> upp(new int(4));

	check_smart_pointer(p);
	check_smart_pointer(pp);
	check_smart_pointer(upp);

	delete p;
	return 0;
}