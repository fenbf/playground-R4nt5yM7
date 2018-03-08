// code taken (with permission from https://h-deb.clg.qc.ca/WG21/PracticalCpp/Temperature.html)
// by Patrice Roy

#include <type_traits>

// C++11/14 version:
/*
template <class T>
constexpr T absolute(T arg) {
   return arg < 0 ? -arg : arg;
}

template <class T>
constexpr std::enable_if_t<std::is_floating_point<T>::value, bool> close_enough(T a, T b) {
   return absolute(a - b) < static_cast<T>(0.000001);
}
template <class T>
constexpr std::enable_if_t<!std::is_floating_point<T>::value, bool> close_enough(T a, T b) {
   return a == b;
}*/

// C++17:

template <class T>
constexpr T absolute(T arg) {
   return arg < 0 ? -arg : arg;
}

template <class T>
constexpr auto precision_threshold = T(0.000001);

template <class T>
constexpr bool close_enough(T a, T b) {
   if constexpr (std::is_floating_point_v<T>)
      return absolute(a - b) < precision_threshold<T>;
   else
      return a == b;
}

int main()
{
	[[maybe_unused]] auto c = close_enough(10.0f, 10.0f);
	[[maybe_unused]] auto d = close_enough(90l, 90l);
}