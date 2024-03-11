#pragma once


template<typename T>
class counted_ptr {
public:
	counted_ptr(T* ptr = nullptr) : m_ptr(ptr), m_count(new int(1)) {};

	counted_ptr(const counted_ptr<T>& other) : m_ptr(other.m_ptr), m_count(other.m_count) {
		(*m_count)++;
	}

	~counted_ptr() { release(); }

	T* get() const {
		return m_ptr;
	}

	int count() const {
		return *m_count;
	}

	counted_ptr <T>& operator = (const counted_ptr<T>&other) { 
		if (this != &other) {
			release();
			m_ptr = other.m_ptr;
			m_count = other.m_count;
			(*m_count)++;
		}
		return this;
	}

private:
	T* m_ptr;
	int* m_count;

	void release() {
		(*m_count)--;
		if (*m_count == 0) {
			delete m_ptr;
			delete m_count;
		}
		m_ptr = nullptr;
		m_count = nullptr;
	}
};