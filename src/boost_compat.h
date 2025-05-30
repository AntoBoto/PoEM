// Copyright (c) 2022 The BrrrFren Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_BOOST_COMPAT_H
#define BITCOIN_BOOST_COMPAT_H

// Include this first to prevent any system headers from polluting the namespace
#include <cstddef>

// Save any existing width macro
#pragma push_macro("width")
#undef width

// Include standard headers that might be affected by macros
#include <iomanip>
#include <ios>
#include <iostream>

// Now include Boost headers in the correct order
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>

// Include all Boost type traits headers that we might need
#include <boost/type_traits.hpp>

// Include Boost smart pointers
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

// Include Boost utility headers
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/string_view.hpp>

// Include Boost function and bind
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Include Boost thread and synchronization
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

// Include Boost filesystem
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

// Include Boost program options
#include <boost/program_options.hpp>

// Include Boost algorithm
#include <boost/algorithm/string.hpp>

// Include Boost range
#include <boost/range/iterator_range.hpp>

// Include Boost optional
#include <boost/optional.hpp>

// Include Boost variant
#include <boost/variant.hpp>

// Include Boost any
#include <boost/any.hpp>

// Include Boost date_time
#include <boost/date_time/posix_time/posix_time.hpp>

// Include Boost signals2
#include <boost/signals2/signal.hpp>

// Include Boost asio
#include <boost/asio.hpp>

// Include Boost interprocess
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_union.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_object.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_compound.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_standard_layout.hpp>
#include <boost/type_traits/is_literal_type.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_destructor.hpp>
#include <boost/type_traits/has_virtual_destructor.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_volatile.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/remove_all_extents.hpp>

// Now include shared_ptr with all type traits available
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/detail/sp_forward.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/smart_ptr/detail/sp_disable_deprecated.hpp>
#include <boost/smart_ptr/detail/sp_convertible.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/smart_ptr/detail/sp_has_sync.hpp>
#include <boost/smart_ptr/detail/sp_has_gcc_intrinsics.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_intrinsics.hpp>
#include <boost/smart_ptr/detail/sp_has_win32_srw_mutex.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_pause.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_builtins.hpp>
#include <boost/smart_ptr/detail/sp_has_gcc_builtin.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_intrinsics.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_pause.hpp>
#include <boost/smart_ptr/detail/sp_has_sync_builtins.hpp>

// Now include signals2 with all dependencies available
#include <boost/signals2/signal.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/slot.hpp>
#include <boost/signals2/variadic_slot.hpp>
#include <boost/signals2/mutex.hpp>
#include <boost/signals2/dummy_mutex.hpp>
#include <boost/signals2/shared_connection_block.hpp>
#include <boost/signals2/deconstruct.hpp>
#include <boost/signals2/deconstruct_ptr.hpp>
#include <boost/signals2/optional_last_value.hpp>
#include <boost/signals2/last_value.hpp>
#include <boost/signals2/signal_type.hpp>

// Include other boost headers that might be needed
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/lock_types.hpp>
#include <boost/thread/lock_algorithms.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/lockable_concepts.hpp>
#include <boost/thread/lockable_traits.hpp>
#include <boost/thread/lock_traits.hpp>
#include <boost/thread/lockable_concepts.hpp>
#include <boost/thread/lockable_traits.hpp>
#include <boost/thread/lock_traits.hpp>

// Restore the width macro if it was defined
#pragma pop_macro("width")

// If width was defined, make sure it's not going to cause problems
#ifdef width
#undef width
#endif

#endif // BITCOIN_BOOST_COMPAT_H
