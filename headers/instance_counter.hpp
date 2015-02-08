#ifndef __UTILITY_INSTANCE_COUNTER_HPP__
#define __UTILITY_INSTANCE_COUNTER_HPP__

namespace Utility
{

template< typename _Base >
class InstanceCounter
{
public:
	unsigned getInstanceCount() const;

protected:
	InstanceCounter();
	~InstanceCounter();

private:
	static int ms_instanceCount;
};

template< typename _Base >
int InstanceCounter< _Base >::ms_instanceCount;

template< typename _Base >
InstanceCounter< _Base >::InstanceCounter()
{
	++ms_instanceCount;
}

template< typename _Base >
InstanceCounter< _Base >::~InstanceCounter()
{
	--ms_instanceCount;
}

template< typename _Base >
unsigned
InstanceCounter< _Base >::getInstanceCount() const
{
	return ms_instanceCount;
}

}

#endif
