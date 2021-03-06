////////////////////////////////////////////////////////////////////////////////
// Filename: FDataSeeker.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FDataSeeker_H_
#define _FDataSeeker_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FDataSeeker
////////////////////////////////////////////////////////////////////////////////
class FDataSeeker
{
public:

public:
	FDataSeeker();
	FDataSeeker(const FDataSeeker&);
	~FDataSeeker();

	// Get x amount of bytes from the data
	void Get(unsigned int _amount, unsigned char* _from, void* _to, bool _useMemcpy = true);

	// Seek to the x position inside the file
	void Seek(unsigned long _position);

private:

	// The current position inside the data
	unsigned long m_DataPosition;
};

#endif
