#pragma once
#include "/home/edward/projects/rpc/rpc/include/rpc/coroutine_enclave/enclave_fix.h"

#include <string>
// #include <sys/epoll.h>
#include <stdint.h>
enum EPOLL_EVENTS
{
    EPOLLIN = 0x001,
#define EPOLLIN EPOLLIN
    EPOLLPRI = 0x002,
#define EPOLLPRI EPOLLPRI
    EPOLLOUT = 0x004,
#define EPOLLOUT EPOLLOUT
    EPOLLRDNORM = 0x040,
#define EPOLLRDNORM EPOLLRDNORM
    EPOLLRDBAND = 0x080,
#define EPOLLRDBAND EPOLLRDBAND
    EPOLLWRNORM = 0x100,
#define EPOLLWRNORM EPOLLWRNORM
    EPOLLWRBAND = 0x200,
#define EPOLLWRBAND EPOLLWRBAND
    EPOLLMSG = 0x400,
#define EPOLLMSG EPOLLMSG
    EPOLLERR = 0x008,
#define EPOLLERR EPOLLERR
    EPOLLHUP = 0x010,
#define EPOLLHUP EPOLLHUP
    EPOLLRDHUP = 0x2000,
#define EPOLLRDHUP EPOLLRDHUP
    EPOLLEXCLUSIVE = 1u << 28,
#define EPOLLEXCLUSIVE EPOLLEXCLUSIVE
    EPOLLWAKEUP = 1u << 29,
#define EPOLLWAKEUP EPOLLWAKEUP
    EPOLLONESHOT = 1u << 30,
#define EPOLLONESHOT EPOLLONESHOT
    EPOLLET = 1u << 31
#define EPOLLET EPOLLET
};

enum
{
    EPOLL_CLOEXEC = 02000000
#define EPOLL_CLOEXEC EPOLL_CLOEXEC
};

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
#define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface.  */
#define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface.  */
#define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure.  */

typedef union epoll_data
{
    void*    ptr;
    int      fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event
{
    uint32_t     events; /* Epoll events */
    epoll_data_t data;   /* User data variable */
};

// extern epoll_event __EPOLL_PACKED;

int epoll_create1(int);
int epoll_ctl(int, int, int, struct epoll_event*);
int close(int);
ssize_t write(int, const void*, size_t);
int epoll_wait(int , struct epoll_event*, int, int);

namespace coro
{
enum class poll_op : uint64_t
{
    /// Poll for read operations.
    read = EPOLLIN,
    /// Poll for write operations.
    write = EPOLLOUT,
    /// Poll for read and write operations.
    read_write = EPOLLIN | EPOLLOUT
};

inline auto poll_op_readable(poll_op op) -> bool
{
    return (static_cast<uint64_t>(op) & EPOLLIN);
}

inline auto poll_op_writeable(poll_op op) -> bool
{
    return (static_cast<uint64_t>(op) & EPOLLOUT);
}

auto to_string(poll_op op) -> const std::string&;

enum class poll_status
{
    /// The poll operation was was successful.
    event,
    /// The poll operation timed out.
    timeout,
    /// The file descriptor had an error while polling.
    error,
    /// The file descriptor has been closed by the remote or an internal error/close.
    closed
};

auto to_string(poll_status status) -> const std::string&;

} // namespace coro
