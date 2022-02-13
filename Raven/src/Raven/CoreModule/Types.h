#pragma once
#include <type_traits>

namespace Raven { namespace Types {
	// TODO: Create different ids for TypeID and UID
#ifdef WIN_64
	typedef int64_t t_uid;
#else
	typedef int32_t t_uid;
#endif
}}
