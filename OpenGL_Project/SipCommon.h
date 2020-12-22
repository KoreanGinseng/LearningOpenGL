#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <tchar.h>

#include <string>
#include <codecvt>

#include <compare>
#include <filesystem>

namespace sip
{
	using convert_t = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_t, wchar_t> strconverter;

	std::string to_string(std::wstring wstr)
	{
		return strconverter.to_bytes(wstr);
	}

	std::wstring to_wstring(std::string str)
	{
		return strconverter.from_bytes(str);
	}

	void SIP_PRINTLOG(const _TCHAR* fmt, ...)
	{
		_TCHAR buf[512];
		va_list ap;
		va_start(ap, fmt);
		_vsntprintf(buf, 511, fmt, ap);
		buf[511] = 0;
		OutputDebugString(buf);
	}
}