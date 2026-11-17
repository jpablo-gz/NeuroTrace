#ifndef NEUROTRACE_ERROR_H
#define NEUROTRACE_ERROR_H

// includes:
#include <stdexcept>
#include <string>

// Base error class for NeuroTrace
class NeuroTraceError : public std::runtime_error {
public:
    explicit NeuroTraceError(const std::string& message): std::runtime_error(message){}
};

// Error for dimension issues
class DimensionError : public NeuroTraceError {
public:
    explicit DimensionError(const std::string& message): NeuroTraceError(message){}
};

// Error for index issues
class IndexError : public NeuroTraceError {
public:
    explicit IndexError(const std::string& message): NeuroTraceError(message){}
};

#endif // NEUROTRACE_ERROR_H