#include "Utils.h"
using namespace BloombergLP;
using namespace blpapi;

std::string ElementTypeString(const int & input)
{
	std::string tmp;
	switch (input) {
	case 1:
		tmp = "BOOL";
		break;
	case 2:
		tmp = "CHAR";
		break;
	case 3:
		tmp = "BYTE";
		break;
	case 4:
		tmp = "INT32";
		break;
	case 5:
		tmp = "INT64";
		break;
	case 6:
		tmp = "FLOAT32";
		break;
	case 7:
		tmp = "FLOAT64";
		break;
	case 8:
		tmp = "STRING";
		break;
	case 9:
		tmp = "BYTEARRAY";
		break;
	case 10:
		tmp = "DATE";
		break;
	case 11:
		tmp = "TIME";
		break;
	case 12:
		tmp = "DECIMAL";
		break;
	case 13:
		tmp = "DATETIME";
		break;
	case 14:
		tmp = "ENUMERATION";
		break;
	case 15:
		tmp = "SEQUENCE";
		break;
	case 16:
		tmp = "CHOICE";
		break;
	case 17:
		tmp = "CORRELATION_ID";
		break;
	}
	return tmp;
}

void printElem(std::fstream &os,const blpapi::Element &e,const int &elemtype) {
	switch (elemtype) {
	case 1:
		os << e.getValueAsBool();
		break;
	case 2:
		os << e.getValueAsChar();
		break;
	case 3:
		os << "Byte: not treated";
		break;
	case 4:
		os << e.getValueAsInt32();
		break;
	case 5:
		os << e.getValueAsInt64();
		break;
	case 6: case 12:
		os << e.getValueAsFloat32();
		break;
	case 7:
		os << e.getValueAsFloat64();
		break;
	case 8:
		os << e.getValueAsString();
		break;
	case 9:
		os << "Bytearray: not treated";
		break;
	case 10: case 11:case 13:
		std::cout << "sort out dates later";
		//os << e.getValueAsDatetime();
		break;
	case 14:
		os << "Enum: not treated";
		break;
	case 15:
		os << "Sequence: not treated";
		break;
	case 16:
		os << "Choice: not treated";
		break;
	case 17:
		os << e.getValueAsString();
		break;
	default:
		os << "Type " << elemtype << " not recognized";
	}
}
void printElem(const blpapi::Element &e,const  int &elemtype) {
	switch (elemtype) {
	case 1:
		std::cout << e.getValueAsBool();
		break;
	case 2:
		std::cout << e.getValueAsChar();
		break;
	case 3:
		std::cout << "Byte: not treated";
		break;
	case 4:
		std::cout << e.getValueAsInt32();
		break;
	case 5:
		std::cout << e.getValueAsInt64();
		break;
	case 6: case 12:
		std::cout << e.getValueAsFloat32();
		break;
	case 7:
		std::cout << e.getValueAsFloat64();
		break;
	case 8:
		std::cout << e.getValueAsString();
		break;
	case 9:
		std::cout << "Bytearray: not treated";
		break;
	case 10: case 11:case 13:
		std::cout << e.getValueAsDatetime();
		break;
	case 14:
		std::cout << "Enum: not treated";
		break;
	case 15:
		std::cout << "Sequence: not treated";
		break;
	case 16:
		std::cout << "Choice: not treated";
		break;
	case 17:
		std::cout << e.getValueAsString();
		break;
	default:
		std::cout << "Type " << elemtype << " not recognized";
	}
}
std::ostream &printElem(std::ostream &os, const blpapi::Element &e, const int &elemtype) {
	switch (elemtype) {
	case 1:
		os << e.getValueAsBool();
		break;
	case 2:
		os << e.getValueAsChar();
		break;
	case 3:
		os << "Byte: not treated";
		break;
	case 4:
		os << e.getValueAsInt32();
		break;
	case 5:
		os << e.getValueAsInt64();
		break;
	case 6: case 12:
		os << e.getValueAsFloat32();
		break;
	case 7:
		os << e.getValueAsFloat64();
		break;
	case 8:
		os << e.getValueAsString();
		break;
	case 9:
		os << "Bytearray: not treated";
		break;
	case 10: case 11:case 13:
		os << e.getValueAsDatetime();
		break;
	case 14:
		os << "Enum: not treated";
		break;
	case 15:
		os << "Sequence: not treated";
		break;
	case 16:
		os << "Choice: not treated";
		break;
	case 17:
		os << e.getValueAsString();
		break;
	default:
		os << "Type " << elemtype << " not recognized";
	}
	return os;
}

std::string fields_string(const std::vector<std::string>& vec)
{
	std::string tmp;
	int i{ 0 };
	for (const auto &f : vec) {
		if (i == 0)
			tmp += f;
		if (i > 0)
			tmp +=  (","+f);
		++i;
	}
	return tmp;
}
