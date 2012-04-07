#include "testserializationcommon.h"
#include "cpgf/serialization/gmetaxmlarchive.h"


#include <stdio.h>


using namespace std;
using namespace cpgf;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996)
#endif


MetaReaderGetterXml::MetaReaderGetterXml(IMetaService * service, GMetaXmlArchive & outputArchive)
	: service(service), outputArchive(outputArchive)
{
}

IMetaReader * MetaReaderGetterXml::get() const
{
	if(! this->reader) {
		stringstream stream;
		this->outputArchive.saveToStream(stream);
		this->inputArchive.loadNonIntrusive(stream.str().c_str());
		this->reader.reset(cpgf::createXmlMetaReader(this->service, this->inputArchive));
	}
	return this->reader.get();
}


void initTestValue(bool & value, long long seed)
{
	value = ((seed % 2) != 0);
}

void initTestValue(char & value, long long seed)
{
	value = 'a' + (seed % 26);
}

void initTestValue(wchar_t & value, long long seed)
{
	value = 'a' + (seed % 26);
}

void initTestValue(signed char & value, long long seed)
{
	value = 'a' + (seed % 26);
}

void initTestValue(unsigned char & value, long long seed)
{
	value = 'a' + (seed % 26);
}

void initTestValue(std::string & value, long long seed)
{
	char buffer[100];
	sprintf(buffer, "STL-string:%d", (int)seed);
	value = buffer;
}

void initTestValue(float & value, long long seed)
{
	value = (float)(seed % 1000) + (seed % 2 == 0 ? 0.5f : 0.8f);
}

void initTestValue(double & value, long long seed)
{
	value = (float)(seed % 1000) + (seed % 2 == 0 ? 0.5f : 0.8f);
}

void initTestValue(long double & value, long long seed)
{
	value = (float)(seed % 1000) + (seed % 2 == 0 ? 0.5f : 0.8f);
}

long long getTestSeed(int n)
{
return n;
/*
	long long seed = 0x739521LL;
	
	seed <<= (n % 32);
	seed += n;

	return seed;
*/	
}