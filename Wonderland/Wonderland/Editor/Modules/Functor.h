////////////////////////////////////////////////////////////////////////////////
// Filename: Functor.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

struct BaseFunctor
{
	virtual ~BaseFunctor() {}
	virtual void operator()() = 0;
};

template< typename TARGET, typename RESULT, typename... ARGS >
struct SpecializedFunctor : BaseFunctor
{
	SpecializedFunctor(TARGET* ptr, RESULT(TARGET::*pmfn)(ARGS...), ARGS... data)
		: fun(std::bind(pmfn, ptr, data...)) {}

	SpecializedFunctor(TARGET& ref, RESULT(TARGET::*pmfn)(ARGS...), ARGS... data)
		: fun(std::bind(pmfn, ref, data...)) {}

	virtual void operator()() override { fun(); }

private: std::function< void() > fun;
};

template< typename T, typename R, typename... ARGS > inline // helper to deduce the types
SpecializedFunctor<T, R, ARGS...> MakeFunctor(T* p, R(T::*pmf)(ARGS...), ARGS... data)
{
	return SpecializedFunctor<T, R, ARGS...>(p, pmf, data...);
}

template< typename T, typename R, typename... ARGS > inline // helper to deduce the types
SpecializedFunctor<T, R, ARGS...> MakeFunctor(T& r, R(T::*pmf)(ARGS...), ARGS... data)
{
	return SpecializedFunctor<T, R, ARGS...>(r, pmf, data...);
}