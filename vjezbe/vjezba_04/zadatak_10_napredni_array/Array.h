#pragma once

#include <algorithm>
#include <utility>
#include <cstdlib>
#include <memory>

template <typename Array>
class Iterator {
	
public:

	typedef typename Array::value_type value_type;
	typedef typename Array::pointer pointer;
	typedef typename Array::reference reference;
	typedef Iterator Self;

	Iterator(pointer ptr)
		: m_Ptr{ ptr } {
	}

	Self& operator++() {
		++m_Ptr;
		return *this;
	}

	Self operator++(int) {
		Self it = *this;
		++(*this);
		return it;
	}

	Self& operator--() {
		--m_Ptr;
		return *this;
	}

	Self operator--(int) {
		Self it = *this;
		--(*this);
		return it;
	}

	pointer operator+(int val) {
		return m_Ptr + val;
	}

	pointer operator-(int val) {
		return m_Ptr - val;
	}

	pointer operator->() {
		return m_Ptr;
	}

	reference operator[](int idx) {
		return *(m_Ptr + idx);
	}

	reference operator*() {
		return *m_Ptr;
	}

	bool operator==(const Self& rhs) const {
		return m_Ptr == rhs.m_Ptr;
	}

	bool operator!=(const Self& rhs) const {
		return !(*this == rhs);
	}

	bool operator>(const Self& rhs) const {
		return m_Ptr > rhs.m_Ptr;
	}

	bool operator<(const Self& rhs) const {
		return m_Ptr < rhs.m_Ptr;
	}

private:
	pointer m_Ptr;

};

template <typename _Ty> 
class Array {

public:

	// Member types

	typedef _Ty value_type;
	typedef std::size_t size_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef _Ty&& rvalue_reference;
	typedef Iterator<Array<_Ty>> iterator;


	// Constructors / Destructors

	Array(const size_type& capacity)
		: m_Capacity{ capacity }, m_Size{ 0 }, m_Data{ nullptr } {
		m_Data = reinterpret_cast<pointer>(::operator new[](m_Capacity * sizeof(value_type)));
	}

	Array(const Array& lvalue)
		: Array{ lvalue.m_Capacity } {
		m_Size = lvalue.m_Size;
		for (size_type i{ 0 }; i < m_Size; ++i)
			new(&m_Data[i]) value_type{ lvalue.m_Data[i] };
	}

	Array(Array&& rvalue) noexcept
		: m_Capacity{ std::move(rvalue.m_Capacity) }, m_Size{ std::move(rvalue.m_Size) }, m_Data{ std::exchange(rvalue.m_Data, nullptr) } {
	}

	~Array() {
		Clear();
		::operator delete[](m_Data, m_Capacity * sizeof(value_type));
	}


	// Element access

	reference operator[](const size_type& idx) noexcept {
		return m_Data[idx];
	}
	constexpr const_reference operator[](const size_type& idx) const noexcept {
		return m_Data[idx];
	}

	reference At(const size_type& idx) {
		if (idx >= m_Size)
			throw std::out_of_range("ARRAY::OUT_OF_RANGE::idx greater than size");
		return m_Data[idx];
	}
	constexpr const_reference At(const size_type& idx) const {
		if (idx >= m_Size)
			throw std::out_of_range("ARRAY::OUT_OF_RANGE::idx greater than size");
		return m_Data[idx];
	}

	reference Front() noexcept {
		return m_Data[0];
	}
	constexpr const_reference Front() const noexcept {
		return m_Data[0];
	}

	reference Back() noexcept {
		return m_Data[m_Size - 1];
	}
	constexpr const_reference Back() const noexcept {
		return m_Data[m_Size - 1];
	}

	pointer Data() noexcept {
		return m_Data;
	}
	constexpr const_pointer Data() const noexcept {
		return m_Data;
	}

	// Iterators

	iterator begin() {
		return iterator{ m_Data };
	}

	iterator end() {
		return iterator{ m_Data + m_Size };
	}


	// Capacity

	constexpr size_type Size() const noexcept {
		return m_Size;
	}

	void SetSize(const size_type size) noexcept {
		m_Size = size;
	}

	constexpr size_type Capacity() const noexcept {
		return m_Capacity;
	}

	constexpr bool Empty() const noexcept {
		return m_Size == 0;
	}


	// Modifiers

	void Clear() noexcept {
		for (size_type i{ 0 }; i < m_Size; ++i)
			m_Data[i].~value_type();
		m_Size = 0;
	}

	template <typename... Args>
	void EmplaceBack(Args&&... args) {
		if (m_Size >= m_Capacity)
			throw std::out_of_range("ARRAY::OUT_OF_RANGE::max size");
		new(&m_Data[m_Size++]) value_type{ std::forward<Args>(args)... };
	}

	void PopBack() {
		if (m_Size == 0)
			throw std::out_of_range("ARRAY::OUT_OF_RANGE::min size");
		m_Data[--m_Size].~value_type();
	}


private:
	size_type m_Capacity;
	size_type m_Size;
	pointer m_Data;

};