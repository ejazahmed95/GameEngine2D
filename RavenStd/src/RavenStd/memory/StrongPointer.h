#pragma once
#include "ReferenceCounters.h"
#include "../Logger.h"

namespace RavenStd {
	
	template<class T> class WeakPtr;

	template<class T>
	class StrongPtr
	{
		// friends of another (derived) type
		template<class U>
		friend class WeakPtr;
		template<class U>
		friend class StrongPtr;
	public:
		// constructs empty Strongptr.
		// operator==() and operator bool() will return false;
		StrongPtr() : m_Ptr(nullptr), m_Counters(nullptr) {}

		explicit StrongPtr(T* i_ptr) : m_Ptr(i_ptr),
			m_Counters(i_ptr ? new ReferenceCounters(1, 0) : nullptr) {}

		// Copy Constructor from StrongPtr to same type
		StrongPtr(const StrongPtr& i_other): m_Ptr(i_other.m_Ptr), m_Counters(i_other.m_Counters) {
			m_Counters->IncStrongRefs();
		}

		// Copy Constructor from StrongPtr to derived type
		template<class U>
		explicit StrongPtr(const StrongPtr<U>& i_other): m_Ptr(static_cast<T*>(i_other.m_Ptr)), m_Counters(i_other.m_Counters) {
			m_Counters->IncStrongRefs();
		}

		// Move Copy Constructor from StrongPtr of same type
		StrongPtr(StrongPtr&& i_other): m_Ptr(i_other.m_Ptr), m_Counters(i_other.m_Counters) {
			m_Counters->IncStrongRefs();
		}

		// Move Copy Constructor from StrongPtr of derived type
		template<class U>
		explicit StrongPtr(StrongPtr<U>&& i_other): m_Ptr(static_cast<T*>(i_other.m_Ptr)), m_Counters(i_other.m_Counters) {
			m_Counters->IncStrongRefs();
		}

		// Copy Constructor called by WeakPointer
		explicit StrongPtr(T* i_ptr, ReferenceCounters* counters) {
			m_Ptr = i_ptr;
			m_Counters = counters;
			if (m_Counters) m_Counters->IncStrongRefs();
		}

		template<class U>
		explicit StrongPtr(U* i_ptr, ReferenceCounters* counters) {
			m_Ptr = static_cast<T*>(i_ptr);
			m_Counters = counters;
			if (m_Counters) m_Counters->IncStrongRefs();
		}

		// Copy Constructor from WeakPtr of derived type
		// template<class U>
		// StrongPtr(const WeakPtr<U>& i_other);

		// Assignment Operators
		StrongPtr& operator=(const StrongPtr& i_other) {
			reduceCount();
			m_Ptr = i_other.m_Ptr;
			m_Counters = i_other.m_Counters;
			m_Counters->IncStrongRefs();
			return (*this);
		}

		template<class U>
		StrongPtr& operator=(const StrongPtr<U>& i_other) {
			reduceCount();
			m_Ptr = static_cast<T*>(i_other.m_Ptr);
			m_Counters = i_other.m_Counters;
			m_Counters->IncStrongRefs();
			return (*this);
		}
		// Move Assignment Operators
		StrongPtr& operator=(StrongPtr&& i_other) {
			reduceCount();
			m_Ptr = i_other.m_Ptr;
			m_Counters = i_other.m_Counters;
			m_Counters->IncStrongRefs();
			return (*this);
		}

		template<class U>
		StrongPtr& operator=(StrongPtr<U>&& i_other) {
			reduceCount();
			m_Ptr = static_cast<T*>(i_other.m_Ptr);
			m_Counters = i_other.m_Counters;
			m_Counters->IncStrongRefs();
			return (*this);
		}

		// Assignment Operator - null specific - easier implementation
		StrongPtr& operator=(std::nullptr_t i_null) {
			reduceCount();
			m_Ptr = nullptr;
		}
		// Destructor
		~StrongPtr() {
			reduceCount();
		}

		// Equality operators
		bool operator==(const StrongPtr& i_other) const {
			return m_Ptr == i_other.m_Ptr;
		}
		template<class U>
		bool operator==(const StrongPtr<U>& i_other) const {
			return m_Ptr == static_cast<T*>(i_other.m_Ptr);
		}
		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		bool operator==(const WeakPtr<T>& i_other) const {
			return m_Ptr == i_other.m_Ptr;
		}
		template<class U>
		bool operator==(const WeakPtr<U>& i_other) const {
			return m_Ptr == static_cast<T*>(i_other.m_Ptr);
		}

		template<class U>
		bool operator==(U* i_ptr) const {
			return m_Ptr == static_cast<T*>(i_ptr);
		}

		bool operator==(std::nullptr_t nullp) const {
			return m_Ptr == nullptr;
		}
		// Inequality opertors
		bool operator!=(const StrongPtr& i_other) const {
			return !(*this == i_other);
		}
		template<class U>
		bool operator!=(const StrongPtr<U>& i_other) const {
			return !(*this == i_other);
		}
		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		bool operator!=(const WeakPtr<T>& i_other) const {
			return !(*this == i_other);
		}
		template<class U>
		bool operator!=(const WeakPtr<U>& i_other) const {
			!(*this == i_other);
		}
		// bool operator - used for using inside if() checks to see if it's a valid StrongPtr(underlying object hasn't been released)
		inline operator bool() const {
			return (*this) == nullptr;
		}
		// Access operator
		T* operator->() {
			return m_Ptr;
		}
		T& operator*() {
			return *m_Ptr;
		}
		// Access operator for const types
		const T* operator->() const {
			return m_Ptr;
		}
		const T& operator*() const {
			return *m_Ptr;
		}
	private:
		inline void reduceCount() {
			if (!m_Ptr) {
				return;
			}
			Log::T("Reducing Strong References; Strong References = " + std::to_string(m_Counters->StrongRefs()) + " | WeakRef=" + std::to_string(m_Counters->WeakRefs()));
			if (m_Counters->DecStrongRefs() == 0) {
				delete m_Ptr;
				m_Ptr = nullptr;
				if (m_Counters->WeakRefs() == 0) {
					delete m_Counters;
				}
				m_Counters = nullptr;
			}
		}
	private:
		T* m_Ptr;
		ReferenceCounters* m_Counters;
	};
} 