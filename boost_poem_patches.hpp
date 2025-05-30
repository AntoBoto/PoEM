// POEM Project - Boost compatibility patches
// This header should be included in files that interact with Boost.Variant and Boost.Signals2

#ifndef POEM_BOOST_PATCHES_HPP
#define POEM_BOOST_PATCHES_HPP

// Simple basic includes without any special tricks
#include <cstddef>
#include <string>
#include <vector>

// Include Boost headers normally
#include <boost/variant/variant.hpp>
#include <boost/signals2/connection.hpp>

// Safe access utilities for Boost classes
namespace boost {
namespace poem_patches {

// Simple wrappers that maintain the same interface
template <typename VariantType, typename VisitorType>
inline typename VisitorType::result_type 
apply_visitor_safe(VisitorType& visitor, VariantType& variant) {
    return boost::apply_visitor(visitor, variant);
}

template <typename SignalType, typename SlotType>
inline boost::signals2::connection
connect_slot_safe(SignalType& signal, const SlotType& slot) {
    return signal.connect(slot);
}

} // namespace poem_patches
} // namespace boost

#endif // POEM_BOOST_PATCHES_HPP
