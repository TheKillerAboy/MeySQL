#include <iostream>
#include <boost/log/trivial.hpp>

int main(int, char*[])
{
    BOOST_LOG_TRIVIAL(error) << "This is an informational severity message";
    return 0;
}