/*
 * Debug.hpp
 *
 *  Created on: Nov 5, 2013
 *      Author: michael
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <cassert>
#include <iostream>

#ifndef REPORT_LEVEL
#define REPORT_LEVEL 0
#endif

#define REPORT_REQUIRED_BASE 1
#define REPORT_REQUIRED_ERROR 2

//! message reporting

#if REPORT_LEVEL>=REPORT_REQUIRED_BASE
#define report(str) std::cout << str << std::endl
#else
#define report(str)
#endif

#if REPORT_LEVEL>=REPORT_REQUIRED_BASE
#define reportE(str) std::cerr << "Error: " << str << std::endl
#else
#define reportE(str)
#endif

//! named assertions

#if REPORT_LEVEL>=REPORT_REQUIRED_ERROR
#define assertM(cond, str) if (!cond) { \
		std::cout << "Assertion failed: " << str << std::endl; \
		assert(0 && cond); \
	}
#else
#define assertM(cond, str)
#endif

//! error reporting

#if REPORT_LEVEL>=REPORT_REQUIRED_ERROR
#define error(str) std::cerr << "Error: " << str << std::endl; \
	assert(0);
#else
#define error(str) reportE(str)
#endif

#endif /* DEBUG_HPP_ */
