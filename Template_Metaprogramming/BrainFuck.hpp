#pragma once

#ifndef BRAINFUCK_H

#define BRAINFUCK_H

#include <Timothy_all.h>

#include <cstddef>
#include <cstdint>

__TIMOTHY_NAMESPACE_BEGIN

template <std::size_t memSize, std::size_t outSize>
class BrainFuck
{
public:

	using Byte = std::uint8_t;

	template <std::size_t size>
	class ByteArray
	{
	public:

		constexpr ByteArray() = default;
		constexpr ByteArray(const ByteArray&) = default;
		[[nodiscard]] constexpr const Byte* GetArr() const { return arr; }
		[[nodiscard]] constexpr std::size_t GetLength() const { return length; }
		constexpr void Push(const Byte& ch) { arr[length++] = ch; }
		[[nodiscard]] constexpr Byte operator[](std::ptrdiff_t idx) const { return arr[idx]; }
		[[nodiscard]] constexpr Byte& operator[](std::ptrdiff_t idx) { return arr[idx]; }

	private:
		std::size_t length{ 0u };
		Byte arr[size]{ 0 };
	};

	template <typename IStream, typename InputCharType>
	static constexpr ByteArray<outSize> Eval(IStream& xin, const InputCharType* const in)
	{
		ByteArray<outSize> out{};
		Parser<memSize>(in, out, xin);
		return out;
	}

private:

	template <typename IStream, typename InputCharType, std::size_t outSize>
	static constexpr std::ptrdiff_t Parser(const InputCharType* const in, ByteArray<outSize>& out, std::uint8_t*& memptr, bool skip, IStream& xin)
	{
		const InputCharType* pIn = in;
		while (*pIn)
		{
			switch (static_cast<uint8_t>(*pIn))
			{
			case '+': if (!skip)++* memptr; break;
			case '-': if (!skip)--* memptr; break;
			case '<': if (!skip) --memptr; break;
			case '>': if (!skip) ++memptr; break;
			case '.': if (!skip) out.Push(*memptr); break;
			case ',': if (!skip) *memptr = xin.get(); break;
			case '[':
				if (!skip) while (*memptr) Parser(pIn + 1, out, memptr, false, xin);
				pIn += Parser(pIn + 1, out, memptr, true, xin) + 1;
				break;
			case ']': return pIn - in;
			}
			++pIn;
		}
		return pIn - in;
	}

	template <std::size_t memSize, std::size_t outSize, typename IStream, typename InputCharType>
	static constexpr std::ptrdiff_t Parser(const InputCharType* const in, ByteArray<outSize>& out, IStream& xin)
	{
		std::uint8_t memory[memSize]{ 0 };
		std::uint8_t* memptr = memory;
		return Parser(in, out, memptr, false, xin);
	}
};

__TIMOTHY_NAMESPACE_END

#endif // !BRAINFUCK_H
