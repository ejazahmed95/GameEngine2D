#pragma once
#include "ReferenceCounters.h"
#include "StrongPointer.h"

namespace RavenStd {
	template<class T>
	class WeakPtr {
		template<class U>
		friend class StrongPtr;
		template<class U>
		friend class WeakPtr;
	public:
		// Constructor from StrongPtrs
		WeakPtr(const StrongPtr<T>& i_owner) : m_Ptr(i_owner.m_Ptr), m_Counters(i_owner.m_Counters) {
			m_Counters->IncWeakRefs();
		}

		// Constructor from Strong Ptr of derived type
		template<class U>
		WeakPtr(const StrongPtr<U>& i_owner) : m_Ptr(static_cast<T*>(i_owner.m_Ptr)), m_Counters(i_owner.m_Counters) {
			m_Counters->IncWeakRefs();
		}

		// Constructor from WeakPtrs
		WeakPtr(const WeakPtr& i_owner) : m_Ptr(i_owner.m_Ptr), m_Counters(i_owner.m_Counters) {
			m_Counters->IncWeakRefs();
		}

		template<class U>
		WeakPtr(const WeakPtr<U>& i_owner) : m_Ptr(i_owner.m_Ptr), m_Counters(i_owner.m_Counters) {
			m_Counters->IncWeakRefs();
		}

		// Destructor
		~WeakPtr() {
			Log::T("Reducing Weak References; Strong References = " + std::to_string(m_Counters->StrongRefs()) + " | WeakRef=" + std::to_string(m_Counters->WeakRefs()));
			if (m_Counters->DecWeakRefs() == 0) {
				if (m_Counters->StrongRefs() == 0) {
					delete m_Counters;
				}
			}
		}

		// Assignment operators
		WeakPtr& operator=(const WeakPtr& i_other) {
			m_Ptr = i_other.m_Ptr;
			m_Counters = i_other.m_Counters;
			m_Counters->IncWeakRefs();
			return *this;
		}

		template<class U>
		WeakPtr& operator=(const WeakPtr<U>& i_other) {
			m_Ptr = i_other.m_Ptr;
			m_Counters = i_other.m_Counters;
			m_Counters->IncWeakRefs();
			return *this;
		}

		WeakPtr& operator=(const StrongPtr<T>& i_other) {
			m_Ptr = i_other.m_Ptr;
			m_Counters = i_other.m_Counters;
			m_Counters->IncWeakRefs();
			return *this;
		}

		template<class U>
		WeakPtr& operator=(const StrongPtr<U>& i_other) {
			m_Ptr = static_cast<T*>(i_other.m_Ptr);
			m_Counters = i_other.m_Counters;
			m_Counters->IncWeakRefs();
			return *this;
		}

		// null specific version - easier implmentation
		WeakPtr<T>& operator=(std::nullptr_t i_null) {
			m_Ptr = nullptr;
			if (m_Counters->DecWeakRefs() == 0) {
				if (m_Counters->StrongRefs() == 0) {
					delete m_Counters;
				}
			}
			m_Counters = nullptr;
		}

		// Attempt to acquire a StrongPtr (Owner)
		// Just calls the Copy Construct StrongPtr(const WeakPtr, DestroyT>& i_other)
		// which should verify if the underlying object is valid and set itself
		// into the appropriate state (valid underlying pointer or empty (m_Ptr is null)
		inline StrongPtr<T> AcquireOwnership() {
			return StrongPtr<T>(this->m_Ptr, this->m_Counters);
		}

		inline bool operator==(const WeakPtr& i_other) {
			return m_Ptr == i_other.m_Ptr;
		}

		template<class U>
		inline bool operator==(const WeakPtr<U>& i_other) {
			return m_Ptr == static_cast<T*>(i_other.m_Ptr);
		}

		// Comparison operators
		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		inline bool operator==(const StrongPtr<T>& i_other) {
			if (m_Counters->StrongRefs() == 0) {
				return m_Counters == i_other.m_Counters;
			}
			else return m_Ptr == i_other.m_Ptr;
		}

		template<class U>
		inline bool operator==(const StrongPtr<U>& i_other) {
			if (m_Counters->StrongRefs() == 0) {
				return m_Counters == i_other.m_Counters;
			}
			else return m_Ptr == static_cast<T*>(i_other.m_Ptr);
		}

		inline bool operator==(T* i_ptr) {
			return m_Ptr == i_ptr;
		}

		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		inline bool operator!=(const StrongPtr<T>& i_other) {
			return m_Ptr != i_other.m_Ptr;
		}

		template<class U>
		inline bool operator!=(const StrongPtr<U>& i_other) {
			return m_Ptr != static_cast<T*>(i_other.m_Ptr);
		}

		template<class U>
		inline bool operator!=(const WeakPtr<U>& i_other) {
		}

		operator bool() const {
			return m_Ptr != nullptr;
		}

		void TestFunc() {
			// does nothing
		}

	private:
		T* m_Ptr;
		ReferenceCounters* m_Counters;
	};
}
