//
// Created by root on 7/15/18.
//

#ifndef IADS_STEVY_H
#define IADS_STEVY_H

#include <vector>
#include <string>
#include "boost/regex.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/format.hpp"
#include <streambuf>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include "Exception.h"
#include "ThreadPool.h"
using namespace std;

typedef boost::property_tree::ptree sptree;
typedef boost::property_tree::ptree::iterator siterator;

#endif //IADS_STEVY_H
