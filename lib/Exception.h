//
// Created by root on 7/14/18.
//

#ifndef IADS_EXCEPTION_H
#define IADS_EXCEPTION_H

#include <exception>
#include <boost/exception/all.hpp>

struct Exception:
    virtual std::exception,
    virtual boost::exception {
};

typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;

#endif //IADS_EXCEPTION_H
