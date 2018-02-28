#include <cassert>
#include <memory>
#include <type_traits>
#include <utility>
#include <iostream>

// before
template <typename Concrete, typename... Ts>
std::enable_if_t<std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete> >
constructArgsOld(Ts&&... params)
{
	std::cout << __func__ << " templated..." << std::endl;
    return std::make_unique<Concrete>(std::forward<Ts>(params)...);
}

template <typename Concrete, typename... Ts>
std::enable_if_t<!std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete> >
constructArgsOld(...)
{
	std::cout << __func__ << "(...)" << std::endl;
    return nullptr;
}

template <typename Concrete, typename... Ts>
std::unique_ptr<Concrete> constructArgs(Ts&&... params)
{ 
std::cout << __func__ << ": ";
((std::cout << params << ", "), ...);
std::cout << "\n";
    
  if constexpr (std::is_constructible_v<Concrete, Ts...>)
      return std::make_unique<Concrete>(std::forward<Ts>(params)...);
   else
       return nullptr;
}

class IRenderer
{
public:
	virtual ~IRenderer() { }
	
	virtual void render() = 0;
};

class MesaRenderer : public IRenderer
{
public:
	MesaRenderer() { }
	
	void render() override { }
};

class GLRenderer : public IRenderer
{
public:
	explicit GLRenderer(const std::string& ) { }
	
	void render() override { }
};

class DXRenderer : public IRenderer
{
public:
	explicit DXRenderer(int , int ) { }
	
	void render() override { }
};

template <typename... Ts> 
std::unique_ptr<IRenderer> createRenderer(const std::string &name, Ts&&... params)
{
	std::cout << __func__ << ", " << name << std::endl;
    if (name == "Mesa")
		return constructArgsOld<MesaRenderer, Ts...>(std::forward<Ts>(params)...);
    else if (name == "GL")
		return constructArgsOld<GLRenderer, Ts...>(std::forward<Ts>(params)...);
    else if (name == "DX")
		return constructArgsOld<DXRenderer, Ts...>(std::forward<Ts>(params)...);

	std::cout << "nullptr from \'create\'" << std::endl;
    return nullptr;
}

int main()
{
    auto noArgs = createRenderer("Mesa");
    assert(noArgs);
    auto oneArg = createRenderer("GL", "hello");
    assert(oneArg);
    auto twoArgs = createRenderer("DX", 2, 2.0);
    assert(twoArgs);
    auto nothing = createRenderer("SomethingElse", 'a');
    assert(!nothing);
}