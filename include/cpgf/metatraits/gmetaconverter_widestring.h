#ifndef __GMETACONVERTER_WIDESTRING_H
#define __GMETACONVERTER_WIDESTRING_H

#include "cpgf/metatraits/gmetaconverter.h"

#include <string>


namespace cpgf {

namespace metatraits_internal {

	IMetaConverter * doCreateConverterForStdWideString();

} // namespace metatraits_internal


template <>
struct GMetaTraitsCreateConverter <std::wstring>
{
	static IMetaConverter * createConverter(const GMetaTraitsParam &) {
		return metatraits_internal::doCreateConverterForStdWideString();
	}
};



} // namespace cpgf



#endif
