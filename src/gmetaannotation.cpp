#include "cpgf/gmetaannotation.h"
#include "cpgf/gmetatype.h"

#include <vector>

#include <string.h>


namespace cpgf {

namespace meta_internal {

class GAnnotationItemImplement
{
public:
	GAnnotationItemImplement(const std::string & name) : name(name) {
	}

	~GAnnotationItemImplement() {
	}
	
	std::string name;
};


class GMetaAnnotationImplement
{
public:
	typedef std::vector<GAnnotationItem *> ListType;

public:
	ListType annotationItems;
};


} // namespace meta_internal



GAnnotationValue::GAnnotationValue(const GAnnotationValue & other)
{
	this->var = other.var;

	if(vtGetType(this->var.data.typeData) == meta_internal::vtAnnoString) {
		this->var.data.valueObject = meta_internal::duplicateAnnoString(const_cast<const std::string *>(static_cast<const volatile std::string *>(other.var.data.valueObject))->c_str());
	}
	else {
		if(vtGetType(this->var.data.typeData) == meta_internal::vtAnnoWideString) {
			this->var.data.valueObject = meta_internal::duplicateAnnoWideString(const_cast<const std::wstring *>(static_cast<const volatile std::wstring *>(other.var.data.valueObject))->c_str());
		}
	}
}

GAnnotationValue & GAnnotationValue::operator = (GAnnotationValue other)
{
	this->swap(other);

	return *this;
}

GAnnotationValue::~GAnnotationValue()
{
	if(vtGetType(this->var.data.typeData) == meta_internal::vtAnnoString) {
		delete static_cast<const volatile std::string *>(this->var.data.valueObject);
	}
	else {
		if(vtGetType(this->var.data.typeData) == meta_internal::vtAnnoWideString) {
			delete static_cast<const volatile std::wstring *>(this->var.data.valueObject);
		}
	}
}

void GAnnotationValue::swap(GAnnotationValue & other)
{
	using std::swap;

	swap(this->var, other.var);
}

const GVariant * GAnnotationValue::getVariant() const
{
	return &this->var;
}

bool GAnnotationValue::canToString() const
{
	return this->var.getType() == meta_internal::vtAnnoString;
}

bool GAnnotationValue::canToWideString() const
{
	return this->var.getType() == meta_internal::vtAnnoWideString;
}

bool GAnnotationValue::canToInt() const
{
	return canFromVariant<int>(this->var);
}

const char * GAnnotationValue::toString() const
{
	return const_cast<const std::string *>(static_cast<const volatile std::string *>(this->var.data.valueObject))->c_str();
}

const wchar_t * GAnnotationValue::toWideString() const
{
	return const_cast<const std::wstring *>(static_cast<const volatile std::wstring *>(this->var.data.valueObject))->c_str();
}

int GAnnotationValue::toInt() const
{
	return fromVariant<int>(this->var);
}

bool GAnnotationValue::toBoolean() const
{
	return fromVariant<bool>(this->var);
}


GAnnotationItem::GAnnotationItem()
	: implement(new meta_internal::GAnnotationItemImplement("")), value()
{
}

GAnnotationItem::~GAnnotationItem()
{
}

GAnnotationItem::GAnnotationItem(const char * name, const GAnnotationValue & value)
	: implement(new meta_internal::GAnnotationItemImplement(name)), value(value)
{
}

GAnnotationItem::GAnnotationItem(const GAnnotationItem & other)
{
	this->implement.reset(new meta_internal::GAnnotationItemImplement(other.implement->name.c_str()));
	this->value = other.value;
}

GAnnotationItem & GAnnotationItem::operator = (const GAnnotationItem & other)
{
	if(this != &other) {
		this->implement->name = other.implement->name;
		this->value = other.value;
	}

	return *this;
}

const char * GAnnotationItem::getName() const
{
	return this->implement->name.c_str();
}

const GAnnotationValue * GAnnotationItem::getValue() const
{
	return &this->value;
}




GMetaAnnotation::GMetaAnnotation(const char * name)
	: super(name, GMetaType(), mcatAnnotation), implement(new meta_internal::GMetaAnnotationImplement), metaItem(NULL) {
}

GMetaAnnotation::~GMetaAnnotation() {
	this->clear();
}

void GMetaAnnotation::clear()
{
	for(meta_internal::GMetaAnnotationImplement::ListType::iterator it = this->implement->annotationItems.begin(); it != this->implement->annotationItems.end(); ++it) {
		delete *it;
	}
}

void GMetaAnnotation::doAddItem(GAnnotationItem * item)
{
	this->implement->annotationItems.push_back(item);
}

const GMetaItem * GMetaAnnotation::getMetaItem() const
{
	return this->metaItem;
}

const GAnnotationValue * GMetaAnnotation::getValue(const char * name) const
{
	for(meta_internal::GMetaAnnotationImplement::ListType::const_iterator it = this->implement->annotationItems.begin(); it != this->implement->annotationItems.end(); ++it) {
		if(strcmp((*it)->getName(), name) == 0) {
			return (*it)->getValue();
		}
	}

	return NULL;
}

size_t GMetaAnnotation::getCount() const
{
	return this->implement->annotationItems.size();
}

const char * GMetaAnnotation::getNameAt(size_t index) const
{
	return this->implement->annotationItems[index]->getName();
}

const GAnnotationValue * GMetaAnnotation::getValueAt(size_t index) const
{
	return this->implement->annotationItems[index]->getValue();
}

void GMetaAnnotation::setMetaItem(const GMetaItem * metaItem)
{
	this->metaItem = metaItem;
}

GMetaExtendType GMetaAnnotation::getItemExtendType(uint32_t flags) const
{
	(void)flags;
	
	return GMetaExtendType();
}


} // namespace cpgf
