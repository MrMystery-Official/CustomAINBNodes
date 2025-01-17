#ifndef SEAD_CRITICAL_SECTION_H_
#define SEAD_CRITICAL_SECTION_H_

#if defined(cafe)
#include <cafe.h>
#elif defined(NNSDK)
#include <nn/os.h>
#endif

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace sead
{
class Heap;

class CriticalSection
{
public:
    CriticalSection();
    ~CriticalSection();

    CriticalSection(const CriticalSection&) = delete;
    CriticalSection& operator=(const CriticalSection&) = delete;

    void lock();
    bool tryLock();
    void unlock();

    // For compatibility with the standard Lockable concept.
    bool try_lock() { return tryLock(); }

#if defined(cafe)
    OSMutex mCriticalSectionInner;
#elif defined(NNSDK)
    nn::os::MutexType mCriticalSectionInner;
#else
#error "Unknown platform"
#endif
};
#if defined(NNSDK)
static_assert(sizeof(CriticalSection) == 0x20);
#endif

}  // namespace sead

#endif  // SEAD_CRITICAL_SECTION_H_
