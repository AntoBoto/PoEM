// Copyright (c) 2022 The BrrrFren Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef BITCOIN_BOOST_COMPAT_H
#define BITCOIN_BOOST_COMPAT_H

// Include shared_ptr first to ensure it's complete
#include <boost/shared_ptr.hpp>

// Undefine problematic macros that might be defined by system headers
#ifdef width
#undef width
#endif

// Now include other boost headers
#include <boost/thread.hpp>

// Include signals2 after shared_ptr is complete
#include <boost/signals2/signal.hpp>

// Include boost exception headers after we've handled the width macro
#include <boost/exception/all.hpp>

#endif // BITCOIN_BOOST_COMPAT_H
