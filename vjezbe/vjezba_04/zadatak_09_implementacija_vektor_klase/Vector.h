#pragma once

// VECTOR CLASS	- najbolje radi s korisnickim tipovima podataka i jednostavnim tipovima podataka
// u fileu se nalazi primjer Vektor2i tipa podataka koji ima definirane sve konstruktore,
// Vector klasa radi izvrsno s tim tipom podatka
// radi na nacin da maksimalno move-a objekte, a ne da ih kopira
// klasa ne podrzava std::string (testirano), std::vector i ostale STL tipove podataka

#include <initializer_list>
#include <algorithm>
#include <utility>

template <typename Vector>
class Iterator {

public:

	typedef typename Vector::value_type value_type;
	typedef typename Vector::pointer pointer;
	typedef typename Vector::reference reference;
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

	Self operator+(int val) {
		return m_Ptr + val;
	}

	Self operator-(int val) {
		return m_Ptr - val;
	}

	reference operator[](int idx) {
		return *(m_Ptr + idx);
	}

	pointer operator->() {
		return m_Ptr;
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

template <typename Vector>
class ConstIterator {
	
public:

	typedef typename Vector::value_type value_type;
	typedef typename Vector::const_pointer const_pointer;
	typedef typename Vector::const_reference const_reference;
	typedef ConstIterator Self;

	ConstIterator(const_pointer ptr)
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

	const_reference operator[](int idx) const {
		return *(m_Ptr + idx);
	}

	const_pointer operator->() const {
		return m_Ptr;
	}

	const_reference operator*() const {
		return *m_Ptr;
	}

	bool operator==(const Self& rhs) const {
		return m_Ptr == rhs.m_Ptr;
	}

	bool operator!=(const Self& rhs) const {
		return !(*this == rhs);
	}

private:
	const_pointer m_Ptr;

};

template <typename Vector>
class ReverseIterator {

public:

	typedef typename Vector::value_type value_type;
	typedef typename Vector::pointer pointer;
	typedef typename Vector::reference reference;
	typedef ReverseIterator Self;

	ReverseIterator(pointer ptr)
		: m_Ptr{ ptr } {
	}

	Self& operator++() {
		--m_Ptr;
		return *this;
	}

	Self operator++(int) {
		Self it = *this;
		--(*this);
		return it;
	}

	Self& operator--() {
		++m_Ptr;
		return *this;
	}

	Self operator--(int) {
		Self it = *this;
		++(*this);
		return it;
	}

	reference operator[](int idx) {
		return *(m_Ptr + idx);
	}

	pointer operator->() {
		return m_Ptr;
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


private:
	pointer m_Ptr;

};

template <typename Vector>
class ConstReverseIterator {

public:

	typedef typename Vector::value_type value_type;
	typedef typename Vector::const_pointer const_pointer;
	typedef typename Vector::const_reference const_reference;
	typedef ConstReverseIterator Self;

	ConstReverseIterator(const_pointer ptr)
		: m_Ptr{ ptr } {
	}

	Self& operator++() {
		--m_Ptr;
		return *this;
	}

	Self operator++(int) {
		Self it = *this;
		--(*this);
		return it;
	}

	Self& operator--() {
		++m_Ptr;
		return *this;
	}

	Self operator--(int) {
		Self it = *this;
		++(*this);
		return it;
	}

	const_reference operator[](int idx) const {
		return *(m_Ptr + idx);
	}

	const_pointer operator->() const {
		return m_Ptr;
	}

	const_reference operator*() const {
		return *m_Ptr;
	}

	bool operator==(const Self& rhs) const {
		return m_Ptr == rhs.m_Ptr;
	}

	bool operator!=(const Self& rhs) const {
		return !(*this == rhs);
	}

private:
	const_pointer m_Ptr;

};

template <typename _Ty>
class Vector {

public:

	// Member types

	typedef std::size_t size_type;
	typedef _Ty value_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef _Ty&& rvalue_reference;
	typedef Vector<_Ty> Self;
	typedef Iterator<Vector<_Ty>> iterator;
	typedef ConstIterator<Vector<_Ty>> const_iterator;
	typedef ReverseIterator<Vector<_Ty>> reverse_iterator;
	typedef ConstReverseIterator<Vector<_Ty>> const_reverse_iterator;


	// Constructors / Destructors

	Vector() noexcept
		: m_Size{ 0 }, m_Capacity{ 0 }, m_Data{ nullptr } {
	}
	Vector(const size_type& capacity)
		: m_Size{ 0 }, m_Capacity{ capacity }, m_Data{ nullptr } {
		_ReAllocate(_TestCapacity(capacity));
	}
	Vector(std::initializer_list<value_type>&& values)
		: Vector(_IncreaseCapacity(values.size())) {
		m_Size = values.size();
		pointer it = m_Data;
		for (const_reference value : values)
			new(it++) value_type{ std::move(value) };
	}

	~Vector() {
		Clear();
		_DeallocateOldBlock(m_Data, m_Capacity);
	}

	static Self MakeEmpty() noexcept {
		return Self();
	}


	// Element access

	reference operator[](const size_type& idx) {
		return m_Data[idx];
	}
	const_reference operator[](const size_type& idx) const {
		return m_Data[idx];
	}

	reference At(const size_type& idx) {
		if (idx >= m_Size)
			throw std::out_of_range("VECTOR::AT::index out of range");
		return m_Data[idx];
	}
	const_reference At(const size_type& idx) const {
		if (idx >= m_Size)
			throw std::out_of_range("VECTOR::AT::index out of range");
		return m_Data[idx];
	}

	reference Front() {
		return m_Data[0];
	}
	const_reference Front() const {
		return m_Data[0];
	}

	reference Back() {
		return m_Data[m_Size - 1];
	}
	const_reference Back() const {
		return m_Data[m_Size - 1];
	}

	pointer Data() {
		return m_Data;
	}
	const_pointer Data() const {
		return m_Data;
	}


	// Itarators

	iterator begin() const noexcept {
		return iterator{ m_Data };
	}

	iterator end() const noexcept {
		return iterator{ m_Data + m_Size };
	}

	const_iterator cbegin() const noexcept {
		return const_iterator{ m_Data };
	}

	const_iterator cend() const noexcept {
		return const_iterator{ m_Data + m_Size };
	}

	reverse_iterator rbegin() const noexcept {
		return reverse_iterator{ m_Data + m_Size - 1 };
	}

	reverse_iterator rend() const noexcept {
		return reverse_iterator{ m_Data - 1 };
	}

	const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator{ m_Data + m_Size - 1 };
	}

	const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator{ m_Data - 1 };
	}


	// Capacity

	void Reserve(const size_type& capacity) {
		m_Capacity = capacity;
	}

	size_type Size() const {
		return m_Size;
	}

	size_type Capacity() const {
		return m_Capacity;
	}

	bool Empty() const noexcept {
		return m_Size == 0;
	}


	// Modifiers

	void Clear() {
		_CallElementDestructors(m_Data, m_Size);
		m_Size = 0;
	}

	iterator Insert(iterator pos, const_reference value) {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		for (iterator i = end(); i > pos; --i) {
			new(i.operator->()) value_type{ std::move(*(i - 1)) };
			(*(i - 1)).~value_type();
		}
		*pos = value;
		++m_Size;
		return ++pos;
	}
	iterator Insert(iterator pos, rvalue_reference value) {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		for (iterator i = end(); i > pos; --i) {
			new(i.operator->()) value_type{ std::move(*(i - 1)) };
			(*(i - 1)).~value_type();
		}
		*pos = std::move(value);
		++m_Size;
		return ++pos;
	}

	template <typename... Args>
	iterator Emplace(iterator pos, Args&&... args) {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		for (iterator i = end(); i > pos; --i) {
			new(i.operator->()) value_type{ std::move(*(i - 1)) };
			(*(i - 1)).~value_type();
		}
		new(pos.operator->()) value_type{ std::forward<Args>(args)... };
		++m_Size;
		return ++pos;
	}

	iterator Erase(iterator pos) {
		(*(pos)).~value_type();
		for (iterator i = pos + 1; i < end(); ++i) {
			new((i - 1).operator->()) value_type{ std::move(*(i)) };
			(*i).~value_type();
		}
		if (m_Size > 0)
			--m_Size;
		return ++pos;
	}

	void PushBack(const_reference value) {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		m_Data[m_Size++] = value;
	}
	void PushBack(rvalue_reference value) noexcept {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		m_Data[m_Size++] = std::move(value);
	}

	template <typename... Args>
	void EmplaceBack(Args&&... args) noexcept {
		if (m_Size >= m_Capacity)
			_ReAllocate(_TestCapacity(_IncreaseCapacity(m_Capacity)));
		new(&m_Data[m_Size++]) value_type{ std::forward<Args>(args)... };
	}

	void PopBack() {
		if (m_Size > 0)
			--m_Size;
		m_Data[m_Size].~value_type();
	}


private:

	static size_type _IncreaseCapacity(const size_type& capacity) noexcept {
		return capacity + (capacity % 2 == 0 ? capacity : capacity + 1) / 2;
	}

	static size_type _TestCapacity(const size_type& capacity) noexcept {
		return capacity < 1
			? 1
			: capacity;
	}

	static void _AllocateNewBlock(pointer& newBlock, const size_type& capacity) {
		newBlock = static_cast<pointer>(::operator new(capacity * sizeof(value_type)));
	}

	static void _DeallocateOldBlock(pointer& oldBlock, const size_type& capacity) {
		::operator delete[](oldBlock, capacity * sizeof(value_type));
	}

	static void _CallElementDestructors(pointer data, const size_type& size) {
		for (size_type i{ 0 }; i < size; ++i)
			data[i].~value_type();
	}

	void _ReAllocate(const size_type& newCapacity) {
		pointer newData{ nullptr };
		_AllocateNewBlock(newData, newCapacity);

		if (m_Size > newCapacity)
			m_Size = newCapacity;

		for (size_type i{ 0 }; i < m_Size; ++i)
			new(&newData[i]) value_type{ std::move(m_Data[i]) };

		_CallElementDestructors(m_Data, m_Size);
		_DeallocateOldBlock(m_Data, m_Capacity);

		m_Data = newData;
		m_Capacity = newCapacity;
	}


	// Member variables

	size_type m_Size;
	size_type m_Capacity;
	pointer m_Data;

};