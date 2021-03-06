#pragma once

class xEXPORT xGroup
{
	friend class xRegex;
	friend class xMatch;
public:
	xGroup();
	virtual ~xGroup();

	size_t Index() const;
	size_t Length() const;
	xString Value() const;
protected:
	size_t	mIndex;
	size_t	mLength;
	xString	mValue;
};

class xEXPORT xGroupCollection
{
	friend class xRegex;
public:
	typedef xArray<xGroup*>::Iterator Iterator;

	xGroupCollection();
	~xGroupCollection();

	Iterator Begin() const;
	Iterator End() const;

	const xGroup& operator[](int index) const;
	size_t Count() const;
protected:
	xArray<xGroup*>	mGroups;
};

class xEXPORT xMatch : public xGroup
{
	friend class xRegex;
public:
	xMatch();

	bool Success() const;

	xGroupCollection Groups;
protected:
	bool mSuccess;
};

class xEXPORT xMatchCollection
{
	friend class xRegex;
public:
	typedef xArray<xMatch*>::Iterator Iterator;

	xMatchCollection();
	~xMatchCollection();

	Iterator Begin() const;
	Iterator End() const;

	const xMatch& operator[](int index) const;
	size_t Count() const;
protected:
	xArray<xMatch*>	mMatches;
};


struct xRegexOptions
{
	enum Flags
	{
		None			= 0,
		IgnoreCase		= 1 << 0,
		Multiline		= 1 << 1
	};
};

xDEFINE_FLAGS(xRegexOptions::Flags)

class xEXPORT xRegex
{
	xHIDE_IMPLEMENTATION
public:
	xRegex(const xString& pattern, xRegexOptions::Flags options = xRegexOptions::None);
	~xRegex();

	bool IsMatch(const xString& input);
	bool Match(const xString& input, xMatch& match);
	bool Matches(const xString& input, xMatchCollection& matches);
	xString Replace(const xString& input, const xString replacement);

	static bool IsMatch(const xString& input, const xString& pattern, xRegexOptions::Flags options = xRegexOptions::None);
	static bool Match(const xString& input, const xString& pattern, xMatch& match, xRegexOptions::Flags options = xRegexOptions::None);
	static bool Matches(const xString& input, const xString& pattern, xMatchCollection& matches, xRegexOptions::Flags options = xRegexOptions::None);
	static xString Replace(const xString& input, const xString& pattern, const xString replacement, xRegexOptions::Flags options = xRegexOptions::None);
};