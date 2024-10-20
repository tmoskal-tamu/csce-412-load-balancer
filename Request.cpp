#include "Request.h"

Request::Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_) : ipIn(ipIn_), ipOut(ipOut_), time(time_), jobType(jobType_) {}

std::string Request::getIPIn() const {
    return ipIn;
}

std::string Request::getIPOut() const {
    return ipOut;
}

int Request::getTime() const {
    return time;
}

char Request::getJobType() const {
    return jobType;
}
