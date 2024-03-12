/*
 * counted_ptr - simple reference counted pointer.
 *
 * The is a non-intrusive implementation that allocates an additional
 * int and pointer for every counted object.
 */

#pragma once





template<class X> 
class counted_ptr
{
public:
	typedef X element_type;

	explicit counted_ptr(X* p = nullptr) : itsCounter(nullptr) {
		if (p) itsCounter = new counter(p);
	}

	~counted_ptr() { release(); }

	counted_ptr(const counted_ptr& r) throw() { acquire(r.itsCounter); }

	counted_ptr& operator=(const counted_ptr& r) {
		if (this != &r) {
			release();
			acquire(r.itsCounter);
		}
		return *this;
	}

	X& operator*()		const throw() { return *itsCounter->ptr; }
	X* operator->()		const throw() { return itsCounter->ptr; }
	X* get()			const throw() { return itsCounter ? itsCounter->ptr : 0; }
	bool unique()		const throw() { return itsCounter ? itsCounter->count == 1 : true; }
private:
	struct counter
	{
		counter(X* p = nullptr, unsigned c = 1) :ptr(p), count(c) {}
		X*			ptr;
		unsigned	count;
	}* itsCounter;

	void acquire(counter* c) throw() { // mean that function will not throw anything 
		itsCounter = c;
		if (c) ++c->count;
	}

	void release() {
		if (itsCounter) {
			if (--itsCounter->count == 0) {
				delete itsCounter->ptr;
				delete itsCounter;
			}
			itsCounter = 0;
		}
	}
};