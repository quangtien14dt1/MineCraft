/*
 * autocreate_ptr - create-on-access auto-deleting pointer
 *
 * Useful for implementing the Singleton pattern.
 * Note: The instance never gets deleted. This is fine if the
 * destructor only frees memory, but may be problematic if it needs to
 * free other resources.
 */
#pragma once

template <class X> class autocreate_ptr
{
public:
    typedef X element_type;

    autocreate_ptr() throw() : itsPtr(nullptr) {}
    ~autocreate_ptr() { delete itsPtr; }
    X& operator*() { create(); return *itsPtr; }
    X* operator->() { create(); return itsPtr; }
    X* get() { create(); return itsPtr; }
private:
    X* itsPtr;
    void create() { if (!itsPtr) itsPtr = new X; }
    autocreate_ptr(const autocreate_ptr&) {}
    autocreate_ptr& operator=(const autocreate_ptr&) {}
};

