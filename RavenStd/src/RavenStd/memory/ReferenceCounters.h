#pragma once
#include <cstdint>

typedef uint64_t ref_counter_t;
struct ReferenceCounters
{
	ReferenceCounters(ref_counter_t initialStrongReferences, ref_counter_t
		initialWeakReferences) :
		m_StrongReferences(initialStrongReferences),
		m_WeakReferences(initialWeakReferences)
	{}
	ref_counter_t StrongRefs() const { return m_StrongReferences; }
	ref_counter_t IncStrongRefs() { return ++m_StrongReferences; }
	ref_counter_t DecStrongRefs() { return --m_StrongReferences; }
	ref_counter_t WeakRefs() const { return m_WeakReferences; }
	ref_counter_t IncWeakRefs() { return ++m_WeakReferences; }
	ref_counter_t DecWeakRefs() { return --m_WeakReferences; }
private:
	ref_counter_t m_StrongReferences;
	ref_counter_t m_WeakReferences;
};