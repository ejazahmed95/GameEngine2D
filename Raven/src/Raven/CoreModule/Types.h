#pragma once
#include <type_traits>

namespace Raven { namespace Types {
#ifdef WIN_64
	typedef int64_t t_uid;
#else
	typedef int32_t t_uid;
#endif
}}
