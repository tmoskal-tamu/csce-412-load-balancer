#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a request sent to the server.
 * 
 * A Request contains information about the IP addresses involved, 
 * the amount of time required to process the request, and the type 
 * of job (e.g., 'P' for processing, 'S' for streaming).
 */
class Request {
private:
    std::string ipIn;  ///< IP address of the client making the request
    std::string ipOut; ///< IP address of the server responding to the request
    int time;          ///< Time required to process the request
    char jobType;      ///< Type of job ('P' for processing, 'S' for streaming)

public:
    /**
     * @brief Constructs a request with given parameters.
     * @param ipIn_ IP address of the client.
     * @param ipOut_ IP address of the server.
     * @param time_ Processing time for the request.
     * @param jobType_ Type of job ('P' or 'S').
     */
    Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_);

    /**
     * @brief Gets the IP address of the client making the request.
     * @return The client's IP address.
     */
    std::string getIPIn() const;

    /**
     * @brief Gets the IP address of the server responding to the request.
     * @return The server's IP address.
     */
    std::string getIPOut() const;

    /**
     * @brief Gets the time required to process the request.
     * @return Processing time.
     */
    int getTime() const;

    /**
     * @brief Gets the type of job.
     * @return Job type ('P' or 'S').
     */
    char getJobType() const;
};

#endif // REQUEST_H
