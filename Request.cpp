#include "Request.h"

/**
 * @brief Constructs a request with the given IP addresses, processing time, and job type.
 * @param ipIn_ IP address of the client making the request.
 * @param ipOut_ IP address of the server responding to the request.
 * @param time_ Time required to process the request.
 * @param jobType_ Type of job ('P' for processing, 'S' for streaming).
 */
Request::Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_)
    : ipIn(ipIn_), ipOut(ipOut_), time(time_), jobType(jobType_) {}

/**
 * @brief Gets the IP address of the client making the request.
 * @return The client's IP address.
 */
std::string Request::getIPIn() const {
    return ipIn;
}

/**
 * @brief Gets the IP address of the server responding to the request.
 * @return The server's IP address.
 */
std::string Request::getIPOut() const {
    return ipOut;
}

/**
 * @brief Gets the time required to process the request.
 * @return Processing time in clock cycles.
 */
int Request::getTime() const {
    return time;
}

/**
 * @brief Gets the type of job.
 * @return The job type ('P' or 'S').
 */
char Request::getJobType() const {
    return jobType;
}
